#include "UI.hpp"
#include "FutureEqualizerGUI.cpp"
#include <iostream>

UI::UI(FutureEqualizerGUI* parent)
{
	image = Gdk::Pixbuf::create_from_file(BACKGROUND_PATH);
	set_size_request(560, 370);
	add_events(Gdk::BUTTON_PRESS_MASK);
	add_events(Gdk::BUTTON_RELEASE_MASK);
	add_events(Gdk::POINTER_MOTION_MASK);
	buttonIsPressed = false;
	parentClass = parent;
	kn_lc_freq = new Knob(10, 10000, 10, true);
	kn_hc_freq = new Knob(10, 20000, 20000, true);
}

UI::~UI()
{

}

bool UI::on_expose_event(GdkEventExpose* event)
{
	Glib::RefPtr<Gdk::Window> window = get_window();
	window->resize(560, 370);
	Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();

	if (!image)
    {
    	std::cout << "Image aps chargé" << std::endl;
    }
	Gdk::Cairo::set_source_pixbuf(cr, image, 0,0);
	cr->rectangle(0, 0, image->get_width(), image->get_height());
	cr->fill();

	kn_lc_freq->drawKnob(cr, 343, 40);
	kn_hc_freq->drawKnob(cr, 475, 40);

	return true;
}

bool UI::on_button_press_event(GdkEventButton*event)
{
	if(event->button == 1)
	{
		buttonIsPressed = true;
		xmouseorigin = event->x;
		ymouseorigin = event->y;
		xmovemem = xmouseorigin;
		ymovemem = ymouseorigin;
		kn_lc_freq->checkClickZone(event->x, event->y);
		kn_hc_freq->checkClickZone(event->x, event->y);
	}
}

void UI::refreshLowCutFreq(float value)
{
	kn_lc_freq->setValue(value);
	queue_draw_area(0,0,560, 370);
}

void UI::refreshHighCutFreq(float value)
{
	kn_hc_freq->setValue(value);
	queue_draw_area(0,0,560, 370);
}

bool UI::on_button_release_event(GdkEventButton*event)
{
	if(event->button == 1)
	{
		buttonIsPressed = false;
		kn_hc_freq->onRelease();
		kn_lc_freq->onRelease();
	}
}

bool UI::on_motion_notify_event(GdkEventMotion* event)
{
	if(buttonIsPressed)
	{
		if(event->y < ymovemem)
		{
			kn_lc_freq->addUp();
			kn_hc_freq->addUp();
			xmovemem = event->x;
			ymovemem = event->y;
			parentClass->writeLCFrequency(kn_lc_freq->getValue());
			parentClass->writeHCFrequency(kn_hc_freq->getValue());
		}
		if(event->y > ymovemem)
		{
			kn_lc_freq->addDown();
			kn_hc_freq->addDown();
			xmovemem = event->x;
			ymovemem = event->y;
			parentClass->writeLCFrequency(kn_lc_freq->getValue());
			parentClass->writeHCFrequency(kn_hc_freq->getValue());
		}
		queue_draw_area(0,0,560, 370);
	}
}