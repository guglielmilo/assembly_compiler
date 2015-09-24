/*--------------------------------------------------------------*/
/*			Operands.c				*/
/*--------------------------------------------------------------*/

#include "Entete.h"
#include "Operands.h"
#include "Utilitaires.h"

/*----------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------*/
UNITE_LEXICALE LexemeOperands(char *expression, int *pdeb, UL_VAL_OPERANDS *pvalexpr) 
{
  int courant = (*pdeb);
  int nbcar=0; /* nombre de caractere a prendre en compte dans le lexeme retourné : Initialisation OBLIGATOIRE */
  char carlu ;

  /*--------------------------------*/
  /* On saute les caracteres espace */
  /*--------------------------------*/
  while (expression[courant] == SPACE)
    {
      courant++; /* on pointe sur le caractere suivant */
      /* on n'incremente pas nbcar car on ne tient pas compte des blancs */
    }

  /*--------------------------------------------------------------------------------------*/
  /* on modifie *pdeb afin de ne pas prendre en compte les blancs dans ExtraireCaracteres */
  /*--------------------------------------------------------------------------------------*/
  (*pdeb) = courant;

  /*------------------------------*/
  /* Lecture du premier caractere */
  /*------------------------------*/
  carlu = expression[courant];
  nbcar++;   /* mise a jour de nbcar */

  courant++; /* on pointe sur le caractere suivant */
  
  /*------------------------------*/
  /* Analyse du premier caractere */
  /*------------------------------*/
  switch (carlu) {
    case EOS :
      {
	pvalexpr->ul = UL_EOS;
	pvalexpr->string_value = (char *)malloc(sizeof(char) );
	pvalexpr->string_value = "";
	break;
      }
      
    case DIESE :
      {
	pvalexpr->ul = UL_DIESE;
	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	strcpy(pvalexpr->string_value , "#");
	break;
      }

    case COMMA :
      {
	pvalexpr->ul = UL_COMMA;
	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	strcpy(pvalexpr->string_value , ",");
	break;
      }

    case A_PLUS :
      {
	pvalexpr->ul = UL_INC;
	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	strcpy(pvalexpr->string_value , "+");
	break;
      }

    case A_SOUST :
      {
	pvalexpr->ul = UL_DEC;
	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	strcpy(pvalexpr->string_value , "-");
	break;
      }

    case STAR :
      {
	pvalexpr->ul = UL_STAR;
	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	strcpy(pvalexpr->string_value , "*");
	break;
      }

    case CRO_OUV :
      {
	pvalexpr->ul = UL_CRO_OUV;
	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	strcpy(pvalexpr->string_value , "[");
	break;
      }

    case CRO_FERM :
      {
	pvalexpr->ul = UL_CRO_FERM;
	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	strcpy(pvalexpr->string_value , "]");
	break;
      }

    case DOLLAR :
      {
	pvalexpr->ul = UL_CONST;

	carlu = expression[courant];
	while ( EstDans(carlu, "0123456789abcdefABCDEF") )
	  {
	    nbcar++;   /* mise a jour de nbcar */
	    courant++; /* on pointe sur le caractere suivant */
	    carlu = expression[courant];
	  }
	
	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	/*-------------------------------*/
	/* On prend les nbcar caracteres */
	/*-------------------------------*/
	strcpy(pvalexpr->string_value , ExtraireCaracteres(expression, *pdeb, nbcar));
	/*-------------------------------------------------*/
	/* Mise en majuscules des constantes hexadecimales */
	/*-------------------------------------------------*/
        MettreEnMajuscules(pvalexpr->string_value);

	break;
      }

    case ATSIGN :
      {
	pvalexpr->ul = UL_CONST;
	
	carlu = expression[courant];
	while ( EstDans(carlu, "01234567") )
	  {
	    nbcar++;   /* mise a jour de nbcar */
	    courant++; /* on pointe sur le caractere suivant */
	    carlu = expression[courant];
	  }

	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	/* On prend les nbcar caracteres */
	strcpy(pvalexpr->string_value , ExtraireCaracteres(expression, *pdeb, nbcar));
	break;
      }

    case PERCENT :
      {
	pvalexpr->ul = UL_CONST;

	carlu = expression[courant];
	while ( EstDans(carlu, "01") )
	  {
	    nbcar++;   /* mise a jour de nbcar */
	    courant++; /* on pointe sur le caractere suivant */
	    carlu = expression[courant];
	  }

	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	/* On prend les nbcar caracteres */
	strcpy(pvalexpr->string_value , ExtraireCaracteres(expression, *pdeb, nbcar));
	break;
      }

    case APOSTROPHE :
      {
	pvalexpr->ul = UL_CONST;

	carlu = expression[courant];
	nbcar++;   /* mise a jour de nbcar */
	courant++; /* on pointe sur le caractere suivant */

	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	/* On prend les nbcar caracteres */
	/* ET ON NE LES MET PAS EN MAJUSCULES ! */
	strcpy(pvalexpr->string_value , ExtraireCaracteres(expression, *pdeb, nbcar));
	break;
      }
      
    case '0' :
    case '1' :
    case '2' :
    case '3' :
    case '4' :
    case '5' :
    case '6' :
    case '7' :
    case '8' :
    case '9' :
      {
	pvalexpr->ul = UL_CONST;

	carlu = expression[courant];
	while ( EstDans(carlu, "0123456789") )
	  {
	    nbcar++;   /* mise a jour de nbcar */
	    courant++; /* on pointe sur le caractere suivant */
	    carlu = expression[courant];
	  }
	
	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	/* On prend les nbcar caracteres */
	strcpy(pvalexpr->string_value , ExtraireCaracteres(expression, *pdeb, nbcar));
	break;
      }

    default :
      if ( (EstCaractereLettre(carlu)) || (carlu == PERIOD) || (carlu == UNDERSCORE) )
      {
	carlu = expression[courant];
	while ( (EstCaractereLettre(carlu))  ||
                (EstCaractereChiffre(carlu)) ||
                (carlu == PERIOD)            ||
                (carlu == UNDERSCORE)        ||
                (carlu == DOLLAR)
              )
	  {
	      nbcar++;   /* mise a jour de nbcar */
	      courant++; /* on pointe sur le caractere suivant */
	      carlu = expression[courant];
	  }
	
	pvalexpr->string_value = (char *)malloc( (nbcar +1) * sizeof(char) );
	/* On prend les nbcar caracteres */
	strcpy(pvalexpr->string_value , ExtraireCaracteres(expression, *pdeb, nbcar));
	/*---------------------------------*/
	/* Mise en majuscules des symboles */
	/*---------------------------------*/
	MettreEnMajuscules(pvalexpr->string_value);

	if (strcmp("A",pvalexpr->string_value) == 0)
	  pvalexpr->ul = UL_REG_A;
	else
	  if (strcmp("B",pvalexpr->string_value) == 0)
	    pvalexpr->ul = UL_REG_B;
	  else
	    if (strcmp("D",pvalexpr->string_value) == 0)
	      pvalexpr->ul = UL_REG_D;
	    else
	      if (strcmp("X",pvalexpr->string_value) == 0)
		pvalexpr->ul = UL_REG_X;
	      else
		if (strcmp("Y",pvalexpr->string_value) == 0)
		  pvalexpr->ul = UL_REG_Y;
		else
		  if (strcmp("SP",pvalexpr->string_value) == 0)
		    pvalexpr->ul = UL_REG_SP;
		  else
		    if (strcmp("PC",pvalexpr->string_value) == 0)
		      pvalexpr->ul = UL_REG_PC;
		    else
		      if (strcmp("CCR",pvalexpr->string_value) == 0)
			pvalexpr->ul = UL_REG_CCR;
		      else
			pvalexpr->ul = UL_SYMBOL;
      }
      else
	{
	  pvalexpr->ul= UL_INCONNU;
	  pvalexpr->string_value = (char *)malloc(sizeof(char) );
	  pvalexpr->string_value = "";
	}
      break;
  }

  /* Mise à jour de pdeb */
  (*pdeb) = courant;
  
  return (*pvalexpr).ul;
}

