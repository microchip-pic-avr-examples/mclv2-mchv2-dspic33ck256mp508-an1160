/**
  Generated main.c file from MPLAB Code Configurator

  @Company
    Microchip Technology Inc.

  @File Name
    main.c

  @Summary
    This is the generated main.c using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    This source file provides main entry point for system initialization and application code development.
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
#include "mcc_generated_files/system.h"
#include "mcc_generated_files/X2Cscope/X2CscopeComm.h"
#include "mcc_generated_files/X2Cscope/X2Cscope.h"
#include "mcc_generated_files/adc1.h"
#include "mcc_generated_files/sccp1_tmr.h"
#include "mcc_generated_files/sccp3_tmr.h"
#include "mcc_generated_files/pin_manager.h"
#include "motor_control/motor_control_declarations.h"
#include "motor_control/motor_control_types.h"
#include "button_service.h"
#include "userparms.h"



const uint16_t PWM_STATE1_CLKW[8] = {0x3000, 0x3400, 0x3000, 0x1000, 0x1000, 0x3000, 0x3400, 0x3000};
const uint16_t PWM_STATE2_CLKW[8] = {0x3000, 0x3000, 0x3400, 0x3400, 0x3000, 0x1000, 0x1000, 0x3000};
const uint16_t PWM_STATE3_CLKW[8] = {0x3000, 0x1000, 0x1000, 0x3000, 0x3400, 0x3400, 0x3000, 0x3000};
uint16_t PWM_STATE1[8];
uint16_t PWM_STATE2[8];
uint16_t PWM_STATE3[8];

/*AND & OR operators for masking the active BEMF signal*/
const unsigned int ADC_MASK_CLKW[8] = {0x0000, 0x0002, 0x0001, 0x0004, 0x0002, 0x0001, 0x0004, 0x0000};
uint16_t ADC_MASK[8];

const unsigned int ADC_XOR_CLKW[8] = {0x0000, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000, 0xFFFF, 0x0000};
uint16_t ADC_XOR[8];

/*BEMF Majority Function Filter values*/
const unsigned char ADC_BEMF_FILTER_CLKW[64] = {0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1A, 0x1C, 0x1E,
    0x20, 0x22, 0x24, 0x26, 0x28, 0x2A, 0x2C, 0x2E, 0x01, 0x01, 0x01, 0x36, 0x01, 0x3A, 0x3C, 0x3E,
    0x00, 0x02, 0x04, 0x06, 0x08, 0x0A, 0x0C, 0x0E, 0x01, 0x01, 0x01, 0x16, 0x01, 0x1A, 0x1C, 0x1E,
    0x01, 0x01, 0x01, 0x26, 0x01, 0x2A, 0x2C, 0x2E, 0x01, 0x01, 0x01, 0x36, 0x01, 0x3A, 0x3C, 0x3E};
unsigned char ADC_BEMF_FILTER[64];

/*Application Flags to indicate the motor status*/
struct {
    unsigned RunMotor : 1;
    unsigned RotorAlignment : 1;
    unsigned Direction : 1;
    unsigned unused : 13;
} Flags;

typedef struct {
    uint32_t speedAcc;
    uint32_t calculatedSpeed;
    uint16_t speedValue;
    uint16_t index;
    int16_t buffer[SPEED_MOVING_AVG_FILTER_SIZE];
    int32_t sum;
    int16_t avg;
} MOVING_AVG_SPEED;

typedef struct {
    MC_PIPARMIN_T piInputSpeed;
    MC_PIPARMOUT_T piOutputSpeed;
} PI_Controller_Input;

//###################### Miscellaneous Variables and Defines ####################
uint16_t Timer2Value_neu;
uint16_t Timer2Value_alt;
uint16_t Timer2Average;
uint16_t Timer1Value;
uint16_t PWMticks;
uint16_t MaxPWMTicks = MAXPWMTICKS;
uint16_t ADCCommState;
uint8_t RampUpCommState;
uint8_t adcBackEMFFilter;
uint16_t PhaseAdvance = 0;
uint16_t PhaseAdvanceDegrees = PHASE_ADVANCE_DEGREES;
uint16_t BlankingCounter;
uint8_t BlankCnt_max_u8;
uint16_t V_M1;
uint16_t V_M2;
uint16_t V_M3;
uint16_t I_a;
uint16_t I_b;
uint16_t I_sum;
uint16_t V_pot;
uint16_t HallValue; // Variable containing the Hall Value from PORTB
uint16_t RecNeutrVoltage;
uint8_t ComparatorOutputs;
uint16_t DesiredPWMDutyCycle;
uint16_t CurrentPWMDutyCycle;
uint16_t PotVal;
uint16_t CurrentSpeed;
uint16_t DesiredSpeed;

MOVING_AVG_SPEED MovingAvgSpeed; //Moving average speed calculated from 60 degrees counter reading
PI_Controller_Input PI_Input;

//motor control functions. defined here, implemented in main.c
void DelayNmSec(uint16_t Counter);
void PreCommutationState(void);
void OpenLoopController(void);
void PICloseLoopController(void);
void StartMotor(void);
void StopMotor(void);
void CalcMovingAvgSpeed(int16_t instCount);
void InitMovingAvgSpeed(void);
void Init_PIControlParameters(void);

/*
                         Main application
 */
int main(void) {
    // initialize the device
    SYSTEM_Initialize();
    StopMotor();
    BoardServiceInit();

    /****************** Check Buttons*********************************/
    while (1) {
        BoardService();
        X2CScope_Communicate();
        if (IsPressed_Button1()) {

            if (!Flags.RunMotor) {
                StartMotor();
            } else {
                StopMotor();
            }
        }
#ifdef MCLV2
        if (IsPressed_Button2()) {
            Flags.Direction = ~Flags.Direction;
            if (Flags.RunMotor == 1) {
                StopMotor();
                DelayNmSec(1000);
                StartMotor();
            }
        }
#endif
    }

    return 1;
}

void PWM_Generator1_CallBack(void) {
    /* Add your custom callback code here or implement
    the Callback in the application code, without the weak attribute */

    if (Flags.RunMotor) {
        //Ramp-up period to detect the rotor position
        if (Flags.RotorAlignment && Flags.RunMotor) {
            PG1DC = PG2DC = PG3DC = CurrentPWMDutyCycle;
            ++PWMticks;
        }
        //Check if the Ramp-up value is disabled, if so starts sensorless operation
        if (++PWMticks > MaxPWMTicks)
            PreCommutationState();

        // Masking the BEMF signals according to the SECTOR in order to determine the ACTIVE BEMF signal
        // XOR operator helps to determine the direction of the upcoming zero-crossing slope
        BlankingCounter++;
        if (BlankingCounter > BLANKING_COUNT) {
            if ((ComparatorOutputs^ADC_XOR[ADCCommState]) & ADC_MASK[ADCCommState])
                adcBackEMFFilter |= 0x01;

            //Majority detection filter	
            adcBackEMFFilter = ADC_BEMF_FILTER[adcBackEMFFilter];
            if (adcBackEMFFilter & 0b00000001)
                PreCommutationState();
        }
    }
}

void ADC1_CallBack(void) {
    X2CScope_Update();
    BoardServiceStepIsr();

    I_a = ADCBUF0;
    I_b = ADCBUF1;
    I_sum = ADCBUF15;
    V_pot = PotVal = ADCBUF19;
    V_M1 = ADCBUF20;
    V_M2 = ADCBUF21;
    V_M3 = ADCBUF22;

    //Reconstrucs Voltage at the  Motor Neutral Point
    RecNeutrVoltage = (V_M1 + V_M2 + V_M3) / 3;

    /********************* ADC SAMPLING & BMEF signals comparison ****************/

    if (BlankingCounter > BlankCnt_max_u8) {
        ComparatorOutputs = 0; // Precondition all comparator bits as zeros
        if (V_M1 > RecNeutrVoltage)
            ComparatorOutputs += 1; // Set bit 0 when Phase C is higher than Neutural
        if (V_M2 > RecNeutrVoltage)
            ComparatorOutputs += 2; // Set bit 1 when Phase B is higher than Neutural
        if (V_M3 > RecNeutrVoltage)
            ComparatorOutputs += 4; // Set bit 2 when Phase A is higher than Neutral
    }

}

void SCCP1_TMR_PrimaryTimerCallBack(void) {
    // Add your custom callback code here
    PG1IOCONL = PWM_STATE1[ADCCommState];
    PG2IOCONL = PWM_STATE2[ADCCommState];
    PG3IOCONL = PWM_STATE3[ADCCommState];
    BlankingCounter = 0;
    SCCP1_TMR_Stop(); // Stop TIMER1
    SCCP1_TMR_Counter16BitPrimarySet(0);
}

/******************************************************************************
 * Function:     PreCommutationState(void)
 *
 * Output:		None
 *
 * Overview:		This function measures the 60 and 30 electrical degrees
 *				using the TIMER2. The 60 electrical degrees is proportional
 *				to the elpased time between zero-crossing events.
 *				The zero-crossing events occur 30 electrical degrees in advace
 *				of the commutation point. Hence a delay proportional to the 30
 *				electrical degrees is added using the TIMER1
 *
 * Note:			None
 *******************************************************************************/
void PreCommutationState(void) {
    // Calculate the time proportional to the 60 electrical degrees
    SCCP3_TMR_Stop(); // Stop TIMER2
    Timer2Value_neu = SCCP3_TMR_Counter16BitPrimaryGet();
    Timer2Average = ((Timer2Average + Timer2Value_alt + Timer2Value_neu) / 3);
    Timer2Value_alt = Timer2Value_neu;
    CalcMovingAvgSpeed(Timer2Average);
    CurrentSpeed = MovingAvgSpeed.avg;
    SCCP3_TMR_Counter16BitPrimarySet(0);
    SCCP3_TMR_Start(); // Start TIMER2
    //Calculate the delay in TIMER1 counts proportional to the Phase Adv angle
    PhaseAdvance = ((Timer2Average * PhaseAdvanceDegrees) / 60);

    // Calculate the time proportional to the 30 electrical degrees
    // Load the TIMER1 with  the TIMER1 counts porportional to 30 deg	minus the PHASE ADV angle delay
    Timer1Value = (((Timer2Average) >> 1) - PhaseAdvance);
    if (Timer1Value > 1)
        SCCP1_TMR_Period16BitPrimarySet(Timer1Value);
    else
        Timer1Value = 1;
    SCCP1_TMR_Period16BitPrimarySet(Timer1Value);

    //    SCCP1_TMR_Period16BitPrimarySet( 10 );
    // Start TIMER1
    SCCP1_TMR_Counter16BitPrimarySet(0);
    SCCP1_TMR_Start();

    //disabling rotor alignment & ramp-up sequence
    PWMticks = 0;
    RampUpCommState = 7;
    Flags.RotorAlignment = false;

    //if Motor is runnining in sensorless mode and the SPEED_CLOSELOOP is defined
    //then the PI controller is enabled else, the motor runs in open loop
    if ((!Flags.RotorAlignment) && Flags.RunMotor) {
#ifdef SPEED_CLOSEDLOOP
        PICloseLoopController();
#else
        OpenLoopController();
#endif
    }

    // Change The Six-Step Commutation Sector
    adcBackEMFFilter = 0;
    if (++ADCCommState > 6)
        ADCCommState = 1;
}

/******************************************************************************
 * Function:     OpenLoopController(void)
 *
 * Output:		None
 *
 * Overview:		When the PI button is OFF on the DMCI window
 *				the motor operates in open loop mode.
 *
 * Note:			None
 *******************************************************************************/
void OpenLoopController(void) {

    DesiredPWMDutyCycle = (int16_t) ((__builtin_mulss(PotVal, (MAX_DUTY - MIN_DUTY)) >> 12) + MIN_DUTY);
    //Update the duty cycle according to the POT value, a POT follower is implemented here
    if (CurrentPWMDutyCycle != DesiredPWMDutyCycle) {
        if (CurrentPWMDutyCycle < DesiredPWMDutyCycle)
            CurrentPWMDutyCycle += 10;
        if (CurrentPWMDutyCycle > DesiredPWMDutyCycle)
            CurrentPWMDutyCycle -= 10;
    }
    // Max and Min PWM duty cycle limits
    if (CurrentPWMDutyCycle < MIN_DUTY)
        CurrentPWMDutyCycle = MIN_DUTY;
    if (CurrentPWMDutyCycle > MAX_DUTY)
        CurrentPWMDutyCycle = MAX_DUTY;
    //Assigning new duty cycles to the PWM channels
    PG1DC = CurrentPWMDutyCycle;
    PG2DC = CurrentPWMDutyCycle;
    PG3DC = CurrentPWMDutyCycle;

}

#ifdef SPEED_CLOSEDLOOP

/******************************************************************************
 * Description: PI PICloseLoopController routine calls the Close Loop Pi function 
 * from the motor control library.
 ******************************************************************************/
void PICloseLoopController(void) {

    DesiredSpeed = (int16_t) ((__builtin_mulss(PotVal, (MAX_CLOSELOOP_MOTORSPEED - MIN_CLOSELOOP_MOTORSPEED)) >> 12) + MIN_CLOSELOOP_MOTORSPEED);
    PI_Input.piInputSpeed.inMeasure = CurrentSpeed;
    PI_Input.piInputSpeed.inReference = DesiredSpeed;
    MC_ControllerPIUpdate_Assembly(PI_Input.piInputSpeed.inReference,
            PI_Input.piInputSpeed.inMeasure,
            &PI_Input.piInputSpeed.piState,
            &PI_Input.piOutputSpeed.out);
    CurrentPWMDutyCycle = (int16_t) (__builtin_mulss(PI_Input.piOutputSpeed.out, (MAX_DUTY)) >> 15);
    //Assigning new duty cycles to the PWM channels
    PG1DC = CurrentPWMDutyCycle;
    PG2DC = CurrentPWMDutyCycle;
    PG3DC = CurrentPWMDutyCycle;
}
#endif

void StartMotor(void) {
    int i;
    if (Flags.Direction == 1) {
        for (i = 0; i < 8; i++) {
            PWM_STATE1[i] = PWM_STATE1_CLKW[i];
            PWM_STATE2[i] = PWM_STATE2_CLKW[i];
            PWM_STATE3[i] = PWM_STATE3_CLKW[i];

            ADC_MASK[i] = ADC_MASK_CLKW[i];
            ADC_XOR[i] = ADC_XOR_CLKW[7 - i];
        }
        for (i = 0; i < 64; i++)
            ADC_BEMF_FILTER[i] = ADC_BEMF_FILTER_CLKW[63 - i];

    } else {
        for (i = 0; i < 8; i++) {
            PWM_STATE1[i] = PWM_STATE1_CLKW[7 - i];
            PWM_STATE2[i] = PWM_STATE2_CLKW[7 - i];
            PWM_STATE3[i] = PWM_STATE3_CLKW[7 - i];

            ADC_MASK[i] = ADC_MASK_CLKW[7 - i];
            ADC_XOR[i] = ADC_XOR_CLKW[7 - i];
        }
        for (i = 0; i < 64; i++)
            ADC_BEMF_FILTER[i] = ADC_BEMF_FILTER_CLKW[63 - i];
    }
    SCCP3_TMR_Start();
    /*ROTOR ALIGNMENT SEQUENCE*/
    Flags.RotorAlignment = 1; // TURN ON rotor alignment sequence
    Flags.RunMotor = 1; // Indicating that motor is running
    CurrentPWMDutyCycle = STARTUP_DUTY; //Init PWM values
    DesiredPWMDutyCycle = STARTUP_DUTY; //Init PWM values
    PWMticks = 0; //Init Rotor aligment counter
    BlankCnt_max_u8 = BLANKING_COUNT;
    Init_PIControlParameters();
    InitMovingAvgSpeed();
    /************* Rotor alignment sequence and ramp-up sequence ************/
    for (RampUpCommState = 1; RampUpCommState < 7; RampUpCommState++) {
        while (PWMticks < MaxPWMTicks && Flags.RotorAlignment) {
            PG1IOCONL = PWM_STATE1[RampUpCommState];
            PG2IOCONL = PWM_STATE2[RampUpCommState];
            PG3IOCONL = PWM_STATE3[RampUpCommState];
        }
        PWMticks = 0;
    }
    Flags.RotorAlignment = 0; // TURN OFF rotor alignment sequence
    PWMticks = MaxPWMTicks + 1; // RAMP UP for breaking the motor IDLE state
    DelayNmSec(RAM_UP_DELAY); // RAMP UP DELAY
    LED1_SetHigh();
}

/******************************************************************************
 * Description: StopMotor function 
 *****************************************************************************/

void StopMotor(void) {
    Flags.RotorAlignment = 0; // turn on RAMP UP
    Flags.RunMotor = 0; // reset run flag
    CurrentPWMDutyCycle = 1; // Set PWM to the min value

    //Initi speed measurement variables & timer
    SCCP3_TMR_Stop();
    SCCP3_TMR_Counter16BitPrimarySet(0);
    Timer2Value_alt = 0;
    Timer2Average = 0;
    SCCP1_TMR_Stop(); // Stop TIMER1
    SCCP1_TMR_Counter16BitPrimarySet(0);
    PG1DC = PG2DC = PG3DC = 0;
    PG1IOCONL = PWM_STATE1_CLKW[0];
    PG2IOCONL = PWM_STATE2_CLKW[0];
    PG3IOCONL = PWM_STATE3_CLKW[0];
    LED1_SetLow();
}

/******************************************************************************
 * Function:     DelayNmSec(unsigned int N)
 *
 * Output:		None
 *
 * Overview:		Delay function used for push buttons debounce loop and for the
 *				motor start-up sequence
 *
 * Note:			None
 *******************************************************************************/
void DelayNmSec(uint16_t Counter) {
    uint16_t j;
    while (Counter--) {
        for (j = 0; j < 3000; j++) {
        };
    }
}

/******************************************************************************
 * Description: The InitMovingAvgSpeed function initializes the current 
 *              array table that is being used to calculate the moving average,
 *              thereby eliminate the undesired response and variations during
 *              reset and restart of motor.
 *****************************************************************************/

void InitMovingAvgSpeed(void) {
    uint16_t i;

    for (i = 0; i < SPEED_MOVING_AVG_FILTER_SIZE; i++) {
        MovingAvgSpeed.buffer[i] = 0;
    }

    MovingAvgSpeed.index = 0;
    MovingAvgSpeed.sum = 0;
    MovingAvgSpeed.avg = 0;
}

/******************************************************************************
 * Description: The CalcMovingAvgSpeed function calculates the moving
 *              average of speed.
 *****************************************************************************/

void CalcMovingAvgSpeed(int16_t instCount) {

    uint16_t i;
    MovingAvgSpeed.speedAcc = MovingAvgSpeed.speedAcc + instCount;
    if (ADCCommState == 5) {
        MovingAvgSpeed.speedValue = MovingAvgSpeed.speedAcc;
        MovingAvgSpeed.calculatedSpeed = (int16_t) (__builtin_divud(SPEED_MULTI, MovingAvgSpeed.speedValue));
        MovingAvgSpeed.speedAcc = 0;

        MovingAvgSpeed.buffer[MovingAvgSpeed.index] = MovingAvgSpeed.calculatedSpeed;
        MovingAvgSpeed.index++;
        if (MovingAvgSpeed.index >= SPEED_MOVING_AVG_FILTER_SIZE)
            MovingAvgSpeed.index = 0;

        MovingAvgSpeed.sum = 0;
        for (i = 0; i < SPEED_MOVING_AVG_FILTER_SIZE; i++) {
            MovingAvgSpeed.sum = MovingAvgSpeed.sum + MovingAvgSpeed.buffer[i];
            MovingAvgSpeed.avg = MovingAvgSpeed.sum >> SPEED_MOVING_AVG_FILTER_SCALE;
        }
    }
}

/******************************************************************************
 * Description: Init_PIControlParameters initializes close loop pi parameters
 ******************************************************************************/
void Init_PIControlParameters(void) {
    /** PI - Speed Control */
    PI_Input.piInputSpeed.piState.kp = SPEEDCNTR_PTERM;
    PI_Input.piInputSpeed.piState.ki = SPEEDCNTR_ITERM;
    PI_Input.piInputSpeed.piState.kc = SPEEDCNTR_CTERM;
    PI_Input.piInputSpeed.piState.outMax = SPEEDCNTR_OUTMAX;
    PI_Input.piInputSpeed.piState.outMin = SPEEDCNTR_OUTMIN;
    PI_Input.piInputSpeed.piState.integrator = 0;
    PI_Input.piOutputSpeed.out = 0;
}
/**
 End of File
 */

