cmake_minimum_required(VERSION 3.11...3.16)

project(BucketGang)

set(ASSETS_DIR ${CMAKE_SOURCE_DIR}/ass)
set(BUILD_ASSETS_DIR ${CMAKE_BINARY_DIR})

add_executable(${PROJECT_NAME} main.cpp player.cpp world.cpp camera.cpp object.cpp anim.cpp bullet.cpp enemy.cpp texture_cache.cpp screen.cpp audio_manager.cpp matildas.cpp gui.cpp)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${ASSETS_DIR} ${BUILD_ASSETS_DIR}
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   ${CMAKE_SOURCE_DIR}/index.html $<TARGET_FILE_DIR:${PROJECT_NAME}>)

if(EMSCRIPTEN)
    include_directories(${CMAKE_SOURCE_DIR}/raylib/src)

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -s WASM=1 -s USE_GLFW=3 -s FULL_ES3=1 -s ASYNCIFY -lnodefs.js")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s USE_GLFW=3 -s ASYNCIFY -lnodefs.js")
    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "--preload-file ${CMAKE_SOURCE_DIR}/ass@/assets")
    target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/raylib/src/libraylib.a)
else()
    target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include)
    target_link_libraries(${PROJECT_NAME} PRIVATE /usr/local/lib/libraylib.a)
endif()
