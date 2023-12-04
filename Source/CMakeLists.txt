# https://github.com/juce-framework/JUCE/blob/master/docs/CMake%20API.md

# EQ CMakeLists.txt

# Builds to VST3: 
#                   /AudioFX-EQ\build\plugin\EQ_artefacts\Debug\VST3\EQ.vst3\Contents\x86_64-win\EQ.vst3
# and Standalone:
#                   /AudioFX-EQ\build\plugin\EQ_artefacts\Debug\Standalone\EQ.exe

# Set CMake version
cmake_minimum_required(VERSION 3.22)

# Name and version of the project
project(EQ VERSION 0.1.0)

juce_add_plugin(${PROJECT_NAME}
    COMPANY_NAME HarveyFretwell
    PRODUCT_NAME "EQ"
    COMPANY_WEBSITE "https://harveyf2801.github.io/portfolio/"
    COMPANY_EMAIL "hgfretwell@gmail.com"
    PLUGIN_MANUFACTURER_CODE HFAP
    PLUGIN_CODE EQAP
    DESCRIPTION Equaliser
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT FALSE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    FORMATS VST3 Standalone
    # USE GLOBAL APPCIN HEADER FALSE
    # USE NAMESPACE JUCE FALSE
)

juce_generate_juce_header(EQ)

target_sources(${PROJECT_NAME}
    PRIVATE
        CustomLookAndFeel.cpp
        CutBandParameters.cpp
        EQProcessor.cpp
        FFTProcessor.cpp
        FIFO.cpp
        GraphBackground.cpp
        LabelledChoiceSlider.cpp
        LabelledSlider.cpp
        LowCutBand.cpp
        PeakBandParameters.cpp
        PluginEditor.cpp
        PluginProcessor.cpp
        ShelfBandParameters.cpp
        TDF2Biquad.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        juce::juce_audio_basics
        juce::juce_audio_devices
        juce::juce_audio_formats
        juce::juce_audio_plugin_client
        juce::juce_audio_processors
        juce::juce_audio_utils
        juce::juce_core
        juce::juce_data_structures
        juce::juce_dsp
        juce::juce_events
        juce::juce_graphics
        juce::juce_gui_basics
        juce::juce_gui_extra
    PUBLIC
        juce::juce_recommended_config_flags
        juce::juce_recommended_lto_flags
        juce::juce_recommended_warning_flags
)

target_compile_definitions(${PROJECT_NAME}
    PUBLIC
        JUCE_DISPLAY_SPLASH_SCREEN=0 # need lisence for this !!!
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_VST3_CAN_REPLACE_VST2=0
)

if(MSVC)
    target_compile_definitions(${PROJECT_NAME}
        PRIVATE
           _SILENCE_CXX23_ALIGNED_STORAGE_DEPRECATION_WARNING
    )
endif()
