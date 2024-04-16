#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

/*
BEGIN_JUCE_MODULE_DECLARATION

 ID:               juce_circle_layout
 vendor:           LeonPS
 version:          1.0.0
 name:             Juce Circle Layout
 description:      An easy to use 'flex-box' style utility for layouts based around circles.
 license:          MIT
 dependencies:     juce_gui_basics

END_JUCE_MODULE_DECLARATION
*/

struct Circle
{
    float rotation_radians;
    float radius;
    juce::Point<float> centre;

    [[nodiscard]] Circle WithRotationRadians (float new_rotation) const;
    [[nodiscard]] Circle WithRotationDegrees (float new_rotation) const;
    [[nodiscard]] Circle WithRadius (float new_radius) const;
    [[nodiscard]] Circle WithCentre (juce::Point<float> new_centre) const;
    [[nodiscard]] Circle WithBounds (juce::Rectangle<float> bounds) const;
    [[nodiscard]] float GetArea () const;
    [[nodiscard]] juce::Point<float> GetPointOnCircumferenceForAngleRadians (float angle) const;
    [[nodiscard]] juce::Point<float> GetPointOnCircumferenceForAngleDegrees (float angle) const;
    [[nodiscard]] juce::Path GetPath () const;
    [[nodiscard]] juce::Rectangle<float> GetEnclosingBounds () const;
};

struct CircleLayout
{
    enum class Anchor
    {
        kCentre,
        kCircumference
    };

    enum class OffsetSpecifier
    {
        kRelative,
        kAbsolute
    };

    struct Item
    {
        Anchor anchor;
        Circle circle;

        OffsetSpecifier offset_specifier;
        juce::Point<float> offset;

        Circle layout;
        CircleLayout * circle_layout;

        Circle * scoped_layout;

        [[nodiscard]] Item WithCircleLayout (CircleLayout & new_circle_layout) const;
        [[nodiscard]] Item WithScopedLayout (Circle & new_scoped_layout) const;
        [[nodiscard]] Item WithAnchor (Anchor new_anchor) const;
        [[nodiscard]] Item WithCircle (Circle new_circle) const;
        [[nodiscard]] Item WithOffsetAbsolute (juce::Point<float> new_offset) const;
        [[nodiscard]] Item WithOffsetRelative (juce::Point<float> new_offset) const;
    };

    juce::Array<Item> items;

    void PerformLayout (Circle circle);
    void PerformLayout (juce::Rectangle<float> bounds);
};