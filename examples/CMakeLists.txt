juce_add_gui_app(circle_layout_examples PRODUCT_NAME "circle_layout_examples")

target_sources(circle_layout_examples
        PRIVATE
        Main.cpp
        CircleLayoutExamples.h
        CircleLayoutExamples.cpp)

target_compile_definitions(circle_layout_examples
        PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0)

target_link_libraries(circle_layout_examples
        PRIVATE
        juce::juce_core
        juce::juce_gui_basics
        juce::juce_gui_extra
        juce_circle_layout
        PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags)