# blackpill
Collection of examples working with STM32F411CEU6 Core Board (WeActTC/MiniSTM32F4x1)

## Toolchain installation

 - ### MacOS
    - Install [Homebrew](https://brew.sh/):

        `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`
    
    - Install the **gcc-arm-embedded** toolchain:
        
        - [Option 1](https://formulae.brew.sh/cask/gcc-arm-embedded): `brew install --cask gcc-arm-embedded`
        - [Option 2](https://github.com/osx-cross/homebrew-arm): `brew tap osx-cross/arm && brew install arm-gcc-bin`
        - [Option 3](https://github.com/ARMmbed/homebrew-formulae): `brew tap ArmMbed/homebrew-formulae && brew install arm-none-eabi-gcc`
    
            **NOTE:** Option 1 is listed on the official "Homebrew Formulae" directory. Option 2 comes from osx-cross team. Option 3 seems to be the "official" version, but it also tends to be the one that takes the longest to get updated.
    
    - Install **OpenOCD** which can be used to flash and debug:
            
        `brew install open-ocd --HEAD`

        **NOTE:** The [Cortex Debug](https://github.com/Marus/cortex-debug) VSCode extension recommends [installing from source](https://github.com/Marus/cortex-debug#installation), thus the `--HEAD` option. I did run into an issue on an M1 MacBook Pro when "poured from bottle" (installed from pre-built binaries).
    
    - Install **pyocd** which can be used to flash and debug:
            
        `python3 -m pip install pyocd`

        - Install the necessary "pack" to be able to interact with the device via **pyocd**:

            `pyocd pack install stm32f411`