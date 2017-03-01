#ifndef MAINCOMPONENT_H_INCLUDED
#define MAINCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MyKnobScene.h"
#include "MyKnobScene_V2.h"

class MainContentComponent   : public Component
{
public:
	MainContentComponent() :
		myKnob1(Colours::blue)
    {

		addAndMakeVisible(myKnob1);
		addAndMakeVisible(myKnob2);
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
			Rectangle<int> dialArea = area.removeFromTop(area.getHeight() / 2);
			myKnob1.setBounds(dialArea.removeFromLeft(dialArea.getWidth() / 2).reduced(border));
			myKnob2.setBounds(dialArea.reduced(border));
		}
        
        const int buttonHeight = 30;
        /*
        button1.setBounds (area.removeFromTop (buttonHeight).reduced (border));
        button2.setBounds (area.removeFromTop (buttonHeight).reduced (border));
		*/
	}

private:
	MyKnobScene_V2 myKnob1;
	MyKnobScene_V2 myKnob2;
    TextButton button1;
    TextButton button2;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainContentComponent)
};


#endif  // MAINCOMPONENT_H_INCLUDED
