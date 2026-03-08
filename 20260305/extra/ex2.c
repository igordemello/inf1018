#include <ctype.h>
#include <stdio.h>

void num2string(char *s, int num, int base)
{
    if (num == 0)
    {
        *s = '0';
        s[1] = '\0';
        return;
    }

    int resto = 0;
    int n = 0;
    while(num > 0)
    {
        resto = num % base;
        char t = '0' + resto;
        s[n] = t;
        n++;
        num = num / base;
    }

    int m = n - 1;
    int j = 0;
    while(j < m)
    {
        char temp = s[j];
        s[j] = s[m];
        s[m] = temp;
        j++;
        m--;
    }

    s[n] = '\0';
}

int main (void) {
    char buffer[50];

    num2string(buffer, 13, 2);
    printf("13 em base 2 = %s\n", buffer);

    num2string(buffer, 255, 10);
    printf("255 em base 10 = %s\n", buffer);

    num2string(buffer, 100, 8);
    printf("100 em base 8 = %s\n", buffer);

    num2string(buffer, 0, 10);
    printf("0 em base 10 = %s\n", buffer);
    return 0;
}