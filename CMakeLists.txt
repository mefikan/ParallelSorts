cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)

project(ParallelSorts)

add_executable (ParallelSorts "src/main.cpp" "src/timer_common.h" "src/timer_common.cpp"
        src/sequential_sorts.cpp
        src/sequential_sorts.h
        src/generator.h
        src/generator.cpp
        src/consts.h
        src/check.h
        src/check.cpp
        src/block_sort.cpp
        src/block_sort.h
        src/batcher_true_bitonic_merge.cpp
        src/batcher_true_bitonic_merge.h
        src/thread_pool.cpp
        src/timer_pool.cpp
        src/timer_pool.h
        src/thread_pool.h
        src/batcher_recursive.cpp
        src/batcher_recursive.h
        src/SampleSort.cpp
        src/SampleSort.h
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
