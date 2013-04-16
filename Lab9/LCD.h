
//Methods
extern void LCD_Open(void);
extern void LCD_OutNibble(unsigned char);
extern void LCD_OutByte(unsigned char);
extern void LCD_OutCommand(unsigned char);
extern void LCD_OutData(unsigned int);
extern void LCD_OutString(char []);
extern void LCD_Clear(void);
extern void LCD_SetCursor(unsigned int);
extern void LCD_GoTo(unsigned int);
extern void LCD_OutDec(unsigned int);



