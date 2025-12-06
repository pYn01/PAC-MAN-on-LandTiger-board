/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "../table.h"
#include "../led/led.h"
#include "../pacman.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../fantasma.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down0=0;
volatile int down1=0;	
volatile int down2=0;


#define N 8

unsigned int VAR=0;
unsigned int VETT[N]={0};

int n=0;
char flag;

int current_direction=1;  // Nessuna direzione inizialmente
int next_direction=1;     // Nessuna direzione inizialmente

#define DIR_UP    0
#define DIR_DOWN  1
#define DIR_LEFT  2
#define DIR_RIGHT 3

void RIT_IRQHandler (void)
{			
	static int joy_sel=0;
	static int joy_down=0;
	static int joy_up=0;
	static int joy_left=0;
	static int joy_right=0;
		
	//+++++++++++++++++++++++++++++++++++++++++++++
	//									JOYSTICK										
	//+++++++++++++++++++++++++++++++++++++++++++++
	
	//+++++++++ SEL ++++++++++++++
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){
		joy_sel++;
		switch(joy_sel){
			case 1:
				//+++++++ PRESSIONE ++++++++++
				break;
			default:
				break;
		}
	}else{
		joy_sel=0;
	}
	
	
	//+++++++++ DOWN ++++++++++++++++++
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){
		joy_down++;
		switch(joy_down){
			case 1:
				//+++++++ PRESSIONE ++++++++++
				next_direction=DIR_DOWN;
				break;
			default:
				break;
		}
	}else{
		joy_down=0;
	}
	
	
	//+++++++++ LEFT ++++++++++++++
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){
		joy_left++;
		switch(joy_left){
			case 1:
				//+++++++ PRESSIONE ++++++++++
				next_direction=DIR_LEFT;				
				break;
			default:
				break;
		}
	}else{
		joy_left=0;
	}
	
	
	//+++++++++ RIGHT ++++++++++++++++
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){
		joy_right++;
		switch(joy_right){
			case 1:
				//+++++++ PRESSIONE ++++++++++
				next_direction=DIR_RIGHT;			
				break;
			default:
				break;
		}
	}else{
		joy_right=0;
	}
	
	
	//+++++++++ UP ++++++++++++++
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){
		joy_up++;
		switch(joy_up){
			case 1:
				//+++++++ PRESSIONE ++++++++++
				next_direction=DIR_UP;			
				break;
			default:
				break;
		}
	}else{
		joy_up=0;
	}
	
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
