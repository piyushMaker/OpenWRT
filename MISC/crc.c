#include <stdio.h>

const unsigned char CRC7_POLY = 0x91;
unsigned char getCRC(unsigned char message[], unsigned char length)
{
  unsigned char i, j, crc = 0;
 
  for (i = 0; i < length; i++)
  {
    crc ^= message[i];
    for (j = 0; j < 8; j++)
    {
      if (crc & 1)
        crc ^= CRC7_POLY;
      crc >>= 1;
    }
  }
  return crc;
}
 
int main()
{
  unsigned char message[3] = {0x83, 0x34, 0x00};
  message[2] = getCRC(message, 2);

  printf("Data1: 0x%X\n",message[0]);
  printf("DATA2: 0x%X\n",message[1]);
  printf("CRC: 0x%X\n",message[2]);
	
}
