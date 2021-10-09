#include "regx51.h"
void init_uart(); //宣告UART函式
char recivevalue; //接收輸入的資料
void main()
{
    init_uart(); //開啟UART
    while (1)
    {
        if (RI == 1)
        { //若為接收中斷
            RI = 0;
            recivevalue = SBUF;     //每當中斷將SBUF的值放入recivevalue中
            P2 = recivevalue;       //將輸入的值用LED顯示觀察
            if (recivevalue == 'q') //當接收字元為q
            {
                SBUF = recivevalue; //回傳接收到的值
            }
        }
        if (TI == 1)
        {           //若為傳送中斷
            TI = 0; //將TI旗標設回0
        }
    }
}
void init_uart(void)
{
    SCON = 0x50; //設定SCON暫存器為mode1
    TMOD = 0x20; //開啟TIMER1的Mode2
    TH1 = 0xe6;  //baud的設定
    TR1 = 1;     //TCON中Timer1的啟動開關
}