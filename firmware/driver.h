#pragma once

#include "ch32fun.h"
#include "oled_min.h"

/**
 * Driver for the game of the badge 44con here comes where it detects the buttons and oled
 * 
 * This functions are adapted for the games from this repository https://github.com/wagiminator/CH32V003-GameConsole
 */

// Buttons in the badge
#define BUTTON_UP       PD2
#define BUTTON_DOWN     PC6
#define BUTTON_LEFT     PC7 
#define BUTTON_RIGHT    PD3

#ifdef __cplusplus
extern "C" {
#endif

#define JOY_OLED_init             OLED_init
#define JOY_OLED_end              I2C_stop
#define JOY_OLED_send(b)          I2C_write(b)
#define JOY_OLED_send_command(c)  OLED_send_command(c)
#define JOY_OLED_data_start(y)    {OLED_setpos(0,y);OLED_data_start();}

// Function to start the gpios and oled for the badge
void JOY_init(void){

    // Init the system
    SystemInit();

    // Init ports
    funGpioInitAll();

    // Set buttons config
    funPinMode(BUTTON_DOWN,   GPIO_CNF_IN_PUPD);
    funPinMode(BUTTON_RIGHT,   GPIO_CNF_IN_PUPD);
    funPinMode(BUTTON_LEFT, GPIO_CNF_IN_PUPD);
    funPinMode(BUTTON_UP,     GPIO_CNF_IN_PUPD);

    // Init buttons
    funDigitalWrite(BUTTON_DOWN,1);
    funDigitalWrite(BUTTON_RIGHT,1);
    funDigitalWrite(BUTTON_LEFT,1);
    funDigitalWrite(BUTTON_UP,1);

    // Init Oled
    OLED_init();
}

#define JOY_act_pressed()   1 //(!funDigitalRead(BUTTON_RIGHT))

uint8_t JOY_up_pressed(void){
    return funDigitalRead(BUTTON_UP);
}

uint8_t JOY_down_pressed(void){
    return funDigitalRead(BUTTON_DOWN);
}

uint8_t JOY_left_pressed(void){
    return funDigitalRead(BUTTON_LEFT);
}

uint8_t JOY_right_pressed(void){
    return funDigitalRead(BUTTON_RIGHT);
}


#define JOY_DLY_ms(n)   Delay_Ms(n)
#define JOY_DLY_us(n)   Delay_Us(n)

#define JOY_SLOWDOWN()    Delay_Ms(20)

// Pseudo random number generator
uint16_t rnval = 0xACE1;
uint16_t JOY_random(void) {
  rnval = (rnval >> 0x01) ^ (-(rnval & 0x01) & 0xB400);
  return rnval;
}

// Buzzer
void JOY_sound(uint8_t freq, uint8_t dur) {
    #if JOY_SOUND 
    while(dur--) {
        DLY_us(255 - freq);
        PIN_high(PIN_BEEP);
        DLY_us(255 - freq);
    }
    #endif
}

#ifdef __cplusplus
};
#endif