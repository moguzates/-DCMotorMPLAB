#include <xc.h>  
#include <stdio.h>

#pragma config FOSC = XT // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = OFF // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = ON // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3/PGM pin has PGM

#pragma config CPD = OFF // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF // Flash Program Memory Write Enable bits (Write protection off; all program memory may be

#pragma config CP = OFF // Flash Program Memory Code Protection bit (Code protection off)

#define _XTAL_FREQ 4000000  //Kristal frekans?
#define Sil 1
#define BasaDon 2
#define SolaYaz 4
#define SagaYaz 5
#define ImlecGizle 12
#define ImlecYanSon 15
#define ImlecGeri 16
#define KaydirSaga 24
#define KaydirSola 28
#define EkraniKapat 8
#define BirinciSatir 128
#define IkinciSatir 192
#define KarakterUretAdres 64
#define CiftSatir8Bit 56
#define CiftSatir4Bit 48
#define TekSatir8Bit 40
#define TekSatir4Bit 32
#define RS RC0
#define RW RC6
#define E RC3
#define Data PORTD

void Lcd_Port(char a){
    if(a & 1)
        RD4 = 1;
    else
        RD4 = 0;
    if(a & 2)
        RD5 = 1;
    else
        RD5 = 0;
    if(a & 4)
        RD6 = 1;
    else
        RD6 = 0;
    if(a & 8)
        RD7 = 1;
    else
        RD7 = 0;
 }

void Lcd_Cmd(char a)
{
    RS = 0;
    Lcd_Port(a);
    E = 1;
     __delay_ms(4);
     E = 0;
    }

void Lcd_Clear() 
        {
    Lcd_Cmd(0);
    Lcd_Cmd(1);
    }
void Lcd_Set_Cursor(char a, char b) 

{
    char temp,z,y;
    if(a == 1)
        {
         temp = 0x80 + b - 1;
        z = temp>>4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
    }
    else if(a == 2)
    {
        temp = 0xC0 + b - 1;
        z = temp>>4;
        y = temp & 0x0F;
        Lcd_Cmd(z);
        Lcd_Cmd(y);
        }
}
void Lcd_Init() 

{
    Lcd_Port(0x00);
    __delay_ms(20);
    Lcd_Cmd(0x03);
   __delay_ms(5);
    Lcd_Cmd(0x03);
   __delay_ms(11);
    Lcd_Cmd(0x03);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x02);
    Lcd_Cmd(0x08);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x0C);
    Lcd_Cmd(0x00);
    Lcd_Cmd(0x06);
}
void Lcd_Write_Char(char a) 

{
    char temp,y;
    temp = a&0x0F;
    y = a&0xF0;
    RS = 1;
    Lcd_Port(y>>4);
    E = 1;
    __delay_us(40);
    E = 0;
    Lcd_Port(temp);
    E = 1;
    __delay_us(40);
    E = 0;
}
void Lcd_Write_String(char *a) 

{
    int i;
    for(i=0;a[i]!='\0';i++)
     Lcd_Write_Char(a[i]);
}


void duty_sag(int pwm){
    
    CCP1X = pwm & 2;
    CCP1Y = pwm & 1;
    CCPR1L = pwm>>2;
    
}

void duty_sol(int pwm){
    
    CCP2X = pwm & 2;
    CCP2Y = pwm & 1;
    CCPR2L = pwm>>2;

}

void baslangic(){
    
    Lcd_Set_Cursor(1,1);
    Lcd_Write_String("   B210101373");
    Lcd_Set_Cursor(2,1); 
    Lcd_Write_String("   MELIH OGDUL");
    __delay_ms(3000);
    Lcd_Clear();
    
}
    
void motor(int sayac, int hiz){
    
    if (sayac == 0){  //sa? dön
        
        duty_sag(hiz);
        duty_sol(0);
        __delay_ms(2);    
        Lcd_Set_Cursor(2,9);
        Lcd_Write_String("SOL"); 
    }
    
    if (sayac == 1){ //sola dön

        duty_sol(hiz);
        duty_sag(0);
        __delay_ms(2);
        Lcd_Set_Cursor(2,9);
        Lcd_Write_String("SAG");
        
    }   
       
}

int sayac_hiz = 45;  //ba?lang?ç de?eri
void main(){
    int sayac; 
     
    
    TRISD = 0X00; 
    TRISC = 0X00;
    TRISB = 0XFF;
    PORTD = 0X00;
    PORTC = 0X00;
    PORTB = 0X00;
    
    Lcd_Init(); 
     
    CCP1M3 = 1; 
    CCP1M2 = 1;
    CCP2M3 = 1; 
    CCP2M2 = 1;
    T2CKPS0 = 1; 
    T2CKPS1 = 0;
    TMR2ON = 1; 
           
    TMR2 = 0;  
    PR2 = 249; 
    
    baslangic();
    unsigned int hiz;
    __delay_ms(2);

    while(1){  //h?z ve yön 

        Lcd_Set_Cursor(1,5);   
        Lcd_Write_String("HIZ:");
        Lcd_Set_Cursor(2,5);
        Lcd_Write_String("YON:");
       
        
        if(RB0 == 0){

            while(RB0 == 0);  
            sayac_hiz = sayac_hiz + 1;
            
            if(sayac_hiz >= 100){
                sayac_hiz = 100;
            }
        }

        else if(RB1 == 0){

            while(RB1 == 0);                 
            sayac_hiz = sayac_hiz - 1;
            
            if(sayac_hiz <= 0){
                sayac_hiz = 0;
            }
        }
        
        else if(RB6 == 0){

            while(RB6 == 0);  
            sayac = 1;

        }

        else if(RB7 == 0){

            while(RB7 == 0);                 
            sayac = 0;

        }
        char yuzde_veri[16];
        hiz = sayac_hiz*10;                                              							

        sprintf(yuzde_veri, "%3d", sayac_hiz);   
        Lcd_Set_Cursor(1,9);
        Lcd_Write_String(yuzde_veri);
        
 
        motor(sayac, hiz);
        
        }
}