cmake_minimum_required(VERSION 3.13.1)

set(ZEPHYR_MODULES /Users/rot/git/zephyr_example/hal_stm32;/Users/rot/git/zephyr_example/cmsis)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(blinky)

target_sources(app PRIVATE src/main.c)