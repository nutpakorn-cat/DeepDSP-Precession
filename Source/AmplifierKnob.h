/*
  ==============================================================================

    AmplifierKnob.h
    Created: 2 Sep 2020 5:50:11pm
    Author:  nutpakorn-cat
 
  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class AmplifierKnob :   public juce::LookAndFeel_V4 {
public:
    void setCacheImageId(int otherCacheId);
    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override;
    
private:
    int cacheId;
    juce::Image knobImage;
};
