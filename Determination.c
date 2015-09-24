TYPE_OPERATION Determination_Type_OP (TYPE_VAL_FIELD operation_field, struct oper *TabMne)
{    
 	switch case(operation_field.type_field){
		case LABEL_FIELD :
			printf("LABEL_FIELD: %s\n",operation_field.string_value);
			return(EMPTY_OPERATION);
		break;
		case OPERATION_FIELD :
			printf("OPERATION_FIELD: %s\n",operation_field.string_value);
			return(MNEMONIQUE);			
		break;
		case OPERANDS_FIELD :
			printf("OPERANDS_FIELD: %s\n",operation_field.string_value);
			return(MNEMONIQUE);			
		break;
		/*case COMMENT_FIELD :

		break;
		case EMPTY_FIELD :

		break;*/
		default:
			return (ERROR_OPERATION);
		break;}
}


/*typedef struct {
  TYPE_FIELD  type_field; 
      char *string_value;     
     } TYPE_VAL_FIELD;

/*typedef enum	{
  DIRECTIVE,
  MNEMONIQUE,
  EMPTY_OPERATION,
  ERROR_OPERATION
		} TYPE_OPERATION;*/
