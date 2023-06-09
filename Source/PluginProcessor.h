/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class MidsideProjectAudioProcessor  : public juce::AudioProcessor,
                                        public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    MidsideProjectAudioProcessor();
    ~MidsideProjectAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    void parameterChanged(const juce::String& parameterID, float newValue) override;
    
    float gainParameter{ 1.0 }; //total gain control
    float gainMidParameter{ 1.0 }; //MID signal gain control
    float gainSideParameter{ 1.0 }; //SIDE signal gain control
private:
    
    juce::AudioProcessorValueTreeState treeState;
    //juce::dsp::AudioProcessor<float> MidsideProject;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidsideProjectAudioProcessor)
};
