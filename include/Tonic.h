//
//  Tonic.h
//  Tonic
//
//  Created by Nick Donaldson on 2/24/13.
//

/***********************************************************
 *
 * Consolidated header file for Tonic core objects
 * These objects are enough to build signal chains
 * using Generators and ControlGenerators with overloaded
 * operators for arithmetic.
 *
 ***********************************************************/

#pragma once

// ------- Core Objects --------

#include "Arithmetic.h"
#include "ControlArithmetic.h"
#include "ControlComparison.h"
#include "ControlParameter.h"
#include "ControlTrigger.h"
#include "ControlValue.h"
#include "FixedValue.h"
#include "Mixer.h"
#include "MonoToStereoPanner.h"
#include "RampedValue.h"
#include "SampleTable.h"
#include "Synth.h"
#include "TonicCore.h"
#include "TonicFrames.h"

// -------- Generators ---------

// Oscillators
#include "SineWave.h"
#include "TableLookupOsc.h"

#include "RectWave.h" // Aliasing
#include "SawtoothWave.h" // Aliasing
#include "SquareWave.h" // Aliasing
#include "TriangleWave.h" // Aliasing

#include "Noise.h"

// Effects
#include "BasicDelay.h"
#include "BitCrusher.h"
#include "CombFilter.h"
#include "DelayUtils.h"
#include "FilterUtils.h"
#include "Filters.h"
#include "Reverb.h"
#include "StereoDelay.h"

// Utiliti
#include "ADSR.h"
#include "LFNoise.h"
#include "RingBuffer.h"

// Non-Oscr Audio Sources
#include "BufferPlayer.h"

// ------- Control Generators --------

#include "ControlCallback.h" // C++11 only
#include "ControlCounter.h"
#include "ControlDbToLinear.h"
#include "ControlDelay.h"
#include "ControlFloor.h"
#include "ControlMetro.h"
#include "ControlMetroDivider.h"
#include "ControlMidiToFreq.h"
#include "ControlPrinter.h"
#include "ControlPulse.h"
#include "ControlRandom.h"
#include "ControlSnapToScale.h"
#include "ControlStepper.h"
#include "ControlSwitcher.h"
#include "ControlTriggerFilter.h"
#include "ControlXYSpeed.h"

// ------- ---------

#include "AudioFileUtils.h"
