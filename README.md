# CD74HC4067

***STM32*** LL(Low Layer) library for the CD74HC4067 High Speed CMOS 16-Channel Analog Multiplexer/Demultiplexer.

### Features

- No HAL dependencies
- Lightweight design
- Easy to use

### Trade-offs

- Single GPIO port for all pins

<img src="https://github.com/ximtech/CD74HC4067/blob/main/example/view.PNG" alt="image" width="300"/>

### Add as CPM project dependency

How to add CPM to the project, check the [link](https://github.com/cpm-cmake/CPM.cmake)
```cmake
# For Clion STM32 plugin generated Cmake add
CPMAddPackage(
        NAME CD74HC4067
        GITHUB_REPOSITORY ximtech/CD74HC4067
        GIT_TAG origin/main)

include_directories(${CD74HC4067_DIRECTORY}) # add directory to project
file(GLOB_RECURSE SOURCES ${CD74HC4067_SOURCES}) # add source files
```

### Wiring

- <img src="https://github.com/ximtech/CD74HC4067/blob/main/example/wiring.PNG" alt="image" width="300"/>
- <img src="https://github.com/ximtech/CD74HC4067/blob/main/example/pin_config2.PNG" alt="image" width="300"/>

### Usage

***LED with multiplexer***
```c
    Multiplexer mux = initMultiplexer(GPIOA, MUX_S0_Pin, MUX_S1_Pin, MUX_S2_Pin, MUX_S3_Pin, MUX_ENABLE_Pin, MUX_SIGNAL_Pin);
    setEnableMultiplexer(&mux, true);   // by default disabled

    while (1) {
        writeMultiplexer(&mux, MUX_CHANNEL_0, MUX_HIGH);
        for (MultiplexerChannel i = MUX_CHANNEL_0; i < MUX_CHANNEL_15; i++) {
            LL_mDelay(100);
            writeMultiplexer(&mux, i, MUX_LOW);
            writeMultiplexer(&mux, i + 1, MUX_HIGH);
        }

        LL_mDelay(100);
        writeMultiplexer(&mux, MUX_CHANNEL_15, MUX_LOW);
    }
}
```

***Input data***
```c
    Multiplexer mux = initMultiplexer(GPIOA, MUX_S0_Pin, MUX_S1_Pin, MUX_S2_Pin, MUX_S3_Pin, MUX_ENABLE_Pin, 0);
    setEnableMultiplexer(&mux, true);
    setMultiplexerChannel(&mux, MUX_CHANNEL_1); // select channel
    uint32_t adcValue = readADC();  // use signal value
```