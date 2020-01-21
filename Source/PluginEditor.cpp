/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
JuceNrProjectAudioProcessorEditor::JuceNrProjectAudioProcessorEditor (JuceNrProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	enum RadioButtonIds {
		EncodingButtons = 1001,
		AlgorithmButtons = 1002
	};

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    sliderValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, JuceNrProject);
    
    setSize (200, 400);

	//Encode Toggle Adjustment
	encodeToggle.setRadioGroupId(EncodingButtons);
	decodeToggle.setRadioGroupId(EncodingButtons);
	addAndMakeVisible(encodeToggle);
	addAndMakeVisible(decodeToggle);

	// NR Type Toggle Adjustment
	typeBToggle.setRadioGroupId(AlgorithmButtons);
	TypeCToggle.setRadioGroupId(AlgorithmButtons);
	addAndMakeVisible(typeBToggle);
	addAndMakeVisible(TypeCToggle);

	// Slider Adjustement
	JuceNrProject.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	JuceNrProject.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
	JuceNrProject.setRange(-48.0f, 0.0f);
	JuceNrProject.setValue(-15.0f);
	addAndMakeVisible(&JuceNrProject);

}

JuceNrProjectAudioProcessorEditor::~JuceNrProjectAudioProcessorEditor()
{
}

//==============================================================================
void JuceNrProjectAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
   
}

void JuceNrProjectAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    JuceNrProject.setBounds (getLocalBounds());

}
