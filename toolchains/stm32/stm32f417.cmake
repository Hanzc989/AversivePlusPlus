cmake_minimum_required(VERSION 2.8)
cmake_policy(SET CMP0011 NEW)

set(AVERSIVE_TOOLCHAIN_STM32F417 1 CACHE STRING "")
set(AVERSIVE_TOOLCHAIN_MCU "stm32f417xx" CACHE STRING "")
include("${CMAKE_CURRENT_LIST_DIR}/stm32f4.cmake")

set(STM32F417XX_FLAGS "-DSTM32F417xx -s")
set(STM32F417XX_FLAGS "${STM32F417XX_FLAGS} -DAVERSIVE_TOOLCHAIN_STM32F417")

set(CMAKE_C_FLAGS      "${CMAKE_C_FLAGS} ${STM32F417XX_FLAGS}")
set(CMAKE_CXX_FLAGS    "${CMAKE_CXX_FLAGS} ${STM32F417XX_FLAGS}")
set(CMAKE_ASM_FLAGS    "${CMAKE_ASM_FLAGS} ${STM32F417XX_FLAGS}")

unset(STM32F417XX_FLAGS)
