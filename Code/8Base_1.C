#include "regx51.h"
void init_uart(); //宣告UART初始化函式
char recivevalue; //接收輸入的資料
void main()
{
    init_uart(); //開啟UART
    while (1)
    {
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
    { //若為接收中斷
        RI = 0;
        recivevalue = SBUF; //當中斷將SBUF的值放入recivevalue中
        P2 = recivevalue;   //將輸入的值用LED顯示觀察
    }
    if (recivevalue == 'q') //當接收字元為q
    {
        SBUF = recivevalue; //回傳接收到的值
    }
    if (TI == 1)
    {           //若為傳送中斷
        TI = 0; //將TI旗標設回0
    }
}
