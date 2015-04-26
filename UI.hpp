#ifndef DEF_UI_HPP
#define DEF_UI_HPP

#define BACKGROUND_PATH "/usr/local/share/future-lv2/background_eq.png"

#include <gtkmm.h>
#include "Knob.hpp"
#include "Switch.hpp"

class FutureEqualizerGUI;

class UI : public Gtk::DrawingArea
{
public:
	UI(FutureEqualizerGUI* parent);
	virtual ~UI();
	void refreshLowCutFreq(float value);
	void refreshHighCutFreq(float value);
	void refreshPeak1Freq(float value);
	void refreshPeak1Res(float value);
	void refreshPeak1Gain(float value);
	void refreshLCSwitch(float value);
	void refreshHCSwitch(float value);
	void refreshP1Switch(float value);

protected:
	virtual bool on_expose_event(GdkEventExpose* event);
	bool on_button_press_event(GdkEventButton* event);
	bool on_button_release_event(GdkEventButton* event);
	bool on_motion_notify_event (GdkEventMotion* event);
	bool buttonIsPressed;
	int xmouseorigin, ymouseorigin, xmovemem, ymovemem;
	Glib::RefPtr<Gdk::Pixbuf> image;
	FutureEqualizerGUI *parentClass;
	Knob *kn_lc_freq, *kn_hc_freq, *kn_p1_freq, *kn_p1_res, *kn_p1_gain;
	Switch *sw_lc, *sw_hc, *sw_p1;
};

#endif // DEF_UI_HPP