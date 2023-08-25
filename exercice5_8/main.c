#include "my_fichier.h"
#include <stdio.h>
#include <stdlib.h>



int main (void)
{
    FICHIER fin=my_open("toto","r");
    FICHIER fout=my_open("titi","w");
    int a;
    do
    {
        a = my_getc(fin);
        my_putc(a,fout);
    }
    while ( a != EOF);
    my_close(fin);
    my_close(fout);   
    return 0;
}
