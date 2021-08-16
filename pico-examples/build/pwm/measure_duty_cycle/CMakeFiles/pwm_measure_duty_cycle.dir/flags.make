# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# compile ASM with /usr/bin/arm-none-eabi-gcc
# compile C with /usr/bin/arm-none-eabi-gcc
# compile CXX with /usr/bin/arm-none-eabi-g++
ASM_FLAGS = -mcpu=cortex-m0plus -mthumb -O3 -DNDEBUG   -Wall -Wno-format -Wno-unused-function -Wno-maybe-uninitialized -ffunction-sections -fdata-sections

ASM_DEFINES = -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDIO_UART=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CORE=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UTIL=1 -DPICO_BOARD=\"pico\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Release\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_PROGRAM_URL=\"https://github.com/raspberrypi/pico-examples/tree/HEAD/pwm/measure_duty_cycle\" -DPICO_TARGET_NAME=\"pwm_measure_duty_cycle\" -DPICO_USE_BLOCKED_RAM=0

ASM_INCLUDES = -I/home/kang/tmp/pico/pico-sdk/src/common/pico_stdlib/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_gpio/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_base/include -I/home/kang/tmp/pico/pico-examples/build/generated/pico_base -I/home/kang/tmp/pico/pico-sdk/src/boards/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_platform/include -I/home/kang/tmp/pico/pico-sdk/src/rp2040/hardware_regs/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_base/include -I/home/kang/tmp/pico/pico-sdk/src/rp2040/hardware_structs/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_claim/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_sync/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_uart/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_divider/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_time/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_timer/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_sync/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_util/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_runtime/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_clocks/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_irq/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_resets/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_pll/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_vreg/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_watchdog/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_xosc/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_printf/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_bootrom/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_bit_ops/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_divider/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_double/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_int64_ops/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_float/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_malloc/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/boot_stage2/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_binary_info/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_stdio/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_stdio_uart/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_pwm/include 

C_FLAGS = -mcpu=cortex-m0plus -mthumb -O3 -DNDEBUG   -Wall -Wno-format -Wno-unused-function -Wno-maybe-uninitialized -ffunction-sections -fdata-sections -std=gnu11

C_DEFINES = -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDIO_UART=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CORE=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UTIL=1 -DPICO_BOARD=\"pico\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Release\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_PROGRAM_URL=\"https://github.com/raspberrypi/pico-examples/tree/HEAD/pwm/measure_duty_cycle\" -DPICO_TARGET_NAME=\"pwm_measure_duty_cycle\" -DPICO_USE_BLOCKED_RAM=0

C_INCLUDES = -I/home/kang/tmp/pico/pico-sdk/src/common/pico_stdlib/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_gpio/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_base/include -I/home/kang/tmp/pico/pico-examples/build/generated/pico_base -I/home/kang/tmp/pico/pico-sdk/src/boards/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_platform/include -I/home/kang/tmp/pico/pico-sdk/src/rp2040/hardware_regs/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_base/include -I/home/kang/tmp/pico/pico-sdk/src/rp2040/hardware_structs/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_claim/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_sync/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_uart/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_divider/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_time/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_timer/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_sync/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_util/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_runtime/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_clocks/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_irq/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_resets/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_pll/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_vreg/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_watchdog/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_xosc/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_printf/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_bootrom/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_bit_ops/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_divider/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_double/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_int64_ops/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_float/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_malloc/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/boot_stage2/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_binary_info/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_stdio/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_stdio_uart/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_pwm/include 

CXX_FLAGS = -mcpu=cortex-m0plus -mthumb -O3 -DNDEBUG   -Wall -Wno-format -Wno-unused-function -Wno-maybe-uninitialized -ffunction-sections -fdata-sections -fno-exceptions -fno-unwind-tables -fno-rtti -fno-use-cxa-atexit -std=gnu++17

CXX_DEFINES = -DLIB_PICO_BIT_OPS=1 -DLIB_PICO_BIT_OPS_PICO=1 -DLIB_PICO_DIVIDER=1 -DLIB_PICO_DIVIDER_HARDWARE=1 -DLIB_PICO_DOUBLE=1 -DLIB_PICO_DOUBLE_PICO=1 -DLIB_PICO_FLOAT=1 -DLIB_PICO_FLOAT_PICO=1 -DLIB_PICO_INT64_OPS=1 -DLIB_PICO_INT64_OPS_PICO=1 -DLIB_PICO_MALLOC=1 -DLIB_PICO_MEM_OPS=1 -DLIB_PICO_MEM_OPS_PICO=1 -DLIB_PICO_PLATFORM=1 -DLIB_PICO_PRINTF=1 -DLIB_PICO_PRINTF_PICO=1 -DLIB_PICO_RUNTIME=1 -DLIB_PICO_STANDARD_LINK=1 -DLIB_PICO_STDIO=1 -DLIB_PICO_STDIO_UART=1 -DLIB_PICO_STDLIB=1 -DLIB_PICO_SYNC=1 -DLIB_PICO_SYNC_CORE=1 -DLIB_PICO_SYNC_CRITICAL_SECTION=1 -DLIB_PICO_SYNC_MUTEX=1 -DLIB_PICO_SYNC_SEM=1 -DLIB_PICO_TIME=1 -DLIB_PICO_UTIL=1 -DPICO_BOARD=\"pico\" -DPICO_BUILD=1 -DPICO_CMAKE_BUILD_TYPE=\"Release\" -DPICO_COPY_TO_RAM=0 -DPICO_CXX_ENABLE_EXCEPTIONS=0 -DPICO_NO_FLASH=0 -DPICO_NO_HARDWARE=0 -DPICO_ON_DEVICE=1 -DPICO_PROGRAM_URL=\"https://github.com/raspberrypi/pico-examples/tree/HEAD/pwm/measure_duty_cycle\" -DPICO_TARGET_NAME=\"pwm_measure_duty_cycle\" -DPICO_USE_BLOCKED_RAM=0

CXX_INCLUDES = -I/home/kang/tmp/pico/pico-sdk/src/common/pico_stdlib/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_gpio/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_base/include -I/home/kang/tmp/pico/pico-examples/build/generated/pico_base -I/home/kang/tmp/pico/pico-sdk/src/boards/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_platform/include -I/home/kang/tmp/pico/pico-sdk/src/rp2040/hardware_regs/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_base/include -I/home/kang/tmp/pico/pico-sdk/src/rp2040/hardware_structs/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_claim/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_sync/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_uart/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_divider/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_time/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_timer/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_sync/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_util/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_runtime/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_clocks/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_irq/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_resets/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_pll/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_vreg/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_watchdog/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_xosc/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_printf/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_bootrom/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_bit_ops/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_divider/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_double/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_int64_ops/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_float/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_malloc/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/boot_stage2/include -I/home/kang/tmp/pico/pico-sdk/src/common/pico_binary_info/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_stdio/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/pico_stdio_uart/include -I/home/kang/tmp/pico/pico-sdk/src/rp2_common/hardware_pwm/include 

