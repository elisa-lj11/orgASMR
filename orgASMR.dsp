// "orgASMR" Faust code
// Created by Elisa Lupin-Jimenez

import("stdfaust.lib");

// input from flex sensor
freq = hslider("freq[midi: ctrl 8]",261.6,130.82,523.25,0.01) : si.smoo;
// input from potentiometer
gain = hslider("gain[midi: ctrl 9]",0.5,0,1,0.01) : si.smoo;
// input from button
gate = hslider("gate[midi: ctrl 10]",0,0,127,1)>0;

// eight chord options determined by accelerometer
maj = hslider("major[midi: ctrl 0]",0,0,127,1)>0 : si.smoo;
minor = hslider("minor[midi: ctrl 1]",0,0,127,1)>0 : si.smoo;
dim = hslider("diminished[midi: ctrl 2]",0,0,127,1)>0 : si.smoo;
maj7 = hslider("major7[midi: ctrl 3]",0,0,127,1)>0 : si.smoo;
min7 = hslider("minor7[midi: ctrl 4]",0,0,127,1)>0 : si.smoo;
dom7 = hslider("dom7[midi: ctrl 5]",0,0,127,1)>0 : si.smoo;
sus = hslider("suspended[midi: ctrl 6]",0,0,127,1)>0 : si.smoo;
aug = hslider("augmented[midi: ctrl 7]",0,0,127,1)>0 : si.smoo;

// chord building with frequency from flex sensor
majChord = (os.osc(freq) + os.osc(freq*1.259921) + os.osc(freq*1.498307))/3;
minChord = (os.osc(freq) + os.osc(freq*1.189207) + os.osc(freq*1.498307))/3;
dimChord = (os.osc(freq) + os.osc(freq*1.189207) + os.osc(freq*1.414214) + os.osc(freq*1.681793))/4;
maj7Chord = (os.osc(freq) + os.osc(freq*1.259921) + os.osc(freq*1.498307) + os.osc(freq*1.887749))/4;
min7Chord = (os.osc(freq) + os.osc(freq*1.189207) + os.osc(freq*1.498307) + os.osc(freq*1.781797))/4;
dom7Chord = (os.osc(freq) + os.osc(freq*1.259921) + os.osc(freq*1.498307) + os.osc(freq*1.781797))/4;
susChord = (os.osc(freq) + os.osc(freq*1.334840) + os.osc(freq*1.498307))/3;
augChord = (os.osc(freq) + os.osc(freq*1.259921) + os.osc(freq*1.587401))/3;

// output
process = en.asr(0.5,1,0.5,gate) * ((maj*majChord + minor*minChord + dim*dimChord + maj7*majChord + min7*min7Chord + dom7*dom7Chord + sus*susChord + aug*augChord) * gain);
			
