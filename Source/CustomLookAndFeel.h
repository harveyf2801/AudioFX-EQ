/*
  ==============================================================================

    CustomLookAndFeel.h
    Created: 30 Nov 2023 4:28:05pm
    Author:  Harvey Fretwell

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================

class CustomLookAndFeel : public juce::LookAndFeel_V4
{
public:
    //==============================================================================
    
    // Constructor / Destructor
    CustomLookAndFeel();
    virtual ~CustomLookAndFeel();

    // Draws a rotary slider
	virtual void drawRotarySlider(juce::Graphics& g,
                                  int x, int y,
                                  int width, int height,
                                  float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                                  juce::Slider& slider);
    
    // Draws the lozenge-shaped background for a standard button
    virtual void drawButtonBackground(juce::Graphics& g,
                                      juce::Button& button,
                                      const juce::Colour& backgroundColour,
                                      bool isMouseOverButton, bool isButtonDown);


    // Draws the contents of a standard ToggleButton
    virtual void drawToggleButton(juce::Graphics& g,
                                  juce::ToggleButton& button,
                                  bool isMouseOverButton, bool isButtonDown);
    
    // Draws a tick box
    virtual void drawTickBox(juce::Graphics& g,
                             juce::Component& component,
                             float x, float y, float w, float h,
                             bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown);

    //==============================================================================
    
    // Draws a progress bar
//    virtual void drawProgressBar(juce::Graphics& g,
//                                 juce::ProgressBar& progressBar,
//                                 int width, int height,
//                                 double progress,
//                                 const juce::String& textToShow);

    //==============================================================================
    
    // Draws a scroll bar button / handle
    virtual void drawScrollbarButton(juce::Graphics& g,
                                     juce::ScrollBar& scrollbar,
                                     int width, int height,
                                     int buttonDirection,
                                     bool isScrollbarVertical, bool isMouseOverButton, bool isButtonDown);
    
    // Draws a scroll bar
    virtual void drawScrollbar(juce::Graphics& g,
                               juce::ScrollBar& scrollbar,
                               int x, int y, int width, int height,
                               bool isScrollbarVertical,
                               int thumbStartPosition, int thumbSize,
                               bool isMouseOver, bool isMouseDown);

    virtual juce::ImageEffectFilter* getScrollbarEffect();

    //==============================================================================
    
    // Draws the outline around a text edit
    virtual void drawTextEditorOutline(juce::Graphics& g,
                                       int width, int height,
                                       juce::TextEditor& textEditor);

    //==============================================================================
    
    // Fills the background of a popup menu component
    virtual void drawPopupMenuBackground(juce::Graphics& g,
                                         int width, int height);
    
    // Fills the background of a popup menu component
    virtual void drawMenuBarBackground(juce::Graphics& g,
                                       int width, int height,
                                       bool isMouseOverBar,
                                       juce::MenuBarComponent& menuBar);

    //==============================================================================
    
    // Draw a combo box
    virtual void drawComboBox(juce::Graphics& g,
                              int width, int height,
                              bool isButtonDown,
                              int buttonX, int buttonY, int buttonW, int buttonH,
                              juce::ComboBox& box);

    virtual juce::Font getComboBoxFont (juce::ComboBox& box);

    //==============================================================================
    
    // Draws a linear slider
    virtual void drawLinearSlider(juce::Graphics& g,
                                  int x, int y, int width, int height,
                                  float sliderPos, float minSliderPos, float maxSliderPos,
                                  const juce::Slider::SliderStyle style,
                                  juce::Slider& slider);

    virtual int getSliderThumbRadius(juce::Slider& slider);
    
    // Draws the slider thumb/handle/button
    virtual juce::Button* createSliderButton(bool isIncrement);

    virtual juce::ImageEffectFilter* getSliderEffect();

    //==============================================================================
    
    // Draws a corener resizer
    virtual void drawCornerResizer(juce::Graphics& g,
                                   int w, int h,
                                   bool isMouseOver, bool isMouseDragging);

    // Draws a document window button
    virtual juce::Button* createDocumentWindowButton(int buttonType);

    // Configures the document window button positions
    virtual void positionDocumentWindowButtons(juce::DocumentWindow& window,
                                               int titleBarX, int titleBarY, int titleBarW, int titleBarH,
                                               juce::Button* minimiseButton, juce::Button* maximiseButton, juce::Button* closeButton,
                                               bool positionTitleBarButtonsOnLeft);


private:
    
    juce::DropShadowEffect scrollbarShadow;
    
    //==============================================================================

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomLookAndFeel);
};
