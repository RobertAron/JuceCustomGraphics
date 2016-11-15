/*
  ==============================================================================

    MyCustomLookAndFeel_V2.h
    Created: 8 Nov 2016 2:10:55pm
    Author:  HeyImRige

  ==============================================================================
*/

#ifndef MYCUSTOMLOOKANDFEEL_V2_H_INCLUDED
#define MYCUSTOMLOOKANDFEEL_V2_H_INCLUDED
#include "../JuceLibraryCode/JuceHeader.h"
#include <string>


class MyCustomLookAndFeel_V2 : public LookAndFeel_V3
{
public:
	MyCustomLookAndFeel_V2(Colour colour)
	{
		setColour(Slider::rotarySliderOutlineColourId,colour);
		log = Logger::getCurrentLogger();
	}
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderposition, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		const float pi = 3.14159;
		//outer circle radius
		const float radius = jmin(width / 2, height / 2) - 3.0f;
		//inner circle radius
		const float innerradius = jmin(width / 2, height / 2) - 7.0f;
		//percentage of glowy ring
		const float glowPercentage = radius / innerradius;
		//outter circle centers
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		//corner point of the outer circle
		const float rx = centreX - radius;
		const float ry = centreY - radius;
		//corner point of the inner circle
		const float innerx = centreX - innerradius;
		const float innery = centreY - innerradius;
		//width of the inner circle
		const float innerw = innerradius *2.0f;
		//width of the outer circle
		const float rw = radius * 2.0f;
		//angle of the knob
		const float angle = rotaryStartAngle + sliderposition * (rotaryEndAngle - rotaryStartAngle);
		//change opacity over based on mouse
		mouseOverBool=slider.isMouseOver();
		if(mouseOverBool&&(animationValue < .9f))
		{
			animationValue = animationValue+ 0.15f;
			if (animationValue > 1)animationValue = 1;
		} 
		else if(!mouseOverBool&& (animationValue>0.1f))
		{
			animationValue = animationValue- 0.18f;
			if (animationValue < 0)animationValue = 0;
		}


		//fill knob area white
		g.setColour(Colours::white);
		g.fillEllipse(rx, ry, rw, rw);
		
		//draw outline
		Line<float> myLine1(0, 0, 0, -radius);
		Line<float> myLine2(0, -radius, 0, 0);
		myLine1.applyTransform(AffineTransform::rotation(rotaryStartAngle).translated(centreX, centreY));
		myLine2.applyTransform(AffineTransform::rotation(rotaryEndAngle).translated(centreX, centreY));
		Path knobAngleEtch;
		knobAngleEtch.addLineSegment(myLine2, 0.0f);
		knobAngleEtch.addLineSegment(myLine1,0.0f);
		knobAngleEtch.addCentredArc(centreX, centreY,radius , radius, 0.0f, rotaryStartAngle, rotaryEndAngle);
		knobAngleEtch.closeSubPath();
		g.setColour(Colours::grey);
		g.fillPath(knobAngleEtch);

		//glowy path
		Path knobRingGlow;
		knobRingGlow.addPieSegment(innerx, innery, innerw, innerw, rotaryStartAngle, angle, glowPercentage);
		g.setColour(Colours::red);
		g.fillPath(knobRingGlow);
		
		
		
		
		
		
		/*
		//full circle
		g.setColour(Colours::black);
		g.fillEllipse(rx, ry, rw, rw);
		//outter ring
		g.setColour(Colours::darkgrey);
		g.drawEllipse(rx, ry, rw, rw, 6.0f);

		//elispse around the circle
		g.setColour(Colours::purple);
		Path arc;
		arc.addPieSegment(rx - 3.0f, ry - 3.0f, rw + 6.0f, rw + 6.0f, rotaryStartAngle, angle, 0.95f);
		g.fillPath(arc);
		//outter ring special
		g.setColour(Colours::red.withAlpha(animationValue));
		g.fillPath(arc);

		//tiny circle
		Path tinyCircle;
		tinyCircle.addEllipse(-4.0f, -radius - 4.0f, 8.0f, 8.0f);
		tinyCircle.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));


		g.setColour(Colours::white);
		g.fillPath(tinyCircle);

		*/
	}
private:
	bool mouseOverBool;
	float animationValue = 0.0f;
	Logger* log;
};



#endif  // MYCUSTOMLOOKANDFEEL_V2_H_INCLUDED