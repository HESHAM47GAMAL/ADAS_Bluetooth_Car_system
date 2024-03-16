 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC_program.h
 *
 * Description: contain Implementation of ADC Driver 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "ADC_private.h"
#include "ADC_interface.h"
#include "ADC_config.h"
#include "../../SERVICE/COMMON_MACROS.h"
#include "../../SERVICE/IVT.h"


/**************************                   Extern Global variable                   **************************/
extern ADC_ConfigType  ADC_ConfigTypeParam ;
    uint16 ADC_conversion_value = 0 ;

#if (ADC_Interrupt_State == ADC_Interrupt_Enable)

/**************************                   Global Variables                   **************************/
/*  Volatile as it change only inside ISR and compiler may make optimization on it and I try to avoid it  */
volatile uint16 g_adcResult ; 

/**************************                   ISR's Definitions                   **************************/

ISR(ADC_vect)
{
	/* Read ADC Data after conversion complete */
	g_adcResult = ADC_ReadConversionRegister();
}

#endif


void ADC_OnlyStartConversionGeneral(uint8 Channel_NUM)
{
    /*  As this code use Single Ended input so I need to use first 7 cases from ADC Multiplexer  */
    Channel_NUM &= 0x07 ;  
    /*  tell which channel want to read     */
    ADMUX = (ADMUX & 0xE0) | (Channel_NUM);
    /*  Start convertion for this channel*/
    SET_BIT(ADCSRA , ADSC);
}

void ADC_Init(void)
{
    /*  Set ADC Voltage Reference    */
    ADMUX = (ADMUX & 0x3F)| ( ADC_ConfigTypeParam.ADC_ReferenceVoltage_Value << 6) ;
    /*  Set ADC result conversion Adjustment*/
    if(ADC_ConfigTypeParam.ADC_ValueAdjustment_value == ADC_Adjust_Right)
        CLEAR_BIT(ADMUX, ADLAR);
    else if(ADC_ConfigTypeParam.ADC_ValueAdjustment_value == ADC_Adjust_Left)
        SET_BIT(ADMUX, ADLAR);
    /*  Enable  ADC     */
    SET_BIT(ADCSRA , ADEN);
    /*  Set ADC Working Mode*/
    if(ADC_ConfigTypeParam.ADC_WorkingMode_value == Single_Conversion_Mode)
    {
        /*  Do Nothing as this mode is simply start converion @ anytime want to read channel    */
    }
    else if (ADC_ConfigTypeParam.ADC_WorkingMode_value == Free_Running_Mode)
    {
        /*  Can do that by set  Auto trigger  bit   */
        SET_BIT(ADCSRA , ADATE);
        /*  Then choose option  1 Free Running mode from ADC Auto Trigger Source*/
        SFIOR = (SFIOR & 0x0F);
    }
    else if (ADC_ConfigTypeParam.ADC_WorkingMode_value == Auto_Trigger_Mode)
    {
        /*  Can do that by set  Auto trigger  bit   */
        SET_BIT(ADCSRA , ADATE);
        /*  choose Auto trigger source*/
        SFIOR = (SFIOR & 0x0F) | (ADC_ConfigTypeParam.ADC_AutoTriggerSource_value << ADTS0);
    }
    /*  Set Prescaler for ADC   */
    ADCSRA = (ADCSRA & 0xF8) | (ADC_ConfigTypeParam.ADC_PrescalerSelect_value & 0x07);
    #if (ADC_Interrupt_State == ADC_Interrupt_Enable)
        SET_BIT(ADCSRA,ADIE);
        /*  Enable GLobal Interrupt   */
        SET_BIT(SREG,7);
    #elif (ADC_Interrupt_State == ADC_Interrupt_Disable)
        CLEAR_BIT(ADCSRA,ADIE);
    #endif
        
}


uint16 ADC_ReadChannelSingleConvertion(uint8 Channel_NUM)
{
    ADC_OnlyStartConversionGeneral(Channel_NUM);
    /*  wait uintil ADIF (conversion flag) in ADCSRA register convert from Low to High As that mean conversion completed  */
    while (BIT_IS_CLEAR(ADCSRA,ADIF));
    ADC_conversion_value = ADC_ReadConversionRegister();
    /*  Clear ADIF (conversion flag) in ADCSRA register by write one when use Polling Technique     */
    SET_BIT(ADCSRA,ADIF);
    return ADC_conversion_value;
}

void ADC_FreeRunningStart (uint8 Channel_NUM)
{
    ADC_OnlyStartConversionGeneral(Channel_NUM);
}

uint16 ADC_ReadConversionRegister(void)
{   
    /* ⚠️NOTE if I use #define ADC (* (volatile uint16 *) (0x24) )  will reduce all below steps */
    uint16 RegisterValue = 0 ;
    if(ADC_ConfigTypeParam.ADC_ValueAdjustment_value == ADC_Adjust_Right)
    {
        /*  When ADCL is read, the ADC Data Register is not updated until ADCH is read */
        RegisterValue = ADCL;
        RegisterValue = (( (uint16)(ADCH & 0x03) ) << 8) | RegisterValue ;
    }
    else if(ADC_ConfigTypeParam.ADC_ValueAdjustment_value == ADC_Adjust_Left)
    {
        /*  When ADCL is read, the ADC Data Register is not updated until ADCH is read */
        RegisterValue = ((ADCL & 0xC0) ) >> 6 ;
        RegisterValue = (( (uint16)ADCH ) << 2) | RegisterValue ;
    }
    return RegisterValue ;
}






