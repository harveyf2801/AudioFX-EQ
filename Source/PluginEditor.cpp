

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQAudioProcessorEditor::EQAudioProcessorEditor (EQAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , _audioProcessor (p)
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

    setSize(400, 300);
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

    auto bounds = getBounds();

    auto width = bounds.getWidth() / (2 + EQAudioProcessor::peakingBands);

    _lowCutParams.setBounds (bounds.removeFromLeft(width));

    for (PeakBandParameters* peakBand : _peakBands)
    {
        peakBand->setBounds(bounds.removeFromLeft(width));
    }

    _highCutParams.setBounds(bounds.removeFromLeft(width));
}
