#include "serial.h"

#include "stm32f303xc.h"

// We store the pointers to the GPIO and USART that are used
//  for a specific serial port. To add another serial port
//  you need to select the appropriate values.
struct _SerialPort {
	USART_TypeDef *UART;
	GPIO_TypeDef *GPIO;
	volatile uint32_t MaskAPB2ENR;	// mask to enable RCC APB2 bus registers
	volatile uint32_t MaskAPB1ENR;	// mask to enable RCC APB1 bus registers
	volatile uint32_t MaskAHBENR;	// mask to enable RCC AHB bus registers
	volatile uint32_t SerialPinModeValue;
	volatile uint32_t SerialPinSpeedValue;
	volatile uint32_t SerialPinAlternatePinValueLow;
	volatile uint32_t SerialPinAlternatePinValueHigh;
	void (*completion_function)(uint32_t, uint32_t);
};



// instantiate the serial port parameters
//   note: the complexity is hidden in the c file
SerialPort USART1_PORT = {USART1,
		GPIOC,
		RCC_APB2ENR_USART1EN, // bit to enable for APB2 bus
		0x00,	// bit to enable for APB1 bus
		RCC_AHBENR_GPIOCEN, // bit to enable for AHB bus
		0xA00,
		0xF00,
		0x770000,  // for USART1 PC10 and 11, this is in the AFR low register
		0x00, // no change to the high alternate function register
		0x00 // default function pointer is NULL
		};


// InitialiseSerial - Initialise the serial port
// Input: baudRate is from an enumerated set
void SerialInitialise(uint32_t baudRate, SerialPort *serial_port, void (*completion_function)(uint32_t)) {

	serial_port->completion_function = completion_function;

	// enable clock power, system configuration clock and GPIOC
	// common to all UARTs
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	// enable the GPIO which is on the AHB bus
	RCC->AHBENR |= serial_port->MaskAHBENR;

	// set pin mode to alternate function for the specific GPIO pins
	serial_port->GPIO->MODER = serial_port->SerialPinModeValue;

	// enable high speed clock for specific GPIO pins
	serial_port->GPIO->OSPEEDR = serial_port->SerialPinSpeedValue;

	// set alternate function to enable USART to external pins
	serial_port->GPIO->AFR[0] |= serial_port->SerialPinAlternatePinValueLow;
	serial_port->GPIO->AFR[1] |= serial_port->SerialPinAlternatePinValueHigh;

	// enable the device based on the bits defined in the serial port definition
	RCC->APB1ENR |= serial_port->MaskAPB1ENR;
	RCC->APB2ENR |= serial_port->MaskAPB2ENR;

	// Get a pointer to the 16 bits of the BRR register that we want to change
	uint16_t *baud_rate_config = (uint16_t*)&serial_port->UART->BRR; // only 16 bits used!

	switch(baudRate){
	case BAUD_9600:

		*baud_rate_config = 0x342;  // 115200 at 8MHz
		break;
	case BAUD_19200:

		*baud_rate_config = 0x1a1;  // 115200 at 8MHz
		break;
	case BAUD_38400:

		*baud_rate_config = 0xd1;  // 115200 at 8MHz
		break;
	case BAUD_57600:

		*baud_rate_config = 0x8b;  // 115200 at 8MHz
		break;
	case BAUD_115200:
		*baud_rate_config = 0x46;  // 115200 at 8MHz
		break;
	}


	// enable serial port for tx and rx
	serial_port->UART->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}


void SerialOutputChar(uint8_t data, SerialPort *serial_port) {

	while((serial_port->UART->ISR & USART_ISR_TXE) == 0){
	} //This checks whether a flag has been waiting


	serial_port->UART->TDR = data;
}



void SerialOutputString(uint8_t *pt, SerialPort *serial_port) {

	uint32_t counter = 0;
	while(*pt) {
		SerialOutputChar(*pt, serial_port);
		counter++;
		pt++;
	}

	//serial_port->completion_function(counter);
}


void SerialReadChar(uint8_t *incoming_buffer, SerialPort *serial_port) {

	while (((serial_port->UART->ISR & (USART_ISR_ORE | USART_ISR_FE)) != 0)) {
		// set the flags ORECF and FECF to 1
		serial_port->UART->ICR = serial_port->UART->ICR | (1 << 3 | 1 << 1);
	}

	if ((serial_port->UART->ISR & USART_ISR_RXNE) == 0) {
		SerialReadChar(incoming_buffer, serial_port);
		//This causes an infinite loop

	}

	else {
		*incoming_buffer = serial_port->UART->RDR;
		serial_port->UART->RQR |= (1 << 3 | 1 << 1) ;
	}

}

void SerialReadString(uint8_t *incoming_buffer, SerialPort *serial_port) {
	uint32_t counter = 0;

	while((*incoming_buffer != '+')) {
		SerialReadChar((incoming_buffer+1), serial_port);
		counter++;
		incoming_buffer++;
	}
	serial_port->completion_function((incoming_buffer - (counter-1)), counter);
}

void LED_string(uint8_t *string, uint32_t counter) {

	for(int i = 0; (i) < (counter-1); i++) {

	uint8_t *led_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
	*led_register = string[i]; //I am unable to write into the led_register
	//Insert Delay function

	}
}


void initialise_board() {
	// get a pointer to the second half word of the MODER register (for outputs pe8-15)
	uint16_t *led_output_registers = ((uint16_t *)&(GPIOE->MODER)) + 1;
	*led_output_registers = 0x5555;
}


void enable_clocks() {

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOEEN;

}
