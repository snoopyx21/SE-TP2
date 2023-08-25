#define BUFFER 128
#define EOF -1
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

// rajouter droit d'ouverture 
typedef struct sp{ 
   int descripteur;
   unsigned char buf[BUFFER];
   int pos;
   int nb_caracteres;
} FICHIER;

FICHIER* my_open(const char *filename, const char mode)
{
   FICHIER* file_out;
   file_out = (FICHIER *)malloc(sizeof(struct sp));
   file_out->nb_caracteres=0;
   file_out->pos=0;
   if ( mode == 'r' )
   {
       file_out->descripteur=open(filename, O_RDONLY);
       if ( file_out->descripteur == -1) return NULL;
       else return file_out;
   }
   else if ( mode == 'w' ) 
   {
       file_out->descripteur=open(filename, O_WRONLY | O_CREAT | O_TRUNC);
       if ( file_out->descripteur == -1 ) return NULL;
       else return file_out;
   }
   else return NULL;
}

int my_getc(FICHIER* filename)
{
   if (filename->nb_caracteres == filename->pos) return 0;
   int nb;
   if ( (nb=read(filename->descripteur, filename->buf, BUFFER)) == -1)
   {
       perror("read(filename->descripteur, filename->buf, BUFFER");
       return EOF;
   }
   else
   {
       filename->nb_caracteres=nb;
       return nb;   
   }
}

int main()
{
   FICHIER* f=my_open("titi",'r');
   FICHIER* f2=my_open("toto",'w');
   free(f);
   free(f2);
   return 0;
}
