#include "regx51.h"
void delay(int t);
void turn();
code char one_phase[] = {0x01, 0x02, 0x04, 0x08};
code char two_phase[] = {0x0c, 0x06, 0x03, 0x09};
int dir, delay_time;
void main()
{
    delay_time = 3000;
    dir = 1;
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
        for (x = 0; x < 4; x++)
        {
            P1 = one_phase[x];
            delay(delay_time);
        }
    }
    else //two phase, turn left
    {
        for (x = 0; x < 4; x++)
        {
            P1 = two_phase[x];
            delay(delay_time);
        }
    }
}
void delay(int t)
{
    int x;
    for (x = 0; x < t; x++)
        ;
}