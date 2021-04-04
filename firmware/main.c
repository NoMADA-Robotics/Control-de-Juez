/*
 * Control juez firmware.c
 *
 * Created: 01/03/2021 03:32:32 p. m.
 * Author : SYSTEMS
 */ 
#define F_CPU 10000000UL //Frecuencia del cpu 20 MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/cpufunc.h>
#include <string.h>
//CALCULO DE BAUDIOS PARA TRANMISIÓN DE DATOS DEL PUERTO USART
#define USART0_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 * (float)BAUD_RATE)) + 0.5)
//DEFINICION PARA LOS PINES DE ENTRADA Y SALIDA
#define RESET PIN2_bm//RESET Y READY ESTAN AL REVEZ EN EL ESQUEMÁTICO
#define READY PIN6_bm
#define GO PIN7_bm
#define LED_DATOS PIN4_bm
#define LED_ESTATUS PIN3_bm


int main(void){
	//CONFIGURACIÓN DE VELOCIDAD DEL PROCESADOR PARA ESTAR EN LAS CARACTERISTICAS ELECTRICAS ESPECIFICADAS
	PORTA.DIRSET |= LED_DATOS|LED_ESTATUS;
	//CCP = CCP_IOREG_gc;//HABILITA LA ESCRITURA DE REGISTROS PROTEGIDOS
	//CLKCTRL.MCLKCTRLB = CLKCTRL_PDIV_2X_gc|CLKCTRL_PEN_bm;//FRECUENCIA DIVIDIDA ENTRE DIS Y HABILITADA
	ccp_write_io((void *) & (CLKCTRL.MCLKCTRLB), (CLKCTRL_PDIV_2X_gc|CLKCTRL_PEN_bm));
	//CONFIGURACIÓN DE PINES DE ENTRADA
   	PORTA.DIRCLR |= RESET|READY|GO;//PINES DE ENTRADA PARA LOS BOTONES
	PORTB.DIRSET |= LED_DATOS|LED_ESTATUS;//PINES DE SALIDA PARA LOS LEDS DE SALIDA Y LED DE ESTATUS
	PORTB.PIN2CTRL |= PORT_PULLUPEN_bm;//RESISTENCIA DE PULLUP PARA PUERTOS PA3,PA6 Y PA7
	PORTA.PIN6CTRL |= PORT_PULLUPEN_bm;
	PORTA.PIN7CTRL |= PORT_PULLUPEN_bm;
	PORTB.OUTCLR |= LED_ESTATUS;
	//CONFIGURACIÓN DE TIMER PARA TRANSMISIÓN DE DATOS, MANDAR ONDA CON PWM SINUSOIDAL?
	//TCA0.SINGLE.CTRLA |= TCA_SINGLE_CLKSEL_DIV16_gc;
	//TCA0.SINGLE.PER = 0x09C4;//0x5DC
	//TCA0.SINGLE.CTRLA |= 1;
	//TCA0.SINGLE.CTRLB |= TCA_SINGLE_CMP0EN_bm|TCA_SINGLE_WGMODE_SINGLESLOPE_gc;
	//TCA0.SINGLE.CMP0 = 0x9C4;
	////CONFIGURACION DE PUERTO USART PARA TRANSMISIÓN DE DATOS
	//USART0.CTRLB |= USART_ODME_bm;//modo de drenador abierto
	//USART0.BAUD = (uint16_t)USART0_BAUD_RATE(100000);
	//USART0.CTRLC = USART_CHSIZE_8BIT_gc|USART_CMODE0_bm;//Modo sincrono,7 bits para direccion en 12c XCLK en pin PA2
	//USART0.CTRLB |= USART_TXEN_bm;//|USART_RXEN_bm;habilita transmision
	////CONFIGURABLE CUSTOM LOGIC SUENA BIEN TIENE ENTRADA TCA WO Y USART CON AND USART Y TCA A 38 KHZ Y SALIDA CON EL PIN DE SALIDA
	//CCL.CTRLA |= CCL_ENABLE_bm;
	//
    while (1){
				if(PORTB.IN & RESET){//LECTURA DEL BOTON, EL BOTÓN CONECTA CON TIERRA POR LO QUE EL IF ENTRA CUANDO NO ESTA PRESIONADO
					PORTB.OUTSET |= LED_ESTATUS;
					}else{
					PORTB.OUTCLR |= LED_ESTATUS;
				}
    }
}
