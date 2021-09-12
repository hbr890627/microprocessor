#include "regx51.h"
void init_uart(); //宣告UART初始化函式
char recivevalue; //接收輸入的資料
int count;
int iswrong;
int flag;
void main()
{
    init_uart(); //開啟UART
    count = 0;
    iswrong = 0;
    flag = 0;
    while (1)
    {
        if (count == 9)
        {
            count = 0;
            P2 = recivevalue;
            if (iswrong)
            {
                flag = 1;
                SBUF = 'w';
                while (flag)
                    ;
                flag = 1;
                SBUF = 'r';
                while (flag)
                    ;
                flag = 1;
                SBUF = 'o';
                while (flag)
                    ;
                flag = 1;
                SBUF = 'n';
                while (flag)
                    ;
                flag = 1;
                SBUF = 'g';
                while (flag)
                    ;
                flag = 1;
                SBUF = '\n';
                while (flag)
                    ;
                flag = 1;
            }
            else
            {
                flag = 1;
                SBUF = 'c';
                while (flag)
                    ;
                flag = 1;
                SBUF = 'o';
                while (flag)
                    ;
                flag = 1;
                SBUF = 'r';
                while (flag)
                    ;
                flag = 1;
                SBUF = 'r';
                while (flag)
                    ;
                flag = 1;
                SBUF = 'e';
                while (flag)
                    ;
                flag = 1;
                SBUF = 'c';
                while (flag)
                    ;
                flag = 1;
                SBUF = 't';
                while (flag)
                    ;
                flag = 1;
                SBUF = '\n';
                while (flag)
                    ;
                flag = 1;
            }
            iswrong = 0;
        }
    }
}
void init_uart(void)
{
    SCON = 0x50; //設定SCON暫存器傳輸模式為mode1
    TMOD = 0x20; //開啟TIMER1的Mode2
    TH1 = 0xe6;  //baud的設定 1200
    TR1 = 1;     //TCON中Timer1的啟動開關 TR1為1
    IE = 0x90;   //開起UART中斷設定 EA跟ES位元為1
}
void UART_Isr(void) interrupt 4 //UART中斷
{
    if (RI == 1)
    {
        RI = 0;
        recivevalue = SBUF;
        switch (count)
        {
        case 0:
            if (recivevalue != 'e' && recivevalue != 'E')
                iswrong = 1;
            count++;
            break;
        case 1:
            if (recivevalue != '9')
                iswrong = 1;
            count++;
            break;
        case 2:
            if (recivevalue != '4')
                iswrong = 1;
            count++;
            break;
        case 3:
            if (recivevalue != '0')
                iswrong = 1;
            count++;
            break;
        case 4:
            if (recivevalue != '7')
                iswrong = 1;
            count++;
            break;
        case 5:
            if (recivevalue != '6')
                iswrong = 1;
            count++;
            break;
        case 6:
            if (recivevalue != '0')
                iswrong = 1;
            count++;
            break;
        case 7:
            if (recivevalue != '5')
                iswrong = 1;
            count++;
            break;
        case 8:
            if (recivevalue != '5')
                iswrong = 1;
            count++;
            break;
        default:
            break;
        }
    }
    if (TI == 1)
    {           //若為傳送中斷
        TI = 0; //將TI旗標設回0
        flag = 0;
    }
}

// void delay()
// {
//     int n;
// }
