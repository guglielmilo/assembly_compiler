/*--------------------------------------------------------------*/
/*			Labels.h              			*/
/*--------------------------------------------------------------*/

/*---------------------------------------*/
/*   Fonctions définies dans Lables.c    */
/*---------------------------------------*/

void Remplir_Table_Labels (TYPE_VAL_FIELD OperandsField,
			   TYPE_VAL_FIELD label_field,
			   int *compteur_label,
			   struct label *labels);

long Parcours_Labels (char *label,struct label *labels);

