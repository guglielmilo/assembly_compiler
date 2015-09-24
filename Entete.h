/*--------------------------------------------------------------*/
/*			Entete.h            		        */
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
#define TAILLE_TABLE_MNEMONIQUES 561

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
  int no_ligne;         
  TYPE_OPERATION top;

  TYPE_VAL_FIELD LabelField;
  TYPE_VAL_FIELD OperationField; 
  TYPE_VAL_FIELD OperandsField;  
  TYPE_VAL_FIELD CommentField;   

  struct oper def_code;
  long compteur_assemblage; 

  int nboctets;
  int octet1;
  int octet2;
  int octet3;
  int octet4;
  int octet5;
  int octet6;
  };

/*-------------------------------------------------------------------------------------------*/
/*                        FONCTIONS UTILISATEUR                                              */
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

/*----------------------*/
/*	Focntions.o 	*/
/*----------------------*/

