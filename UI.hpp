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
	void refreshPeak2Freq(float value);
	void refreshPeak2Res(float value);
	void refreshPeak2Gain(float value);
	void refreshPeak3Freq(float value);
	void refreshPeak3Res(float value);
	void refreshPeak3Gain(float value);
	void refreshLCSwitch(float value);
	void refreshHCSwitch(float value);
	void refreshP1Switch(float value);
	void refreshP2Switch(float value);
	void refreshP3Switch(float value);
	void refreshHarmMode(float value);
	void refreshHarmGain(float value);
	void refreshHarmRes(float value);
	void refreshHaSwitch(float value);

protected:
	virtual bool on_expose_event(GdkEventExpose* event);
	bool on_button_press_event(GdkEventButton* event);
	bool on_button_release_event(GdkEventButton* event);
	bool on_motion_notify_event (GdkEventMotion* event);
	bool buttonIsPressed;
	int xmouseorigin, ymouseorigin, xmovemem, ymovemem;
	Glib::RefPtr<Gdk::Pixbuf> image;
	FutureEqualizerGUI *parentClass;
	Knob *kn_lc_freq, *kn_hc_freq, *kn_p1_freq, *kn_p1_res, *kn_p1_gain, *kn_p2_freq, *kn_p2_res, *kn_p2_gain, *kn_p3_freq, *kn_p3_res, *kn_p3_gain, *kn_ha_mode, *kn_ha_res, *kn_ha_gain;
	Switch *sw_lc, *sw_hc, *sw_p1, *sw_p2, *sw_p3, *sw_ha;
};

#endif // DEF_UI_HPP