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
                           
                                    std::make_unique<juce::AudioParameterFloat>("midGainModule", "Mid Gain", 0.0f, 10.0f, 6.0f),
                                    std::make_unique<juce::AudioParameterFloat>("sideGainModule", "Side Gain", 0.0f, 10.0f, 6.0f),

                           
                                    std::make_unique<juce::AudioParameterFloat>("cutoff", "Cutoff", 20.0f, 20000.0f, 200.0f),
                                    std::make_unique<juce::AudioParameterChoice>("modeInput", "Input Type", juce::StringArray("Stereo", "Mid-side"), 0),
                                    std::make_unique<juce::AudioParameterChoice>("modeOutput", "Output Type", juce::StringArray("Stereo", "Mid-side"), 0)

                           
                       })
#endif

    {
    // adds a listener to each parameter in the array.
        treeState.addParameterListener("cutoff", this);
        treeState.addParameterListener("stereoWidth", this);
        
        treeState.addParameterListener("modeInput", this);
        treeState.addParameterListener("modeOutput", this);
        
        treeState.addParameterListener("midGainModule", this);
        treeState.addParameterListener("sideGainModule", this);

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
    
    lwrFilter.reset();
    lwrFilter.prepare(spec);
    
    midGainModule.prepare(spec);
    sideGainModule.prepare(spec);

    //audioBlock.copyFrom
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
        
    if (totalNumInputChannels == 2)
    
        juce::dsp::AudioBlock<float> audioBlock {buffer};
    

   // Midside Processing
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);
        
        // Getting the left and right channels into variables
        auto* leftData = buffer.getWritePointer(0);
        auto* rightData = buffer.getWritePointer(1);

        
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            const auto mid = 0.5 * (leftData[sample] + rightData[sample]);
            const auto sides = 0.5 * (leftData[sample] - rightData[sample]);
              
            const auto newMid = (2.0 - width) * (mid);
            const auto newSides = width * sides;

            
            //Stereo Width
            const auto newLeft = newMid + newSides;
            const auto newRight = newMid - newSides;
            
            leftData[sample] = newLeft;
            rightData[sample] = newRight;
            
            midGainModule.setGainDecibels(midGain);
            midGainModule.processSample(mid);
            
            sideGainModule.setGainDecibels(sideGain);
            sideGainModule.processSample(sides);
        }
        }
        {
            //Midside
            
            //float mid = (buffer.getSample(0, i) + buffer.getSample(1, i)) / 2.0f;
            //float side = (buffer.getSample(0, i) - buffer.getSample(1, i)) / 2.0f;
            //float in = channelData[i];
            float low = 0.0f;
            float high = 0.0f;
             

            //Cut off Processing
           // lwrFilter.processSample(channel, in , low, high);
            
            if (modeOutputChoice == 1) {
                if (low < 0)
                    low = 0.0f;
                
            }
            else if (modeOutputChoice == 2) {
                if(low < 0)
                    low = fabs(low);
            }
            
            if (modeInputChoice == 1) {
                if (high < 0)
                    high = 0.0f;
            }
            else if (modeInputChoice == 2)
                if (high < 0)
                    high = fabs(high);
                
            //channelData[i] = low + high;
        }
}
        
       // juce::dsp::AudioBlock<float> block(buffer);
        //auto processingContext = juce::dsp::ProcessContextReplacing<float>(block);
        //AudioProcessor.process(processingContext);
    
        //auto* channelDataL = buffer.getWritePointer(0);
        //auto* channelDataR = buffer.getWritePointer(1);


    


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
    auto state = treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void MidsideProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

      if (xmlState.get() != nullptr)
          if (xmlState->hasTagName(treeState.state.getType()))
              treeState.replaceState(juce::ValueTree::fromXml(*xmlState));
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
        //stereoWidth == newValue;
    }
    
    else if (parameterID == "midGainModule") {
        sideGainModule.setGainDecibels(newValue);
    }
    
    else if (parameterID == "sideGainModule") {
        midGainModule.setGainDecibels(newValue);
    }
    
    else if (parameterID == "cutoff") {
        lwrFilter.setCutoffFrequency(newValue);
    }
    
    else if (parameterID == "modeOutput") {
        modeOutputChoice = newValue;
    }
    
    else if (parameterID == "modeInput") {
        modeInputChoice = newValue;
    }
}

 



