/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
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


int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
												/* BUTTON Initialization              */
	//TP_Init();
	joystick_init();											/* Joystick Initialization            */
	
	//scheda
	init_RIT(0x004C4B40);									/* RIT Initialization 50 msec       	*/

	enable_RIT();			/* RIT enabled												*/
	LED_init();
  LCD_Initialization();
	BUTTON_init();
	
	// 240 X 320
	// 224 X 248 labirinto
	// 8 pixel cella

	
/*
	//SCHEDA timer 0 FANTASMA
	LPC_SC -> PCONP |= (1 << 20);
  init_timer(0, 0, 0, 1, 0x5F5E10); //TIM2 - MR0
	init_timer(0, 0, 1, 3, 0xBEBC20); //TIM2 - MR1
	enable_timer(0);
*/

	//EMULATORE timer 0 FANTASMA
	LPC_SC -> PCONP |= (1 << 20);  
  init_timer(0, 0, 0, 1, 0x7A120); //TIM2 - MR0
	init_timer(0, 0, 1, 3, 0xF4240); //TIM2 - MR1
	enable_timer(0);


	//SCHEDA timer 1 (PUNTI, VITE, TEMPO)
	LPC_SC -> PCONP |= (1 << 21);  // TURN ON TIMER 1
  init_timer(1, 0, 0, 1, 0xBEBC20); //TIM2 - MR0
	init_timer(1, 0, 1, 3, 0x17D7840); //TIM2 - MR1
	enable_timer(1);

/*
	//SCHEDA timer 2 MOVIMENTO
	LPC_SC -> PCONP |= (1 << 22);
  init_timer(2, 0, 0, 1, 0x2FAF08); //TIM2 - MR0
	init_timer(2, 0, 1, 3, 0x5F5E10); //TIM2 - MR1
	enable_timer(2);
*/

	//EMULATORE timer 2 MOVIMENTO
	LPC_SC -> PCONP |= (1 << 22);  
  init_timer(2, 0, 0, 1, 0x3D090); //TIM2 - MR0
	init_timer(2, 0, 1, 3, 0x7A120); //TIM2 - MR1
	enable_timer(2);


	// timer 3 (POWER PILLS)
	LPC_SC -> PCONP |= (1 << 23);
  init_timer(3, 0, 0, 1, 0x2625A0); //TIM2 - MR0
	init_timer(3, 0, 1, 3, 0x4C4B40); //TIM2 - MR1
	enable_timer(3);


	LCD_Clear(Black);
	
	Draw_table();
	Pacman_render();
	Fantasma_render();
	
	GUI_Text(15, 20, (uint8_t *) "  PAUSA: INT_0 TO START ", Red, Black);
	
	sprintf(Buffer_P, "Points= %d",points);
	sprintf(Buffer_T, "Tempo = %d",tempo);
	
	GUI_Text(0, 305, (uint8_t *) Buffer_P, Red, Black);
	GUI_Text(155, 305, (uint8_t *) Buffer_T, Red, Black);
	Pacman_printLife();



	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
	  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
