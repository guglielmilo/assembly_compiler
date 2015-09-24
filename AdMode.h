/*--------------------------------------------------------------*/
/*			AdMode.h   	           		*/
/*--------------------------------------------------------------*/

/*---------------------------------------*/
/*  Fonctions définies dans AdMode.c     */
/*---------------------------------------*/

/* Définie le mode d'adressage */
int Mode_Adressage(TYPE_VAL_FIELD OperationField,struct oper *TabMne,struct label *labels);

/* Recherche dans la table de mnémoniques si l'operande a un mode d'adressage relative */	
int Relative_Mode(char *mne,struct oper *TabMne);

/* Recherche dans la table de mnémoniques la ligne équivalente à l'operande et au mode d'adressage */
struct oper Definition_Codage_Instruction(char *mne,int *admode,struct oper *TabMne);

/* Calcul du code machine correspondant aux paramètres passés */
long Codage_Operandes(int data,TYPE_VAL_FIELD OperandsField,int pc,struct label *labels);


