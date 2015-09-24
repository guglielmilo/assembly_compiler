/*--------------------------------------------------------------*/
/*			main.h            		        */
/*--------------------------------------------------------------*/

/*----------------------*/
/* Librairies Standards */
/*----------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*--------------------------------------------------------------*/
/*      Codage des Modes d'adressage du 68HC12             	*/
/*--------------------------------------------------------------*/
#define INDEFINI (-1)           /* on ne sait pas encore ...    */
#define INH      0		/* Inherent addressing          */
#define IMM      1		/* Immediat mode                */
#define DIR      2		/* Direct mode                  */
#define EXT      3		/* Extended mode                */
#define REL      4		/* Relative mode                */
#define IDX      5		/* Indexed mode                 */
#define IDX1     6		/* 9-bit Indexed                */
#define IDX2     7		/* 16-bit Indexed               */
#define IIDX2    8		/* Indirect 16-bit Indexed      */
#define DIDX     9		/* D-Indirect Indexed           */

/*--------------------------------------------------------------*/
/* Codage du format des operandes				*/
/*--------------------------------------------------------------*/
#define	ii	0
#define dd	1
#define	hh	2
#define ll	3
#define xb	4
#define ee	5
#define	ff	6
#define	jj	7
#define kk	8
#define	mm	9
#define pg	10
#define qq	11
#define	rr	12
#define lb	13
#define EMPTY	(-1)

/*--------------------------------------------------------------*/
/* Structure détaillée d'une instruction du HC12                */
/*--------------------------------------------------------------*/
struct oper {
  int admode;	    /* son mode d'adressage 	                                          */
  int nboctets;     /* nombre d'octets pour le codage total de l'instruction (1 à 6)      */
  int nbopcodes;    /* nombre d'octets utilisés pour le codage de la mnémoniques (1 ou 2) */
  int opcode1;	    /* le 1er octet du codage de la mnémonique	                          */
  int opcode2;	    /* le 2eme octet du codage de la mnémonique	                          */
  int nbdata;       /* nombre d'octets du codage des operandes (0 à 5)                    */
  int data1;	    /* format 1er  octet machine coding                                   */
  int data2;	    /* format 2eme octet machine coding                                   */
  int data3;	    /* format 3eme octet machine coding                                   */
  int data4;	    /* format 4eme octet machine coding                                   */
  int data5;	    /* format 5eme octet machine coding                                   */
  char mnemonic[6]; /* la mnémonique en majuscules                                        */
};

/*-----------------*/
/* Table de Labels */
/*---------------- */
struct label {
  char string_value[20];
  long value;
  struct label *suivant;
};

/*------------------------------*/
/* Constantes et nouveaux types */
/*------------------------------*/
#define TRUE      1
#define FALSE     0

#define EOL_STRING  '\r'
#define EOF_STRING  '\0'
#define EOL_WIN     '\n'
#define EOS         '\0'
#define TABU        '\t'
#define SPACE       ' '
#define PERIOD      '.'
#define UNDERSCORE  '_'
#define DOLLAR      '$'
#define SEMICOLON   ';'
#define A_PLUS      '+'
#define A_SOUST     '-'
#define STAR        '*'
#define PAR_OUV     '('
#define PAR_FERM    ')'
#define CRO_OUV     '['
#define CRO_FERM    ']'
#define DIESE       '#'
#define COMMA       ','
#define PERCENT     '%'
#define ATSIGN      '@'
#define APOSTROPHE  '\''

/*----------------------------------------------------------------------*/
/* Les unitées lexicales d'une ligne d'instruction et du champ Operands */
/*----------------------------------------------------------------------*/

typedef enum {
  UL_EOL, 
  UL_ALPHABET,
  UL_PERIOD,
  UL_UNDERSCORE,
  UL_DIGIT,
  UL_DOLLAR,
  UL_TABU, 
  UL_SPACE,
  UL_SEMICOLON,
  UL_INC, 
  UL_DEC, 
  UL_STAR, 
  UL_CRO_OUV, 
  UL_CRO_FERM,
  UL_DIESE, 
  UL_PERCENT, 
  UL_ATSIGN, 
  UL_APOSTROPHE,
  UL_COMMA,

  UL_EOS,
  UL_SYMBOL,
  UL_CONST, 
  UL_REG_A, 
  UL_REG_B,
  UL_REG_D,
  UL_REG_X,
  UL_REG_Y,
  UL_REG_CCR,
  UL_REG_SP,
  UL_REG_PC,
  UL_REG_PCR,

  UL_INCONNU
             } UNITE_LEXICALE;


/*------------------------------------------------------------------*/
/* Les differents types de champs dans une ligne de code assembleur */
/*------------------------------------------------------------------*/

typedef enum {
  LABEL_FIELD,
  OPERATION_FIELD,
  OPERANDS_FIELD,
  COMMENT_FIELD,
  EMPTY_FIELD
             } TYPE_FIELD;

/*--------------------------------*/
/* Les differents types de lignes */
/*--------------------------------*/

typedef enum {
  LIGNE_VIDE,
  LIGNE_REMPLIE
             } TYPE_LIGNE;

/*-----------------------------------------------------------------------*/
/* Les informations relatives à un champs d'une ligne de code assembleur */
/*-----------------------------------------------------------------------*/

typedef struct {
  TYPE_FIELD  type_field; /* type d'un champs */
  char *string_value;     /* valeur du champs */
               } TYPE_VAL_FIELD;


/*----------------------------------------------------------*/
/* Les informations relatives à un lexeme du champs Operands*/
/*----------------------------------------------------------*/

typedef struct {
  UNITE_LEXICALE ul;
  char *string_value;
               } UL_VAL_OPERANDS;

/*--------------------------------------------------------*/
/* Liste chainée des lexemes composant le champs Operands */
/*--------------------------------------------------------*/

typedef struct maillon_operands {
  UL_VAL_OPERANDS info; 
  struct maillon_operands *suivant;
               } MAILLON_OPERANDS;

/*------------------------------------------*/
/* Type de resultat de Extraction__Operands */
/*------------------------------------------*/
typedef enum {
  OPERANDS_VIDE,
  OPERANDS_REMPLIE
             } CONTENU_OPERANDS;

/*--------------------------------------------------------------------*/
/* Nombre d'instructions detaillées dans le fichier Mnemoniques.txt   */
/*--------------------------------------------------------------------*/
#define TAILLE_TABLE_MNEMONIQUES 562
#define TAILLE_TABLE_MNEMONIQUES_REL 44
#define TAILLE_LABELS 100
#define CODE_ERROR 0xEEEEEEEE

/*-------------------------------*/
/* Les differents TYPE_OPERATION */
/*-------------------------------*/
typedef enum	{
  DIRECTIVE,
  MNEMONIQUE,
  EMPTY_OPERATION,
  ERROR_OPERATION
		} TYPE_OPERATION;

/*-----------------------------------*/
/* Codage machine d'une instructions */
/*-----------------------------------*/
struct machine_coding {
  long compteur_assemblage;
  int nbopcodes;
  int opcode1;
  int opcode2;
  int nbdata;
  int data1;
  int data2;
  int data3;
  int data4;
  int data5;
  };

/*-------------------------------------------------------------------------------------------*/
/*                                FONCTIONS UTILISATEUR                                      */
/*-------------------------------------------------------------------------------------------*/
/*             Pour plus d'information ouvrir le fichier header correspondant                */
/*-------------------------------------------------------------------------------------------*/

/*-----------------------*/
/* StringTypes.o         */
/*-----------------------*/
/* uniquement code objet */
/*-----------------------*/
char *StringUnite_Lexicale(UNITE_LEXICALE lex);
char *StringType_Ligne(TYPE_LIGNE tlg);
char *StringType_Field(TYPE_FIELD tf);
char *StringContenu_Operands(CONTENU_OPERANDS co);
char *StringType_Operation(TYPE_OPERATION top);
char *StringMode_Adressage(int mode);
char *StringCodeNotation(int code);

/*-----------------------*/
/* Analyse.o             */
/*-----------------------*/
/* uniquement code objet */
/*-----------------------*/
TYPE_LIGNE Extraction_Fields(char *ligne, 
                             TYPE_VAL_FIELD *pLabelField, 
                             TYPE_VAL_FIELD *pOperationField, 
                             TYPE_VAL_FIELD *pOperandsField, 
                             TYPE_VAL_FIELD *pCommentField);

CONTENU_OPERANDS Extraction_Operands(TYPE_VAL_FIELD OperandsField, MAILLON_OPERANDS **poperands);

/*------------------------*/
/* ListeChaineeOperands.o */
/*------------------------*/
/* uniquement code objet */
/*-----------------------*/
void FreeMaillon_Operands(MAILLON_OPERANDS *lst);
MAILLON_OPERANDS *InitialiseMaillon_Operands(UL_VAL_OPERANDS ValExpr);
MAILLON_OPERANDS *AjouterMaillon_Operands(MAILLON_OPERANDS *poperande, UL_VAL_OPERANDS ValExpr);
void AfficherMaillon_Operands(MAILLON_OPERANDS *poperande);

/*---------------------------------------*/
/*  Fonctions définies dans Fonctions.o  */
/*---------------------------------------*/
void RemplirTableMnemoniques (char *fic_phy,struct oper *TabMne);
void Affichage_Ligne_TabMnemonique (struct oper TabMne);
TYPE_OPERATION Determination_Type_OP (TYPE_VAL_FIELD operation_field, struct oper *TabMne);
void Affichage_Code_Machine (struct machine_coding mcode);
void Gestion_Code_Machine (struct oper code_op, TYPE_VAL_FIELD OperandsField, int *compteur_assemblage, struct label *labels, struct machine_coding *mcode);

/*---------------------------------------*/
/*  Fonctions définies dans AdMode.o     */
/*---------------------------------------*/
int Mode_Adressage(TYPE_VAL_FIELD OperandsField,struct oper *TabMne,struct label *labels);
int Relative_Mode(char *mne,struct oper *TabMne);
struct oper Definition_Codage_Instruction(char *mne,int *admode,struct oper *TabMne);
long Codage_Operandes(int data,TYPE_VAL_FIELD OperandsField,int pc,struct label *labels);

/*---------------------------------------*/
/*     Fonctions définies dans S19.o     */
/*---------------------------------------*/
void Code_S19_Mnemonique (struct machine_coding mcode,int *compteur_assemblage_S19,int *compteur_S19,int *ligne_S19,char *nom,FILE* S19);
char *Creation_S19 (char *nom,FILE* S19);
void Finalisation_S19 (char *nom,FILE* S19);
void Ecriture_Ligne_S19 (int *ligne_S19,int *compteur_S19,int *compteur_assemblage_S19,char *nom,FILE* S19);
char *CheckSum (int *ligne_S19,int compteur_S19,int compteur_assemblage_S19,int compteur_S19_reste);

/*---------------------------------------*/
/*   Fonctions définies dans Listing.o   */
/*---------------------------------------*/
char *Creation_listing (char *fic_asm,FILE* lst);
void Ecriture_Ligne_listing_directives (int ligne_listing,TYPE_VAL_FIELD OperandsField,struct label *labels,char *nom,FILE* lst);
void Ecriture_Ligne_asm_listing (char *ligne,char *nom,FILE* lst);
void Ecriture_Ligne_vide_listing (int ligne_listing,char *nom,FILE* lst);
void Ecriture_Ligne_listing_mcode (int ligne_listing,struct machine_coding mcode,struct oper code_op,char *nom,FILE* lst);


/*-------------------------------------------*/
/*   Fonctions définies dans Directives.o    */
/*-------------------------------------------*/
void Remplir_Table_Labels(TYPE_VAL_FIELD OperandsField,TYPE_VAL_FIELD label_field,int *compteur_label,struct label *labels);
void Remplir_Table_Labels_Adresse (TYPE_VAL_FIELD label_field,int adresse,int *compteur_label,struct label *labels);
long Parcours_Labels (char *label,struct label *labels);
void Compteur_Assembalge (TYPE_VAL_FIELD OperandsField,int *compteur_assemblage,struct label *labels);

/*---------------------------------------*/
/*   Fonctions définies dans Calculs.o   */
/*---------------------------------------*/
long ValueConst (UL_VAL_OPERANDS lex);
int TientSurUnOctet (long operand);
int Bits3_constant_offset (long operand);
int Bits5_constant_offset (long operand);
int TientSur9Bits (long operand);
int TientSur16Bits (long operand);
int Base16 (int b);
int Base8 (int b);
int Base2 (int b);
long Chaine_Hexa (char chaine[]);
long Chaine_Octal (char chaine[]);
long Chaine_Binaire (char chaine[]);
long Chaine_Dec (char chaine[]);
long OctetHaut (long val);
long OctetBas (long val);
char *Gener_Hexa(int val);
char *Gener_Hexa4(int val);
char *Gener_Hexa8(int val);

