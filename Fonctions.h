/*--------------------------------------------------------------*/
/*			Fonctions.h              		*/
/*--------------------------------------------------------------*/

/*---------------------------------------*/
/*  Fonctions définies dans Fonctions.c  */
/*---------------------------------------*/

/* Sauvergarde en mémoire du fichier de la table des mnémoniques */
void RemplirTableMnemoniques (char *fic_phy,struct oper *TabMne);

/* Affichage de la ligne extraite de la table des mnémoniques */
void Affichage_Ligne_TabMnemonique (struct oper TabMne);

/* Détermination du type d'opérande passée en paramètres */
TYPE_OPERATION Determination_Type_OP (TYPE_VAL_FIELD operation_field, struct oper *TabMne);

/* Affichage du code machine */
void Affichage_Code_Machine (struct machine_coding mcode);

/* Gère et crée le code machine */
void Gestion_Code_Machine (struct oper code_op,
			   TYPE_VAL_FIELD OperandsField,
			   int *compteur_assemblage,
			   struct label *labels,
			   struct machine_coding *mcode);

