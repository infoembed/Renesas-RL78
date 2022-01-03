/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIESREGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2015 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : Applilet3 for RL78/G14 V2.04.02.01 [15 May 2015]
* Device(s)    : R5F104PJ
* Tool-Chain   : IAR Systems iccrl78
* Description  : This file implements main function.
* Creation Date: 03/01/2022
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_intc.h"
#include "r_cg_timer.h"
#include "r_cg_wdt.h"
/* Start user code for include. Do not edit comment generated here */
#define ON 1
#define OFF 0
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
volatile uint8_t flg_blink_1ms = 0U;
volatile uint8_t flg_time_switch =0U;
volatile uint8_t flg_switch1 = 0U;
volatile uint8_t flg_switch2 = 0U;

uint8_t flg;

static uint8_t s_state;/* this variable will return the state of the switch*/

void blink_led(uint16_t time, volatile uint8_t *timer_flg);
void led_shift_r(uint8_t flg_s, uint16_t delay, uint8_t loop_number);

uint8_t read_switch (volatile uint8_t  *switch_state);

/* End user code. Do not edit comment generated here */

/* Set option bytes */
#pragma location = "OPTBYTE"
__root const uint8_t opbyte0 = 0xFFU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte1 = 0xFFU;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte2 = 0xE8U;
#pragma location = "OPTBYTE"
__root const uint8_t opbyte3 = 0x04U;

/* Set security ID */
#pragma location = "SECUID"
__root const uint8_t secuid[10] = 
    {0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U, 0x00U};

void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
        P4_bit.no3 = 1;
        P4_bit.no4 = 1U;
        P6_bit.no2 = 0;
        P6_bit.no3 = 0;
    while (1U)
    {

      //led_shift_right(500, &flg_time_switch, &flg_switch1);
      flg = read_switch(&flg_switch1);
      
        led_shift_r(flg,500,5);
        
        blink_led( 500, &flg_blink_1ms);
        /**
        * read the button switch without interrupt and turn on the led else
        * turn off the led
        */
        if( P7_bit.no6  == 1U){
          P6_bit.no2 = 1U;
        }else {
            P6_bit.no2 = 0U;
        }
        
        

    }
    /* End user code. Do not edit comment generated here */
}


/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
  
  /* enable timer to start work */
  R_TAU0_Channel0_Start();
  R_INTC8_Start();
  R_INTC9_Start();
  
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */

void blink_led(uint16_t time, volatile uint8_t *timer_flg){
  
  static  uint16_t blink_counter = 0;
  
  if(*timer_flg == 1U){
    blink_counter ++;
    
    if(blink_counter >= time){
        blink_counter = 0U;
        P6_bit.no3 ^= 1;
    }
    
     *timer_flg = 0U;
  }
  
}


uint8_t read_switch (volatile uint8_t  *switch_state){
  
  
  static uint8_t cnt_swtch = 0U; 
  
  
  /* this flag "switch_state" changed inside the external interrupt when 
  change in the state of the pin rising or falling*/
  if(*switch_state == 1U){

    if(P7_bit.no4 == 1U){
      
      cnt_swtch++;
      if(cnt_swtch >= 50){ 
        
        cnt_swtch = 51; 
        s_state  = ON;
        *switch_state  = 0;
      } 
    }
  }
  return(s_state);
}

void led_shift_r(uint8_t flg_s, uint16_t delay, uint8_t loop_number){
  
  static  uint16_t counter = 0U;
  static uint8_t index_led = 0U;
  static uint8_t j= 0U;

  if(flg_s == 1U){
    if(flg_time_switch == 1U){
        flg_time_switch = 0U;
          counter ++;
    }

    if(counter >= delay/*500*/){
        counter = 0U;
        index_led ++;
        
    if(index_led >= 2U){
      index_led = 0U;
      j++;
      if(j == loop_number){
        j =0;
      s_state  = OFF;
      }
      
    }
    }

    switch (index_led)
    {
    case 0:
        P4_bit.no3 = 0U;
        P4_bit.no4 = 1U;
        
      break;
    case 1:
        P4_bit.no3 = 1U;
        P4_bit.no4 = 0U;
      
      break;

    default:
       P4_bit.no3 = 1U;
       P4_bit.no4 = 1U;
         
      break;
    }
     
  }else{
          P4_bit.no3 = 1U;
        P4_bit.no4 = 1U;
  }
  
}


/* End user code. Do not edit comment generated here */
