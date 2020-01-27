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
    sliderValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, GAIN_ID, GainSlider);
	encodeSelection = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(processor.treeState, "encode", encodeToggle);
	decodeSelection = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(processor.treeState, "decode", decodeToggle);

    
    setSize (200, 100);

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
	GainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	GainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
	GainSlider.setRange(-48.0f, 0.0f);
	GainSlider.setValue(-15.0f);
	addAndMakeVisible(&GainSlider);

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
    
    //GainSlider.setBounds (getLocalBounds());

	Rectangle<int> area = getLocalBounds();
	Rectangle<int> topArea = area.removeFromTop(area.getHeight() * 0.5);
	Rectangle<int> bottomArea = area.removeFromBottom(area.getHeight() * 0.5);

	encodeToggle.setBounds(topArea.removeFromTop(topArea.getHeight() * 0.3));
	decodeToggle.setBounds(topArea.removeFromTop(topArea.getHeight() * 0.6));
	GainSlider.setBounds(bottomArea.removeFromBottom(bottomArea.getHeight() / 2));
}
