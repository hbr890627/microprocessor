#include <regx51.h>              //you can only include this header file
#define TH0_init 0x06            //TH0 = 255 - 249
#define TL0_init 0x06            //TL0 = 255 - 249
#define Timer0_int_exe_time 1300 //you should adjust this parameter
void delay(int t);
int counter;
void main()
{
    TMOD = 0x02; //set timer0 to mode 2, 8-bits and auto-reload
    IP = 0x02;   //timer0 interrupt has high priority
    IE = 0x82;   //enable timer0 interrupt
    P2 = 0xff;
    TL0 = TL0_init;
    TH0 = TH0_init; //set TH0 & TL0
    TCON = 0x10;    //enable timer0
    while (1)
    {
        delay(25000); //you should adjust this parameter
        P2_0 = ~P2_0; //inverse P2.0
    }
}

void timer0_interrupt(void) interrupt 1
{
    counter++;
    if (counter == Timer0_int_exe_time) //250clock cycle * 2000 = 0.5 second
    {
        P2_1 = ~P2_1; //inverse P2.0
        counter = 0;
    }
}
//you should adjust this delay function
void delay(int t)
{
    for (; t > 0; t--);
}