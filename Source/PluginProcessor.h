/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class JuceNrProjectAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    JuceNrProjectAudioProcessor();
    ~JuceNrProjectAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	void updateFilter();

	// Envelope //====================================================================
	void setAttack(float attack);
	void setRelease(float release);
	//===============================================================================

	// Compressor //===================================================================
	float getThreshold();
	float getRatio();
	void setThreshold(float threshold);
	void setRatio(float ratio);
	//================================================================================

	dsp::ProcessSpec spec;
	double currentSampleRate;
    
    float rawGainValue;
    AudioProcessorValueTreeState treeState;
    AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

private:

	dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float>, dsp::StateVariableFilter::Parameters<float>> stateVariableFilter;
	AudioBuffer<float> sideChannel;

	float dbLimit = 1;
	float lastSampleRate;

	void setDecibelLimit(float db);

	// Envelope //====================================================================
	float m_Envelope = 0.0f;
	float m_Attack = 0.0f;
	float m_AttackInMilliseconds = 10.0f;
	float m_Release = 0.0f;
	float m_ReleaseInMilliseconds = 100.0f;

	void updateAttackRelease();
	float envelopeCalculate(float time);
	//===============================================================================

	// Compressor //==================================================================
	const float BOUND_LOGARITHM = -96.0f;
	const float BOUND_LINEAR = decibelToAmplitude(BOUND_LOGARITHM);

	float m_Threshold = 0.0f;
	float m_Ratio = 1.0f;

	float amplitudeToDecibel(float amplitude);
	float decibelToAmplitude(float decibel);
	//================================================================================

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceNrProjectAudioProcessor)
};
