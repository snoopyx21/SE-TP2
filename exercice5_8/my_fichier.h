// Fichier My_Fichier.h
#define EOF -1

#define BUFSIZZ 128
typedef struct sfich {
        int descrip;
        unsigned char buf[BUFSIZZ];
        int nbcar;
        int pos;
        int lire;
        int ecrire;
        }*FICHIER;

/*rajouter les modes d'ouvertures dans la struct*/

FICHIER my_open(const char *filen, const char *mode);
int my_getc(FICHIER f);
int my_putc(int c, FICHIER f);
int my_close(FICHIER f);
