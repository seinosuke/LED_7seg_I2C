#include <Wire.h>
#include <MsTimer2.h>
const int anode_pin[] = {1,2,3,4}; // digit number
const int cathode_pin[] = {5,6,7,8,9,10,11}; // A,B,C,D,E,F,G
#define DP 12
int numbers_to_display = 0; //LEDに表示する数字を保持
 
const int number[] =
{
    // GFEDCBA
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00100111, // 7
    0b01111111, // 8
    0b01101111, // 9
    0b00000000  // clear segment
};
 
const int digit[] =
{
    0b1000, // 1
    0b0100, // 2
    0b0010, // 3
    0b0001, // 4
};
 
void setup()
{
    Wire.begin(8); // スレーブのアドレスを８に設定
    Wire.onReceive(set_numbers);
 
    for(int i=1; i<13; i++)
    {
        pinMode(i, OUTPUT);
    }
    //display_numbers関数は少なくとも4[ms]かかるので5[ms]ごと呼ぶ
    MsTimer2::set(5,display_numbers);
    MsTimer2::start();
}
 
void loop()
{
    delay(100);
}
 
// anodeのピンをひとつだけHIGHにする
void digit_number (int n)
{
    for(int i=0; i<4; i++)
    {
        digitalWrite(anode_pin[i], digit[n] & (1 << i) ? HIGH:LOW);
    }
}
 
// 0~9の数字を表示する
void display_number (int n)
{
    for(int i=0; i<7; i++)
    {
        digitalWrite(cathode_pin[i], number[n] & (1 << i) ? HIGH:LOW);
    }
}
 
// numbers_to_display へ数字を入れる
// Wire.onReceive()で呼ばれる
void set_numbers(int numBytes)
{
    int n = 0;
     
    while(Wire.available())
    {
        n = Wire.read();
    }
    numbers_to_display = n;
}
 
// numbers_to_display の数字を表示する
void display_numbers ()
{
    int num = numbers_to_display;
    for(int i=0; i<4; i++)
    {
        digit_number(i); //表示する桁数を選択
        display_number(num % 10); //numの１の位の数
        num = num/10; //次の桁へ(切り捨て)
        display_number(10); // clear segment ４桁目を消すため
        delay(1);
    }
}