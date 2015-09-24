/*--------------------------------------------------------------*/
/*		   	    S19.c				*/
/*--------------------------------------------------------------*/

#include "main.h"
#include "S19.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
char *Creation_S19 (char *fic_asm,FILE* S19)
{  
	int i,l;
	char *fic_s19; /* Nom physique du fichier s19*/
	l=strlen(fic_asm);
	fic_s19=(char *)malloc(l*sizeof(char));
	for(i=l-4;i>=0;i--)
		fic_s19[i]=fic_asm[i];
	fic_s19[l-3]='s';fic_s19[l-2]='1';fic_s19[l-1]='9';fic_s19[l]='\0';
	S19=fopen(fic_s19,"w");
	fputs("S0030000FC\n",S19);
	fclose(S19);
	return fic_s19;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
void Code_S19_Mnemonique (struct machine_coding mcode,int *compteur_assemblage_S19,int *compteur_S19,
						int *ligne_S19,char *nom,FILE* S19)
{
	if(mcode.nbopcodes>=1){
	    if(*compteur_S19==16)
		Ecriture_Ligne_S19(ligne_S19,compteur_S19,compteur_assemblage_S19,nom,S19);
	    ligne_S19[*compteur_S19]=mcode.opcode1;
	    *compteur_S19=*compteur_S19+1;}
	    if(mcode.nbopcodes==2){
	   	if(*compteur_S19==16)
		   Ecriture_Ligne_S19(ligne_S19,compteur_S19,compteur_assemblage_S19,nom,S19);
		ligne_S19[*compteur_S19]=mcode.opcode2;
		*compteur_S19=*compteur_S19+1;}
	if(mcode.nbdata>=1){
	    if(*compteur_S19==16)
		Ecriture_Ligne_S19(ligne_S19,compteur_S19,compteur_assemblage_S19,nom,S19);
	    ligne_S19[*compteur_S19]=mcode.data1;
	    *compteur_S19=*compteur_S19+1;}
	    if(mcode.nbdata>=2){
	  	if(*compteur_S19==16)
		   Ecriture_Ligne_S19(ligne_S19,compteur_S19,compteur_assemblage_S19,nom,S19);
		ligne_S19[*compteur_S19]=mcode.data2;
		*compteur_S19=*compteur_S19+1;}
		if(mcode.nbdata>=3){
	   	    if(*compteur_S19==16)
			Ecriture_Ligne_S19(ligne_S19,compteur_S19,compteur_assemblage_S19,nom,S19);
	   	    ligne_S19[*compteur_S19]=mcode.data3;
		    *compteur_S19=*compteur_S19+1;}
 		    if(mcode.nbdata>=4){
	   		if(*compteur_S19==16)
			    Ecriture_Ligne_S19(ligne_S19,compteur_S19,compteur_assemblage_S19,nom,S19);
		    	ligne_S19[*compteur_S19]=mcode.data4;
			*compteur_S19=*compteur_S19+1;}
			if(mcode.nbdata==5){
	    		   if(*compteur_S19==16)
			       Ecriture_Ligne_S19(ligne_S19,compteur_S19,compteur_assemblage_S19,nom,S19);
		    	   ligne_S19[*compteur_S19]=mcode.data5;
			   *compteur_S19=*compteur_S19+1;}
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/	
void Ecriture_Ligne_S19 (int *ligne_S19,int *compteur_S19,int *compteur_assemblage_S19,char *nom,FILE* S19)
{
	int i;
	S19=fopen(nom,"a");
	fputs("S1",S19);
	fputs(Gener_Hexa(*compteur_S19+3),S19);
	fputs(Gener_Hexa4(*compteur_assemblage_S19),S19);
	for(i=0;i<*compteur_S19;i++)
		fputs(Gener_Hexa(ligne_S19[i]),S19);
	fputs(CheckSum(ligne_S19,*compteur_S19,*compteur_assemblage_S19,*compteur_S19+3),S19);
	fputs("\n",S19);
	*compteur_assemblage_S19=*compteur_assemblage_S19+*compteur_S19;
	*compteur_S19=0;
	fclose(S19);
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
char *CheckSum (int *ligne_S19,int compteur_S19,int compteur_assemblage_S19,int compteur_S19_reste)
{
	char *checksum;
	int i,cs=compteur_S19_reste;
	cs=cs+OctetHaut(compteur_assemblage_S19)+OctetBas(compteur_assemblage_S19);
	checksum=(char *)malloc(3*sizeof(char));
	for(i=0;i<compteur_S19;i++)
		cs=cs+ligne_S19[i];
	checksum=Gener_Hexa((~cs)&0xFF);/*Poids faible du complément à 1*/
	return checksum;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
void Finalisation_S19 (char *nom,FILE* S19)
{
	S19=fopen(nom,"a");
	fputs("S9030000FC\n",S19);
	fclose(S19);
}
	
