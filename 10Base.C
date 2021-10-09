#include <regx51.h>
void print_msg(char *msg);
void write(char cmd, char rs_value);
void delay(unsigned int i);
void main()
{
    write(0x38, 0);              // 功能設定 8位元、2行、5x7字型
    write(0x0F, 0);              // 顯示器設定開啟、有游標、要閃爍
    write(0x06, 0);              // 資料輸入LED時，游標右移一格、顯示器不動
    write(0x01, 0);              // 清除顯示器
    write(0x80, 0);              // DDRAM位址設定 00H
    print_msg("Hello, world !"); // LCD顯示Hello world!
    while (1)
        ;
}

void print_msg(char *msg)
{
    for (; *msg != '\0'; ++msg) // 對於每一個字元
        write(*msg, 1);         // LCD顯示字元
}

void write(char cmd, char rs_value)
{
    P1 = cmd;        //設定 cmd
    P3_0 = rs_value; // 設定 RS (0或 1)
    P3_1 = 1;        // ENABLE high
    delay(100);      // 延遲讓ENABLE訊號穩定
    P3_1 = 0;        // ENABLE low
}

void delay(unsigned int i)
{
    while (i--)
        ;
}