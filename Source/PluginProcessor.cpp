/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <cmath>

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
															0.0f	//Default -15.0f
		); 
	auto filterParam = std::make_unique<AudioParameterFloat>(	"cutoff",	//ID
																"Cutoff",	//Name
																20.0f,		//Min
																20000.0f,	//Max
																5000.0f		//Default
		);
	auto decibelLimitParam = std::make_unique<AudioParameterFloat>(	"dbLimit",	//ID
																"DbLimit",		//Name
																-200.0f,		//Min
																200.0f,			//Max
																1.0f			//Default
		);
	auto compressorThresholdParam = std::make_unique<AudioParameterFloat>(	"compressorThreshold",	//ID
																			"CompressorThreshold",	//Name
																			-100.0f,				//Min
																			100.0f,					//Max
																			-24.0f					//Default
		);
	auto compressorRatioParam = std::make_unique<AudioParameterFloat>(	"compressorRatio",	//ID
																		"CompressorRatio",	//Name
																		0.0f,				//Min
																		100.0f,				//Max
																		10.0f				//Default
		);
	auto attackMsParam = std::make_unique<AudioParameterFloat>(	"attackMs",	//ID
																"AttackMs",	//Name
																0.0f,			//Min
																1000.0f,		//Max
																100.0f			//Default
		);
	auto releaseMsParam = std::make_unique<AudioParameterFloat>(	"releaseMs",	//ID
																	"ReleaseMs",	//Name
																	0.0f,			//Min
																	1000.0f,		//Max
																	100.0f			//Default
		);
	params.push_back(std::move(filterParam));
    params.push_back(std::move(gainParam));
	params.push_back(std::move(decibelLimitParam));
	params.push_back(std::move(compressorThresholdParam));
	params.push_back(std::move(compressorRatioParam));
	params.push_back(std::move(attackMsParam));
	params.push_back(std::move(releaseMsParam));
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
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;
	spec.numChannels = getMainBusNumOutputChannels();

	updateFilter();
	updateAttackRelease();
}

void JuceNrProjectAudioProcessor::updateFilter() {

	//make filter High Pass
	stateVariableFilter.reset();
	stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
	stateVariableFilter.state->setCutOffFrequency(currentSampleRate, 500);
	stateVariableFilter.prepare(spec);

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

	auto sliderGainValue = treeState.getRawParameterValue("gain");
	auto filterValue = treeState.getRawParameterValue("cutoff");
	auto sliderDecibelValue = treeState.getRawParameterValue("dbLimit");
	auto sliderCompressorThresholdValue = treeState.getRawParameterValue("compressorThreshold");
	auto sliderCompressorRatioValue = treeState.getRawParameterValue("compressorRatio");
	auto sliderAttackMsValue = treeState.getRawParameterValue("attackMs");
	auto sliderReleaseMsValue = treeState.getRawParameterValue("releaseMs");

	setAttack(*sliderAttackMsValue);
	setRelease(*sliderReleaseMsValue);
	setRatio(*sliderCompressorRatioValue);
	setThreshold(*sliderCompressorThresholdValue);

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

	dsp::AudioBlock<float> block(buffer);

	updateFilter();
	stateVariableFilter.process(dsp::ProcessContextReplacing<float>(block));

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...

        for (int sampleCount = 0; sampleCount < buffer.getNumSamples(); ++sampleCount)
        {

			float detectionSignal = fabs(buffer.getSample(channel, sampleCount));
			detectionSignal = amplitudeToDecibel(detectionSignal);
			float workingSample = buffer.getSample(channel, sampleCount);

			if (buffer.getSample(channel, sampleCount) > m_Envelope) {
				m_Envelope = m_Envelope + m_Attack * (buffer.getSample(channel, sampleCount) - m_Envelope);
			}
			else if (buffer.getSample(channel, sampleCount) < m_Envelope) {
				m_Envelope = m_Envelope + m_Release * (buffer.getSample(channel, sampleCount) - m_Envelope);
			}

			float db = Decibels::gainToDecibels(fabs(m_Envelope));
			setDecibelLimit(*sliderDecibelValue);

			if(db <= dbLimit) {
				workingSample = workingSample * Decibels::decibelsToGain(*sliderGainValue);

				if (detectionSignal > m_Threshold) {
					float scale = 1.0f - (1.0f / m_Ratio);
					float gain = scale * (m_Threshold - detectionSignal);
					gain = decibelToAmplitude(gain);

					workingSample = workingSample * gain;
				}

			}
			
			channelData[sampleCount] = workingSample;
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

// Envelope ====================================================================
void JuceNrProjectAudioProcessor::setAttack(float attack) {
	m_AttackInMilliseconds = attack;
	updateAttackRelease();
}

void JuceNrProjectAudioProcessor::setRelease(float release) {
	m_ReleaseInMilliseconds = release;
	updateAttackRelease();
}

float JuceNrProjectAudioProcessor::envelopeCalculate(float time) {
	if (time <= 0.0f || spec.sampleRate <= 0.0f) {
		return 1.0f;
	}
	else return 1.0f - exp(-1.0f / (time * 0.001f * spec.sampleRate));
}

void JuceNrProjectAudioProcessor::updateAttackRelease() {
	m_Attack = envelopeCalculate(m_AttackInMilliseconds);
	m_Release = envelopeCalculate(m_ReleaseInMilliseconds);
}
//==============================================================================

// Compressor ==================================================================
float JuceNrProjectAudioProcessor::getThreshold() {
	return m_Threshold;
}

float JuceNrProjectAudioProcessor::getRatio() {
	return m_Ratio;
}

void JuceNrProjectAudioProcessor::setThreshold(float threshold) {
	m_Threshold = threshold;
}

void JuceNrProjectAudioProcessor::setRatio(float ratio) {
	m_Ratio = ratio;
}

float JuceNrProjectAudioProcessor::amplitudeToDecibel(float amplitude) {
	amplitude = std::max(amplitude, BOUND_LINEAR);
	return 20.0f * log10(amplitude);
}

float JuceNrProjectAudioProcessor::decibelToAmplitude(float decibel) {
	return pow(10.0f, decibel / 20.0f);
}
//==============================================================================

void JuceNrProjectAudioProcessor::setDecibelLimit(float db) {
	dbLimit = db;
}
