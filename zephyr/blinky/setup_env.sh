# Setup the build environment for Zephyr

# Zephyr build variables
export ZEPHYR_BASE=/Users/rot/git/zephyr_example/zephyr
export ZEPHYR_TOOLCHAIN_VARIANT=gnuarmemb
export GNUARMEMB_TOOLCHAIN_PATH=/opt/homebrew/

# Python environment needed to build
if [[ -z "${VIRTUAL_ENV}" ]]; then
    # There's no VIRTUAL_ENV defined, check if we can activate an existing virtualenv
    SCRIPT_LOCATION=$(realpath $0)
    APP_DIR=$(dirname "$SCRIPT_LOCATION")
    ZEPHYR_DIR=$(dirname "$APP_DIR")
    PYTHON_VENV_LOCATION=$ZEPHYR_DIR/zephyr_venv
    PYTHON_VENV_ACTIVATE_LOCATION=$PYTHON_VENV_LOCATION/bin/activate

    if [[ -f "$PYTHON_VENV_ACTIVATE_LOCATION" ]]; then
        # Python virtualenv exists, so just source the "activate" script
        source $PYTHON_VENV_ACTIVATE_LOCATION
    else
        # Python virtualenv does not exist, create it and source the activate script
        python3.10 -m venv $PYTHON_VENV_LOCATION
        source $PYTHON_VENV_ACTIVATE_LOCATION
        pip install -r $APP_DIR/requirements.txt
    fi
fi

# Main Zephyr environment setup
source ${ZEPHYR_BASE}/zephyr-env.sh