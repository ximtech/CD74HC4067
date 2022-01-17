#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "main.h"

#define CD74HC4067_CHANNEL_COUNT 16

typedef enum MultiplexerChannel {
    MUX_CHANNEL_0,
    MUX_CHANNEL_1,
    MUX_CHANNEL_2,
    MUX_CHANNEL_3,
    MUX_CHANNEL_4,
    MUX_CHANNEL_5,
    MUX_CHANNEL_6,
    MUX_CHANNEL_7,
    MUX_CHANNEL_8,
    MUX_CHANNEL_9,
    MUX_CHANNEL_10,
    MUX_CHANNEL_11,
    MUX_CHANNEL_12,
    MUX_CHANNEL_13,
    MUX_CHANNEL_14,
    MUX_CHANNEL_15,
} MultiplexerChannel;

typedef enum MultiplexerValue {
    MUX_HIGH,
    MUX_LOW
} MultiplexerValue;

typedef struct Multiplexer {
    GPIO_TypeDef *GPIOx;
    uint32_t dataS0;
    uint32_t dataS1;
    uint32_t dataS2;
    uint32_t dataS3;
    uint32_t enablePin;
    uint32_t signalPin;
} Multiplexer;


Multiplexer initMultiplexer(GPIO_TypeDef *GPIOx, uint32_t dataS0, uint32_t dataS1, uint32_t dataS2, uint32_t dataS3, uint32_t enablePin, uint32_t signalPin);

void setEnableMultiplexer(Multiplexer *mux, bool isEnabled);
void writeMultiplexer(Multiplexer *mux, MultiplexerChannel channel, MultiplexerValue value);    // set signal pin to high or low level
void setMultiplexerChannel(Multiplexer *mux, MultiplexerChannel channel);