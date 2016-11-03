/*
  ==============================================================================

    KnobMask.h
    Created: 1 Nov 2016 3:21:34pm
    Author:  HeyImRige

  ==============================================================================
*/

#ifndef KNOBMASK_H_INCLUDED
#define KNOBMASK_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class KnobMask    : public Component
{
public:
    KnobMask()
    {
        // In your constructor, you should add any child components, and
        // initialise any special settings that your component needs.
		myMouseListener = MouseListener();
		addMouseListener(&myMouseListener, true);

    }

    ~KnobMask()
    {
    }

    void paint (Graphics& g) override
    {
        /* This demo code just fills the component's background and
           draws some placeholder text to get you started.

           You should replace everything in this method with your own
           drawing code..
        */

		//elispse around the circle
		g.setColour(Colours::green);
		g.fillRect(getLocalBounds());
		/*
		g.setColour(Colours::purple);
		Path arc;
		arc.addPieSegment(rx - 3.0f, ry - 3.0f, rw + 6.0f, rw + 6.0f, rotaryStartAngle, angle, 0.95f);
		g.fillPath(arc);
		*/
    }

    void resized() override
    {
        // This method is where you should set the bounds of any child
        // components that your component contains..

    }
	void setSliderPosition(float f){
		sliderPosition = f;
	}
private:
	MouseListener myMouseListener;
	float sliderPosition;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KnobMask)
};


#endif  // KNOBMASK_H_INCLUDED
