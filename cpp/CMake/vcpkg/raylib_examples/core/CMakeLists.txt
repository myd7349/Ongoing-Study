set(raylib_USE_STATIC_LIBS ${USE_MSVC_STATIC_RUNTIME})
set(raylib_VERBOSE ON)
find_package(raylib CONFIG REQUIRED)

set(core_example_sources
    core_2d_camera.c
    core_3d_camera_first_person.c
    core_3d_camera_free.c
    core_3d_mode.c
    core_3d_picking.c
    core_basic_window.c
    core_basic_window_web.c
    core_color_select.c
    core_custom_logging.c
    core_drop_files.c
    core_gestures_detection.c
    core_input_gamepad.c
    core_input_keys.c
    core_input_mouse.c
    core_mouse_wheel.c
    core_multitouch.c
    core_random_values.c
    core_storage_values.c
    core_vr_simulator.c
    core_world_screen.c
)

foreach (example_src ${core_example_sources})
    if (NOT EXISTS "${CMAKE_CURRENT_LIST_DIR}/${example_src}")
        message(STATUS "Downloading ${example_src} ...")
        
        file(DOWNLOAD
            "https://raw.githubusercontent.com/raysan5/raylib/master/examples/core/${example_src}"
            "${CMAKE_CURRENT_LIST_DIR}/${example_src}"
        )
    endif ()

    get_filename_component(example_name ${example_src} NAME_WE)

    add_executable(${example_name} "${CMAKE_CURRENT_LIST_DIR}/${example_src}")
    target_include_directories(${example_name} PRIVATE ${raylib_INCLUDE_DIRS})
    target_link_libraries(${example_name} PRIVATE ${raylib_LIBRARIES})
endforeach ()
