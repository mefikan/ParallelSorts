# CMakeList.txt: проект CMake для ParallelSorts; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (ParallelSorts "src/main.cpp" "src/batcher_sort.h" "src/batcher_sort.cpp" "src/timer.h" "src/timer.cpp"
        src/sequential_sorts.cpp
        src/sequential_sorts.h
        src/generator.h
        src/generator.cpp
        src/consts.h
        src/show.h
        src/show.cpp
        src/check.h
        src/check.cpp
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ParallelSorts PROPERTY CXX_STANDARD 20)
endif()

# TODO: Добавьте тесты и целевые объекты, если это необходимо.
