#include "juce_circle_layout.h"

Circle Circle::WithRotationRadians (float new_rotation) const
{
    auto circle = *this;
    circle.rotation_radians = new_rotation;
    return circle;
}

Circle Circle::WithRotationDegrees (float new_rotation) const
{
    return WithRotationRadians (new_rotation * juce::MathConstants<float>::pi / 180.0f);
}

Circle Circle::WithRadius (float new_radius) const
{
    auto circle = *this;
    circle.radius = new_radius;
    return circle;
}

Circle Circle::WithCentre (juce::Point<float> new_centre) const
{
    auto circle = *this;
    circle.centre = new_centre;
    return circle;
}

Circle Circle::WithBounds (juce::Rectangle<float> bounds) const
{
    auto circle = *this;
    return circle.WithRadius (std::min (bounds.getWidth (), bounds.getHeight ()) / 2.f)
        .WithCentre (bounds.getCentre ());
}

float Circle::GetArea () const
{
    return juce::MathConstants<float>::pi * std::pow (radius, 2);
}

juce::Point<float> Circle::GetPointOnCircumferenceForAngleRadians (float angle) const
{
    return centre.getPointOnCircumference (radius, angle + rotation_radians);
}

juce::Point<float> Circle::GetPointOnCircumferenceForAngleDegrees (float angle) const
{
    return GetPointOnCircumferenceForAngleRadians (angle *
                                                   (juce::MathConstants<float>::pi / 180.0f));
}

juce::Path Circle::GetPath () const
{
    juce::Path circle_path;
    circle_path.addEllipse (centre.x - radius, centre.y - radius, radius * 2.f, radius * 2.f);
    return circle_path;
}

juce::Rectangle<float> Circle::GetEnclosingBounds () const
{
    return GetPath ().getBounds ();
}

CircleLayout::Item CircleLayout::Item::WithCircleLayout (CircleLayout & new_circle_layout) const
{
    auto item = *this;
    item.circle_layout = &new_circle_layout;
    return item;
}

CircleLayout::Item CircleLayout::Item::WithScopedLayout (Circle & new_scoped_layout) const
{
    auto item = *this;
    item.scoped_layout = &new_scoped_layout;
    return item;
}

CircleLayout::Item CircleLayout::Item::WithAnchor (Anchor new_anchor) const
{
    auto item = *this;
    item.anchor = new_anchor;
    return item;
}

CircleLayout::Item CircleLayout::Item::WithCircle (Circle new_circle) const
{
    auto item = *this;
    item.circle = new_circle;
    return item;
}

CircleLayout::Item CircleLayout::Item::WithOffsetAbsolute (juce::Point<float> new_offset) const
{
    auto item = *this;
    item.offset = new_offset;
    item.offset_specifier = OffsetSpecifier::kAbsolute;
    return item;
}

CircleLayout::Item CircleLayout::Item::WithOffsetRelative (juce::Point<float> new_offset) const
{
    auto item = *this;
    item.offset = new_offset;
    item.offset_specifier = OffsetSpecifier::kRelative;
    return item;
}

static void LayoutCircumferenceItem (const Circle & circle, CircleLayout::Item & item)
{
    auto position_along_circumference =
        circle.GetPointOnCircumferenceForAngleRadians (item.circle.rotation_radians);
    item.layout = item.layout.WithCentre (position_along_circumference);
}

static void LayoutCentreItem (const Circle & circle, CircleLayout::Item & item)
{
    item.layout = item.layout.WithCentre (circle.centre);
}

static void ApplyOffset (CircleLayout::Item & item, juce::Point<float> offset)
{
    auto rotated_offset = offset.rotatedAboutOrigin (item.layout.rotation_radians);
    item.layout = item.layout.WithCentre (rotated_offset + item.layout.centre);
}

static void ApplyOffsetAbsolute (CircleLayout::Item & item)
{
    ApplyOffset (item, item.offset);
}

static void ApplyOffsetRelative (const Circle & circle, CircleLayout::Item & item)
{
    auto scaled_offset = item.offset * circle.radius;
    ApplyOffset (item, scaled_offset);
}

void CircleLayout::PerformLayout (Circle circle)
{
    for (auto & item : items)
    {
        item.layout = item.circle.WithRotationRadians (item.circle.rotation_radians +
                                                       circle.rotation_radians);
        switch (item.anchor)
        {
            case Anchor::kCircumference:
                LayoutCircumferenceItem (circle, item);
                break;
            case Anchor::kCentre:
                LayoutCentreItem (circle, item);
                break;
        }

        switch (item.offset_specifier)
        {
            case OffsetSpecifier::kRelative:
                ApplyOffsetRelative (circle, item);
                break;
            case OffsetSpecifier::kAbsolute:
                ApplyOffsetAbsolute (item);
                break;
        }

        if (item.circle_layout != nullptr)
            item.circle_layout->PerformLayout (item.layout);

        if (item.scoped_layout != nullptr)
            *item.scoped_layout = item.layout;
    }
}

void CircleLayout::PerformLayout (juce::Rectangle<float> bounds)
{
    PerformLayout (Circle ().WithBounds (bounds));
}