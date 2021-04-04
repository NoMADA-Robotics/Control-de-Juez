/*
 * Control de juez.c
 *
 * Created: 27/02/2021 22:52:37
 * Author : Sol
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define RESET PIN6_bm//reset en PA6(reset y ready creo que estan al revez en el equemático)
#define READY PIN3_bm//ready en PA3
#define GO PIN7_bm//go en PA7
#define LEDS PIN3_bm//pin para transmisión de datos en PA2
#define LED_STATUS PIN2_bm//Led de estatus y transmición en PA1

int main(void)
{
	//CLKCTRL.MCLKCTRLB |= CLKCTRL_PEN_bm; (DIVICION DE RELOJ PARA 10 MHZ)
	
    //Configuración de pines de entrada
	PORTA.DIRCLR |= RESET|READY|GO;//ENTRADA DE LOS BOTONES DE ENCEDIDO
	PORTA.DIRSET |= LEDS|LED_STATUS;//Salida para los leds de transmisión y status
	PORTA.PIN3CTRL |= PORT_PULLUPEN_bm;//Resistencias de pullup para los botones
	PORTA.PIN6CTRL |= PORT_PULLUPEN_bm;
	PORTA.PIN7CTRL |= PORT_PULLUPEN_bm;
	
    while (1) 
    {
    }
}

