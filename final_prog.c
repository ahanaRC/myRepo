#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>

void token_next(int state,char buf[],char KEYWORD[10][10]);          //declaring the functions globally 
int r_start();
FILE  *fp;                                                           //declaring the file pointer
char  tmp[20];
int i,k,start=0,no_id=0,no_kwd=0,no_op=0,no_sym=0;                            //declaring the variables globally

int main()
{
	int state=0;
        
        
        char KEYWORD[10][10]={"suru","shesh","jodi","othoba","shankya","borno","lekho","poro","jokhn","koro"}; //declaration of variables
        char ch,fname[50],buffer[5000],buf[5000];                                                               // taking the file name as input
        printf("Enter the input file name=>\n");                                                              
               gets(fname);
	    if((fp=fopen(fname,"r"))==NULL)                                                                        //checking whether the contents of file is NULL or not
	           printf("\nERROR \n");
        else                                                                                                    //if not NULL then lexical analysis of the program done
        {
            printf("\n\n\n\t*************** :LEXICAL ANALYSIS: ***************\n\n\n\n");
	     	while(!feof(fp))                                                                                  //analysis done until the EOF
	     	//while(gets(buf))
	    	{
               
                              start=0;
                              i=0;k=0;
                              state=0;
	                          fscanf(fp," %s",&buffer);                                                // reading the contents of file in buffer 
	                          token_next(state,buffer,KEYWORD);                                        //passing arguments to the func token_next
            }
             printf("\n\n\t*********************************\n\n");                                    //printing the output
             printf("\tNUMBER OF KEYWORDS => %d\n", no_kwd);
             printf("\tNUMBER OF IDENTIFIERS => %d\n", no_id);
             printf("\tNUMBER OF OPERATORS => %d\n", no_op);
             printf("\tNUMBER OF SYMBOLS => %d\n", no_sym);
             printf("\n\t*********************************\n");
      }
         getch();
        return 0;
}
 
int r_start()
{
           switch(start)                                                //using switch case to change the states 
	  {
               case 0:                                                  //case 0 used for checking blank spaces ,new line ,operators
                           k=0;
                           start =11;                                    //changing the state from 0 to 11
                           break;
               case 11:                                                  //case 11 used for checking the keywords and identifiers                          
                           start=14;                                     //changing the state from 11 to 14                       
                           break;
		       case 14:
       	                   start=0;                                      //case 14 used for checking the constants
                           break;
	}
	return start;
}

void token_next( int state,char buf[],char KEYWORD[10][10])
{
         char ch;                                          //declaring the variables
         int flag;
        while(buf[i]!='\0' && buf[i]!=';')                 // loop until ';' is found which marks the end of program
         {    	
                	flag=0;
 			        switch(state)                          //swich case used to change the states
         {
             case 0:                                       //checking for blank space ,tabs ,new line operators
                  ch=buf[i];                             
                if(ch==' ' || ch=='\t' ||ch=='\n')
                {
                      state=0;
                      i++;
                }
               else if(ch=='.')
                     state=1;
                else if(ch=='[')
                     state=2;
               else if(ch==']')
                     state=3;
               else if(ch==',')
                     state=4;
               else if(ch=='=')
                     state=5;
               else if(ch=='<')
                     state=6;
               else if(ch=='>')
                     state=7;
               else if(ch=='+')
                    state=8;
                else if(ch=='-')
                    state=9;
                else if(ch=='*')
                    state=10;
                else if(ch=='/')
                    state=55;
               
		else
                state=r_start();                          //if not found then restart the state
                break;
      case 1:
                printf("\tSYMBOL:   { . }\n");         //if operator found then printing the corresponding operators    
                i++;
                no_sym++;                                   //counting the no. of symbols
                 state=0;
               break;
      case 2:
                printf("\tSYMBOL:   {  [  } \n");
                i++;
                no_sym++;
                state=0;
                break;

	  case 3:     
                 printf("\tSYMBOL:   {  ] }\n");
                 i++;
                 no_sym++;
                 state=0;
                 break;
      case 4:
                 printf("\tSYMBOL:    { , }\n");
                 i++;
                 no_sym++;
                 state=0;
                 break;
   
     
     
       case 5:
                ch=buf[++i];
                if(ch=='=')
                {
                     printf("\tRELATIONAL OPERATOR: { == }\n");
                     state=0;
                     no_op++;                                                  //counting the no. of operators
                     i++;
                }
                else 
                {
                      printf("\tASSIGNMENT OPERATOR: { = }\n");
                      state=0;
                       no_op++;
                      i++;
                }
                      
                 break;                     
    

     case 6:
                ch=buf[++i];
                if(ch=='=')
                {
                 printf("\tRELATIONAL OPERATOR:  { >= }\n");
                  no_op++;
                 state=0;
                 i++;
                }
                else
                {
                    printf("\tRELATIONAL OPERATOR:  { >  }\n");
                    state=0;
                     no_op++;
                    i++;
                }
               break;                 
                
    case 7:
                ch=buf[++i];
                if(ch=='=')
                {
                 printf("\tRELATIONAL OPERATOR:  { <= }\n");
                 state=0;
                 no_op++;
                 i++;
                }
                else
                {
                    printf("\tRELATIONAL OPERATOR:  { < }\n");
                    state=0;
                    no_op++;
                    i++;
                }
               break;
 
       case 8:
                 printf("\tARITHMETIC OPERATOR: { + }\n");
                 i++;
                 no_op++;
                 state=0;
                 break;
       case 9 :
                 printf("\tARITHMETIC OPERATOR:  { - }\n");
                 i++;
                 no_op++;
                 state=0;
                 break;
       case 10:
                  printf("\tARITHMETIC OPERATOR:  { * }\n");
                  i++;
                  no_op++;
                  state=0;
                  break;
         
   
   
       case 55:
                 
		         printf("\tARITHMETIC OPERATOR:{ / }\n");
                 i++;
                  no_op++;
                 state=0;
                 break;
   
       case 11:                                                      //checking for keywords and identifiers
                k=0;
                ch=buf[i];
                if(isalpha(ch))
                {
                     if(ch=='s')                                  //checking for keywords 'suru' ,'shesh' & 'shonkha' 
			        {                       
                         state=17;
                         tmp[k]=ch;
                         k++;
                     }
                     else if(ch=='j')                              //checking for keywords 'jodi' & 'jokhn' .
                    {
                         state=28;
                        tmp[k]=ch;
                     k++;
                    }

                    else if(ch=='o')                              //checking for keyword 'othoba'   
                   {
                         state=33;
                    tmp[k]=ch;
                      k++;
                    }

                  else if(ch=='b')                               //checking for keyword 'borno'   
                  {
                        state=44;
                       tmp[k]=ch;
			           k++ ;   
                   }
                   else if(ch=='l')                            //checking for keyword 'lekho'
                   {
                         state=48;
			             tmp[k]=ch;
                         k++;
                    }
                    else if(ch=='p')                            //checking for keyword 'poro'
                    {
                         state=38;
			             tmp[k]=ch;
                         k++;
                    }
                    else if(ch=='k')                               //checking for keyword 'koro'
                   {
                       state=41;
                       tmp[k]=ch;
                      k++;
                   }
                  else                                            //if keyword not found then checking for identifier 
                   {
						tmp[k]=ch;
						state=12;i--;
					}
				}
                    else                                            //if keyword & identifier not found then restart the state 
                      state=r_start();
                     break;

       case 12:                                                   //checking for identifiers.
				ch=buf[++i];
				if(isalpha(ch) || isdigit(ch))
				{
					state=12;
					tmp[k]=ch;
					k++;
				}
				else
				{
					i--;
					state=13;
				}
				break;
           
       case 13:
                   tmp[k]='\0';
                   printf("\tIDENTIFIER:{ %s }\n",tmp);   //printing the identifiers
                   state=0;
                   no_id++;                           //counting the no. of IDENTIFIERS
                   i++;
                     break;

       case 14:                                     //checking for constants
                 k=0;
                 ch=buf[i];
              if(isdigit(ch))
              {
                   tmp[k]=ch;
                    k++;
                     state=15;
                }
                 else
                    state=r_start();
                 break;
            case 15:
                 ch=buf[++i];
                if(isdigit(ch))
               {
                    state=15;
                    tmp[k]=ch;
                    k++;
                }
                	else
				{	
					i--;
					state=16;
				}
                
		             break;
   	      case 16:
				tmp[k]='\0';
				k=0;
				printf("\tCONSTANT:{ %s }\n",tmp);          //printing the constants.
				state=0;
				i++;
				break;
          case 17:
                ch=buf[++i];                         //checking for suru
                if(ch=='u')
                {
                    state=18;
		            tmp[k]=ch;
                    k++;
                }
                else if(ch=='h')                   //checking for shesh
                {
                    state=19;
                    tmp[k]=ch;
                    k++;
                }   
                else                                //if not printing as identifier
                {
                   i--;
                    state=12;
                }
                   break;

          case 18:
                    ch=buf[++i];
                   if(ch=='r')                         //checking for suru
                   {
                     tmp[k]=ch;
                     k++;
                    state=22;
                  }
                  else                               //if not checkng for identifier
                  {
                    i--;
                    state=12;
                 }
                 break;
          case 19:                                    //checking for shesh
                 ch=buf[++i];
                 if(ch=='e')
                {
                    state=20;
                    tmp[k]=ch;
                    k++;
                }
                else if(ch=='o')                    //checking for shankya
                {
                    state=24;
                    tmp[k]=ch;
                    k++;
                }
                else                              //if not then checking for identifier
                {
                     i--;
			       state=12;
                }
                break;
          case 20:                           //checking for shesh
              ch=buf[++i];
               if(ch=='s')
               {
                    tmp[k]=ch;
                    k++;
                   state=21;
               }
                else                          //if not printng as identifier
               {
                   i--;
                    state=12;
                }
                break;

         case 21:
                ch=buf[++i];
                if(ch=='h')
               {
                   printf("\tKEYWORD: { shesh }\n");          //checking for shesh
                   i++;
                    no_kwd++;
                   state=0;
               }
               else                                          //if not printing as identifier 
                {
                     i--;
                     state=12;
                }
               break;
         case 22:
               ch=buf[++i];
              if(ch=='u')
              {
                   printf("\tKEYWORD: { suru }\n");           // printing the found keyword suru
                   i++;
                   no_kwd++;
                   state=0;
              }
              else                                               //check for identifier
              {
                  i--;
                  state=12;
               }
               break;
            
         case 24:
                 ch=buf[++i];
                if(ch=='n')
                {
                     state=25;
                    tmp[k]=ch;
                   	k++;
                }
                 else
                {
                    i--;
                state=12;
              }
             break;
         case 25:
                ch=buf[++i];
                 if(ch=='k')
                 {
                   tmp[k]=ch;
                   k++;
                   state=26;
                }
                else
                {
                    i--;
                    state=12;
                }
                break;
         case 26:
                ch=buf[++i];
                 if(ch=='h')
                 {
                    tmp[k]=ch;
                    k++;
                     state=27;
                 }
              else
              {
                   i--;
                     state=12;
            }
              break;
         case 27:
               ch=buf[++i];
		       if(ch=='a')
               {
                     printf("\tKEYWORD: { shonkha }\n");            //shankya keyword found and printed
                     i++;
                     no_kwd++; 
                     state=0;
               }
               else                                         //else checking for identifier
                {
                    i--;
                 state=12;
		        }
               break;
           
          case 28:
                 ch=buf[++i];
                 if(ch=='o')
                 {
                    tmp[k]=ch;
                    k++;
                    state=29;
                 }
               else
                 {
                    i--;
                    state=12;
                 }
                break;
         case 29:
                  ch=buf[++i];
                if(ch=='k')
                {
                   tmp[k]=ch;
                   k++; 
   	               state=30;
                }
                 else if(ch=='d')
                 {
                     state=32;
                    tmp[k]=ch;
                    k++;
                }
              else
             {
                   i--;
                   state=12;
                 }
                 break;
          case 30:
               ch=buf[++i];
               if(ch=='h')
              {
                  tmp[k]=ch;
                  k++;
                  state=31;
               }
               else
                {
                   i--;
                    state=12;
               }
                 break;

          case 31:
                  ch=buf[++i];
              if(ch=='n')
                {
                     printf("\tKEYWORD: { jokhn }\n");              //keyword jokhn found and printed
                     i++;
                     no_kwd++;                                       //printing the no. of keywords
                     state=0;
                }
                 else
		         {
                   i--;
                   state=12;
               }
                break;

          case 32:
                 ch=buf[++i];
                 if(ch=='i')
                {
                    printf("\tKEYWORD:{ jodi }\n");              //keyword jodi found and printed    
                    i++;
                    no_kwd++;
                    state=0;
               }
                else                                            //else checking for identifier 
                {
                    i--;
                   state=12;
                }
                 break;
          
          case 33:
                ch=buf[++i];
                 if(ch=='t')
                {
                     state=34;
                    tmp[k]=ch;
                    k++;
                }
                else
                {
                   i--;
                     state=12;
                }
                break;
          case 34:
                 ch=buf[++i];
                 if(ch=='h')
               {
                     state=35;
                    tmp[k]=ch;
                    k++;
                 }
                 else
                 {
                     i--;
                    state=12;
                 }
                 break;
          case 35:
                ch=buf[++i];
               if(ch=='o')
               {
                    tmp[k]=ch;
                     k++;
                    state=36;
               }
                else
		        {
                    i--;
                    state=12;
                 }
                break;
          case 36:
                ch=buf[++i];
                if(ch=='b')
                 {
                    state=37;
                    tmp[k]=ch;
                     k++;
              }
                 else
               {
                    i--;
                 state=12;
                }
                break;
         case 37:
                     ch=buf[++i];
                if(ch=='a')
               {
                  printf("\tKEYWORD:{ othoba }\n");           //printing the keyword othoba 
                  i++;
                  no_kwd++;                                   //counting the no. of keywords
                  state=0;
              }
               else                                             //else check for identifier
                {
                     i--;
                  state=12;
                }
               break;
        

         case 38:
                     ch=buf[++i];
               if(ch=='o')
              {
                 state=39;
                   tmp[k]=ch;
                   k++;
             }
                 else
                {
                     i--;
                    state=12;
               }
                break;
         case 39:
                     ch=buf[++i];
                 if(ch=='r')
               {
                    state=40;
                   tmp[k]=ch;
                     k++;
              }
                 else
                 {
                   i--;
                     state=12;
               }
                break;
         case 40:
             ch=buf[++i];
             if(ch=='o')
                {
                    printf("\tKEYWORD:{ poro }\n");                   //printing the keyword poro
                    i++;
                    no_kwd++;
                    state=0;
                }
                 else                                                 //else check for identifiers
                {
                    i--;
                    state=12;
                }
                break;
           
         case 41:
                 ch=buf[++i];
                 if(ch=='o')
                {
                    state=42;
                   tmp[k]=ch;
                     k++;
               }
               else
               {
                     i--;
                     state=12;
               }
                break;
          case 42:
                 ch=buf[++i];
                 if(ch=='r')
               {
                    state=43;
                   tmp[k]=ch;
                     k++;
              }
                 else
                 {
                      i--;
                     state=12;
               }
                break;

         case 43:
                  ch=buf[++i];
                 if(ch=='o')
                {
                    printf("\tKEYWORD:{ koro }\n");                 //printing the keyword koro
                    i++;
                    no_kwd++;
                    state=0;
                }
                else                                               //else check for identifiers
                {
                   i--;
                     state=12;
                }
                break;

      
       case 44:
                ch=buf[++i];
                 if(ch=='o')
               {
                   state=45;
                   tmp[k]=ch;
                   k++;
              }
                 else
                 {
                     i--;
                     state=12;
                }
                break;
      case 45:
              ch=buf[++i];
                 if(ch=='r')
               {
                    state=46;
                   tmp[k]=ch;
                     k++;
              }
                 else
                 {
                   i--;
                     state=12;
               }
                break;
       case 46:
               ch=buf[++i];
                 if(ch=='n')
               {
                    state=47;
                   tmp[k]=ch;
                     k++;
              }
                 else
                 {
                   i--;
                     state=12;
               }
                break;
      case 47:
                ch=buf[++i];
                 if(ch=='o')
               {
                   printf("\tKEYWORD: { borno }\n");                       //printing the keyword borno
                   i++;
                   no_kwd++;
                   state=0;
              }
                 else                                                      //else check for identifiers
                 {
                   i--;
                     state=12;
               }
                break;
       case 48:
           ch=buf[++i];
                 if(ch=='e')
               {
                    state=49;
                   tmp[k]=ch;
                     k++;
              }
                 else
                 {
                   i--;
                     state=12;
               }
                break;
           
       case 49:
           ch=buf[++i];
                 if(ch=='k')
               {
                    state=50;
                   tmp[k]=ch;
                     k++;
              }
                 else
                 {
                   i--;
                     state=12;
               }
                break;
      case 50:
          ch=buf[++i];
                 if(ch=='h')
               {
                    state=51;
                   tmp[k]=ch;
                     k++;
              }
                 else
                 {
                   i--;
                     state=12;
               }
                break;
                
      case 51:
          
            ch=buf[++i];
                 if(ch=='o')
               {
                   printf("\tKEYWORD:{ lekho }\n");                   //printing the keyword lekho
                   i++;
                   no_kwd++;
                   state=0;
              }
                 else                                               //else check for identifiers
                 {
                   i--;
                     state=12;
                }
                break;      
           
      }
  }
}




