/*--------------------------------------------------------------*/
/*		   ListeChaineeOperands.c			*/
/*--------------------------------------------------------------*/

#include "Entete.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

void FreeMaillon_Operands(MAILLON_OPERANDS *lst)
{
  if (lst != NULL)
    {
      free((lst->info).string_value);
      FreeMaillon_Operands(lst->suivant);

      free(lst);
    }
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/

MAILLON_OPERANDS *InitialiseMaillon_Operands(UL_VAL_OPERANDS ValExpr)
{
    MAILLON_OPERANDS *maillon;

    maillon = (MAILLON_OPERANDS *) malloc(sizeof(MAILLON_OPERANDS));

    (maillon->info).ul = ValExpr.ul;

    (maillon->info).string_value = (char *) malloc( (1 + strlen(ValExpr.string_value)) * sizeof(char));
    strcpy((maillon->info).string_value, ValExpr.string_value);

    maillon->suivant = NULL;

    return maillon;
}

/*----------------------------------------------------------------------------------------------------*/
/*----------------------------------------------------------------------------------------------------*/

MAILLON_OPERANDS *AjouterMaillon_Operands(MAILLON_OPERANDS *poperande, UL_VAL_OPERANDS ValExpr)
{
  MAILLON_OPERANDS *maillon;
  MAILLON_OPERANDS *tete;
  MAILLON_OPERANDS *pt;

  tete = poperande;
  maillon = InitialiseMaillon_Operands(ValExpr);

  if (tete == NULL)
    {
      tete = maillon;
    }
  else
    {
      /* On met le maillon a la FIN de la LISTE CHAINEE */
      for(pt = tete; pt->suivant != NULL; pt = pt->suivant)
	;
      pt->suivant = maillon;
    }
  return tete;
}

/*-----------------------------------------------------------*/
/*-----------------------------------------------------------*/
void AfficherMaillon_Operands(MAILLON_OPERANDS *poperande)
{
  while(poperande != NULL)
    { 
      printf("\t\t[%-17s] [%s]\n", StringUnite_Lexicale((poperande->info).ul), (poperande->info).string_value);
      poperande = poperande->suivant;
    }
}
