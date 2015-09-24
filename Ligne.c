/*--------------------------------------------------------------*/
/*			Ligne.c	               			*/
/*--------------------------------------------------------------*/

#include "Entete.h"
#include "Ligne.h"
#include "Utilitaires.h"

/*--------------------------------------------------*/
/*--------------------------------------------------*/

UNITE_LEXICALE LexemeLigne(char *ligne, int *pdeb) 
{
  int courant = (*pdeb); /* Initialisation sur le caractere actuellement pointé */
  int nbcar=0; /* nombre de caractere a prendre en compte dans le lexeme retourné */
  char carlu ;

  /* Prise en compte du premier caractere examiné */
  carlu = ligne[courant];
  nbcar++;
  courant++;

  /* Mise à jour de pdeb pour le prochain appel à LexemeLigne */
  *pdeb = courant;

  /* analyse du premier caractere */
  switch (carlu) {
    case EOL_STRING :
    case EOF_STRING :     
    case EOL_WIN :
      return UL_EOL;
      break;

    case SEMICOLON :
      return UL_SEMICOLON;
      break;

    case SPACE :
       return UL_SPACE;
       break;

    case TABU :
      return UL_TABU;
      break;

    case PERIOD :
      return UL_PERIOD;
      break;

    case UNDERSCORE :
      return UL_UNDERSCORE;
      break;

    case DOLLAR :
      return UL_DOLLAR;
      break;

    case A_PLUS :
      return UL_INC;
      break;

    case A_SOUST :
      return UL_DEC;
      break;

    case STAR :
      return UL_STAR;
      break;

    case CRO_OUV :
      return UL_CRO_OUV;
      break;

    case CRO_FERM :
      return UL_CRO_FERM;
      break;

    case DIESE :
      return UL_DIESE;
      break;

    case PERCENT :
      return UL_PERCENT;
      break;

    case ATSIGN :
      return UL_ATSIGN;
      break;

    case APOSTROPHE :
      return UL_APOSTROPHE;
      break;

    case COMMA :
      return UL_COMMA;
      break;
  }

  /* Si on arrive ici, c'est que l'on pas reconnu l'un des caracteres ci-dessus */
  /* (on a pas fait le return) */

  if (EstCaractereLettre(carlu) == TRUE)
    return UL_ALPHABET;

  if (EstCaractereChiffre(carlu) == TRUE)
    return UL_DIGIT;

  return UL_INCONNU;
}

/*------------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------------*/

void statement (char *ligne, int *pdeb, UNITE_LEXICALE *pProchain, TYPE_LIGNE *ptlg, 
                TYPE_VAL_FIELD *pLabelField, 
                TYPE_VAL_FIELD *pOperationField, 
                TYPE_VAL_FIELD *pOperandsField, 
                TYPE_VAL_FIELD *pCommentField)
{
  int posdebut;
  int posfin;

  /* INITIALISATION à EMPTY_FIELD */
  (*pLabelField).type_field = EMPTY_FIELD;
  pLabelField->string_value = (char *)malloc(sizeof(char) );
  pLabelField->string_value = "";

  (*pOperationField).type_field = EMPTY_FIELD;
  pOperationField->string_value = (char *)malloc(sizeof(char) );
  pOperationField->string_value = "";

  (*pOperandsField).type_field = EMPTY_FIELD;
  pOperandsField->string_value = (char *)malloc(sizeof(char) );
  pOperandsField->string_value = "";
  (*pCommentField).type_field = EMPTY_FIELD;
  pCommentField->string_value = (char *)malloc(sizeof(char) );
  pCommentField->string_value = "";

  *pProchain = LexemeLigne(ligne, pdeb);

  if (*pProchain == UL_SEMICOLON)
    {       
      /* La ligne est remplie */
      (*ptlg) = LIGNE_REMPLIE;

      /* Position de debut du lexeme COMMENT */
      posdebut = (*pdeb)-1; /* on prend en compte a partir du SEMICOLON */

      *pProchain = LexemeLigne(ligne, pdeb);

      suite_comment(ligne, pdeb, pProchain);

      /* Position de fin du lexeme COMMENT */
      posfin = (*pdeb) - 2; /* -2 car on ne prend pas le EOL et pdeb pointe apres le EOL */

      /* Extraction du lexeme reconnu */
      (*pCommentField).type_field = COMMENT_FIELD;
      pCommentField->string_value = (char *)malloc( (posfin-posdebut+2) * sizeof(char) );
      pCommentField->string_value = ExtraireSousChaine(ligne, posdebut, posfin);

      if (*pProchain != UL_EOL)
	{ printf("\t[%-25s]\n","ERREUR : il manque UL_EOL"); }

    }
  else
    { 
      if ( (*pProchain == UL_ALPHABET)   || 
           (*pProchain == UL_PERIOD)     || 
           (*pProchain == UL_UNDERSCORE) || 
           (*pProchain == UL_TABU) )
	{ 
	  /* La ligne est remplie */
	  (*ptlg) = LIGNE_REMPLIE;

	  /* Position de debut du lexeme LABEL */
	  posdebut = (*pdeb)-1; /* On prend en compte le 1er caractere du label */

	  label_field(ligne, pdeb, pProchain);

	  /* Position de fin du lexeme LABEL */
	  posfin = (*pdeb) - 2; /* -2 car on ne prend pas le TABU et pdeb pointe apres le TABU */  

	  /* Extraction du lexeme reconnu */
	  (*pLabelField).type_field = LABEL_FIELD;
	  pLabelField->string_value = (char *)malloc( (posfin-posdebut+2) * sizeof(char) );
	  pLabelField->string_value = ExtraireSousChaine(ligne, posdebut, posfin);

	  /* Position de debut du lexeme OPERATION*/
	  posdebut = (*pdeb); /* on prend en compte les caracteres apres la TABU */

	  operation_field(ligne, pdeb, pProchain);

	  /* Position de fin du lexeme OPERATION */
	  posfin = (*pdeb) - 2; /* -2 car on ne prend pas le TABU et pdeb pointe apres la TABU*/  

	  /* Extraction du lexeme reconnu */
	  (*pOperationField).type_field = OPERATION_FIELD;
	  pOperationField->string_value = (char *)malloc( (posfin-posdebut+2) * sizeof(char) );
	  pOperationField->string_value = ExtraireSousChaine(ligne, posdebut, posfin);

	  /* Position de debut du lexeme OPERANDS*/
	  posdebut = (*pdeb); /* on prend en compte les caracteres apres la TABU */

	  operands_field(ligne, pdeb, pProchain);

	  /* Position de fin du lexeme OPERANDS*/
	  posfin = (*pdeb) - 2; /* -2 car on ne prend pas le TABU et pdeb pointe apres la TABU*/  
	  /* Extraction du lexeme reconnu */
	  (*pOperandsField).type_field = OPERANDS_FIELD;
	  pOperandsField->string_value = (char *)malloc( (posfin-posdebut+2) * sizeof(char) );
	  pOperandsField->string_value = ExtraireSousChaine(ligne, posdebut, posfin);

	  /* Position de debut du lexeme COMMENT*/
	  posdebut = (*pdeb); /* on prend en compte les caracteres apres la TABU */

	  comment_field(ligne, pdeb, pProchain);

	  /* Position de fin du lexeme COMMENT*/
	  posfin = (*pdeb) - 2; /* -2 car on ne prend pas le EOL et pdeb pointe apres le EOL */

	  /* Extraction du lexeme reconnu */
	  (*pCommentField).type_field = COMMENT_FIELD;
	  pCommentField->string_value = (char *)malloc( (posfin-posdebut+2) * sizeof(char) );
	  pCommentField->string_value = ExtraireSousChaine(ligne, posdebut, posfin);

	  if (*pProchain != UL_EOL)
	    { printf("\t[%-25s]\n","ERREUR : il manque UL_EOL"); }
	}
      else
	if (*pProchain != UL_EOL)
	  { printf("\t[%-25s]\n","ERREUR : il manque UL_EOL"); }	
	else
	  {
	    /* La ligne est vide */
	    (*ptlg) = LIGNE_VIDE;
	  }
    }
}

/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/

void label_field (char *ligne, int *pdeb, UNITE_LEXICALE *pProchain)
{
  if ( (*pProchain == UL_ALPHABET) || 
       (*pProchain == UL_PERIOD)   || 
       (*pProchain == UL_UNDERSCORE) )
    {
      *pProchain = LexemeLigne(ligne, pdeb);

      suite_label(ligne, pdeb, pProchain);
    }
}

/*--------------------------------------------------------------------*/
/*--------------------------------------------------------------------*/

void suite_label (char *ligne, int *pdeb, UNITE_LEXICALE *pProchain)
{
  if ( (*pProchain == UL_ALPHABET)   || 
       (*pProchain == UL_PERIOD)     || 
       (*pProchain == UL_UNDERSCORE) || 
       (*pProchain == UL_DIGIT)      || 
       (*pProchain == UL_DOLLAR) )
    {
      *pProchain = LexemeLigne(ligne, pdeb);

      suite_label(ligne, pdeb, pProchain);
    }
}

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/

void operation_field (char *ligne, int *pdeb, UNITE_LEXICALE *pProchain)
{
  if (*pProchain == UL_TABU)
    {
      *pProchain = LexemeLigne(ligne, pdeb);

      suite_operation(ligne,pdeb,pProchain);
    }
}

/*-----------------------------------------------------------------------*/
/*-----------------------------------------------------------------------*/

void suite_operation(char *ligne, int *pdeb, UNITE_LEXICALE *pProchain)
{
  if (*pProchain == UL_ALPHABET)
    {
      *pProchain = LexemeLigne(ligne, pdeb);

      suite_operation(ligne,pdeb,pProchain);
    }
}

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/

void operands_field(char *ligne, int *pdeb, UNITE_LEXICALE *pProchain)
{
  if (*pProchain == UL_TABU)
    {
      *pProchain = LexemeLigne(ligne, pdeb);

      suite_operands(ligne,pdeb,pProchain);
    }
}

/*----------------------------------------------------------------------*/
/*----------------------------------------------------------------------*/

void suite_operands(char *ligne, int *pdeb, UNITE_LEXICALE *pProchain)
{
  if ( (*pProchain == UL_ALPHABET)   || (*pProchain == UL_DIGIT)   || (*pProchain == UL_PERIOD)  ||
       (*pProchain == UL_UNDERSCORE) || (*pProchain == UL_DOLLAR)  || (*pProchain == UL_SPACE)   ||
       (*pProchain == UL_INC)        || (*pProchain == UL_DEC)     || (*pProchain == UL_STAR)    || 
       (*pProchain == UL_CRO_OUV)    || (*pProchain == UL_CRO_FERM)||
       (*pProchain == UL_DIESE)      || (*pProchain == UL_COMMA)   ||
       (*pProchain == UL_PERCENT)    || (*pProchain == UL_ATSIGN)  || (*pProchain == UL_APOSTROPHE) )
    {
      *pProchain = LexemeLigne(ligne, pdeb);

      suite_operands(ligne,pdeb,pProchain);
    }
}

/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/

void comment_field(char *ligne, int *pdeb, UNITE_LEXICALE *pProchain)
{
  if (*pProchain == UL_TABU)
    {
      *pProchain = LexemeLigne(ligne, pdeb);

      if (*pProchain == UL_SEMICOLON)
	{
	  *pProchain = LexemeLigne(ligne, pdeb);

	  suite_comment(ligne,pdeb,pProchain);
	}
      else
	{
	  printf("\t[%-25s]\n","ERREUR : il manque UL_SEMICOLON");
	}
    }
}

/*---------------------------------------------------------------------*/
/*---------------------------------------------------------------------*/

void suite_comment(char *ligne, int *pdeb, UNITE_LEXICALE *pProchain)
{
  if ( (*pProchain == UL_ALPHABET)   || (*pProchain == UL_DIGIT)   || (*pProchain == UL_PERIOD)     ||
       (*pProchain == UL_UNDERSCORE) || (*pProchain == UL_DOLLAR)  || (*pProchain == UL_SPACE)      ||
       (*pProchain == UL_INC)        || (*pProchain == UL_DEC)     || (*pProchain == UL_STAR)       || 
       (*pProchain == UL_CRO_OUV)    || (*pProchain == UL_CRO_FERM)|| 
       (*pProchain == UL_DIESE)      || (*pProchain == UL_COMMA)   ||
       (*pProchain == UL_PERCENT)    || (*pProchain == UL_ATSIGN)  || (*pProchain == UL_APOSTROPHE) ||
       (*pProchain == UL_SEMICOLON)  || (*pProchain == UL_TABU) )
    {
      *pProchain = LexemeLigne(ligne, pdeb);

      suite_comment(ligne,pdeb,pProchain);
    }
}
