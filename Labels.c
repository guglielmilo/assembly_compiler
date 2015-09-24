/*--------------------------------------------------------------*/
/*		   	Fonctions.c				*/
/*--------------------------------------------------------------*/

#include "main.h"
#include "Labels.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
void Remplir_Table_Labels (TYPE_VAL_FIELD OperandsField,
			   TYPE_VAL_FIELD label_field,
			   int *compteur_label,
			   struct label *labels)
{
	MAILLON_OPERANDS *operands=NULL;
	Extraction_Operands(OperandsField, &operands); 
	strcpy(labels[*compteur_label].string_value,label_field.string_value);
	labels[*compteur_label].value=ValueConst(operands->info);
	*compteur_label=*compteur_label+1;
	free(operands);	
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
long Parcours_Labels (char *label,struct label *labels)
{
	int i;
	for(i=0;i<TAILLE_LABELS;i++){	
		if(strcmp(labels[i].string_value,label)==0)
			return(labels[i].value);}
	printf("\nAttention label introuvable");
	return CODE_ERROR;
}
