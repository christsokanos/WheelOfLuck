
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
typedef struct troxos{ /*pedia enos kombou*/
struct troxos *next;
struct troxos *prev;
char data[40];
}tr;
typedef struct paiktis{
int sum;
}paik;

/*global*/
struct troxos *head=NULL;
struct troxos *tail=NULL;
struct troxos *ptr=NULL;
struct troxos *velos=NULL;
int count_komvous=0;
char gramma;
char array[40];
char grifos[40];
char array1[40];
char pp[40];
struct paiktis p[3];/*arxikopoio ta posa kathe paikti me 0*/
int player=0;

/*sinatisis*/
void add_in_list(char *my_data);/*dimiourgia komvon*/
int delete_list();
char *metakinisi_velous();/*metakinisi velous pano ston troxo*/
int if_is_consonant();
int if_is_vowel();
int if_gramma_exist();
int print_grifos();
int if_grifos_is_solved();
int elegxos_simfonon();
int elegxos_fonienton();
int entoles();
int poso();
int print_grifos()
{
    int i;
	for(i=0;i<strlen(array);i++)
    {
       printf("%c ",grifos[i]);
    }
    printf("\n");
	return 0;
}
void next_player()
{
    if(player==0 || player==1)
        player++;
    else
        player=0;
}
void add_in_list(char my_data[])
{

 struct troxos *tmp=NULL;
  tmp=(struct troxos *)malloc(sizeof(struct troxos));
  tmp->next=NULL;
  tmp->prev=NULL;
  strcpy(tmp->data,my_data);//antigrafei to my_data sto pedio data tou stuct os pinaka
  if(head==NULL)
  {
    head=tmp;
    ptr=head;
  }
    else
    {
    tmp->prev=ptr;
    tmp->next=head;
    head->prev=tmp;
    ptr->next=tmp;
    ptr=tmp;
    }
}
char *metakinisi_velous(int fora_velous)
{
int i=0;
int x=0;

if(count_komvous==0)
{
    velos=head;
    x=rand()%24+1;
    for(i=0;i<x;i++)
        velos=velos->next;
    printf("stin arxi to velos vrisketai sto : %s \n",velos->data);
    count_komvous++;
}
else
{

	if(fora_velous=='!')
        exit(0);

	if(fora_velous=='r' || fora_velous=='R')
	{
		x=rand()%24+1;
		for(i=0;i<x;i++)
       	 velos=velos->next;
   		printf("to velos vrisketai sto : %s\n",velos->data);
	}
	else
	{
		x=rand()%24+1;
		for(i=0;i<x;i++)
       	 velos=velos->prev;
   		printf("to velos vrisketai sto : %s\n",velos->data);
	}
}
return velos->data;
}
int exists_char_in_array(char p[],char chr)
{
    int i;
    for(i=0;i<strlen(p);i++)
    {
        if(p[i]==chr)
            return 1;
    }
    return 0;
}
int check_if_free_to_add_vowel(char basic_array[],char grifos_array[],char vowels_array[])
{
        int i;
        int sum_vowel=0;
        int sum_grifos_vowel=0;
        for(i=0;i<strlen(basic_array);i++)
        {
            if(exists_char_in_array(vowels_array,basic_array[i])==1)
                sum_vowel++;
        }
        for(i=0;i<strlen(grifos_array);i++)
        {
            if(grifos_array[i]!='_')
            {
               if(exists_char_in_array(vowels_array,grifos_array[i])==1)
                    sum_grifos_vowel++;
            }
        }
        printf("sum_vowel=%d & sum_grifos_vowel=%d\n",sum_vowel,sum_grifos_vowel);
        if(sum_vowel>sum_grifos_vowel)
            return 1;
        else
            return 0;
}
int check_if_free_to_add_consonant(char basic_array[],char grifos_array[],char vowels_array[])
{
        int i;
        int sum_conson=0;
        int sum_grifos_conson=0;
        for(i=0;i<strlen(basic_array);i++)
        {
            if(exists_char_in_array(vowels_array,basic_array[i])==0)
                sum_conson++;
        }
        for(i=0;i<strlen(grifos_array);i++)
        {
            if(grifos_array[i]!='_')
            {
                if(exists_char_in_array(vowels_array,grifos_array[i])==0)
                    sum_grifos_conson++;
            }
        }
        printf("sum_conson=%d & sum_grifos_conson=%d\n",sum_conson,sum_grifos_conson);
        if(sum_conson>sum_grifos_conson)
            return 1;
        else
            return 0;
}
void add_amount(int amount)
{
    p[player].sum+=amount;
}
int char_frequency(char p[],char c)
{
    int sum=0;
    int i;
    for(i=0;i<strlen(p);i++)
    {
        if(p[i]==c)
            sum++;
    }
    return sum;
}
void print_euros()
{
    int i;
    for(i=0;i<3;i++)
    {
        printf("Player %d has %d money\n",i+1,p[i].sum);
    }
}
int check_if_found(char l[],char r[])
{
    int i;
    int sum=0;
    for(i=0;i<strlen(l);i++)
    {
        if(l[i]==r[i])
            sum++;
    }
    if(sum==strlen(l))
        return 1;
    else
        return 0;
}
void sub_mount(int amount)
{
    if(amount==0)
        p[player].sum=0;
    else
    {
        p[player].sum-=amount;
        printf("You lost %d euros\n",amount);
    }
}
int winner()
{
    int max=-1;
    int i;
    int pos=0;
    for(i=0;i<3;i++)
    {
        if(p[i].sum>max)
        {
            max=p[i].sum;
            pos=i;
        }
    }
    return pos;
}
int main(void)
{
/////////////////////////
char vowels[]="aeuio";
int i=0;
int x=0;
char consonant;
char vowel;
int solved=0;
int giros=0;
char fora_velous;
FILE *fp;
char value[40];
char conson;
int answer;
char give_word[40];
int sum_found=0;
/* otidipote epistrefetai apo thn metakinisi_velous()*/
/////////////////////////
srand(time(NULL));
add_in_list("XREOKOPIA");
add_in_list("100");
add_in_list("30");
add_in_list("40");
add_in_list("XANEIS TIN SEIRA SOU");
add_in_list("250");
add_in_list("20");
add_in_list("300");
add_in_list("XANEIS 20 euro");
add_in_list("10");
add_in_list("35");
add_in_list("30");
add_in_list("XREOKOPIA");/*antidiametriko 1hs plithos komvon/2 +1 */
add_in_list("200");
add_in_list("40");
add_in_list("10");
add_in_list("XANEIS TIN SEIRA SOU");
add_in_list("60");
add_in_list("130");
add_in_list("70");
add_in_list("XANEIS 30 euro");
add_in_list("50");
add_in_list("60");
add_in_list("120");


////////////////////////////////////////////////////////////////////////////////////////////////////////////////

for( i=0;i<3;i++)
    p[i].sum=0;


	fp=fopen("troxos.dat","r"); /*anoigma arxeiou gia diavasma*/
	if(fp==NULL)
		return 0;
	x=rand()%17;

	i=0;
	while(!feof(fp) && i<=x)
    {
        fscanf(fp,"%s\n",pp);
        i++;
    }

	strcpy(array,pp);
	printf("Array of word %s \n",array);
	for(i=0;i<strlen(array);i++)
    {
        grifos[i]='_';
    }


	fclose(fp);
    strcpy(array1,array);
    player=rand()%3;
    printf("First player of the game is the player :%d\n",player+1);


    do
        {
            print_euros();
                giros++;
                printf("**************************** ROUND %d ****************************\n\n",giros);
                printf("Plays the player:%d\n",player+1);
                printf("GRIFOS:array ->");
                print_grifos();
                printf("\n");
                do{
                        printf("Dialexe fora troxou: R(right)  or L(left)\n");
                        scanf(" %c",&fora_velous);
                  }while(fora_velous!='R' && fora_velous!='r' && fora_velous!='L' && fora_velous!='l' && fora_velous!='!');
                strcpy(value,metakinisi_velous(fora_velous));
               /* printf("1 for free space for consonants else 0 ->%d\n",check_if_free_to_add_consonant(pp,grifos,vowels));
                printf("1 for free space for vowels else 0 ->%d\n",check_if_free_to_add_vowel(pp,grifos,vowels));*/
                if(isalpha(value[0]))
                {
                    if(strcmp(value,"XREOKOPIA")==0)
                    {
                        sub_mount(0);
                        next_player();
                        continue;
                    }
                    else if(strcmp(value,"XANEIS TIN SEIRA SOU")==0)
                    {
                        next_player();
                        printf("Plays the next player\n");
                        continue;
                    }
                    else if(strcmp(value,"XANEIS 30 euro")==0)
                    {
                        if(p[player].sum<30)
                        {
                            next_player();
                            continue;
                        }
                        else
                           sub_mount(30);
                    }
                    else if(strcmp(value,"XANEIS 20 euro")==0)
                    {
                        if(p[player].sum<20)
                        {
                            next_player();
                            continue;
                        }
                        else
                        sub_mount(20);
                    }
                    print_euros();
                }
                else if(check_if_free_to_add_consonant(pp,grifos,vowels)==1)
                {
                    printf("Give 1 to add a consonant and 2 to add the whole word\n");
                    scanf("%d",&answer);
                    if(answer==2)
                    {
                        printf("Give the whole word \n");
                        scanf(" %s",give_word);
                        if(strcmp(array,give_word)==0)
                        {
                            printf("You won !!\n");
                            return 0;
                        }
                        else
                        {
                            next_player();
                            continue;
                        }
                    }
                    else
                    {
                    do
                    {
                        printf("Give a consonant!\n");
                        scanf(" %c",&conson);
                    }while(exists_char_in_array(vowels,conson)==1);

                    if(exists_char_in_array(array,conson)==1)
                    {

                        sum_found=0;

                        for(i=0;i<strlen(array);i++)
                        {
                            if(array[i]==conson)
                            {
                                grifos[i]=conson;
                                sum_found++;
                            }

                        }
                        print_grifos();
                        add_amount(atoi(value)*sum_found);
                        if(check_if_found(array,grifos)==1)
                        {
                            printf("Found!!::\n");
                            if(player==2)
                              player=0;
                            else if(player==0)
                             player=2;
                            else
                             player--;
                            printf("Winner is %d",player+1);
                            return 0;
                        }
                        if(check_if_free_to_add_vowel(pp,grifos,vowels)==1)
                        {
                            do{
                                    printf("Give 1 to add a vowel and 2 to add the whole word\n");
                                    scanf(" %d",&answer);
                            }while(answer!=1 && answer!=2);
                            if(answer==2)
                            {
                                printf("Please give the whole word !\n");
                                scanf(" %s",give_word);
                                if(strcmp(array,give_word)==0)
                                {
                                    printf("You won !!\n");
                                    printf("won the player %d\n",player+1);
                                    print_euros();
                                    return 0;
                                }
                            }
                            else
                            {
                                do
                                {
                                 printf("Give a vowel\n");
                                 scanf(" %c",&vowel);
                                }while(exists_char_in_array(vowels,vowel)==0);
                                if(exists_char_in_array(array,vowel)==1)
                                {
                                     //add_poso();

                                     sum_found=0;
                                       for(i=0;i<strlen(array);i++)
                                        {
                                            if(array[i]==vowel)
                                            {
                                                grifos[i]=vowel;
                                                sum_found++;
                                            }

                                        }
                                        print_grifos();
                                        printf("\n");
                                        add_amount(atoi(value)*sum_found);
                                        if(check_if_found(array,grifos)==1)
                                        {
                                            printf("Found!!::\n");
                                            if(player==2)
                                                player=0;
                                            else if(player==0)
                                                player=2;
                                            else
                                                player--;
                                            printf("Winner is %d",player+1);
                                            return 0;
                                        }
                                            next_player();
                                }
                                else
                                {
                                    next_player();
                                    continue;
                                }
                            }
                        }
                        else
                        {
                            printf("There are no other vowels hidden !\n");
                            printf("Give the whole word !\n");
                            scanf(" %s",give_word);
                            if(strcmp(array,give_word)==0)
                            {
                                printf("You won !\n");
                                printf("won the player %d\n",player+1);
                                print_euros();
                                return 0;
                            }
                            else
                            {
                                printf("Sorry..!\n");
                                return 0;
                            }
                        }

                    }
                    else
                    {
                        next_player();
                    }
                    }
                }
                else
                {
                                do
                                {
                                 printf("There are no other consonants free to add ! Give a vowel\n");
                                 scanf(" %c",&vowel);
                                }while(exists_char_in_array(vowels,vowel)==0);
                                if(exists_char_in_array(array,vowel)==1)
                                {
                                            print_grifos();
                                            printf("\nPlease solve it \n");
                                            scanf(" %s",give_word);
                                            if(strcmp(array,give_word)==0)
                                            {
                                                printf("You won !\n");
                                                print_euros();
                                                printf("won the player %d\n",player+1);
                                                return 0;
                                            }
                                }
                                else
                                    next_player();

                }

    }while(conson!='!' && vowel!='!' && solved==0 && check_if_found(array,grifos)==0);

    //delete_list();
    return 0;
}
//////////////////////////////////////////////////////
/*
int delete_list()
{
    struct troxos * pt;
    pt=head;
    do{
        tail=head->prev;
        pt=pt->next;
        free(head);
        head=pt;

    }while(head!=NULL);
    return 0;
}

*/
