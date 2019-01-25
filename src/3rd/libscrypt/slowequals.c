#include <string.h>

int slow_equals(const char* a, const char* b)
{
    size_t lena, lenb, diff, i;
    lena = strlen(a);
    lenb = strlen(b);
    diff = strlen(a) ^ strlen(b);

    for(i=0; i<lena && i<lenb; i++)
    {
        diff |= a[i] ^ b[i];
    }
    if (diff == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


