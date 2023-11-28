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
        PluginEditor.cpp
        PluginProcessor.cpp
        EQProcessor.cpp
        FFTProcessor.cpp
        FIFO.cpp
        CutBandParameters.cpp
        PeakBandParameters.cpp
        SpectralAnalyser.cpp
        LabelledChoiceSlider.cpp
        LabelledSlider.cpp
        # source/PluginEditor.cpp
        # source/PluginProcessor.cpp
        # source/Processing/EQProcessor.cpp
        # source/Processing/FFTProcessor.cpp
        # source/Processing/FIFO.cpp
        # source/GUI/EQComponents/CutBandParameters.cpp
        # source/GUI/EQComponents/PeakBandParameters.cpp
        # source/GUI/EQComponents/SpectralAnalyser.cpp
        # source/GUI/Components/LabelledChoiceSlider.cpp
        # source/GUI/Components/LabelledSlider.cpp
)

# target_include_directories(${PROJECT_NAME}
#     PRIVATE
#         source
#         source/GUI
#         source/GUI/Components
#         source/GUI/EQComponents
#         source/Processing
# )

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
