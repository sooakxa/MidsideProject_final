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
    midGainModuleSlider.setRange(0.0f, 2.0f, 1.0f);
    midGainModuleSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 80, 20);
   addAndMakeVisible(&midGainModuleSlider);
    
    // Side Gain  slider
    sideGainModuleValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, "sideGainModule", sideGainModuleSlider);
    sideGainModuleSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    sideGainModuleSlider.setRange(0.0f, 2.0f, 1.0f);
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
    g.drawFittedText("F", 55, 85, 10, 10, juce::Justification::centred, 1, 0.0f);
    g.drawFittedText("R", 165, 85, 10, 10, juce::Justification::centred, 1, 0.0f);
    g.drawFittedText("D", 55, 175, 12, 12, juce::Justification::centred, 1, 0.0f);
}

void MidsideProjectAudioProcessorEditor::resized()
{
   
    // Slider Placement within UI
    stereoWidthSlider.setBounds(10, 35, 380, 50);
    midGainModuleSlider.setBounds(10, 85, 380, 50);
    sideGainModuleSlider.setBounds(10, 155, 380, 50);
    cutoffSlider.setBounds(10, 205, 380, 50);
    
    // ComboBox Placement within UI
    modeSelInput.setBounds(127.5, 320, 75, 25);
    modeSelOutput.setBounds(10, 320, 75, 25);
}
