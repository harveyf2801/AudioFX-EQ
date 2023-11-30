

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

EQAudioProcessorEditor::EQAudioProcessorEditor (EQAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , _audioProcessor (p)

    // Initialising the spectral analyser object with the frequency ticks and gain ticks to display on the graph
    , _spectralAnalyser (
        juce::Array<float>( 20.f, 40.f, 100.f, 200.f, 400.f, 600.f, 1000.f, 2000.f, 4000.f, 6000.f, 10000.f, 20000.f ),
        juce::Array<float>( -30, -25, -20, -15, -10, -5, 0, 5, 10, 20 )
    )
    // Initialising the cut parameters, passing in a reference to the audio processor value tree state, and the ID for the parameter group
    , _lowCutParams (_audioProcessor.apvts, "low-cut")
    , _highCutParams (_audioProcessor.apvts, "high-cut")
{
    // Setting the custom look and feel
    setLookAndFeel (&_customLookAndFeel);

    // Creating all peaking band sliders and appending to the peak sliders array
    for (auto i = 1; i <= EQAudioProcessor::peakingBands; ++i)
    {
        juce::String id = "peak-" + juce::String(i);

        auto peakBand = new PeakBandParameters(_audioProcessor.apvts, id);

        _peakBands.add(peakBand);
        
        // Showing the peak band parameters on the plugin
        addAndMakeVisible(peakBand);
    }
    
    // Displaying the cut band parameters on the plugin
    addAndMakeVisible(_lowCutParams);
    addAndMakeVisible(_highCutParams);

    // Displaying the spectral analyser
    addAndMakeVisible (_spectralAnalyser);
    
    // Finding the primary screen's dimentions and finding the user area (i.e. minus the top and bottom taskbar)
    const juce::Displays::Display* screen = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    auto bounds = (screen != nullptr) ? screen->userArea : juce::Rectangle<int>(0, 0, 1000, 1000);

    setSize(static_cast<int>(bounds.getWidth() / 2), static_cast<int>(bounds.getHeight() / 2));
    
    // Setting the limits of the plugin to have a min of half the screen dimentions and max as the user area
    setResizeLimits (
        bounds.getWidth() / 2, bounds.getHeight() / 2,
        bounds.getWidth(),     bounds.getHeight()
    );
    
    // Allowing the plugin to be resized from all corners of the window
    setResizable(true, false);
}

EQAudioProcessorEditor::~EQAudioProcessorEditor()
{
    setLookAndFeel (nullptr);
}

//==============================================================================

void EQAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (juce::Colours::dimgrey);//(getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void EQAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // Getting the windows bounds
    auto bounds = getLocalBounds();

    // -----------------------
    
    // Creating a flexbox container for all of the parameter groups.
    // Configuring the container so that it stretches to the full width/height
    // and centers the content, placed along the X axis.
    juce::FlexBox paramFlexContainer (
        juce::FlexBox::Direction::row,
        juce::FlexBox::Wrap::noWrap,
        juce::FlexBox::AlignContent::stretch,
        juce::FlexBox::AlignItems::stretch,
        juce::FlexBox::JustifyContent::center
    );

    // Adding each element to the parameter container
    paramFlexContainer.items.add(
        juce::FlexItem (_lowCutParams).withFlex (0.8f)
    );
    
    for (PeakBandParameters* peakBand : _peakBands)
    {
        paramFlexContainer.items.add(
            juce::FlexItem (*peakBand).withFlex (0.8f)
        );
    }

    paramFlexContainer.items.add(
        juce::FlexItem (_highCutParams).withFlex (0.8f)
    );
    
//    paramFlexContainer.performLayout(bounds);
    
    // -----------------------
    
    // Creating a flexbox container for the root container.
    // Configuring the container so that it stretches to the full width/height
    // and centers the content, placed along the Y axis.
    juce::FlexBox rootFlexContainer (
        juce::FlexBox::Direction::column,
        juce::FlexBox::Wrap::noWrap,
        juce::FlexBox::AlignContent::stretch,
        juce::FlexBox::AlignItems::stretch,
        juce::FlexBox::JustifyContent::center
    );
    
    // Adding each element to the root container
    rootFlexContainer.items.add(
        juce::FlexItem (_spectralAnalyser).withFlex (0.8f, 0.8f)
    );
    rootFlexContainer.items.add(
        juce::FlexItem (paramFlexContainer).withFlex (0.8f, 0.8f)
    );
    
    // Applying the layout on the bounds of the plugin window
    rootFlexContainer.performLayout(bounds);
}
