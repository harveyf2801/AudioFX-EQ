

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQAudioProcessorEditor::EQAudioProcessorEditor (EQAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , _audioProcessor (p)
    , _graphBackground (
        { 20.f, 40.f, 100.f, 200.f, 400.f, 600.f, 1000.f, 2000.f, 4000.f, 6000.f, 10000.f, 20000.f },
        { -30, -25, -20, -15, -10, -5, 0, 5, 10, 20 }
    )
    , _lowCutParams (_audioProcessor.apvts, "low-cut")
    , _highCutParams (_audioProcessor.apvts, "high-cut")
    , bbb (juce::ShapeButton("shapeButton", juce::Colours::red, juce::Colours::yellow, juce::Colours::blue))
{

    // Creating all peaking band sliders and appending to the peak sliders array
    for (auto i = 1; i <= EQAudioProcessor::peakingBands; ++i)
    {
        juce::String id = "peak-" + juce::String(i);

        auto peakBand = new PeakBandParameters(_audioProcessor.apvts, id);

        _peakBands.add(peakBand);

        //addAndMakeVisible(peakBand);
    }

    //addAndMakeVisible(_lowCutParams);
    //addAndMakeVisible(_highCutParams);

    addAndMakeVisible (_graphBackground);
    addAndMakeVisible(bbb);

    const juce::Displays::Display* screen = juce::Desktop::getInstance().getDisplays().getPrimaryDisplay();
    bounds = (screen != nullptr) ? screen->userArea : juce::Rectangle<int>(0, 0, 1000, 1000);

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

    juce::FlexBox flexContainer (
        juce::FlexBox::Direction::column,
        juce::FlexBox::Wrap::noWrap,
        juce::FlexBox::AlignContent::stretch,
        juce::FlexBox::AlignItems::stretch,
        juce::FlexBox::JustifyContent::center
    );

    flexContainer.items.add(
        juce::FlexItem (_graphBackground).withFlex (0.8),
        juce::FlexItem (bbb).withFlex (0.2)
    );

    flexContainer.performLayout(bounds.toFloat());


    //auto width = bounds.getWidth() / (2 + EQAudioProcessor::peakingBands);

    //_lowCutParams.setBounds (bounds.removeFromLeft(width));

    //for (PeakBandParameters* peakBand : _peakBands)
    //{
    //    peakBand->setBounds(bounds.removeFromLeft(width));
    //}

    //_highCutParams.setBounds(bounds.removeFromLeft(width));
}
