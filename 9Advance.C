#include "regx51.h"
int range=32;
void main()
{
    IT0 = 0;  //開啟外部中斷信號種類-負緣觸發(TCON)
    EX0 = 1;  //致能外部中斷EX0(IE)
    EA = 1;   //開全部中斷致能位元(IE)
    P3_4 = 0; //11101111 WR(P3.4)設為0 ADC開始轉換
    P3_4 = 1; //WR=1，停止持續轉換
    while (1) //主程式持續執行
    {
    }
}

void int_0(void) interrupt 0 //INT0中斷函式
{
    P3_5 = 0; //設定RD為0，開啟資料讀取接腳
    if(P1>32*7){
        P2=255;
    }else if(P1>32*6){
        P2=127;
    }else if(P1>32*5){
        P2=63;
    }else if(P1>32*4){
        P2=31;
    }else if(P1>32*3){
        P2=15;
    }else if(P1>32*2){
        P2=7;
    }else if(P1>32*1){
        P2=3;
    }else if(P1>0){
        P2=1;
    }else{
        P2=0;
    }
    P3_5 = 1; //RD=1，停止讀取
    P3_4 = 0; //11101111 WR(P3.4)設為0 ADC開始轉換
    P3_4 = 1; //WR=1，暫停持續轉換
}