/*
  ==============================================================================

    PeakBandParameters.cpp
    Created: 24 Mar 2023 8:07:00pm
    Author:  Harvey

  ==============================================================================
*/

#include "PeakBandParameters.h"

//==============================================================================

PeakBandParameters::PeakBandParameters(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID)
    // Passing in the constructor parameters to initialise the peaking band slider components.
    // These parameters include:
    // * The apvts state to link the slider attatchment to the slider
    // * The parameter ID for each slider
    : _freqSlider(stateToUse, parameterID + "-freq")
    , _gainSlider(stateToUse, parameterID + "-gain")
    , _qSlider(stateToUse, parameterID + "-q")
{
    // Adding the unit suffix to each parameter
    _freqSlider.setTextValueSuffix(" Hz");
    _gainSlider.setTextValueSuffix(" dB");
    
    // Displaying all slider parameters
    addAndMakeVisible(_freqSlider);
    addAndMakeVisible(_gainSlider);
    addAndMakeVisible(_qSlider);
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
        juce::FlexItem (_freqSlider).withFlex (0.8f),
        juce::FlexItem (_gainSlider).withFlex (0.8f),
        juce::FlexItem (_qSlider).withFlex (0.8f)
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
