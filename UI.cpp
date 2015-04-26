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
	kn_p1_freq = new Knob(10, 20000, 200, true);
	kn_p1_res  = new Knob(0.6, 10, 1, false);
	kn_p1_gain = new Knob(-24, 24, 0, false);
	sw_lc = new Switch();
	sw_hc = new Switch();
	sw_p1 = new Switch();
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
    	std::cout << "FutureEqualizer: Can't find background image where it belongs" << std::endl;
    }
	Gdk::Cairo::set_source_pixbuf(cr, image, 0,0);
	cr->rectangle(0, 0, image->get_width(), image->get_height());
	cr->fill();

	kn_lc_freq->drawKnob(cr, 347, 46);
	kn_hc_freq->drawKnob(cr, 483, 46);
	kn_p1_freq->drawKnob(cr, 75, 163);
	kn_p1_res->drawKnob(cr, 75, 218);
	kn_p1_gain->drawKnob(cr, 75, 274);
	sw_lc->drawSwitch(cr, 336, 106);
	sw_hc->drawSwitch(cr, 470, 106);
	sw_p1->drawSwitch(cr, 62, 336);

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
		kn_p1_freq->checkClickZone(event->x, event->y);
		kn_p1_res->checkClickZone(event->x, event->y);
		kn_p1_gain->checkClickZone(event->x, event->y);
		sw_lc->checkClickZone(event->x, event->y);
		sw_hc->checkClickZone(event->x, event->y);
		sw_p1->checkClickZone(event->x, event->y);
		parentClass->writeLCSwitch(sw_lc->getValue());
		parentClass->writeHCSwitch(sw_hc->getValue());
		parentClass->writeP1Switch(sw_p1->getValue());
		queue_draw_area(0,0,560, 370);
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

void UI::refreshPeak1Freq(float value)
{
	kn_p1_freq->setValue(value);
	queue_draw_area(0,0,560, 370);
}

void UI::refreshPeak1Res(float value)
{
	kn_p1_res->setValue(value);
	queue_draw_area(0,0,560, 370);
}

void UI::refreshPeak1Gain(float value)
{
	kn_p1_gain->setValue(value);
	queue_draw_area(0,0,560, 370);
}

void UI::refreshLCSwitch(float value)
{
	sw_lc->setValue(value);
	queue_draw_area(0,0,560, 370);
}

void UI::refreshHCSwitch(float value)
{
	sw_hc->setValue(value);
	queue_draw_area(0,0,560, 370);
}

void UI::refreshP1Switch(float value)
{
	sw_p1->setValue(value);
	queue_draw_area(0,0,560, 370);
}


bool UI::on_button_release_event(GdkEventButton*event)
{
	if(event->button == 1)
	{
		buttonIsPressed = false;
		kn_hc_freq->onRelease();
		kn_lc_freq->onRelease();
		kn_p1_freq->onRelease();
		kn_p1_res->onRelease();
		kn_p1_gain->onRelease();
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
			kn_p1_freq->addUp();
			kn_p1_res->addUp();
			kn_p1_gain->addUp();
			xmovemem = event->x;
			ymovemem = event->y;
			parentClass->writeLCFrequency(kn_lc_freq->getValue());
			parentClass->writeHCFrequency(kn_hc_freq->getValue());
			parentClass->writeP1Frequency(kn_p1_freq->getValue());
			parentClass->writeP1Resonance(kn_p1_res->getValue());
			parentClass->writeP1Gain(kn_p1_gain->getValue());
		}
		if(event->y > ymovemem)
		{
			kn_lc_freq->addDown();
			kn_hc_freq->addDown();
			kn_p1_freq->addDown();
			kn_p1_res->addDown();
			kn_p1_gain->addDown();
			xmovemem = event->x;
			ymovemem = event->y;
			parentClass->writeLCFrequency(kn_lc_freq->getValue());
			parentClass->writeHCFrequency(kn_hc_freq->getValue());
			parentClass->writeP1Frequency(kn_p1_freq->getValue());
			parentClass->writeP1Resonance(kn_p1_res->getValue());
			parentClass->writeP1Gain(kn_p1_gain->getValue());
		}
		queue_draw_area(0,0,560, 370);
	}
}