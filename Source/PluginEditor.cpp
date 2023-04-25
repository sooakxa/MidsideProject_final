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
    
     // Cutoff Frequency
     cutoffValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, "cutoff", cutoffDial);
     cutoffDial.setSliderStyle(juce::Slider::RotaryVerticalDrag);
     cutoffDial.setRange(20.0f, 20000.0f, 0.0f);
     cutoffDial.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
     addAndMakeVisible(&cutoffDial);
    
    
    // Resonance
    resonanceValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState,"resonance",
    resonanceDial);
    resonanceDial.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    resonanceDial.setRange(0.0f, 1.10f, 0.0f);
    resonanceDial.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&resonanceDial);
    
    
    // Drive
    driveValue = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(treeState, "drive",
    driveDial);
    driveDial.setSliderStyle(juce::Slider::RotaryVerticalDrag);
    driveDial.setRange(1.0f, 25.0f, 1.0f);
    driveDial.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, true, 0, 0);
    addAndMakeVisible(&driveDial);
    
    
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
    cutoffDial.setBounds(10, 40, 100, 100);
    resonanceDial.setBounds(120, 40, 100, 100);
    driveDial.setBounds(10, 130, 100, 100);
    modeSelInput.setBounds(127.5, 169.5, 75, 25);
    modeSelOutput.setBounds(10, 169.5, 75, 25);
}
