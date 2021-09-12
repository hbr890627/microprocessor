#include <regx51.h>
void delay(unsigned int t);

void main()
{
    while (1)
    {
        P2_0 = 0; //relay and LED are on
        delay(50000);
        P2_0 = 1; //relay and LED are off
        delay(50000);
    }
}
void delay(unsigned int t)
{
    while (t--)
        ;
}
