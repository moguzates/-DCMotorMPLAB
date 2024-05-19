#include "lcd_library.h"

void bekle(void){
    __delay_us(250);
}
void lcd_komut(unsigned char c){
    rw=0;
    rs=0;
    e=1;
    port_lcd = (c & 0xF0);
    e=0;
    bekle();
    e=1;
    port_lcd = ( (c & 0x0F)<<4 );
    e=0;
    bekle();
}
void veri_yolla(unsigned char c){
    rw=0;
    rs=1;
    e=1;
    port_lcd = (c & 0xF0);
    e=0;
    bekle();
    e=1;
    port_lcd = ( (c & 0x0F)<<4 );
    e=0;
    bekle();
}
void lcd_sil(void){
    lcd_komut(sil);
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
    rs=0;
    e=0;
    rw=0;
    __delay_ms(15);
    e=1;
    lcd_komut(0x02);
    __delay_ms(2);
    lcd_komut(CiftSatir);
    lcd_komut(Sagayaz);
    lcd_komut(ImlecGizle);
    lcd_sil();
    lcd_komut(BirinciSatir);
}


