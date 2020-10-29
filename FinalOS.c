#include<unistd.h>
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/msg.h>

#define MAX 10

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
int SRTN(proces process[10],int timer);
int aindex =0;
int DiscHead = 0;
void SJN(proces process[10]);
void HRRN(proces process[10],int timer);
void removefirstp(proces process[10]);
int RR(proces process[10],int timer)
char [50] cpualgorithm = "SJN";
main(){
    FILE *f;

   typedef struct
    {
	int type;
	char msg[MAX];
    } mymsg;

    proces process[10];

   char * array[100];
   char name[20];
   char arrayelem[50];
    char linecopy[50];
   key_t key = 6765;
   mymsg msg_queue ;

   int realpidi = 0;
   struct msqid_ds buf;
   int msqid = msgget(key, IPC_CREAT | 0666 );
   char * realpid;
   char * msg;
   int pid = 100;
   int timer = 0;
   char *tmp;
   int i;
   char *linesplit;
   char *ttok;
   tmp = (char *) malloc(50);
   int killedornot = 0;

   f = fopen("/home/ma30/Desktop/a.txt","r");
 //  fgets(tmp,50,f);
    /////////////////////////////////////////////



  //  int i ;
 //  fclose(f);
 //  printf("%s \n",tmp);


    while(fgets(tmp,50,f) != NULL){

         array[aindex]= tmp;
         tmp = (char *) malloc(50);
         aindex++;


	}
    aindex--;
//	printf("%d",aindex);
    fclose(f);
  // linesplit = strtok (tmp," \n");

   int cpuburst;
   int cpubursttotal = 0;
   int counter = 0 ;

     char processLine[50];

  while(counter <= aindex){

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

   strcpy(processLine,process[counter].line);
  // linesplit = strtok (processLine," \n");


   int cpuburst;
   int cpubursttotal = 0;

   int x;

    for(x=0; processLine[x] != '\n';x++){
               if(processLine[x]=='c'){
			        cpuburst = 0;
			        for (i=1; processLine[x+i]>='0' && processLine[x+i]<='9' ;i++ ){
			       // printf("%c\n",processLine[x+i]);
		              	 cpuburst = (processLine[x+i]-'0') + (cpuburst*10);
	          		}

			           cpubursttotal += cpuburst;
			        }


           }
           process[counter].burst = cpubursttotal;
            process[counter].rem = process[counter].burst;
             counter++;

           }
/*
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

  }

*/
   counter = 0;

/*

    printf("%d\n",aindex);
    for(i=0;i<=aindex;i++){
        printf("%d\t",process[i].arrival);
        printf("%s\t",process[i].name);
        printf("%d\t",process[i].burst);
        printf("%s\n\n",process[i].line);
        }



*/






  // freopen ("Output.txt","w",stdout);

    while(aindex>0){


    killedornot = 0 ;


 //   SRTN(process,timer);
       /*
    printf("%d\n",aindex);
    for(i=0;i<=aindex;i++){
        printf("%d\t",process[i].arrival);
        printf("%s\t",process[i].name);
        printf("%d\t",process[i].rem);
        printf("%s\n",process[i].line);
        }


    */


 //   if( process[counter].flag ==0){







   char inputline[100];
   memset(inputline,0,sizeof(inputline));
   strcat(inputline,"./process ");
  // linesplit = strtok (NULL," ");
  // strcpy(name,linesplit);


   strcat(inputline,process[counter].name);
   strcat(inputline," ");
   char pids[4];

   process[counter].id = pid;
   sprintf(pids,"%d",pid++);

   strcat(inputline,pids);
   strcat(inputline," ");
  // linesplit = strtok (NULL,"");
   strcat(inputline,process[counter].line);
 ///////////////////////////////////////
	fflush(stdout);
	char *Args[10];
   Args[0]="/usr/bin/gnome-terminal";
   Args[1]="-e";
   Args[2]=inputline;
   Args[3]=NULL;
  // strcat(inputline,linesplit);

   pid_t fork_result ;
   fork_result = fork();
//   printf("%s", inputline);
   fflush(stdout);
   //sleep(3);
   if ( fork_result == 0 ){

	printf("Childprocess");
	execv(Args[0],Args);}

     msgrcv( msqid, &msg_queue, sizeof(msg_queue.msg)+1,0,0);

     realpid = msg_queue.msg;
     for (i=0; realpid[i]!='\0';i++ ){
	 realpidi = (realpid[i]-'0') + (realpidi*10);
	}
	process[counter].id = realpidi;


	printf("%s \t",process[counter].name);
	printf("%d \t",timer); //                               TIIIIIIIIIIMEEEEEEEEEEEEEEEEEEEEEEEEER
	kill(realpidi,SIGSTOP);
	printf("CREATE\n");
    kill(realpidi,SIGCONT);

    if( (strcmp(cpualgorithm,"SRTN"))  ) {
	printf("%s \t",process[counter].name);
	printf("%d \t",timer);
	kill(realpidi,SIGSTOP);
	printf("CPU\n");
//	kill(realpidi,SIGCONT);

	strcpy(linecopy,process[counter].line);
	ttok = strtok(linecopy," \n");
	int time;
    int ioburst;

	if(ttok[0]=='c'){
			time = 0;
			for (i=1; ttok[i]!='\0';i++ ){
			 time = (ttok[i]-'0') + (time*10);
			}
		//	timer += time;

		//	process[counter].rem = process[counter].rem - time;
			}

    for(i=0;i<time ; i++ ){
	   kill(realpidi,SIGCONT);
	   sleep(1);
	   kill(realpidi,SIGSTOP);
	   killedornot = SRTN(process,timer);

	   if(killedornot == 1){
	      timer+=2;
	      process[counter].flag = 1;
	      break;
	      }
	   process[counter].rem--;
	   timer++;
	   }

    if(killedornot == 1){
       killedornot = 0;
       continue;
       }
    }
    if( (strcmp(cpualgorithm,"SJN"))  || (strcmp(cpualgorithm,"HRRN")) ){
        kill(realpidi,SIGSTOP);
        printf("%s \t",process[counter].name);
        printf("%d \t",timer);
        printf("CPU\n");

        strcpy(linecopy,process[counter].line);
        ttok = strtok(linecopy," \n");
        int time;
        int ioburst;

        if(ttok[0]=='c'){
			time = 0;
			for (i=1; ttok[i]!='\0';i++ ){
			 time = (ttok[i]-'0') + (time*10);
			}
			timer += time;

			process[counter].rem = process[counter].rem - time;
			}

        kill(realpidi,SIGCONT);




    }






	while(1){

  		fflush(stdout);

        msgrcv( msqid, &msg_queue, sizeof(msg_queue.msg)+1,0,0);
        msg = msg_queue.msg;
  		if(strcmp(msg,"MEM")==0 ){

  		    ttok = strtok(NULL," \n");
			printf("%s \t",process[counter].name);
			printf("%d \t",timer++);
			kill(realpidi,SIGSTOP);
			printf("MEM\n");
			kill(realpidi,SIGCONT);

		}
		else if(strcmp(msg,"IO")==0){

			ttok = strtok(NULL," \n");
			if(ttok[0]=='i'){
			ioburst = 0;
			for (i=1; ttok[i]!='\0';i++ ){
			    ioburst = (ttok[i]-'0') + (ioburst*10);
			}
			}

			printf("%s \t",process[counter].name);
			printf("%d \t",timer);
			timer = timer + (abs(DiscHead - ioburst))*20;
			kill(realpidi,SIGSTOP);
			printf("IO\n");
			kill(realpidi,SIGCONT);
               	 }
		else if(strcmp(msg,"FORK")==0){


			printf("%s \t",process[counter].name);
			ttok = strtok(NULL," \n");
			printf("%d \t",timer);
			kill(realpidi,SIGSTOP);
			printf("FORK\n");
			kill(realpidi,SIGCONT);
			timer = timer + 5;
			int x;
			for(i=0;process[counter].line[i] != 'f'; i++);
			char fprocess [50];
			char timerstr[20];
			process[aindex+1].arrival = timer;
		//	sprintf(timerstr, "%d", timer);
		//	strcat(fprocess,timerstr);
		//	strcat(fprocess," ");
			strcpy(process[aindex+1].name,"f1");
		//	strcat(fprocess,"f1");
		//	strcat(fprocess," ");
		//    printf("%s\n",process[counter].line+(i+3));
			strcpy(fprocess,process[counter].line+(i+2));
		//	strcat(fprocess,' ');
			strcpy(process[aindex+1].line,fprocess);


		   printf("%s\n",process[aindex+1].line);
           strcpy(processLine,process[aindex+1].line);
          // linesplit = strtok (processLine," \n");


           int cpuburst=0;
           int cpubursttotal = 0;

            printf("%s\n",processLine);
           for(x=0; processLine[x] != '\n';x++){
               if(processLine[x]=='c'){
			        cpuburst = 0;
			        for (i=1; processLine[x+i]>='0' && processLine[x+i]<='9' ;i++ ){
			        printf("%c\n",processLine[x+i]);
		              	 cpuburst = (processLine[x+i]-'0') + (cpuburst*10);
	          		}

			           cpubursttotal += cpuburst;
			        }


           }

           process[aindex+1].burst = cpubursttotal;

			aindex++;


			}
		else if (strcmp(msg,"TERM")==0)
                {

                        break;
                            }

	//	kill(realpidi,SIGCONT);
        ///////////////////////////////////////////////
        if( (strcmp(cpualgorithm,"SRTN"))  ) {
            printf("%s \t",process[counter].name);
            printf("%d \t",timer);
            kill(realpidi,SIGSTOP);
            printf("CPU\n");
        //	kill(realpidi,SIGCONT);


           ttok = strtok(NULL," \n");

            if(ttok[0]=='c'){
			time = 0;
			for (i=1; ttok[i]!='\0' && ttok[i]!='\n';i++ ){
			    time = (ttok[i]-'0') + (time*10);
			}
		//	timer += time;

		//	process[counter].rem = process[counter].rem - time;
			}

            for(i=0;i<time ; i++ ){
               kill(realpidi,SIGCONT);
               sleep(1);
               kill(realpidi,SIGSTOP);
               killedornot = SRTN(process,timer);

               if(killedornot == 1){
                  timer+=2;
                  process[counter].flag = 1;
                  break;
                  }
               process[counter].rem--;
               timer++;
               }
            if(killedornot == 1)
               break;

        }




	//////////////////////////////////////////////////////
        if( (strcmp(cpualgorithm,"SJN"))  || (strcmp(cpualgorithm,"HRRN")) ){
            printf("%s \t",process[counter].name);
            printf("%d \t",timer);
            kill(realpidi,SIGSTOP);
            printf("CPU\n");
        	kill(realpidi,SIGCONT);


           ttok = strtok(NULL," \n");

            if(ttok[0]=='c'){
			time = 0;
			for (i=1; ttok[i]!='\0' && ttok[i]!='\n';i++ ){
			    time = (ttok[i]-'0') + (time*10);
			}
			timer += time;

			process[counter].rem = process[counter].rem - time;
			}


       }

	}
    if(killedornot == 1)
               continue;
	printf("%s \t",process[counter].name);
	printf("%d \t",timer);
	kill(realpidi,SIGSTOP);
	printf("Term\n");
    kill(realpidi,SIGCONT);
	kill(realpidi,SIGTERM);
	timer = timer+2;

    removefirstp(process);
/*
    printf("%d\n",aindex);
    for(i=0;i<=aindex;i++){
        printf("%d\t",process[i].arrival);
        printf("%s\t",process[i].name);
        printf("%d\t",process[i].burst);
        printf("%s\n",process[i].line);
        } */
    }

	msgctl(msqid,IPC_RMID,NULL);
    return 0;
}


int RR(proces process[10],int timer){

	int i, j, k, time = 0, n=aindex-1;
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
	process[aindex+1].arrival = timer;
	process[aindex+1].burst = process[0].burst;
	process[aindex+1].flag = process[0].flag;
    process[aindex+1].rem = process[0].rem;
    process[aindex+1].name = process[0].name;
    aindex++;
	removefirstp(process);

}






void SJN(proces process[10]){

	int i, j, k, time = 0, n=aindex-1;
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

	//no = 0;
	j = 1;
	//process[0].start = process[0].arrival;
    time = 0;
    int index = 0;

    for(i = index; i <= n; i++){
                for(j = i + 1; j <= n && process[j].arrival == process[i].arrival; j++,index++)
                {
                    if(process[i].burst > process[j].burst)
                    {
                    temp = process[i];
                    process[i] = process[j];
                    process[j] = temp;
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
    int m;
   // int min = 5000;
    int minindex = 0;
    for(x = 0; process[x].arrival <= timer; x++);
            for(i = 0; i <= x-1; i++){
                    if(process[i].rem < process[0].rem )
                    {
                      minindex = i;
                      temp = process[0];
                           process[0] = process[minindex];
                        process[minindex] = temp;
                      flag = 1;
                      }

                      }





    if(flag == 0)
        return 0;
    if(flag == 1)
        return 1;



            }






void removefirstp(proces process[10]){

	int i;



    for(i = 0; i < aindex ; i++){
                process[i] = process[i+1];
                }
    aindex--;

            }



void HRRN(proces process[10],int timer){

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

	j = 1;
	time = 0;
    int index = 0;
    int min =1000;
    int minindex = 0;

    for(i = index; i <= n && process[i].arrival <= timer; i++){
     //           for(j = i + 1; j <= n && process[j].arrival == process[i].arrival; j++,index++)
       //         {
                    if( ( (timer - process[i].arrival) / process[i].burst ) < min )
                    {
                        minindex = i;
                    }

                }

                temp = process[0];
                process[0] = process[minindex];
                process[minindex] = temp;


            }

