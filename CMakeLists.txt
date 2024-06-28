cmake_minimum_required(VERSION 3.11...3.16)

project(BucketGang)

set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/ass)
set(BUILD_ASSETS_DIR ${CMAKE_BINARY_DIR}/ass)

add_executable(${PROJECT_NAME} main.cpp player.cpp world.cpp camera.cpp object.cpp anim.cpp bullet.cpp enemy.cpp texture_cache.cpp screen.cpp audio_manager.cpp matildas.cpp gui.cpp)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR} ${BUILD_ASSETS_DIR}
)

if(EMSCRIPTEN)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s USE_GLFW=3 -s FULL_ES3=1")
endif()

target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include)
target_link_libraries(${PROJECT_NAME} PRIVATE /usr/local/lib/libraylib.a)
