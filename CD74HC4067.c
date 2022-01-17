#include "CD74HC4067.h"

#define BIT_READ(value, bit) (((value) >> (bit)) & 0x01)

static const uint8_t MUX_TRUTH_TABLE[CD74HC4067_CHANNEL_COUNT] = {
        0b00000000,
        0b00001000,
        0b00000100,
        0b00001100,
        0b00000010,
        0b00001010,
        0b00000110,
        0b00001110,
        0b00000001,
        0b00001001,
        0b00000101,
        0b00001101,
        0b00000011,
        0b00001011,
        0b00000111,
        0b00001111
};


Multiplexer initMultiplexer(GPIO_TypeDef *GPIOx, uint32_t dataS0, uint32_t dataS1, uint32_t dataS2, uint32_t dataS3, uint32_t enablePin, uint32_t signalPin) {
    Multiplexer mux = {0};
    mux.GPIOx = GPIOx;
    mux.dataS0 = dataS0;
    mux.dataS1 = dataS1;
    mux.dataS2 = dataS2;
    mux.dataS3 = dataS3;
    mux.enablePin = enablePin;
    mux.signalPin = signalPin;

    if (signalPin != 0) {
        LL_GPIO_ResetOutputPin(GPIOx, signalPin);
    }
    LL_GPIO_SetOutputPin(GPIOx, enablePin); // High level means disable input/output signal
    LL_GPIO_ResetOutputPin(GPIOx, dataS0 | dataS1 | dataS2 | dataS3);   // set all data pins low, by default channel 0 selected
    return mux;
}

void setEnableMultiplexer(Multiplexer *mux, bool isEnabled) {
    if (mux != NULL) {
        if (isEnabled) {
            LL_GPIO_ResetOutputPin(mux->GPIOx, mux->enablePin);
        } else {
            LL_GPIO_SetOutputPin(mux->GPIOx, mux->enablePin);
        }
    }
}

void writeMultiplexer(Multiplexer *mux, MultiplexerChannel channel, MultiplexerValue value) {
    if (mux->signalPin != 0) {
        setMultiplexerChannel(mux, channel);
        if (value == MUX_HIGH) {
            LL_GPIO_SetOutputPin(mux->GPIOx, mux->signalPin);
        } else {
            LL_GPIO_ResetOutputPin(mux->GPIOx, mux->signalPin);
        }
    }
}

void setMultiplexerChannel(Multiplexer *mux, MultiplexerChannel channel) {
    uint32_t pinMask = 0;
    uint8_t muxValue = MUX_TRUTH_TABLE[channel];
    pinMask |= (BIT_READ(muxValue, 3) ? mux->dataS0 : mux->dataS0 << 16);
    pinMask |= (BIT_READ(muxValue, 2) ? mux->dataS1 : mux->dataS1 << 16);
    pinMask |= (BIT_READ(muxValue, 1) ? mux->dataS2 : mux->dataS2 << 16);
    pinMask |= (BIT_READ(muxValue, 0) ? mux->dataS3 : mux->dataS3 << 16);
    LL_GPIO_SetOutputPin(mux->GPIOx, pinMask);
}