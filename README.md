## TommRo libraries

TommRo libraries are a portable C framework designed for microcontrollers (mainly ARM Cortex-M family), ESP32,...

They are compatible with ARM Cortex-M family (STM32, NXP, SiLabs,...), GCC and IAR compiler, ESP32 (Xtensa and RISC-V),...

```
1. tommRoC library.
   A set of common functionalities that can be used in firmware projects.
   
2. tommRoCHw - hardware - library.
   A set of common hardware functionalities (buses, bus devices, network, BLE,...) that can be used in firmware projects.
   
3. tommRoCMw - middleware - library.
   A set of common RTOS functionalities (thread, mutex,...) that can be used in firmware projects.
   
4. tommRoCSw - secure ware - library. Security and TLS functionalities.
```

```
.-------------------------------------------------------.
|                      Application                      |
'---|-----------|----------------|----------------|-----'
    |           |                |                |
    |     .-----|-----.    .-----|-----.    .-----|-----.
    |     | tommRoCHw |    | tommRoCMw |    | tommRoCSw |
    |     '-----|-----'    '-----|-----'    '-----|-----'
    |           |                |                |
.---|-----------|----------------|----------------|-----.
|                        tommRoC                        |
'-------------------------------------------------------'

.-------. .-----. .--------. .-------.  .-----------.  .----------.
| STM32 | | NXP | | SiLabs | | ESP32 |  | Baremetal |  | FreeRTOS |
'-------' '-----' '--------' '-------'  '-----------'  | ThreadX  |
                                                       | NXP_OSA  |
                                                       | pthread  |
                                                       '----------'
```

