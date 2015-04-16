#include "Knob.hpp"

#include <gtkmm.h>
#include <cmath>

Knob::Knob(float kmin, float kmax, float kdef, bool ilog)
{
	isLog= ilog;
	if(isLog)
	{
		min = log10(kmin);
		max = log10(kmax);
		def = log10(kdef);
		current = log10(def);
	}
	else
	{
		min = kmin;
		max = kmax;
		def = kdef;
		current = def;
	}

	clicked = false;


	kimage = Gdk::Pixbuf::create_from_file(KNOB_PATH);
}

Knob::~Knob()
{

}

void Knob::drawKnob(Cairo::RefPtr<Cairo::Context> cr, int x, int y)
{
	cr->save();
	xpos = x;
	ypos = y;
	cr->translate(x, y);
	cr->translate((kimage->get_width()/2), (kimage->get_height()/2));
	cr->rotate_degrees(static_cast<int>( ((current-min)/(max-min))*180 ));
	Gdk::Cairo::set_source_pixbuf(cr, kimage, -(kimage->get_width()/2), -(kimage->get_height()/2));
	cr->rectangle(-(kimage->get_width()/2), -(kimage->get_height()/2), kimage->get_width(), kimage->get_height());
	cr->fill();

	cr->restore();
}

void Knob::setValue(float port_input)
{
	if(isLog)
	{
		current = log10(port_input);
	}
	else
	{
		current = port_input;
	}
}

float Knob::getValue()
{
	if(isLog)
	{
		return pow(10, current);
	}
	else
	{
		return current;
	}
}

void Knob::handleEvent(GdkEventExpose* event)
{

}

void Knob::checkClickZone(int x, int y)
{
	if( (x>xpos && x<(xpos+60)) && (y>ypos && y<(ypos+60)) )
	{
		clicked = true;
	}
}

void Knob::onRelease()
{
	clicked = false;
}

void Knob::addUp()
{
	if(clicked)
	{
		current = current + (max-min)*0.03;
		if(current>max)
		{
			current=max;
		}
	}
}

void Knob::addDown()
{
	if(clicked)
	{
		current = current - (max-min)*0.03;
		if(current<min)
		{
			current=min;
		}
	}
}