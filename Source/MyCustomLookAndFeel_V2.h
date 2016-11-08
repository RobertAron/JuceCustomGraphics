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


class MyCustomLookAndFeel_V2 : public LookAndFeel_V3
{
public:
	MyCustomLookAndFeel_V2()
	{
		log = Logger::getCurrentLogger();
	}
	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderposition, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
		log->writeToLog("inside draw of v2 current opacity"+String(ringOpacity));
		const float pi = 3.14159;
		const float radius = jmin(width / 2, height / 2) - 4.0f;
		const float innerradius = jmin(width / 2, height / 2) - 4.5f;
		const float centreX = x + width * 0.5f;
		const float centreY = y + height * 0.5f;
		const float rx = centreX - radius;
		const float ry = centreY - radius;
		const float innerx = centreX - innerradius;
		const float innery = centreY - innerradius;
		const float innerw = innerradius *2.0f;
		const float rw = radius * 2.0f;
		const float angle = rotaryStartAngle + sliderposition * (rotaryEndAngle - rotaryStartAngle);
		//change opacity over based on mouse
		mouseOverBool=slider.isMouseOver();
		if(mouseOverBool&&(ringOpacity < .9f))
		{
			log->writeToLog("changing opacity up");
			ringOpacity = ringOpacity+ 0.15f;
			if (ringOpacity > 1)ringOpacity = 1;
		} 
		else if(!mouseOverBool&& (ringOpacity>0.1f))
		{
			log->writeToLog("changing opacity down");
			ringOpacity = ringOpacity- 0.18f;
			if (ringOpacity < 0)ringOpacity = 0;
		}

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
		g.setColour(Colours::red.withAlpha(ringOpacity));
		g.fillPath(arc);

		//tiny circle
		Path tinyCircle;
		tinyCircle.addEllipse(-4.0f, -radius - 4.0f, 8.0f, 8.0f);
		tinyCircle.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));


		g.setColour(Colours::white);
		g.fillPath(tinyCircle);
	}
private:
	bool mouseOverBool;
	float ringOpacity = 0.0f;
	Logger* log;
};



#endif  // MYCUSTOMLOOKANDFEEL_V2_H_INCLUDED
