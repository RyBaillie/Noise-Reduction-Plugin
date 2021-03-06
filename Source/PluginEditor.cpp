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
	setSize(800, 500);

	enum RadioButtonIds {
		EncodingButtons = 1001,
		AlgorithmButtons = 1002
	};

	decibelLimitSliderValue = 
		std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(processor.treeState, "dbLimit", decibelLimitSlider);
	filterCutoffSliderValue = 
		std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(processor.treeState, "cutoff", filterCutoffSlider);
	filterResonanceSliderValue = 
		std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(processor.treeState, "resonance", filterResonanceSlider);
	compressorRatioSliderValue = 
		std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(processor.treeState, "compressorRatio", compressorRatioSlider);
	attackMsSliderValue = 
		std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(processor.treeState, "attackMs", attackMsSlider);
	releaseMsSliderValue = 
		std::make_unique<AudioProcessorValueTreeState::SliderAttachment>
		(processor.treeState, "releaseMs", releaseMsSlider);

	encodeSelection = 
		std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
		(processor.treeState, "encodeBtn", encodeToggle);
	nrEnabledSelection = 
		std::make_unique<AudioProcessorValueTreeState::ButtonAttachment>
		(processor.treeState, "noiseReductionOnBtn", nrEnabledToggle);

	//NR Enabled Toggle Adjustment
	addAndMakeVisible(nrEnabledLabel);
	nrEnabledLabel.setText("Noise Reduction Enabled", dontSendNotification);

	nrEnabledToggle.setClickingTogglesState(true);
	addAndMakeVisible(nrEnabledToggle);

	//Encode Toggle Adjustment
	addAndMakeVisible(conversionModeLabel);
	conversionModeLabel.setText("Conversion Mode", dontSendNotification);

	encodeToggle.setRadioGroupId(EncodingButtons);
	decodeToggle.setRadioGroupId(EncodingButtons);

	encodeToggle.setClickingTogglesState(true);
	decodeToggle.setClickingTogglesState(true);
	addAndMakeVisible(encodeToggle);
	addAndMakeVisible(decodeToggle);

	// NR Type Toggle Adjustment

	//addAndMakeVisible(algorithmModeLabel);
	algorithmModeLabel.setText("Algorithm Mode", dontSendNotification);

	typeBToggle.setRadioGroupId(AlgorithmButtons);
	typeCToggle.setRadioGroupId(AlgorithmButtons);

	typeBToggle.setClickingTogglesState(true);
	typeCToggle.setClickingTogglesState(true);

	typeBToggle.setToggleState(true, false);

	//addAndMakeVisible(typeBToggle);
	//addAndMakeVisible(typeCToggle);

	// Decibel Limit Slider Adjustement

	addAndMakeVisible(decibelLimitLabel);
	decibelLimitLabel.setText("Decibel Limit", dontSendNotification);
	decibelLimitLabel.attachToComponent(&decibelLimitSlider, false);

	decibelLimitSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	decibelLimitSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
	addAndMakeVisible(&decibelLimitSlider);

	// Attack (ms) Slider Adjustement

	//addAndMakeVisible(attackMsSliderLabel);
	attackMsSliderLabel.setText("Attack (ms)", dontSendNotification);
	attackMsSliderLabel.attachToComponent(&attackMsSlider, false);

	attackMsSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	attackMsSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
	//addAndMakeVisible(&attackMsSlider);

	// Envelope

	//addAndMakeVisible(envelopeLabel);
	envelopeLabel.setText("Envelope", dontSendNotification);
	envelopeLabel.setJustificationType(Justification::centred);

	// Release (ms) Slider Adjustement

	//addAndMakeVisible(releaseMsSliderLabel);
	releaseMsSliderLabel.setText("Release (ms)", dontSendNotification);
	releaseMsSliderLabel.attachToComponent(&releaseMsSlider, false);

	releaseMsSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	releaseMsSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
	//addAndMakeVisible(&releaseMsSlider);

	// Filter

	addAndMakeVisible(filterCategoryLabel);
	filterCategoryLabel.setText("Filter", dontSendNotification);
	filterCategoryLabel.setJustificationType(Justification::centred);

	// Filter Cutoff Slider Adjustement

	addAndMakeVisible(filterCutoffLabel);
	filterCutoffLabel.setText("Cutoff (f)", dontSendNotification);
	filterCutoffLabel.attachToComponent(&filterCutoffSlider, false);

	filterCutoffSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	filterCutoffSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
	filterCutoffSlider.setSkewFactorFromMidPoint(500.);
	addAndMakeVisible(&filterCutoffSlider);

	// Filter Resonance Slider Adjustement

	addAndMakeVisible(filterResonanceLabel);
	filterResonanceLabel.setText("Resonance", dontSendNotification);
	filterResonanceLabel.attachToComponent(&filterResonanceSlider, false);

	filterResonanceSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	filterResonanceSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
	addAndMakeVisible(&filterResonanceSlider);

	// Compressor

	addAndMakeVisible(compressorLabel);
	compressorLabel.setText("Compressor", dontSendNotification);
	compressorLabel.setJustificationType(Justification::centred);

	// Compressor Ratio Slider Adjustement

	addAndMakeVisible(compressorRatioLabel);
	compressorRatioLabel.setText("Ratio", dontSendNotification);
	compressorRatioLabel.attachToComponent(&compressorRatioSlider, false);

	compressorRatioSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
	compressorRatioSlider.setTextBoxStyle(Slider::TextBoxBelow, true, 100, 25);
	addAndMakeVisible(&compressorRatioSlider);

	// Compilation Info

	String compileMessage = "Last changed on " __DATE__ " at " __TIME__;
	addAndMakeVisible(compilationInfoLabel);
	compilationInfoLabel.setJustificationType(Justification::centred);
	compilationInfoLabel.setText(compileMessage, dontSendNotification);
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

	auto areaItemHeight = area.getHeight() / 12;

	/*envelopeLabel.setBounds(area.removeFromTop(areaItemHeight));
	attackMsSlider.setBounds(area.removeFromTop(areaItemHeight));
	releaseMsSlider.setBounds(area.removeFromTop(areaItemHeight));*/

	filterCategoryLabel.setBounds(area.removeFromTop(areaItemHeight));
	filterCutoffSlider.setBounds(area.removeFromTop(areaItemHeight));
	filterResonanceSlider.setBounds(area.removeFromTop(areaItemHeight));

	compressorLabel.setBounds(area.removeFromTop(areaItemHeight));
	decibelLimitSlider.setBounds(area.removeFromTop(areaItemHeight));
	compressorRatioSlider.setBounds(area.removeFromTop(areaItemHeight));
	
	auto sidebarItemHeight = sidebar.getHeight() / 10;
	auto sidebarItemMargin = sidebar.getWidth() * 0.02;

	nrEnabledLabel.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));
	nrEnabledToggle.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));

	conversionModeLabel.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));
	encodeToggle.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));
	decodeToggle.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));

	algorithmModeLabel.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));
	typeBToggle.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));
	typeCToggle.setBounds(sidebar.removeFromTop(sidebarItemHeight).reduced(sidebarItemMargin));


	auto footerItemHeight = footer.getHeight();

	compilationInfoLabel.setBounds(footer.removeFromTop(footerItemHeight));
}
