/*
  ==============================================================================

    AnalyserPathGenerator.h
    Created: 15 Dec 2023 8:08:53am
    Author:  Harvey

    Reference:
    [SimpleEQ - Yashita Namdeo](https://github.com/yashitanamdeo/SimpleEQ/tree/main)

  ==============================================================================
*/

#pragma once

#include "JuceHeader.h"
#include "FIFO.h"

template<typename PathType>
struct AnalyserPathGenerator
{
    // This struct converts 'renderData[]' into a juce::Path

    void generatePath(const std::vector<float>& renderData,
        juce::Rectangle<float> fftBounds,
        int fftSize,
        float binWidth,
        float negativeInfinity)
    {
        // Extracting bounds information as temp variables (this will be the graph's innerContainer)
        auto top = fftBounds.getY();
        auto bottom = fftBounds.getHeight();
        auto width = fftBounds.getWidth();

        // Calculating the number of bins in the FFT
        int numBins = (int)fftSize / 2;

        // Creating a PathType object to store the path
        PathType p;
        p.preallocateSpace(3 * (int)fftBounds.getWidth()); // Preallocating space for efficiency

        // Mapping function to convert values to the vertical position in the graph using a lambda function
        auto map = [bottom, top, negativeInfinity](float v)
            {
                return juce::jmap(v,
                    negativeInfinity, 0.f,
                    float(bottom + 10), top);
            };

        // Starting the path with the first data point
        auto y = map(renderData[0]);

        // Handling NaN and infinity values
        if (std::isnan(y) || std::isinf(y))
            y = bottom;

        p.startNewSubPath(0, y);

        const int pathResolution = 2; // You can draw line-to's every 'pathResolution' pixels.

        // Looping through bins to create the path
        for (int binNum = 1; binNum < numBins; binNum += pathResolution)
        {
            y = map(renderData[binNum]);

            // Handling NaN and infinity values
            if (!std::isnan(y) && !std::isinf(y))
            {
                // Mapping the frequency to the horizontal position in the graph
                auto binFreq = binNum * binWidth;
                auto normalizedBinX = juce::mapFromLog10(binFreq, 20.f, 20000.f);
                int binX = std::floor(normalizedBinX * width);

                // Adding a line-to point to the path
                p.lineTo(binX, y);
            }
        }

        // Pushing the generated path into the FIFO
        pathFifo.push(p);
    }

    // Get the number of paths available in the FIFO
    int getNumPathsAvailable() const
    {
        return pathFifo.getNumAvailableForReading();
    }

    // Get a path from the FIFO
    bool getPath(PathType& path)
    {
        return pathFifo.pull(path);
    }

private:
    FIFO<PathType> pathFifo; // FIFO (First In, First Out) container for storing paths
};