BUNDLE = future-equalizer.lv2
INSTALL_DIR = /usr/local/lib/lv2
RESSOURCE_DIR = /usr/local/share/future-lv2


$(BUNDLE): manifest.ttl future_equalizer.ttl FutureEqualizer.so FutureEqualizerGUI.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp manifest.ttl future_equalizer.ttl FutureEqualizer.so FutureEqualizerGUI.so $(BUNDLE)

FutureEqualizer.so: FutureEqualizer.cpp FutureEqualizer.hpp LowCut.cpp LowCut.hpp HighCut.cpp HighCut.hpp Peak.cpp Peak.hpp Harmonics.cpp Harmonics.hpp
	g++ -shared -fPIC -DPIC FutureEqualizer.cpp LowCut.cpp HighCut.cpp Peak.cpp Harmonics.cpp `pkg-config --cflags --libs lv2-plugin` -o FutureEqualizer.so 

FutureEqualizerGUI.so: FutureEqualizerGUI.cpp UI.cpp UI.hpp Knob.cpp Switch.hpp Switch.cpp Knob.hpp 
	g++ -shared -fPIC -DPIC FutureEqualizerGUI.cpp Switch.cpp UI.cpp Knob.cpp `pkg-config --cflags --libs lv2-gui` -o FutureEqualizerGUI.so

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)
	mkdir -p $(RESSOURCE_DIR)
	rm -rf $(RESSOURCE_DIR)/*
	cp background_eq.png $(RESSOURCE_DIR)
	cp knob_eq.png $(RESSOURCE_DIR)
	cp toggle_eq.png $(RESSOURCE_DIR)

clean:
	rm -rf $(BUNDLE) FutureEqualizer.so FutureEqualizerGUI.so