
/* 
 * File:   LCD_library.h
 * Author: DELL
 *
 * Created on 01 Ocak 2021 Cuma, 14:27
 */

#ifndef LCD_LIBRARY_H
#define LCD_LIBRARY_H

// Header file content goes here

#endif /* LCD_LIBRARY_H */

#pragma config FOSC = XT        // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON         // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM function; low-voltage programming enabled)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF         // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)
#define _XTAL_FREQ 4000000
#define rs  RB3
#define rw  RB1 
#define e   RB2
#define port_lcd PORTD
#define sil 1
#define BasaDon 2
#define Solayaz 4
#define Sagayaz 6
#define ImlecGizle 12
#define ImlecAltta 14
#define ImlecYanSon 15
#define ImlecGeri 16
#define KaydirSaga 24
#define KaydirSola 28
#define EkraniKapat 8
#define BirinciSatir 128
#define IkinciSatir 192
#define KarakUretAdres 64
#define CiftSatir 40
#define TekSatir 32
extern void bekle (void);
extern void veri_yolla(unsigned char c);
extern void lcd_sil(void);
extern void lcd_yaz(const char *s);
extern void lcd_gotolcd_yazxy(unsigned char x,unsigned char y);
extern void lcd_hazirla(void);
extern void lcd_komut(unsigned char c);

