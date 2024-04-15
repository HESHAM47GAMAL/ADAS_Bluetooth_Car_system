 /******************************************************************************
 *
 * Module: Common - Macros
 *
 * File Name: COMMON_MACROS.h
 *
 * Description: Commonly used Macros
 *
 * Author: Hesham Shehata
 *
 *******************************************************************************/


#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

/*  Set Specific bit in any register    */
#define SET_BIT(REG , BIT) ( (REG) |= (1 << (BIT)) )

/*  Clear Specific bit in any register    */
#define CLEAR_BIT(REG , BIT) ( (REG) &= ~ (1 << (BIT)) )

/*  Toggle Specific bit in any register    */
#define TOGGLE_BIT(REG , BIT) ( (REG) ^=  (1 << (BIT)) )

/*  Rotate Register value right with specific number    */
#define ROTATE_REG_RIGHT(REG , NUM) ( (REG) = ( REG >> (NUM) ) | ( REG << ( 8 - (NUM) ) ) )

/*  Rotate Register value left with specific number */
#define ROTATE_REG_LEFT(REG , NUM) ( (REG) = ( REG << (NUM) ) | ( REG >> ( 8 - (NUM) ) ) )

/*  Check if certain Bit in any register is Set */
#define BIT_IS_SET(REG , BIT) ((REG) & (1 << (BIT)))

/*  Check if certain Bit in any register is Clear */
#define BIT_IS_CLEAR(REG , BIT) ( ! ( (REG) & (1 << (BIT)) ) )



#endif
