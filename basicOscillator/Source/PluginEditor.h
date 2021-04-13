/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class BasicOscillatorAudioProcessorEditor
  : public juce::AudioProcessorEditor,
    public juce::Slider::Listener
{
public:
    BasicOscillatorAudioProcessorEditor (BasicOscillatorAudioProcessor&);
    ~BasicOscillatorAudioProcessorEditor() override;

    //==============================================================================
    void sliderValueChanged(juce::Slider*) override;
    //void sliderDragStarted(juce::Slider*) override;
    //void sliderDragEnded(juce::Slider*) override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    BasicOscillatorAudioProcessor& audioProcessor;

    juce::Slider active_oscillator_slider_;
    juce::Slider oscillator_slider_;
    juce::Slider gain_slider_;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BasicOscillatorAudioProcessorEditor)
};
