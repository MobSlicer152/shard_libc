cmake_minimum_required(VERSION 3.10)

add_executable(main main/main.c)
add_executable(memccpy string/memccpy.c)

target_link_libraries(main c_shard)
target_link_libraries(memccpy c_shard)
