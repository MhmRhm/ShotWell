add_library(capture_obj OBJECT
    capture.cpp
)
target_compile_options(capture_obj
	PRIVATE ${DEFAULT_CXX_COMPILE_FLAGS}
	PRIVATE ${DEFAULT_CXX_OPTIMIZE_FLAG}
)
target_include_directories(capture_obj INTERFACE
	"$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
	"$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
)
set_target_properties(capture_obj PROPERTIES
    PUBLIC_HEADER src/capture/include/capture/capture.h
    POSITION_INDEPENDENT_CODE 1
)
target_link_libraries(capture_obj PRIVATE precompiled PRIVATE realsense2)
BuildInfo(capture_obj)

add_library(capture_shared SHARED)
target_link_libraries(capture_shared capture_obj)
add_library(capture_static STATIC)
target_link_libraries(capture_static capture_obj)

add_executable(capture_app main.cpp)
target_link_libraries(capture_app
	PRIVATE precompiled
	PRIVATE capture_static
	PRIVATE ftxui::screen
	PRIVATE ftxui::dom
	PRIVATE ftxui::component
)

include(Coverage)
CleanCoverage(capture_static)
include(Format)
Format(capture_static .)
Format(capture_app .)
include(CppCheck)
AddCppCheck(capture_obj)
include(Doxygen)
Doxygen(capture src/capture)