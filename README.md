# lorawan-basic-cookbook
step by step to interface your lorawan for any STM32 mcu &amp; SX1276
* 1, platform: STM32CubeIDE V1.3 or V1.2
    https://www.st.com/en/development-tools/stm32cubeide.html
- 2, initialize project by CUBEMX
- 3, RCC -> enable RCC HSE and LSE(for RTC)
    > go to Clock Configuration, set **LSE 32.768** source for RTC
- 4, RTC -> active RTC source, active Calender, 
    > **Hour Format = 24H**, **AsynchPrediv = 3**, **SynchPrediv = 3**;
    > **Calender time Format = BIN data**, **DaylightSaving OFF**, **Storeoperation RESET**;
    > **no alarm**
- 5, set 4 gpio *external interrupt* and rename as `LORA_D0`, `LORA_D1`, `LORA_D2`, `LORA_D3`, 
    > **go to NVIC, check related interrupt EXT line, make sure all EXT lines are not enabled**
- 6, set gpio reset pin `LORA_RST`, spi nss pin `LORA_NSS`, to **OUTPUT, PUSH-PULL, output HIGH**
- 7, set SPI, full-duplex master, 
    > use default 8-bit, MSB first, CPOL = LOW, CPHA = 1 Edge, use software NSS
    > change prescaller, set baudrate to **2 Mbits/s**
- 8, go to project setting -> code generator tab, tick `Generate peripheral initialization as a pair of ".c/.h" ...`
- 9, save and generate code
- 10, copy folder `mac`, `board`, `sx1276` to project root folder, copy `lorawan.h` to `Core/inc`, copy `lorawan.c` to `Core/src`
- 11, IDE -> project -> properties, go to `C/C++ general` -> `path and symbols`, 
    > go to `includes`, add -> input `mac`, then add `mac/crypto`, `board` and `sx1276`
    > go to `Source location`, add folder -> select `mac`, `board` and `sx1276`
    > go to `Symbols`, add name `USE_BAND_915`, the value just leave empty
    > apply, apply and close
- 12, edit `board.h`, check line `#include "stm32l1xx_hal.h"`, make sure it fits your stm32 mcu series, otherwise change it.
- 13, edit `main.c`
    > `#include "board.h"`
    > `#include "lorawan.h"`
    > add `static Gpio_t led1;` before **main()**
- 14, test gpio output functions
    > add `GpioInit( &led1, PB_8, PIN_OUTPUT, PIN_PUSH_PULL, PIN_NO_PULL, 0 );` before main while, (assume PB_8 control LED of your demo board)
    > add `GpioWrite(&led1, 1);`
    > compile and run the code, if the LED got light up, **congratilations! go to step 15**, otherwise fix errors
    > possible compile error issue: `GpioMcuSetInterrupt()` -> exi irq name and `Board_Init()` -> alarm irq name, different series of mcu got different interrupt definition, refer the stm32 header file.
- 15, test gpio interrupt functions, add code after `led1` definition,
    ```javascript
    static void keyCallback(void){
        GpioToggle(&led1);
    }
    static Gpio_t key;
    DioIrqHandler *keyHandler = keyCallback;
    ```
    add code after led1 initialization, assume PA_12 pin is input of your demo board
    ```javascript
    GpioInit( &key, PA_12, PIN_INPUT, PIN_PUSH_PULL, PIN_PULL_UP, 0 );
    GpioSetInterrupt( &key, IRQ_FALLING_EDGE, IRQ_HIGH_PRIORITY, keyHandler );
    ```
    > compile and run the code, if short pin PA_12 to GND, you will see led light flip, **congratilations! go to step 15**, otherwise fix errors
