find_path(kfr_INCLUDE_DIR NAMES kfr/kfr.h)

get_filename_component(_prefix_path ${kfr_INCLUDE_DIR} PATH)

find_library(
    kfr_io_LIBRARY_DEBUG
    NAMES kfr_io
    PATHS ${_prefix_path}/debug/lib
    NO_DEFAULT_PATH
)

find_library(
    kfr_io_LIBRARY_RELEASE
    NAMES kfr_io
    PATHS ${_prefix_path}/lib
    NO_DEFAULT_PATH
)

unset(_prefix_path)

include(SelectLibraryConfigurations)
select_library_configurations(kfr_io)
