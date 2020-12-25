cmake_minimum_required(VERSION 3.10)

add_executable(test_main test_main/main.c)
target_link_libraries(test_main c_shard)
