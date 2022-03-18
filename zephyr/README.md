# This project builds an application using Zephyr RTOS

## Build Instructions

In order to be able to build, the Zephyr environment needs to be setup.
Instead of using the "automated" build/dependency management system provided by Zephyr, called **West**, this project sets up all necessary build dependencies and repositories, explicitly.

In order to build, the following steps need to be followed:

1. The necessary git submodules need to be fetched/initialized: `git submodule update --init --recursive`
2. Go to the application folder you want to build (ie blinky), and simply run **build.sh**: `cd blinky; ./build.sh`

Under the hood, **build.sh** is *sourcing* the setup_env.sh script which sets up the necessary environment variables, including the Python virtual environment and its necessary packages; it then calls **CMake** with the appropriate board definition (**blackpill_f411ce**), and finally calls "make", which compiles and produces the actual binaries.

## Flashing instructions

### Using a ST-Link V2 dongle

- Via OpenOCD:

   `openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/zephyr/zephyr.bin reset exit 0x08000000"`

- Via PyOCD:

    `pyocd load build/zephyr/zephyr.hex --target stm32f411ce`

    `pyocd load build/zephyr/zephyr.elf --target stm32f411ce`

    `pyocd load build/zephyr/zephyr.bin@0x08000000 --target stm32f411ce`

### Using DFU bootloader

- Via dfu-util:

    `dfu-util -a 0 --dfuse-address 0x08000000:leave -D build/zephyr/zephyr.bin`

    - `-a 0` - Internal Flash alt setting of the DFU interface
    - `:leave` - Transition to main application (leave DFU)
