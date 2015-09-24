/*--------------------------------------------------------------*/
/*			Calculs.h              		*/
/*--------------------------------------------------------------*/

/*---------------------------------------*/
/*   Fonctions définies dans Calculs.c   */
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

