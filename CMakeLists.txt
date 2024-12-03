cmake_minimum_required(VERSION 3.10)
project(01_openGL)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # 添加头文件路径
# include_directories(${PROJECT_SOURCE_DIR}/thirdPart/include ${PROJECT_SOURCE_DIR}/include
# ${PROJECT_SOURCE_DIR}/application/include)

# 查找源文件
file(GLOB SOURCES "src/*.cpp")
list(APPEND SOURCES ${PROJECT_SOURCE_DIR}/src/glad.c)

# 添加可执行文件
add_executable(01_openGL ${SOURCES})

# 添加头文件路径
target_include_directories(01_openGL PRIVATE
    ${PROJECT_SOURCE_DIR}/thirdPart/include
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/application/include
)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

# 查找并链接 GLFW 动态库
find_library(GLFW_DLL_LIB glfw3dll PATHS ${PROJECT_SOURCE_DIR}/thirdPart/lib NO_DEFAULT_PATH)
if(NOT GLFW_DLL_LIB)
    message(FATAL_ERROR "Could not find GLFW dynamic import library at specified path")
endif()

#编译子项目app库
add_subdirectory(${PROJECT_SOURCE_DIR}/application ${PROJECT_BINARY_DIR}/application)

# 链接所需的库
target_link_libraries(01_openGL PRIVATE
    app
    ${GLFW_DLL_LIB}
    opengl32
    gdi32
)

# # 添加预编译宏定义（全局）
# add_definitions(-DDEBUG)
# 添加预编译宏定义
target_compile_definitions(01_openGL PRIVATE DEBUG)

# 设置特定目标的输出目录
set_target_properties(01_openGL PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
    ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
    LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin
)

# 确保所有动态库在运行时直接能找到
file(GLOB_RECURSE DLL_FILES 
    "${PROJECT_SOURCE_DIR}/thirdPart/lib/*.dll"
    "$<TARGET_FILE:app>"  # 添加 application 动态库
)
foreach(DLL_FILE IN LISTS DLL_FILES)
    add_custom_command(TARGET 01_openGL POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${DLL_FILE}
        $<TARGET_FILE_DIR:01_openGL>
    )
endforeach()

# # 确保动态库在运行时直接能找到
# add_custom_command(TARGET 01_openGL POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     ${PROJECT_SOURCE_DIR}/thirdPart/lib/glfw3.dll
#     $<TARGET_FILE_DIR:01_openGL>
# )
# # 可选：设置运行时路径，确保运行时能找到动态库
# set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,${PROJECT_SOURCE_DIR}/thirdPart/lib")