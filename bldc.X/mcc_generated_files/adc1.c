/**
  ADC1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.c

  @Summary
    This is the generated driver implementation file for the ADC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for ADC1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  dsPIC33CK256MP508      
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "adc1.h"

/**
 Section: File specific functions
*/

static void (*ADC1_CommonDefaultInterruptHandler)(void);
static void (*ADC1_channel_AN15DefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_channel_AN19DefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_channel_AN20DefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_channel_AN21DefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_channel_AN22DefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_channel_AN24DefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_channel_AN25DefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_channel_AN0DefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_channel_ANA1DefaultInterruptHandler)(uint16_t adcVal);

/**
  Section: Driver Interface
*/

void ADC1_Initialize (void)
{
    // ADSIDL disabled; ADON enabled; 
    ADCON1L = (0x8000 & 0x7FFF); //Disabling ADON bit
    // FORM Integer; SHRRES 12-bit resolution; 
    ADCON1H = 0x60;
    // PTGEN disabled; SHRADCS 2; REFCIE disabled; SHREISEL Early interrupt is generated 1 TADCORE clock prior to data being ready; REFERCIE disabled; EIEN disabled; 
    ADCON2L = 0x00;
    // SHRSAMC 15; 
    ADCON2H = 0x0F;
    // SWCTRG disabled; SHRSAMP disabled; SUSPEND disabled; SWLCTRG disabled; SUSPCIE disabled; CNVCHSEL AN0; REFSEL disabled; 
    ADCON3L = 0x00;
    // SHREN enabled; C1EN enabled; C0EN enabled; CLKDIV 1; CLKSEL FOSC/2; 
    ADCON3H = (0x83 & 0xFF00); //Disabling C0EN, C1EN, C2EN, C3EN and SHREN bits
    // SAMC0EN disabled; SAMC1EN disabled; 
    ADCON4L = 0x00;
    // C0CHS AN0; C1CHS ANA1; 
    ADCON4H = 0x04;
    // SIGN0 disabled; SIGN4 disabled; SIGN3 disabled; SIGN2 disabled; SIGN1 disabled; SIGN7 disabled; SIGN6 disabled; DIFF0 disabled; SIGN5 disabled; DIFF1 disabled; DIFF2 disabled; DIFF3 disabled; DIFF4 disabled; DIFF5 disabled; DIFF6 disabled; DIFF7 disabled; 
    ADMOD0L = 0x00;
    // DIFF15 disabled; DIFF14 disabled; SIGN8 disabled; DIFF13 disabled; SIGN14 disabled; DIFF12 disabled; SIGN15 disabled; DIFF11 disabled; DIFF10 disabled; SIGN9 disabled; DIFF8 disabled; DIFF9 disabled; SIGN10 disabled; SIGN11 disabled; SIGN12 disabled; SIGN13 disabled; 
    ADMOD0H = 0x00;
    // DIFF19 disabled; DIFF18 disabled; DIFF17 disabled; DIFF16 disabled; DIFF23 disabled; SIGN16 disabled; DIFF22 disabled; SIGN17 disabled; DIFF21 disabled; SIGN18 disabled; DIFF20 disabled; SIGN19 disabled; SIGN20 disabled; SIGN21 disabled; SIGN22 disabled; SIGN23 disabled; 
    ADMOD1L = 0x00;
    // SIGN24 disabled; DIFF25 disabled; DIFF24 disabled; SIGN25 disabled; 
    ADMOD1H = 0x00;
    // IE15 disabled; IE1 disabled; IE0 disabled; IE3 disabled; IE2 disabled; IE5 disabled; IE4 disabled; IE10 disabled; IE7 disabled; IE6 disabled; IE9 disabled; IE13 disabled; IE8 disabled; IE14 disabled; IE11 disabled; IE12 disabled; 
    ADIEL = 0x00;
    // IE17 disabled; IE18 disabled; IE16 disabled; IE19 disabled; IE20 disabled; IE21 disabled; IE24 enabled; IE25 enabled; IE22 enabled; IE23 disabled; 
    ADIEH = 0x340;
    // CMPEN10 disabled; CMPEN11 disabled; CMPEN6 disabled; CMPEN5 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN14 disabled; CMPEN9 disabled; CMPEN15 disabled; CMPEN8 disabled; CMPEN12 disabled; CMPEN7 disabled; CMPEN13 disabled; 
    ADCMP0ENL = 0x00;
    // CMPEN10 disabled; CMPEN11 disabled; CMPEN6 disabled; CMPEN5 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN14 disabled; CMPEN9 disabled; CMPEN15 disabled; CMPEN8 disabled; CMPEN12 disabled; CMPEN7 disabled; CMPEN13 disabled; 
    ADCMP1ENL = 0x00;
    // CMPEN10 disabled; CMPEN11 disabled; CMPEN6 disabled; CMPEN5 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN14 disabled; CMPEN9 disabled; CMPEN15 disabled; CMPEN8 disabled; CMPEN12 disabled; CMPEN7 disabled; CMPEN13 disabled; 
    ADCMP2ENL = 0x00;
    // CMPEN10 disabled; CMPEN11 disabled; CMPEN6 disabled; CMPEN5 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN14 disabled; CMPEN9 disabled; CMPEN15 disabled; CMPEN8 disabled; CMPEN12 disabled; CMPEN7 disabled; CMPEN13 disabled; 
    ADCMP3ENL = 0x00;
    // CMPEN21 disabled; CMPEN22 disabled; CMPEN20 disabled; CMPEN18 disabled; CMPEN19 disabled; CMPEN16 disabled; CMPEN17 disabled; CMPEN25 disabled; CMPEN23 disabled; CMPEN24 disabled; 
    ADCMP0ENH = 0x00;
    // CMPEN21 disabled; CMPEN22 disabled; CMPEN20 disabled; CMPEN18 disabled; CMPEN19 disabled; CMPEN16 disabled; CMPEN17 disabled; CMPEN25 disabled; CMPEN23 disabled; CMPEN24 disabled; 
    ADCMP1ENH = 0x00;
    // CMPEN21 disabled; CMPEN22 disabled; CMPEN20 disabled; CMPEN18 disabled; CMPEN19 disabled; CMPEN16 disabled; CMPEN17 disabled; CMPEN25 disabled; CMPEN23 disabled; CMPEN24 disabled; 
    ADCMP2ENH = 0x00;
    // CMPEN21 disabled; CMPEN22 disabled; CMPEN20 disabled; CMPEN18 disabled; CMPEN19 disabled; CMPEN16 disabled; CMPEN17 disabled; CMPEN25 disabled; CMPEN23 disabled; CMPEN24 disabled; 
    ADCMP3ENH = 0x00;
    // CMPLO 0; 
    ADCMP0LO = 0x00;
    // CMPLO 0; 
    ADCMP1LO = 0x00;
    // CMPLO 0; 
    ADCMP2LO = 0x00;
    // CMPLO 0; 
    ADCMP3LO = 0x00;
    // CMPHI 0; 
    ADCMP0HI = 0x00;
    // CMPHI 0; 
    ADCMP1HI = 0x00;
    // CMPHI 0; 
    ADCMP2HI = 0x00;
    // CMPHI 0; 
    ADCMP3HI = 0x00;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL0CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL1CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL2CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL3CON = 0x400;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP0CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP1CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP2CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP3CON = 0x00;
    // LVLEN9 disabled; LVLEN8 disabled; LVLEN11 disabled; LVLEN7 disabled; LVLEN10 disabled; LVLEN6 disabled; LVLEN13 disabled; LVLEN5 disabled; LVLEN12 disabled; LVLEN4 disabled; LVLEN15 disabled; LVLEN3 disabled; LVLEN14 disabled; LVLEN2 disabled; LVLEN1 disabled; LVLEN0 disabled; 
    ADLVLTRGL = 0x00;
    // LVLEN20 disabled; LVLEN22 disabled; LVLEN21 disabled; LVLEN24 disabled; LVLEN23 disabled; LVLEN25 disabled; LVLEN17 disabled; LVLEN16 disabled; LVLEN19 disabled; LVLEN18 disabled; 
    ADLVLTRGH = 0x00;
    // SAMC 0; 
    ADCORE0L = 0x00;
    // SAMC 0; 
    ADCORE1L = 0x00;
    // RES 12-bit resolution; EISEL Early interrupt is generated 1 TADCORE clock prior to data being ready; ADCS 2; 
    ADCORE0H = 0x300;
    // RES 12-bit resolution; EISEL Early interrupt is generated 1 TADCORE clock prior to data being ready; ADCS 2; 
    ADCORE1H = 0x300;
    // EIEN9 disabled; EIEN7 disabled; EIEN8 disabled; EIEN5 disabled; EIEN6 disabled; EIEN3 disabled; EIEN4 disabled; EIEN1 disabled; EIEN2 disabled; EIEN13 disabled; EIEN0 disabled; EIEN12 disabled; EIEN11 disabled; EIEN10 disabled; EIEN15 disabled; EIEN14 disabled; 
    ADEIEL = 0x00;
    // EIEN17 disabled; EIEN16 disabled; EIEN25 disabled; EIEN19 disabled; EIEN18 disabled; EIEN20 disabled; EIEN24 disabled; EIEN23 disabled; EIEN22 disabled; EIEN21 disabled; 
    ADEIEH = 0x00;
    // C0CIE disabled; C1CIE disabled; SHRCIE disabled; WARMTIME 32768 Source Clock Periods; 
    ADCON5H = (0xF00 & 0xF0FF); //Disabling WARMTIME bit
	
    //Assign Default Callbacks
    ADC1_SetCommonInterruptHandler(&ADC1_CallBack);
    ADC1_Setchannel_AN15InterruptHandler(&ADC1_channel_AN15_CallBack);
    ADC1_Setchannel_AN19InterruptHandler(&ADC1_channel_AN19_CallBack);
    ADC1_Setchannel_AN20InterruptHandler(&ADC1_channel_AN20_CallBack);
    ADC1_Setchannel_AN21InterruptHandler(&ADC1_channel_AN21_CallBack);
    ADC1_Setchannel_AN22InterruptHandler(&ADC1_channel_AN22_CallBack);
    ADC1_Setchannel_AN24InterruptHandler(&ADC1_channel_AN24_CallBack);
    ADC1_Setchannel_AN25InterruptHandler(&ADC1_channel_AN25_CallBack);
    ADC1_Setchannel_AN0InterruptHandler(&ADC1_channel_AN0_CallBack);
    ADC1_Setchannel_ANA1InterruptHandler(&ADC1_channel_ANA1_CallBack);
    
    // Clearing ADC1 interrupt.
    IFS5bits.ADCIF = 0;
    // Enabling ADC1 interrupt.
    IEC5bits.ADCIE = 1;
    // Clearing channel_AN22 interrupt flag.
    IFS7bits.ADCAN22IF = 0;
    // Enabling channel_AN22 interrupt.
    IEC7bits.ADCAN22IE = 1;
    // Clearing channel_AN24 interrupt flag.
    IFS12bits.ADCAN24IF = 0;
    // Enabling channel_AN24 interrupt.
    IEC12bits.ADCAN24IE = 1;
    // Clearing channel_AN25 interrupt flag.
    IFS12bits.ADCAN25IF = 0;
    // Enabling channel_AN25 interrupt.
    IEC12bits.ADCAN25IE = 1;

    // Setting WARMTIME bit
    ADCON5Hbits.WARMTIME = 0xF;
    // Enabling ADC Module
    ADCON1Lbits.ADON = 0x1;
    // Enabling Power for the Shared Core
    ADC1_SharedCorePowerEnable();
    // Enabling Power for Core0
    ADC1_Core0PowerEnable();
    // Enabling Power for Core1
    ADC1_Core1PowerEnable();

    //TRGSRC0 PWM1 Trigger1; TRGSRC1 PWM1 Trigger1; 
    ADTRIG0L = 0x404;
    //TRGSRC3 None; TRGSRC2 None; 
    ADTRIG0H = 0x00;
    //TRGSRC4 None; TRGSRC5 None; 
    ADTRIG1L = 0x00;
    //TRGSRC6 None; TRGSRC7 None; 
    ADTRIG1H = 0x00;
    //TRGSRC8 None; TRGSRC9 None; 
    ADTRIG2L = 0x00;
    //TRGSRC11 None; TRGSRC10 None; 
    ADTRIG2H = 0x00;
    //TRGSRC13 None; TRGSRC12 None; 
    ADTRIG3L = 0x00;
    //TRGSRC15 PWM1 Trigger1; TRGSRC14 None; 
    ADTRIG3H = 0x400;
    //TRGSRC17 None; TRGSRC16 None; 
    ADTRIG4L = 0x00;
    //TRGSRC19 PWM1 Trigger1; TRGSRC18 None; 
    ADTRIG4H = 0x400;
    //TRGSRC20 PWM1 Trigger1; TRGSRC21 PWM1 Trigger1; 
    ADTRIG5L = 0x404;
    //TRGSRC22 PWM1 Trigger1; TRGSRC23 None; 
    ADTRIG5H = 0x04;
    //TRGSRC24 Common Software Trigger; TRGSRC25 Common Software Trigger; 
    ADTRIG6L = 0x101;
}

void ADC1_Core0PowerEnable ( ) 
{
    ADCON5Lbits.C0PWR = 1; 
    while(ADCON5Lbits.C0RDY == 0);
    ADCON3Hbits.C0EN = 1;     
}

void ADC1_Core1PowerEnable ( ) 
{
    ADCON5Lbits.C1PWR = 1; 
    while(ADCON5Lbits.C1RDY == 0);
    ADCON3Hbits.C1EN = 1;     
}

void ADC1_SharedCorePowerEnable ( ) 
{
    ADCON5Lbits.SHRPWR = 1;   
    while(ADCON5Lbits.SHRRDY == 0);
    ADCON3Hbits.SHREN = 1;   
}


void __attribute__ ((weak)) ADC1_CallBack ( void )
{ 

}

void ADC1_SetCommonInterruptHandler(void* handler)
{
    ADC1_CommonDefaultInterruptHandler = handler;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCInterrupt ( void )
{
    if(ADC1_CommonDefaultInterruptHandler) 
    { 
        ADC1_CommonDefaultInterruptHandler(); 
    }

    // clear the ADC1 interrupt flag
    IFS5bits.ADCIF = 0;
}

void __attribute__ ((weak)) ADC1_channel_AN15_CallBack( uint16_t adcVal )
{ 

}

void ADC1_Setchannel_AN15InterruptHandler(void* handler)
{
    ADC1_channel_AN15DefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_channel_AN15_Tasks ( void )
{
    uint16_t valchannel_AN15;

    if(ADSTATLbits.AN15RDY)
    {
        //Read the ADC value from the ADCBUF
        valchannel_AN15 = ADCBUF15;

        if(ADC1_channel_AN15DefaultInterruptHandler) 
        { 
            ADC1_channel_AN15DefaultInterruptHandler(valchannel_AN15); 
        }
    }
}

void __attribute__ ((weak)) ADC1_channel_AN19_CallBack( uint16_t adcVal )
{ 

}

void ADC1_Setchannel_AN19InterruptHandler(void* handler)
{
    ADC1_channel_AN19DefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_channel_AN19_Tasks ( void )
{
    uint16_t valchannel_AN19;

    if(ADSTATHbits.AN19RDY)
    {
        //Read the ADC value from the ADCBUF
        valchannel_AN19 = ADCBUF19;

        if(ADC1_channel_AN19DefaultInterruptHandler) 
        { 
            ADC1_channel_AN19DefaultInterruptHandler(valchannel_AN19); 
        }
    }
}

void __attribute__ ((weak)) ADC1_channel_AN20_CallBack( uint16_t adcVal )
{ 

}

void ADC1_Setchannel_AN20InterruptHandler(void* handler)
{
    ADC1_channel_AN20DefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_channel_AN20_Tasks ( void )
{
    uint16_t valchannel_AN20;

    if(ADSTATHbits.AN20RDY)
    {
        //Read the ADC value from the ADCBUF
        valchannel_AN20 = ADCBUF20;

        if(ADC1_channel_AN20DefaultInterruptHandler) 
        { 
            ADC1_channel_AN20DefaultInterruptHandler(valchannel_AN20); 
        }
    }
}

void __attribute__ ((weak)) ADC1_channel_AN21_CallBack( uint16_t adcVal )
{ 

}

void ADC1_Setchannel_AN21InterruptHandler(void* handler)
{
    ADC1_channel_AN21DefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_channel_AN21_Tasks ( void )
{
    uint16_t valchannel_AN21;

    if(ADSTATHbits.AN21RDY)
    {
        //Read the ADC value from the ADCBUF
        valchannel_AN21 = ADCBUF21;

        if(ADC1_channel_AN21DefaultInterruptHandler) 
        { 
            ADC1_channel_AN21DefaultInterruptHandler(valchannel_AN21); 
        }
    }
}

void __attribute__ ((weak)) ADC1_channel_AN22_CallBack( uint16_t adcVal )
{ 

}

void ADC1_Setchannel_AN22InterruptHandler(void* handler)
{
    ADC1_channel_AN22DefaultInterruptHandler = handler;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN22Interrupt ( void )
{
    uint16_t valchannel_AN22;
    //Read the ADC value from the ADCBUF
    valchannel_AN22 = ADCBUF22;

    if(ADC1_channel_AN22DefaultInterruptHandler) 
    { 
        ADC1_channel_AN22DefaultInterruptHandler(valchannel_AN22); 
    }

    //clear the channel_AN22 interrupt flag
    IFS7bits.ADCAN22IF = 0;
}

void __attribute__ ((weak)) ADC1_channel_AN24_CallBack( uint16_t adcVal )
{ 

}

void ADC1_Setchannel_AN24InterruptHandler(void* handler)
{
    ADC1_channel_AN24DefaultInterruptHandler = handler;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN24Interrupt ( void )
{
    uint16_t valchannel_AN24;
    //Read the ADC value from the ADCBUF
    valchannel_AN24 = ADCBUF24;

    if(ADC1_channel_AN24DefaultInterruptHandler) 
    { 
        ADC1_channel_AN24DefaultInterruptHandler(valchannel_AN24); 
    }

    //clear the channel_AN24 interrupt flag
    IFS12bits.ADCAN24IF = 0;
}

void __attribute__ ((weak)) ADC1_channel_AN25_CallBack( uint16_t adcVal )
{ 

}

void ADC1_Setchannel_AN25InterruptHandler(void* handler)
{
    ADC1_channel_AN25DefaultInterruptHandler = handler;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN25Interrupt ( void )
{
    uint16_t valchannel_AN25;
    //Read the ADC value from the ADCBUF
    valchannel_AN25 = ADCBUF25;

    if(ADC1_channel_AN25DefaultInterruptHandler) 
    { 
        ADC1_channel_AN25DefaultInterruptHandler(valchannel_AN25); 
    }

    //clear the channel_AN25 interrupt flag
    IFS12bits.ADCAN25IF = 0;
}


void __attribute__ ((weak)) ADC1_channel_AN0_CallBack( uint16_t adcVal )
{ 

}

void ADC1_Setchannel_AN0InterruptHandler(void* handler)
{
    ADC1_channel_AN0DefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_channel_AN0_Tasks ( void )
{
    uint16_t valchannel_AN0;

    if(ADSTATLbits.AN0RDY)
    {
        //Read the ADC value from the ADCBUF
        valchannel_AN0 = ADCBUF0;

        if(ADC1_channel_AN0DefaultInterruptHandler) 
        { 
            ADC1_channel_AN0DefaultInterruptHandler(valchannel_AN0); 
        }
    }
}

void __attribute__ ((weak)) ADC1_channel_ANA1_CallBack( uint16_t adcVal )
{ 

}

void ADC1_Setchannel_ANA1InterruptHandler(void* handler)
{
    ADC1_channel_ANA1DefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_channel_ANA1_Tasks ( void )
{
    uint16_t valchannel_ANA1;

    if(ADSTATLbits.AN1RDY)
    {
        //Read the ADC value from the ADCBUF
        valchannel_ANA1 = ADCBUF1;

        if(ADC1_channel_ANA1DefaultInterruptHandler) 
        { 
            ADC1_channel_ANA1DefaultInterruptHandler(valchannel_ANA1); 
        }
    }
}



/**
  End of File
*/
