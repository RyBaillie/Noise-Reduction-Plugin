/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class JuceNrProjectAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    JuceNrProjectAudioProcessorEditor (JuceNrProjectAudioProcessor&);
    ~JuceNrProjectAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    JuceNrProjectAudioProcessor& processor;

    Slider gainSlider;

	GroupComponent modes;
	TextButton encodeToggle {"Encode"};
	TextButton decodeToggle {"Decode"};
	TextButton typeBToggle  {"Type B"};
	TextButton typeCToggle  {"Type C"};

	Label gainLabel;
	Label conversionModeLabel;
	Label algorithmModeLabel;

    
public:

    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sliderValue;
	std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> encodeSelection;
	std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> decodeSelection;
	std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> AlgorithmSelection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceNrProjectAudioProcessorEditor)
};
