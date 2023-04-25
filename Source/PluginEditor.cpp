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
    setSize (230, 230);
    
     // Stereo Width
    stereoWidthValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, "stereoWidth", stereoWidthSlider);
    stereoWidthSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    stereoWidthSlider.setRange(0.0f, 2.0f, 1.0f);
    stereoWidthSlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxAbove, true, 80, 20);
    addAndMakeVisible(&stereoWidthSlider);
    
    

    
    
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
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(juce::Colours::aqua);
    g.setColour(juce::Colours::black);
    // Title Text
    g.setFont(30);
    g.drawFittedText("Ladder Filter", 10, 20, 210, 10, juce::Justification::centred, 1, 0.0f);
    // Frequnecy, Resonance & Drive labels
    g.setFont(25);
    g.drawFittedText("F", 55, 85, 10, 10, juce::Justification::centred, 1, 0.0f);
    g.drawFittedText("R", 165, 85, 10, 10, juce::Justification::centred, 1, 0.0f);
    g.drawFittedText("D", 55, 175, 12, 12, juce::Justification::centred, 1, 0.0f);
}

void MidsideProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    stereoWidthSlider.setBounds(10, 30, 380, 50);
    modeSelInput.setBounds(127.5, 169.5, 75, 25);
    modeSelOutput.setBounds(10, 169.5, 75, 25);
}
