#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

class AltLookAndFeel : public LookAndFeel_V3
{
public:
    AltLookAndFeel()
    {
        setColour (Slider::rotarySliderFillColourId, Colours::red);
    }
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
    {
        const float radius = jmin (width / 2, height / 2) - 4.0f;
        const float centreX = x + width * 0.5f;
        const float centreY = y + height * 0.5f;
        const float rx = centreX - radius;
        const float ry = centreY - radius;
        const float rw = radius * 2.0f;
        const float angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        // fill
        g.setColour (Colours::orange);
        g.fillEllipse (rx, ry, rw, rw);
        
        // outline
        g.setColour (Colours::red);
        g.drawEllipse (rx, ry, rw, rw, 1.0f);
        
        Path p;
        const float pointerLength = radius * 0.33f;
        const float pointerThickness = 2.0f;
        p.addRectangle (-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform (AffineTransform::rotation (angle).translated (centreX, centreY));
        
        // pointer
        g.setColour (Colours::yellow);
        g.fillPath (p);
    }
};

//==============================================================================

class MainContentComponent   : public Component
{
public:
    MainContentComponent()
    {
        dial1.setLookAndFeel (&altLookAndFeel);
        dial1.setSliderStyle (Slider::Rotary);
        dial1.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (dial1);
        
        dial2.setSliderStyle (Slider::Rotary);
        dial2.setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        addAndMakeVisible (dial2);
        
        button1.setButtonText ("Button 1");
        addAndMakeVisible (button1);
        
        button2.setButtonText ("Button 2");
        addAndMakeVisible (button2);
        
        setSize (600, 400);
    }
    
    ~MainContentComponent()
    {
    }

    void paint (Graphics& g) override
    {
        g.fillAll (Colours::lightgrey);
    }
    
    void resized() override
    {
        const int border = 4;
        
        Rectangle<int> area = getLocalBounds();
        
        {
            Rectangle<int> dialArea = area.removeFromTop (area.getHeight() / 2);
            dial1.setBounds (dialArea.removeFromLeft (dialArea.getWidth() / 2).reduced (border));
            dial2.setBounds (dialArea.reduced (border));
        }
        
        const int buttonHeight = 30;
        
        button1.setBounds (area.removeFromTop (buttonHeight).reduced (border));
        button2.setBounds (area.removeFromTop (buttonHeight).reduced (border));
    }

private:
    AltLookAndFeel altLookAndFeel; // [2]
    Slider dial1;
    Slider dial2;
    TextButton button1;
    TextButton button2;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
