#include "Switch.hpp"

Switch::Switch()
{
	state = 0;

	kimage = Gdk::Pixbuf::create_from_file(SWITCH_PATH);
}

Switch::~Switch()
{
	
}

void Switch::drawSwitch(Cairo::RefPtr<Cairo::Context> cr, int x, int y)
{
	cr->save();
	xpos = x;
	ypos = y;
	if(state == 1)
	{
		xpos = xpos + 10;
	}
	cr->translate(xpos, ypos);
	Gdk::Cairo::set_source_pixbuf(cr, kimage, 0, 0);
	cr->rectangle(0, 0, kimage->get_width(), kimage->get_height());
	cr->fill();

	cr->restore();
}

void Switch::setValue(float port_input)
{
	state = port_input;
}

float Switch::getValue()
{
	return state;
}

void Switch::checkClickZone(int x, int y)
{
	if(state == 0)
	{
		if( (x>xpos && x<(xpos+30)) && (y>ypos && y<(ypos+11)) )
		{
			state = 1;
		}
	}
	else if(state == 1)
	{
		if( (x>(xpos-10) && x<(xpos+20)) && (y>ypos && y<(ypos+11)) )
		{
			state = 0;
		}
	}
}