/*--------------------------------------------------------------*/
/*		   	Listing.h				*/
/*--------------------------------------------------------------*/

/*---------------------------------------*/
/*   Fonctions définies dans Listing.c   */
/*---------------------------------------*/

/* Création du fichier lst */
char *Creation_listing (char *fic_asm,FILE* lst);

/* Ecriture d'une ligne spécifique aux directices */
void Ecriture_Ligne_listing_directives (int ligne_listing,TYPE_VAL_FIELD OperandsField,struct label *labels,char *nom,FILE* lst);

/* Ecriture d'une ligne */
void Ecriture_Ligne_asm_listing (char *ligne,char *nom,FILE* lst);

/* Ecriture d'une ligne vide */
void Ecriture_Ligne_vide_listing (int ligne_listing,char *nom,FILE* lst);
void Ecriture_Ligne_listing_mcode (int ligne_listing,struct machine_coding mcode,struct oper code_op,char *nom,FILE* lst);

