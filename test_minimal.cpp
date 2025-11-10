/* ------------------------------------------------------------
name: "SGT_HarmonyGenerator"
Code generated with Faust 2.81.10 (https://faust.grame.fr)
Compilation options: -a minimal-effect.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/******************* BEGIN minimal-effect.cpp ****************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/
 
#include <algorithm>

#include "faust/gui/UI.h"
#include "faust/gui/meta.h"
#include "faust/dsp/dsp.h"

#if defined(SOUNDFILE)
#include "faust/gui/SoundUI.h"
#endif

using std::max;
using std::min;

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <math.h>

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

#if defined(_WIN32)
#define RESTRICT __restrict
#else
#define RESTRICT __restrict__
#endif

class mydspSIG0 {
	
  private:
	
	int iVec0[2];
	int iRec2[2];
	
  public:
	
	int getNumInputsmydspSIG0() {
		return 0;
	}
	int getNumOutputsmydspSIG0() {
		return 1;
	}
	
	void instanceInitmydspSIG0(int sample_rate) {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			iVec0[l0] = 0;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			iRec2[l1] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec0[0] = 1;
			iRec2[0] = (iVec0[1] + iRec2[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * static_cast<float>(iRec2[0]));
			iVec0[1] = iVec0[0];
			iRec2[1] = iRec2[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];

class mydsp : public dsp {
	
 private:
	
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	int iVec1[2];
	float fConst4;
	FAUSTFLOAT fHslider0;
	float fRec3[2];
	int IOTA0;
	float fVec2[131072];
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fHslider2;
	float fRec4[2];
	FAUSTFLOAT fHslider3;
	float fRec1[2];
	float fRec0[2];
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fHslider4;
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fHslider5;
	float fRec5[2];
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("analyzers.lib/name", "Faust Analyzer Library");
		m->declare("analyzers.lib/version", "1.3.0");
		m->declare("analyzers.lib/zcr:author", "Dario Sanfilippo");
		m->declare("analyzers.lib/zcr:copyright", "Copyright (C) 2020 Dario Sanfilippo       <sanfilippo.dario@gmail.com>");
		m->declare("analyzers.lib/zcr:license", "MIT-style STK-4.3 license");
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/sAndH:author", "Romain Michon");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-a minimal-effect.cpp -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("filename", "SGT_HarmonyGenerator.dsp");
		m->declare("filters.lib/lowpass0_highpass1", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lptN:author", "Julius O. Smith III");
		m->declare("filters.lib/lptN:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lptN:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/version", "1.7.1");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.5.1");
		m->declare("name", "SGT_HarmonyGenerator");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/version", "1.6.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "1.3.0");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "1.6.0");
	}

	virtual int getNumInputs() {
		return 2;
	}
	virtual int getNumOutputs() {
		return 3;
	}
	
	static void classInit(int sample_rate) {
		mydspSIG0* sig0 = newmydspSIG0();
		sig0->instanceInitmydspSIG0(sample_rate);
		sig0->fillmydspSIG0(65536, ftbl0mydspSIG0);
		deletemydspSIG0(sig0);
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 0.5f * fConst0;
		fConst2 = std::exp(-(0.00024414062f / fConst0));
		fConst3 = 1.0f - fConst2;
		fConst4 = 1.0f / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider0 = static_cast<FAUSTFLOAT>(4.4e+02f);
		fHslider1 = static_cast<FAUSTFLOAT>(2048.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(7.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(256.0f);
		fHslider4 = static_cast<FAUSTFLOAT>(0.5f);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox3 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider5 = static_cast<FAUSTFLOAT>(4.0f);
	}
	
	virtual void instanceClear() {
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iVec1[l2] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec3[l3] = 0.0f;
		}
		IOTA0 = 0;
		for (int l4 = 0; l4 < 131072; l4 = l4 + 1) {
			fVec2[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec4[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec1[l6] = 0.0f;
		}
		for (int l7 = 0; l7 < 2; l7 = l7 + 1) {
			fRec0[l7] = 0.0f;
		}
		for (int l8 = 0; l8 < 2; l8 = l8 + 1) {
			fRec5[l8] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("SGT_HarmonyGenerator");
		ui_interface->declare(&fCheckbox2, "1", "");
		ui_interface->addCheckButton("Harmony Generator/v1Enable", &fCheckbox2);
		ui_interface->declare(&fCheckbox0, "1", "");
		ui_interface->addCheckButton("Harmony Generator/v2Enable", &fCheckbox0);
		ui_interface->declare(&fCheckbox3, "1", "");
		ui_interface->addCheckButton("Harmony Generator/v3Enable", &fCheckbox3);
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("Harmony Generator/wetDry", &fHslider4, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fHslider2, "2", "");
		ui_interface->declare(&fHslider2, "unit", "semitones");
		ui_interface->addHorizontalSlider("Harmony 1/Shift", &fHslider2, FAUSTFLOAT(7.0f), FAUSTFLOAT(-24.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider5, "3", "");
		ui_interface->declare(&fHslider5, "unit", "semitones");
		ui_interface->addHorizontalSlider("Harmony 2/Shift", &fHslider5, FAUSTFLOAT(4.0f), FAUSTFLOAT(-24.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider3, "4", "");
		ui_interface->addHorizontalSlider("Debug Tools/OLA Crossfade Size (samples)", &fHslider3, FAUSTFLOAT(256.0f), FAUSTFLOAT(128.0f), FAUSTFLOAT(512.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider1, "4", "");
		ui_interface->addHorizontalSlider("Debug Tools/OLA Window Size (samples)", &fHslider1, FAUSTFLOAT(2048.0f), FAUSTFLOAT(1024.0f), FAUSTFLOAT(4096.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fCheckbox1, "4", "");
		ui_interface->addCheckButton("Debug Tools/Test Tone Enable", &fCheckbox1);
		ui_interface->declare(&fHslider0, "4", "");
		ui_interface->declare(&fHslider0, "unit", "Hz");
		ui_interface->addHorizontalSlider("Debug Tools/Test Tone Freq", &fHslider0, FAUSTFLOAT(4.4e+02f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph0, "4", "");
		ui_interface->declare(&fHbargraph0, "unit", "Hz");
		ui_interface->addHorizontalBargraph("Debug Tools/v2FreqOut", &fHbargraph0, FAUSTFLOAT(0.0f), FAUSTFLOAT(1e+03f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		float fSlow0 = static_cast<float>(fCheckbox0);
		int iSlow1 = static_cast<int>(static_cast<float>(fCheckbox1));
		float fSlow2 = fConst4 * static_cast<float>(fHslider0);
		float fSlow3 = static_cast<float>(static_cast<int>(static_cast<float>(fHslider1)));
		float fSlow4 = std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider2));
		float fSlow5 = 1.0f / static_cast<float>(static_cast<int>(static_cast<float>(fHslider3)));
		float fSlow6 = static_cast<float>(fHslider4);
		float fSlow7 = static_cast<float>(fCheckbox2);
		float fSlow8 = static_cast<float>(fCheckbox3);
		float fSlow9 = std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider5));
		float fSlow10 = 1.0f - fSlow6;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			iVec1[0] = 1;
			float fTemp0 = ((1 - iVec1[1]) ? 0.0f : fSlow2 + fRec3[1]);
			fRec3[0] = fTemp0 - std::floor(fTemp0);
			float fTemp1 = 0.5f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec3[0]), 65535))];
			float fTemp2 = ((iSlow1) ? fTemp1 : ((iSlow1) ? fTemp1 : static_cast<float>(input0[i0])));
			fVec2[IOTA0 & 131071] = fTemp2;
			fRec4[0] = std::fmod(fSlow3 + (fRec4[1] + 1.0f - fSlow4), fSlow3);
			int iTemp3 = static_cast<int>(fRec4[0]);
			float fTemp4 = std::floor(fRec4[0]);
			float fTemp5 = 1.0f - fRec4[0];
			float fTemp6 = std::min<float>(fSlow5 * fRec4[0], 1.0f);
			float fTemp7 = fSlow3 + fRec4[0];
			int iTemp8 = static_cast<int>(fTemp7);
			float fTemp9 = std::floor(fTemp7);
			float fTemp10 = fSlow0 * ((fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp3))) & 131071] * (fTemp4 + fTemp5) + (fRec4[0] - fTemp4) * fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp3 + 1))) & 131071]) * fTemp6 + (fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp8))) & 131071] * (fTemp9 + fTemp5 - fSlow3) + (fSlow3 + (fRec4[0] - fTemp9)) * fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp8 + 1))) & 131071]) * (1.0f - fTemp6));
			fRec1[0] = ((fTemp10 != 0.0f) ? fTemp10 : fRec1[1]);
			fRec0[0] = fConst3 * static_cast<float>((fRec1[0] * fRec1[1]) < 0.0f) + fConst2 * fRec0[1];
			fHbargraph0 = static_cast<FAUSTFLOAT>(fConst1 * fRec0[0]);
			output0[i0] = static_cast<FAUSTFLOAT>(fHbargraph0);
			fRec5[0] = std::fmod(fSlow3 + (fRec5[1] + 1.0f - fSlow9), fSlow3);
			int iTemp11 = static_cast<int>(fRec5[0]);
			float fTemp12 = std::floor(fRec5[0]);
			float fTemp13 = 1.0f - fRec5[0];
			float fTemp14 = std::min<float>(fSlow5 * fRec5[0], 1.0f);
			float fTemp15 = fSlow3 + fRec5[0];
			int iTemp16 = static_cast<int>(fTemp15);
			float fTemp17 = std::floor(fTemp15);
			float fTemp18 = fSlow6 * (fTemp10 + fSlow7 * fTemp2 + fSlow8 * ((fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp11))) & 131071] * (fTemp12 + fTemp13) + (fRec5[0] - fTemp12) * fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp11 + 1))) & 131071]) * fTemp14 + (fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp16))) & 131071] * (fTemp17 + fTemp13 - fSlow3) + (fSlow3 + (fRec5[0] - fTemp17)) * fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp16 + 1))) & 131071]) * (1.0f - fTemp14))) + fSlow10 * fTemp2;
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp18);
			output2[i0] = static_cast<FAUSTFLOAT>(fTemp18);
			iVec1[1] = iVec1[0];
			fRec3[1] = fRec3[0];
			IOTA0 = IOTA0 + 1;
			fRec4[1] = fRec4[0];
			fRec1[1] = fRec1[0];
			fRec0[1] = fRec0[0];
			fRec5[1] = fRec5[0];
		}
	}

};

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

// Factory API
dsp* createmydsp() { return new mydsp(); }

/******************* END minimal-effect.cpp ****************/

#endif
