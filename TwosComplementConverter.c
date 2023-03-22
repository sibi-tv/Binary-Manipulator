#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
    FILE *binaryFile = fopen(argv[1], "r");

    long num = 0;
    while (fscanf(binaryFile, "%ld", &num) != EOF)
    {
        int bitCount = 0;
        long MAX = 0, MIN = 0;
        fscanf(binaryFile, "%d", &bitCount);
        int binary[bitCount];
        // Calculate MAX
        MIN -= (long)pow(2, (bitCount - 1));
        MAX = (MIN / -1) - 1;

        if (num > MAX)
        {
            binary[0] = 0;
            for (int i = 1; i < bitCount; i++)
            {
                binary[i] = 1;
            }
        }
        else if (num < MIN)
        {
            binary[0] = 1;
            for (int i = 1; i < bitCount; i++)
            {
                binary[i] = 0;
            }
        }
        else
        {
            long absNum = num;
            if (num < 0)
                absNum = absNum / -1;
            int j = 0;
            for (int i = (bitCount - 1); i >= 0; i--)
            {
                if (absNum < (long)pow(2, i))
                {
                    binary[j] = 0;
                }
                else
                {
                    binary[j] = 1;
                    absNum -= (long)pow(2, bitCount - (j + 1));
                }
                j++;
            }
            if (num < 0)
            {
                for (int i = 0; i < bitCount; i++)
                {
                    if (binary[i] == 0)
                        binary[i] = 1;
                    else
                        binary[i] = 0;
                }
                int i = (bitCount - 1);
                for (; i >= 0; i--)
                {
                    if (binary[i] == 0)
                    {
                        binary[i] = 1;
                        i = -1;
                    }
                    else
                    {
                        binary[i] = 0;
                    }
                }
            }
        }

        for (int i = 0; i < bitCount; i++)
        {
            printf("%d", binary[i]);
        }
        printf("\n");
    }
}