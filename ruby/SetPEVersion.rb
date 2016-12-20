# encoding: UTF-8
# frozen_string_literal: true
#
# = SetPEVersion.rb
#
# A Ruby clone of `Ongoing-Study/python/SetPEVersion.py`.
# `SetPEVersion.py` relies on `StampVer.exe`. This implementation
# can also use `rcedit.exe` as a replacement.
#
# 2016-12-20T18:30:07+08:00


class VersionNumberSource
    # Matchs version numbers of these format:
    # 1.2.3
    # 1.2.3.4
    VERSION_NUMBER_REGEXP = /([0-9]+(?:.[0-9]+){2,3})/

    def version_string
        raise NotImplementedError, ":version_string is not implemented by #{self}"
    end

    def self.canonize_version_string(version_string)
        if !is_version_string?(version_string)
            raise ArgumentError, 'Invalid version string'
        end

        return version_string.count('.') == 3 ? version_string : version_string + '.0'
    end

    def self.is_version_string?(version_string)
        if !version_string.is_a?(String)
            raise ArgumentError, 'A version string should be a "String" object'
        end

        return VERSION_NUMBER_REGEXP =~ version_string
    end

    def self.is_canonized_version_string?(version_string)
        return is_version_string?(version_string) && version_string.count('.') == 3
    end
end


class ChangelogSource < VersionNumberSource
    def initialize(changelog_file, mode="r:UTF-8")
        @changelog_file = changelog_file
        @mode = mode
    end

    def version_string
        File.open(@changelog_file, @mode).each { |line|
            if @@version_number_line_regexp =~ line
                return $1
            end
        }

        return nil
    end

    @@version_number_line_regexp = Regexp.new("^### v#{VERSION_NUMBER_REGEXP}.*$")
end


class VersionTool
    def initialize(tool_search_path=nil)
        @tool_search_path = tool_search_path
        @tool_path = nil
    end

    def build_cli(target_pe_file, canonized_version_string)
        @tool_path = find_tool
        if @tool_path == nil
            raise RuntimeError, 'Neither "rcedit.exe" nor "StampVer.exe" was found'
        end

        if !File.exist?(target_pe_file)
            raise ArgumentError, "\"#{target_pe_file}\" doesn't exist"
        end

        if !VersionNumberSource.is_canonized_version_string?(canonized_version_string)
            raise ArgumentError, "\"#{canonized_version_string}\" is not a canonized version string"
        end

        case @tool_path
        when /rcedit.exe$/i
            return [
                @tool_path,
                target_pe_file,
                '--set-file-version',
                canonized_version_string,
                '--set-product-version',
                canonized_version_string
            ]
        when /StampVer.exe$/i
            cmd = "\"#{@tool_path}\" -k -f\"#{canonized_version_string}\" -p\"#{canonized_version_string}\" \"#{target_pe_file}\""
            return [cmd]
        end
    end

    def find_tool
        search_paths = []

        if @tool_search_path != nil && File.exist?(@tool_search_path)
            if File.directory?(@tool_search_path)
                search_paths << @tool_search_path
            else
                return @tool_search_path
            end
        end

        search_paths << '.'
        search_paths << File.dirname($0)
        search_paths += ENV['path'].split(/;/)

        search_paths.each { |path|
            [
                'rcedit.exe',   # https://github.com/electron/rcedit
                'StampVer.exe', # http://blog.dixo.net/downloads/stampver/
            ].each { |tool_fname|
                fullpath = File.join(path, tool_fname)
                if File.exist?(fullpath)
                    return fullpath
                end
            }
        }

        return nil
    end

    def run(target_pe_file, canonized_version_string)
        Process.exec(*build_cli(target_pe_file, canonized_version_string))
    end
end



# References:
# 