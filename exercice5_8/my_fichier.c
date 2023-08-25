#include "my_fichier.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

FICHIER my_open(const char *filen, const char *mode)
{
    FICHIER file_sor=malloc(sizeof(struct sfich));
    if (*mode == 'r')
    {
        file_sor->descrip=open(filen, O_RDONLY);
        if (file_sor->descrip == -1)
        {   
            perror("open(filen,O_RDONLY)");
            return NULL;       
        }
        file_sor->lire=1;
        file_sor->ecrire=0;
    }
    else if (*mode == 'w' )
    {
        file_sor->descrip=open(filen, O_WRONLY);
        if (file_sor->descrip == -1)
        {   
            perror("open(filen,O_WRONLY)"); 
            return NULL;       
        }
        file_sor->lire=0;
        file_sor->ecrire=1;
    }
    else
        return NULL;
    file_sor->nbcar=0;
    file_sor->pos=0;
    return file_sor;
}


int my_getc(FICHIER f)
{   
    if (f->lire == 0)
    {
        printf("pas le droit de lecture \n");
        return 0;
    }
    if (f->nbcar ==  f->pos)
    {
        int a=read(f->descrip,f->buf, BUFSIZZ);
        if (a == 0)
            return EOF;
        else if (a < 0)
        {
            perror("read(f->descrip,f->buf, BUFSIZZ)");
            return EOF;
        }
        f->nbcar=a;
        f->pos=0;        
    }
    f->pos++;
    return f->buf[f->pos-1];
}


int my_putc(int c,FICHIER f)
{
    if (f->ecrire == 0)
    {
        printf("pas le droit d'écriture");
        return EOF;
    }
    if (c == EOF)
    {
        return EOF;
    }
    if(f->nbcar == BUFSIZZ)
    {
        int a = write(f->descrip,f->buf,BUFSIZZ);
        f->nbcar =1; 
        f->pos =0;
        f->buf[f->pos]=c;
        if (a == 0)
            return EOF;
        else if (a < 0)
            return EOF;
    }
    else
    {
        f->buf[f->pos]=c;
        f->nbcar++;
    }    
    return f->buf[f->pos++];
} 

int my_close(FICHIER f)
{
    if (f->ecrire == 1 && (f->nbcar!=0))
        write(f->descrip,f->buf,f->nbcar);
    if (close(f->descrip)<0)
    {
        perror("close(f->drescrip)");
        return EOF;
    }
    free(f);    
    return 0;
}
