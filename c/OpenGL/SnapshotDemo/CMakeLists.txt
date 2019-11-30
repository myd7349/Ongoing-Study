cmake_minimum_required(VERSION 3.8)
project(SnapshotDemo C)

find_package(OpenGL REQUIRED)

add_executable(SnapshotDemo
    SnapshotDemo.c
    "${CMAKE_CURRENT_LIST_DIR}/../GLSnapshot.c"
    "${CMAKE_CURRENT_LIST_DIR}/../../Win32/BitmapUtility.c"
)
set_target_properties(SnapshotDemo PROPERTIES WIN32_EXECUTABLE ON)
target_compile_definitions(
    SnapshotDemo
    PRIVATE
        $<$<C_COMPILER_ID:MSVC>:
            _CRT_SECURE_NO_WARNINGS
            _UNICODE
            UNICODE
        >
)
target_link_libraries(SnapshotDemo PRIVATE OpenGL::GL)
