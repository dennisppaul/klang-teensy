//
// ExampleKlangTeensyAudio
//

/*
  this example demonstrates how to integrate the *Klang* library into the Teensy Audio Library.
*/

#include <Audio.h>

#define KLANG_EXT_NODE_REVERB
#include <KlangTeensy.h>
#include <Nodes.hpp>

using namespace klang;

NodeVCOFunction mVCO;
NodeADSR        mADSR;
NodeReverb      mReverb;
NodeDAC         mDAC;

/* integrate `KlangTeensy` like any other audio object */
KlangTeensy             mKlangTeensy;
AudioOutputI2S          i2s1;
AudioControlSGTL5000    sgtl5000_1;
AudioConnection         patchCord1(mKlangTeensy, 0, i2s1, 0);
AudioConnection         patchCord2(mKlangTeensy, 0, i2s1, 1);

int     mLED = 13;
float   mFreq = 220;
int     mFreqCounter = 0;

void setup() {
  Serial.begin(115200);
  /* wait for virtual serial port … note that the sketch will not start before the connection is established. */
  while (!Serial);

  /* check if the audio blocks’ sizes match. if not they need to be changed in the header files of either *Klang* or *Teensy Audio* */
  if (AUDIO_BLOCK_SAMPLES != KLANG_SAMPLES_PER_AUDIO_BLOCK * 2 ) {
    Serial.println("### WARNING change `KlangstromDefines.hpp` (Klang) or `AudioStream.h` (Teensy) to make `AUDIO_BLOCK_SAMPLES == KLANG_SAMPLES_PER_AUDIO_BLOCK * 2");
  }

  pinMode(mLED, OUTPUT);

  /* --- teensy audio setup --- */
  AudioMemory(10);
  AudioNoInterrupts();
  sgtl5000_1.enable();
  sgtl5000_1.volume(0.85); // @TODO("SGTL5000 might need extra configuration")
  AudioInterrupts();

  /* --- klang setup --- */
  Klang::lock();

  Klang::connect(mVCO,    Node::CH_OUT_SIGNAL,  mADSR,   Node::CH_IN_SIGNAL);
  Klang::connect(mADSR,   Node::CH_OUT_SIGNAL,  mReverb, NodeDAC::CH_IN_SIGNAL_LEFT);
  Klang::connect(mReverb, Node::CH_OUT_SIGNAL,  mDAC,    NodeDAC::CH_IN_SIGNAL_LEFT);

  mVCO.set_frequency(440);
  mVCO.set_amplitude(0.75);
  mVCO.set_waveform(NodeVCOFunction::WAVEFORM::SAWTOOTH);

  mADSR.set_attack(0.001);
  mADSR.set_decay(0.01);
  mADSR.set_sustain(0.5);
  mADSR.set_release(0.25);

  Klang::unlock();
}

void loop() {
  digitalWrite(mLED, HIGH);
  mADSR.start();
  delay(125);
  digitalWrite(mLED, LOW);
  mADSR.stop();
  delay(125);
  mVCO.set_frequency(mFreq + mFreq * mFreqCounter);
  mFreqCounter++;
  mFreqCounter %= 4;
}

void audioblock_transmit(SIGNAL_TYPE* pLeft, SIGNAL_TYPE* pRight) {
  mDAC.process_frame(pLeft, pRight);
}
