#pragma once

#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

class CircleLayoutExamples : public juce::AnimatedAppComponent {
public:
    CircleLayoutExamples();
    ~CircleLayoutExamples() override = default;

    void paint (juce::Graphics & g) override;
    void update () override;
private:
    float rotation_ = 0.f;
};
