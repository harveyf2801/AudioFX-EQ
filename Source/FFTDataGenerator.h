/*
  ==============================================================================

    FFTDataGenerator.h
    Created: 15 Dec 2023 8:07:19am
    Author:  Harvey

    Reference:
    [SimpleEQ - Yashita Namdeo](https://github.com/yashitanamdeo/SimpleEQ/tree/main)

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "FIFO.h"

// Enum to represent FFT orders
enum FFTOrder
{
    order2048 = 11,
    order4096 = 12,
    order8192 = 13
};

template<typename BlockType>
struct FFTDataGenerator
{
    // Method to produce FFT data from an audio buffer for rendering
    void produceFFTDataForRendering(const juce::AudioBuffer<float>& audioData, const float negativeInfinity)
    {
        const auto fftSize = getFFTSize();

        // Clear and copy audio data into fftData
        fftData.assign(fftData.size(), 0);
        auto* readIndex = audioData.getReadPointer(0);
        std::copy(readIndex, readIndex + fftSize, fftData.begin());

        // Apply windowing function to the data
        window->multiplyWithWindowingTable(fftData.data(), fftSize);       // [1]

        // Perform forward FFT on the data
        forwardFFT->performFrequencyOnlyForwardTransform(fftData.data());  // [2]

        int numBins = (int)fftSize / 2;

        // Normalize the FFT values
        for (int i = 0; i < numBins; ++i)
        {
            auto v = fftData[i];
            if (!std::isinf(v) && !std::isnan(v))
            {
                v /= float(numBins);
            }
            else
            {
                v = 0.f;
            }
            fftData[i] = v;
        }

        // Convert FFT values to decibels
        for (int i = 0; i < numBins; ++i)
        {
            fftData[i] = juce::Decibels::gainToDecibels(fftData[i], negativeInfinity);
        }

        // Push the processed FFT data into the FIFO
        fftDataFifo.push(fftData);
    }

    // Method to change the FFT order
    void changeOrder(FFTOrder newOrder)
    {
        // When order changes, recreate window, forwardFFT, fifo, and fftData
        // Reset fifoIndex

        order = newOrder;
        auto fftSize = getFFTSize();

        // Recreate window and forwardFFT on the heap
        forwardFFT = std::make_unique<juce::dsp::FFT>(order);
        window = std::make_unique<juce::dsp::WindowingFunction<float>>(fftSize, juce::dsp::WindowingFunction<float>::blackmanHarris);

        // Clear and resize fftData
        fftData.clear();
        fftData.resize(fftSize * 2, 0);

        // Prepare fftDataFifo with the new size
        fftDataFifo.prepare(fftData.size());
    }

    //==============================================================================
    // Getter methods

    // Get the FFT size
    int getFFTSize() const { return 1 << order; }

    // Get the number of available FFT data blocks in the FIFO
    int getNumAvailableFFTDataBlocks() const { return fftDataFifo.getNumAvailableForReading(); }

    //==============================================================================
    // Method to retrieve FFT data from the FIFO
    bool getFFTData(BlockType& fftData) { return fftDataFifo.pull(fftData); }

private:
    // Member variables

    // FFT order
    FFTOrder order;

    // Block for storing FFT data
    BlockType fftData;

    // Unique pointers for FFT and window functions
    std::unique_ptr<juce::dsp::FFT> forwardFFT;
    std::unique_ptr<juce::dsp::WindowingFunction<float>> window;

    // FIFO for storing FFT data
    FIFO<BlockType> fftDataFifo;
};