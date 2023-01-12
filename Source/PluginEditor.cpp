

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EQAudioProcessorEditor::EQAudioProcessorEditor (EQAudioProcessor& p)
    : AudioProcessorEditor (&p)
    , _audioProcessor (p)
{
    setSize(400, 300);

    // Creating all cut band sliders and appending to the cut sliders array
    for (juce::String i : { "Low", "High" })
    {
        juce::String id = i + "-cut-";

        auto freqSlider = LabelledSlider(_audioProcessor.apvts, id + "freq");
        auto gainSlider = LabelledSlider(_audioProcessor.apvts, id + "gain");
        auto slopeChoice = juce::MultiChoicePropertyComponent(); // need a custom choice component

        _cutSliders.push_back(freqSlider);
        _cutSliders.push_back(gainSlider);
        _cutSliders.push_back(slopeChoice);

        freqSlider.setTextValueSuffix(" Hz");
        gainSlider.setTextValueSuffix(" gain");

        addAndMakeVisible(freqSlider);
        addAndMakeVisible(gainSlider);
        addAndMakeVisible(slopeSlider);
    }

    // Creating all peaking band sliders and appending to the peak sliders array
    for (auto i = 1; i <= EQAudioProcessor::peakingBands; ++i)
    {
        juce::String id = "peak-" + juce::String(i) + "-";

        auto freqSlider = std::make_unique<LabelledSlider>(_audioProcessor.apvts, id + "freq");
        auto gainSlider = std::make_unique<LabelledSlider>(_audioProcessor.apvts, id + "gain");
        auto qSlider = std::make_unique<LabelledSlider>(_audioProcessor.apvts, id + "q");

        _peakSliders.add(freqSlider);
        _peakSliders.add(gainSlider);
        _peakSliders.add(qSlider);

        freqSlider->setTextValueSuffix(" Hz");
        gainSlider->setTextValueSuffix(" gain");

        addAndMakeVisible(*freqSlider);
        addAndMakeVisible(*gainSlider);
        addAndMakeVisible(*qSlider);
    }

    //_slider.setTextValueSuffix(" Hz");
    //addAndMakeVisible (&_slider);
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

    //_slider.setBounds (2, 2, 200, 200);
}
