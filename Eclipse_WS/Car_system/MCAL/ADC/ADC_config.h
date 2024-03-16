 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC_config.h
 *
 * Description: Header to configure all ADC 
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


//Gard file

#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_



/**************************                   Declare custom types                   **************************/
typedef enum
{
    Single_Conversion_Mode ,  // Call function of read ADC value each time you want to know value
    Free_Running_Mode , // once the initial conversion is started, subsequent conversions will automatically start without any additional 
    Auto_Trigger_Mode   // convertion happen each time event happen
}ADC_WorkingMode;



//   Note ⛔⛔⛔⛔⛔🙆‍♂️  you need to connect power to AVCC pin in any
typedef enum{
    AREF ,              //      ----|  --> connect wanted reference voltage to this pin
    AVCC ,              //      ----|
    Internal_Voltage =3         // use internal  2.56V
}ADC_ReferenceVoltage ;





/*  this control how 10 bit of ADC convertion stored in 16 bit register*/
typedef enum{
    ADC_Adjust_Right ,  /* Recommended  */
    ADC_Adjust_Left
}ADC_ValueAdjustment ;

/*  As ADC circuit Need 50:200 KHZ So use suitable prescaler to  get this frequency depend on your MCU CLK    */
typedef enum{
    ADC_Divide_By_2 = 1 , ADC_Divide_By_4 , ADC_Divide_By_8 , ADC_Divide_By_16 , ADC_Divide_By_32 , ADC_Divide_By_64 , ADC_Divide_By_128
}ADC_PrescalerSelect;

/*  Note ⛔🙆‍♂️ it will ignored if not use Auto_Trigger_Mode */
/*  So if not use  Auto_Trigger_Mode  write NO_NEED*/
typedef enum 
{
    NO_NEED ,
    Analog_Comparator =  1 , 
    External_Interrupt_Request_0 , 
    Timer_Counter_0_Compare_Match ,
    Timer_Counter_0_Overflow ,
    Timer_Counter_1_Compare_Match_B ,
    Timer_Counter_1_Overflow ,
    Timer_Counter_1_Capture_Event
}ADC_AutoTriggerSource;


typedef struct 
{
    ADC_WorkingMode         ADC_WorkingMode_value;
    ADC_ReferenceVoltage    ADC_ReferenceVoltage_Value ;
    ADC_ValueAdjustment     ADC_ValueAdjustment_value;
    ADC_PrescalerSelect     ADC_PrescalerSelect_value;
    ADC_AutoTriggerSource   ADC_AutoTriggerSource_value;
}ADC_ConfigType ;




/*  write value of voltage that will use in voltage reference   */
#define REFRENCE_Volt_AVCC_OR_AREF_OR_internal  5

/*  Choose between Enable and Disable ADC Interrupt     */
#define ADC_Interrupt_Enable    1              //  Option 1 -----------|
#define ADC_Interrupt_Disable   0              //  Option 2 -----------|  
//                                                                     | Here
#define ADC_Interrupt_State         ADC_Interrupt_Disable  //<----------



#endif