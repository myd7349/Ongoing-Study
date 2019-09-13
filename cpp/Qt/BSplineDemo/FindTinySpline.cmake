find_path(TINYSPLINE_INCLUDE_DIRS NAMES tinyspline.h tinysplinecpp.h)

find_library(TINYSPLINE_LIBRARY_DEBUG NAMES libtinysplined tinysplined)
find_library(TINYSPLINE_LIBRARY_RELEASE NAMES libtinyspline tinyspline)

find_library(TINYSPLINECPP_LIBRARY_DEBUG NAMES libtinysplinecppd tinysplinecppd)
find_library(TINYSPLINECPP_LIBRARY_RELEASE NAMES libtinysplinecpp tinysplinecpp)

include(SelectLibraryConfigurations)

select_library_configurations(TINYSPLINE)
select_library_configurations(TINYSPLINECPP)

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    TINYSPLINE
    REQUIRED_VARS
        TINYSPLINE_INCLUDE_DIRS
        TINYSPLINE_LIBRARIES
        TINYSPLINECPP_LIBRARIES
)

mark_as_advanced(
    TINYSPLINE_FOUND
    TINYSPLINE_INCLUDE_DIRS
    TINYSPLINE_LIBRARIES
    TINYSPLINECPP_LIBRARIES
)
