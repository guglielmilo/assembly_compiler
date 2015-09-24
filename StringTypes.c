/*--------------------------------------------------------------*/
/*			StringTypes.c				*/
/*--------------------------------------------------------------*/

#include "main.h"

/*------------------------------------------------*/
/* char *StringUnite_Lexicale(UNITE_LEXICALE lex) */
/*------------------------------------------------*/

char *StringUnite_Lexicale(UNITE_LEXICALE lex)
{
  switch (lex) {
    case UL_EOL :
      return("EOL");
      break;

    case UL_ALPHABET :
      return("ALPHABET");
      break;

    case UL_PERIOD :
      return("PERIOD");
      break;

    case UL_UNDERSCORE :
      return("UNDERSCORE");
      break;

    case UL_DIGIT :
      return("DIGIT");
      break;

    case UL_DOLLAR :
      return("DOLLAR");
      break;

    case UL_TABU :
      return("TABU");
      break;

    case UL_SPACE :
       return("SPACE");
       break;

    case UL_SEMICOLON :
      return("SEMICOLON");
      break;

    case UL_INC :
      return("INC");
      break;

    case UL_DEC :
      return("DEC");
      break;

    case UL_STAR :
      return("STAR");
      break;

    case UL_CRO_OUV :
      return("CRO_OUV");
      break;

    case UL_CRO_FERM :
      return("CRO_FERM");
      break;

    case UL_DIESE :
      return("DIESE");
      break;

    case UL_PERCENT :
      return("PERCENT");
      break;

    case UL_ATSIGN :
      return("ATSIGN");
      break;

    case UL_APOSTROPHE :
      return("APOSTROPHE");
      break;

    case UL_COMMA :
      return("COMMA");
      break;

    case UL_EOS :
      return("EOS");
      break;

    case UL_SYMBOL :
      return("SYMBOL");
      break;
    
    case UL_REG_A :
      return("REG_A");
      break;

    case UL_REG_B :
      return("REG_B");
      break;

    case UL_REG_D :
      return("REG_D");
      break;

    case UL_REG_X :
      return("REG_X");
      break;

    case UL_REG_Y :
      return("REG_Y");
      break;

    case UL_REG_CCR :
      return("REG_CCR");
      break;

    case UL_REG_SP :
      return("REG_SP");
      break;

    case UL_REG_PC :
      return("REG_PC");
      break;

    case UL_REG_PCR :
      return("REG_PCR");
      break;

    case UL_CONST :
      return("CONST");
      break;

    case UL_INCONNU :
      return("INCONNU");
      break;

    default :
      return("ERREUR");
      break;
  }
}

/*----------------------------------------*/
/* char *StringType_Ligne(TYPE_LIGNE tlg) */
/*----------------------------------------*/

char *StringType_Ligne(TYPE_LIGNE tlg)
{
  switch (tlg) {
    case LIGNE_VIDE :
      return("LIGNE_VIDE");
      break;

    case LIGNE_REMPLIE :
      return("LIGNE_REMPLIE");
      break;

    default :
      return("ERREUR");
      break;
  }
}

/*---------------------------------------*/
/* char *StringType_Field(TYPE_FIELD tf) */
/*---------------------------------------*/

char *StringType_Field(TYPE_FIELD tf)
{
  switch (tf) {
    case LABEL_FIELD :
      return("LABEL_FIELD");
      break;

    case OPERATION_FIELD :
      return("OPERATION_FIELD");
      break;

    case OPERANDS_FIELD :
      return("OPERANDS_FIELD");
      break;

    case COMMENT_FIELD :
      return("COMMENT_FIELD");
      break;

    case EMPTY_FIELD :
      return("EMPTY_FIELD");
      break;

    default :
      return("ERREUR");
      break;
  }
}

/*---------------------------------------------------*/
/* char *StringContenu_Operands(CONTENU_OPERANDS co) */
/*---------------------------------------------------*/

char *StringContenu_Operands(CONTENU_OPERANDS co)
{
  switch (co) {
    case OPERANDS_VIDE :
      return("OPERANDS_VIDE");
      break;

    case OPERANDS_REMPLIE :
      return("OPERANDS_REMPLIE");
      break;

    default :
      return("ERREUR");
      break;
  }
}

/*------------------------------------------------*/
/* char *StringType_Operation(TYPE_OPERATION top) */
/*------------------------------------------------*/
char *StringType_Operation(TYPE_OPERATION top)
{
  switch (top) {
     case DIRECTIVE :
       return("DIRECTIVE");
       break;

     case MNEMONIQUE :
       return("MNEMONIQUE");
       break;

     case EMPTY_OPERATION :
       return("EMPTY_OPERATION");
       break;

     default :
      return("ERROR_OPERATION");
      break;
                 }
}

/*--------------------------------------*/
/* char *StringMode_Adressage(int mode) */
/*--------------------------------------*/
char *StringMode_Adressage(int mode)
{
  switch(mode)
    {

    case INH :
      return("INH");
      break;

    case IMM :
      return("IMM");
      break;

    case DIR :
      return("DIR");
      break;

    case EXT :
      return("EXT");
      break;

    case REL :
      return("REL");
      break;

    case IDX :
      return("IDX");
      break;

    case IDX1 :
      return("IDX1");
      break;

    case IDX2 :
      return("IDX2");
      break;

    case IIDX2 :
      return("[IDX2]");
      break;

    case DIDX :
      return("[D,IDX]");
      break;

    default :
      return("INDEFINI");
      break;
    }
}

/*------------------------------------*/
/* char *StringCodeNotation(int code) */
/*------------------------------------*/
char *StringCodeNotation(int code)
{
  switch(code)
    {
    case ii :
      return("ii");
      break;

    case dd :
      return("dd");
      break;

    case hh :
      return("hh");
      break;

    case ll :
      return("ll");
      break;

    case xb :
      return("xb");
      break;

    case ee :
      return("ee");
      break;

    case ff :
      return("ff");
      break;

    case jj :
      return("jj");
      break;

    case kk :
      return("kk");
      break;

    case mm :
      return("mm");
      break;


    case pg :
      return("pg");
      break;

    case qq :
      return("qq");
      break;

    case rr :
      return("rr");
      break;

    case lb :
      return("lb");
      break;

    default :
      return("EMPTY");
      break;
    }
}
