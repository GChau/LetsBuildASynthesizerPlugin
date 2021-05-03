/*
  ==============================================================================

    SynthVoice.h
    Created: 13 Apr 2021 11:31:33pm
    Author:  gklch

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <memory>
#include <unordered_map>

// Custom includes
#include "SynthSound.h"

enum class OscillatorType {
    SINE_E = 0,
    SAW_E,
    SQUARE_E
};

class SynthVoice
  : public juce::SynthesiserVoice
{
public:
    bool canPlaySound(juce::SynthesiserSound* sound) override;
    void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
    void stopNote(float velocity, bool allowTailOff) override;
    void controllerMoved(int controllerNumber, int newControllerValue) override;
    void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples) override;
    void pitchWheelMoved(int newPitchWheelValue) override;

private:
    // ADSR - Attack Decay Sustain Release
    juce::ADSR adsr_;
    juce::ADSR::Parameters adsr_parameters_;

    // Oscillator
    // Sine, Saw and Square
    std::unordered_map<OscillatorType, std::shared_ptr<juce::dsp::Oscillator<float>>> oscillators_;
    OscillatorType active_oscillator_;

    // Gain
    juce::dsp::Gain<float> gain_;

    bool is_prepared_{ false };
};