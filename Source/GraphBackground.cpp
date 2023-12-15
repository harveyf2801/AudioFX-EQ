/*
  ==============================================================================

    GraphBackground.cpp
    Created: 6 Apr 2023 11:43:45pm
    Author:  Harvey

  ==============================================================================
*/

#include "GraphBackground.h"


GraphBackground::GraphBackground(const juce::Array<float>& freqs, const juce::Array<float>& gains, EQAudioProcessor& p)
    // Intialising all attributes
    : _freqs(freqs)
    , _gains(gains)
    , _logFreqs(freqs)
    , _logGains(gains)
    , _minFreq(_freqs.getFirst())
    , _maxFreq(_freqs.getLast())
    , _minGain(_gains.getFirst())
    , _maxGain(_gains.getLast())
    , _colourGradient()
    , audioProcessor(p)
{
    // Setting the default colours for this component
    setColour(backgroundColourId, juce::Colour (16, 21, 24));
    setColour(freqLineColourId, juce::Colour (49, 54, 57));
    setColour(gainLineColourId, juce::Colour (41, 47, 47));
    setColour(gain0LineColourId, juce::Colour (141, 149, 152));
    setColour(labelColourId, juce::Colour (141, 149, 152));
    
    // Creating the colour gradient
    _colourGradient.addColour(0, juce::Colours::transparentBlack);
    _colourGradient.addColour(0.05, findColour(freqLineColourId));
    _colourGradient.addColour(0.95, findColour(freqLineColourId));
    _colourGradient.addColour(1.0, juce::Colours::transparentBlack);

    audioProcessor.apvts.addParameterListener("low-cut-power", this);
    audioProcessor.apvts.addParameterListener("low-cut-freq", this);
    audioProcessor.apvts.addParameterListener("low-cut-q", this);
    audioProcessor.apvts.addParameterListener("low-shelf-power", this);
    audioProcessor.apvts.addParameterListener("low-shelf-freq", this);
    audioProcessor.apvts.addParameterListener("low-shelf-q", this);
    audioProcessor.apvts.addParameterListener("low-shelf-gain", this);
    audioProcessor.apvts.addParameterListener("peak-1-power", this);
    audioProcessor.apvts.addParameterListener("peak-1-freq", this);
    audioProcessor.apvts.addParameterListener("peak-1-q", this);
    audioProcessor.apvts.addParameterListener("peak-1-gain", this);
    audioProcessor.apvts.addParameterListener("peak-2-power", this);
    audioProcessor.apvts.addParameterListener("peak-2-freq", this);
    audioProcessor.apvts.addParameterListener("peak-2-q", this);
    audioProcessor.apvts.addParameterListener("peak-2-gain", this);
    audioProcessor.apvts.addParameterListener("peak-3-power", this);
    audioProcessor.apvts.addParameterListener("peak-3-freq", this);
    audioProcessor.apvts.addParameterListener("peak-3-q", this);
    audioProcessor.apvts.addParameterListener("peak-3-gain", this);
    audioProcessor.apvts.addParameterListener("high-shelf-power", this);
    audioProcessor.apvts.addParameterListener("high-shelf-freq", this);
    audioProcessor.apvts.addParameterListener("high-shelf-q", this);
    audioProcessor.apvts.addParameterListener("high-shelf-gain", this);
    audioProcessor.apvts.addParameterListener("high-cut-power", this);
    audioProcessor.apvts.addParameterListener("high-cut-freq", this);
    audioProcessor.apvts.addParameterListener("high-cut-q", this);
}

GraphBackground::~GraphBackground()
{
    audioProcessor.apvts.removeParameterListener("low-cut-power", this);
    audioProcessor.apvts.removeParameterListener("low-cut-freq", this);
    audioProcessor.apvts.removeParameterListener("low-cut-q", this);
    audioProcessor.apvts.removeParameterListener("low-shelf-power", this);
    audioProcessor.apvts.removeParameterListener("low-shelf-freq", this);
    audioProcessor.apvts.removeParameterListener("low-shelf-q", this);
    audioProcessor.apvts.removeParameterListener("low-shelf-gain", this);
    audioProcessor.apvts.removeParameterListener("peak-1-power", this);
    audioProcessor.apvts.removeParameterListener("peak-1-freq", this);
    audioProcessor.apvts.removeParameterListener("peak-1-q", this);
    audioProcessor.apvts.removeParameterListener("peak-1-gain", this);
    audioProcessor.apvts.removeParameterListener("peak-2-power", this);
    audioProcessor.apvts.removeParameterListener("peak-2-freq", this);
    audioProcessor.apvts.removeParameterListener("peak-2-q", this);
    audioProcessor.apvts.removeParameterListener("peak-2-gain", this);
    audioProcessor.apvts.removeParameterListener("peak-3-power", this);
    audioProcessor.apvts.removeParameterListener("peak-3-freq", this);
    audioProcessor.apvts.removeParameterListener("peak-3-q", this);
    audioProcessor.apvts.removeParameterListener("peak-3-gain", this);
    audioProcessor.apvts.removeParameterListener("high-shelf-power", this);
    audioProcessor.apvts.removeParameterListener("high-shelf-freq", this);
    audioProcessor.apvts.removeParameterListener("high-shelf-q", this);
    audioProcessor.apvts.removeParameterListener("high-shelf-gain", this);
    audioProcessor.apvts.removeParameterListener("high-cut-power", this);
    audioProcessor.apvts.removeParameterListener("high-cut-freq", this);
    audioProcessor.apvts.removeParameterListener("high-cut-q", this);
}

void GraphBackground::updateXMap(float xmin, float xmax)
{
    // Mapping each frequency line to the corresponding log value
    for (auto i = 0; i < _freqs.size(); ++i)
    {
        auto normX = juce::mapFromLog10(_freqs[i], _minFreq, _maxFreq);
        _logFreqs.insert(i, xmin + xmax * normX);
    }
}

void GraphBackground::updateYMap(float ymin, float ymax)
{
    // Mapping each gain line to the corresponding log value
    for (auto i = 0; i < _gains.size(); ++i)
    {
        _logGains.insert(i, juce::jmap(_gains[i], _minGain, _maxGain, ymin, ymax));
    }
}

void GraphBackground::drawResponseCurve()
{
    // Defining some temp variables to help with dimentions
    auto responseArea = innerGraphContainer;

    auto w = responseArea.getWidth();

    // Get the coefficients from the EQProcessor
    auto highCutCoefficients = audioProcessor._eqProcessor.highCutBand.getCoefficients();
    auto lowCutCoefficients = audioProcessor._eqProcessor.lowCutBand.getCoefficients();

    auto sampleRate = audioProcessor.getSampleRate();
    std::vector<double> mags;

    mags.resize(w);

    for (int i = 0; i < w; ++i)
    {
        double mag = 1.f;
        auto freq = juce::mapToLog10(double(i) / double(w), 20.0, 20000.0);

        if (!audioProcessor._eqProcessor.peakBand1.isBypassed())
            mag *= audioProcessor._eqProcessor.peakBand1.getCoefficients()->getMagnitudeForFrequency(freq, sampleRate);

        if (!audioProcessor._eqProcessor.peakBand2.isBypassed())
            mag *= audioProcessor._eqProcessor.peakBand2.getCoefficients()->getMagnitudeForFrequency(freq, sampleRate);

        if (!audioProcessor._eqProcessor.peakBand3.isBypassed())
            mag *= audioProcessor._eqProcessor.peakBand3.getCoefficients()->getMagnitudeForFrequency(freq, sampleRate);

        if (!audioProcessor._eqProcessor.lowCutBand.isBypassed())
        {
            mag *= audioProcessor._eqProcessor.lowCutBand.getCoefficients()->getMagnitudeForFrequency(freq, sampleRate);
        }

        if (!audioProcessor._eqProcessor.lowShelfBand.isBypassed())
        {
            mag *= audioProcessor._eqProcessor.lowShelfBand.getCoefficients()->getMagnitudeForFrequency(freq, sampleRate);
        }

        if (!audioProcessor._eqProcessor.highShelfBand.isBypassed())
        {
            mag *= audioProcessor._eqProcessor.highShelfBand.getCoefficients()->getMagnitudeForFrequency(freq, sampleRate);
        }

        if (!audioProcessor._eqProcessor.highCutBand.isBypassed())
        {
            mag *= audioProcessor._eqProcessor.highCutBand.getCoefficients()->getMagnitudeForFrequency(freq, sampleRate);
        }

        mags[i] = juce::Decibels::gainToDecibels(mag);
    }

    responseCurve.clear();

    const double outputMin = responseArea.getBottom();
    const double outputMax = responseArea.getY();
    auto map = [outputMin, outputMax](double input)
        {
            return juce::jmap(input, -30.0, 20.0, outputMin, outputMax);
        };

    responseCurve.startNewSubPath(responseArea.getX(), map(mags.front()));

    for (size_t i = 1; i < mags.size(); ++i)
    {
        responseCurve.lineTo(responseArea.getX() + i, map(mags[i]));
    }
}

void GraphBackground::drawBackground()
{
    // Defining some temp variables to help with dimentions
    auto left = innerGraphContainer.getX();
    auto right = innerGraphContainer.getRight();
    auto top = innerGraphContainer.getY();
    auto bottom = innerGraphContainer.getBottom();
    auto width = innerGraphContainer.getWidth();
    auto height = innerGraphContainer.getHeight();

    // Creating a background image to draw on
    background = juce::Image(juce::Image::ARGB, getLocalBounds().getWidth(), getLocalBounds().getHeight(), true);
    auto g = juce::Graphics(background);
    g.setFont(fontHeight);
    
    // Setting the background colour
    g.setColour(findColour(backgroundColourId));
    g.fillAll(findColour(backgroundColourId));

    /* ============================================== */

    // Drawing all horizontal lines
    
    // Setting the gradient to start at the top and end at the bottom
    _colourGradient.point1 = juce::Point<float>(static_cast<float>(width / 2), static_cast<float>(top));
    _colourGradient.point2 = juce::Point<float>(static_cast<float>(width / 2), static_cast<float>(bottom));

    // Itterating through each frequency tick
    for (auto i = 0; i < _freqs.size(); ++i)
    {
        auto freq = _freqs[i];
        auto x = _logFreqs[i];
        
        // Applying the gradient fill to the line
        if (i != 0 && i != (_freqs.size() - 1))
        {
            g.setGradientFill(_colourGradient);
            g.drawVerticalLine(static_cast<int>(x), static_cast<float>(top), static_cast<float>(bottom));
        }

        // Reformatting the string to a shortened version i.e. 10kHz
        juce::String str = (freq > 999.f) ? juce::String(freq / 1000.f) + "k" : juce::String(freq);
        str << "Hz";
        
        // Finding the text width and height to center the text at the tick point
        auto textWidth = g.getCurrentFont().getStringWidth(str);

        juce::Rectangle<int> r;

        r.setSize(textWidth, static_cast<int>(fontHeight));
        r.setY(getLocalBounds().getY());
        r.setX(static_cast<int>(x) - (textWidth / 2));
        
        // Setting the colour of the text / label
        g.setColour(findColour(labelColourId));
        g.drawFittedText(str, r, juce::Justification::centred, 1);
    }

    /* ============================================== */

    // Drawing all vertical lines

    // Setting the gradient points to start at the left and end at the right
    _colourGradient.point1 = juce::Point<float>(static_cast<float>(left), static_cast<float>(innerGraphContainer.getCentreY()));
    _colourGradient.point2 = juce::Point<float>(static_cast<float>(right), static_cast<float>(innerGraphContainer.getCentreY()));

    // Itterating through each gain tick
    for (auto i = 0; i < _gains.size(); ++i)
    {
        auto gain = _gains[i];
        auto y = _logGains[i];
        
        // Drawing the gain line
        if (i != 0 && i != (_gains.size() - 1))
        {
            // Setting the 0 point line to it's specified colour
            if (gain == 0.f)
            {
                // Apply gain 0 line colour to the line
                g.setColour(findColour(gain0LineColourId));
            }
            else {
                // Applying the gradient fill to the line
                g.setGradientFill(_colourGradient);
            }

            g.drawHorizontalLine(static_cast<int>(y), static_cast<float>(left), static_cast<float>(right));
        }
        
        // Setting the label colour
        g.setColour(findColour(labelColourId));

        // Finding the text width and height to center the text at the tick point
        // and reformatting the gain label text applying dB
        juce::String str = (gain > 0) ? "+" : "";
        str << gain << "dB";
        auto textWidth = g.getCurrentFont().getStringWidth(str);
        
        juce::Rectangle<int> r;
        
        r.setSize(textWidth, static_cast<int>(fontHeight));
        r.setX(right);
        r.setY(static_cast<int>(y-(fontHeight/2)));

        // Setting the colour of the text / label
        g.drawFittedText(str, r, juce::Justification::centredLeft, 1);

        // Draws gain ticks to the left of the graph with skewedFactor so 0 is top
        str.clear();
        str << (gain - _maxGain) << "dB";

        textWidth = g.getCurrentFont().getStringWidth(str);
        r.setSize(textWidth, static_cast<int>(fontHeight));
        r.setX(left - textWidth);

        g.drawFittedText(str, r, juce::Justification::centredRight, 1);
    }
}

void GraphBackground::paint(juce::Graphics& g)
{
    // Redrawing the image
    g.drawImage(background, getLocalBounds().toFloat());
    drawResponseCurve();

    g.setColour(juce::Colours::white);
    g.strokePath(responseCurve, juce::PathStrokeType(2.f));
}

void GraphBackground::resized()
{
    // Getting the component bounds
    auto bounds = getLocalBounds();

    // Reducing the bounds for the main graph container
    innerGraphContainer = bounds.reduced(45, 30);

    // Updating the X and Y maps for drawing the lines
    updateXMap(static_cast<float>(innerGraphContainer.getX()), static_cast<float>(innerGraphContainer.getWidth()));
    updateYMap(static_cast<float>(innerGraphContainer.getBottom()), static_cast<float>(innerGraphContainer.getY()));

    // Redraw the background image
    drawBackground();
}

void GraphBackground::parameterChanged(const juce::String& parameterID, float newValue)
{
    repaint();
}