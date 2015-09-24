/*--------------------------------------------------------------*/
/*		   	Directives.c				*/
/*--------------------------------------------------------------*/

#include "main.h"
#include "Directives.h"

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
void Remplir_Table_Labels_Adresse (TYPE_VAL_FIELD label_field,
				   int adresse,
			  	   int *compteur_label,
			   	   struct label *labels)
{
	MAILLON_OPERANDS *operands=NULL;
	Extraction_Operands(label_field, &operands); 
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

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
void Compteur_Assembalge (TYPE_VAL_FIELD OperandsField,int *compteur_assemblage,struct label *labels)
{
	MAILLON_OPERANDS *operands=NULL;
	Extraction_Operands(OperandsField, &operands); 
	if(operands->info.ul==UL_CONST)
		*compteur_assemblage=ValueConst(operands->info);
	if(operands->info.ul==UL_SYMBOL)
		*compteur_assemblage=Parcours_Labels(operands->info.string_value,labels);
}

