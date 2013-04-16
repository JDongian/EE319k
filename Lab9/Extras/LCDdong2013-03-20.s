; LCD.s
; Runs on LM3S1968
; EE319K lab 6 device driver for the LCD
; Valvano
; March 2, 2013 (Spring 2013 version)
;
;  size is 1*16
;  because we do not need to read busy, then we will tie R/W=ground
;  10k potentiometer (not the slide pot for Lab 8)
;      one end of pot is +5V, 
;      center of pot to pin 3 of LCD,
;      other end of pot is ground
;  ground = pin 1    Vss
;  power  = pin 2    Vdd   +5V (EE319K LCDs)
;  pot    = pin 3    Vlc   connected to center of pot
;  PF4    = pin 4    RS    (1 for data, 0 for control/status)
;  ground = pin 5    R/W   (1 for read, 0 for write)
;  PF5    = pin 6    E     (enable)
;  PF0    = pin 11   DB4   (4-bit data)
;  PF1    = pin 12   DB5
;  PF2    = pin 13   DB6
;  PF3    = pin 14   DB7
;16 characters are configured as 2 rows of 8
;addr  00 01 02 03 04 05 06 07 40 41 42 43 44 45 46 47


        EXPORT   LCD_Open
        EXPORT   LCD_Clear
        EXPORT   LCD_OutChar
        EXPORT   LCD_GoTo
        EXPORT   LCD_OutString
        EXPORT   LCD_OutChar
        EXPORT   LCD_OutDec
        EXPORT   LCD_OutFix
	EXPORT	Wait
SYSCTL_RCGC2_R          EQU 0x400FE108
SYSCTL_RCGC2_GPIOF      EQU 0x00000020   ; port F Clock Gating Control

GPIO_PORTF_DIR_R        EQU 0x40025400
GPIO_PORTF_AFSEL_R      EQU 0x40025420
GPIO_PORTF_DEN_R        EQU 0x4002551C

GPIO_F					EQU 0x40025000
GPIO_LCD_CTRL_F			EQU 0x40025000 + 4*1 + 4*2 + 4*4 + 4*8
GPIO_LCD_E				EQU 0x40025000 + 4*16
GPIO_LCD_RS				EQU 0x40025000 + 4*32

	AREA    |.text|, CODE, READONLY, ALIGN=2
	THUMB
	ALIGN          

; -----------------------Modulo----------------------
; R0 = R0%R1
Modulo
decBase
	CMP R0, R1
	BLT retMod
	SUB R0, R0, R1
	B decBase
retMod
	BX LR
	
;---------------------Delay------------------------
;Waits R0 cycles
; Input: R0 microseconds
; Output: none
; This is a public function
Wait
	MOV R1, #0x0D
	MUL R0, R0, R1
loopWait
	SUBS R0, R0, #0x01
	BEQ retWait
	B loopWait
retWait
	BX LR


;--------------- outCsrNibble ------------------
; Sends 4 bits to the LCD control/status
; Input: R0 is 4-bit command, in bit positions 3,2,1,0 of R0
; Output: none
; This is a private function
; Invariables: This function must not permanently modify registers R4 to R11
outCsrNibble
	PUSH {R4,R5,R14}
	LDR R2, =GPIO_LCD_E
	LDR R1, =GPIO_LCD_CTRL_F
	
	STR R0, [R1]
	
	MOV R0, #125
	BL Wait
	
	MOV R3, #0xFF	;Set E to 1 and wait 9000 ns
	STR R3, [R2]
	MOV R0, #9000
	BL Wait
	MOV R3, #0x00
	STR R3, [R2]
	
	MOV R0, #90
	BL Wait
	
	POP {R4,R5,PC}

;---------------------outCsr---------------------
; Sends one command code to the LCD control/status
; Input: R0 is 8-bit command to execute
; Output: none
;* Entry Mode Set 0,0,0,0,0,1,I/D,S
;*     I/D=1 for increment cursor move direction
;*        =0 for decrement cursor move direction
;*     S  =1 for display shift
;*        =0 for no display shift
;*   Display On/Off Control 0,0,0,0,1,D,C,B
;*     D  =1 for display on
;*        =0 for display off
;*     C  =1 for cursor on
;*        =0 for cursor off
;*     B  =1 for blink of cursor position character
;*        =0 for no blink
;*   Cursor/Display Shift  0,0,0,1,S/C,R/L,*,*
;*     S/C=1 for display shift
;*        =0 for cursor movement
;*     R/L=1 for shift to left
;*        =0 for shift to right
;*   Function Set   0,0,1,DL,N,F,*,*
;*     DL=1 for 8 bit
;*       =0 for 4 bit
;*     N =1 for 2 lines
;*       =0 for 1 line
;*     F =1 for 5 by 10 dots
;*       =0 for 5 by 7 dots 
; This is a private function
; Invariables: This function must not permanently modify registers R4 to R11
outCsr
    PUSH {R4,LR}
	LDR R2, =GPIO_LCD_RS
	MOV R1, #0x00
	STR R1, [R2]
	
	MOV R1, R0
	LSR R1, #4
	MOV R0, R1
	BL outCsrNibble
	MOV R0, R1
	BL outCsrNibble
	;MOV R0, #9000
	;BL Wait
    POP  {R4,PC}


;---------------------LCD_Open---------------------
; initialize the LCD display, called once at beginning
; Input: none
; Output: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_Open 
    PUSH {LR}
	
	LDR R1, =SYSCTL_RCGC2_R     
    LDR R0, [R1]
    ORR R0, R0, #(SYSCTL_RCGC2_GPIOF) ; activate port E and port F 
    STR R0, [R1]                 
    NOP
    NOP 
	; set direction register
    LDR R1, =GPIO_PORTF_DIR_R       ; R1 = &GPIO_PORTG_DIR_R
    LDR R0, [R1]                    ; R0 = [R1]
    ORR R0, R0, #0x3F               ; R0 = R0|0x04 (make PG2 output)
    STR R0, [R1]                    ; [R1] = R0
    ; regular port function
    LDR R1, =GPIO_PORTF_AFSEL_R     ; R1 = &GPIO_PORTG_AFSEL_R
    LDR R0, [R1]                    ; R0 = [R1]
    BIC R0, R0, #0x84               ; R0 = R0&~0x04 (disable alt funct on PG2) (default setting)
    STR R0, [R1]                    ; [R1] = R0
    ; enable digital port
    LDR R1, =GPIO_PORTF_DEN_R       ; R1 = &GPIO_PORTG_DEN_R
    LDR R0, [R1]                    ; R0 = [R1]
    ORR R0, R0, #0x84               ; R0 = R0|0x04 (enable digital I/O on PG2) (default setting on LM3S811, not default on other microcontrollers)
    STR R0, [R1]                    ; [R1] = R0
    
;0) save any registers that will be destroyed by pushing on the stack
;1) wait 20ms allowing the LCD to power up
	LDR R0, =20000
	BL Wait	
;2) set direction register(s) so that the six pins are output signals to the LCD
;3) outCsrNibble(0x03) (DL=1 8-bit mode)
	MOV R0, #0x03
	BL outCsrNibble
;4) blind cycle 5ms wait
	MOV R0, #5000
	BL Wait
;5) outCsrNibble(0x03) (DL=1 8-bit mode)
	MOV R0, #0x03
	BL outCsrNibble
;6) blind cycle 100us wait
	MOV R0, #100
	BL Wait
;7) outCsrNibble(0x03) (DL=1 8-bit mode)
	MOV R0, #0x03
	BL outCsrNibble
;8) blind cycle 100us wait (not called for, but do it anyway)
	MOV R0, #100
	BL Wait
;9) outCsrNibble(0x02)(DL=0 4-bit mode)
	MOV R0, #0x02
	BL outCsrNibble
;10)blind cycle 100 us wait
	MOV R0, #100
	BL Wait
;11)outCsr(0x28) // DL=0 4-bit, N=1 2-line, F=0 5by7 dots
	MOV R0, #0x28
	BL outCsr
;12)outCsr(0x14) // S/C=0 cursormove, R/L=1 shiftright
	MOV R0, #0x14
	BL outCsr
;13)outCsr(0x06) // I/D=1 Increment, S=0 no displayshift
	MOV R0, #0x06
	BL outCsr
;14)outCsr(0x0C) // D=1 displayon, C=0 cursoroff, B=0 blink off
	MOV R0, #0x0C
	BL outCsr
;15)restore the registers by pulling off the stack
    POP {PC}


;---------------------LCD_OutChar---------------------
; sends one ASCII to the LCD display
; Input: R0 (call by value) letter is 8-bit ASCII code
; Outputs: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutChar
    PUSH {R4,LR}
	LDR R2, =GPIO_LCD_RS
	MOV R1, #0x20
	STR R1, [R2]
	
	MOV R1, R0
	LSR R1, #4
	MOV R0, R1
	BL outCsrNibble
	MOV R0, R1
	BL outCsrNibble
	;MOV R0, #9000
	;BL Wait
    POP {R4,PC}

;---------------------LCD_Clear---------------------
; clear the LCD display, send cursor to home
; Input: none
; Outputs:  one
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_Clear
    PUSH {LR}
    
    	LDR R2, =GPIO_LCD_RS
	MOV R1, #0x00
	STR R1, [R2]
    
;1) output a 0x01 command
	MOV R0, #0x01
	BL outCsr
;2) step 2 is to wait ~1.64ms
	MOV R0, #1640
	BL Wait
;3) output a 0x02 command
	MOV R0, #0x02
	BL outCsr
;4) wait an additional ~1.64ms.
	MOV R0, #1640
	BL Wait
    POP  {PC}


;-----------------------LCD_GoTo-----------------------
; Move cursor (set display address) 
; Input: R0 is display address (DDaddr) is 0 to 7, or 0x40 to 0x47 
; Output: none
; errors: it will check for legal address
;  0) save any registers that will be destroyed by pushing on the stack
;  1) go to step 3 if DDaddr is 0x08 to 0x3F or 0x48 to 0xFFFFFFFF
;  2) outCsr(DDaddr+0x80)     
;  3) restore the registers by pulling off the stack
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_GoTo
    PUSH {LR}
;0) save any registers that will be destroyed by pushing on the stack
;1) go to step 3 if DDaddr is 0x08 to 0x3F or 0x48 to 0xFF
	MOV R1, R0
	BIC R0, R1, #0xB8
	CMP R0, #0x00
	BNE outOfBounds
;2) outCsr(DDaddr+0x80)
	ADD R0, R0, #0x80
	BL outCsr
;3) restore the registers by pulling off the stack
outOfBounds
    POP  {PC}

; ---------------------LCD_OutString-------------
; Output character string to LCD display, terminated by a NULL(0)
; Inputs:  R0 (call by reference) points to a string of ASCII characters 
; Outputs: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutString
    PUSH {R4,LR}   
	MOV R1, R0
stringItr
	LDR R0, [R1]
	CBZ R0, outStringEnd
	BL LCD_OutChar
	ADD R1, R1, #1
	BL stringItr
outStringEnd
    POP {R4,PC}



;-----------------------LCD_OutDec-----------------------
; Output a 32-bit number in unsigned decimal format
; Input: R0 (call by value) 32-bit unsigned number 
; Output: none
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutDec
    PUSH {R0,R4,LR}
	
	MOV R3, 0x00	; R3 = counter
	MOV R2, R0		; R2 = val
	MOV R1, #10		; mod 10

	MOV R0, #0x00
	PUSH{R0}
	
nextDigit
	MOV R0, R2
	BL Modulo
	ADD R0, R0, #0x30 ; R0 = chr(R2%10)
	
	PUSH{R0}
	ADD R3, R3, #0x01
	
	UDIV R2, R2, R1 ; R2 = R2/10
	BNE nextDigit
	
printDigits
	CMP R3, #0x00
	BEQ retOutDec
	POP{R0}
	BL LCD_OutChar
	SUB R3, R3, #0x01
	B printDigits
retOutDec

    POP  {R0,R4,PC}

; -----------------------LCD _OutFix----------------------
; Output characters to LCD display in fixed-point format
; unsigned decimal, resolution 0.001, range 0.000 to 9.999 
; Inputs:  R0 is an unsigned 16-bit number
; Outputs: none
; E.g., R0=0,    then output "0.000 " 
;       R0=3,    then output "0.003 " 
;       R0=89,   then output "0.089 " 
;       R0=123,  then output "0.123 " 
;       R0=9999, then output "9.999 " 
;       R0>9999, then output "*.*** "
; This is a public function
; Invariables: This function must not permanently modify registers R4 to R11
LCD_OutFix
    PUSH {LR}
	MOV R2, R0
	MOV R1, #10

	BL Modulo
	PUSH{R0}
	UDIV R2, R2, R1
	
	MOV R0, R2
	BL Modulo
	PUSH{R0}
	UDIV R2, R2, R1
	
	MOV R0, R2
	BL Modulo
	PUSH{R0}
	UDIV R2, R2, R1
	
	MOV R0, #0x2E
	PUSH{R0}
	
	MOV R0, R2
	BL Modulo
	PUSH{R0}
	UDIV R2, R2, R1
	
	POP{R0}
	BL LCD_OutChar
	POP{R0}
	BL LCD_OutChar
	POP{R0}
	BL LCD_OutChar
	POP{R0}
	BL LCD_OutChar
	POP{R0}
	BL LCD_OutChar
	
    POP {PC}

    ALIGN                           ; make sure the end of this section is aligned
    END                             ; end of file
    