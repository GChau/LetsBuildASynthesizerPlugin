# LetsBuildASynthesizerPlugin
My second JUCE audio plugin. 

Following a YouTube series to build a Synthesizer plugin and learn how to use JUCE.

I used Reaper to pick up my VST3 plugin.

# Build Environment
* Visual Studio 2019
* Reaper

# Build Steps
1. Download JUCE (see below for link).
2. Run Projucer.
3. Set path to JUCE modules.
4. Set target plugin format.
5. Create project.
6. Compile in Release mode.
7. Use an IDE to scan your build directory.
8. Have fun.

Source: 
* Download - https://juce.com/get-juce/download
* Obscure issue with updating VS to 16.9.4 - https://forum.juce.com/t/ms-visual-studio-16-9-4-compile-failed-after-vs-update/45555
    * Resolution is to just build develop branch of Producer to generate correct project config.
* Lessons
    * Part 2 - https://youtu.be/AfrAWH5i-pQ
    * Part 1 - https://youtu.be/nQR-wtzsRhA
    * Part 0 - https://youtu.be/ADG6Rsd3ekg