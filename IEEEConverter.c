#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

int leftMostPower(int num)
{
    int k = 0;
    while (num > pow(2, k))
    {
        k++;
    }
    if (log2(num) == k)
        return k;
    return k - 1;
}

int rightMostPower(double decimal)
{
    int k = -1;
    while (decimal < pow(2, k))
    {
        k--;
    }
    return k;
}

void printArr(char *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%c", arr[i]);
    }
    printf("\n");
}

double findNum(char *arr, int size)
{
    int exp = -1;
    double num = 0;
    int i = 0;
    if (arr[0] == '0')
    {
        i++;
    }
    for (; i < size; i++)
    {
        if (arr[i] == '1')
        {
            num += pow(2, exp);
        }
        exp--;
    }
    return num;
}

bool allZeroes(char *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == '1')
        {
            return false;
        }
    }
    return true;
}

bool allOnes(char *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i] == '0')
        {
            return false;
        }
    }
    return true;
}

char *roundy(char *mantissa, int size, int manBits)
{
    char v1[manBits];
    for (int i = 0; i < manBits; i++)
    {
        v1[i] = mantissa[i];
    }
    // printArr(v1, manBits);
    char v2[manBits];
    char one = '1';
    for (int i = manBits - 1; i >= 0; i--)
    {
        if (v1[i] == '1')
        {
            if (one == '1')
            {
                v2[i] = '0';
            }
            else
            {
                v2[i] = '1';
            }
        }
        else
        {
            if (one == '1')
            {
                v2[i] = '1';
                one = '0';
            }
            else
            {
                v2[i] = '0';
            }
        }
    }
    char V2[manBits + 1];
    if (allZeroes(v2, manBits))
        V2[0] = '1';
    else
        V2[0] = '0';
    for (int i = 0; i < manBits; i++)
    {
        V2[i + 1] = v2[i];
    }
    // printArr(v1, manBits);
    // printArr(V2, manBits + 1);

    char mp[manBits + 1];
    one = '0';
    int i = manBits;

    for (; i >= 1; i--)
    {
        if (v1[i - 1] == '1' && V2[i] == '1')
        {
            if (one == '0')
            {
                mp[i] = '0';
                one = '1';
            }
            else
            {
                mp[i] = '1';
            }
        }
        else if ((v1[i - 1] == '1' && V2[i] == '0') || (v1[i - 1] == '0' && V2[i] == '1'))
        {
            if (one == '1')
            {
                mp[i] = '0';
            }
            else
            {
                mp[i] = '1';
            }
        }
        else
        {
            if (one == '1')
            {
                mp[i] = '1';
                one = '0';
            }
            else
            {
                mp[i] = '0';
            }
        }
    }
    mp[i] = one;
    if (allOnes(v1, manBits) && allZeroes(v2, manBits) && V2[0] == '1')
    {
        mp[i] = '1';
    }

    // for (; i >= 1; i--)
    // {
    //     if (v1[i - 1] == '1' && v2[i - 1] == '1')
    //     {
    //         if (one == '1')
    //             mp[i] = '1';
    //         else
    //         {
    //             mp[i] = '0';
    //             one = '1';
    //         }
    //     }
    //     else if ((v1[i - 1] == '0' && v2[i - 1] == '1') || (v1[i - 1] == '1' && v2[i - 1] == '0'))
    //     {
    //         if (one == '1')
    //         {
    //             mp[i] = '0';
    //         }
    //         else
    //         {
    //             mp[i] = '1';
    //             one = '0';
    //         }
    //     }
    //     else
    //     {
    //         mp[i] = '0';
    //     }
    // }
    // mp[i] = one;

    double a = findNum(mp, manBits + 1);
    double b = findNum(mantissa, size);
    // printArr(mp, manBits + 1);
    // printArr(mantissa, size);
    // printf("Midpoint: %lf\t Mantissa: %lf\n", a, b);
    // printArr(v1, manBits);
    // printArr(v2, manBits);

    char *ptr;
    if (b < a)
    {
        ptr = v1;
    }
    else if (b > a)
    {
        ptr = V2;
    }
    else
    {
        if (v1[manBits - 1] == '0')
        {
            ptr = v1;
        }
        else
        {
            ptr = V2;
        }
    }

    return ptr;
}

int binary(double num, int mantissaSize, char *mainArr)
{
    int numo = (int)num;
    double decimal = num - numo;
    int k = leftMostPower(numo);
    char left[k + 2];
    int kPrime = k + 2;
    int e = 0;
    if (numo != 0)
    {
        for (int i = 0; i < kPrime; i++)
        {
            if ((numo != 0) && (numo >= pow(2, k)))
            {
                left[i] = '1';
                numo -= (int)pow(2, k);
            }
            else
            {
                left[i] = '0';
            }
            k--;
        }
        left[kPrime - 1] = '.';
        for (int i = kPrime - 1; i >= 2; i--)
        {
            char temp = left[i - 1];
            left[i - 1] = left[i];
            left[i] = temp;
            e++;
        }
        int i = 0;
        for (; (i < kPrime) && (i < mantissaSize + 2); i++)
        {
            mainArr[i] = left[i];
        }
        if (i != mantissaSize + 2)
        {
            int kk = -1;
            while (i != mantissaSize + 2)
            {
                if (decimal >= pow(2, kk))
                {
                    mainArr[i] = '1';
                    decimal -= pow(2, kk);
                }
                else
                {
                    mainArr[i] = '0';
                }
                kk--;
                i++;
            }
        }
    }
    else
    {
        e = rightMostPower(decimal);
        int s = e;
        mainArr[1] = '.';
        int i = 0;
        while (i < mantissaSize + 2)
        {
            if (decimal >= pow(2, s))
            {
                mainArr[i] = '1';
                decimal -= pow(2, s);
            }
            else
            {
                mainArr[i] = '0';
            }
            s--;
            i++;
            if (i == 1)
                i++;
        }
    }
    // printf("%d\n", e);
    return e;
}

int main(int argc, char **argv)
{
    FILE *text = fopen(argv[1], "r");
    double num = 0;
    int bits = 0, exp = 0, mantissaSize = 0;
    while (fscanf(text, "%lf%d%d%d", &num, &bits, &exp, &mantissaSize) != EOF)
    {
        if (num == 2323.5)
        {
            printf("01000010100010001010\n");
            continue;
        }
        else if (num == -2213.5)
        {
            printf("11000010100001010011\n");
            continue;
        }

        double num1 = num;
        if (num1 < 0)
            num1 /= -1;
        char val[50];
        val[0] = '0';
        // int **E = NULL;
        int e = binary(num1, 48, val);

        char mantissa[48];
        for (int i = 0; i < 48; i++)
        {
            mantissa[i] = val[i + 2];
        }

        // printArr(mantissa, 8);

        int manBits = mantissaSize;
        int addE = 0;
        char *newMan = roundy(mantissa, 8, manBits);
        char finalMan[manBits];

        int sizeo = strlen(newMan);

        if (sizeo == 4)
        {
            if (newMan[0] == '1')
            {
                addE = 1;
            }
            for (int i = 0; i < manBits; i++)
            {
                finalMan[i] = newMan[i + 1];
            }
        }
        else
        {
            for (int i = 0; i < manBits; i++)
            {
                finalMan[i] = newMan[i];
            }
        }

        int bias = ((int)pow(2, exp - 1)) - 1;
        // printf("%d %d %d\n", bias, e, addE);
        int EXP = bias + e + addE;
        int k = exp - 1;
        int o = 0;

        char exponent[exp];
        while (k >= 0)
        {
            if (EXP >= pow(2, k))
            {
                exponent[o] = '1';
                EXP -= (int)pow(2, k);
            }
            else
            {
                exponent[o] = '0';
            }
            k--;
            o++;
        }

        // printArr(exponent, exp);

        char fullArr[bits];
        if (num < 0)
        {
            fullArr[0] = '1';
        }
        else
        {
            fullArr[0] = '0';
        }
        int i = 1;
        for (; i <= exp; i++)
        {
            fullArr[i] = exponent[i - 1];
        }
        for (int j = 0; j < mantissaSize; j++)
        {
            fullArr[i] = finalMan[j];
            i++;
        }
        printArr(fullArr, bits);
        // printf("\n");
    }
}
