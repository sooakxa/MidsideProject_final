/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidsideProjectAudioProcessor::MidsideProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), treeState(*this, nullptr, juce::Identifier("PARAMETERS"),
                                     { std::make_unique<juce::AudioParameterFloat>("stereoWidth", "Stereo Width", 0.0f, 2.0f, 1.0f),
                                    std::make_unique<juce::AudioParameterFloat>("cutoff", "Cutoff", 20.0f, 20000.0f, 200.0f),
                                    std::make_unique<juce::AudioParameterChoice>("modeInput", "Input Type", juce::StringArray("Stereo", "Mid-side"), 0),
                                    std::make_unique<juce::AudioParameterChoice>("modeOutput", "Output Type", juce::StringArray("Stereo", "Mid-side"), 0) })
#endif

    {
    // adds a listener to each parameter in the array.
        treeState.addParameterListener("cutoff", this);
        treeState.addParameterListener("stereoWidth", this);
        treeState.addParameterListener("modeInput", this);
        treeState.addParameterListener("modeOutput", this);

    }
    


MidsideProjectAudioProcessor::~MidsideProjectAudioProcessor()
{
}

//==============================================================================
const juce::String MidsideProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidsideProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidsideProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidsideProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidsideProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidsideProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidsideProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidsideProjectAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MidsideProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidsideProjectAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MidsideProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = sampleRate;
    spec.maximumBlockSize = samplesPerBlock;
    spec.numChannels = getTotalNumOutputChannels();

}

void MidsideProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidsideProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
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

void MidsideProjectAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

   
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
        
        juce::dsp::AudioBlock<float> block(buffer);
       // auto processingContext = juce::dsp::ProcessContextReplacing<float>(block);
        //AudioProcessor.process(processingContext);
    {
        auto* channelDataL = buffer.getWritePointer(0);
        auto* channelDataR = buffer.getWritePointer(1);

        //channelDataL[sample] = gainParameter * (midData + sideData) / 2;
        //channelDataR[sample] = gainParameter * (midData - sideData) / 2;
    }
}

//==============================================================================
bool MidsideProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MidsideProjectAudioProcessor::createEditor()
{
    return new MidsideProjectAudioProcessorEditor (*this, treeState);
}

//==============================================================================
void MidsideProjectAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidsideProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

    

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidsideProjectAudioProcessor();
}

// Function called when parameter is changed
void MidsideProjectAudioProcessor::parameterChanged(const juce::String &parameterID, float newValue)
{
    if (parameterID == "stereoWidth") {
        // do something here
    }
    else if (parameterID == "cutoff") {
        // do something here
    }
    else if (parameterID == "modeOutput") {
        // do something here
    }
    else if (parameterID == "modeInput") {
        // do something here
    }
}

        


        
