# AUDIO_API = LINUX_ALSA
# AUDIO_API = LINUX_OSS
# AUDIO_API = UNIX_JACK
AUDIO_API = LINUX_PULSE

ifeq ($(AUDIO_API),LINUX_ALSA)
  RTAUDIO_LIBS = -lasound -lpthread
else ifeq ($(AUDIO_API),LINUX_PULSE)
  RTAUDIO_LIBS = -lpulse-simple -lpulse -lpthread
else ifeq ($(AUDIO_API),UNIX_JACK)
  RTAUDIO_LIBS = `pkg-config --cflags --libs jack` -lpthread
endif

main:
	ccache $(CXX) -Os -pipe -std=c++17 $(CCFLAGS) -Iinclude -D__$(AUDIO_API)__ -o demo $(RTAUDIO_LIBS) common/*.cpp main.cpp -o $@

clean:
	rm -rf main
