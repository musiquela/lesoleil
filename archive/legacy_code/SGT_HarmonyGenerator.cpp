/* ------------------------------------------------------------
name: "SGT_HarmonyGenerator"
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

class mydspSIG0 {
	
  private:
	
	int iVec0[2];
	int iRec0[2];
	
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
			iRec0[l1] = 0;
		}
	}
	
	void fillmydspSIG0(int count, float* table) {
		for (int i1 = 0; i1 < count; i1 = i1 + 1) {
			iVec0[0] = 1;
			iRec0[0] = (iVec0[1] + iRec0[1]) % 65536;
			table[i1] = std::sin(9.58738e-05f * static_cast<float>(iRec0[0]));
			iVec0[1] = iVec0[0];
			iRec0[1] = iRec0[0];
		}
	}

};

static mydspSIG0* newmydspSIG0() { return (mydspSIG0*)new mydspSIG0(); }
static void deletemydspSIG0(mydspSIG0* dsp) { delete dsp; }

static float ftbl0mydspSIG0[65536];

class mydsp : public dsp {
	
 private:
	
	FAUSTFLOAT fEntry0;
	FAUSTFLOAT fHbargraph0;
	FAUSTFLOAT fHslider0;
	FAUSTFLOAT fCheckbox0;
	FAUSTFLOAT fCheckbox1;
	int iVec1[2];
	int fSampleRate;
	float fConst0;
	FAUSTFLOAT fHslider1;
	float fRec1[2];
	int IOTA0;
	float fVec2[131072];
	FAUSTFLOAT fCheckbox2;
	FAUSTFLOAT fHslider2;
	float fRec2[2];
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fCheckbox3;
	FAUSTFLOAT fHslider4;
	float fRec3[2];
	
 public:
	mydsp() {
	}
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "1.22.0");
		m->declare("compile_options", "-lang cpp -ct 1 -es 1 -mcd 16 -mdd 1024 -mdy 33 -single -ftz 0");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "1.2.0");
		m->declare("filename", "SGT_HarmonyGenerator.dsp");
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
		fConst0 = 1.0f / std::min<float>(1.92e+05f, std::max<float>(1.0f, static_cast<float>(fSampleRate)));
	}
	
	virtual void instanceResetUserInterface() {
		fEntry0 = static_cast<FAUSTFLOAT>(67.0f);
		fHslider0 = static_cast<FAUSTFLOAT>(0.5f);
		fCheckbox0 = static_cast<FAUSTFLOAT>(0.0f);
		fCheckbox1 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider1 = static_cast<FAUSTFLOAT>(4.4e+02f);
		fCheckbox2 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider2 = static_cast<FAUSTFLOAT>(2048.0f);
		fHslider3 = static_cast<FAUSTFLOAT>(256.0f);
		fCheckbox3 = static_cast<FAUSTFLOAT>(0.0f);
		fHslider4 = static_cast<FAUSTFLOAT>(4.0f);
	}
	
	virtual void instanceClear() {
		for (int l2 = 0; l2 < 2; l2 = l2 + 1) {
			iVec1[l2] = 0;
		}
		for (int l3 = 0; l3 < 2; l3 = l3 + 1) {
			fRec1[l3] = 0.0f;
		}
		IOTA0 = 0;
		for (int l4 = 0; l4 < 131072; l4 = l4 + 1) {
			fVec2[l4] = 0.0f;
		}
		for (int l5 = 0; l5 < 2; l5 = l5 + 1) {
			fRec2[l5] = 0.0f;
		}
		for (int l6 = 0; l6 < 2; l6 = l6 + 1) {
			fRec3[l6] = 0.0f;
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
		ui_interface->declare(&fCheckbox0, "1", "");
		ui_interface->addCheckButton("Harmony Generator/v1Enable", &fCheckbox0);
		ui_interface->declare(&fCheckbox2, "1", "");
		ui_interface->addCheckButton("Harmony Generator/v2Enable", &fCheckbox2);
		ui_interface->declare(&fCheckbox3, "1", "");
		ui_interface->addCheckButton("Harmony Generator/v3Enable", &fCheckbox3);
		ui_interface->declare(&fHslider0, "1", "");
		ui_interface->declare(&fHslider0, "style", "knob");
		ui_interface->addHorizontalSlider("Harmony Generator/wetDry", &fHslider0, FAUSTFLOAT(0.5f), FAUSTFLOAT(0.0f), FAUSTFLOAT(1.0f), FAUSTFLOAT(0.01f));
		ui_interface->declare(&fEntry0, "2", "");
		ui_interface->declare(&fEntry0, "midi", "note");
		ui_interface->addNumEntry("Harmony 1/Midi Note", &fEntry0, FAUSTFLOAT(67.0f), FAUSTFLOAT(0.0f), FAUSTFLOAT(127.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider4, "3", "");
		ui_interface->declare(&fHslider4, "unit", "semitones");
		ui_interface->addHorizontalSlider("Harmony 2/Shift", &fHslider4, FAUSTFLOAT(4.0f), FAUSTFLOAT(-24.0f), FAUSTFLOAT(24.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider3, "4", "");
		ui_interface->addHorizontalSlider("Debug Tools/OLA Crossfade Size (samples)", &fHslider3, FAUSTFLOAT(256.0f), FAUSTFLOAT(128.0f), FAUSTFLOAT(512.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fHslider2, "4", "");
		ui_interface->addHorizontalSlider("Debug Tools/OLA Window Size (samples)", &fHslider2, FAUSTFLOAT(2048.0f), FAUSTFLOAT(1024.0f), FAUSTFLOAT(4096.0f), FAUSTFLOAT(1.0f));
		ui_interface->declare(&fCheckbox1, "4", "");
		ui_interface->addCheckButton("Debug Tools/Test Tone Enable", &fCheckbox1);
		ui_interface->declare(&fHslider1, "4", "");
		ui_interface->declare(&fHslider1, "unit", "Hz");
		ui_interface->addHorizontalSlider("Debug Tools/Test Tone Freq", &fHslider1, FAUSTFLOAT(4.4e+02f), FAUSTFLOAT(1e+02f), FAUSTFLOAT(1e+03f), FAUSTFLOAT(1.0f));
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
		float fSlow0 = std::pow(2.0f, 0.083333336f * (static_cast<float>(fEntry0) + -6e+01f));
		fHbargraph0 = static_cast<FAUSTFLOAT>(4.4e+02f * fSlow0);
		float fSlow1 = fHbargraph0;
		float fSlow2 = static_cast<float>(fHslider0);
		float fSlow3 = static_cast<float>(fCheckbox0);
		int iSlow4 = static_cast<int>(static_cast<float>(fCheckbox1));
		float fSlow5 = fConst0 * static_cast<float>(fHslider1);
		float fSlow6 = static_cast<float>(fCheckbox2);
		float fSlow7 = static_cast<float>(static_cast<int>(static_cast<float>(fHslider2)));
		float fSlow8 = 1.0f / static_cast<float>(static_cast<int>(static_cast<float>(fHslider3)));
		float fSlow9 = static_cast<float>(fCheckbox3);
		float fSlow10 = std::pow(2.0f, 0.083333336f * static_cast<float>(fHslider4));
		float fSlow11 = 1.0f - fSlow2;
		for (int i0 = 0; i0 < count; i0 = i0 + 1) {
			output0[i0] = static_cast<FAUSTFLOAT>(fSlow1);
			iVec1[0] = 1;
			float fTemp0 = ((1 - iVec1[1]) ? 0.0f : fSlow5 + fRec1[1]);
			fRec1[0] = fTemp0 - std::floor(fTemp0);
			float fTemp1 = 0.5f * ftbl0mydspSIG0[std::max<int>(0, std::min<int>(static_cast<int>(65536.0f * fRec1[0]), 65535))];
			float fTemp2 = ((iSlow4) ? fTemp1 : ((iSlow4) ? fTemp1 : static_cast<float>(input0[i0])));
			fVec2[IOTA0 & 131071] = fTemp2;
			fRec2[0] = std::fmod(fSlow7 + (fRec2[1] + 1.0f - fSlow0), fSlow7);
			int iTemp3 = static_cast<int>(fRec2[0]);
			float fTemp4 = std::floor(fRec2[0]);
			float fTemp5 = 1.0f - fRec2[0];
			float fTemp6 = std::min<float>(fSlow8 * fRec2[0], 1.0f);
			float fTemp7 = fSlow7 + fRec2[0];
			int iTemp8 = static_cast<int>(fTemp7);
			float fTemp9 = std::floor(fTemp7);
			fRec3[0] = std::fmod(fSlow7 + (fRec3[1] + 1.0f - fSlow10), fSlow7);
			int iTemp10 = static_cast<int>(fRec3[0]);
			float fTemp11 = std::floor(fRec3[0]);
			float fTemp12 = 1.0f - fRec3[0];
			float fTemp13 = std::min<float>(fSlow8 * fRec3[0], 1.0f);
			float fTemp14 = fSlow7 + fRec3[0];
			int iTemp15 = static_cast<int>(fTemp14);
			float fTemp16 = std::floor(fTemp14);
			float fTemp17 = fSlow2 * (fSlow3 * fTemp2 + fSlow6 * ((fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp3))) & 131071] * (fTemp4 + fTemp5) + (fRec2[0] - fTemp4) * fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp3 + 1))) & 131071]) * fTemp6 + (fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp8))) & 131071] * (fTemp9 + fTemp5 - fSlow7) + (fSlow7 + (fRec2[0] - fTemp9)) * fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp8 + 1))) & 131071]) * (1.0f - fTemp6)) + fSlow9 * ((fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp10))) & 131071] * (fTemp11 + fTemp12) + (fRec3[0] - fTemp11) * fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp10 + 1))) & 131071]) * fTemp13 + (fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp15))) & 131071] * (fTemp16 + fTemp12 - fSlow7) + (fSlow7 + (fRec3[0] - fTemp16)) * fVec2[(IOTA0 - std::min<int>(65537, std::max<int>(0, iTemp15 + 1))) & 131071]) * (1.0f - fTemp13))) + fSlow11 * fTemp2;
			output1[i0] = static_cast<FAUSTFLOAT>(fTemp17);
			output2[i0] = static_cast<FAUSTFLOAT>(fTemp17);
			iVec1[1] = iVec1[0];
			fRec1[1] = fRec1[0];
			IOTA0 = IOTA0 + 1;
			fRec2[1] = fRec2[0];
			fRec3[1] = fRec3[0];
		}
	}

};

#endif
