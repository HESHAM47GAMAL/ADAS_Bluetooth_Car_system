 /******************************************************************************
 *
 * Module: ADC
 *
 * File Name: ADC_config.c
 *
 * Description: include configuration that will applied
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/

/**************************                   INCLUDES                   **************************/
#include "ADC_config.h"

/*  fill this data from available option in     ADC_config.h     */


ADC_ConfigType  ADC_ConfigTypeParam ={
    Single_Conversion_Mode ,  /*    Choose Mode of conversion   */
    AVCC ,        /*    Choose volatge reference used in ADC Conversion     */
    ADC_Adjust_Right ,        /*    Choose Storing of 10 bit ADC value adjusted in 16 bits  */
    ADC_Divide_By_64 ,        /*    Choose prescaler for MCU clock as ADC circuit need to get 50 : 200 KHZ clock to Work correctly  */
    NO_NEED                   /*    If use "Auto Trigger Mode" give trigger source if not use this mode write No Need or any give will ignored  */
};