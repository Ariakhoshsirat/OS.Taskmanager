

#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
typedef struct
    {
    char name[20];
	int id;
	char line[50];
	int arrival;
	int burst;
	int start;
	int rem;
	int wait;
	int finish;
	int turnaround;
	float ratio;
	int flag;
    } proces;
 int aindex=0;
//process SJN(process process[50]);
void removefirstp(proces process[10]);
int SRTN(proces process[10],int timer);
main(){
    proces process[10];
    char *tmp;
    FILE *f;
   char *linesplit;
   char * array[100];
   int timer = 0;
   char *ttok;
   char arrayelem[50];
   tmp = (char *) malloc(50);
   f = fopen("C:\\users\\aria\\Desktop\\a.txt","r");
  // fgets(tmp,50,f);


    int i ;
 //  fclose(f);
 //  printf("%s \n",tmp);


    while(fgets(tmp,50,f) != NULL){

         array[aindex]= tmp;
         tmp = (char *) malloc(50);
         aindex++;


	}

//	printf("%d",aindex);
    fclose(f);
  // linesplit = strtok (tmp," \n");

   int cpuburst;
   int cpubursttotal = 0;
   int counter = 0 ;



  while(counter < aindex){

    strcpy(arrayelem,array[counter]);
    linesplit = strtok (arrayelem," \n");
    int time = 0;



   for (i=0; linesplit[i]!='\0';i++ ){
       time = (linesplit[i]-'0') + (time*10);
	}

   process[counter].arrival = time;

   linesplit = strtok (NULL," \n");
   strcpy(process[counter].name,linesplit);
   linesplit = strtok (NULL,"");

   strcpy(process[counter].line,linesplit);
   char processLine[50];
   strcpy(processLine,process[counter].line);
   linesplit = strtok (processLine," \n");


   int cpuburst;
   int cpubursttotal = 0;


   while(linesplit !=NULL){
       if(linesplit[0]=='c'){
			   cpuburst = 0;
			for (i=1; linesplit[i]!='\0';i++ ){
		      	 cpuburst = (linesplit[i]-'0') + (cpuburst*10);
	  		}
			   cpubursttotal += cpuburst;
			}
        linesplit = strtok (NULL," \n");
   }
   process[counter].burst = cpubursttotal;
   process[counter].rem = process[counter].burst;
   counter++;
  }


   while (timer!=10){

       timer++;

    if ((SRTN(process,timer))==1){
         for(i=0;i<aindex;i++){
               printf("%d\t",process[i].arrival);
               printf("%s\t",process[i].name);
               printf("%d\n",process[i].burst);
               printf("%s\t",process[i].line);
               printf("\n");
                }
    }
        }



  }








int SRTN(proces process[10],int timer){

	int i, j, k, time = 0, n=2;
	proces temp;

	for(i = 0; i <= n; i++)
	{
		for(j = i + 1; j <= n; j++)
		{
			if(process[i].arrival > process[j].arrival)
			{
				temp = process[i];
				process[i] = process[j];
				process[j] = temp;
			}
		}
	}
    int flag = 0;
	//no = 0;
	j = 1;
	//process[0].start = process[0].arrival;
    time = 0;
 //   int index = 0;
    int x;
    for(x = 0; process[x].arrival <= timer; x++);



            for(i = 0; i <= x-1; i++){
                for(j = i + 1; j <= x-1; j++)
                {
                    if(process[i].rem > process[j].rem)
                    {
                    temp = process[i];
                    process[i] = process[j];
                    process[j] = temp;
                    if(timer == process[i].arrival)
                        flag = 1;

                    }
                }


            }
    if(flag == 0)
        return 0;
    if(flag == 1)
        return 1;



            }

















