#ifndef KLANG_TEENSY_H
#define KLANG_TEENSY_H

#include <Audio.h>
#include "Klang.hpp"

extern void audioblock_transmit(SIGNAL_TYPE* pLeft, SIGNAL_TYPE* pRight);

class KlangTeensy : public AudioStream {
  private:
    SIGNAL_TYPE  mLeftTX[KLANG_SAMPLES_PER_AUDIO_BLOCK];
    SIGNAL_TYPE mRightTX[KLANG_SAMPLES_PER_AUDIO_BLOCK];

  public:

    KlangTeensy() : AudioStream(0, NULL) {
      //@TODO(check if AUDIO_BLOCK_SAMPLES == KLANG_SAMPLES_PER_AUDIO_BLOCK*2)
    }

    void update(void) {
      audio_block_t *block;
      block = allocate();

      if (block == NULL) {
        return;
      }

      audioblock_transmit(mLeftTX, mRightTX);

      for (uint32_t i = 0; i < AUDIO_BLOCK_SAMPLES; i += 2) {
        block->data[i + 0] = (  mLeftTX[i / 2] + 1.0 ) * (1 << 14);
        block->data[i + 1] = ( mRightTX[i / 2] + 1.0 ) * (1 << 14);
      }

      transmit(block);
      release(block);
    }

};

#endif // KLANG_TEENSY_H
