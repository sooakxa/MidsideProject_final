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
    MidsideProjectAudioProcessorEditor (MidsideProjectAudioProcessor&, juce::AudioProcessorValueTreeState&);
    ~MidsideProjectAudioProcessorEditor();

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    juce::Slider midsideBalanceSlider;
    juce::Slider cutoffSlider;
    juce::Slider stereoWidthSlider;
    juce::ComboBox modeSelInput;
    juce::ComboBox modeSelOutput;
    
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> midsideBalanceValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> cutoffValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::SliderAttachment> stereoWidthValue;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> modeChoiceInput;
    std::unique_ptr <juce::AudioProcessorValueTreeState::ComboBoxAttachment> modeChoiceOutput;

    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MidsideProjectAudioProcessor& audioProcessor;
    juce::AudioProcessorValueTreeState& treeState;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidsideProjectAudioProcessorEditor)
};
