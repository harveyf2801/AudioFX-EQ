/*
  ==============================================================================

    SpectralAnalyser.cpp
    Created: 6 Apr 2023 11:43:45pm
    Author:  Harvey

  ==============================================================================
*/

#include "SpectralAnalyser.h"


SpectralAnalyser::SpectralAnalyser(const std::vector<float>& freqs, const std::vector<float>& gains)
    : _freqs(freqs)
    , _gains(gains)
    , _logFreqs(freqs)
    , _logGains(gains)
    , _minFreq(*std::ranges::min_element(_freqs))
    , _maxFreq(*std::ranges::max_element(_freqs))
    , _minGain(*std::ranges::min_element(_gains))
    , _maxGain(*std::ranges::max_element(_gains))
    , _colourGradient()
{
    _colourGradient.addColour(0, juce::Colours::transparentBlack);
    _colourGradient.addColour(0.2, freqLineColourId);
    _colourGradient.addColour(0.8, freqLineColourId);
    _colourGradient.addColour(1.0, juce::Colours::transparentBlack);
}

SpectralAnalyser::~SpectralAnalyser()
{
}

void SpectralAnalyser::updateXMap(float xmin, float xmax)
{
    for (auto i = 0; i < _freqs.size(); ++i)
    {
        auto normX = juce::mapFromLog10(_freqs[i], _minFreq, _maxFreq);
        _logFreqs[i] = xmin + xmax * normX;
    }
}

void SpectralAnalyser::updateYMap(float ymin, float ymax)
{
    for (auto i = 0; i < _gains.size(); ++i)
    {
        _logGains[i] = juce::jmap(_gains[i], _minGain, _maxGain, ymin, ymax);
    }
}

void SpectralAnalyser::drawBackground()
{
    // bounds
    auto container = getLocalBounds();

    auto left = container.getX();
    auto right = container.getRight();
    auto top = container.getY();
    auto bottom = container.getBottom();
    auto width = container.getWidth();
    auto height = container.getHeight();

    background = juce::Image(juce::Image::ARGB, width, height, true);
    auto g = juce::Graphics(background);
    
    g.setColour(backgroundColourId);
    g.fillAll(backgroundColourId);

    /* ============================================== */

    // Horizontal lines

    _colourGradient.point1 = juce::Point<float>(static_cast<float>(width / 2), static_cast<float>(top));
    _colourGradient.point2 = juce::Point<float>(static_cast<float>(width / 2), static_cast<float>(bottom));

    for (auto i = 0; i < _freqs.size(); ++i)
    {
        auto freq = _freqs[i];
        auto x = _logFreqs[i];

        g.setGradientFill(_colourGradient);
        g.drawVerticalLine(static_cast<int>(x), static_cast<float>(top), static_cast<float>(bottom));

        juce::String str = (freq > 999.f) ? juce::String(freq / 1000.f) + "k" : juce::String(freq);
        str << "Hz";

        auto textWidth = g.getCurrentFont().getStringWidth(str);

        juce::Rectangle<int> r;

        r.setSize(textWidth, fontHeight);
        r.setCentre(static_cast<int>(x), 0);
        r.setY(1);

        g.setColour(labelColourId);
        g.drawFittedText(str, r, juce::Justification::centred, 1);
    }

    /* ============================================== */

    // Vertical lines

    _colourGradient.point1 = juce::Point<float>(static_cast<float>(left), static_cast<float>(container.getCentreY()));
    _colourGradient.point2 = juce::Point<float>(static_cast<float>(right), static_cast<float>(container.getCentreY()));

    for (auto i = 0; i < _gains.size(); ++i)
    {
        auto gain = _gains[i];
        auto y = _logGains[i];

        juce::String str = (gain > 0) ? "+" : "";
        str << gain << "dB";
        auto textWidth = g.getCurrentFont().getStringWidth(str);

        auto lineColour = (gain == 0.f) ? gain0LineColourId : gainLineColourId;

        g.setGradientFill(_colourGradient);
        g.drawHorizontalLine(static_cast<int>(y), static_cast<float>(left), static_cast<float>(right));

        g.setColour(gainLineColourId);

        juce::Rectangle<int> r;
        r.setSize(textWidth, fontHeight);
        r.setX(getWidth() - textWidth);
        r.setCentre(r.getCentreX(), static_cast<int>(y));

        g.drawFittedText(str, r, juce::Justification::centredLeft, 1);

        //str.clear();
        //str << (gain - _maxGain) << "dB";

        //r.setX(1);
        //textWidth = g.getCurrentFont().getStringWidth(str);
        //r.setSize(textWidth, fontHeight);

        //g.drawFittedText(str, r, juce::Justification::centredLeft, 1);
    }
}

void SpectralAnalyser::paint(juce::Graphics& g)
{
    g.drawImage(background, getLocalBounds().toFloat());
}

void SpectralAnalyser::resized()
{
    auto bounds = getLocalBounds();

    updateXMap(static_cast<float>(bounds.getX()), static_cast<float>(bounds.getRight()));
    updateYMap(static_cast<float>(bounds.getY()), static_cast<float>(bounds.getBottom()));

    drawBackground();
}