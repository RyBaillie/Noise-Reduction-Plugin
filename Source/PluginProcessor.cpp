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
	auto filterCutoffParam = std::make_unique<AudioParameterFloat>(	"cutoff",	//ID
																	"Cutoff",		//Name
																	20.0f,			//Min
																	20000.0f,		//Max
																	500.0f			//Default
		);
	auto filterResonanceParam = std::make_unique<AudioParameterFloat>(	"resonance",	//ID
																		"Resonance",	//Name
																		1.0f,			//Min
																		5.0f,			//Max
																		1.0f			//Default
		);
	auto decibelLimitParam = std::make_unique<AudioParameterFloat>(	"dbLimit",	//ID
																	"DbLimit",		//Name
																	-200.0f,		//Min
																	200.0f,			//Max
																	5.0f			//Default
		);

	auto compressorRatioParam = std::make_unique<AudioParameterFloat>(	"compressorRatio",	//ID
																		"CompressorRatio",	//Name
																		0.0f,				//Min
																		100.0f,				//Max
																		5.0f				//Default
		);
	auto attackMsParam = std::make_unique<AudioParameterFloat>(	"attackMs",		//ID
																"AttackMs",		//Name
																0.0f,			//Min
																1000.0f,		//Max
																300.0f			//Default
		);
	auto releaseMsParam = std::make_unique<AudioParameterFloat>(	"releaseMs",	//ID
																	"ReleaseMs",	//Name
																	0.0f,			//Min
																	1000.0f,		//Max
																	200.0f			//Default
		);
	auto encodeBtnParam = std::make_unique<AudioParameterBool>(		"encodeBtn",	//ID
																	"EncodeBtn",	//Name
																	true			//Default
		);
	auto noiseReductionOnParam = std::make_unique<AudioParameterBool>(	"noiseReductionOnBtn",	//ID
																		"NoiseReductionOnBtn",	//Name
																		true			//Default
		);

	params.push_back(std::move(noiseReductionOnParam));
	params.push_back(std::move(encodeBtnParam));
	params.push_back(std::move(filterCutoffParam));
	params.push_back(std::move(filterResonanceParam));
	params.push_back(std::move(decibelLimitParam));
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

	sideChannel.setSize(4, samplesPerBlock);

	lastSampleRate = sampleRate;
	dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;
	spec.numChannels = getMainBusNumOutputChannels();
	stateVariableFilter.reset();
	updateFilter();

	stateVariableFilter.prepare(spec);
	updateAttackRelease();
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
	
	auto sliderDecibelValue = treeState.getRawParameterValue("dbLimit");
	auto sliderCompressorRatioValue = treeState.getRawParameterValue("compressorRatio");
	auto sliderAttackMsValue = treeState.getRawParameterValue("attackMs");
	auto sliderReleaseMsValue = treeState.getRawParameterValue("releaseMs");

	setAttack(*sliderAttackMsValue);
	setRelease(*sliderReleaseMsValue);
	setRatio(*sliderCompressorRatioValue);

	//In this implementation, the side channel is buffer and the passthrough channel is buffer's copy.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i){
		buffer.clear(i, 0, buffer.getNumSamples());
	}
	sideChannel.makeCopyOf(buffer, true);

	dsp::AudioBlock<float> block(buffer);

	updateFilter();

	if (*treeState.getRawParameterValue("noiseReductionOnBtn")) {
		stateVariableFilter.process(dsp::ProcessContextReplacing<float>(block));
	}

    for (int channel = 0; channel < totalNumInputChannels; ++channel){
        auto* channelData = buffer.getWritePointer (channel);

        for (int sampleCount = 0; sampleCount < buffer.getNumSamples(); ++sampleCount) {

			float workingSample = buffer.getSample(channel, sampleCount);

			if (*treeState.getRawParameterValue("noiseReductionOnBtn")) {

				if (buffer.getSample(channel, sampleCount) > m_Envelope) {
					m_Envelope = m_Envelope + m_Attack * 
						(buffer.getSample(channel, sampleCount) - m_Envelope);
				}
				else if (buffer.getSample(channel, sampleCount) < m_Envelope) {
					m_Envelope = m_Envelope + m_Release * 
						(buffer.getSample(channel, sampleCount) - m_Envelope);
				}

				float db = Decibels::gainToDecibels(fabs(m_Envelope));
				setDecibelLimit(*sliderDecibelValue);

				//Check signal is quiet enough
				if (db <= dbLimit) {

					workingSample = compressAudio(workingSample);

				}

				bool btnEncodeMode = *treeState.getRawParameterValue("encodeBtn");

				// Boosts the modified signal by the unmodified one
				if (btnEncodeMode) {
					workingSample = (workingSample + sideChannel.getSample(channel, sampleCount)) / 2;
				}
				// Cancels the modified signal by the unmodified one
				else {
					workingSample = (workingSample - sideChannel.getSample(channel, sampleCount)) / 2;
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

// Filter ======================================================================
void JuceNrProjectAudioProcessor::updateFilter() {

	auto filterSliderValue = *treeState.getRawParameterValue("cutoff");
	auto filterResonanceValue = *treeState.getRawParameterValue("resonance");

	//make filter High Pass
	stateVariableFilter.state->type = 
		dsp::StateVariableFilter::Parameters<float>::Type::highPass;
	stateVariableFilter.state->setCutOffFrequency
	(lastSampleRate, filterSliderValue, filterResonanceValue);

}
//==============================================================================

// Compressor ==================================================================


float JuceNrProjectAudioProcessor::getRatio() {
	return m_Ratio;
}

void JuceNrProjectAudioProcessor::setRatio(float ratio) {
	m_Ratio = ratio;
}

float JuceNrProjectAudioProcessor::compressAudio(float sample) {

	float scale = 1.0f - (1.0f / m_Ratio);
	float compressionGain = scale * (dbLimit - m_Envelope);
	compressionGain = decibelToAmplitude(compressionGain);
	return sample * compressionGain;

}
//==============================================================================

void JuceNrProjectAudioProcessor::setDecibelLimit(float db) {
	dbLimit = db;
}

float JuceNrProjectAudioProcessor::amplitudeToDecibel(float amplitude) {
	amplitude = std::max(amplitude, BOUND_LINEAR);
	return 20.0f * log10(amplitude);
}

float JuceNrProjectAudioProcessor::decibelToAmplitude(float decibel) {
	return pow(10.0f, decibel / 20.0f);
}
