#include <Wire.h>

void setup()
{
	Wire.begin(); // マスターに設定
}

void loop()
{
	for(int i=0; i<10000; i++)
	{
		write_numbers(i);
		delay(500);
	}
}

void write_numbers(int numbers)
{
	unsigned short int upper = (unsigned short int)numbers >> 8;
	unsigned short int lower = (unsigned short int)numbers << 8;
	lower = lower / 256;

	Wire.beginTransmission(8);
	Wire.write(upper);
	Wire.write(lower);
	Wire.endTransmission();
}
