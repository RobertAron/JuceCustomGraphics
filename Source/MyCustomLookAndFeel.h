/*
  ==============================================================================

    MyCustomLookAndFeel.h
    Created: 24 Oct 2016 5:25:47pm
    Author:  HeyImRige

  ==============================================================================
*/

#ifndef MYCUSTOMLOOKANDFEEL_H_INCLUDED
#define MYCUSTOMLOOKANDFEEL_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "KnobMask.h"


class MyCustomLookAndFeel : public LookAndFeel_V3
{
public:
	MyCustomLookAndFeel()
	{
		setColour(Slider::rotarySliderFillColourId, Colours::purple);
	}
	void drawButtonBackground(Graphics& g, Button& button, const Colour& backgroundColour,
		bool isMouseOverButton, bool isButtonDown) override
	{
		Rectangle<int> buttonArea = button.getLocalBounds();
		const int edge = 4;
		buttonArea.removeFromLeft(edge);
		buttonArea.removeFromTop(edge);

		//shadow
		g.setColour(Colours::darkgrey.withAlpha(0.5f));
		g.fillRect(buttonArea);
		
		const int offset = isButtonDown ? -edge / 2 : -edge;
		buttonArea.translate(offset, offset);
		g.setColour(backgroundColour);
		g.fillRect(buttonArea);
		//...
	}

	void drawButtonText(Graphics& g, TextButton& button, bool isMouseOverButton, bool isButtonDown) override
	{
		Font font(getTextButtonFont(button, button.getHeight()));
		g.setFont(font);
		g.setColour(button.findColour(button.getToggleState() ? TextButton::textColourOnId
			: TextButton::textColourOffId)
			.withMultipliedAlpha(button.isEnabled() ? 1.0f : 0.5f));

		const int yIndent = jmin(4, button.proportionOfHeight(0.3f));
		const int cornerSize = jmin(button.getHeight(), button.getWidth()) / 2;

		const int fontHeight = roundToInt(font.getHeight() * 0.6f);
		const int leftIndent = jmin(fontHeight, 2 + cornerSize / (button.isConnectedOnLeft() ? 4 : 2));
		const int rightIndent = jmin(fontHeight, 2 + cornerSize / (button.isConnectedOnRight() ? 4 : 2));
		const int textWidth = button.getWidth() - leftIndent - rightIndent;

		const int edge = 4;
		const int offset = isButtonDown ? -edge / 2 : -edge;
		if (textWidth > 0)
			g.drawFittedText( button.getButtonText(),
				leftIndent+offset, yIndent+offset, textWidth, button.getHeight() - yIndent * 2,
				Justification::centred, 2);
	}



	void drawRotarySlider(Graphics& g, int x, int y, int width, int height, float sliderposition, const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider) override
	{
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
		//full circle
		g.setColour(Colours::black);
		g.fillEllipse(rx, ry, rw, rw);
		//outter ring
		g.setColour(Colours::darkgrey);
		g.drawEllipse(rx, ry, rw, rw, 6.0f);

		//elispse around the circle
		g.setColour(Colours::purple);
		Path arc;
		arc.addPieSegment(rx-3.0f, ry-3.0f, rw+6.0f, rw+6.0f, rotaryStartAngle, angle,0.95f);
		g.fillPath(arc);
		//outter ring special
		g.setColour(Colours::red.withAlpha(ringOpacity));
		g.fillPath(arc);

		//tiny circle
		Path tinyCircle;
		tinyCircle.addEllipse(-4.0f,-radius-4.0f,8.0f,8.0f);
		tinyCircle.applyTransform(AffineTransform::rotation(angle).translated(centreX, centreY));
		

		g.setColour(Colours::white);
		g.fillPath(tinyCircle);
		
	}
private:
	int test=0;
	float ringOpacity = 0.0f;
};




#endif  // MYCUSTOMLOOKANDFEEL_H_INCLUDED
