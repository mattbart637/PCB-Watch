/* 
 * File:   lcd.h
 *
 * Routines for LCD display
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <xc.h>

 void initializeLCD()
 {
     LCDPSbits.LP = 5;           // 49 Hz frame freq at TIMER1 and 1/4 mux
     LCDPSbits.WA = 1;           // Writing to LCDDATAn registers is allowed
     LCDPSbits.WFT = 0;          // Type-A phase changes within each common type
 
     LCDCONbits.LMUX = 0b11;     // 1/4 mux
     LCDCONbits.SLPEN = 0;       // Enable LCD driver in sleep
     LCDCONbits.CS = 0b01;       // Timer1 as LCD clock 
     
     LCDREFbits.LCDIRE = 1;      // Enable internal LCD reference ladder
     LCDREFbits.LCDIRS = 1;      // LCD Contract Control powered from output of FVR (3.072V)
     LCDREFbits.LCDIRI = 1;      // LCD FVR off in mode B
     
     LCDRLbits.LRLAP = 0b01;     // Power mode A - reference ladder medium power    
     LCDRLbits.LRLBP = 0b01;     // Power mode B - reference ladder low power
     LCDRLbits.LRLAT = 0b001;    // Mode A for 1 clock, Mode B for the remainder
     
     LCDCSTbits.LCDCST = 0b000;   // Max contrast for given reference ladder power mode
    
     // Enable LCD segments
     LCDSE0 = 0b00110110;        
     LCDSE1 = 0b00001111;
     
     // Clear all LCD registers
     LCDDATA0 = 0;
     LCDDATA1 = 0;
     LCDDATA3 = 0;
     LCDDATA4 = 0;
     LCDDATA6 = 0;
     LCDDATA7 = 0;
     LCDDATA9 = 0;
     LCDDATA10 = 0;
     
     LCDCONbits.LCDEN = 1;
     
     return;
 }
 
 void allLCD()
 {
     // Turn on all active segments
     LCDDATA0 = 0b00110110;
     LCDDATA1 = 0b00001111;
     LCDDATA3 = 0b00110110;
     LCDDATA4 = 0b00001111;        
     LCDDATA6 = 0b00110110;        
     LCDDATA7 = 0b00001111;        
     LCDDATA9 = 0b00110110;
     LCDDATA10 = 0b00001111;
     return;
 }
 
 void clearLCD()
  {
     // Turn off all active segments
     LCDDATA0 = 0;
     LCDDATA1 = 0;
     LCDDATA3 = 0;
     LCDDATA4 = 0;        
     LCDDATA6 = 0;        
     LCDDATA7 = 0;        
     LCDDATA9 = 0;
     LCDDATA10 = 0;
     return;
 }
 
 void digitsHM_LCD(void)
 {
     D4 = minutes % 10;
     D3 = (minutes / 10) % 10;
     D2 = hours % 10;
     D1 = (hours / 10) % 10;
     return;
 }
 
 void digitsMS_LCD(void)
  {
     D4 = seconds % 10;
     D3 = (seconds / 10) % 10;
     D2 = minutes % 10;
     D1 = (minutes / 10) % 10;
     return;
 }
 
 void updateLCD()
 {
     clearLCD();
     LCDDATA6bits.SEG1COM2 = 1; // Turn colon back on
     
     if (D4 == 0) 
     {LCDDATA0bits.SEG1COM0 = 1;
     LCDDATA3bits.SEG1COM1 = 1;
     LCDDATA9bits.SEG1COM3 = 1;
     LCDDATA0bits.SEG2COM0 = 1;
     LCDDATA6bits.SEG2COM2 = 1;
     LCDDATA9bits.SEG2COM3 = 1;}
     
     if (D4 == 1) 
     {LCDDATA3bits.SEG1COM1 = 1;
     LCDDATA9bits.SEG1COM3 = 1;}
     
     if (D4 == 2)
     {LCDDATA0bits.SEG1COM0 = 1;
     LCDDATA3bits.SEG1COM1 = 1;
     LCDDATA3bits.SEG2COM1 = 1;
     LCDDATA6bits.SEG2COM2 = 1;
     LCDDATA9bits.SEG2COM3 = 1;}
     
     if (D4 == 3)
     {LCDDATA0bits.SEG1COM0 = 1;
     LCDDATA3bits.SEG1COM1 = 1;
     LCDDATA9bits.SEG1COM3 = 1;
     LCDDATA3bits.SEG2COM1 = 1;
     LCDDATA6bits.SEG2COM2 = 1;}
     
     if (D4 == 4)
     {LCDDATA3bits.SEG1COM1 = 1;
     LCDDATA9bits.SEG1COM3 = 1;
     LCDDATA0bits.SEG2COM0 = 1;
     LCDDATA3bits.SEG2COM1 = 1;}
      
     if (D4 == 5)
     {LCDDATA0bits.SEG1COM0 = 1;
     LCDDATA9bits.SEG1COM3 = 1;
     LCDDATA0bits.SEG2COM0 = 1;
     LCDDATA3bits.SEG2COM1 = 1;
     LCDDATA6bits.SEG2COM2 = 1;}
     
     if (D4 == 6)
     {LCDDATA0bits.SEG1COM0 = 1;
     LCDDATA9bits.SEG1COM3 = 1;
     LCDDATA0bits.SEG2COM0 = 1;
     LCDDATA3bits.SEG2COM1 = 1;
     LCDDATA6bits.SEG2COM2 = 1;
     LCDDATA9bits.SEG2COM3 = 1;}
     
     if (D4 == 7)
     {LCDDATA0bits.SEG1COM0 = 1;
     LCDDATA3bits.SEG1COM1 = 1;
     LCDDATA9bits.SEG1COM3 = 1;}
     
     if (D4 == 8)
     {LCDDATA0bits.SEG1COM0 = 1;
     LCDDATA3bits.SEG1COM1 = 1;
     LCDDATA9bits.SEG1COM3 = 1;
     LCDDATA0bits.SEG2COM0 = 1;
     LCDDATA3bits.SEG2COM1 = 1;
     LCDDATA6bits.SEG2COM2 = 1;
     LCDDATA9bits.SEG2COM3 = 1;}
     
     if (D4 == 9)
     {LCDDATA0bits.SEG1COM0 = 1;
     LCDDATA3bits.SEG1COM1 = 1;
     LCDDATA9bits.SEG1COM3 = 1;
     LCDDATA0bits.SEG2COM0 = 1;
     LCDDATA3bits.SEG2COM1 = 1;}
     
     /////////////////////////////////////////////////////
     
     if (D3 == 0) 
     {LCDDATA0bits.SEG5COM0 = 1;
     LCDDATA3bits.SEG5COM1 = 1;
     LCDDATA9bits.SEG5COM3 = 1;
     LCDDATA0bits.SEG4COM0 = 1;
     LCDDATA6bits.SEG4COM2 = 1;
     LCDDATA9bits.SEG4COM3 = 1;}
     
     if (D3 == 1) 
     {LCDDATA3bits.SEG5COM1 = 1;
     LCDDATA9bits.SEG5COM3 = 1;}
     
     if (D3 == 2)
     {LCDDATA0bits.SEG5COM0 = 1;
     LCDDATA3bits.SEG5COM1 = 1;
     LCDDATA3bits.SEG4COM1 = 1;
     LCDDATA6bits.SEG4COM2 = 1;
     LCDDATA9bits.SEG4COM3 = 1;}
     
     if (D3 == 3)
     {LCDDATA0bits.SEG5COM0 = 1;
     LCDDATA3bits.SEG5COM1 = 1;
     LCDDATA9bits.SEG5COM3 = 1;
     LCDDATA3bits.SEG4COM1 = 1;
     LCDDATA6bits.SEG4COM2 = 1;}
     
     if (D3 == 4)
     {LCDDATA3bits.SEG5COM1 = 1;
     LCDDATA9bits.SEG5COM3 = 1;
     LCDDATA0bits.SEG4COM0 = 1;
     LCDDATA3bits.SEG4COM1 = 1;}
      
     if (D3 == 5)
     {LCDDATA0bits.SEG5COM0 = 1;
     LCDDATA9bits.SEG5COM3 = 1;
     LCDDATA0bits.SEG4COM0 = 1;
     LCDDATA3bits.SEG4COM1 = 1;
     LCDDATA6bits.SEG4COM2 = 1;}
     
     if (D3 == 6)
     {LCDDATA0bits.SEG5COM0 = 1;
     LCDDATA9bits.SEG5COM3 = 1;
     LCDDATA0bits.SEG4COM0 = 1;
     LCDDATA3bits.SEG4COM1 = 1;
     LCDDATA6bits.SEG4COM2 = 1;
     LCDDATA9bits.SEG4COM3 = 1;}
     
     if (D3 == 7)
     {LCDDATA0bits.SEG5COM0 = 1;
     LCDDATA3bits.SEG5COM1 = 1;
     LCDDATA9bits.SEG5COM3 = 1;}
     
     if (D3 == 8)
     {LCDDATA0bits.SEG5COM0 = 1;
     LCDDATA3bits.SEG5COM1 = 1;
     LCDDATA9bits.SEG5COM3 = 1;
     LCDDATA0bits.SEG4COM0 = 1;
     LCDDATA3bits.SEG4COM1 = 1;
     LCDDATA6bits.SEG4COM2 = 1;
     LCDDATA9bits.SEG4COM3 = 1;}
     
     if (D3 == 9)
     {LCDDATA0bits.SEG5COM0 = 1;
     LCDDATA3bits.SEG5COM1 = 1;
     LCDDATA9bits.SEG5COM3 = 1;
     LCDDATA0bits.SEG4COM0 = 1;
     LCDDATA3bits.SEG4COM1 = 1;}
     
     /////////////////////////////////////////////////////
     
     if (D2 == 0) 
     {LCDDATA1bits.SEG11COM0 = 1;
     LCDDATA4bits.SEG11COM1 = 1;
     LCDDATA10bits.SEG11COM3 = 1;
     LCDDATA1bits.SEG10COM0 = 1;
     LCDDATA7bits.SEG10COM2 = 1;
     LCDDATA10bits.SEG10COM3 = 1;}
     
     if (D2 == 1) 
     {LCDDATA4bits.SEG11COM1 = 1;
     LCDDATA10bits.SEG11COM3 = 1;}
     
     if (D2 == 2)
     {LCDDATA1bits.SEG11COM0 = 1;
     LCDDATA4bits.SEG11COM1 = 1;
     LCDDATA4bits.SEG10COM1 = 1;
     LCDDATA7bits.SEG10COM2 = 1;
     LCDDATA10bits.SEG10COM3 = 1;}
     
     if (D2 == 3)
     {LCDDATA1bits.SEG11COM0 = 1;
     LCDDATA4bits.SEG11COM1 = 1;
     LCDDATA10bits.SEG11COM3 = 1;
     LCDDATA4bits.SEG10COM1 = 1;
     LCDDATA7bits.SEG10COM2 = 1;}
     
     if (D2 == 4)
     {LCDDATA4bits.SEG11COM1 = 1;
     LCDDATA10bits.SEG11COM3 = 1;
     LCDDATA1bits.SEG10COM0 = 1;
     LCDDATA4bits.SEG10COM1 = 1;}
      
     if (D2 == 5)
     {LCDDATA1bits.SEG11COM0 = 1;
     LCDDATA10bits.SEG11COM3 = 1;
     LCDDATA1bits.SEG10COM0 = 1;
     LCDDATA4bits.SEG10COM1 = 1;
     LCDDATA7bits.SEG10COM2 = 1;}
     
     if (D2 == 6)
     {LCDDATA1bits.SEG11COM0 = 1;
     LCDDATA10bits.SEG11COM3 = 1;
     LCDDATA1bits.SEG10COM0 = 1;
     LCDDATA4bits.SEG10COM1 = 1;
     LCDDATA7bits.SEG10COM2 = 1;
     LCDDATA10bits.SEG10COM3 = 1;}
     
     if (D2 == 7)
     {LCDDATA1bits.SEG11COM0 = 1;
     LCDDATA4bits.SEG11COM1 = 1;
     LCDDATA10bits.SEG11COM3 = 1;}
     
     if (D2 == 8)
     {LCDDATA1bits.SEG11COM0 = 1;
     LCDDATA4bits.SEG11COM1 = 1;
     LCDDATA10bits.SEG11COM3 = 1;
     LCDDATA1bits.SEG10COM0 = 1;
     LCDDATA4bits.SEG10COM1 = 1;
     LCDDATA7bits.SEG10COM2 = 1;
     LCDDATA10bits.SEG10COM3 = 1;}
     
     if (D2 == 9)
     {LCDDATA1bits.SEG11COM0 = 1;
     LCDDATA4bits.SEG11COM1 = 1;
     LCDDATA10bits.SEG11COM3 = 1;
     LCDDATA1bits.SEG10COM0 = 1;
     LCDDATA4bits.SEG10COM1 = 1;}
     
     /////////////////////////////////////////////////////
     
     if (D1 == 0) {}                // Turn off leading zero completely
//     {LCDDATA1bits.SEG9COM0 = 1;
//     LCDDATA4bits.SEG9COM1 = 1;
//     LCDDATA10bits.SEG9COM3 = 1;
//     LCDDATA1bits.SEG8COM0 = 1;
//     LCDDATA7bits.SEG8COM2 = 1;
//     LCDDATA10bits.SEG8COM3 = 1;}
     
     if (D1 == 1) 
     {LCDDATA4bits.SEG9COM1 = 1;
     LCDDATA10bits.SEG9COM3 = 1;}
     
     if (D1 == 2)
     {LCDDATA1bits.SEG9COM0 = 1;
     LCDDATA4bits.SEG9COM1 = 1;
     LCDDATA4bits.SEG8COM1 = 1;
     LCDDATA7bits.SEG8COM2 = 1;
     LCDDATA10bits.SEG8COM3 = 1;}
     
     if (D1 == 3)
     {LCDDATA1bits.SEG9COM0 = 1;
     LCDDATA4bits.SEG9COM1 = 1;
     LCDDATA10bits.SEG9COM3 = 1;
     LCDDATA4bits.SEG8COM1 = 1;
     LCDDATA7bits.SEG8COM2 = 1;}
     
     if (D1 == 4)
     {LCDDATA4bits.SEG9COM1 = 1;
     LCDDATA10bits.SEG9COM3 = 1;
     LCDDATA1bits.SEG8COM0 = 1;
     LCDDATA4bits.SEG8COM1 = 1;}
      
     if (D1 == 5)
     {LCDDATA1bits.SEG9COM0 = 1;
     LCDDATA10bits.SEG9COM3 = 1;
     LCDDATA1bits.SEG8COM0 = 1;
     LCDDATA4bits.SEG8COM1 = 1;
     LCDDATA7bits.SEG8COM2 = 1;}
     
     if (D1 == 6)
     {LCDDATA1bits.SEG9COM0 = 1;
     LCDDATA10bits.SEG9COM3 = 1;
     LCDDATA1bits.SEG8COM0 = 1;
     LCDDATA4bits.SEG8COM1 = 1;
     LCDDATA7bits.SEG8COM2 = 1;
     LCDDATA10bits.SEG8COM3 = 1;}
     
     if (D1 == 7)
     {LCDDATA1bits.SEG9COM0 = 1;
     LCDDATA4bits.SEG9COM1 = 1;
     LCDDATA10bits.SEG9COM3 = 1;}
     
     if (D1 == 8)
     {LCDDATA1bits.SEG9COM0 = 1;
     LCDDATA4bits.SEG9COM1 = 1;
     LCDDATA10bits.SEG9COM3 = 1;
     LCDDATA1bits.SEG8COM0 = 1;
     LCDDATA4bits.SEG8COM1 = 1;
     LCDDATA7bits.SEG8COM2 = 1;
     LCDDATA10bits.SEG8COM3 = 1;}
     
     if (D1 == 9)
     {LCDDATA1bits.SEG9COM0 = 1;
     LCDDATA4bits.SEG9COM1 = 1;
     LCDDATA10bits.SEG9COM3 = 1;
     LCDDATA1bits.SEG8COM0 = 1;
     LCDDATA4bits.SEG8COM1 = 1;}
     
     /////////////////////////////////////////////////////
     
     if (DP3 == 1) {LCDDATA6bits.SEG5COM2 = 1;}
     if (DP1 == 1) {LCDDATA7bits.SEG9COM2 = 1;}
     
     return;
 }
 
 
 
 