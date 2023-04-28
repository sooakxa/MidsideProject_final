/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidsideProjectAudioProcessorEditor::MidsideProjectAudioProcessorEditor (MidsideProjectAudioProcessor& p, juce::AudioProcessorValueTreeState& vts)
    : AudioProcessorEditor (&p), audioProcessor (p), treeState(vts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (500, 500);
    
     // Stereo width slider
    stereoWidthValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, "stereoWidth", stereoWidthSlider);
    stereoWidthSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    stereoWidthSlider.setRange(0.0f, 2.0f, 1.0f);
    stereoWidthSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 80, 20);
    addAndMakeVisible(&stereoWidthSlider);
    
    // Cutoff frequency slider
   cutoffValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, "cutoff", cutoffSlider);
   cutoffSlider.setSliderStyle(juce::Slider::LinearHorizontal);
   cutoffSlider.setRange(20.0f, 20000.0f, 1.0f);
   cutoffSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 80, 20);
   addAndMakeVisible(&cutoffSlider);
    
    // Mid Gain  slider
    midGainModuleValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, "midGainModule", midGainModuleSlider);
    midGainModuleSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    midGainModuleSlider.setRange(0.0f, 100.0f, 6.0f);
    midGainModuleSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 80, 20);
   addAndMakeVisible(&midGainModuleSlider);
    
    // Side Gain  slider
    sideGainModuleValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, "sideGainModule", sideGainModuleSlider);
    sideGainModuleSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    sideGainModuleSlider.setRange(0.0f, 100.0f, 6.0f);
    sideGainModuleSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 80, 20);
   addAndMakeVisible(&sideGainModuleSlider);
    
    
    // Mode Selection Input
    modeSelInput.addItem("Stereo", 1);
    modeSelInput.addItem("Mid-side", 2);
    modeChoiceInput = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(treeState, "modeInput", modeSelInput);
    addAndMakeVisible(&modeSelInput);
    
    // Mode Selection Output
    modeSelOutput.addItem("Stereo", 1);
    modeSelOutput.addItem("Mid-side", 2);
    modeChoiceOutput = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(treeState, "modeOutput", modeSelOutput);
    addAndMakeVisible(&modeSelOutput);

}

MidsideProjectAudioProcessorEditor::~MidsideProjectAudioProcessorEditor()
{
}

//==============================================================================
void MidsideProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Background Fill Colour
    g.fillAll(juce::Colours::aqua);
    g.setColour(juce::Colours::black);
    
    // Title Text
    g.setFont(30);
    g.drawFittedText("Midside Plugin", 10, 20, 210, 10, juce::Justification::centred, 1, 0.0f);
    
    
    // Slider and ComboBox Lbels
    g.setFont(25);
    g.drawFittedText("Stereo Width", 55, 55, 50, 50, juce::Justification::centred, 12, 0.0f);
    g.drawFittedText("Mid Gain", 55, 120, 50, 50, juce::Justification::centred, 8, 0.0f);
    g.drawFittedText("Side Gain", 55, 200, 50, 50, juce::Justification::centred, 9, 0.0f);
    g.drawFittedText("Cutoff Frequency", 55, 255, 50, 50, juce::Justification::centred, 16, 0.0f);
}

void MidsideProjectAudioProcessorEditor::resized()
{
   
    // Slider Placement within UI
    stereoWidthSlider.setBounds(10, 70, 380, 50);
    midGainModuleSlider.setBounds(10, 135, 380, 50);
    sideGainModuleSlider.setBounds(10, 215, 380, 50);
    cutoffSlider.setBounds(10, 265, 380, 50);
    
    // Combobox Placement within UI
    modeSelInput.setBounds(127.5, 350, 75, 25);
    modeSelOutput.setBounds(10, 350, 75, 25);
}
