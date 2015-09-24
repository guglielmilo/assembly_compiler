/*--------------------------------------------------------------*/
/*			Ligne.h	               			*/
/*--------------------------------------------------------------*/

/*-----------------------------------*/
/*  Fonctions définies dans Ligne.c  */
/*-----------------------------------*/

UNITE_LEXICALE LexemeLigne(char *ligne, int *pdeb);

void statement (char *ligne, int *pdeb, UNITE_LEXICALE *pProchain, TYPE_LIGNE *ptlg, 
                TYPE_VAL_FIELD *pLabelField, 
                TYPE_VAL_FIELD *pOperationField, 
                TYPE_VAL_FIELD *pOperandsField, 
                TYPE_VAL_FIELD *pCommentField);

void label_field (char *ligne, int *pdeb, UNITE_LEXICALE *pProchain);

void suite_label (char *ligne, int *pdeb, UNITE_LEXICALE *pProchain);

void operation_field (char *ligne, int *pdeb, UNITE_LEXICALE *pProchain);

void suite_operation(char *ligne, int *pdeb, UNITE_LEXICALE *pProchain);

void operands_field(char *ligne, int *pdeb, UNITE_LEXICALE *pProchain);

void suite_operands(char *ligne, int *pdeb, UNITE_LEXICALE *pProchain);

void comment_field(char *ligne, int *pdeb, UNITE_LEXICALE *pProchain);

void suite_comment(char *ligne, int *pdeb, UNITE_LEXICALE *pProchain);