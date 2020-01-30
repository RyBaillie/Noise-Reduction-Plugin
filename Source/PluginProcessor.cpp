/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceNrProjectAudioProcessor::JuceNrProjectAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), treeState (*this, nullptr, "PARAMETER", createParameterLayout())
#endif
{
	
}

JuceNrProjectAudioProcessor::~JuceNrProjectAudioProcessor()
{
}

//==============================================================================

AudioProcessorValueTreeState::ParameterLayout JuceNrProjectAudioProcessor::createParameterLayout()
{
    std::vector <std::unique_ptr<RangedAudioParameter>> params;
    auto gainParam = std::make_unique<AudioParameterFloat>( "gain", //ID
															"Gain", //Name
															-48.0f, //Min
															0.0f,	//Max
															-15.0f	//Default
		); 
	auto filterParam = std::make_unique<AudioParameterFloat>(	"cutoff",	//ID
																"Cutoff",	//Name
																20.0f,		//Min
																20000.0f,	//Max
																5000.0f		//Default
		);
	params.push_back(std::move(filterParam));
    params.push_back(std::move(gainParam));
    return { params.begin(), params.end() };
}

const String JuceNrProjectAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool JuceNrProjectAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool JuceNrProjectAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool JuceNrProjectAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double JuceNrProjectAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int JuceNrProjectAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int JuceNrProjectAudioProcessor::getCurrentProgram()
{
    return 0;
}

void JuceNrProjectAudioProcessor::setCurrentProgram (int index)
{
}

const String JuceNrProjectAudioProcessor::getProgramName (int index)
{
    return {};
}

void JuceNrProjectAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void JuceNrProjectAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void JuceNrProjectAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool JuceNrProjectAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void JuceNrProjectAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
        
        auto sliderGainValue = treeState.getRawParameterValue("gain");

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData [sample] = buffer.getSample(channel, sample) * Decibels::decibelsToGain(*sliderGainValue);
        }
    }
}

//==============================================================================
bool JuceNrProjectAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* JuceNrProjectAudioProcessor::createEditor()
{
    return new JuceNrProjectAudioProcessorEditor (*this);
}

//==============================================================================
void JuceNrProjectAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void JuceNrProjectAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new JuceNrProjectAudioProcessor();
}
