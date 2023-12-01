/*
  ==============================================================================

    GraphBackground.cpp
    Created: 6 Apr 2023 11:43:45pm
    Author:  Harvey

  ==============================================================================
*/

#include "GraphBackground.h"


GraphBackground::GraphBackground(const juce::Array<float>& freqs, const juce::Array<float>& gains)
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
{
    // Setting the default colours for this component
    setColour(backgroundColourId, juce::Colour (16, 21, 24));
    setColour(freqLineColourId, juce::Colour (49, 54, 57));
    setColour(gainLineColourId, juce::Colour (41, 47, 47));
    setColour(gain0LineColourId, juce::Colour (141, 149, 152));
    setColour(labelColourId, juce::Colour (141, 149, 152));
    
    // Creating the colour gradient
    _colourGradient.addColour(0, juce::Colours::transparentBlack);
    _colourGradient.addColour(0.1, findColour(freqLineColourId));
    _colourGradient.addColour(0.9, findColour(freqLineColourId));
    _colourGradient.addColour(1.0, juce::Colours::transparentBlack);
}

GraphBackground::~GraphBackground()
{
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

void GraphBackground::drawBackground(juce::Rectangle<int> container)
{
    // Defining some temp variables to help with dimentions
    auto left = container.getX();
    auto right = container.getRight();
    auto top = container.getY();
    auto bottom = container.getBottom();
    auto width = container.getWidth();
    auto height = container.getHeight();

    // Creating a background image to draw on
    background = juce::Image(juce::Image::ARGB, width, height, true);
    auto g = juce::Graphics(background);
    g.setFont(fontHeight);
    
    // Setting the background colour
    g.setColour(findColour(backgroundColourId));
    g.fillAll(findColour(backgroundColourId));

    /* ============================================== */

    // Drwaing all horizontal lines
    
    // Setting the gradient to start at the top and end at the bottom
    _colourGradient.point1 = juce::Point<float>(static_cast<float>(width / 2), static_cast<float>(top));
    _colourGradient.point2 = juce::Point<float>(static_cast<float>(width / 2), static_cast<float>(bottom));

    // Itterating through each frequency tick
    for (auto i = 0; i < _freqs.size(); ++i)
    {
        auto freq = _freqs[i];
        auto x = _logFreqs[i];
        
        // Applying the gradient fill to the line
        g.setGradientFill(_colourGradient);
        g.drawVerticalLine(static_cast<int>(x), static_cast<float>(top), static_cast<float>(bottom));

        // Reformatting the string to a shortened version i.e. 10kHz
        juce::String str = (freq > 999.f) ? juce::String(freq / 1000.f) + "k" : juce::String(freq);
        str << "Hz";
        
        // Finding the text width and height to center the text at the tick point
        auto textWidth = g.getCurrentFont().getStringWidth(str);

        juce::Rectangle<int> r;

        r.setSize(textWidth, fontHeight);
        r.setTop(top);
        r.setX(x-(textWidth/2));
        
        // Setting the colour of the text / label
        g.setColour(findColour(labelColourId));
        g.drawFittedText(str, r, juce::Justification::centred, 1);
    }

    /* ============================================== */

    // Drawing all vertical lines

    // Setting the gradient points to start at the left and end at the right
    _colourGradient.point1 = juce::Point<float>(static_cast<float>(left), static_cast<float>(container.getCentreY()));
    _colourGradient.point2 = juce::Point<float>(static_cast<float>(right), static_cast<float>(container.getCentreY()));

    // Itterating through each gain tick
    for (auto i = 0; i < _gains.size(); ++i)
    {
        auto gain = _gains[i];
        auto y = _logGains[i];
        
        // Setting the 0 point line to it's specified colour
        if (gain == 0.f)
        {
            // Apply gain 0 line colour to the line
            g.setColour(findColour(gain0LineColourId));
        } else {
            // Applying the gradient fill to the line
            g.setGradientFill(_colourGradient);
        }
        
        // Drawing the gain line
        g.drawHorizontalLine(static_cast<int>(y), static_cast<float>(left), static_cast<float>(right));
        
        // Setting the label colour
        g.setColour(findColour(labelColourId));

        // Finding the text width and height to center the text at the tick point
        // and reformatting the gain label text applying dB
        juce::String str = (gain > 0) ? "+" : "";
        str << gain << "dB";
        auto textWidth = g.getCurrentFont().getStringWidth(str);
        
        juce::Rectangle<int> r;
        
        r.setSize(textWidth, fontHeight);
        r.setX(getWidth() - textWidth);
        r.setY(static_cast<int>(y)-(fontHeight/2));

        // Setting the colour of the text / label
        g.drawFittedText(str, r, juce::Justification::centredLeft, 1);

        // * Draws gain ticks to the left of the graph
        str.clear();
        str << (gain - _maxGain) << "dB";

        r.setLeft(left);
        textWidth = g.getCurrentFont().getStringWidth(str);
        r.setSize(textWidth, fontHeight);

        g.drawFittedText(str, r, juce::Justification::centredLeft, 1);
    }
}

void GraphBackground::paint(juce::Graphics& g)
{
    // Redrawing the image
    g.drawImage(background, getLocalBounds().toFloat());
}

void GraphBackground::resized()
{
    // Getting the component bounds
    auto bounds = getLocalBounds();

    // Updating the X and Y maps for drawing the lines
    updateXMap(static_cast<float>(bounds.getX()), static_cast<float>(bounds.getRight()));
    updateYMap(static_cast<float>(bounds.getBottom()), static_cast<float>(bounds.getY()));

    // Redraw the background image
    drawBackground(bounds);
}
