/*
  ==============================================================================

    FIFO.cpp
    Created: 27 Apr 2023 3:46:29pm
    Author:  Harvey

  ==============================================================================
*/

#include "FIFO.h"

void Fifo::prepare(int numChannels, int numSamples)
{
    for( auto& buffer : buffers)
    {
        buffer.setSize(numChannels,
                        numSamples,
                        false,   // clear everything
                        true,    // remove extra space
                        true);   // avoid reallocating
        buffer.clear();
    }
}
    
bool Fifo::push(const juce::AudioBuffer<float>& buffer)
{
    auto writeHandle = fifo.write(1);
    if(writeHandle.blockSize1 > 0)
    {
        buffers[writeHandle.startIndex1] = buffer;
        return true;
    }
        
    return false;
}
    
bool Fifo::pull(juce::AudioBuffer<float>& buffer)
{
    auto readHandle = fifo.read(1);
    if(readHandle.blockSize1 > 0)
    {
        buffer = buffers[readHandle.startIndex1];
        return true;
    }
        
    return false;
}
    
int Fifo::getNumAvailableForReading() const
{
    return fifo.getNumReady();
}