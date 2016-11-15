/*
  ==============================================================================

    MyKnobScene_V2.h
    Created: 8 Nov 2016 2:10:43pm
    Author:  HeyImRige

  ==============================================================================
*/

#ifndef MYKNOBSCENE_V2_H_INCLUDED
#define MYKNOBSCENE_V2_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "MyCustomLookAndFeel_V2.h"

//==============================================================================
/*
*/
class MyKnobScene_V2    :	public Component,
							public Component::MouseListener
{
public:
    MyKnobScene_V2(Colour knobColour):myCustomLook(knobColour)
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
		myDesktop = &Desktop::getInstance();
		globalAnimator = &myDesktop->getAnimator();
		log = Logger::getCurrentLogger();
		setLookAndFeel(&myCustomLook);
		rotaryDial.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);


		rotaryDial.addMouseListener(this, true);
		addAndMakeVisible(rotaryDial);
		

    }

    ~MyKnobScene_V2()
    {
		removeMouseListener(this);
    }

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

		g.setColour(Colours::seagreen);
		g.drawRect(getLocalBounds(), 2);//draw an outline
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
		rotaryDial.setBounds(getLocalBounds());

    }
	void MyKnobScene_V2::mouseEnter(const MouseEvent& event) {
		log->writeToLog("test3");
		globalAnimator->animateComponent(&rotaryDial, rotaryDial.getBounds(), .95, 100, false, 1, 1);
	}
	void MyKnobScene_V2::mouseExit(const MouseEvent& event) {
		log->writeToLog("test4");
		globalAnimator->animateComponent(&rotaryDial, rotaryDial.getBounds(), 1, 150, false, 1, 1);
	}

private:
	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MyKnobScene_V2)
	MyCustomLookAndFeel_V2 myCustomLook;
	Slider rotaryDial;
	ComponentAnimator* globalAnimator;
	Logger* log;
	Desktop* myDesktop;
};


#endif  // MYKNOBSCENE_V2_H_INCLUDED
