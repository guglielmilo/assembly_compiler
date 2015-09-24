/*--------------------------------------------------------------*/
/*			Analyse.c				*/
/*--------------------------------------------------------------*/

#include "main.h"
#include "Ligne.h"
#include "Operands.h"
#include "Utilitaires.h"

void UpdateExtraction_Operands(MAILLON_OPERANDS **poperands);

/*--------------------------------------------------------------*/
/*TYPE_LIGNE Extraction_Fields(char *ligne,                     */
/*                             TYPE_VAL_FIELD *pLabelField,     */
/*                             TYPE_VAL_FIELD *pOperationField, */
/*                             TYPE_VAL_FIELD *pOperandsField,  */
/*                             TYPE_VAL_FIELD *pCommentField)   */
/*--------------------------------------------------------------*/
TYPE_LIGNE Extraction_Fields(char *ligne, 
                             TYPE_VAL_FIELD *pLabelField, 
                             TYPE_VAL_FIELD *pOperationField,
                             TYPE_VAL_FIELD *pOperandsField,
                             TYPE_VAL_FIELD *pCommentField)
{
  /*-------------------------------------------------------------------------------*/
  /* Retourne LIGNE_VIDE ou LIGNE_REMPLIE                                          */
  /* Extrait d'une ligne assembleur les champs LABEL, OPERATION, OPERANDS, COMMENT */
  /* Met en majuscule LABEL, OPERATION                                             */
  /* a partir de la grammaire LL(1)                                                */
  /*-------------------------------------------------------------------------------*/

  int deb=0; /* Initialisation obligatoire, on pointe sur le premier caractere de ligne */
  TYPE_LIGNE tlg;
  UNITE_LEXICALE Prochain;

  statement(ligne, &deb, &Prochain,&tlg, 
            pLabelField, pOperationField, pOperandsField, pCommentField);

  /*-----------------------------------------------------------*/
  /* MISE EN MAJUSCULES DES CHAMPS LABEL, OPERATION            */
  /*-----------------------------------------------------------*/
  MettreEnMajuscules(pLabelField->string_value);
  MettreEnMajuscules(pOperationField->string_value);
  
  /*-----------------------------------------------------------*/
  /* La mise en majuscules du champs OPERANDS se fera lors de  */
  /* l'analyse lexicale de ce champs  car il ne faut pas mettre*/
  /* en majuscules les constantes ascii                        */
  /*-----------------------------------------------------------*/
  
  /*------------------------------------------------------------*/
  /* Mise a jour de type_field dans le cas ou string_value = "" */
  /*------------------------------------------------------------*/
  if ( (pLabelField->type_field == LABEL_FIELD) && (strcmp(pLabelField->string_value, "") == 0) )
    pLabelField->type_field = EMPTY_FIELD;

  if ( (pOperationField->type_field == OPERATION_FIELD) && (strcmp(pOperationField->string_value, "") == 0) )  
    pOperationField->type_field = EMPTY_FIELD;

  if ( (pOperandsField->type_field == OPERANDS_FIELD) && (strcmp(pOperandsField->string_value, "") == 0) )
    pOperandsField->type_field = EMPTY_FIELD;

  if ( (pCommentField->type_field == COMMENT_FIELD) && (strcmp(pCommentField->string_value, "") == 0) )
    pCommentField->type_field = EMPTY_FIELD;
  
  /*------------------------------------*/
  /* Mise a jour du TYPE_LIGNE retourné */
  /*------------------------------------*/
  if ( (pLabelField->type_field == EMPTY_FIELD) &&
       (pOperationField->type_field == EMPTY_FIELD) &&
       (pOperandsField->type_field == EMPTY_FIELD) &&
       (pCommentField->type_field == EMPTY_FIELD) )
    tlg=LIGNE_VIDE;

  return tlg;
}

/*--------------------------------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------------------------------*/
CONTENU_OPERANDS Extraction_Operands(TYPE_VAL_FIELD OperandsField, MAILLON_OPERANDS **poperands)
{
  int deb;
  UNITE_LEXICALE Prochain;
  UL_VAL_OPERANDS ValExpr;

  deb=0; /* Initialisation obligatoire, on pointe sur le premier caractere du champs operands */
  
  if (OperandsField.type_field == OPERANDS_FIELD)
    {
      Prochain = LexemeOperands(OperandsField.string_value, &deb, &ValExpr);

      while ( (Prochain != UL_EOS) && (Prochain != UL_INCONNU) )
	{
	  *poperands = AjouterMaillon_Operands(*poperands, ValExpr);

	  Prochain = LexemeOperands(OperandsField.string_value, &deb, &ValExpr);
	}
      
      if (Prochain == UL_EOS)
	{
	}
      else
	{
	 /* printf("\t\t[%-25s]\n","ERREUR champs_operands : manque UL_EOS");*/
	}

      UpdateExtraction_Operands(poperands);
      
      return OPERANDS_REMPLIE;
    }
  else
    {
      return OPERANDS_VIDE;     
    }
}

/*--------------------------------------------------------------*/
/* void UpdateExtraction_Operands(MAILLON_OPERANDS **poperands) */
/*--------------------------------------------------------------*/
void UpdateExtraction_Operands(MAILLON_OPERANDS **poperands)
{
  MAILLON_OPERANDS *nouv;
  MAILLON_OPERANDS *cour;
  MAILLON_OPERANDS *prec;
  UL_VAL_OPERANDS ValExpr;

  /* On teste si les 2 premiers maillons sont : (UL_INC, UL_DEC) (UL_SYMBOL, UL_CONST) */
  /* Si oui, on fusionne les 2 maillons */
  cour = *poperands;
  if ((cour->suivant) != NULL)
    {
      if (  (((cour->info).ul == UL_INC) || ((cour->info).ul == UL_DEC)) &&
            ((((cour->suivant)->info).ul == UL_SYMBOL) || (((cour->suivant)->info).ul == UL_CONST)) )
	{
	  ValExpr.ul = ((cour->suivant)->info).ul;
	  ValExpr.string_value = (char *)malloc( (strlen(((cour->suivant)->info).string_value) + 2) * sizeof(char) );
	  strcpy(ValExpr.string_value , (cour->info).string_value);
	  strcat(ValExpr.string_value , ((cour->suivant)->info).string_value);

	  nouv = InitialiseMaillon_Operands(ValExpr);

	  nouv->suivant = (cour->suivant)->suivant;

	  *poperands = nouv;
	}
    }

  prec=*poperands;
  cour = (*poperands)->suivant;

  while ( (cour != NULL) && ((cour->suivant) != NULL) )
    {
      
      if (  (((cour->info).ul == UL_INC) || 
             ((cour->info).ul == UL_DEC)
            ) 
            &&
	    ((((cour->suivant)->info).ul == UL_SYMBOL) || 
             (((cour->suivant)->info).ul == UL_CONST ) ||
	     (((cour->suivant)->info).ul == UL_REG_A ) ||
	     (((cour->suivant)->info).ul == UL_REG_B ) ||
	     (((cour->suivant)->info).ul == UL_REG_D ) ||
	     (((cour->suivant)->info).ul == UL_REG_CCR)||
	     (((cour->suivant)->info).ul == UL_REG_PC) ||
	     (((cour->suivant)->info).ul == UL_REG_PCR)
            ) 
         )
	{
	  
	  ValExpr.ul = ((cour->suivant)->info).ul;
	  ValExpr.string_value = (char *)malloc( (strlen(((cour->suivant)->info).string_value) + strlen(((cour)->info).string_value)+1) * sizeof(char) );
	  strcpy(ValExpr.string_value , (cour->info).string_value);
	  strcat(ValExpr.string_value , ((cour->suivant)->info).string_value);
	  
	  
	  nouv = InitialiseMaillon_Operands(ValExpr);
	  nouv->suivant = (cour->suivant)->suivant;
	  
	  prec->suivant = nouv;
	  
	  cour=nouv;
	}
	  
      prec = cour;
      cour = cour->suivant;
    }
}

