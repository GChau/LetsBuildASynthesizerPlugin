/*
  ==============================================================================

    SynthVoice.cpp
    Created: 13 Apr 2021 11:31:33pm
    Author:  gklch

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound)
{
    return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}

void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
    for (auto& it : oscillators_) {
        it.second->setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
    }
    adsr_.noteOn();
}

void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
    adsr_.noteOff();
}

void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{
}

void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
    juce::dsp::ProcessSpec spec;
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = outputChannels;

    // Sine, Saw and Square
    oscillators_.insert(std::make_pair(OscillatorType::SINE_E, std::make_shared<juce::dsp::Oscillator<float>>([](float x) { return std::sin(x); })));
    oscillators_.insert(std::make_pair(OscillatorType::SAW_E, std::make_shared<juce::dsp::Oscillator<float>>([](float x) { return x / juce::MathConstants<float>::pi; })));
    oscillators_.insert(std::make_pair(OscillatorType::SQUARE_E, std::make_shared<juce::dsp::Oscillator<float>>([](float x) { return x < 0.0f ? -1.f : 1.f; })));

    // Set current 
    active_oscillator_ = OscillatorType::SINE_E;

    // Pass process spec to our dsp
    for (auto& it : oscillators_) {
        it.second->prepare(spec);
        //it.second->setFrequency(220.f);
    }

    // Set Gain
    gain_.prepare(spec);
    gain_.setGainLinear(0.01f);

    // ADSR
    adsr_.setSampleRate(sampleRate);
    adsr_.setParameters(adsr_parameters_);

    is_prepared_ = true;
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer, int startSample, int numSamples)
{
    jassert(is_prepared_);

    // Assign audio block to active occilator
    juce::dsp::AudioBlock<float> audio_block(outputBuffer);
    oscillators_[active_oscillator_]->process(juce::dsp::ProcessContextReplacing<float>(audio_block));

    // Gain
    gain_.process(juce::dsp::ProcessContextReplacing<float>(audio_block));

    // ADSR
    adsr_.applyEnvelopeToBuffer(outputBuffer, startSample, numSamples);
}

void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{
}
