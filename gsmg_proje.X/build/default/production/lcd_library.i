# 1 "lcd_library.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files/Microchip/MPLABX/v6.05/packs/Microchip/PIC16Fxxx_DFP/1.3.42/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "lcd_library.c" 2
# 1 "./lcd_library.h" 1
# 16 "./lcd_library.h"
#pragma config FOSC = XT
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config BOREN = ON
#pragma config LVP = ON
#pragma config CPD = OFF
#pragma config WRT = OFF
#pragma config CP = OFF
# 45 "./lcd_library.h"
extern void bekle (void);
extern void veri_yolla(unsigned char c);
extern void lcd_sil(void);
extern void lcd_yaz(const char *s);
extern void lcd_gotolcd_yazxy(unsigned char x,unsigned char y);
extern void lcd_hazirla(void);
extern void lcd_komut(unsigned char c);
# 1 "lcd_library.c" 2


void bekle(void){
    __delay_us(250);
}
void lcd_komut(unsigned char c){
    RB1=0;
    RB3=0;
    RB2=1;
    PORTD = (c & 0xF0);
    RB2=0;
    bekle();
    RB2=1;
    PORTD = ( (c & 0x0F)<<4 );
    RB2=0;
    bekle();
}
void veri_yolla(unsigned char c){
    RB1=0;
    RB3=1;
    RB2=1;
    PORTD = (c & 0xF0);
    RB2=0;
    bekle();
    RB2=1;
    PORTD = ( (c & 0x0F)<<4 );
    RB2=0;
    bekle();
}
void lcd_sil(void){
    lcd_komut(1);
    __delay_ms(2);
}
void lcd_yaz(const char *s){
    bekle();
    while(*s){
        veri_yolla(*s++);
    }
}
void lcd_gotoxy(unsigned char x,unsigned char y){
    if(x==1)
        lcd_komut(0x80+((y-1)%16));
    else
        lcd_komut(0xC0+((y-1)%16));
}
void lcd_hazirla(void){
    RB3=0;
    RB2=0;
    RB1=0;
    __delay_ms(15);
    RB2=1;
    lcd_komut(0x02);
    __delay_ms(2);
    lcd_komut(40);
    lcd_komut(6);
    lcd_komut(12);
    lcd_sil();
    lcd_komut(128);
}
