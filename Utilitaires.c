/*--------------------------------------------------------------*/
/*			Utilitaires.c               		*/
/*--------------------------------------------------------------*/

#include "Entete.h"
#include "Utilitaires.h"

/*-----------------------------------------*/
/* int EstCaractereChiffre(char caractere) */
/*-----------------------------------------*/

int EstCaractereChiffre(char caractere)
{
  int retour;

  retour = (caractere >= '0' && caractere <= '9') ? TRUE : FALSE;
  return(retour);
}

/*----------------------------------------*/
/* int EstCaractereLettre(char caractere) */
/*----------------------------------------*/

int EstCaractereLettre(char caractere)
{
int min, maj;

  min = (caractere >= 'a' && caractere <= 'z') ? TRUE : FALSE; 
  maj = (caractere >= 'A' && caractere <= 'Z') ? TRUE : FALSE; 
   
  return( min | maj ); 
} 

/*------------------------------------------------------------------*/
/* char * ExtraireSousChaine(char *ligne, int posdebut, int posfin) */
/*------------------------------------------------------------------*/

char * ExtraireSousChaine(char *ligne, int posdebut, int posfin) 
{ 
  char *res; 
  int i; 

  res = (char *) malloc((posfin-posdebut+1+1) * sizeof(char)); 
 
  for(i=posdebut;i<=posfin;i++) 
    res[i-posdebut]=ligne[i]; 
 
  res[posfin-posdebut+1]='\0'; 
 
  return res; 
} 

/*--------------------------------*/
/* char Majuscule(char caractere) */
/*--------------------------------*/

char Majuscule(char caractere)
{
  char res;

  res = (char)((caractere >='a' && caractere <='z') ? caractere - 'a' + 'A' : caractere);

  return res;
}

/*---------------------------------------*/
/* void MettreEnMajuscules(char *chaine) */
/*---------------------------------------*/

void MettreEnMajuscules(char *chaine)
{
  int i;

  for(i=0; i< strlen(chaine); i++)
    chaine[i] = Majuscule(chaine[i]);
}

/*----------------------------------*/
/* int EstDans( char c, char *str ) */
/*----------------------------------*/

int EstDans( char c, char *str )
{
  while( *str != '\0' )
    if( *str++ == c )
      return(TRUE);

  return(FALSE);
}

/*------------------------------------------------------------*/
/* char * ExtraireCaracteres(char *ligne, int deb, int nbcar) */
/*------------------------------------------------------------*/

char *ExtraireCaracteres(char *ligne, int deb, int nbcar) 
{ 
  char *res; 
  int i; 

  res = (char *) malloc((nbcar+1) * sizeof(char)); 
 
  for(i=0;i<nbcar;i++) 
    res[i]=ligne[deb+i]; 
 
  res[nbcar]='\0'; 
 
  return res; 
} 
