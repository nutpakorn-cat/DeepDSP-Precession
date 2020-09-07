/*
  ==============================================================================

    AmplifierKnob.cpp
    Created: 2 Sep 2020 5:50:11pm
    Author:  nutpakorn-cat

  ==============================================================================
*/

#include "AmplifierKnob.h"

void AmplifierKnob::setCacheImageId(int otherCacheId) {
    this->cacheId = otherCacheId;
}

void AmplifierKnob::drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                                      const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) {
    const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
    const float pivotX = juce::ImageCache::getFromHashCode(cacheId).getWidth()/2.0;
    const float pivotY = juce::ImageCache::getFromHashCode(cacheId).getHeight()/2.0;
    g.drawImageTransformed(juce::ImageCache::getFromHashCode(cacheId), juce::AffineTransform::rotation(angle, pivotX, pivotY));
}
