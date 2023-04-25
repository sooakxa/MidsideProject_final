/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MidsideProjectAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MidsideProjectAudioProcessorEditor (MidsideProjectAudioProcessor&,
    juce::AudioProcessorValueTreeState&);
    ~MidsideProjectAudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidsideProjectAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& treeState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidsideProjectAudioProcessorEditor)
};
