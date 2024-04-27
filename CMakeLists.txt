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
        src/batcher_default_merge.cpp
        src/batcher_default_merge.h
        src/batcher_true_merge.cpp
        src/batcher_true_merge.h
)

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
