 /******************************************************************************
 *
 * Module: Common - Platform Types Abstraction
 *
 * File Name: STD_TYPES.h
 *
 * Description: use types that have specific bits not depend on Target
 *
 * Author: Hesham Shehata 
 *
 *******************************************************************************/


#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Boolean Data type */
typedef  unsigned char  boolean;

#ifndef TRUE 
#define TRUE (1u)
#endif

#ifndef FALSE
#define FALSE (0u)
#endif

#define LOGIC_HIGH (1u)
#define LOGIC_LOW (0u)

#define NULL_PTR ((void*) 0)



typedef signed char         sint8;
typedef unsigned char       uint8;
typedef signed short        sint16;
typedef unsigned short      uint16;
typedef signed long         sint32;
typedef unsigned long       uint32;
typedef signed long long    sint64;
typedef unsigned long long  uint64;
typedef float               float32;
typedef double              float64;



typedef unsigned char Byte ;

typedef union 
{
    Byte Data;
    struct 
    {
        Byte BIT0 : 1 ;
        Byte BIT1 : 1 ;
        Byte BIT2 : 1 ;
        Byte BIT3 : 1 ;
        Byte BIT4 : 1 ;
        Byte BIT5 : 1 ; 
        Byte BIT6 : 1 ;
        Byte BIT7 : 1 ;
    }Bits;

}Reg_8Bits;

#endif