/*
  ==============================================================================

    SynthTap.h
    Created: 13 Apr 2021 11:31:26pm
    Author:  gklch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound
  : public juce::SynthesiserSound
{
public: 
    bool appliesToNote(int midiNoteNumber) override
    {
        return true;
    };

    bool appliesToChannel(int midiChannel) override
    {
        return true;
    };
};