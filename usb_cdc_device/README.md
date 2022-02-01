## Build Instructions

- `make <clean>`

## Run Instructions

- `screen /dev/cu.<USB_INSTANCE>`
- Characters typed should be echoed right back

## Flashing instructions

### Using a ST-Link V2 dongle

- Via OpenOCD:

   `openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/usb_cdc_device.bin reset exit 0x08000000"`

- Via PyOCD:

    `pyocd load build/usb_cdc_device.hex --target stm32f411ce`

    `pyocd load build/usb_cdc_device.elf --target stm32f411ce`

    `pyocd load build/usb_cdc_device.bin@0x08000000 --target stm32f411ce`

### Using DFU bootloader

- Via dfu-util:

    `dfu-util -a 0 --dfuse-address 0x08000000:leave -D build/usb_cdc_device.bin`

    - `-a 0` - Internal Flash alt setting of the DFU interface
    - `:leave` - Transition to main application (leave DFU)


## Debugging instructions

Debugging via OpenOCD and PyOCD is supported when using a ST-Link V2 dongle.

The "Cortex-Debug" VS Code Extension works correctly when using the two configurations (**"Debug (openocd)"** & **"Debug (pyocd)"**) in the `.vscode/launch.json` file.


## Using PyOCD for target inspection/control

See **pyocd_example.py** as a starting point.

**IMPORTANT NOTE:** When setting breakpoints, they are not actually set (flushed) until the target
is instructed to advance (via `step` or `resume`), so make sure to do that.
