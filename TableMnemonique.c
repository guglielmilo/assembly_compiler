void RemplirTableMnemoniques (char *fic_phy, struct oper *TabMne)
{
  char ligne[80];
  int i=0;
  FILE *fic_log_phy;

/*-------------------------------------------------*/
/* Ouverture du fichier texte en mode Lecture	   */
/*-------------------------------------------------*/
 
  fic_log_phy = fopen(fic_phy, "rt");

  if (fic_log_phy == NULL)
  {
    perror("Erreur ouverture fichier table mnemonique");
    exit(1);
  }
	
/*-----------------------------------------------*/
/* Lecture du fichier texte ligne par ligne      */
/*-----------------------------------------------*/
  
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
  fgets(ligne, 80, fic_log_phy); /* Permet de sauter la ligne en cours */
 /* printf("l:%d eof:%d => %d %d %d %08.8X %08.8X %d %d %d %d %d %d %s\n",i+1,feof(fic_log_phy),
	TabMne[i].admode,
	TabMne[i].nboctets,
	TabMne[i].nbopcodes,
	TabMne[i].opcode1,
	TabMne[i].opcode2,
	TabMne[i].nbdata,
	TabMne[i].data1,
	TabMne[i].data2,
	TabMne[i].data3,
	TabMne[i].data4,
	TabMne[i].data5,
	TabMne[i].mnemonic);*/}


/*---------------------------------*/
/* Fermeture du fichier texte      */
/*---------------------------------*/
  fclose(fic_log_phy);

}
