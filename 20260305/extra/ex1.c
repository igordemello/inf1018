#include <stdio.h>

int aux (void *p) {
  unsigned char *p1 = p;
  if(*p1 == 16)
  {
    return 1;
  }
  return 0;
}

int is_little() {
    int p = 10000;
    if (aux(&p))
    {
        return 1;
    }
    return 0;
}

int main()
{
    if (is_little())
    {
        printf("É litlle endian\n");
    }
    else
    {
        printf("É big endian\n");
    }

    return 0;
}