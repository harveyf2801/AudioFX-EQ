/*
  ==============================================================================

    PeakBandParameters.cpp
    Created: 24 Mar 2023 8:07:00pm
    Author:  Harvey

  ==============================================================================
*/

#include "PeakBandParameters.h"

//==============================================================================

PeakBandParameters::PeakBandParameters(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID, const juce::String bandName)
    // Passing in the constructor parameters to initialise the peaking band slider components.
    // These parameters include:
    // * The apvts state to link the slider attatchment to the slider
    // * The parameter ID for each slider
    : _powerButton(stateToUse, parameterID + "-power")
    , _freqSlider(stateToUse, parameterID + "-freq")
    , _gainSlider(stateToUse, parameterID + "-gain")
    , _qSlider(stateToUse, parameterID + "-q")
{
    // Adding the unit suffix to each parameter
    _freqSlider.setTextValueSuffix(" Hz");
    _gainSlider.setTextValueSuffix(" dB");
    
    // Setting the text for the label
    // * Don't send notification means that a listener won't need to be be notified of any changes to this text as it will be static
    _label.setText(bandName, juce::dontSendNotification);
    _label.setJustificationType(juce::Justification::centred);

    // Displaying all parameters
    addAndMakeVisible(_powerButton);
    addAndMakeVisible(_freqSlider);
    addAndMakeVisible(_gainSlider);
    addAndMakeVisible(_qSlider);
    addAndMakeVisible(_label);
}

PeakBandParameters::~PeakBandParameters()
{
}

void PeakBandParameters::resized()
{
    // Getting the component bounds
    auto bounds = getLocalBounds();

    // -----------------------
    
    // Creating a flexbox container for all of the peaking parameters.
    // Configuring the container so that it stretches to the full width/height
    // and centers the content, placed along the Y axis.
    juce::FlexBox peakParamFlexContainer (
        juce::FlexBox::Direction::column,
        juce::FlexBox::Wrap::noWrap,
        juce::FlexBox::AlignContent::stretch,
        juce::FlexBox::AlignItems::stretch,
        juce::FlexBox::JustifyContent::center
    );

    // Adding each element to the parameter container
    peakParamFlexContainer.items.add(
        juce::FlexItem (_powerButton).withFlex (0.3f).withMargin(juce::FlexItem::Margin(5, 5, 5, 5)), // margin for flex gap
        juce::FlexItem (_label).withFlex(0.3f).withMargin(juce::FlexItem::Margin(5, 5, 5, 5)), // margin for flex gap
        juce::FlexItem (_freqSlider).withFlex (0.8f).withMargin(juce::FlexItem::Margin(5, 5, 5, 5)), // margin for flex gap
        juce::FlexItem (_gainSlider).withFlex (0.8f).withMargin(juce::FlexItem::Margin(5, 5, 5, 5)), // margin for flex gap
        juce::FlexItem (_qSlider).withFlex (0.8f).withMargin(juce::FlexItem::Margin(5, 5, 5, 5)) // margin for flex gap
    );
    
    // Applying the layout on the bounds of the component
    peakParamFlexContainer.performLayout(bounds);

    // * Old method to layout components
    //    auto height = bounds.getHeight() / 3;
    //
    //    _freqSlider.setBounds(bounds.removeFromTop(height));
    //    _gainSlider.setBounds(bounds.removeFromTop(height));
    //    _qSlider.setBounds(bounds.removeFromTop(height));
}
