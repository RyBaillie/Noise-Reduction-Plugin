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

	Slider decibelLimitSlider;
	Slider filterCutoffSlider;
	Slider filterResonanceSlider;
	Slider compressorRatioSlider;
	Slider attackMsSlider;
	Slider releaseMsSlider;

	GroupComponent modes;
	TextButton nrEnabledToggle{ "On" };
	TextButton encodeToggle {"Encode"};
	TextButton decodeToggle {"Decode"};
	TextButton typeBToggle  {"Type B"};
	TextButton typeCToggle  {"Type C"};

	Label nrEnabledLabel;
	Label gainLabel;
	Label decibelLimitLabel;
	Label filterCutoffLabel;
	Label filterResonanceLabel;
	Label compressorRatioLabel;
	Label conversionModeLabel;
	Label algorithmModeLabel;
	Label attackMsSliderLabel;
	Label releaseMsSliderLabel;

	Label envelopeLabel;
	Label compressorLabel;
	Label filterCategoryLabel;

	Label compilationInfoLabel;

    
public:

	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> decibelLimitSliderValue;
	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> compressorRatioSliderValue;
	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> filterCutoffSliderValue;
	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> filterResonanceSliderValue;
	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> attackMsSliderValue;
	std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> releaseMsSliderValue;
	std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> nrEnabledSelection;
	std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> encodeSelection;
	std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> decodeSelection;
	std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> algorithmSelection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (JuceNrProjectAudioProcessorEditor)
};
