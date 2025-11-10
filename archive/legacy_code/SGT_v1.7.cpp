/* ------------------------------------------------------------
name: "SGT_HarmonyGenerator_v1.7"
Code generated with Faust 2.81.10 (https://faust.grame.fr)
Compilation options: -lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

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


class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fCheckbox0;
	int fSampleRate;
	float fConst0;
	float fConst1;
	FAUSTFLOAT fButton0;
	FAUSTFLOAT fButton1;
	FAUSTFLOAT fButton2;
	FAUSTFLOAT fButton3;
	FAUSTFLOAT fButton4;
	FAUSTFLOAT fButton5;
	FAUSTFLOAT fButton6;
	FAUSTFLOAT fButton7;
	FAUSTFLOAT fButton8;
	FAUSTFLOAT fButton9;
	FAUSTFLOAT fButton10;
	float fConst2;
	float fRec0[2];
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fHslider1;
	FAUSTFLOAT fCheckbox1;
	float fConst3;
	FAUSTFLOAT fHslider2;
	float fRec1[2];
	int IOTA0;
	float fVec0[131072];
	FAUSTFLOAT fHslider3;
	float fRec3[2];
	FAUSTFLOAT fHslider4;
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("compile_options", "-lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("filename", "SGT_HarmonyGenerator_v1.7.dsp");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.9.0");
		m->declare("misceffects.lib/name", "Misc Effects Library");
		m->declare("misceffects.lib/version", "2.5.1");
		m->declare("name", "SGT_HarmonyGenerator_v1.7");
		m->declare("oscillators.lib/name", "Faust Oscillator Library");
		m->declare("oscillators.lib/saw2ptr:author", "Julius O. Smith III");
		m->declare("oscillators.lib/saw2ptr:license", "STK-4.3");
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
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
		fConst1 = 44.1f / fConst0;
		fConst2 = 1.0f - fConst1;
		fConst3 = 1.0f / fConst0;
	}
	
	virtual void instanceResetUserInterface() {
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fButton0 = static_cast<FAUSTFLOAT>(0.0f);
		fButton1 = static_cast<FAUSTFLOAT>(0.0f);
		fButton2 = static_cast<FAUSTFLOAT>(0.0f);
		fButton3 = static_cast<FAUSTFLOAT>(0.0f);
		fButton4 = static_cast<FAUSTFLOAT>(0.0f);
		fButton5 = static_cast<FAUSTFLOAT>(0.0f);
		fButton6 = static_cast<FAUSTFLOAT>(0.0f);
		fButton7 = static_cast<FAUSTFLOAT>(0.0f);
		fButton8 = static_cast<FAUSTFLOAT>(0.0f);
		fButton9 = static_cast<FAUSTFLOAT>(0.0f);
		fButton10 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider0 = static_cast<FAUSTFLOAT>(7.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(0.5f);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(4.4e+02f);
		fHslider3 = static_cast<FAUSTFLOAT>(2048.0f);
		fHslider4 = static_cast<FAUSTFLOAT>(256.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; l0 < 2; l0 = l0 + 1) {
			fRec0[l0] = 0.0f;
		}
		for (int l1 = 0; l1 < 2; l1 = l1 + 1) {
			fRec1[l1] = 0.0f;
		}
		IOTA0 = 0;
		for (int l2 = 0; l2 < 131072; l2 = l2 + 1) {
			fVec0[l2] = 0.0f;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec3[l3] = 0.0f;
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
		ui_interface->openVerticalBox("SGT_HarmonyGenerator_v1.7");
		ui_interface->declare(&fCheckbox0, "1", "");
		ui_interface->addCheckButton("Harmony Control/Manual Mode (Override Preset)", &fCheckbox0);
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->addHorizontalSlider("Harmony Control/Manual Semitones", &fHslider0, FAUSTFLOAT(7.0f), FAUSTFLOAT(-24.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider1, "1", "");
		ui_interface->declare(&fHslider1, "style", "knob");
		ui_interface->addHorizontalSlider("Harmony Control/Wet/Dry Mix", &fHslider1, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fButton1, "2", "");
		ui_interface->declare(&fButton1, "midi", "key 22");
		ui_interface->addButton("Presets/A#0 - M2 Down", &fButton1);
		ui_interface->declare(&fButton3, "2", "");
		ui_interface->declare(&fButton3, "midi", "key 21");
		ui_interface->addButton("Presets/A0 - m3 Down", &fButton3);
		ui_interface->declare(&fButton10, "2", "");
		ui_interface->declare(&fButton10, "midi", "key 23");
		ui_interface->addButton("Presets/B0 - Octave Down", &fButton10);
		ui_interface->declare(&fButton6, "2", "");
		ui_interface->declare(&fButton6, "midi", "key 13");
		ui_interface->addButton("Presets/C#0 - P5 Up", &fButton6);
		ui_interface->declare(&fButton4, "2", "");
		ui_interface->declare(&fButton4, "midi", "key 15");
		ui_interface->addButton("Presets/D#0 - M3 Up", &fButton4);
		ui_interface->declare(&fButton8, "2", "");
		ui_interface->declare(&fButton8, "midi", "key 14");
		ui_interface->addButton("Presets/D0 - P4 Up", &fButton8);
		ui_interface->declare(&fButton2, "2", "");
		ui_interface->declare(&fButton2, "midi", "key 16");
		ui_interface->addButton("Presets/E0 - m3 Up", &fButton2);
		ui_interface->declare(&fButton7, "2", "");
		ui_interface->declare(&fButton7, "midi", "key 18");
		ui_interface->addButton("Presets/F#0 - P5 Down", &fButton7);
		ui_interface->declare(&fButton0, "2", "");
		ui_interface->declare(&fButton0, "midi", "key 17");
		ui_interface->addButton("Presets/F0 - M2 Up", &fButton0);
		ui_interface->declare(&fButton5, "2", "");
		ui_interface->declare(&fButton5, "midi", "key 20");
		ui_interface->addButton("Presets/G#0 - M3 Down", &fButton5);
		ui_interface->declare(&fButton9, "2", "");
		ui_interface->declare(&fButton9, "midi", "key 19");
		ui_interface->addButton("Presets/G0 - P4 Down", &fButton9);
		ui_interface->declare(&fHslider4, "4", "");
		ui_interface->addHorizontalSlider("Debug Tools/OLA Crossfade Size (samples)", &fHslider4, FAUSTFLOAT(256.0f), FAUSTFLOAT(128.0f), FAUSTFLOAT(512.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider3, "4", "");
		ui_interface->addHorizontalSlider("Debug Tools/OLA Window Size (samples)", &fHslider3, FAUSTFLOAT(2048.0f), FAUSTFLOAT(1024.0f), FAUSTFLOAT(4096.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fCheckbox1, "4", "");
		ui_interface->addCheckButton("Debug Tools/Test Tone Enable", &fCheckbox1);
		ui_interface->declare(&fHslider2, "4", "");
		ui_interface->declare(&fHslider2, "unit", "Hz");
		ui_interface->addHorizontalSlider("Debug Tools/Test Tone Freq", &fHslider2, FAUSTFLOAT(4.4e+02f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHbargraph0, "4", "");
		ui_interface->declare(&fHbargraph0, "unit", "Hz");
		ui_interface->addHorizontalBargraph("Debug Tools/v2FreqOut", &fHbargraph0, FAUSTFLOAT(0.0f), FAUSTFLOAT(2e+03f));
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** RESTRICT inputs, FAUSTFLOAT** RESTRICT outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		FAUSTFLOAT* output2 = outputs[2];
		int iSlow0 = static_cast<int>(static_cast<float>(fCheckbox0));
		float fSlow1 = fConst1 * (2.0f * (static_cast<float>(fButton0) - static_cast<float>(fButton1)) + 3.0f * (static_cast<float>(fButton2) - static_cast<float>(fButton3)) + 4.0f * (static_cast<float>(fButton4) - static_cast<float>(fButton5)) + 7.0f * (static_cast<float>(fButton6) - static_cast<float>(fButton7)) + 5.0f * (static_cast<float>(fButton8) - static_cast<float>(fButton9)) - 12.0f * static_cast<float>(fButton10));
		float fSlow2 = static_cast<float>(fHslider0);
		float fSlow3 = static_cast<float>(fHslider1);
		float fSlow4 = 1.0f - fSlow3;
		int iSlow5 = static_cast<int>(static_cast<float>(fCheckbox1));
		float fSlow6 = std::max<float>(1.1920929e-07f, std::fabs(static_cast<float>(fHslider2)));
		float fSlow7 = fConst3 * fSlow6;
		float fSlow8 = 1.0f - fConst0 / fSlow6;
		float fSlow9 = static_cast<float>(static_cast<int>(static_cast<float>(fHslider3)));
		float fSlow10 = 1.0f / static_cast<float>(static_cast<int>(static_cast<float>(fHslider4)));
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			fRec0[0] = fSlow1 + fConst2 * fRec0[1];
			float fTemp0 = std::pow(2.0f, 0.083333336f * ((iSlow0) ? fSlow2 : fRec0[0]));
			fHbargraph0 = static_cast<FAUSTFLOAT>(4.4e+02f * fTemp0);
			output0[i0] = static_cast<FAUSTFLOAT>(fHbargraph0);
			float fTemp1 = fSlow7 + fRec1[1] + -1.0f;
			int iTemp2 = fTemp1 < 0.0f;
			float fTemp3 = fSlow7 + fRec1[1];
			fRec1[0] = ((iTemp2) ? fTemp3 : fTemp1);
			float fRec2 = ((iTemp2) ? fTemp3 : fSlow7 + fRec1[1] + fSlow8 * fTemp1);
			float fTemp4 = 0.5f * (2.0f * fRec2 + -1.0f);
			float fTemp5 = ((iSlow5) ? fTemp4 : ((iSlow5) ? fTemp4 : static_cast<float>(input0[i0])));
			fVec0[IOTA0 & 131071] = fTemp5;
			fRec3[0] = std::fmod(fSlow9 + fRec3[1] + (1.0f - fTemp0), fSlow9);
			int iTemp6 = static_cast<int>(fRec3[0]);
			float fTemp7 = std::floor(fRec3[0]);
			float fTemp8 = 1.0f - fRec3[0];
			float fTemp9 = std::min<float>(fSlow10 * fRec3[0], 1.0f);
			float fTemp10 = fSlow9 + fRec3[0];
			int iTemp11 = static_cast<int>(fTemp10);
			float fTemp12 = std::floor(fTemp10);
			float fTemp13 = fSlow4 * fTemp5 + fSlow3 * ((fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp6))) & 131071] * (fTemp7 + fTemp8) + (fRec3[0] - fTemp7) * fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp6 + 1))) & 131071]) * fTemp9 + (fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp11))) & 131071] * (fTemp12 + fTemp8 - fSlow9) + (fSlow9 + (fRec3[0] - fTemp12)) * fVec0[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp11 + 1))) & 131071]) * (1.0f - fTemp9));
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp13);
			output2[i0] = static_cast<FAUSTFLOAT>(fTemp13);
			fRec0[1] = fRec0[0];
			fRec1[1] = fRec1[0];
			IOTA0 = IOTA0 + 1;
			fRec3[1] = fRec3[0];
		}
	}

};

#endif
