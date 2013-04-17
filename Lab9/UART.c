// Simple device driver for the UART.

// U0Rx (VCP receive) connected to PA0
// U0Tx (VCP transmit) connected to PA1

#include "UART.h"

long debugLoops;
long errors;


//------------UART_Init------------
// Wait for new serial port input
// Initialize the UART for 115,200 baud rate (assuming 50 MHz UART clock),
// 8 bit word length, no parity bits, one stop bit, FIFOs enabled
// Input: none
// Output: none
void UART_Init(void){
	debugLoops = 0;
	errors = 0;
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_UART1; // activate UART1
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD; // activate port D
	delay(10);
  UART1_CTL_R &= ~UART_CTL_UARTEN;      // disable UART
  UART1_IBRD_R = 27;                    // IBRD = int(50,000,000 / (16 * 115,200)) = int(27.1267)
  UART1_FBRD_R = 8;                     // FBRD = int(0.1267 * 64 + 0.5) = 8
                                        // 8 bit word length (no parity bits, one stop bit, FIFOs)
  UART1_LCRH_R = (UART_LCRH_WLEN_8|UART_LCRH_FEN);
  UART1_CTL_R |= UART_CTL_UARTEN;       // enable UART
  GPIO_PORTD_AFSEL_R |= 0x0C;           // enable alt funct on PA1-0
  GPIO_PORTD_DEN_R |= 0x0C;             // enable digital I/O on PA1-0
}

//------------UART_InChar------------
// Wait for new serial port input
// Input: none
// Output: ASCII code for key typed
unsigned char UART_InChar(void){
  while((UART1_FR_R&UART_FR_RXFE) != 0);
  return((unsigned char)(UART1_DR_R&0xFF));
}
//------------UART_OutChar------------
// Output 8-bit to serial port
// Input: letter is an 8-bit ASCII character to be transferred
// Output: none
void UART_OutChar(unsigned char data){
  while((UART1_FR_R&UART_FR_TXFF) != 0);
  UART1_DR_R = data;
}

//------------UART_OutString------------
// Output String (NULL termination)
// Input: pointer to a NULL-terminated string to be transferred
// Output: none
void UART_OutString(char *pt){
  while(*pt){
    UART_OutChar(*pt);
    pt++;
  }
}

//------------UART_InString------------
// Accepts ASCII characters from the serial port
//    and adds them to a string until <enter> is typed
//    or until max length of the string is reached.
// It echoes each character as it is inputted.
// If a backspace is inputted, the string is modified
//    and the backspace is echoed
// terminates the string with a null character
// uses busy-waiting synchronization on RDRF
// Input: pointer to empty buffer, size of buffer
// Output: Null terminated string
// -- Modified by Agustinus Darmawan + Mingjie Qiu --
void UART_InString(char *bufPt, unsigned short max) {
int length=0;
char character;
  character = UART_InChar();
  while(character != CR){
    if(character == BS){
      if(length){
        bufPt--;
        length--;
        UART_OutChar(BS);
      }
    }
    else if(length < max){
      *bufPt = character;
      bufPt++;
      length++;
      UART_OutChar(character);
    }
    character = UART_InChar();
  }
  *bufPt = 0;
}

//------------UART_Handler------------
// Activated when data is input from the UART line
// Input: data byte
// Output: None
void UART1_Handler(void) {
	while(UART_FR_RXFE == 0){
		RxFifo_Put(UART1_DR_R);
		if(RxFifo_Size() > 16){
			errors += 1;
			break;
		}
	}
	debugLoops += 1;
	UART1_ICR_R = 0x10;
	GPIO_PORTG_DATA_R ^= 0x04;
	return;
}

//------------UART_Enable------------
// Activate UART_Handler
// Input: None
// Output: None
void UART_Enable(void) {
	UART1_IM_R |= 0x10;
	UART1_IFLS_R |= 0x38;
	NVIC_PRI1_R |= 0xE00000;
	NVIC_EN0_R ^= 2<<6;
}

