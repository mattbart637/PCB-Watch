/*
 * File:   main.c
 * 
 * Button logic:
 * Modes cycle from normal operation, setting minutes, setting hours. Press and hold 
 * for 3 seconds to cycle between modes. Decimal points illuminate to indicate
 * which mode you're in.
 * 
 * If in minute/hours setting mode, short press to advance minutes/hours.
 */

// PIC16F1938 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Memory Code Protection (Data memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = OFF   // Clock Out Enable (CLKOUT function is disabled. I/O or oscillator function on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable (All VCAP pin functionality is disabled)
#pragma config PLLEN = OFF      // PLL Enable (4x PLL disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#define _XTAL_FREQ 500000
int D1 = 1;         // LCD digit 1 value
int D2 = 2;         // LCD digit 2 value
int D3 = 0;         // LCD digit 3 value
int D4 = 0;         // LCD digit 4 value
int DP1 = 0;        // Decimal Point 1 On/Off
int DP3 = 0;        // Decimal Point 3 On/Off
int seconds = 0;
int minutes = 0;
int hours = 12;
int set_mode = 0;       // 0 = timekeeping, 1 = set min, 2 = set hr
int long_press = 0;     // flag for when a long press (2s) is detected
int button_state = 1;   // capture button state, 0 is pressed
int tick = 0;           // temp variable used to count entrance into time setting mode

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "lcd.h"
#include "button.h"

void main(void) 
{
    // Button configuration
    TRISBbits.TRISB1 = 1;       // RB1 input
    ANSELBbits.ANSB1 = 0;       // RB1 digital
    OPTION_REGbits.nWPUEN = 0;  // Weak pull-ups are enabled by individual WPUx latch values
    WPUBbits.WPUB1 = 1;         // RB1 pullup enabled
    
    // Timer1 configuration
    T1CONbits.nT1SYNC = 1;      //Do not synchronize with system clock
    T1CONbits.T1CKPS0 = 0;      //1:1 prescale value 
    T1CONbits.T1CKPS1 = 0;
    T1CONbits.TMR1CS = 2;       //set oscillator as Timer1 source
    
    // Enable Timer1 count
    T1CONbits.TMR1ON = 1;       //enable Timer1
    T1GCONbits.TMR1GE = 1;      //enable Timer1 gate
    
    // Enable oscillator circuit with delay for startup time
    T1CONbits.T1OSCEN = 1;      //enable oscillator circuit
    PIR1bits.TMR1IF = 0;        //clear interrupt flag
    TMR1L = 0x00;
    TMR1H = 0xfc;
    
    // Interrupt configuration
    INTCONbits.GIE = 1;         // Global Interrupt Enable
    INTCONbits.PEIE = 1;        // Peripheral Interrupt Enable
    INTCONbits.IOCIE = 1;       // Interrupt-on-change enable
    PIE1bits.TMR1IE = 1;        // Timer1 Interrupt Enable
   
    // Turn on display
    initializeLCD();
    updateLCD();
    
    while(1)
    {        
        if (seconds == 60) 
        {
            seconds = 0; 
            minutes++; 
            if (minutes == 60) 
            {
               minutes = 0;
               hours++;
               if (hours == 13) 
               {
                   hours = 1;
               }
            }
            digitsHM_LCD();
            updateLCD();
        }

        switch(set_mode)
        {
            case 0:
                if (PORTBbits.RB1 == 0) {tick++;}
                else {tick = 0;}
                if (tick == 3)
                {
                    PIE1bits.TMR1IE = 0;
                    PIR1bits.TMR1IF = 0; // Clear Timer1 interrupt flag in PIR1 register
                    tick = 0; 
                    DP3 = 1;
                    DP1 = 0;
                    set_mode = 1; 
                    updateLCD();
                    wait_release();
                }
                else {SLEEP();}
                break;
            case 1:
                if (PORTBbits.RB1 == 0 && button_state == 1)
                {
                    button_pressed();
                }                    
                if (PORTBbits.RB1 == 1 && button_state == 0)
                {
                    button_released();
                    minutes++; if (minutes == 60) {minutes = 0;}
                    digitsHM_LCD();
                    updateLCD();
                }
                if (long_press == 1)
                {
                    long_press = 0;
                    set_mode = 2;
                    DP3 = 0;
                    DP1 = 1;
                    updateLCD();
                    wait_release();
                }
                break;
            case 2:
                if (PORTBbits.RB1 == 0 && button_state == 1) // pressed
                {
                    button_pressed();
                }    
                if (PORTBbits.RB1 == 1 && button_state == 0)   // released
                {
                    button_released();
                    hours++; if (hours == 13) {hours = 1;}
                    digitsHM_LCD();
                    updateLCD();
                }
                if (long_press == 1)
                {
                    long_press = 0;
                    set_mode = 0;
                    seconds = 0;
                    DP3 = 0;
                    DP1 = 0;
                    updateLCD();
                    TMR1L = 0;
                    TMR1H = 0b10000000;
                    PIR1bits.TMR1IF = 0;
                    PIE1bits.TMR1IE = 1;                    
                    wait_release();
                }
                break;
        }
    }
}

// Interrupt service routine
void __interrupt() isr()
{
    // 1 Second elapsed under normal timekeeping
    if (PIR1bits.TMR1IF == 1 && set_mode == 0)
    {
        seconds++;
        PIR1bits.TMR1IF = 0; // Clear Timer1 interrupt flag in PIR1 register
        TMR1H |= 0b10000000;       // Overflow 1 second later)
    }
    
    
    // Long-press timer expires
    if (PIR1bits.TMR1IF == 1 && set_mode != 0)
    {
        PIE1bits.TMR1IE = 0; // Disable interrupt, will be re-enabled in main loop
        PIR1bits.TMR1IF = 0; // Clear Timer1 interrupt flag in PIR1 register
        long_press = 1;
    }
}


