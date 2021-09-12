#include "regx51.h"
void main()
{
    while (1)
    {
        if (P1 > 256 / 2) //若讀出的值大於256/2
            P2 = 0;       //點亮LED
        else
            P2 = 255; //LED不亮
    }
}