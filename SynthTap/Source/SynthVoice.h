/*
  ==============================================================================

    SynthVoice.h
    Created: 13 Apr 2021 11:31:33pm
    Author:  gklch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

// Custom includes
#include "SynthSound.h"

class SynthVoice
  : public juce::SynthesiserVoice
{
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void pitchWheelMoved(int newPitchWheelValue) override;
};