



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


main(){
    FILE *f;

   typedef struct {
	int type;
	char msg[MAX];
   }mymsg;
   char * array[100];
   int aindex=0;
   char name[20];
   char arrayelem[50];
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
   int time = 0;
   tmp = (char *) malloc(50);
   f = fopen("/home/ma30/Desktop/a.txt","r");
   fgets(tmp,50,f);
   for (i=0; *tmp != 0;i++ ){
	 array[i]= tmp;
	tmp = (char *) malloc(50);
	aindex ++;
	 fgets(tmp,50,f);



	}
   fclose(f);
 //  freopen ("Output.txt","w",stdout);
 	int counter=0;
  while (counter < aindex){



   strcpy(arrayelem,array[counter]);
   linesplit = strtok (arrayelem," ");
   time = 0;
   for (i=0; linesplit[i]!='\0';i++ ){
	 time = (linesplit[i]-'0') + (time*10);
	}
  // printf("%d\n",timer);
   timer += time;
//printf("%d",timer);
 //  printf("%d",timer);

   char inputline[100];
   memset(inputline,0,sizeof(inputline));
   strcat(inputline,"./process ");
   linesplit = strtok (NULL," ");
   strcpy(name,linesplit);
   strcat(inputline,linesplit);
   strcat(inputline," ");
   char pids[4];
   sprintf(pids,"%d",pid++);
   strcat(inputline,pids);
   strcat(inputline," ");
   linesplit = strtok (NULL,"");
  // printf("%s\n",array[0]);

	fflush(stdout);
	char *Args[10];
   Args[0]="/usr/bin/gnome-terminal";
   Args[1]="-e";
   Args[2]=inputline;
   Args[3]=NULL;
   strcat(inputline,linesplit);
 //  printf("%s\n",linesplit);
   pid_t fork_result ;
   fork_result = fork();


//  printf("%d \n",fork_result);
	fflush(stdout);
   if ( fork_result == 0 ){
	printf("Childprocess");
	execv(Args[0],Args);
}


	//sleep(5);
 //    printf("Process ID :%d\n",getpid());

   //  printf("I'm the father\n");

     msgrcv( msqid, &msg_queue, sizeof(msg_queue.msg)+1,0,0);
//	msqid = msgget(6765, IPC_CREAT | 0666 );
//   kill(realpidi,SIGSTOP);
     realpid = msg_queue.msg;
     for (i=0; realpid[i]!='\0';i++ ){
	 realpidi = (realpid[i]-'0') + (realpidi*10);
	}

      //  printf("%s\n",realpid);
//	kill(realpidi,SIGCONT);
	//


//      printf("%s\n",msg_queue.msg);

	//int adad;


	//printf("%d   %s \n",timer,ttok);
	printf("%s \t",name);
	printf("%d \t",timer);
	kill(realpidi,SIGSTOP);
	printf("CREATE\n");
        kill(realpidi,SIGCONT);
	//sscanf(linesplit,"c%d",&adad);
   //     printf("%s\n",linesplit);
	//sscanf(NULL,"c%d",&adad);
	printf("%s \t",name);
	printf("%d \t",timer);
	kill(realpidi,SIGSTOP);
	printf("CPU\n");
	kill(realpidi,SIGCONT);
	ttok = strtok(linesplit," \n");
	if(ttok[0]=='c'){
			time = 0;
			for (i=1; ttok[i]!='\0';i++ ){
			 time = (ttok[i]-'0') + (time*10);
			}
			timer += time;
			}

	while(1){

  		fflush(stdout);




	       msgrcv( msqid, &msg_queue, sizeof(msg_queue.msg)+1,0,0);
	        msg = msg_queue.msg;
  		if(strcmp(msg,"MEM")==0 ){
			ttok = strtok(NULL," ");
			//printf("%s       \n",ttok);
			printf("%s \t",name);

			printf("%d \t",timer++);
			kill(realpidi,SIGSTOP);
			printf("MEM\n");
			kill(realpidi,SIGCONT);
		}
		else if(strcmp(msg,"IO")==0){
			ttok = strtok(NULL," ");
			printf("%s \t",name);
			//printf("%s       \n",ttok);
			printf("%d \t",timer++);
			kill(realpidi,SIGSTOP);
			printf("IO\n");
			kill(realpidi,SIGCONT);
               	 }
		else if(strcmp(msg,"FORK")==0){
			printf("%s \t",name);
			ttok = strtok(NULL," ");
			printf("%d \t",timer++);
			kill(realpidi,SIGSTOP);
			printf("FORK\n");
			kill(realpidi,SIGCONT);
			int x;
			for(i=0;array[counter][i] != 'f'; i++)
				;
			char fprocess [30];
			char timerstr[20];
			sprintf(timerstr, "%d", timer);
			strcat(fprocess,timerstr);
			strcat(fprocess," ");
			strcat(fprocess,"f1");
			strcat(fprocess," ");
			strcat(fprocess,array[counter]+i+2);
			array[aindex] = fprocess;
			aindex++;
		/*	for(i=0;i<aindex; i++){
				printf("%s",array[i]);
				}

			*/
			}
		else if (strcmp(msg,"TERM")==0)
		{
			/*printf("TERM\n");
			printf("%d \t",timer);
			kill(realpidi,SIGSTOP);
			printf("TERM\n");
			kill(realpidi,SIGTERM);*/
		//	printf("%s \t",name);
			//printf("%s       \n",ttok);
		//	printf("%d \n",timer);


			break;
			}
		printf("%s \t",name);
		printf("%d \t",timer);
		kill(realpidi,SIGSTOP);
		printf("CPU\n");
		kill(realpidi,SIGCONT);
		ttok = strtok(NULL," ");
		//printf("%s       \n",ttok);
		if(ttok[0]=='c'){
			if(strcmp(ttok,"c2")==0){
				timer += 2;
  			 	continue;
			}
			time = 0;
			//printf("%s       \n",ttok);
			for (i=1; ttok[i]!='\0' && ttok[i]!='\n'  ;i++ ){				//printf("%c \t",ttok[i]);
			 time = (ttok[i]-'0') + (time*10);
			}
			//printf("\n");
			//printf("%d \n",timer);
			timer += time;
			//printf("%d \n",timer);
			}
	//printf("%d \n",timer);
       }
	printf("%s \t",name);
	printf("%d \t",timer);
	kill(realpidi,SIGSTOP);
	printf("Term\n");
        kill(realpidi,SIGCONT);
	kill(realpidi,SIGTERM);

	counter++;
}
 	msgctl(msqid,IPC_RMID,NULL);
   return 0;

}

/*
		if(ttok[0]=='c'){
			time = 0;
			for (i=1; ttok[i]!='\0';i++ ){
			 time = (linesplit[i]-'0') + (time*10);
			}
			timer += time;
			}
		*/




