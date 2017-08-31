#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#define MAX_APPS 10
#define MAX_LEN_APPS 20
int spawn(char * , char **);
void theBeginning(int);

struct process{
    char *command;
    char **arglist;
}s[10];

struct processList{
    int PID;
    char *command;
    struct processList *next;
}*head=NULL;
typedef struct processList ProcessList;
void wrapperForKill(int,ProcessList **);

void insertProcess(ProcessList **head,char *command,int PID)
{
    ProcessList *link = (ProcessList *) malloc(sizeof(ProcessList));
    link->command=(char *) malloc(sizeof(char) * (strlen(command)+1));
    strcpy(link->command,command);
    link->PID=PID;
    link->next=*head;
    *head=link;
}


void printList(ProcessList *node){
    int count=0;
    printf("\e[38;2;255;0;0mCommand\tPID\t\n\e[0m");
    while(node!=NULL){
        printf("%s\t%d\t\n",node->command,node->PID);
        node=node->next;
    }
}


void foobar(){}

int spawn (char* program, char** arg_list)
{
    pid_t child_pid;
    int i;

    child_pid = fork (); 
    if (child_pid != 0)
        return child_pid;
    else {
        execvp (program, arg_list);
        fprintf (stderr, "There is an error \n");
        abort (); 
    }   
}

void wrapperForKill(int pid,ProcessList **head){

    ProcessList *temp=(ProcessList *)malloc(sizeof(ProcessList));
    temp= *head;
    ProcessList *prev=NULL;
    if(temp != NULL && temp->PID ==pid){
        kill(pid,SIGTERM);
        *head = temp->next;
        free(temp);
        return ;
    }
    while(temp != NULL && temp->PID != pid){
        prev=temp;
        temp=temp->next;
    }
    if(temp ==NULL)
        return;
    kill(pid,SIGTERM);
    prev->next=temp->next;
    free(temp);
}

void theBeginning(int N){

    int status,i,ret;
    int flag=0,child_status;
    static int skip;
    char *PID=(char *) malloc(sizeof(char) * 10);
    char *choice =(char *)malloc(sizeof(char)*MAX_LEN_APPS);
    strcpy(choice,"");
    //char choice[20];
    printf("\e[38;2;241;196;15mWhat do you want to do next?\e[0m"); //rgb(241, 196, 15)
    fflush(stdout);
   // scanf("%s",choice);
    fgets(choice,20,stdin);

    if(strstr(choice,"exit") !=0 ){
      //  printf("debug\n");
        flag++;
        return;
    }
    if(strstr(choice,"list") !=0 ){
        printList(head); 
        flag++;
    }
    if(strstr(choice,"clear") != 0)
        foobar();
    if(strstr(choice,"kill") != 0){
        flag++;
        wrapperForKill(atoi(choice+5),&head);
    }
    for(i=0;i<N;i++){
        if(strstr(choice,s[i].command)!=0){
            ret=spawn(s[i].command,s[i].arglist);
           
            insertProcess(&head,s[i].command,ret);
            flag++;
        }
    }
    if(!flag)
        printf("Invalid Command: Try again\n");

    theBeginning(N);
}
int main(){
    char **args =(char **)malloc(MAX_APPS*sizeof(char *));
    int i,c;
    static int j=0;
    pid_t process;
    int numberOfApps;
    char *initProgram="";
    char *initArglist[] ={""};
    char *AppNumber = (char *)malloc(sizeof(char)*2);
    printf("Enter the number of apps\n");
    numberOfApps=atoi(fgets(AppNumber,2,stdin));
    for(i=0;i<numberOfApps;i++){
        s[i].command=(char *)malloc(sizeof(char)*MAX_LEN_APPS);
        scanf("%s",s[i].command);
    }
    for(i=0;i<numberOfApps;i++){
        s[i].arglist=(char **)malloc(sizeof(char *) * 10);
        s[i].arglist[0]=s[i].command;
        s[i].arglist[1]=NULL;
    }
    while ( (c = getchar()) != '\n' && c != EOF );
   // printf("hello");
    theBeginning(numberOfApps);
}



