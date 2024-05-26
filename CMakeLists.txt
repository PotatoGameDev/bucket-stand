cmake_minimum_required(VERSION 3.11...3.16)

project(BucketGang)

add_executable(${PROJECT_NAME} main.cpp player.cpp world.cpp camera.cpp object.cpp anim.cpp bullet.cpp enemy.cpp texture_cache.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE /usr/local/include)
target_link_libraries(${PROJECT_NAME} PRIVATE /usr/local/lib/libraylib.a)
