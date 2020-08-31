/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DeepDspPrecessionAudioProcessorEditor::DeepDspPrecessionAudioProcessorEditor (DeepDspPrecessionAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (1000, 747);
}

DeepDspPrecessionAudioProcessorEditor::~DeepDspPrecessionAudioProcessorEditor()
{
}

//==============================================================================
void DeepDspPrecessionAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    juce::Image backgroundImage = juce::ImageCache::getFromMemory (BinaryData::backgroundpink_png, BinaryData::backgroundpink_pngSize);
    
    backgroundImage = backgroundImage.rescaled(1000, 747);
    g.drawImageAt(backgroundImage, 0, 0);
}

void DeepDspPrecessionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
