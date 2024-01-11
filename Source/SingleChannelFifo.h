/*
  ==============================================================================

    SingleChannelFifo.h
    Created: 15 Dec 2023 7:55:31am
    Author:  Harvey

    Reference:
    [SimpleEQ - Yashita Namdeo](https://github.com/yashitanamdeo/SimpleEQ/tree/main)

  ==============================================================================
*/

#pragma once
#include "JuceHeader.h"
#include "FIFO.h"

// Enum to represent the channel (Right or Left)
enum Channel
{
    Right, // 0
    Left   // 1
};

template<typename BlockType>
struct SingleChannelFifo
{
    // Constructor that takes a channel enum as a parameter
    SingleChannelFifo(Channel ch) : channelToUse(ch)
    {
        prepared.set(false);
    }

    // Method to update the FIFO with a new block of samples
    void update(const BlockType& buffer)
    {
        // Assertion checks to ensure proper usage
        jassert(prepared.get());
        jassert(buffer.getNumChannels() > channelToUse);

        // Get a pointer to the specified channel in the input buffer
        auto* channelPtr = buffer.getReadPointer(channelToUse);

        // Push each sample from the channel into the FIFO
        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {
            pushNextSampleIntoFifo(channelPtr[i]);
        }
    }

    // Method to prepare the FIFO for a given buffer size
    void prepare(int bufferSize)
    {
        prepared.set(false);
        size.set(bufferSize);

        // Set up the bufferToFill with the specified channel and size
        bufferToFill.setSize(1,             // channel
            bufferSize,    // num samples
            false,         // keepExistingContent
            true,          // clear extra space
            true);         // avoid reallocating

        // Prepare the audioBufferFifo with the specified channel and size
        audioBufferFifo.prepare(1, bufferSize);

        // Reset FIFO index and mark as prepared
        fifoIndex = 0;
        prepared.set(true);
    }

    //==============================================================================
    // Getter methods

    // Get the number of complete buffers available in the FIFO
    int getNumCompleteBuffersAvailable() const { return audioBufferFifo.getNumAvailableForReading(); }

    // Check if the FIFO is prepared
    bool isPrepared() const { return prepared.get(); }

    // Get the size of the FIFO
    int getSize() const { return size.get(); }

    //==============================================================================
    // Method to retrieve an audio buffer from the FIFO
    bool getAudioBuffer(BlockType& buf) { return audioBufferFifo.pull(buf); }

private:
    // Member variables

    // Enum representing the channel to use
    Channel channelToUse;

    // Index for FIFO operations
    int fifoIndex = 0;

    // FIFO for storing audio buffers
    FIFO<BlockType> audioBufferFifo;

    // Buffer used to fill the FIFO
    BlockType bufferToFill;

    // Atomic flag to indicate whether the FIFO is prepared
    juce::Atomic<bool> prepared = false;

    // Atomic variable to store the size of the FIFO
    juce::Atomic<int> size = 0;

    // Method to push the next sample into the FIFO
    void pushNextSampleIntoFifo(float sample)
    {
        // Check if the current buffer is full
        if (fifoIndex == bufferToFill.getNumSamples())
        {
            // Push the filled buffer into the FIFO
            auto ok = audioBufferFifo.push(bufferToFill);

            // Ignore the unused variable
            juce::ignoreUnused(ok);

            // Reset FIFO index
            fifoIndex = 0;
        }

        // Set the sample in the bufferToFill
        bufferToFill.setSample(0, fifoIndex, sample);

        // Increment FIFO index
        ++fifoIndex;
    }
};