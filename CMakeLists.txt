cmake_minimum_required(VERSION 3.20)
project(interp-1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 23)

add_executable(main
    main.cpp
    src/parser.cpp
    src/tokenizer.cpp
    src/eval.cpp
)
