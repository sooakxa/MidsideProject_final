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
    juce::dsp::LinkwitzRileyFilter<float> lwrFilter;
    juce::dsp::Gain<float> midGainModule;
    juce::dsp::Gain<float> sideGainModule;

    

    
    float midGainModuleChoice = 0;
    float modeOutputChoice = 0;
    float modeInputChoice = 0;
    float mid = 0;
    float side = 0;
    float stereoWidth = 0;
    float midGain {0.0};
    float sideGain {0.0};
    
    float width {1.0f};

    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidsideProjectAudioProcessor)
};
