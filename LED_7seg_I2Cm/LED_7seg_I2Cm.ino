#include <Wire.h>
 
void setup()
{
    Wire.begin(); // マスターに設定
}
 
void loop()
{
    for(int i=0; i<256; i++)
    {
        write_numbers(i);
        delay(500);
    }
}
 
void write_numbers(int numbers)
{
    Wire.beginTransmission(8);
    Wire.write(numbers);
    Wire.endTransmission();
}