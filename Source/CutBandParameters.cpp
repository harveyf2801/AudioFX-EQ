/*
  ==============================================================================

    CutBandParameters.cpp
    Created: 24 Mar 2023 8:06:19pm
    Author:  Harvey

  ==============================================================================
*/

#include "CutBandParameters.h"

//==============================================================================

CutBandParameters::CutBandParameters(juce::AudioProcessorValueTreeState& stateToUse, const juce::String parameterID)
    // Passing in the constructor parameters to initialise the cut band slider components.
    // These parameters include:
    // * The apvts state to link the slider attatchment to the slider
    // * The parameter ID for each slider
    : _freqSlider (stateToUse, parameterID + "-freq")
    , _slopeSlider(stateToUse, parameterID + "-slope", juce::Array<int>(6, 12, 18, 24, 36, 48))
    , _qSlider(stateToUse, parameterID + "-q")
{
    // Adding the unit suffix to each parameter
    _freqSlider.setTextValueSuffix(" Hz");
    _slopeSlider.setTextValueSuffix(" dB/Oct");
    
    // Make the slider parameters visible
    addAndMakeVisible(_freqSlider);
    addAndMakeVisible(_slopeSlider);
    addAndMakeVisible(_qSlider);
}

CutBandParameters::~CutBandParameters()
{
}

void CutBandParameters::resized()
{
    // Getting the component bounds
    auto bounds = getLocalBounds();

    // -----------------------
    
    // Creating a flexbox container for all of the cut parameters.
    // Configuring the container so that it stretches to the full width/height
    // and centers the content, placed along the Y axis.
    juce::FlexBox cutParamFlexContainer (
        juce::FlexBox::Direction::column,
        juce::FlexBox::Wrap::noWrap,
        juce::FlexBox::AlignContent::stretch,
        juce::FlexBox::AlignItems::stretch,
        juce::FlexBox::JustifyContent::center
    );

    // Adding each element to the parameter container
    cutParamFlexContainer.items.add(
        juce::FlexItem (_freqSlider).withFlex (0.8f),
        juce::FlexItem (_slopeSlider).withFlex (0.8f),
        juce::FlexItem (_qSlider).withFlex (0.8f)
    );
    
    // Applying the layout on the bounds of the component
    cutParamFlexContainer.performLayout(bounds);

    // * Old method to layout components
    //    auto height = bounds.getHeight() / 3;
    //    _freqSlider.setBounds(bounds.removeFromTop(height));
    //    _slopeSlider->setBounds(bounds.removeFromTop(height));
    //    _qSlider.setBounds(bounds.removeFromTop(height));
}
