/*--------------------------------------------------------------*/
/*			S19.h              			*/
/*--------------------------------------------------------------*/

/*---------------------------------------*/
/*     Fonctions définies dans S19.c     */
/*---------------------------------------*/

/* Création du fichier S19 */
char *Creation_S19 (char *nom,FILE* S19);

/* Gestion du codage S19 lors du traitement de chaque mnémoniques */
void Code_S19_Mnemonique (struct machine_coding mcode,int *compteur_assemblage_S19,int *compteur_S19,int *ligne_S19,char *nom,FILE* S19);

/* Ecriture du ligne complète asm */
void Ecriture_Ligne_S19 (int *ligne_S19,int *compteur_S19,int *compteur_assemblage_S19,char *nom,FILE* S19);

/* Géneration de la check sum */
char *CheckSum (int *ligne_S19,int compteur_S19,int compteur_assemblage_S19,int compteur_S19_reste);

/* Finilasation du fichier S19 */
void Finalisation_S19 (char *nom,FILE* S19);
