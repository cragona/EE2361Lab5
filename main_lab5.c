/*
 * File:   main_lab5.c
 * Author: crago
 *
 * Created on March 20, 2018, 2:59 PM
 */


#include "xc.h"
#include <p24Fxxxx.h>
#include <stdio.h>
#include <string.h>
#include "lcdlib.h"


// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1 // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME // Clock Switching and Monitor (Clock switching is enabled,


// Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void setup(void)
{
    CLKDIVbits.RCDIV = 0;
    AD1PCFG = 0x9fff;
    TRISBbits.TRISB5 = 0;

    
    //i2c setup
    I2C2CONbits.I2CEN = 0; //disable
    I2C2BRG = 0x9D; //100 kHz
    I2C2CONbits.I2CEN = 1; //enable
    _MI2C2IF = 0;
    
    //TIMER SETUP
    T1CON = 0;
    PR1 = 15999;
    TMR1 = 0;
    IFS0bits.T1IF = 0;
    T1CONbits.TON = 1; 
}

int main(void) {
    setup();
    lcdinit(); 
    lcdSetCursor(0,0);
    
    lcdString("Jennifer and Charles's lab 5 demo.");
  
    while(1)
    {
        int i;
    
        for(i = 0; i < 350; i++) //delay for 350ms
        {
            while(!IFS0bits.T1IF);
            IFS0bits.T1IF = 0;
        }
        
        lcd_cmd(0b00011000); //scroll command
        LATBbits.LATB5 ^= 1; //heartbeat led
    }
    return 0;
}
