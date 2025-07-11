/* 
 * File:   button.h
 *
 * Routines for handling push button
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <xc.h>

void button_pressed(void)
{
    // debounce, set button_state flag, enable timer interrupt to catch long press
    __delay_ms(30);
    button_state = 0;
    TMR1H = 0;
    TMR1L = 0;
    PIR1bits.TMR1IF = 0;
    PIE1bits.TMR1IE = 1;
    return;
}

void button_released(void)
{
    // disable timer interrupt (short press), debounce, set button_state flag, 
    PIE1bits.TMR1IE = 0;
    __delay_ms(30);     // debounce the change
    button_state = 1; 
    return;
}

void wait_release(void)
{
    // wait for release after a long press, debounce and set button_state
    while (PORTBbits.RB1 == 0) {} // wait for release
    __delay_ms(30);     // debounce button release
    button_state = 1;
    return;
}