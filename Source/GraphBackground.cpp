/*
  ==============================================================================

    GraphBackground.cpp
    Created: 6 Apr 2023 11:43:45pm
    Author:  Harvey

  ==============================================================================
*/

#include "GraphBackground.h"


GraphBackground::GraphBackground(const std::vector<float>& freqs, const std::vector<float>& gains)
    : _freqs (freqs)
    , _gains (gains)
    , _minGain (*std::ranges::min_element(_gains))
    , _maxGain (*std::ranges::max_element(_gains))
{

    for (auto freq : _freqs)
    {
        juce::String str = (freq > 999.f) ? juce::String(freq / 1000.f) + "k" : juce::String(freq);
        str << "Hz";
        _freqLabels.add(new juce::Label(str, str));
    }

    for (auto gain : _gains)
    {
        juce::String str = (gain > 0) ? "+" : "";
        str << gain << "dB";
        _rightGainLabels.add(new juce::Label(str, str));

        str.clear();
        str << (gain - _maxGain) << "dB";
        _leftGainLabels.add(new juce::Label(str, str));
    }
}

GraphBackground::~GraphBackground()
{
}

std::vector<float> GraphBackground::getLogXfreqs(int xmin, int xmax)
{
    std::vector<float> logXfreqs;

    for (auto f : _freqs)
    {
        auto normX = juce::mapFromLog10(f, 20.f, 20000.f);
        logXfreqs.push_back(xmin + xmax * normX);
    }

    return logXfreqs;
}

void GraphBackground::drawFreqLabels(juce::Graphics& g)
{}

void GraphBackground::drawLeftGainLabels(juce::Graphics& g)
{}

void GraphBackground::drawRightGainLabels(juce::Graphics& g)
{}

void GraphBackground::drawGraph(juce::Graphics& g)
{
    
    g.setFont(fontHeight);

    // bounds
    auto graphBounds = getLocalBounds();
    auto borderTopBounds = graphBounds.removeFromTop(fontHeight);
    auto borderLeftBounds = graphBounds.removeFromLeft(20);
    auto borderRightBounds = graphBounds.removeFromRight(20);

    g.setColour(backgroundColour);
    g.fillRect(borderTopBounds);
    g.fillRect(borderLeftBounds);
    g.fillRect(borderRightBounds);

    auto left = graphBounds.getX();
    auto right = graphBounds.getRight();
    auto top = graphBounds.getY();
    auto bottom = graphBounds.getBottom();
    auto width = graphBounds.getWidth();

    /* ============================================== */

    auto logXFreqs = getLogXfreqs(left, width);

    for (int i = 0; i < _freqs.size(); ++i)
    {
        auto f = _freqs[i];
        auto x = logXFreqs[i];

        g.setColour(freqLineColour);
        g.drawVerticalLine(x, top, bottom);

        juce::String str = (f > 999.f) ? juce::String(f / 1000.f) + "k" : juce::String(f);
        str << "Hz";

        auto textWidth = g.getCurrentFont().getStringWidth(str);

        juce::Rectangle<int> r;

        r.setSize(textWidth, borderTopBounds.getHeight());
        r.setCentre(x, 0);
        r.setY(0);

        g.setColour(labelColour);
        g.drawFittedText(str, r, juce::Justification::centred, 1);
    }

    /* ============================================== */

    for (auto gainDb : _gains)
    {
        auto y = juce::jmap(gainDb, _minGain, _maxGain, float(bottom), float(top));

        g.setColour(gainDb == 0.f ? gain0LineColour : gainLineColour);
        g.drawHorizontalLine(y, left, right);

        juce::String str;
        if (gainDb > 0)
            str << "+";
        str << gainDb;
        str << "dB";

        auto textWidth = g.getCurrentFont().getStringWidth(str);

        juce::Rectangle<int> r;
        r.setSize(textWidth, fontHeight);
        r.setCentre(borderRightBounds.getCentreX(), y);

        g.drawFittedText(str, r, juce::Justification::centredLeft, 1);

        str.clear();
        str << (gainDb - maxGain);
        str << "dB";

        r.setCentre(borderLeftBounds.getCentreX(), y);
        textWidth = g.getCurrentFont().getStringWidth(str);
        r.setSize(textWidth, fontHeight);

        g.setColour(gainLineColour);
        g.drawFittedText(str, r, juce::Justification::centredLeft, 1);
    }
}

void GraphBackground::paint(juce::Graphics& g)
{
    g.fillAll(backgroundColour.darker());

    drawFreqLabels(g);
}

void GraphBackground::resized()
{
    graphBounds = getLocalBounds();
    borderTopBounds = graphBounds.removeFromTop(fontHeight);
    borderLeftBounds = graphBounds.removeFromLeft(20);
    borderRightBounds = graphBounds.removeFromRight(20);
}