// Basic command-line program for playing a Tonic synth
// Originally by Nick Donaldson, 2013-05-16

#include <iostream>

// Use the define + include you want, to select pulse/alsa/jack
//// Pulse:
// #define __LINUX_PULSE__
// #include <pulse/pulseaudio.h>
//// Jack:
// #define __UNIX_JACK__
// #include <jack/jack.h>
//// ALSA:
// #define __LINUX_ALSA__
// #include <alsa/asoundlib.h>

#include "Tonic.h"
#include "RtAudio.h"

using namespace Tonic;

const unsigned int nChannels = 2;

// Static smart pointer for our Synth
static Synth synth;

int renderCallback( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
        double streamTime, RtAudioStreamStatus status, void *userData )
{
    synth.fillBufferOfFloats((float*)outputBuffer, nBufferFrames, nChannels);
    return 0;
}

int main(int argc, const char * argv[])
{
    // Configure RtAudio
    RtAudio dac;
    RtAudio::StreamParameters rtParams;
    rtParams.deviceId = dac.getDefaultOutputDevice();
    rtParams.nChannels = nChannels;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 512; // 512 sample frames

    // You don't necessarily have to do this - it will default to 44100 if not set.
    Tonic::setSampleRate(sampleRate);

    // --------- MAKE A SYNTH HERE -----------

    ControlMetro metro = ControlMetro().bpm(100);
    ControlGenerator freq = ControlRandom().trigger(metro).min(0).max(1);

    Generator tone = SquareWaveBL().freq(
                                     freq * 0.25 + 100
                                     + 400
                                     ) * SineWave().freq(50);

    ADSR env = ADSR()
    .attack(0.01)
    .decay( 0.4 )
    .sustain(0)
    .release(0)
    .doesSustain(false)
    .trigger(metro);

    StereoDelay delay = StereoDelay(3.0f,3.0f)
    .delayTimeLeft( 0.5 + SineWave().freq(0.2) * 0.01)
    .delayTimeRight(0.55 + SineWave().freq(0.23) * 0.01)
    .feedback(0.3)
    .dryLevel(0.8)
    .wetLevel(0.2);

    Generator filterFreq = (SineWave().freq(0.01) + 1) * 200 + 225;

    LPF24 filter = LPF24().Q(2).cutoff( filterFreq );

    Generator output = (( tone * env ) >> filter >> delay) * 0.3;

    synth.setOutputGen(output);

    // ---------------------------------------


    // open rtaudio stream
    try {
        dac.openStream( &rtParams, nullptr, RTAUDIO_FLOAT32, sampleRate, &bufferFrames, &renderCallback, nullptr, nullptr );

        dac.startStream();

        // hacky, yes, but let's just hang out for awhile until someone presses a key
        printf("\n\nPress Enter to stop\n\n");
        cin.get();

        dac.stopStream();
    }
    catch ( RtError& e ) {
        std::cout << '\n' << e.getMessage() << '\n' << std::endl;
        exit( 0 );
    }

    return 0;
}

