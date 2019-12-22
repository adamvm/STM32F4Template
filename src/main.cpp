#include "stm32f4xx.h"
#include <vector>

#define Button_PIN GPIO_Pin_0

#define GREEN_PIN GPIO_Pin_12
#define ORANGE_PIN GPIO_Pin_13
#define RED_PIN GPIO_Pin_14
#define BLUE_PIN GPIO_Pin_15

void SetupLedPins();

void SetupButtonPin();

void Delay(volatile unsigned);

void InitializeGpio();

void InitializeClocks();

void EventLoop();

void TurnOnPin(uint16_t Pin);

void TurnOffPin(uint16_t Pin);

void ToglePin(uint16_t Pin);

extern "C" int main() {
    InitializeClocks();

    InitializeGpio();

    TurnOnPin(GREEN_PIN);

    std::vector<int> abc(10000, 33);

    EventLoop();

    return 0;
}

void EventLoop() {
    while (true) {
        TurnOnPin(BLUE_PIN);
        Delay(1e6);
        TurnOffPin(BLUE_PIN);
        Delay(1e6);
        ToglePin(ORANGE_PIN);
        if(GPIO_ReadInputDataBit(GPIOA, Button_PIN) == Bit_SET) {
            TurnOnPin(RED_PIN);
        } else {
            TurnOffPin(RED_PIN);
        }
    };
}

void TurnOnPin(uint16_t Pin) { GPIO_WriteBit(GPIOD, Pin, Bit_SET); }

void TurnOffPin(uint16_t Pin) { GPIO_WriteBit(GPIOD, Pin, Bit_RESET); }

void ToglePin(uint16_t Pin) { GPIO_ToggleBits(GPIOD, Pin); }
void InitializeClocks() {
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
}

void InitializeGpio() {
    SetupLedPins();
    SetupButtonPin();
}

void Delay(volatile unsigned count) {
    while (count--);
}

void SetupLedPins() {
    GPIO_InitTypeDef gpio_out = {
            .GPIO_Pin = GREEN_PIN | BLUE_PIN | RED_PIN | ORANGE_PIN,
            .GPIO_Mode = GPIO_Mode_OUT,
            .GPIO_Speed = GPIO_High_Speed,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd = GPIO_PuPd_NOPULL
    };
    GPIO_Init(GPIOD, &gpio_out);
}

void SetupButtonPin() {
    GPIO_InitTypeDef gpio_in = {
            .GPIO_Pin = Button_PIN,
            .GPIO_Mode = GPIO_Mode_IN,
            .GPIO_Speed = GPIO_High_Speed,
            .GPIO_OType = GPIO_OType_PP,
            .GPIO_PuPd = GPIO_PuPd_NOPULL
    };
    GPIO_Init(GPIOA, &gpio_in);
}