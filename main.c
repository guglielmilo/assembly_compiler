/*--------------------------------------------------------------*/
/*                          main.c                              */
/*--------------------------------------------------------------*/
#include "main.h"
/*************************/
/* Programme Principal   */
/*************************/
int main(int argc,char *argv[])
{  
  printf("\nPROJET INFORMATIQUE");
  printf("\n******************************************************************************");
  printf("\nUtilisation: projet [options]\n");
  printf("\nOptions: -def   default:utilisation de TableMnemoniques.txt et de exemple.asm");
  printf("\n         -ac    affichage code");
  printf("\n         -adm   affichage mode adressage (nécessite l'option -ac)");
  printf("\n         -adc   affichage détaillé du code machine (nécessite l'option -ac)\n\n");

  char fic_asm[20]; /* Nom physique du fichier assembleur */
  char fic_txt[20]; /* Nom physique du fichier texte */
  char *fic_s19; /* Nom physique du fichier s19*/
  char *fic_lst; /* Nom physique du fichier lst*/
  int aff=0, affad=0, affac=0; /*Option d'affichage */
  int def=0; /*Saisie par default*/

  /*--------------------------------------------------------*/
  /* declarations des variables necessaires a l'utilisation */
  /* des fonctions Extraction_Fields et Extraction_Operands */
  /*--------------------------------------------------------*/
  char ligne[80];
  TYPE_LIGNE tlg;
  TYPE_VAL_FIELD LabelField;
  TYPE_VAL_FIELD OperationField;
  TYPE_VAL_FIELD OperandsField;
  TYPE_VAL_FIELD CommentField;
  
  /* Nom logique du fichier assembleur */
  FILE *fic_log_asm;
  /* Nom logique du fichier s19 */
  FILE *S19=NULL;
  /* Nom logique du fichier listing */
  FILE *lst=NULL;

  /*Creation d'un tableau de structure détaillée d'instruction du HC12*/  
  struct oper TabMne[TAILLE_TABLE_MNEMONIQUES];

  /*Type d'opération de la ligne testé*/  
  TYPE_OPERATION top;

  /*Mode d'adressage de la ligne testé*/
  int admode=INDEFINI;

  /*Code OP de la ligne testé*/
  struct oper code_op;

  /*Adresses des codes machines*/
  int compteur_assemblage=0; /*On commence à 0 pour la première passe*/
  int compteur_assemblage_S19=0;

  /*Création d'un tableau de structure de labels*/
  struct label labels[TAILLE_LABELS];
  int compteur_label=0;

  /*Création d'une structure contenant le code machine de la ligne*/
  struct machine_coding mcode;

  /*Compteur de caratères d'une ligne du fichier S19*/
  int compteur_S19=0;

  /*Tableaux d'entier d'une ligne S19*/
  int ligne_S19[16];

  /*Numéro de ligne du fichier listing*/
  int ligne_listing=1;

  /*------------------------------*/
  /* Gestion des options	  */
  /*------------------------------*/
  /*Mode par default*/
  strcpy(fic_asm,"exemple.asm");
  RemplirTableMnemoniques("TableMnemoniques.txt",TabMne);

  if(argc>=2){
    if(strcmp(argv[1],"-def")==0) def=1;
    if(strcmp(argv[1],"-ac")==0) aff=1;
    if(strcmp(argv[1],"-adm")==0) affad=1;
    if(strcmp(argv[1],"-adc")==0) affac=1;
    if(argc>=3){
	if(strcmp(argv[2],"-def")==0) def=1;
	if(strcmp(argv[2],"-ac")==0) aff=1;
	if(strcmp(argv[2],"-adm")==0) affad=1;
	if(strcmp(argv[2],"-adc")==0) affac=1;
	if(argc>=4){
	   if(strcmp(argv[3],"-def")==0) def=1;
	   if(strcmp(argv[3],"-ac")==0) aff=1;
	   if(strcmp(argv[3],"-adm")==0) affad=1;
	   if(strcmp(argv[3],"-adc")==0) affac=1;
	   if(argc>=5){
		if(strcmp(argv[4],"-def")==0) def=1;
	 	if(strcmp(argv[4],"-ac")==0) aff=1;
		if(strcmp(argv[4],"-adm")==0) affad=1;
	   	if(strcmp(argv[4],"-adc")==0) affac=1;}}}}

  if(def!=1){		
  /*----------------------------------------------*/
  /* Saisie du nom physique du fichier texte      */
  /*----------------------------------------------*/
  printf("-----------------------------------------------------------------------\n");
  printf("Entrez le nom du fichier a analyser avec son extension (.txt):\n");
  scanf("%s",fic_txt);
  RemplirTableMnemoniques (fic_txt,TabMne);
  printf("%s charge en memoire\n",fic_txt);
  printf("-----------------------------------------------------------------------\n");

  /*----------------------------------------------*/
  /* Saisie du nom physique du fichier assembleur */
  /*----------------------------------------------*/
  printf("Entrez le nom du fichier a analyser avec son extension (.asm):\n");
  scanf("%s",fic_asm);
  printf("-----------------------------------------------------------------------\n\n");}

  /*-------------------------------------------------*/
  /* Ouverture du fichier assembleur en mode Lecture */
  /*-------------------------------------------------*/
  fic_log_asm = fopen(fic_asm, "rt");
  if (fic_log_asm == NULL){
	perror("Erreur ouverture fichier");
	exit(1);}

  /*-----------------------------------------------*/
  /* Creation du fichier S19 et du fichier listing */
  /*-----------------------------------------------*/
  fic_s19=Creation_S19(fic_asm,S19);
  fic_lst=Creation_listing(fic_asm,lst);

  /*------------------------------------------------------------------------*/
  /* Lecture du fichier assembleur ligne par ligne : Gestion des Labels EQU */
  /*------------------------------------------------------------------------*/
  while(!feof(fic_log_asm))
  {
    /* EXTRACTION de la ligne du fichier asm*/
    fgets(ligne, 80, fic_log_asm);

    /* EXTRACTION des champs LABEL, OPERATION, OPERANDS et COMMENT d'une ligne assembleur */
    tlg = Extraction_Fields(ligne, &LabelField, &OperationField, &OperandsField, &CommentField);

    if (tlg==LIGNE_REMPLIE){	
	/*Determination du type d'opération*/
	top=Determination_Type_OP(OperationField,TabMne);
	
	/*Actualisation de la table des labels*/
	if(top==DIRECTIVE && strcmp(OperationField.string_value,"EQU")==0)
	   	Remplir_Table_Labels(OperandsField,LabelField,&compteur_label,labels);
    }
  }
  
  /*Repositionement du pointeur au début du fichier*/
  rewind(fic_log_asm);

  /*------------------------------------------------------------------------*/
  /* Lecture du fichier assembleur ligne par ligne : Gestion des Labels ORG */
  /*------------------------------------------------------------------------*/
  while(!feof(fic_log_asm))
  {
    /* EXTRACTION de la ligne du fichier asm*/
    fgets(ligne, 80, fic_log_asm);

    /* EXTRACTION des champs LABEL, OPERATION, OPERANDS et COMMENT d'une ligne assembleur */
    tlg = Extraction_Fields(ligne, &LabelField, &OperationField, &OperandsField, &CommentField);

    if (tlg==LIGNE_REMPLIE){
	/*Determination du type d'opération*/
	top=Determination_Type_OP(OperationField,TabMne);

	/*Actualisation du compteur_assemblage*/
	if(top==DIRECTIVE && strcmp(OperationField.string_value,"ORG")==0)
		Compteur_Assembalge(OperandsField,&compteur_assemblage,labels);

	if(top==MNEMONIQUE){
		/*Actualisation de la table des labels d'adressage*/
		Remplir_Table_Labels_Adresse(LabelField,compteur_assemblage,&compteur_label,labels);
		/*Calcul de la taille de l'operation*/		
		admode=Mode_Adressage(OperationField,TabMne,labels);
	    	code_op=Definition_Codage_Instruction(OperationField.string_value,&admode,TabMne);
	    	compteur_assemblage=compteur_assemblage+code_op.nboctets;}
    }
  }		
  
  /*Repositionement du pointeur au début du fichier*/
  rewind(fic_log_asm);
  compteur_assemblage=0;
  admode=INDEFINI;

  /*-----------------------------------------------*/
  /* Lecture du fichier assembleur ligne par ligne */
  /*-----------------------------------------------*/
  while(!feof(fic_log_asm))
  {
    /* EXTRACTION de la ligne du fichier asm*/
    fgets(ligne,80,fic_log_asm);

    /* EXTRACTION des champs LABEL, OPERATION, OPERANDS et COMMENT d'une ligne assembleur */
    tlg = Extraction_Fields(ligne, &LabelField, &OperationField, &OperandsField, &CommentField);

    if (tlg == LIGNE_REMPLIE){

	/*Determination du type d'opération*/
	top=Determination_Type_OP(OperationField,TabMne);

	/* Gestion des ORG + Lables pour fichier listing*/
	if(top==DIRECTIVE){
		/*Ecriture fichier listing*/
		Ecriture_Ligne_listing_directives(ligne_listing,OperandsField,labels,fic_lst,lst);
	 	if(strcmp(OperationField.string_value,"ORG")==0){
		    if(compteur_assemblage_S19!=0)
			/*Ecriture fichier s19*/
			Ecriture_Ligne_S19 (ligne_S19,&compteur_S19,&compteur_assemblage_S19,fic_s19,S19);
			/*Actualisation du compteur_assemblage*/		
			Compteur_Assembalge(OperandsField,&compteur_assemblage,labels);
			compteur_assemblage_S19=compteur_assemblage;}}	

	/*Gestion du mode d'adressage */
	if(top==MNEMONIQUE)		
		admode=Mode_Adressage(OperationField,TabMne,labels);

	/*Afficahge Détaillé*/
	if(aff==1){
		int l;
		l=strlen(OperandsField.string_value);
		printf("%s\t%s\t%s\t",LabelField.string_value,OperationField.string_value,OperandsField.string_value);
		if(l<8) printf("\t");}

	/*RECHERCHE CODE OP CORRESPONDANT*/
	if(top==MNEMONIQUE){	
		code_op=Definition_Codage_Instruction(OperationField.string_value,&admode,TabMne);
		Gestion_Code_Machine(code_op,OperandsField,&compteur_assemblage,labels,&mcode);
		/*Ecriture fichier s19*/
		Code_S19_Mnemonique(mcode,&compteur_assemblage_S19,&compteur_S19,ligne_S19,fic_s19,S19);
 		/*Ecriture fichier listing*/
		Ecriture_Ligne_listing_mcode(ligne_listing,mcode,code_op,fic_lst,lst);}

   }

      /*------------------------*/
      /* Gestion de l'affichage */
      /*------------------------*/
      if(aff==1 && top==MNEMONIQUE){
	Affichage_Code_Machine(mcode);
        if(mcode.nbdata+mcode.nbopcodes<3) 
	      printf("\t");}
	
      /*Afficahge Détaillé Mode Adressage*/
      if(aff==1 && affad==1 && admode!=INDEFINI)
        printf("\tadmode: %s",StringMode_Adressage(admode));

      /*Affichage Détaillé Code Machine*/
      if(aff==1 && affac==1 && top==MNEMONIQUE){
        if(code_op.nbdata>=1){
	  printf("\tcode: %s",StringCodeNotation(code_op.data1));
	  if(mcode.nbdata>=2){
	    printf(" %s",StringCodeNotation(code_op.data2));
	    if(mcode.nbdata>=3){
	      printf(" %s",StringCodeNotation(code_op.data3));
	      if(mcode.nbdata>=4){
	        printf(" %s",StringCodeNotation(code_op.data4));
	        if(mcode.nbdata==5)
	          printf(" %s",StringCodeNotation(code_op.data5));}}}}}

      /*Finalisation Affichage Détaillé*/
      if(aff==1){ top=DIRECTIVE; code_op.nbdata=0; printf("\n");}

      /*Ecriture fichier listing*/
      if (tlg!=LIGNE_REMPLIE)
	   Ecriture_Ligne_vide_listing(ligne_listing,fic_lst,lst);
      Ecriture_Ligne_asm_listing (ligne,fic_lst,lst);
      ligne_listing++;

      admode=INDEFINI;
  }  

  /*-----------------------------*/
  /* Finalisation du fichier S19 */
  /*-----------------------------*/
  if(compteur_S19!=0)
	  Ecriture_Ligne_S19 (ligne_S19,&compteur_S19,&compteur_assemblage_S19,fic_s19,S19);
  Finalisation_S19(fic_s19,S19);

  printf("%s vient d'être créé\n",fic_s19);
  printf("-----------------------------------------------------------------------\n");
  printf("%s vient d'être créé\n",fic_lst);
  printf("-----------------------------------------------------------------------\n");

  /*--------------------------*/
  /* Fermeture du fichier asm */
  /*--------------------------*/
  fclose(fic_log_asm);

  return 0;
}

