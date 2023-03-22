#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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

int main(int argc, char **argv)
{
    FILE *test = fopen(argv[1], "r");
    double num = 0.0;
    int mantissaSize = 0, numo = 0;

    while (fscanf(test, "%lf%d", &num, &mantissaSize) != EOF)
    {
        numo = (int)num;
        double decimal = num - numo;
        int k = leftMostPower(numo);
        char left[k + 2];
        char mainArr[mantissaSize + 2];
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
            for (int j = 0; j < i; j++)
            {
                printf("%c", mainArr[j]);
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
            for (int j = 0; j < i; j++)
            {
                printf("%c", mainArr[j]);
            }
        }
        printf(" %d", e);
        printf("\n");
    }
}
