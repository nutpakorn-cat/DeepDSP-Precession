/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DeepDspPrecessionAudioProcessor::DeepDspPrecessionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor (BusesProperties()
        #if ! JucePlugin_IsMidiEffect
        #if ! JucePlugin_IsSynth
                      .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
        #endif
                      .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
        #endif
    ),
    preHighPassFilter(juce::dsp::IIR::Coefficients<float>::makeHighPass(44100, 29.198f, 0.027f)),
    preLowPassFilter(juce::dsp::IIR::Coefficients<float>::makeLowPass(44100, 6843.9f, 0.1f)),
    band1(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 10.081f, 0.437f, juce::Decibels::decibelsToGain(-27.55f))),
    band2(juce::dsp::IIR::Coefficients<float>::makeLowShelf(44100, 16.681f, 1.00f, juce::Decibels::decibelsToGain(-3.01f))),
    band3(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 26.861f, 7.071f, juce::Decibels::decibelsToGain(0.7f))),
    band4(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 47.406f, 1.363f, juce::Decibels::decibelsToGain(3.47f))),
    band5(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 81.356f, 10.0f, juce::Decibels::decibelsToGain(0.34f))),
    band6(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 95.185f, 14.14f, juce::Decibels::decibelsToGain(-0.33f))),
    band7(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 107.82f, 10.0f, juce::Decibels::decibelsToGain(-1.57f))),
    band8(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 149.65f, 10.0f, juce::Decibels::decibelsToGain(-0.45f))),
    band9(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 176.71f, 20.0f, juce::Decibels::decibelsToGain(0.64f))),
    band10(juce::dsp::IIR::Coefficients<float>::makeHighShelf(44100, 180.73f, 1.0f, juce::Decibels::decibelsToGain(-6.17f))),
    band11(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 328.08f, 20.0f, juce::Decibels::decibelsToGain(0.46))),
    band12(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 411.37f, 5.946, juce::Decibels::decibelsToGain(-0.38))),
    band13(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 478.18, 0.755, juce::Decibels::decibelsToGain(3.89))),
    band14(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 506.38, 14.14, juce::Decibels::decibelsToGain(0.84))),
    band15(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 790.78, 14.14, juce::Decibels::decibelsToGain(-0.38))),
    band16(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 799.93, 1.146, juce::Decibels::decibelsToGain(-2.35))),
    band17(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 1130.4, 12.97, juce::Decibels::decibelsToGain(0.53))),
    band18(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 1625.1, 14.14, juce::Decibels::decibelsToGain(-0.44))),
    band19(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 2736.6, 5, juce::Decibels::decibelsToGain(0.39))),
    band20(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 3808.6, 5.946, juce::Decibels::decibelsToGain(-0.35))),
    band21(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 6873.0, 0.884, juce::Decibels::decibelsToGain(2.8))),
    band22(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 15326, 14.14, juce::Decibels::decibelsToGain(0.39))),
    band23(juce::dsp::IIR::Coefficients<float>::makeHighShelf(44100, 18862, 0.3, juce::Decibels::decibelsToGain(-6.49))),
    lowEq(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 163.62, 0.509, juce::Decibels::decibelsToGain(-0.49))),
    lowMidEq(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 455.24, 1.564, juce::Decibels::decibelsToGain(3.78))),
    highMidEq(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 831.29, 1.00, juce::Decibels::decibelsToGain(-3.44))),
    trebleEq(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 2815.6, 0.724, juce::Decibels::decibelsToGain(-5.39))),
    presenceEq(juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 5011.7, 1.115, juce::Decibels::decibelsToGain(-2.27)))
#endif
{
}

DeepDspPrecessionAudioProcessor::~DeepDspPrecessionAudioProcessor()
{
}

//==============================================================================
const juce::String DeepDspPrecessionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DeepDspPrecessionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DeepDspPrecessionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DeepDspPrecessionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DeepDspPrecessionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DeepDspPrecessionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DeepDspPrecessionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DeepDspPrecessionAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DeepDspPrecessionAudioProcessor::getProgramName (int index)
{
    return {};
}

void DeepDspPrecessionAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DeepDspPrecessionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();
    
    preHighPassFilter.prepare(spec);
    preHighPassFilter.reset();
    
    preLowPassFilter.prepare(spec);
    preLowPassFilter.reset();
    
    band1.prepare(spec);
    band1.reset();
    band2.prepare(spec);
    band2.reset();
    band3.prepare(spec);
    band3.reset();
    band4.prepare(spec);
    band4.reset();
    band5.prepare(spec);
    band5.reset();
    band6.prepare(spec);
    band6.reset();
    band7.prepare(spec);
    band7.reset();
    band8.prepare(spec);
    band8.reset();
    band9.prepare(spec);
    band9.reset();
    band10.prepare(spec);
    band10.reset();
    band11.prepare(spec);
    band11.reset();
    band12.prepare(spec);
    band12.reset();
    band13.prepare(spec);
    band13.reset();
    band14.prepare(spec);
    band14.reset();
    band15.prepare(spec);
    band15.reset();
    band16.prepare(spec);
    band16.reset();
    band17.prepare(spec);
    band17.reset();
    band18.prepare(spec);
    band18.reset();
    band19.prepare(spec);
    band19.reset();
    band20.prepare(spec);
    band20.reset();
    band21.prepare(spec);
    band21.reset();
    band22.prepare(spec);
    band22.reset();
    band23.prepare(spec);
    band23.reset();
    
    lowEq.prepare(spec);
    lowEq.reset();
    lowMidEq.prepare(spec);
    lowMidEq.reset();
    highMidEq.prepare(spec);
    highMidEq.reset();
    trebleEq.prepare(spec);
    trebleEq.reset();
    presenceEq.prepare(spec);
    presenceEq.reset();
}

void DeepDspPrecessionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DeepDspPrecessionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DeepDspPrecessionAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    juce::dsp::AudioBlock<float> bufferBlock(buffer);
    
    preHighPassFilter.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    preLowPassFilter.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    
    float clipingPoint = 0.2;

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0 ; sample < buffer.getNumSamples() ; ++sample) {
            channelData[sample] *= gainSlider * inputSlider;
            
            if (channelData[sample] > clipingPoint) {
                channelData[sample] = clipingPoint;
            }
            
            if (channelData[sample] < -clipingPoint) {
                channelData[sample] = -clipingPoint;
            }
        }
    }
    
    band1.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band2.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band3.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band4.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band5.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band6.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band7.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band8.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band9.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band10.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band11.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band12.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band13.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band14.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band15.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band16.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band17.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band18.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band19.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band20.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band21.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band22.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    band23.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    
    *lowEq.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 163.62, 0.509, juce::Decibels::decibelsToGain(-0.49 + lowSlider));
    *lowMidEq.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 455.24, 1.564, juce::Decibels::decibelsToGain(3.78 + lowMidSlider));
    *highMidEq.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 831.29, 1.00, juce::Decibels::decibelsToGain(-3.44 + highMidSlider));
    *trebleEq.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 2815.6, 0.724, juce::Decibels::decibelsToGain(-5.39 + trebleSlider));
    *presenceEq.state = *juce::dsp::IIR::Coefficients<float>::makePeakFilter(44100, 5011.7, 1.115, juce::Decibels::decibelsToGain(-2.27 + presenceSlider));
    
    lowEq.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    lowMidEq.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    highMidEq.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    trebleEq.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    presenceEq.process(juce::dsp::ProcessContextReplacing<float>(bufferBlock));
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        for (int sample = 0 ; sample < buffer.getNumSamples() ; ++sample) {
            channelData[sample] *= outputSlider;
        }
    }
}

//==============================================================================
bool DeepDspPrecessionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DeepDspPrecessionAudioProcessor::createEditor()
{
    return new DeepDspPrecessionAudioProcessorEditor (*this);
}

//==============================================================================
void DeepDspPrecessionAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DeepDspPrecessionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DeepDspPrecessionAudioProcessor();
}
