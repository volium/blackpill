# Setup the build environment for Zephyr

# Zephyr build variables
export ZEPHYR_BASE=/Users/rot/git/zephyr_example/zephyr
export ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb
export GNUARMEMB_TOOLCHAIN_PATH=/opt/homebrew/

# Python environment needed to build
source /Users/rot/git/zephyr_example/zephyr_venv/bin/activate

# Main Zephyr environment setup
source ${ZEPHYR_BASE}/zephyr-env.sh