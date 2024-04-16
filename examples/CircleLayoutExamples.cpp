#include "CircleLayoutExamples.h"
#include "juce_circle_layout/juce_circle_layout.h"

static void StrokeCircle (juce::Graphics & g, const Circle & circle, float line_thickness)
{
    g.strokePath (circle.GetPath (), juce::PathStrokeType (line_thickness));
}

static void StrokeCircles (juce::Graphics & g, std::vector<Circle> & circles, float line_thickness)
{
    auto num_circles_to_draw = circles.size ();
    auto colour_scalar = 1.f / static_cast<float>(num_circles_to_draw);
    for (auto item_index = 0; item_index < num_circles_to_draw; ++item_index)
    {
        auto colour_value = colour_scalar * item_index;
        g.setColour (juce::Colour::fromFloatRGBA (0.f, colour_value, colour_value, 1.f));
        StrokeCircle (g, circles [item_index], line_thickness);
    }
}

CircleLayoutExamples::CircleLayoutExamples ()
{
    setSize (400, 400);
    setSynchroniseToVBlank (true);
    setOpaque (false);
}

void CircleLayoutExamples::paint (juce::Graphics & g)
{
    static constexpr auto kLineThickness = 4.f;

    auto outer_circle = Circle ()
                            .WithBounds (getLocalBounds ().toFloat ().reduced (
                                80.0f - (10.0f * std::sin (rotation_ * 0.2f))))
                            .WithRotationDegrees (rotation_);
    auto small_circle = Circle ().WithRadius (8.0f);
    auto medium_circle = Circle ().WithRadius (40.f);

    CircleLayout orbit_layout;
    orbit_layout.items.add (CircleLayout::Item ()
                                .WithAnchor (CircleLayout::Anchor::kCircumference)
                                .WithCircle (small_circle.WithRotationDegrees (rotation_ * 4.0f)));

    CircleLayout layout;
    layout.items.add (CircleLayout::Item ()
                          .WithAnchor (CircleLayout::Anchor::kCircumference)
                          .WithCircle (small_circle.WithRotationDegrees (rotation_ * 4.0f)));

    layout.items.add (CircleLayout::Item ()
                          .WithAnchor (CircleLayout::Anchor::kCircumference)
                          .WithCircle (small_circle.WithRotationDegrees (rotation_)));

    layout.items.add (CircleLayout::Item ()
                          .WithAnchor (CircleLayout::Anchor::kCentre)
                          .WithOffsetRelative ({0.f, std::sin (rotation_ * 0.1f)})
                          .WithCircle (small_circle));

    layout.items.add (CircleLayout::Item ()
                          .WithAnchor (CircleLayout::Anchor::kCentre)
                          .WithOffsetRelative ({std::sin (rotation_ * 0.2f), 0.f})
                          .WithCircle (small_circle));

    layout.items.add (CircleLayout::Item ()
                          .WithAnchor (CircleLayout::Anchor::kCircumference)
                          .WithOffsetRelative ({0.0f, std::sin (rotation_ * 0.2f) * 0.2f})
                          .WithCircle (small_circle));

    layout.items.add (CircleLayout::Item ()
                          .WithAnchor (CircleLayout::Anchor::kCircumference)
                          .WithCircle (small_circle));

    layout.items.add (CircleLayout::Item ()
                          .WithCircleLayout (orbit_layout)
                          .WithAnchor (CircleLayout::Anchor::kCircumference)
                          .WithCircle (medium_circle.WithRotationDegrees (rotation_)));

    layout.PerformLayout (outer_circle);

    std::vector<Circle> circles;
    circles.push_back (outer_circle);

    for (auto & item : layout.items)
        circles.push_back (item.layout);

    for (auto & item : orbit_layout.items)
        circles.push_back (item.layout);

    StrokeCircles (g, circles, kLineThickness);
}

void CircleLayoutExamples::update ()
{
    rotation_ += static_cast<float> (getMillisecondsSinceLastUpdate ()) * 0.01f;
}
