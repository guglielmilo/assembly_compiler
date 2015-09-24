/*--------------------------------------------------------------*/
/*			Directives.h           			*/
/*--------------------------------------------------------------*/

/*-------------------------------------------*/
/*   Fonctions définies dans Directives.c    */
/*-------------------------------------------*/

/* Remplissage de la table des étiquettes EQU */
void Remplir_Table_Labels (TYPE_VAL_FIELD OperandsField,TYPE_VAL_FIELD label_field,int *compteur_label,struct label *labels);

/* Remplissage de la table des étiquettes adresses */
void Remplir_Table_Labels_Adresse (TYPE_VAL_FIELD label_field,int adresse,int *compteur_label,struct label *labels);

/* Parcours de la table des Labels */
long Parcours_Labels (char *label,struct label *labels);

/* Gestion et actualisation du compteur d'assemblage */
void Compteur_Assembalge (TYPE_VAL_FIELD OperandsField,int *compteur_assemblage,struct label *labels);

