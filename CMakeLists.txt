cmake_minimum_required(VERSION 3.20)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(juce_circle_layout VERSION 1.0.0 LANGUAGES CXX
        DESCRIPTION "An easy to use 'flex-box' style utility for layouts based around circles."
        HOMEPAGE_URL "https://github.com/leonp-s/juce_circle_layout")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

if (juce_circle_layout_IS_TOP_LEVEL)
    include(FetchContent)

    include(AddJuce)
    include(AddCatch2)

    juce_add_module(juce_circle_layout)

    add_subdirectory(examples)
else ()
    juce_add_module(juce_circle_layout)
endif ()