/*--------------------------------------------------------------*/
/*		   	Listing.c				*/
/*--------------------------------------------------------------*/

#include "main.h"
#include "Listing.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
char *Creation_listing (char *fic_asm,FILE* lst)
{  
	int i,l;
	char *fic_lst; /* Nom physique du fichier s19*/
	l=strlen(fic_asm);
	fic_lst=(char *)malloc(l*sizeof(char));
	for(i=l-4;i>=0;i--)
		fic_lst[i]=fic_asm[i];
	fic_lst[l-3]='l';fic_lst[l-2]='s';fic_lst[l-1]='t';fic_lst[l]='\0';
	lst=fopen(fic_lst,"w");
	fputs(fic_lst,lst);
	fputs("\n\n",lst);
	fclose(lst);
	return fic_lst;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/	
void Ecriture_Ligne_listing_directives (int ligne_listing,TYPE_VAL_FIELD OperandsField,struct label *labels,
					char *nom,FILE* lst)
{
	MAILLON_OPERANDS *operands=NULL;
	Extraction_Operands(OperandsField, &operands);
	lst=fopen(nom,"a"); 
	if(ligne_listing<10)
		fputs("    ",lst);
	if(ligne_listing<100 && ligne_listing>=10)
		fputs("   ",lst);
	fprintf(lst,"%d:          =",ligne_listing);
	if(operands->info.ul==UL_CONST)
		fputs(Gener_Hexa8(ValueConst(operands->info)),lst);
	if(operands->info.ul==UL_SYMBOL)
		fputs(Gener_Hexa8(Parcours_Labels(operands->info.string_value,labels)),lst);
	fputs("\t        ",lst);
	free(operands);
	fclose(lst);
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/	
void Ecriture_Ligne_listing_mcode (int ligne_listing,struct machine_coding mcode,struct oper code_op,char *nom,FILE* lst)
{
	int i=1;
	lst=fopen(nom,"a");
	if(ligne_listing<10)
		fputs("    ",lst);
	if(ligne_listing<100 && ligne_listing>=10)
		fputs("   ",lst);
	fprintf(lst,"%d:     %.4lX ",ligne_listing,mcode.compteur_assemblage);
	
	/*Ecriture des opcodes*/
	if(mcode.nbopcodes==1)
		fprintf(lst,"%.2X",mcode.opcode1);
	if(mcode.nbopcodes==2)
		fprintf(lst,"%.2X%.2X",mcode.opcode1,mcode.opcode2);
	fputs(" ",lst);

	/*Ecritures des data*/
	while(i<=mcode.nbdata){
		switch(i){
		case(1):
			if((code_op.data1==hh && code_op.data2==ll)||
			   (code_op.data1==jj && code_op.data2==kk)||
			   (code_op.data1==qq && code_op.data2==rr)){
				fprintf(lst,"%.2X%.2X ",mcode.data1,mcode.data2);
				i=3;}
			else{
				fprintf(lst,"%.2X ",mcode.data1);i++;}
		break;
		case(2):
			if(code_op.data2==ee && code_op.data3==ff){
				fprintf(lst,"%.2X%.2X ",mcode.data2,mcode.data3);
				i=4;}
			else{
				fprintf(lst,"%.2X ",mcode.data2);i++;}
		break;
		case(3):
			fprintf(lst,"%.2X ",mcode.data3);i++;
		break;
		case(4):
			fprintf(lst,"%.2X ",mcode.data4);i++;
		break;
		case(5):
			fprintf(lst,"%.2X ",mcode.data5);i++;
		break;}}
	if(mcode.nbdata+mcode.nbopcodes < 3)
		fputs("\t",lst);	
	fputs("\t\t ",lst);
	fclose(lst);
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/	
void Ecriture_Ligne_asm_listing (char *ligne,char *nom,FILE* lst)
{
	lst=fopen(nom,"a");
	fprintf(lst,"%s",ligne);
	fclose(lst);
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/	
void Ecriture_Ligne_vide_listing (int ligne_listing,char *nom,FILE* lst)
{
	lst=fopen(nom,"a");
	if(ligne_listing<10)
		fputs("    ",lst);
	if(ligne_listing<100 && ligne_listing>=10)
		fputs("   ",lst);
	fprintf(lst,"%d:",ligne_listing);
	fclose(lst);
}

