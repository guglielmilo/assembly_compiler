/*--------------------------------------------------------------*/
/*		   	AdMode.c				*/
/*--------------------------------------------------------------*/

#include "main.h"
#include "AdMode.h"

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
int Mode_Adressage(TYPE_VAL_FIELD OperationField,struct oper *TabMne,struct label *labels)
{
	MAILLON_OPERANDS *operands=NULL;
	Extraction_Operands(OperationField, &operands); /*Liste chainée des caratères des opérandes*/
	if(operands==NULL)
		return INH; /*Adressage Inhérent:aucune opérande*/
	long val;
	switch (operands->info.ul){
	  case(UL_DIESE): /*Adressage Immédiat*/
		free(operands);
		return IMM;
	  break;
	  case(UL_CRO_OUV): /*Adressage Indexé*/
		operands=operands->suivant;
		if(operands->info.string_value[0]=='D'){
			free(operands);
			return DIDX;} /*Accumulateur D*/
		else{
			free(operands);
			return IIDX2;}/*Présence d'un autre accumulateur*/
	  break;
	  case(UL_CONST): case(UL_SYMBOL): /*Tous les types de constantes et de labels*/
		if(operands->info.ul==UL_CONST)			
			val=ValueConst(operands->info); /*Extraction de tous type de constante*/
		if(operands->info.ul==UL_SYMBOL)			
			val=Parcours_Labels(operands->info.string_value,labels);		
		if((operands->suivant)==NULL){			
			if(Relative_Mode(OperationField.string_value,TabMne)==1){
			/*Recherche dans la table un adressage relatif existant*/			  
				free(operands);
				return REL;} /*Adressage Relatif*/
			else if(TientSurUnOctet(val)==1){
				free(operands);
				return DIR;} /*Adressage Direct (8bits)*/
			else{
				free(operands);
				return EXT;}}/*Adressage Etendu (16bits)*/
		else if((operands->suivant)->info.ul==UL_COMMA) /*Présence d'une virgule Adressage Indexé*/
			
			if((operands->suivant)->suivant->info.ul==UL_CONST ||
			   (operands->suivant)->suivant->info.ul==UL_SYMBOL){
				if(((operands->suivant)->suivant)->suivant==NULL)
					return EXT; /*Type CALL opear16,page */
				else if(((operands->suivant)->suivant)->suivant->info.ul==UL_COMMA){
				/*On a une deuxieme virgule*/
					if(((operands->suivant)->suivant)->suivant->suivant->suivant==NULL){
					/*On a trois paramètres*/
						if(TientSurUnOctet(val)==1){
							free(operands);
							return DIR;} 
							/*Adressage Direct (8bits)*/
						else{
							free(operands);
							return EXT;}}}}
							/*Adressage Etendu (16bits)*/
			if(val>=-8 && val<=8){
				free(operands);
				return IDX;} /*Constante entre 1 et 8*/				
			if(TientSur16Bits(val)==1){
				free(operands);
				return IDX2;} /*Constante de 16bis signés*/
			else if(TientSur9Bits(val)==1){
					free(operands);
					return IDX1;} /*Constante de 9bis signés*/
				else{
					free(operands);
					return IDX;} /*Autres cas*/	
	  break;
	  case(UL_REG_A):case(UL_REG_B):case(UL_REG_D):
		if((operands->suivant)->info.ul==UL_COMMA)
			return IDX; /*Adressage Indexé*/
	  break;
	  case(UL_REG_X):case(UL_REG_Y):case(UL_REG_SP): 
		if((operands->suivant)->info.ul==UL_COMMA || operands->suivant==NULL)		
			return IDX; /*Adressage Indexé*/
	  break;
	  case(UL_REG_PC):
		if(operands->suivant==NULL)
			return IDX; /*Adressage Indexé*/
	  break;
	  default : return INDEFINI;
	  break;}
	return INDEFINI;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
int Relative_Mode(char *mne,struct oper *TabMne)
{
	int i;
	for (i=0;i<TAILLE_TABLE_MNEMONIQUES;i++){		
		if(TabMne[i].admode==4)
			if(strcmp(mne,TabMne[i].mnemonic)==0)
				return 1;}
	return 0;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
struct oper Definition_Codage_Instruction(char *mne,int *admode,struct oper *TabMne)
{
	int i;
	for (i=0;i<TAILLE_TABLE_MNEMONIQUES;i++){
		if(strcmp(mne,TabMne[i].mnemonic)==0)
			if(TabMne[i].admode==*admode)
				return TabMne[i];}
	/*Ex:cas de LSL*/
	*admode=EXT;
	for (i=0;i<TAILLE_TABLE_MNEMONIQUES;i++){
		if(strcmp(mne,TabMne[i].mnemonic)==0)
			if(TabMne[i].admode==*admode)
				return TabMne[i];}
	/*Ex:cas de DBNE (lb)*/
	*admode=REL;
	for (i=0;i<TAILLE_TABLE_MNEMONIQUES;i++){
		if(strcmp(mne,TabMne[i].mnemonic)==0)
			if(TabMne[i].admode==*admode)
				return TabMne[i];}
	struct oper err;
	err.admode=CODE_ERROR;
	printf("\nAttention! Code machine introuvable:%s\n",mne);	
	return err;
}

/*--------------------------------------------------------------------------*/
/*--------------------------------------------------------------------------*/
long Codage_Operandes(int data,TYPE_VAL_FIELD OperandsField,int pc,struct label *labels)
{
	/*Ici pc vaut l'adresse de l'octet qui est calculé dans ce prg*/
	long code=0;	
	MAILLON_OPERANDS *operands=NULL;
	Extraction_Operands(OperandsField, &operands); /*Liste chainée des caratères des opérandes*/
	if(operands==NULL)
		return CODE_ERROR;
	switch(data){
		case(ii): /*Valeur immédiate de 8 bits*/
			if(operands->info.ul==UL_DIESE){ /*Verification de la présence du #*/
				if((operands->suivant)->info.ul==UL_CONST)
					code=ValueConst((operands->suivant)->info)&0x000000FF;
				if((operands->suivant)->info.ul==UL_SYMBOL)
					code=Parcours_Labels((operands->suivant)->info.string_value,labels)&0x000000FF;}
		break;
		case(dd): /*Adressage direct de 8 bits*/
			if(operands->info.ul==UL_CONST)
				code=ValueConst(operands->info);
			if(operands->info.ul==UL_SYMBOL)
				code=Parcours_Labels(operands->info.string_value,labels);
		break;
		case(hh): /*Octet de poids fort pour une opérande de 16bits*/
			if(operands->info.ul==UL_CONST)
				code=OctetHaut(ValueConst(operands->info)); /*poids fort*/
			if(operands->info.ul==UL_SYMBOL)
				code=OctetHaut(Parcours_Labels(operands->info.string_value,labels));
		break;
		case(qq):
			if(operands->info.ul==UL_CONST)
				code=OctetHaut(((signed)(ValueConst(operands->info)-pc))&0x0000FF00);
			if(operands->info.ul==UL_SYMBOL)
				code=OctetHaut(((signed)(Parcours_Labels(operands->info.string_value,labels)-pc))
				&0x0000FF00);		
		break;
		case(ll):/*Octet de poids faible pour une opérande de 16 bits*/
			if(operands->info.ul==UL_CONST)
					code=OctetBas(ValueConst(operands->info)); /*poids faible*/
			if(operands->info.ul==UL_SYMBOL)
				code=OctetBas(Parcours_Labels(operands->info.string_value,labels));	
		break;
		case(rr): /*Octet de poids faible pour un déplacement de 16 bits*/	 	
			if(operands->info.ul==UL_CONST && operands->suivant==NULL)
				      code=((signed)(OctetBas(ValueConst(operands->info))-OctetBas(pc)-1))&0x000000FF;
			else if(operands->info.ul==UL_SYMBOL && operands->suivant==NULL)
					code=((signed)(OctetBas(Parcours_Labels(operands->info.string_value,labels))
					-OctetBas(pc)-1))&0x000000FF;
			else {	while(operands->suivant!=NULL)
					operands=operands->suivant;/*On va à la dernière opérande*/
				if(operands->info.ul==UL_CONST)
					code=((signed)(OctetBas(ValueConst(operands->info))-OctetBas(pc)-1))&0x000000FF;
				if(operands->info.ul==UL_SYMBOL)
					code=((signed)(OctetBas(Parcours_Labels(operands->info.string_value,labels))
					-OctetBas(pc)-1))&0x000000FF;}				
		break;
		case(xb):
		/*Accumulator offset*/		
		if((operands->suivant)->info.ul==UL_COMMA){
		/*Présence d'une virgule en 2eme*/

			/*Constant offset*/
			if(TientSur9Bits(ValueConst(operands->info))==1){
				code=0xE0;
				if(ValueConst(operands->info)<0)
					code=code+1;
				switch((operands->suivant)->suivant->info.ul){
				case(UL_REG_X): code=code+0;break;
				case(UL_REG_Y): code=code+0x8;break;
				case(UL_REG_SP): code=code+0x10;break;
				case(UL_REG_PC): code=code+0x18;break;
				default: code=CODE_ERROR;break;}}

			if(TientSur16Bits(ValueConst(operands->info))==1){;
				code=0xE2;
				switch((operands->suivant)->suivant->info.ul){
				case(UL_REG_X): code=code+0;break;
				case(UL_REG_Y): code=code+0x8;break;
				case(UL_REG_SP): code=code+0x10;break;
				case(UL_REG_PC): code=code+0x18;break;
				default: code=CODE_ERROR;break;}}

			/*Accumulator offset*/			
			if(operands->info.ul==UL_REG_A || operands->info.ul==UL_REG_B || 
			   operands->info.ul==UL_REG_D){
				switch(operands->info.ul){
					case(UL_REG_A):code=0;break;
					case(UL_REG_B): code=0x1;break;
					case(UL_REG_D): code=0x2;break;
					default: code=CODE_ERROR;break;}
				switch(((operands->suivant)->suivant)->info.ul){	
					case(UL_REG_X): code=code+0;break;
					case(UL_REG_Y): code=code+0x8;break;
					case(UL_REG_SP): code=code+0x10;break;
					case(UL_REG_PC): code=code+0x18;break;
					default: code=CODE_ERROR;break;}
				code=code+0xE4;}

			/*Auto in/decrementation*/			
			else if(Bits3_constant_offset(ValueConst(operands->info))==1 &&
			   ((operands->suivant)->suivant)->suivant!=NULL){

				/*PB*/
				if((operands->suivant)->suivant->info.ul==UL_DEC ||
				   (operands->suivant)->suivant->suivant->info.ul==UL_DEC){
					if(ValueConst(operands->info)<0)
						code=(((signed)(~(ValueConst(operands->info))))&0x0F)+0x20;
					else
						code=(((signed)(-(ValueConst(operands->info))))&0x0F)+0x20;}
				if((operands->suivant)->suivant->info.ul==UL_INC ||
				   (operands->suivant)->suivant->suivant->info.ul==UL_INC)
						code=((signed)(ValueConst(operands->info))&0x0F)+0x20;
				/*Pre*/
				if((operands->suivant)->suivant->info.ul==UL_DEC ||
				   (operands->suivant)->suivant->info.ul==UL_INC)
					switch((((operands->suivant)->suivant)->suivant)->info.ul){
						case(UL_REG_X): code=code+0;break;
						case(UL_REG_Y): code=code+0x40;break;
						case(UL_REG_SP): code=code+0x80;break;
						default: code=CODE_ERROR;break;}
				/*Post*/
				if((operands->suivant)->suivant->suivant->info.ul==UL_DEC ||
				   (operands->suivant)->suivant->suivant->info.ul==UL_INC){
					switch(((operands->suivant)->suivant)->info.ul){
						case(UL_REG_X): code=code+0;break;
						case(UL_REG_Y): code=code+0x40;break;
						case(UL_REG_SP): code=code+0x80;break;
						default: code=CODE_ERROR;break;}
					code=code+0x10;}}

			/*5-bit constant offset*/
			else if(Bits5_constant_offset(ValueConst(operands->info))==1){
				switch(((operands->suivant)->suivant)->info.ul){
					case(UL_REG_X): code=code+0;break;
					case(UL_REG_Y): code=code+0x40;break;
					case(UL_REG_SP): code=code+0x80;break;
					case(UL_REG_PC): code=code+0xC0;break;
					default: code=CODE_ERROR;break;}
				code=code+(ValueConst(operands->info)&0x1F);}
		}
		else if(operands->info.ul==UL_CRO_OUV){
		/*Présence d'un crochet ouvert*/

			/*Accumulator D offset*/
			if((operands->suivant)->info.ul==UL_REG_D){	
				operands=((operands->suivant)->suivant)->suivant;
				code=0xE7;					
				switch(operands->info.ul){
				case(UL_REG_X): code=code+0;break;
				case(UL_REG_Y): code=code+0x8;break;
				case(UL_REG_SP): code=code+0x10;break;
				case(UL_REG_PC): code=code+0x18;break;
				default: code=CODE_ERROR;break;}}

			/*16-bit offset indexed-indirect*/
			else{	code=0x3;
				code=code+0xE0;
				switch((((operands->suivant)->suivant)->suivant)->info.ul){
				case(UL_REG_X): code=code+0;break;
				case(UL_REG_Y): code=code+0x8;break;
				case(UL_REG_SP): code=code+0x10;break;
				case(UL_REG_PC): code=code+0x18;break;
				default: code=CODE_ERROR;break;}}

		}	
		else code=CODE_ERROR;
		break;
		case(ee): /*Octet de poids fort d'un déplacement de 16bits en IDX*/ 
			if(operands->info.ul==UL_CRO_OUV)
				operands=operands->suivant;	
			if(operands->info.ul==UL_CONST)
				code=OctetHaut(ValueConst(operands->info))&0x000000FF; /*poids fort*/
			if(operands->info.ul==UL_SYMBOL)
				code=OctetHaut(Parcours_Labels(operands->info.string_value,labels))&0x000000FF;
		break;
		case(ff): /*Octet de poids fiable d'un déplacement de 9 signés ou 16 bits en IDX*/
			if(operands->info.ul==UL_CRO_OUV)
				operands=operands->suivant;	
			if(operands->info.ul==UL_CONST)
				code=OctetBas(ValueConst(operands->info))&0x000000FF; /*poids faible*/
			if(operands->info.ul==UL_SYMBOL)
				code=OctetBas(Parcours_Labels(operands->info.string_value,labels))&0x000000FF;
		break;
		case(jj): /*Octet de poids fort d'une valeur immédiate de 16 bits*/
			if(operands->info.ul==UL_DIESE){ /*Verification de la présence du #*/
				if((operands->suivant)->info.ul==UL_CONST)
					code=OctetHaut(ValueConst((operands->suivant)->info))&0x000000FF;
				if((operands->suivant)->info.ul==UL_SYMBOL)
					code=OctetHaut(Parcours_Labels((operands->suivant)->info.string_value,labels))&0x000000FF;}
		break;
		case(kk): /*Octet de poids faible d'une valeur immédiate de 16 bits*/
			if(operands->info.ul==UL_DIESE){ /*Verification de la présence du #*/
				if((operands->suivant)->info.ul==UL_CONST)
					code=OctetBas(ValueConst((operands->suivant)->info))&0x000000FF;
				if((operands->suivant)->info.ul==UL_SYMBOL)
					code=OctetBas(Parcours_Labels((operands->suivant)->info.string_value,labels))&0x000000FF;} 
		break;
		case(mm): /*Adressage direct de 8 bits*/
			if(operands->info.ul==UL_CONST)
				if((operands->suivant)->info.ul==UL_COMMA)
				/*Verification de la présence de la virgule*/
					code=ValueConst(((operands->suivant)->suivant)->info);
			if(operands->info.ul==UL_SYMBOL)
				if((operands->suivant)->info.ul==UL_COMMA)
					code=Parcours_Labels(((operands->suivant)->suivant)->info.string_value,labels);
		break;
		case(pg): /*Numéro de page pour l'instruction CALL*/
			if(operands->info.ul==UL_CONST)
				if((operands->suivant)->info.ul==UL_COMMA)
				/*Verification de la présence de la virgule*/
					code=ValueConst(((operands->suivant)->suivant)->info);
			if(operands->info.ul==UL_SYMBOL)
				if((operands->suivant)->info.ul==UL_COMMA)
					code=Parcours_Labels(((operands->suivant)->suivant)->info.string_value,labels);
		break;
		case(lb):
		/*Accumulator offset*/		
		if((operands->suivant)->info.ul==UL_COMMA){
		/*Présence d'une virgule en 2eme*/	
			
			switch(operands->info.ul){
			case(UL_REG_A):code=0x0;break;
			case(UL_REG_B): code=0x1;break;
			case(UL_REG_D): code=0x4;break;
			case(UL_REG_X): code=0x5;break;
			case(UL_REG_Y): code=0x6;break;
			case(UL_REG_SP): code=0x7;break;
			default: code=CODE_ERROR;break;}

		   /*Extrait de rr: vérification du signe du rel9*/
		   while(operands->suivant!=NULL)
			operands=operands->suivant;
		   if(operands->info.ul==UL_CONST)
			if((ValueConst(operands->info)-pc-1)<0)
				code=code+0x10;
		   if(operands->info.ul==UL_SYMBOL)
			if((Parcours_Labels(operands->info.string_value,labels)-pc-1)<0)
				code=code+0x10;

		   /*Sélection en fonction de l'opérande*/
		   if(strcmp(OperandsField.string_value,"DBEQ")==0) code=code+0x0;
		   if(strcmp(OperandsField.string_value,"DBNE")==0) code=code+0x20;
		   if(strcmp(OperandsField.string_value,"TBEQ")==0) code=code+0x40;
		   if(strcmp(OperandsField.string_value,"TBNE")==0) code=code+0x60;
		   if(strcmp(OperandsField.string_value,"IBEQ")==0) code=code+0x80;
		   if(strcmp(OperandsField.string_value,"IBNE")==0) code=code+0xA0;	
	
		}
		break;
		case(EMPTY): default:
			return CODE_ERROR;
		break;}
	free(operands);
	return code;
}


