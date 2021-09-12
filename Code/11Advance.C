#include "regx51.h"
void delay(int t);
void turn();
code char one_phase[] = {0x01, 0x02, 0x04, 0x08};
code char two_phase[] = {0x0c, 0x06, 0x03, 0x09};
code char one_point_five[] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0c, 0x08, 0x09};
int dir, delay_time, rotate, speed;
void main()
{
    IT0 = 1; //開啟外部中斷信號種類-負緣觸發(TCON)
    IT1 = 1;
    EX0 = 1; //致能外部中斷EX0(IE)
    EX1 = 1;
    EA = 1; //開全部中斷致能位元(IE)
    delay_time = 500;
    speed = 1;
    dir = 1;
    rotate = 1;
    while (1)
    {
        turn();
    }
}
void turn()
{
    int x;
    if (dir == 1) //one phase, turn right
    {
        if (rotate == 1)
        {

            for (x = 0; x < 4; x++)
            {
                P1 = one_phase[x];
                delay(delay_time);
            }
        }
        else
        {
            for (x = 3; x > -1; x--)
            {
                P1 = one_phase[x];
                delay(delay_time);
            }
        }
    }
    else if (dir == 2) //two phase, turn left
    {
        for (x = 0; x < 4; x++)
        {
            P1 = two_phase[x];
            delay(delay_time);
        }
    }
    else //1.5 phase
    {
        if (rotate == 1)
        {
            for (x = 0; x < 8; x++)
            {
                P1 = one_point_five[x];
                delay(delay_time);
            }
        }
        else
        {
            for (x = 7; x > -1; x--)
            {
                P1 = one_point_five[x];
                delay(delay_time);
            }
        }
    }
}
void delay(int t)
{
    int x;
    for (x = 0; x < t; x++)
        ;
}

void toggle(void) interrupt 0
{
    if (rotate == 1)
    {
        rotate = 0;
        delay(500);
        return;
    }
    else
    {
        rotate = 1;
        delay(500);
        return;
    }
}

void changeSpeed(void) interrupt 2
{
    if (speed == 1)
    {
        speed = 0;
        delay_time = 2000;
    }
    else
    {
        speed = 1;
        delay_time = 500;
    }
    delay(500);
}