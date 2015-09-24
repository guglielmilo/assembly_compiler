/*--------------------------------------------------------------*/
/*		   	Calculs.c				*/
/*--------------------------------------------------------------*/

#include "main.h"
#include "Calculs.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
long ValueConst (UL_VAL_OPERANDS lex)
{
	long val=0,c=0;
	if(lex.ul==UL_CONST){
		if(lex.string_value[0]==A_SOUST || lex.string_value[0]==A_PLUS)	
			c=1;	
		if(lex.string_value[c]==DOLLAR) /*Hexadécimal*/
			val=Chaine_Hexa(lex.string_value);
		else if(lex.string_value[c]==ATSIGN) /*Octal*/
			val=Chaine_Octal(lex.string_value);
		else if(lex.string_value[c]==PERCENT) /*Binaire*/
			val=Chaine_Binaire(lex.string_value);
		else
			val=Chaine_Dec(lex.string_value);/*Decimal*/
		return(val);}
	return 0;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
int TientSurUnOctet (long operand)
{
	if (operand<256)
		return 1;
	else
		return 0;
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
int Bits3_constant_offset (long operand)
{	
	if (operand<=8 && operand>=-8)
		return 1;
	else
		return 0;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
int Bits5_constant_offset (long operand)
{	printf("%ld ",operand);
	if (operand<16 && operand>=-16)
		return 1;
	else
		return 0;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
int TientSur9Bits (long operand)
{	/*operand sup à 5bits*/
	if ((operand<=255 && operand>15)||(operand>=-256 && operand<-16))
		return 1;
	else
		return 0;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
int TientSur16Bits (long operand)
{	/*operand sup à 9bits*/
	if ((operand<=32767 && operand>255)||(operand>=-32768 && operand<-256))
		return 1;
	else
		return 0;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
int Base16 (int b)
{
	int i,res=1;
	if(b==0)
		return 1;
	for(i=b;i>=1;i--)
		res=res*16;
	return res;
}

int Base8 (int b)
{
	int i,res=1;
	if(b==0)
		return 1;
	for(i=b;i>=1;i--)
		res=res*8;
	return res;
}

int Base2 (int b)
{
	int i,res=1;
	if(b==0)
		return 1;
	for(i=b;i>=1;i--)
		res=res*2;
	return res;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
long Chaine_Hexa (char chaine[])
{
	long val=0;
	int s=0,i,l,m=0;
	l=strlen(chaine);
	if(chaine[0]==A_SOUST || chaine[0]==A_PLUS)	
			s=1;
	for (i=l-1;i>s;i--){
		switch (chaine[i]){
			case 'A' :
				val=val+10*Base16(m);
			break;
			case 'B' :
				val=val+11*Base16(m);
			break;				
			case 'C' :
				val=val+12*Base16(m);
			break;
			case 'D' :
				val=val+13*Base16(m);
			break;
			case 'E' :
				val=val+14*Base16(m);
			break;
			case 'F' :
				val=val+15*Base16(m);
			break;
			default :
				val=val+(chaine[i]-48)*Base16(m);
			break;}
		m++;}
	if(s==1)
		return (-val);
	else
		return val;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
long Chaine_Octal (char chaine[])
{
	long val=0;
	int s=0,i,l,m=0;
	if(chaine[0]==A_SOUST || chaine[0]==A_PLUS)	
			s=1;
	l=strlen(chaine);	
	for (i=l-1;i>s;i--){
		val=val+(chaine[i]-48)*Base8(m);
		m++;}
	if(s==1)
		return (-val);
	else
		return val;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
long Chaine_Binaire (char chaine[])
{
	long val=0;
	int s=0,i,l,m=0;
	l=strlen(chaine);
	if(chaine[0]==A_SOUST || chaine[0]==A_PLUS)	
			s=1;
	for (i=l-1;i>s;i--){		
		val=val+(chaine[i]-48)*Base2(m);
		m++;}
	if(s==1)
		return (-val);
	else
		return val;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
long Chaine_Dec (char chaine[])
{
	long val=0;
	int s=0,i,l,m=1;
	l=strlen(chaine);
	if(chaine[0]==A_SOUST || chaine[0]==A_PLUS)	
		s=1;	
	for (i=l-1;i>=s;i--){
		val=val+(chaine[i]-48)*m;
		m=m*10;}
	if(s==1)
		return (-val);
	else
		return val;
}


/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
long OctetHaut(long val)
{
	return (val>>8); /*Valeur shifter de 8 à droite*/
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
long OctetBas(long val)
{
	if(val<0){
		val=(-val)&0x00FF;
		return(-val);}	
	return (val&0x000000FF); /*Masque*/
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
char *Gener_Hexa(int val)
{
	char *code;
	code=(char *)malloc(3*sizeof(char));
	sprintf(code,"%.2X",val);
	return code;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
char *Gener_Hexa4(int val)
{
	char *code;
	code=(char *)malloc(5*sizeof(char));
	sprintf(code,"%.4X",val);
	return code;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
char *Gener_Hexa8(int val)
{
	char *code;
	code=(char *)malloc(9*sizeof(char));
	sprintf(code,"%.8X",val);
	return code;
}



