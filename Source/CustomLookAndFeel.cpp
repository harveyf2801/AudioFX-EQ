/*
  ==============================================================================

    CustomLookAndFeel.cpp
    Created: 30 Nov 2023 4:28:05pm
    Author:  Harvey Fretwell

  ==============================================================================
*/

#include "CustomLookAndFeel.h"

//==============================================================================

CustomLookAndFeel::CustomLookAndFeel()
    : juce::LookAndFeel_V4()
{
    setColour(juce::TextButton::buttonColourId, juce::Colours::yellow);
    setColour(juce::ListBox::outlineColourId, findColour (juce::ComboBox::outlineColourId));
    setColour(juce::ScrollBar::thumbColourId, juce::Colour (0xffbbbbdd));
    setColour(juce::ScrollBar::backgroundColourId, juce::Colours::transparentBlack);
    setColour(juce::Slider::thumbColourId, juce::Colours::yellow);
    setColour(juce::Slider::trackColourId, juce::Colour (0x7f000000));
    setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::green);
    setColour(juce::ProgressBar::backgroundColourId, juce::Colours::white.withAlpha (0.6f));
    setColour(juce::ProgressBar::foregroundColourId, juce::Colours::green.withAlpha (0.7f));
    setColour(juce::PopupMenu::backgroundColourId, juce::Colour (0xffeef5f8));
    setColour(juce::PopupMenu::highlightedBackgroundColourId, juce::Colour (0xbfa4c2ce));
    setColour(juce::PopupMenu::highlightedTextColourId, juce::Colours::black);
    setColour(juce::TextEditor::focusedOutlineColourId, findColour (juce::TextButton::buttonColourId));

    scrollbarShadow.setShadowProperties(juce::DropShadow(juce::Colour(200, 0, 0), 2, juce::Point<int>(0, 0)));
}

CustomLookAndFeel::~CustomLookAndFeel()
{
}

void CustomLookAndFeel::drawRotarySlider(juce::Graphics& g,
                                         int x, int y,
                                         int width, int height,
                                         float sliderPosProportional, float rotaryStartAngle, float rotaryEndAngle,
                                         juce::Slider& slider)
{
	// This is the binary image data that uses very little CPU when rotating
	juce::Image myStrip = juce::ImageCache::getFromMemory (BinaryData::knobstrip_png, BinaryData::knobstrip_pngSize);

	/*
	//THIS IS THE LAME VERSION THAT DRAWS FROM A FILE (40-50% CPU)
	File temp(T("C:\\Users\\nrclark\\programming\\Juce-look-and-feel-examples\\Assets\\knobman\\knobstrip.png"));
	Image myStrip = ImageFileFormat::loadFrom(temp);
	*/
	
	const double fractRotation = (slider.getValue() - slider.getMinimum())  /   (slider.getMaximum() - slider.getMinimum()); //value between 0 and 1 for current amount of rotation
	const int nFrames = myStrip.getHeight()/myStrip.getWidth(); // number of frames for vertical film strip
	const int frameIdx = (int)ceil(fractRotation * ((double)nFrames-1.0) ); // current index from 0 --> nFrames-1

	const float radius = juce::jmin (width / 2.0f, height / 2.0f) ;
    const float centreX = x + width * 0.5f;
    const float centreY = y + height * 0.5f;
    const float rx = centreX - radius - 1.0f;
    const float ry = centreY - radius - 1.0f;

	g.drawImage(myStrip,
				(int)rx,
                (int)ry,
                2*(int)radius,
                2*(int)radius,   //Dest
				0,
                frameIdx*myStrip.getWidth(),
                myStrip.getWidth(),
                myStrip.getWidth()); //Source

}
									 
void CustomLookAndFeel::drawButtonBackground(juce::Graphics& g,
                                             juce::Button& button,
                                             const juce::Colour& backgroundColour,
                                             bool isMouseOverButton, bool isButtonDown)
{
    const int width = button.getWidth();
    const int height = button.getHeight();

    const float indent = 2.0f;
    const int cornerSize = juce::jmin (juce::roundToInt (width * 0.4f),
                                       juce::roundToInt (height * 0.4f));

    juce::Path p;
    p.addRoundedRectangle (indent, indent,
                           width - indent * 2.0f,
                           height - indent * 2.0f,
                           (float) cornerSize);

    juce::Colour bc (backgroundColour.withMultipliedSaturation (0.3f));

    if (isMouseOverButton)
    {
        if (isButtonDown)
            bc = bc.brighter();
        else if (bc.getBrightness() > 0.5f)
            bc = bc.darker (0.1f);
        else
            bc = bc.brighter (0.1f);
    }

    g.setColour (bc);
    g.fillPath (p);

    g.setColour (bc.contrasting().withAlpha ((isMouseOverButton) ? 0.6f : 0.4f));
    g.strokePath (p, juce::PathStrokeType ((isMouseOverButton) ? 2.0f : 1.4f));
}

void CustomLookAndFeel::drawToggleButton(juce::Graphics& g,
                                         juce::ToggleButton& button,
                                         bool isMouseOverButton, bool isButtonDown)
{
    if (button.hasKeyboardFocus (true))
    {
        g.setColour (button.findColour (juce::TextEditor::focusedOutlineColourId));
        g.drawRect (0, 0, button.getWidth(), button.getHeight());
    }

    const int tickWidth = juce::jmin (20, button.getHeight() - 4);

    drawTickBox (g, button, 4.0f, (button.getHeight() - tickWidth) * 0.5f,
                 (float) tickWidth, (float) tickWidth,
                 button.getToggleState(),
                 button.isEnabled(),
                 isMouseOverButton,
                 isButtonDown);

    g.setColour (button.findColour (juce::ToggleButton::textColourId));
    g.setFont (juce::jmin (15.0f, button.getHeight() * 0.6f));

    if (! button.isEnabled())
        g.setOpacity (0.5f);

    const int textX = tickWidth + 5;

    g.drawFittedText (button.getButtonText(),
                      textX, 4,
                      button.getWidth() - textX - 2, button.getHeight() - 8,
                      juce::Justification::centredLeft, 10);
}

void CustomLookAndFeel::drawTickBox(juce::Graphics& g,
                                    juce::Component& component,
                                    float x, float y, float w, float h,
                                    bool ticked, bool isEnabled, bool isMouseOverButton, bool isButtonDown)
{
    juce::Path box;
    box.addRoundedRectangle (0.0f, 2.0f, 6.0f, 6.0f, 1.0f);

    g.setColour (isEnabled ? juce::Colours::blue.withAlpha (isButtonDown ? 0.3f : 0.1f)
                           : juce::Colours::lightgrey.withAlpha (0.1f));

    juce::AffineTransform trans (juce::AffineTransform::scale (w / 9.0f, h / 9.0f).translated (x, y));

    g.fillPath (box, trans);

    g.setColour (juce::Colours::black.withAlpha (0.6f));
    g.strokePath (box, juce::PathStrokeType (0.9f), trans);

    if (ticked)
    {
        juce::Path tick;
        tick.startNewSubPath (1.5f, 3.0f);
        tick.lineTo (3.0f, 6.0f);
        tick.lineTo (6.0f, 0.0f);

        g.setColour (isEnabled ? juce::Colours::black : juce::Colours::grey);
        g.strokePath (tick, juce::PathStrokeType (2.5f), trans);
    }
}

//void CustomLookAndFeel::drawProgressBar(juce::Graphics& g,
//                                        juce::ProgressBar& progressBar,
//                                        int width, int height,
//                                        double progress,
//                                        const juce::String& textToShow)
//{
//    if (progress < 0 || progress >= 1.0)
//    {
//        juce::LookAndFeel::drawProgressBar (g, progressBar, width, height, progress, textToShow);
//    }
//    else
//    {
//        const juce::Colour background (progressBar.findColour (juce::ProgressBar::backgroundColourId));
//        const juce::Colour foreground (progressBar.findColour (juce::ProgressBar::foregroundColourId));
//
//        g.fillAll (background);
//        g.setColour (foreground);
//
//        g.fillRect (1, 1,
//                    juce::jlimit (0, width - 2, juce::roundToInt (progress * (width - 2))),
//                    height - 2);
//
//        if (textToShow.isNotEmpty())
//        {
//            g.setColour (juce::Colour::contrasting (background, foreground));
//            g.setFont (height * 0.6f);
//
//            g.drawText (textToShow, 0, 0, width, height, juce::Justification::centred, false);
//        }
//    }
//}

void CustomLookAndFeel::drawScrollbarButton(juce::Graphics& g,
                                            juce::ScrollBar& scrollbar,
                                            int width, int height,
                                            int buttonDirection,
                                            bool isScrollbarVertical, bool isMouseOverButton, bool isButtonDown)
{
    if (isScrollbarVertical)
        width -= 2;
    else
        height -= 2;

    juce::Path p;

    if (buttonDirection == 0)
        p.addTriangle (width * 0.5f, height * 0.2f,
                       width * 0.1f, height * 0.7f,
                       width * 0.9f, height * 0.7f);
    else if (buttonDirection == 1)
        p.addTriangle (width * 0.8f, height * 0.5f,
                       width * 0.3f, height * 0.1f,
                       width * 0.3f, height * 0.9f);
    else if (buttonDirection == 2)
        p.addTriangle (width * 0.5f, height * 0.8f,
                       width * 0.1f, height * 0.3f,
                       width * 0.9f, height * 0.3f);
    else if (buttonDirection == 3)
        p.addTriangle (width * 0.2f, height * 0.5f,
                       width * 0.7f, height * 0.1f,
                       width * 0.7f, height * 0.9f);

    if (isButtonDown)
        g.setColour (juce::Colours::white);
    else if (isMouseOverButton)
        g.setColour (juce::Colours::white.withAlpha (0.7f));
    else
        g.setColour (scrollbar.findColour (juce::ScrollBar::thumbColourId).withAlpha (0.5f));

    g.fillPath (p);

    g.setColour (juce::Colours::black.withAlpha (0.5f));
    g.strokePath (p, juce::PathStrokeType (0.5f));
}

void CustomLookAndFeel::drawScrollbar(juce::Graphics& g,
                                      juce::ScrollBar& scrollbar,
                                      int x, int y, int width, int height,
                                      bool isScrollbarVertical,
                                      int thumbStartPosition, int thumbSize,
                                      bool isMouseOver, bool isMouseDown)
{
    g.fillAll (scrollbar.findColour (juce::ScrollBar::backgroundColourId));

    g.setColour (scrollbar.findColour (juce::ScrollBar::thumbColourId)
                    .withAlpha ((isMouseOver || isMouseDown) ? 0.4f : 0.15f));

    if (thumbSize > 0.0f)
    {
        juce::Rectangle<int> thumb;

        if (isScrollbarVertical)
        {
            width -= 2;
            g.fillRect (x + juce::roundToInt (width * 0.35f), y,
                        juce::roundToInt (width * 0.3f), height);

            thumb.setBounds (x + 1, thumbStartPosition,
                             width - 2, thumbSize);
        }
        else
        {
            height -= 2;
            g.fillRect (x, y + juce::roundToInt (height * 0.35f),
                        width, juce::roundToInt (height * 0.3f));

            thumb.setBounds (thumbStartPosition, y + 1,
                             thumbSize, height - 2);
        }

        g.setColour (scrollbar.findColour (juce::ScrollBar::thumbColourId)
                        .withAlpha ((isMouseOver || isMouseDown) ? 0.95f : 0.7f));

        g.fillRect (thumb);

        g.setColour (juce::Colours::black.withAlpha ((isMouseOver || isMouseDown) ? 0.4f : 0.25f));
        g.drawRect (thumb.getX(), thumb.getY(), thumb.getWidth(), thumb.getHeight());

        if (thumbSize > 16)
        {
            for (int i = 3; --i >= 0;)
            {
                const float linePos = thumbStartPosition + thumbSize / 2 + (i - 1) * 4.0f;
                g.setColour (juce::Colours::black.withAlpha (0.15f));

                if (isScrollbarVertical)
                {
                    g.drawLine (x + width * 0.2f, linePos, width * 0.8f, linePos);
                    g.setColour (juce::Colours::white.withAlpha (0.15f));
                    g.drawLine (width * 0.2f, linePos - 1, width * 0.8f, linePos - 1);
                }
                else
                {
                    g.drawLine (linePos, height * 0.2f, linePos, height * 0.8f);
                    g.setColour (juce::Colours::white.withAlpha (0.15f));
                    g.drawLine (linePos - 1, height * 0.2f, linePos - 1, height * 0.8f);
                }
            }
        }
    }
}

juce::ImageEffectFilter* CustomLookAndFeel::getScrollbarEffect()
{
    return &scrollbarShadow;
}

//==============================================================================

void CustomLookAndFeel::drawTextEditorOutline(juce::Graphics& g,
                                              int width, int height,
                                              juce::TextEditor& textEditor)
{
    if (textEditor.isEnabled())
    {
        g.setColour (textEditor.findColour (juce::TextEditor::outlineColourId));
        g.drawRect (0, 0, width, height);
    }
}

//==============================================================================

void CustomLookAndFeel::drawPopupMenuBackground(juce::Graphics& g,
                                                int width, int height)
{
    g.fillAll (findColour (juce::PopupMenu::backgroundColourId));

    g.setColour (juce::Colours::black.withAlpha (0.6f));
    g.drawRect (0, 0, width, height);
}

void CustomLookAndFeel::drawMenuBarBackground(juce::Graphics& g,
                                              int width, int height,
                                              bool isMouseOverBar,
                                              juce::MenuBarComponent& menuBar)
{
    g.fillAll (menuBar.findColour (juce::PopupMenu::backgroundColourId));
}

//==============================================================================

void CustomLookAndFeel::drawComboBox(juce::Graphics& g,
                                     int width, int height,
                                     bool isButtonDown,
                                     int buttonX, int buttonY, int buttonW, int buttonH,
                                     juce::ComboBox& box)
{
    g.fillAll (box.findColour (juce::ComboBox::backgroundColourId));

    g.setColour (box.findColour ((isButtonDown) ? juce::ComboBox::buttonColourId
                                                : juce::ComboBox::backgroundColourId));
    g.fillRect (buttonX, buttonY, buttonW, buttonH);

    g.setColour (box.findColour (juce::ComboBox::outlineColourId));
    g.drawRect (0, 0, width, height);

    const float arrowX = 0.2f;
    const float arrowH = 0.3f;

    if (box.isEnabled())
    {
        juce::Path p;
        p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.45f - arrowH),
                       buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.45f,
                       buttonX + buttonW * arrowX,          buttonY + buttonH * 0.45f);

        p.addTriangle (buttonX + buttonW * 0.5f,            buttonY + buttonH * (0.55f + arrowH),
                       buttonX + buttonW * (1.0f - arrowX), buttonY + buttonH * 0.55f,
                       buttonX + buttonW * arrowX,          buttonY + buttonH * 0.55f);

        g.setColour (box.findColour ((isButtonDown) ? juce::ComboBox::backgroundColourId
                                                    : juce::ComboBox::buttonColourId));
        g.fillPath (p);
    }
}

juce::Font CustomLookAndFeel::getComboBoxFont(juce::ComboBox& box)
{
    juce::Font f (juce::jmin (15.0f, box.getHeight() * 0.85f));
    f.setHorizontalScale (0.9f);
    return f;
}

//==============================================================================

static void drawTriangle(juce::Graphics& g,
                         float x1, float y1, float x2, float y2, float x3, float y3,
                         const juce::Colour& fill, const juce::Colour& outline) noexcept
{
    juce::Path p;
    p.addTriangle (x1, y1, x2, y2, x3, y3);
    g.setColour (fill);
    g.fillPath (p);

    g.setColour (outline);
    g.strokePath (p, juce::PathStrokeType (0.3f));
}

void CustomLookAndFeel::drawLinearSlider(juce::Graphics& g,
                                         int x, int y, int width, int height,
                                         float sliderPos, float minSliderPos, float maxSliderPos,
                                         const juce::Slider::SliderStyle style,
                                         juce::Slider& slider)
{
    g.fillAll (slider.findColour (juce::Slider::backgroundColourId));

    if (style == juce::Slider::LinearBar)
    {
        g.setColour (slider.findColour (juce::Slider::thumbColourId));
        g.fillRect (x, y, (int) sliderPos - x, height);

        g.setColour (slider.findColour (juce::Slider::textBoxTextColourId).withMultipliedAlpha (0.5f));
        g.drawRect (x, y, (int) sliderPos - x, height);
    }
    else
    {
        g.setColour (slider.findColour (juce::Slider::trackColourId)
                           .withMultipliedAlpha (slider.isEnabled() ? 1.0f : 0.3f));

        if (slider.isHorizontal())
        {
            g.fillRect (x, y + juce::roundToInt (height * 0.8f),
                        width, juce::roundToInt (height * 0.2f));
        }
        else
        {
            g.fillRect (x + juce::roundToInt (width * 0.5f - juce::jmin (3.0f, width * 0.1f)), y,
                        juce::jmin (4, juce::roundToInt (width * 0.2f)), height);
        }

        float alpha = 0.35f;

        if (slider.isEnabled())
            alpha = slider.isMouseOverOrDragging() ? 1.0f : 0.7f;

        const juce::Colour fill (slider.findColour (juce::Slider::thumbColourId).withAlpha (alpha));
        const juce::Colour outline (juce::Colours::black.withAlpha (slider.isEnabled() ? 0.7f : 0.35f));

        if (style == juce::Slider::TwoValueVertical || style == juce::Slider::ThreeValueVertical)
        {
            drawTriangle (g, x + width * 0.5f + juce::jmin (4.0f, width * 0.3f), minSliderPos,
                          x + width * 0.5f - juce::jmin (8.0f, width * 0.4f), minSliderPos - 7.0f,
                          x + width * 0.5f - juce::jmin (8.0f, width * 0.4f), minSliderPos,
                          fill, outline);

            drawTriangle (g, x + width * 0.5f + juce::jmin (4.0f, width * 0.3f), maxSliderPos,
                          x + width * 0.5f - juce::jmin (8.0f, width * 0.4f), maxSliderPos,
                          x + width * 0.5f - juce::jmin (8.0f, width * 0.4f), maxSliderPos + 7.0f,
                          fill, outline);
        }
        else if (style == juce::Slider::TwoValueHorizontal || style == juce::Slider::ThreeValueHorizontal)
        {
            drawTriangle (g, minSliderPos, y + height * 0.6f - juce::jmin (4.0f, height * 0.3f),
                          minSliderPos - 7.0f, y + height * 0.9f ,
                          minSliderPos, y + height * 0.9f,
                          fill, outline);

            drawTriangle (g, maxSliderPos, y + height * 0.6f - juce::jmin (4.0f, height * 0.3f),
                          maxSliderPos, y + height * 0.9f,
                          maxSliderPos + 7.0f, y + height * 0.9f,
                          fill, outline);
        }

        if (style == juce::Slider::LinearHorizontal || style == juce::Slider::ThreeValueHorizontal)
        {
            drawTriangle (g, sliderPos, y + height * 0.9f,
                          sliderPos - 7.0f, y + height * 0.2f,
                          sliderPos + 7.0f, y + height * 0.2f,
                          fill, outline);
        }
        else if (style == juce::Slider::LinearVertical || style == juce::Slider::ThreeValueVertical)
        {
            drawTriangle (g, x + width * 0.5f - juce::jmin (4.0f, width * 0.3f), sliderPos,
                          x + width * 0.5f + juce::jmin (8.0f, width * 0.4f), sliderPos - 7.0f,
                          x + width * 0.5f + juce::jmin (8.0f, width * 0.4f), sliderPos + 7.0f,
                          fill, outline);
        }
    }
}

int CustomLookAndFeel::getSliderThumbRadius(juce::Slider&)
{
    return 8;
}

juce::Button* CustomLookAndFeel::createSliderButton(const bool isIncrement)
{
    if (isIncrement)
        return new juce::ArrowButton("u", 0.75f, juce::Colours::white.withAlpha (0.8f));
    else
        return new juce::ArrowButton("d", 0.25f, juce::Colours::white.withAlpha (0.8f));
}

juce::ImageEffectFilter* CustomLookAndFeel::getSliderEffect()
{
    return &scrollbarShadow;
}

//==============================================================================

void CustomLookAndFeel::drawCornerResizer(juce::Graphics& g,
                                          int w, int h,
                                          bool isMouseOver, bool isMouseDragging)
{
    g.setColour ((isMouseOver || isMouseDragging) ? juce::Colours::lightgrey
                                                  : juce::Colours::darkgrey);

    const float lineThickness = juce::jmin (w, h) * 0.1f;

    for (float i = 0.0f; i < 1.0f; i += 0.3f)
    {
        g.drawLine (w * i,
                    h + 1.0f,
                    w + 1.0f,
                    h * i,
                    lineThickness);
    }
}

//==============================================================================

juce::Button* CustomLookAndFeel::createDocumentWindowButton(int buttonType)
{
    juce::Path shape;

    if (buttonType == juce::DocumentWindow::closeButton)
    {
        shape.addLineSegment (juce::Line<float> (0.0f, 0.0f, 1.0f, 0.9f), 0.45f);
        shape.addLineSegment (juce::Line<float> (1.0f, 0.0f, 0.0f, 1.0f), 0.35f);

        juce::ShapeButton* const b = new juce::ShapeButton ("close",
                                                      juce::Colour (0x7fff3333),
                                                      juce::Colour (0xd7ff3333),
                                                      juce::Colour (0xf7ff3333));

        b->setShape (shape, true, true, true);
        return b;
    }
    else if (buttonType == juce::DocumentWindow::minimiseButton)
    {
        shape.addLineSegment (juce::Line<float> (0.0f, 0.5f, 1.0f, 0.5f), 0.25f);

        juce::DrawableButton* b = new juce::DrawableButton ("minimise", juce::DrawableButton::ImageFitted);
        juce::DrawablePath dp;
        dp.setPath (shape);
        dp.setFill (juce::Colours::black.withAlpha (0.3f));
        b->setImages (&dp);
        return b;
    }
    else if (buttonType == juce::DocumentWindow::maximiseButton)
    {
        shape.addLineSegment (juce::Line<float> (0.5f, 0.0f, 0.5f, 1.0f), 0.25f);
        shape.addLineSegment (juce::Line<float> (0.0f, 0.5f, 1.0f, 0.5f), 0.25f);

        juce::DrawableButton* b = new juce::DrawableButton ("maximise", juce::DrawableButton::ImageFitted);
        juce::DrawablePath dp;
        dp.setPath (shape);
        dp.setFill (juce::Colours::black.withAlpha (0.3f));
        b->setImages (&dp);
        return b;
    }

    jassertfalse;
    return nullptr;
}

void CustomLookAndFeel::positionDocumentWindowButtons(juce::DocumentWindow& window,
                                                      int titleBarX, int titleBarY, int titleBarW, int titleBarH,
                                                      juce::Button* minimiseButton, juce::Button* maximiseButton, juce::Button* closeButton,
                                                      bool positionTitleBarButtonsOnLeft)
{
    titleBarY += titleBarH / 8;
    titleBarH -= titleBarH / 4;

    const int buttonW = titleBarH;

    int x = positionTitleBarButtonsOnLeft ? titleBarX + 4
                                          : titleBarX + titleBarW - buttonW - 4;

    if (closeButton != nullptr)
    {
        closeButton->setBounds (x, titleBarY, buttonW, titleBarH);
        x += positionTitleBarButtonsOnLeft ? buttonW + buttonW / 5
                                           : -(buttonW + buttonW / 5);
    }

    if (positionTitleBarButtonsOnLeft)
        std::swap (minimiseButton, maximiseButton);

    if (maximiseButton != nullptr)
    {
        maximiseButton->setBounds (x, titleBarY - 2, buttonW, titleBarH);
        x += positionTitleBarButtonsOnLeft ? buttonW : -buttonW;
    }

    if (minimiseButton != nullptr)
        minimiseButton->setBounds (x, titleBarY - 2, buttonW, titleBarH);
}
