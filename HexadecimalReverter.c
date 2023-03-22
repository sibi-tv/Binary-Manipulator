#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

void printArr(char arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%c", arr[i]);
    }
    printf("\n");
}

void binary(int arrSize, char arr[], char bits[])
{
    int k = 0;
    for (int i = 0; i < arrSize; i++)
    {
        int d = 0;
        if (arr[i] <= '9')
        {
            // printf("%c\t", arr[i]);
            d = arr[i] - '0';
        }
        else
        {
            d = arr[i] - '0' - 7;
        }
        // printf("%d\n", d);
        for (int j = 3; j >= 0; j--)
        {
            if (d >= pow(2, j))
            {
                bits[k] = '1';
                d -= pow(2, j);
            }
            else
            {
                bits[k] = '0';
            }
            k++;
        }
    }
}

void truncate(int bitsSize, char bits[], int bitCount, char trunc[])
{
    int diff = bitsSize - bitCount;
    if (diff > 0)
    {
        for (int i = 0; i < bitCount; i++)
        {
            trunc[i] = bits[i];
        }
    }
    if (diff > 0)
    {
        for (int i = 0; i < bitCount; i++)
        {
            trunc[i] = bits[i + diff];
        }
    }
    else
    {
        diff = bitCount - bitsSize;
        int i = 0;
        while (i < diff)
        {
            trunc[i] = '0';
            i++;
        }
        for (; i < bitCount; i++)
        {
            trunc[i] = bits[i - diff];
        }
    }
}

long double IEEE(int expCount, int mantCount, char trunc[])
{
    int index = 0;

    // sign bit
    int s = trunc[index] - '0';

    // Exponent
    index++;
    int exp = expCount - 1;
    int E = 0;
    while (index <= expCount)
    {
        if (trunc[index] == '1')
        {
            E += (int)pow(2, exp);
        }
        exp--;
        index++;
    }
    int A = E;
    if (E == 0)
    {
        E = 1;
    }
    int bias = ((int)pow(2, expCount - 1)) - 1;
    int e = E - bias;
    // printf("E: %d, bias: %d, e: %d\t", E, bias, e);

    // mantissa
    long double mantAdd = 1.0;
    if (A == 0)
    {
        mantAdd = 0.0;
    }

    long double M = 0;
    for (int k = -1; k >= (mantCount) / -1; k--)
    {
        if (trunc[index] == '1')
        {
            M += pow(2, k);
        }
        index++;
    }
    // printf("mantAdd: %Lf, M: %Lf\t", mantAdd, M);
    long double IEEE = (pow(-1, s)) * (mantAdd + M) * (pow(2, e));
    return IEEE;
}

// void positivePrecision(long double ieee, int precision, int decimalSize, char decimal[])
// { //, int precision, int digits, char decimal[]
//     ieee *= 10000;
//     char ie[50];
//     snprintf(ie, 50, "%Lf", ieee);
//     printf("%s\n", ie);
//     int index = 0;
//     while (ie[index] != '.')
//     {
//         index++;
//     }
//     for (int i = 0; (i < 4); i++)
//     {
//         char temp = ie[index];
//         ie[index] = ie[index - 1];
//         ie[index - 1] = temp;
//     }

//     int i = 0;
//     while ((ie[i] != '.') && (i != decimalSize))
//     {
//         decimal[i] = ie[i];
//         i++;
//     }
//     decimal[i] = ie[i];
//     i++;
//     int j = i;
//     for (; ((j < (i + precision)) && (j < strlen(ie))); j++)
//     {
//         decimal[j] = ie[j];
//     }
//     if (j == i + precision)
//     {
//         if (ie[j] >= '5')
//         {
//             decimal[j - 1]++;
//             while (decimal[j - 1] == ':')
//             {
//                 decimal[j - 1] = '0';
//                 j--;
//                 if (decimal[j - 1] == '.')
//                 {
//                     j--;
//                     continue;
//                 }
//                 decimal[j - 1]++;
//             }
//         }
//     }
// }

int main(int argc, char **argv)
{
    FILE *text = fopen(argv[1], "r");
    int bitCount = 0, expCount = 0, mantCount = 0;
    unsigned int hexadecimal = 0;
    int precision = 0;
    int norm = 0;
    int currentNorm = 0;
    int size = 0;

    while (fscanf(text, "%d%d%d%x%d", &bitCount, &expCount, &mantCount, &hexadecimal, &precision) != EOF)
    {
        long a = (long)hexadecimal;
        if (a == 0)
        {
            char zero[precision + 2];
            zero[0] = '0';
            zero[1] = '.';
            for (int i = 2; i < precision + 2; i++)
            {
                zero[i] = '0';
            }
            printArr(zero, precision + 2);
            continue;
        }
        char remainder[100];

        int i = 0;
        while (a > 0)
        {
            long b = a % 16;
            if (b < 10)
                remainder[i] = 48 + b;
            else
                remainder[i] = 55 + b;

            a = a / 16;
            i++;
        }
        if (norm < i)
            norm = i;
        if (size < i)
            size = i;
        currentNorm = i;

        i--;
        int j = 0;
        while (j < i)
        {
            char temp = remainder[i];
            remainder[i] = remainder[j];
            remainder[j] = temp;
            i--;
            j++;
        }
        // printArr(remainder, size);

        char bits[size * 4];
        binary(size, remainder, bits);
        char Bits[size * 4];
        char trunc[bitCount];

        if (currentNorm != norm)
        {
            int q = 0;
            for (; q < 4; q++)
            {
                Bits[q] = '0';
            }
            for (; q < (size * 4); q++)
            {
                Bits[q] = bits[q - 4];
            }
            //printArr(Bits, size * 4);
            truncate(size * 4, Bits, bitCount, trunc);
        }
        else
        {
            //printArr(bits, size * 4);
            truncate(size * 4, bits, bitCount, trunc);
        }
        // printArr(trunc, bitCount);

        long double ieee = IEEE(expCount, mantCount, trunc);
        printf("%.*Lf\n", precision, ieee);

        // int ie = (int)ieee;
        // int digits = 0;
        // while (ie != 0)
        // {
        //     ie /= 10;
        //     digits++;
        // }

        // char decimal[digits + 1 + precision];
        // positivePrecision(ieee, precision, digits + 1 + precision, decimal);
        // printArr(decimal, digits + 1 + precision);
    };
}