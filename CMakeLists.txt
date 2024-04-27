cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)

project(ParallelSorts)

add_executable (ParallelSorts "src/main.cpp" "src/batcher_sort.h" "src/batcher_sort.cpp" "src/timer_common.h" "src/timer_common.cpp"
        src/sequential_sorts.cpp
        src/sequential_sorts.h
        src/generator.h
        src/generator.cpp
        src/consts.h
        src/show.h
        src/show.cpp
        src/check.h
        src/check.cpp
        src/element.cpp
        src/element.h
        src/new_batcher.cpp
        src/new_batcher.h
        src/thread_pool.cpp
        src/timer_pool.cpp
        src/final_batcher.cpp
        src/final_batcher.h
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
