/*Define a 32-bit unsigned integer called temp.

Xor the (d1)th byte of N with the (d2)th byte of N and store the result at the 1st byte of temp.

And the (d2)th byte of N with the (d3)th byte of N and store the result at the 2nd byte of temp.

Or the (d3)th byte of N with the (d1) the byte of N and store the result at the 3rd byte of temp.

Toggle the (d4)th byte of N and place the result at the 4th byte of temp.

Rotate the temp right by (d1 + d2 + d3 + d4) bits.

Xor the upper 16 bits of temp with the lower 16 bits of temp to form a 16-bit unsigned integer.

*/
/*N: 82564876 = 0x04EBD70C
d1: 4, d2: 3, d3: 2, d4: 1

Step 1:
    temp: 0x00000000 (could be any initial value, does not matter)

Step 2:
    4th byte of N: 0x0C, 3rd byte of N: 0xD7
    [0x0C (00001100)] xor [0xD7 (11010111)] = [0xDB (11011011)]
    temp: 0xDB000000

Step 3:
    3rd byte of N: 0xD7, 2nd byte of N: 0xEB
    [0xD7 (11010111)] and [0xEB (11101011)] = [0xC3 (11000011)]
    temp: 0xDBC30000

Step 4:
    2nd byte of N: 0xEB, 4th byte of N: 0x0C
    [0xEB (11101011)] or [0x0C (00001100)] = [0xEF (11101111)]
    temp: 0xDBC3EF00

Step 5:
    1st byte of N: 0x04
    Toggle [0x04 (00000100)] = [0xFB (11111011)]
    temp: 0xDBC3EFFB

Step 6:
    d1 + d2 + d3 + d4 = 10
    Rotate [0xDBC3EFFB (11011011 11000011 11101111 11111011) right 10 bits
        = [0xFEF6F0FB (11111110 11110110 11110000 11111011)

Step 7:
    Upper 16 bits of temp: 0xFEF6, Lower 16 bits of temp: 0xF0FB
    [0xFEF6 (11111110 11110110)] xor [0xF0FB (11110000 11111011)]
        = [0x0E0D (00001110 00001101)] = 3597

Result: 3597
*/
#include<stdio.h>
int main()
{
    unsigned int temp=0;
    unsigned int n;
    scanf("%d",&n);
    int d1;
    int d2;
    int d3;
    int d4;
    scanf("%d %d %d %d",&d1,&d2,&d3,&d4);
    unsigned int mask =0xff;
    unsigned int d1_byte=(n&(mask<<(4-d1)*8))>>(4-d1)*8;
    unsigned int d2_byte=(n&(mask<<(4-d2)*8))>>(4-d2)*8;
    unsigned int d3_byte=(n&(mask<<(4-d3)*8))>>(4-d3)*8;
    unsigned int d4_byte=(n&(mask<<(4-d4)*8))>>(4-d4)*8;
    //step 2
    temp|=((d1_byte^d2_byte)<<3*8);
    //printf("=%x\n",temp);
    //step 3
    temp|=((d3_byte&d2_byte)<<2*8);
   // printf("=%x\n",temp);
    //step 4
    temp|=((d3_byte|d1_byte)<<8);
    //printf("=%x\n",temp);
    
    temp|=(d4_byte^mask);
    //printf("=%x\n",temp);

    //step 6
    int rotate=d1+d2+d3+d4;
    unsigned int A=temp>>rotate;
    unsigned int B=temp<<(32-rotate);
    temp=A|B;
    //printf("=%x\n",temp);
    unsigned int bigmask=0xffff;
    printf("%d\n",(temp&bigmask)^(temp>>16));

    
    return 0;
    }