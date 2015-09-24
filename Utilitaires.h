/*--------------------------------------------------------------*/
/*			Utilitaires.h               		*/
/*--------------------------------------------------------------*/

/*-----------------------------------------*/
/*  Fonctions définies dans Utilitaires.c  */
/*-----------------------------------------*/

int EstCaractereChiffre(char caractere);

int EstCaractereLettre(char caractere);

char * ExtraireSousChaine(char *ligne, int posdebut, int posfin);

char Majuscule(char caractere);

void MettreEnMajuscules(char *chaine);

int EstDans(char c, char *str);

char *ExtraireCaracteres(char *ligne, int deb, int nbcar);