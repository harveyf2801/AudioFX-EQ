/*
  ==============================================================================

    FIFO.h
    Created: 27 Apr 2023 3:46:29pm
    Author:  Harvey

    Reference:
    [SimpleEQ - Yashita Namdeo](https://github.com/yashitanamdeo/SimpleEQ/tree/main)

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

#include <array>

// Template structure representing a First In, First Out (FIFO) buffer
template<typename T>
struct FIFO
{
    // Method to prepare the FIFO for holding juce::AudioBuffer<float>
    void prepare(int numChannels, int numSamples)
    {
        // Ensure the type T is juce::AudioBuffer<float>
        static_assert(std::is_same_v<T, juce::AudioBuffer<float>>,
            "prepare(numChannels, numSamples) should only be used when the Fifo is holding juce::AudioBuffer<float>");

        // Loop through each buffer in the array and set its size
        for (auto& buffer : buffers)
        {
            buffer.setSize(numChannels,
                numSamples,
                false,   // clear everything?
                true,    // including the extra space?
                true);   // avoid reallocating if you can?
            buffer.clear();
        }
    }

    // Method to prepare the FIFO for holding std::vector<float>
    void prepare(size_t numElements)
    {
        // Ensure the type T is std::vector<float>
        static_assert(std::is_same_v<T, std::vector<float>>,
            "prepare(numElements) should only be used when the Fifo is holding std::vector<float>");

        // Loop through each buffer in the array and set its size
        for (auto& buffer : buffers)
        {
            buffer.clear();
            buffer.resize(numElements, 0);
        }
    }

    // Method to push an element into the FIFO
    bool push(const T& t)
    {
        // Obtain a write pointer to the FIFO
        auto write = fifo.write(1);

        // Check if there is space in the FIFO
        if (write.blockSize1 > 0)
        {
            // Copy the element into the FIFO
            buffers[write.startIndex1] = t;
            return true;
        }

        return false;
    }

    // Method to pull an element from the FIFO
    bool pull(T& t)
    {
        // Obtain a read pointer from the FIFO
        auto read = fifo.read(1);

        // Check if there is an element available in the FIFO
        if (read.blockSize1 > 0)
        {
            // Copy the element from the FIFO
            t = buffers[read.startIndex1];
            return true;
        }

        return false;
    }

    // Get the number of elements available for reading in the FIFO
    int getNumAvailableForReading() const
    {
        return fifo.getNumReady();
    }

private:
    // Constants

    // Capacity of the FIFO
    static constexpr int Capacity = 30;

    // Member variables

    // Array of buffers to store elements
    std::array<T, Capacity> buffers;

    // AbstractFifo to manage read and write operations
    juce::AbstractFifo fifo{ Capacity };
};