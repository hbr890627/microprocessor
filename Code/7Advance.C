#include <regx51.h>            //you can only include this header file
#define TH0_init 0x00          //TH0 = 255 - 249
#define TL0_init 0x00          //TL0 = 255 - 249
#define Timer0_int_exe_time 40 //you should adjust this parameter
void delay(int t);
int counter;
void main()
{
    TMOD = 0x09;
    IP = 0x02; //timer0 interrupt has high priority
    IE = 0x82; //enable timer0 interrupt
    P2 = 0xfe;
    TL0 = TL0_init;
    TH0 = TH0_init; //set TH0 & TL0
    TCON = 0x10;    //enable timer0
    while (1)
    {
        // P2_0 = ~P2_0;
        // delay(20000);
    }
}

void timer0_interrupt(void) interrupt 1
{
    counter++;
    if (counter == Timer0_int_exe_time) //250clock cycle * 2000 = 0.5 second
    {
        if (P2 == 0x7f)
        {
            P2 = 0xfe;
        }
        else
        {
            P2 = P2 << 1;
            P2++;
        }

        counter = 0;
        TL0 = TL0_init;
        TH0 = TH0_init;
    }
}

// void delay(int t)
// {
//     for (; t > 0; t--);
// }

//1111 1110
//1111 1101