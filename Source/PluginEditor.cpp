/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
GainSliderAudioProcessorEditor::GainSliderAudioProcessorEditor (GainSliderAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	enum RadioButtonIds {
		EncodingButtons = 1001
	};

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    sliderValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, gainSlider);
    
    setSize (200, 400);

    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
    gainSlider.setRange(-48.0f, 0.0f);
    gainSlider.setValue(-15.0f);
    addAndMakeVisible(&gainSlider);

	encodeToggle.setRadioGroupId(EncodingButtons);
	decodeToggle.setRadioGroupId(EncodingButtons);
	addAndMakeVisible(encodeToggle);
	addAndMakeVisible(decodeToggle);
}

GainSliderAudioProcessorEditor::~GainSliderAudioProcessorEditor()
{
}

//==============================================================================
void GainSliderAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
   
}

void GainSliderAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    gainSlider.setBounds (getLocalBounds());

}
