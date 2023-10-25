

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQAudioProcessorEditor::EQAudioProcessorEditor (EQAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , _audioProcessor (p)
    , _SpectralAnalyser (
        { 20.f, 40.f, 100.f, 200.f, 400.f, 600.f, 1000.f, 2000.f, 4000.f, 6000.f, 10000.f, 20000.f },
        { -30, -25, -20, -15, -10, -5, 0, 5, 10, 20 }
    )
    , _lowCutParams (_audioProcessor.apvts, "low-cut")
    , _highCutParams (_audioProcessor.apvts, "high-cut")
{

    // Creating all peaking band sliders and appending to the peak sliders array
    for (auto i = 1; i <= EQAudioProcessor::peakingBands; ++i)
    {
        juce::String id = "peak-" + juce::String(i);

        auto peakBand = new PeakBandParameters(_audioProcessor.apvts, id);

        _peakBands.add(peakBand);

        addAndMakeVisible(peakBand);
    }

    addAndMakeVisible(_lowCutParams);
    addAndMakeVisible(_highCutParams);

    addAndMakeVisible (_SpectralAnalyser);

    const juce::Displays::Display* screen = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    auto bounds = (screen != nullptr) ? screen->userArea : juce::Rectangle<int>(0, 0, 1000, 1000);

    setSize(static_cast<int>(bounds.getWidth() / 2), static_cast<int>(bounds.getHeight() / 2));

    setResizeLimits (
        bounds.getWidth() / 2, bounds.getHeight() / 2,
        bounds.getWidth(),     bounds.getHeight()
    );

    setResizable(true, false);
}

EQAudioProcessorEditor::~EQAudioProcessorEditor()
{
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

    auto bounds = getLocalBounds();

    juce::FlexBox spectralFlexContainer (
        juce::FlexBox::Direction::column,
        juce::FlexBox::Wrap::noWrap,
        juce::FlexBox::AlignContent::stretch,
        juce::FlexBox::AlignItems::stretch,
        juce::FlexBox::JustifyContent::center
    );

    spectralFlexContainer.items.add(
        juce::FlexItem (_SpectralAnalyser).withFlex (0.8f, 0.8f)
    );

    auto analyserbounds = bounds.removeFromTop(static_cast<int>(bounds.getHeight()/2.f)).toFloat();
    spectralFlexContainer.performLayout(analyserbounds);

    // -----------------------

    juce::FlexBox paramFlexContainer (
        juce::FlexBox::Direction::row,
        juce::FlexBox::Wrap::noWrap,
        juce::FlexBox::AlignContent::stretch,
        juce::FlexBox::AlignItems::stretch,
        juce::FlexBox::JustifyContent::center
    );

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
    

    paramFlexContainer.performLayout(bounds);
}
