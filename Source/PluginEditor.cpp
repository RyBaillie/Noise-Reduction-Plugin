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
	setSize(800, 600);

	enum RadioButtonIds {
		EncodingButtons = 1001,
		AlgorithmButtons = 1002
	};

    sliderValue = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.treeState, "gain", gainSlider);
	encodeSelection = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(processor.treeState, "encode", encodeToggle);
	decodeSelection = std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>(processor.treeState, "decode", decodeToggle);

	//Encode Toggle Adjustment
	addAndMakeVisible(conversionModeLabel);
	conversionModeLabel.setText("Conversion Mode", dontSendNotification);

	encodeToggle.setRadioGroupId(EncodingButtons);
	decodeToggle.setRadioGroupId(EncodingButtons);

	encodeToggle.setClickingTogglesState(true);
	decodeToggle.setClickingTogglesState(true);

	encodeToggle.setToggleState(true, false);

	addAndMakeVisible(encodeToggle);
	addAndMakeVisible(decodeToggle);


	// NR Type Toggle Adjustment
	addAndMakeVisible(algorithmModeLabel);
	algorithmModeLabel.setText("Algorithm Mode", dontSendNotification);

	typeBToggle.setRadioGroupId(AlgorithmButtons);
	typeCToggle.setRadioGroupId(AlgorithmButtons);

	typeBToggle.setClickingTogglesState(true);
	typeCToggle.setClickingTogglesState(true);

	typeBToggle.setToggleState(true, false);

	addAndMakeVisible(typeBToggle);
	addAndMakeVisible(typeCToggle);

	// Slider Adjustement

	addAndMakeVisible(gainLabel);
	gainLabel.setText("Gain", dontSendNotification);
	gainLabel.attachToComponent(&gainSlider, false);

	gainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	gainSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
	gainSlider.setRange(-48.0f, 0.0f);
	gainSlider.setValue(-15.0f);
	addAndMakeVisible(&gainSlider);

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
	auto area = getLocalBounds();

	auto headFootHeight = area.getHeight() / 10;
	auto sidebarWidth = area.getWidth() / 3;

	auto header = area.removeFromTop(headFootHeight);
	auto footer = area.removeFromBottom(headFootHeight);
	auto sidebar = area.removeFromLeft(sidebarWidth);

	auto areaItemHeight = area.getHeight() / 10;

	gainSlider.setBounds(area.removeFromTop(areaItemHeight));

	auto sidebarItemHeight = sidebar.getHeight() / 10;
	auto sidebarItemMargin = sidebar.getWidth() * 0.02;

	conversionModeLabel.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));
	encodeToggle.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));
	decodeToggle.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));

	algorithmModeLabel.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));
	typeBToggle.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));
	typeCToggle.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));
}
