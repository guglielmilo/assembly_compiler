/*--------------------------------------------------------------*/
/*		   	Fonctions.c				*/
/*--------------------------------------------------------------*/

#include "main.h"
#include "Fonctions.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
void RemplirTableMnemoniques (char *fic_phy,struct oper *TabMne)
{
	char ligne[80];
	int i=0;
	FILE *fic_log_phy;
/* Ouverture du fichier texte en mode Lecture */
	fic_log_phy = fopen(fic_phy, "rt");
	if (fic_log_phy == NULL){
		perror("Erreur ouverture fichier table mnemonique");
		exit(1);}

/* Lecture du fichier texte ligne par ligne */
	fgets(ligne, 80, fic_log_phy); /*Première ligne : définition des variables du fichier */  
	for(i=0;i<=TAILLE_TABLE_MNEMONIQUES;i++){
		fscanf(fic_log_phy,"%d %d %d %x %x %d %d %d %d %d %d %s",
			&TabMne[i].admode,
			&TabMne[i].nboctets,
			&TabMne[i].nbopcodes,
			&TabMne[i].opcode1,
			&TabMne[i].opcode2,
			&TabMne[i].nbdata,
			&TabMne[i].data1,
			&TabMne[i].data2,
			&TabMne[i].data3,
			&TabMne[i].data4,
			&TabMne[i].data5,
			TabMne[i].mnemonic);
		fgets(ligne, 80, fic_log_phy);}

/* Fermeture du fichier texte */
	fclose(fic_log_phy);
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
void Affichage_Ligne_TabMnemonique (struct oper TabMne)
{
	printf("%d %d %d %.8X %.8X %d %d %d %d %d %d %s\n",
	TabMne.admode,
	TabMne.nboctets,
	TabMne.nbopcodes,
	TabMne.opcode1,
	TabMne.opcode2,
	TabMne.nbdata,
	TabMne.data1,
	TabMne.data2,
	TabMne.data3,
	TabMne.data4,
	TabMne.data5,
	TabMne.mnemonic);
}
/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
TYPE_OPERATION Determination_Type_OP (TYPE_VAL_FIELD operation_field, struct oper *TabMne)
{    
	int i=0; 	
	switch(operation_field.type_field){
		case LABEL_FIELD : return(DIRECTIVE);
		break;
		case OPERATION_FIELD :
			while(strcmp(operation_field.string_value,TabMne[i].mnemonic)==1 && i<=560)
				i++; /*Recherche du mnémonique dans la table*/
			if(strcmp(operation_field.string_value,TabMne[i].mnemonic)==0){
				/*printf("\tTabMne:%d",i);*/
				return(MNEMONIQUE);}
			else		
				if(strcmp(operation_field.string_value,"EQU")==0 ||
				   strcmp(operation_field.string_value,"ORG")==0)
					return(DIRECTIVE);
				else
					return(ERROR_OPERATION);
		break;
		case OPERANDS_FIELD : return (EMPTY_OPERATION);			
		break;
		case COMMENT_FIELD : return (EMPTY_OPERATION);
		break;
		case EMPTY_FIELD : return (EMPTY_OPERATION);
		break;
		default: return (ERROR_OPERATION);
		break;}
}


/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
void Gestion_Code_Machine (struct oper code_op,
			   TYPE_VAL_FIELD OperandsField,
			   int *compteur_assemblage,
			   struct label *labels,
			   struct machine_coding *mcode)
{
	mcode->compteur_assemblage=*compteur_assemblage;
	mcode->nbopcodes=code_op.nbopcodes;
	if(code_op.nbopcodes>=1){
	  mcode->opcode1=code_op.opcode1;
	  *compteur_assemblage=*compteur_assemblage+1;}
	  if(code_op.nbopcodes==2){
	    mcode->opcode2=code_op.opcode2;
	    *compteur_assemblage=*compteur_assemblage+1;}
	mcode->nbdata=code_op.nbdata;
	if(code_op.nbdata>=1){
	  mcode->data1=Codage_Operandes(code_op.data1,OperandsField,*compteur_assemblage,labels);
	  *compteur_assemblage=*compteur_assemblage+1;}
	    if(code_op.nbdata>=2){
	      mcode->data2=Codage_Operandes(code_op.data2,OperandsField,*compteur_assemblage,labels);
	      *compteur_assemblage=*compteur_assemblage+1;}
		if(code_op.nbdata>=3){
		  mcode->data3=Codage_Operandes(code_op.data3,OperandsField,*compteur_assemblage,labels);	 
		  *compteur_assemblage=*compteur_assemblage+1;}
 		    if(code_op.nbdata>=4){
		      mcode->data4=Codage_Operandes(code_op.data4,OperandsField,*compteur_assemblage,labels);
		      *compteur_assemblage=*compteur_assemblage+1;}
			if(code_op.nbdata==5){
			  mcode->data5=Codage_Operandes(code_op.data5,OperandsField,*compteur_assemblage,labels);
			  *compteur_assemblage=*compteur_assemblage+1;}
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
void Affichage_Code_Machine (struct machine_coding mcode)
{
	printf("%.4lX | ",mcode.compteur_assemblage);
	if(mcode.nbopcodes>=1)
	  printf("%.2X ",mcode.opcode1);
	  if(mcode.nbopcodes==2)
	    printf("%.2X ",mcode.opcode2);
	if(mcode.nbdata>=1)
	  printf("%.2X ",mcode.data1);
	    if(mcode.nbdata>=2)
	      printf("%.2X ",mcode.data2);
		if(mcode.nbdata>=3)
		  printf("%.2X ",mcode.data3);
 		    if(mcode.nbdata>=4)
		      printf("%.2X ",mcode.data4);
			if(mcode.nbdata==5)
			  printf("%.2X ",mcode.data5);
}

