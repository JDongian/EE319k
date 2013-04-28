// FIFOTestMain.c
// Runs on any LM3Sxxx
// Test the functions provided in FIFO.c in two ways.  First, single-
// step through the first four tests of the program while watching the
// variables "letter" and "result" in the debugger.  Verify that they
// have the expected values after each line.  This test should show
// that the functions correctly implement a FIFO in the absence of
// complicating interrupts.  For the fifth test, let the program run
// for an extended period of time.  An interrupt will periodically
// fill the FIFO, and the main() function will continually empty the
// FIFO, checking that the actual received value matches the expected
// value.  This test is meant to show that interrupts at any point in
// the execution of the get() function will never cause the FIFO to
// lose data or return out of order.  Avoid single-stepping,
// especially in the main (foreground) function, because interrupts
// may continue between each step.  This may result in the FIFO
// erroneously overflowing, since it is not being emptied in the
// foreground.  To see the results of the test, look at the user LED
// (on PG2) or watch the global variables particularly "NumFullError",
// "EnteredCount", "Errors", and "LineHistogram".  The LED will be lit
// if "Errors" is non-zero, and the "LineHistogram" will give a record
// of which line of the get() function was interrupted.  The last
// index of the histogram represents the number of times that the
// interrupt missed the get() function.
// Daniel Valvano
// June 16, 2011

// Connect PF2,PF1,PF0 to logic analyzer
// PF2 high during timer ISR
// PF1 high during non critical part of main
// PF0 high during critical part of main (RxFifo_Get)

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to the Arm Cortex M3",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2011
      Programs 3.7, 3.8., 3.9 and 3.10 in Section 3.7


 Copyright 2011 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */
#include "hw_types.h"
#include "sysctl.h"
#include "lm3s1968.h"

#include "FIFO.h"

#define NVIC_EN0_INT19          0x00080000  // Interrupt 19 enable
#define NVIC_EN0_R              (*((volatile unsigned long *)0xE000E100))  // IRQ 0 to 31 Set Enable Register
#define NVIC_PRI4_R             (*((volatile unsigned long *)0xE000E410))  // IRQ 16 to 19 Priority Register
#define TIMER0_CFG_R            (*((volatile unsigned long *)0x40030000))
#define TIMER0_TAMR_R           (*((volatile unsigned long *)0x40030004))
#define TIMER0_CTL_R            (*((volatile unsigned long *)0x4003000C))
#define TIMER0_IMR_R            (*((volatile unsigned long *)0x40030018))
#define TIMER0_MIS_R            (*((volatile unsigned long *)0x40030020))
#define TIMER0_ICR_R            (*((volatile unsigned long *)0x40030024))
#define TIMER0_TAILR_R          (*((volatile unsigned long *)0x40030028))
#define TIMER0_TAR_R            (*((volatile unsigned long *)0x40030048))
#define TIMER_CFG_16_BIT        0x00000004  // 16-bit timer configuration,
                                            // function is controlled by bits
                                            // 1:0 of GPTMTAMR and GPTMTBMR
#define TIMER_TAMR_TAMR_PERIOD  0x00000002  // Periodic Timer mode
#define TIMER_CTL_TAEN          0x00000001  // GPTM TimerA Enable
#define TIMER_IMR_TATOIM        0x00000001  // GPTM TimerA Time-Out Interrupt
                                            // Mask
#define TIMER_ICR_TATOCINT      0x00000001  // GPTM TimerA Time-Out Raw
                                            // Interrupt
#define TIMER_TAILR_TAILRL_M    0x0000FFFF  // GPTM TimerA Interval Load
                                            // Register Low
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF0             (*((volatile unsigned long *)0x40025004))
#define GPIO_PORTF1             (*((volatile unsigned long *)0x40025008))
#define GPIO_PORTF2             (*((volatile unsigned long *)0x40025010))
#define GPIO_PORTF3             (*((volatile unsigned long *)0x40025020))
#define GPIO_PORTG_DATA_R       (*((volatile unsigned long *)0x400263FC))
#define GPIO_PORTG_DIR_R        (*((volatile unsigned long *)0x40026400))
#define GPIO_PORTG_DEN_R        (*((volatile unsigned long *)0x4002651C))
#define GPIO_PORTG2             (*((volatile unsigned long *)0x40026010))

#define SYSCTL_RCGC1_R          (*((volatile unsigned long *)0x400FE104))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define SYSCTL_RCGC1_TIMER0     0x00010000  // timer 0 Clock Gating Control
#define SYSCTL_RCGC2_GPIOG      0x00000040  // Port G Clock Gating Control
#define SYSCTL_RCGC2_GPIOF      0x00000020  // Port F Clock Gating Control
#define TX2FIFOSIZE             32
#define RX2FIFOSIZE             27
#define HISTOGRAMSIZE           32          // > 2*# instructions in get()
#define INTPERIOD               750         // interrupt period (50MHz cycles)
#define INTVARIATION            500         // maximum interrupt period variation from "INTPERIOD" (50MHz cycles)
AddIndexFifo(Tx2, TX2FIFOSIZE, char, 1, 0)
AddPointerFifo(Rx2, RX2FIFOSIZE, char, 1, 0)

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void WaitForInterrupt(void);  // low power mode

// basic test variables
volatile int result;
char letter;
// background variables
char BackData;               // data which is put
char BackCounter;            // number of puts per interrupt
unsigned long EnteredCount;  // number of times Put has interrupted Get
                             // record of lines where interrupt occurred
unsigned long LineHistogram[HISTOGRAMSIZE];
unsigned long LineHistogramAddress[HISTOGRAMSIZE];
// foreground variables
char ForeExpected;           // expected data
char ForeActual;             // actual data
unsigned short Errors;       // number of out-of-sequence points
unsigned short EnterGet;     // true if program has entered Get

// This function returns the return address from the current interrupt.
// For valid results, it must be called from within an interrupt.
// The first line started with [SP, #24], but had to be changed to
// [SP, #40] because Timer0A_Handler() pushed 4 32-bit numbers on the
// stack.

#ifdef __TI_COMPILER_VERSION__
//THE TI VERSION IS UNTESTED!!! (40 is a hardcode)
unsigned long Who(void){
	__asm (	"    LDR R0, [SP,#40]		; R0 = return address from interrupt\n"
		"    bx  LR\n");
}


#else
	__asm unsigned long
	Who(void){
    LDR R0, [SP,#40]               ; R0 = return address from interrupt
    bx  LR
	}

#endif

void Timer0A_Handler(void){
  unsigned long returnaddress;
  unsigned char i;
  static char periodShift = 1;
  GPIO_PORTF2 = 0x04;               // debuging profile
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// acknowledge timer0A timeout
  if(INTVARIATION != 0){            // set time of next interrupt if needed
    TIMER0_TAILR_R = TIMER0_TAILR_R + periodShift;
                                    // check upper bound
    if(((TIMER0_TAILR_R + periodShift) > (INTPERIOD + INTVARIATION - 1)) ||
                                    // check lower bound
     ((TIMER0_TAILR_R + periodShift) < (INTPERIOD - INTVARIATION - 1))){
      periodShift = -periodShift; // start counting in other direction
    }
  }
  if(EnterGet){        // Put has interrupted Get
    EnteredCount = EnteredCount + 1;
  }
  for(i=0; i<=BackCounter; i=i+1){
    if(RxFifo_Put(BackData)){
      BackData = BackData + 1; // sequence is 0,1,2,3,...,254,255,0,1,...
    }                          // ignore full FIFO
  }
  BackCounter = BackCounter + 1;
  if(BackCounter == 10){
    BackCounter = 0;   // 0 to 9
  }
  returnaddress = Who();
  if((returnaddress < (unsigned long)&RxFifo_Get) || (returnaddress >= (unsigned long)&RxFifo_Size)){
    returnaddress = (unsigned long)&RxFifo_Size;
  }
  LineHistogram[(returnaddress - (unsigned long)&RxFifo_Get)/2]++;
  GPIO_PORTF2 = 0x00;
}

int main(void){
  int i;
  SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN |
                 SYSCTL_XTAL_8MHZ);        // 50 MHz
  // **** general initialization ****
  DisableInterrupts();
  SYSCTL_RCGC1_R |= SYSCTL_RCGC1_TIMER0;// activate timer0
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF+SYSCTL_RCGC2_GPIOG; // activate ports F and G
  BackData = 0;                    // allow time to finish activating
  BackCounter = 0;
  EnteredCount = 0;
  ForeExpected = 0;
  Errors = 0;
  EnterGet = 0;
  GPIO_PORTF_DIR_R |= 0x0F;        // make PF3-PF0 out (connect to scope/logic analyzer)
  GPIO_PORTF_DEN_R |= 0x0F;        // enable digital I/O on PF3-PF0
  GPIO_PORTG_DIR_R |= 0x04;        // make PG2 out (PG2 built-in LED)
  GPIO_PORTG_DEN_R |= 0x04;        // enable digital I/O on PG2
  GPIO_PORTG2 = 0x00;              // clear PG2
  GPIO_PORTF0 = 0x00;
  GPIO_PORTF1 = 0x00;
  GPIO_PORTF2 = 0x00;
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
  TIMER0_CFG_R = TIMER_CFG_16_BIT; // configure for 16-bit timer mode
  // **** timer0A initialization ****
  TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;// configure for periodic mode
  TIMER0_TAILR_R = INTPERIOD - 1;  // start value to count down from
  TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
  // **** interrupt initialization ****
                                   // Timer0A=priority 2
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // top 3 bits
  NVIC_EN0_R |= NVIC_EN0_INT19;    // enable interrupt 19 in NVIC

  // *************** Test #5: test interrupt vulnerability ************
  RxFifo_Init();
  for(i=0; i<HISTOGRAMSIZE; i=i+1){ unsigned long returnaddress;
    LineHistogram[i] = 0;
    returnaddress = ((unsigned long)&RxFifo_Get + 2*i)&0xFFFFFFFE;
    LineHistogramAddress[i] = returnaddress;   // possible places in Get that could be interrupted
  }
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
  TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 16-b, periodic, interrupts
  EnableInterrupts();
  while(1){
    do{
      GPIO_PORTF0 = 1;       // profile of main program
      EnterGet = 1;
      i = RxFifo_Get(&ForeActual);  // i = 0 (FIFOFAIL) if error
      EnterGet = 0;
      GPIO_PORTF0 = 0; 
    }
    while(!i);
    GPIO_PORTF1 = 2;       // profile of main program

    if(ForeExpected != ForeActual){
      Errors = Errors + 1;           // critical section found
      ForeExpected = ForeActual + 1; // resych to lost/bad data
      GPIO_PORTG2 = 0x04;            // set PG2, means error
    }
    else{
      ForeExpected = ForeExpected + 1;// sequence is 0,1,2,3,...,254,255,0,1,...
    }
    GPIO_PORTF1 = 0; 
  }
}
int main2(void){    int i;
  // *************** Test #1: test transmit (index) FIFO **************
  TxFifo_Init();
  result = TxFifo_Get(&letter); // letter = ??, result = 0
  result = TxFifo_Put('A');     // result = 1
  result = TxFifo_Put('B');     // result = 1
  result = TxFifo_Put('C');     // result = 1
  result = TxFifo_Get(&letter); // letter = 0x41, result = 1
  result = TxFifo_Get(&letter); // letter = 0x42, result = 1
  result = TxFifo_Put('D');     // result = 1
  result = TxFifo_Size();       // result = 2
  result = TxFifo_Get(&letter); // letter = 0x43, result = 1
  result = TxFifo_Get(&letter); // letter = 0x44, result = 1
  result = TxFifo_Size();       // result = 0
  result = TxFifo_Get(&letter); // letter = ??, result = 0
  for(i='A'; i<'A'+TXFIFOSIZE; i=i+1){
    result = TxFifo_Put(i);     // result = 1
  }
  result = TxFifo_Size();       // result = 16
  result = TxFifo_Get(&letter); // letter = 0x41, result = 1
  result = TxFifo_Size();       // result = 15
  result = TxFifo_Get(&letter); // letter = 0x42, result = 1
  result = TxFifo_Size();       // result = 14
  result = TxFifo_Put(' ');     // result = 1
  result = TxFifo_Size();       // result = 15
  // *************** Test #2: test receive (pointer) FIFO *************
  RxFifo_Init();
  result = RxFifo_Get(&letter); // letter = ??, result = 0
  result = RxFifo_Put('A');     // result = 1
  result = RxFifo_Put('B');     // result = 1
  result = RxFifo_Put('C');     // result = 1
  result = RxFifo_Get(&letter); // letter = 0x41, result = 1
  result = RxFifo_Get(&letter); // letter = 0x42, result = 1
  result = RxFifo_Put('D');     // result = 1
  result = RxFifo_Size();       // result = 2
  result = RxFifo_Get(&letter); // letter = 0x43, result = 1
  result = RxFifo_Get(&letter); // letter = 0x44, result = 1
  result = RxFifo_Size();       // result = 0
  result = RxFifo_Get(&letter); // letter = ??, result = 0
  for(i='A'; i<'A'+RXFIFOSIZE-1; i=i+1){
    result = RxFifo_Put(i);     // result = 1
  }
  result = RxFifo_Size();       // result = 9
  result = RxFifo_Get(&letter); // letter = 0x41, result = 1
  result = RxFifo_Size();       // result = 8
  result = RxFifo_Get(&letter); // letter = 0x42, result = 1
  result = RxFifo_Size();       // result = 7
  result = RxFifo_Put(' ');     // result = 1
  result = RxFifo_Size();       // result = 8
  // *********** Test #3: test transmit (index) FIFO creator **********
  Tx2Fifo_Init();
  result = Tx2Fifo_Get(&letter);// letter = ??, result = 0
  result = Tx2Fifo_Put('A');    // result = 1
  result = Tx2Fifo_Put('B');    // result = 1
  result = Tx2Fifo_Put('C');    // result = 1
  result = Tx2Fifo_Get(&letter);// letter = 0x41, result = 1
  result = Tx2Fifo_Get(&letter);// letter = 0x42, result = 1
  result = Tx2Fifo_Put('D');    // result = 1
  result = Tx2Fifo_Size();      // result = 2
  result = Tx2Fifo_Get(&letter);// letter = 0x43, result = 1
  result = Tx2Fifo_Get(&letter);// letter = 0x44, result = 1
  result = Tx2Fifo_Size();      // result = 0
  result = Tx2Fifo_Get(&letter);// letter = ??, result = 0
  for(i='A'; i<'A'+TX2FIFOSIZE; i=i+1){
    result = Tx2Fifo_Put(i);    // result = 1
  }
  result = Tx2Fifo_Size();      // result = 32
  result = Tx2Fifo_Get(&letter);// letter = 0x41, result = 1
  result = Tx2Fifo_Size();      // result = 31
  result = Tx2Fifo_Get(&letter);// letter = 0x42, result = 1
  result = Tx2Fifo_Size();      // result = 30
  result = Tx2Fifo_Put(' ');    // result = 1
  result = Tx2Fifo_Size();      // result = 31
  // *********** Test #4: test receive (pointer) FIFO creator *********
  Rx2Fifo_Init();
  result = Rx2Fifo_Get(&letter);// letter = ??, result = 0
  result = Rx2Fifo_Put('A');    // result = 1
  result = Rx2Fifo_Put('B');    // result = 1
  result = Rx2Fifo_Put('C');    // result = 1
  result = Rx2Fifo_Get(&letter);// letter = 0x41, result = 1
  result = Rx2Fifo_Get(&letter);// letter = 0x42, result = 1
  result = Rx2Fifo_Put('D');    // result = 1
  result = Rx2Fifo_Size();      // result = 2
  result = Rx2Fifo_Get(&letter);// letter = 0x43, result = 1
  result = Rx2Fifo_Get(&letter);// letter = 0x44, result = 1
  result = Rx2Fifo_Size();      // result = 0
  result = Rx2Fifo_Get(&letter);// letter = ??, result = 0
  for(i='A'; i<'A'+RX2FIFOSIZE-1; i=i+1){
    result = Rx2Fifo_Put(i);    // result = 1
  }
  result = Rx2Fifo_Size();      // result = 26
  result = Rx2Fifo_Get(&letter);// letter = 0x41, result = 1
  result = Rx2Fifo_Size();      // result = 25
  result = Rx2Fifo_Get(&letter);// letter = 0x42, result = 1
  result = Rx2Fifo_Size();      // result = 24
  result = Rx2Fifo_Put(' ');    // result = 1
  result = Rx2Fifo_Size();      // result = 25
  while(1);
}
