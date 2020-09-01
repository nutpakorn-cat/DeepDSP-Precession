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
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(lowSlider);
    addAndMakeVisible(lowMidSlider);
    addAndMakeVisible(highMidSlider);
    addAndMakeVisible(trebleSlider);
    addAndMakeVisible(presenceSlider);
    
    gainSlider.setSliderStyle(juce::Slider::Rotary);
    
    lowSlider.setSliderStyle(juce::Slider::Rotary);
    lowMidSlider.setSliderStyle(juce::Slider::Rotary);
    highMidSlider.setSliderStyle(juce::Slider::Rotary);
    trebleSlider.setSliderStyle(juce::Slider::Rotary);
    presenceSlider.setSliderStyle(juce::Slider::Rotary);
    
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 100);
    
    lowSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 100);
    lowMidSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 100);
    highMidSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 100);
    trebleSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 100);
    presenceSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 100, 100);
    
    gainSlider.setRange(0, 5000);
    
    lowSlider.setRange(-10, 10);
    lowMidSlider.setRange(-10, 10);
    highMidSlider.setRange(-10, 10);
    trebleSlider.setRange(-10, 10);
    presenceSlider.setRange(-10, 10);
    
    gainSlider.setValue(audioProcessor.gainSlider);
    
    lowSlider.setValue(audioProcessor.lowSlider);
    lowMidSlider.setValue(audioProcessor.lowMidSlider);
    highMidSlider.setValue(audioProcessor.highMidSlider);
    trebleSlider.setValue(audioProcessor.trebleSlider);
    presenceSlider.setValue(audioProcessor.presenceSlider);
    
    gainSlider.addListener(this);
    
    lowSlider.addListener(this);
    lowMidSlider.addListener(this);
    highMidSlider.addListener(this);
    trebleSlider.addListener(this);
    presenceSlider.addListener(this);
    
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
    
    gainSlider.setBounds(0, 100, 200, 200);
    
    lowSlider.setBounds(100, 100, 200, 200);
    lowMidSlider.setBounds(250, 100, 200, 200);
    highMidSlider.setBounds(400, 100, 200, 200);
    trebleSlider.setBounds(550, 100, 200, 200);
    presenceSlider.setBounds(700, 100, 200, 200);
}

void DeepDspPrecessionAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void DeepDspPrecessionAudioProcessorEditor::sliderValueChanged(juce::Slider *slider) {
    if (slider == &gainSlider) {
        audioProcessor.gainSlider = slider->getValue();
    }
    
    if (slider == &lowSlider) {
        audioProcessor.lowSlider = slider->getValue();
    }
    
    if (slider == &lowMidSlider) {
        audioProcessor.lowMidSlider = slider->getValue();
    }
    
    if (slider == &highMidSlider) {
        audioProcessor.highMidSlider = slider->getValue();
    }
    
    if (slider == &trebleSlider) {
        audioProcessor.trebleSlider = slider->getValue();
    }
    
    if (slider == &presenceSlider)  {
        audioProcessor.presenceSlider = slider->getValue();
    }
}
