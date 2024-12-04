cmake_minimum_required(VERSION 3.10)
project(application)

# 设置构建类型为 Debug（如果未指定）
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加编译选项以包含调试信息，并禁用优化（仅限Debug模式）
if(CMAKE_BUILD_TYPE MATCHES "Debug")
    target_compile_options(01_openGL PRIVATE -g)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
endif()

# 查找源文件
file(GLOB_RECURSE SOURCES "*.cpp")

# 创建共享库 (动态库)
add_library(app SHARED ${SOURCES})

# 添加头文件路径
target_include_directories(app PUBLIC
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/../thirdPart/include
)

# 查找并链接 GLFW 动态库
find_library(GLFW_DLL_LIB glfw3dll PATHS ${PROJECT_SOURCE_DIR}/../thirdPart/lib NO_DEFAULT_PATH)
if(NOT GLFW_DLL_LIB)
    message(FATAL_ERROR "Could not find GLFW dynamic import library at specified path")
endif()

# 链接所需的库
target_link_libraries(app PRIVATE
    ${GLFW_DLL_LIB}
    opengl32
    gdi32
)