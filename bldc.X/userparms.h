/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
/* 
 * File:   bldc.h
 * Author: A2049
 *
 * Created on January 16, 2020, 2:29 PM
 */

#ifndef USERPARAMS_H
#define	USERPARAMS_H

#ifdef	__cplusplus
extern "C" {
#endif
    
 #define Q15(Float_Value)	\
((Float_Value < 0.0) ? (int16_t)(32768 * (Float_Value) - 0.5) \
: (int16_t)(32767 * (Float_Value) + 0.5))

//Code rubs in openloop by default. Uncomment to change to closedloop
//#define SPEED_CLOSEDLOOP
    
//************************************************************
// Motor Specific Parameters
#define MAXPWMTICKS                200
#define MAX_CLOSELOOP_MOTORSPEED   3200
#define MIN_CLOSELOOP_MOTORSPEED   1000
#define STARTUP_DUTY               800
#define MIN_DUTY                   200
#define MAX_DUTY                   5000
#define PHASE_ADVANCE_DEGREES      12     //Phase advance angles to get the best motor performance
#define RAM_UP_DELAY               0      //Delay for the ramp up sequence, expressed in millisecond
#define BLANKING_COUNT             3	  //Blanking count expressed in PWM periods used to avoid false zero-crossing detection after commutating motor
#define POLEPAIRS                  5      //Number of pole pairs  
//************************************************************

//************************************************************
//General System Parameters
#define FCY                             100000000               //FCY	
#define FPWM                            20000                   //in Hz.
#define TIMER_PRESCALER                 64                      //Timer peripheral prescaler
#define SPEED_MOVING_AVG_FILTER_SCALE   4                       //Buffer scale for the moving average
#define SPEED_MOVING_AVG_FILTER_SIZE    (uint16_t)(1 << SPEED_MOVING_AVG_FILTER_SCALE) //Buffer size for the moving average
#define SPEED_MULTI                     (unsigned long)(((float)FCY/(float)(TIMER_PRESCALER*POLEPAIRS))*(float)60) //speed multipler for speed calculation
    //************************************************************

//************************************************************
/* Velocity Control Loop Coefficients */
#define SPEEDCNTR_PTERM                Q15(0.3)
#define SPEEDCNTR_ITERM                Q15(0.02)
#define SPEEDCNTR_CTERM                Q15(0.999)
#define SPEEDCNTR_OUTMAX               Q15(0.999)
#define SPEEDCNTR_OUTMIN               Q15(0.0)
//************************************************************

#ifdef	__cplusplus
}
#endif

#endif	/* BLDC_H */