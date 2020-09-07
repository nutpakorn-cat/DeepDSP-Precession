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
    juce::Image amplifierKnobImage = juce::ImageCache::getFromMemory (BinaryData::deepdspampknob_png, BinaryData::deepdspampknob_pngSize);
    amplifierKnobImage = amplifierKnobImage.rescaled(60, 60);
    
    juce::Image ioKnobImage = juce::ImageCache::getFromMemory (BinaryData::deepdspioknob_png, BinaryData::deepdspioknob_pngSize);
    ioKnobImage = ioKnobImage.rescaled(75, 75);
    
    juce::ImageCache::addImageToCache(amplifierKnobImage, 0);
    juce::ImageCache::addImageToCache(ioKnobImage, 1);
    
    amplifierKnob.setCacheImageId(0);
    ioKnob.setCacheImageId(1);
    
    addAndMakeVisible(inputSlider);
    addAndMakeVisible(outputSlider);
    
    addAndMakeVisible(gainSlider);
    addAndMakeVisible(lowSlider);
    addAndMakeVisible(lowMidSlider);
    addAndMakeVisible(highMidSlider);
    addAndMakeVisible(trebleSlider);
    addAndMakeVisible(presenceSlider);
    
    inputSlider.setSliderStyle(juce::Slider::Rotary);
    outputSlider.setSliderStyle(juce::Slider::Rotary);
    gainSlider.setSliderStyle(juce::Slider::Rotary);
    lowSlider.setSliderStyle(juce::Slider::Rotary);
    lowMidSlider.setSliderStyle(juce::Slider::Rotary);
    highMidSlider.setSliderStyle(juce::Slider::Rotary);
    trebleSlider.setSliderStyle(juce::Slider::Rotary);
    presenceSlider.setSliderStyle(juce::Slider::Rotary);
    
    inputSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    outputSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    gainSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    lowSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    lowMidSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    highMidSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    trebleSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    presenceSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 100, 100);
    
    inputSlider.setRange(0, 2);
    outputSlider.setRange(0, 4);
    gainSlider.setRange(0, 5000);
    lowSlider.setRange(-10, 10);
    lowMidSlider.setRange(-10, 10);
    highMidSlider.setRange(-10, 10);
    trebleSlider.setRange(-10, 10);
    presenceSlider.setRange(-10, 10);
    
    inputSlider.setSize(75, 75);
    outputSlider.setSize(75, 75);
    gainSlider.setSize(60, 60);
    lowSlider.setSize(60, 60);
    lowMidSlider.setSize(60, 60);
    highMidSlider.setSize(60, 60);
    trebleSlider.setSize(60, 60);
    presenceSlider.setSize(60, 60);
    
    inputSlider.setValue(audioProcessor.inputSlider);
    outputSlider.setValue(audioProcessor.outputSlider);
    gainSlider.setValue(audioProcessor.gainSlider);
    lowSlider.setValue(audioProcessor.lowSlider);
    lowMidSlider.setValue(audioProcessor.lowMidSlider);
    highMidSlider.setValue(audioProcessor.highMidSlider);
    trebleSlider.setValue(audioProcessor.trebleSlider);
    presenceSlider.setValue(audioProcessor.presenceSlider);
    
    gainSlider.setLookAndFeel(&amplifierKnob);
    lowSlider.setLookAndFeel(&amplifierKnob);
    lowMidSlider.setLookAndFeel(&amplifierKnob);
    highMidSlider.setLookAndFeel(&amplifierKnob);
    trebleSlider.setLookAndFeel(&amplifierKnob);
    presenceSlider.setLookAndFeel(&amplifierKnob);
    
    inputSlider.setLookAndFeel(&ioKnob);
    outputSlider.setLookAndFeel(&ioKnob);

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
    juce::Image backgroundImage = juce::ImageCache::getFromMemory (BinaryData::deepdspbackground_png, BinaryData::deepdspbackground_pngSize);
    
    backgroundImage = backgroundImage.rescaled(1000, 747);
    g.drawImageAt(backgroundImage, 0, 0);
    
    int startPosition = 250;
    int yPosition = 480;
    
    int space = 90;
    
    gainSlider.setBounds(startPosition, yPosition, 60, 60);
    lowSlider.setBounds(startPosition + space, yPosition, 60, 60);
    lowMidSlider.setBounds(startPosition + (space * 2), yPosition, 60, 60);
    highMidSlider.setBounds(startPosition + (space * 3), yPosition, 60, 60);
    trebleSlider.setBounds(startPosition + (space * 4), yPosition, 60, 60);
    presenceSlider.setBounds(startPosition + (space * 5), yPosition, 60, 60);
    
    int ioYPosition = 71;
    
    inputSlider.setBounds(110, ioYPosition, 75, 75);
    outputSlider.setBounds(805, ioYPosition, 75, 75);
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
    
    if (slider == &inputSlider) {
        audioProcessor.inputSlider = slider->getValue();
    }
    
    if (slider == &outputSlider) {
        audioProcessor.outputSlider = slider->getValue();
    }
}
