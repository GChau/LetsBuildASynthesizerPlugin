/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <algorithm>

static const int WIDTH = 666;
static const int HEIGHT = 666;

//==============================================================================
BasicOscillatorAudioProcessorEditor::BasicOscillatorAudioProcessorEditor(
    BasicOscillatorAudioProcessor& p)
  : AudioProcessorEditor(&p),
    audioProcessor (p)
{
    setSize(WIDTH, HEIGHT);
    setResizable(true, true);

    // Set up sliders
    active_oscillator_slider_.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    active_oscillator_slider_.setRange(0.0, 2.0, 1.0);
    active_oscillator_slider_.setValue(0.0);
    active_oscillator_slider_.setTextBoxStyle(
        juce::Slider::TextBoxBelow,
        true,
        WIDTH * 0.5f,
        32
    );
    active_oscillator_slider_.addListener(this);

    oscillator_slider_.setSliderStyle(juce::Slider::SliderStyle::LinearBar);
    oscillator_slider_.setRange(1.f, 666.f, 1.f);
    oscillator_slider_.setValue(220.f);
    oscillator_slider_.setTextBoxStyle(
        juce::Slider::TextBoxBelow,
        true,
        WIDTH * 0.5f,
        32
    );
    oscillator_slider_.addListener(this);

    gain_slider_.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    gain_slider_.setRange(0.f, 1.0f, 0.01f);
    gain_slider_.setValue(0.01f);
    gain_slider_.setTextBoxStyle(
        juce::Slider::TextBoxBelow,
        true,
        WIDTH * 0.5f,
        32
    );
    gain_slider_.addListener(this);

    // Add sliders to plugin
    addAndMakeVisible(active_oscillator_slider_);
    addAndMakeVisible(oscillator_slider_);
    addAndMakeVisible(gain_slider_);
}

BasicOscillatorAudioProcessorEditor::~BasicOscillatorAudioProcessorEditor()
{
}

//==============================================================================

void BasicOscillatorAudioProcessorEditor::sliderValueChanged(
    juce::Slider* slider
) {
    if (slider == &active_oscillator_slider_) {
        audioProcessor.active_oscillator_ = (OscillatorType)((int)active_oscillator_slider_.getValue());
    }

    if (slider == &oscillator_slider_) {
        audioProcessor.oscillators_[audioProcessor.active_oscillator_]->setFrequency(oscillator_slider_.getValue());
    }

    if (slider == &gain_slider_) {
        audioProcessor.gain_.setGainLinear(gain_slider_.getValue());
    }

    // If the slider changes value, repaint
    repaint();
}

//==============================================================================
void BasicOscillatorAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Background Colour is ratio of the frequency
    const float freq = oscillator_slider_.getValue();
    const float ratio = freq / (oscillator_slider_.getMaximum() - oscillator_slider_.getMinimum());
    const unsigned char ratio_255 = (unsigned char)(ratio * 255.f);
    unsigned int colour = 0xff00a600;
    colour |= ((unsigned int)ratio_255 << 16);
    g.fillAll(juce::Colour(colour));

    g.setColour(juce::Colour(0xff001eff));

    // Make font stretch or compress if window gets resized
    const float x_ratio = ((float)getWidth() / WIDTH);
    const float y_ratio = ((float)getHeight() / HEIGHT);
    const float min_ratio = std::min(x_ratio, y_ratio);

    const auto font_size = 69.0f * min_ratio;
    g.setFont(font_size);
    g.drawFittedText("max 666 oscillation!!", getLocalBounds(), juce::Justification::centredTop, 1);
    g.drawFittedText("oscillator freq B)", getLocalBounds(), juce::Justification::centredBottom, 1);
}

void BasicOscillatorAudioProcessorEditor::resized()
{
    gain_slider_.setBounds(
        (float)getWidth() * 0.25f,
        (float)getHeight() * 0.25f,
        (float)getWidth() * 0.5f,
        (float)getHeight() * 0.125f
    );

    oscillator_slider_.setBounds(
        (float)getWidth() * 0.25f,
        (float)getHeight() * 0.5f,
        (float)getWidth() * 0.5f,
        (float)getHeight()* 0.125f
    );

    active_oscillator_slider_.setBounds(
        (float)getWidth() * 0.25f,
        (float)getHeight() * 0.65f,
        (float)getWidth() * 0.5f,
        (float)getHeight() * 0.125f
    );
}
