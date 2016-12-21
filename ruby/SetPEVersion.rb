# encoding: GBK
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
        search_paths << File.dirname(Process.argv0)
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
        if !system(*build_cli(target_pe_file, canonized_version_string))
            puts("Failed to set the version of \"#{target_pe_file}\".")
        end
    end
end


# TODO: require 'optparse'
class CLI
    def parse(args)
        if !args.is_a?(Array)
            raise ArgumentError, '"args" is supposed to be an "Array"'
        end

        @args = args

        @parse_result = {
            :help => @args.empty?,
            :version => false,
        }

        done = false
        assign_value = nil
        @args.each { |argv|
            case argv
            when '-c', '--changelog'
                if !@parse_result.has_key?(:changelog)
                    @parse_result[:changelog] = nil
                    assign_value = ->(value) { @parse_result[:changelog] = value }
                else
                    raise RuntimeError, 'Duplicate "--changelog" arugment'
                end
            when '-t', '--tool-path'
                if !@parse_result.has_key?(:tool)
                    @parse_result[:tool] = nil
                    assign_value = ->(value) { @parse_result[:tool] = value }
                else
                    raise RuntimeError, 'Duplicate "--tool-path" arugment'
                end                
            when '-m', '--module-path'
                if !@parse_result.has_key?(:modules)
                    @parse_result[:modules] = []
                end

                assign_value = ->(value) { @parse_result[:modules] << value }
            when '-h', '--help'
                @parse_result[:help] = true
                done = true
            when '-v', '--version'
                @parse_result[:version] = true
                done = true
            else
                if argv[0] == '-'
                    raise RuntimeError, "Unknown option \"#{argv}\""
                end

                if assign_value
                    assign_value.call(argv)
                end
            end

            if done then break end
        }

        if !@parse_result[:help] && !@parse_result[:version]
            if !@parse_result.has_key?(:modules)
                raise RuntimeError, 'Missing "-m"/"--module-path" option'
            elsif @parse_result[:modules].empty?
                raise RuntimeError, 'At least one module should be specified'
            else
                modules = []
                @parse_result[:modules].each { |item|
                    if !File.exist?(item)
                        raise RuntimeError, "Module \"#{item}\" not found"
                    end

                    if File.directory?(item)
                        Dir.foreach(item) { |entry|
                            entry = File.join(item, entry)
                            if !File.directory?(entry) && File.fnmatch('*.{dll,exe}', entry, File::FNM_EXTGLOB | File::FNM_CASEFOLD)
                                modules << entry
                            end
                        }
                    else
                        modules << item
                    end
                }
                @parse_result[:modules] = modules
            end

            if !@parse_result.has_key?(:tool)
                @parse_result[:tool] = nil
            elsif !@parse_result[:tool]
                raise RuntimeError, 'Missing argument for "-t"/"--tool-path" option'
            end

            if !@parse_result.has_key?(:changelog)
                @parse_result[:changelog] = 'Changelog.txt'
            elsif !@parse_result[:changelog]
                raise RuntimeError, 'Missing argument for "-c"/"--changelog" option'
            else
                if File.directory?(@parse_result[:changelog])
                    @parse_result[:changelog] = File.join(@parse_result[:changelog], "Changelog.txt")
                end

                if !File.exist?(@parse_result[:changelog])
                    raise RuntimeError, "Changelog file \"#{@parse_result[:changelog]}\" not found"
                end
            end
        end
    end

    def run(args)
        parse(args)

        if @parse_result[:help]
            puts(usage)
            return
        elsif @parse_result[:version]
            puts("SetPEVersion v0.1.0")
            return
        end

        version_tool = VersionTool.new(@parse_result[:tool])
        changelog_source = ChangelogSource.new(@parse_result[:changelog])
        version_number = VersionNumberSource.canonize_version_string(changelog_source.version_string)

        @parse_result[:modules].each { |pe|
            version_tool.run(pe, version_number)
        }
    end

    def usage
        'Usage:
  SetPEVersion (--module-path=<PATH>) [--changelog=FILE] [--tool-path=FILE]
  SetPEVersion -h | --help
  SetPEVersion -v | --version

  Options:
    -c FILE --changelog=FILE    Specify the full path of "Changelog.txt"
    -t FILE --tool-path=FILE    Specify the search path of "rcedit.exe"/"StampVer.exe"
    -m PATH --module-path=PATH  Specify a single module file(DLL or EXE) or a directory that contains module files
    -h --help                   Show this help message
    -v --version                Show version message'
    end
end


CLI.new.run(ARGV)


# References:
# [What's the point of ARGV in Ruby?](http://stackoverflow.com/questions/13329132/whats-the-point-of-argv-in-ruby)
# Ongoing-Study/python/SetPEVersion.py
# https://github.com/ryangreenberg/urban_dictionary
