/*
  ==============================================================================

    MyKnobScene.h
    Created: 1 Nov 2016 3:20:43pm
    Author:  HeyImRige

  ==============================================================================
*/

#ifndef MYKNOBSCENE_H_INCLUDED
#define MYKNOBSCENE_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "KnobMask.h"
#include "MyCustomLookAndFeel.h"

//==============================================================================
/*
*/
class MyKnobScene    : public Component,
				public Component::MouseListener
{
public:
    MyKnobScene()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
		myDesktop = &Desktop::getInstance();
		globalAnimator = &myDesktop->getAnimator();
		log = Logger::getCurrentLogger();
		setLookAndFeel(&myCustomStuff);
		rotaryDial.setSliderStyle(Slider::RotaryVerticalDrag);
		rotaryDial.setTextBoxStyle(Slider::NoTextBox, false, 0, 0);

		addAndMakeVisible(knobMask);
		addAndMakeVisible(rotaryDial);

		knobMask.addMouseListener(this, true);
		rotaryDial.addMouseListener(this, true);
    }

    ~MyKnobScene()
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


		
        g.setColour (Colours::grey);
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..
		knobMask.setBounds(getLocalBounds());
		rotaryDial.setBounds(getLocalBounds());

    }
	virtual void MyKnobScene::mouseExit(const MouseEvent& event){
		log->writeToLog("test1");
		globalAnimator->animateComponent(&knobMask, knobMask.getBounds(), 1, 100, false, 0, 0);
	}
	virtual void MyKnobScene::mouseEnter(const MouseEvent& event) {
		log->writeToLog("test2");
		globalAnimator->animateComponent(&knobMask, knobMask.getBounds(), 0, 100, false, 0, 0);
	}

private:
	Slider rotaryDial;
	Logger* log;
	KnobMask knobMask;
	MyCustomLookAndFeel myCustomStuff;
	ComponentAnimator* globalAnimator;
	Desktop* myDesktop;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyKnobScene)
};


#endif  // MYKNOBSCENE_H_INCLUDED
