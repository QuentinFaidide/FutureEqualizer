BUNDLE = future-equalizer.lv2
INSTALL_DIR = /usr/local/lib/lv2
RESSOURCE_DIR = /usr/local/share/future-lv2


# $(BUNDLE): manifest.ttl future_equalizer.ttl FutureEqualizer.so FutureEqualizerGUI.so
# 	rm -rf $(BUNDLE)
# 	mkdir $(BUNDLE)
# 	cp manifest.ttl future_equalizer.ttl FutureEqualizer.so FutureEqualizerGUI.so $(BUNDLE)

$(BUNDLE): manifest.ttl future_equalizer.ttl FutureEqualizer.so
	rm -rf $(BUNDLE)
	mkdir $(BUNDLE)
	cp manifest.ttl future_equalizer.ttl FutureEqualizer.so $(BUNDLE)

FutureEqualizer.so: FutureEqualizer.cpp FutureEqualizer.hpp LowCut.cpp LowCut.hpp HighCut.cpp HighCut.hpp
	g++ -shared -fPIC -DPIC FutureEqualizer.cpp LowCut.cpp HighCut.cpp `pkg-config --cflags --libs lv2-plugin` -o FutureEqualizer.so 

# FutureEqualizerGUI.so: FutureEqualizerGUI.cpp DrawUI.cpp Knob.cpp Knob.hpp DrawUI.hpp Switch.hpp Switch.hpp
#  	g++ -shared -fPIC -DPIC FutureEqualizerGUI.cpp DrawUI.cpp Knob.cpp Switch.cpp `pkg-config --cflags --libs lv2-gui` -o FutureEqualizerGUI.so

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)
	mkdir -p $(RESSOURCE_DIR)
	rm -rf $(RESSOURCE_DIR)/*
#	cp background_eq.png $(RESSOURCE_DIR)
#	cp knob_eq.png $(RESSOURCE_DIR)
#	cp switch_on.png &(RESSOURCE_DIR)
#	cp switch_off.png &(RESSOURCE_DIR)

clean:
	rm -rf $(BUNDLE) FutureEqualizer.so #FutureEqualizerGUI.so