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
class GainSliderAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    GainSliderAudioProcessorEditor (GainSliderAudioProcessor&);
    ~GainSliderAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    GainSliderAudioProcessor& processor;

    Slider gainSlider;

	GroupComponent modes;
	ToggleButton encodeToggle;
	ToggleButton decodeToggle;

    
public:

    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> sliderValue;
	std::unique_ptr <AudioProcessorValueTreeState::ButtonAttachment> encodeSelection;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GainSliderAudioProcessorEditor)
};
