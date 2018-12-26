find_path(
    QCustomPlot_INCLUDE_DIRS
    NAMES qcustomplot.h
)

if(QCustomPlot_INCLUDE_DIRS)
    get_filename_component(_root_dir ${QCustomPlot_INCLUDE_DIRS} DIRECTORY)

    find_library(
        _qcustomplot_libraries_debug
        NAMES qcustomplotd2
        HINTS ${_root_dir}/debug/lib
    )

    find_library(
        _qcustomplot_libraries_release
        NAMES qcustomplot2
        HINTS ${_root_dir}/lib
    )

    if(_qcustomplot_libraries_debug AND _qcustomplot_libraries_release)
        set(QCustomPlot_LIBRARIES
            debug ${_qcustomplot_libraries_debug}
            optimized ${_qcustomplot_libraries_release}
        )
    elseif(_qcustomplot_libraries_debug)
        set(QCustomPlot_LIBRARIES ${_qcustomplot_libraries_debug})
    elseif(_qcustomplot_libraries_release)
        set(QCustomPlot_LIBRARIES ${_qcustomplot_libraries_release})
    endif()
endif()

include(FindPackageHandleStandardArgs)

find_package_handle_standard_args(
    QCustomPlot
    REQUIRED_VARS QCustomPlot_INCLUDE_DIRS QCustomPlot_LIBRARIES
)

mark_as_advanced(
    QCustomPlot_FOUND
    QCustomPlot_INCLUDE_DIRS QCustomPlot_LIBRARIES
)

if(NOT TARGET QCustomPlot::QCustomPlot)
    add_library(QCustomPlot::QCustomPlot INTERFACE IMPORTED)
    set_target_properties(QCustomPlot::QCustomPlot PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${QCustomPlot_INCLUDE_DIRS}"
    )
endif()
