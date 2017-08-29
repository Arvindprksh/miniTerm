#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#define MAX_APPS 10
#define MAX_LEN_APPS 20
int spawn(char * , char **);
void theBeginning();



struct process{
    char *command;
    char **arglist;
}s[10];




struct processList{
    int PID;
    char *command;
    struct processList *next;
};
typedef struct processList ProcessList;



void insertProcess(ProcessList **head,char command[10],int PID)
{
    ProcessList *link = (ProcessList *) malloc(sizeof(ProcessList *) );
    strcpy(link->command,command);
    link->PID=PID;
    link->next=*head;
    *head=link;
}


void printList(ProcessList *node){
    printf("Command\tPID\t\n");
    while(node!=NULL){
        printf("%s\t%d\t\n",node->command,node->PID);
        node=node->next;
    }
}

int main(){
    char **args =(char **)malloc(MAX_APPS*sizeof(char *));
    int i;
    static int j=0;
    printf("hello %d",j++);
    //static int numberOfApps;
    pid_t process;
    printf("hello %d",j++);  
    int numberOfApps;
    char *initProgram="";
    char *initArglist[] ={""};
    printf("Enter the number of apps");
    scanf("%d",&numberOfApps);
    //struct process s[numberOfApps];

    for(i=0;i<numberOfApps;i++){

        s[i].command=(char *)malloc(sizeof(char)*MAX_LEN_APPS);
        scanf("%s",s[i].command);
    }
     printf("hello %d",j++);
    // printf("enter the number of commands");
    for(i=0;i<numberOfApps;i++){
        s[i].arglist=(char **)malloc(sizeof(char *) * 10);
        s[i].arglist[0]=s[i].command;
        s[i].arglist[1]=NULL;
    }  
    theBeginning(numberOfApps);
}
int spawn (char* program, char** arg_list)
{
    pid_t child_pid;
    int i;
    //printf("in spawn function");

    /* Duplicate this process. */
    child_pid = fork (); 
    if (child_pid != 0)
        /* This is the parent process. */
        return child_pid;
    else {
        /* Now execute PROGRAM, searching for it in the path. */
        execvp (program, arg_list);
        /* The execvp function returns only if an error occurs. */
        fprintf (stderr, "an error occurred in execvp\n");
        abort (); 
    }   
}
//sfsdfsf
void theBeginning(int N){

    int status,i,ret;
    //for(i=0;i<2;i++)
    //  printf("%s",s[0].arglist[i]);
    ProcessList *head = NULL;
    //char *choice =(char *)malloc(sizeof(char)*MAX_LEN_APPS);
    char choice[8];
    printf("What do you want to do next? ");
    scanf("%s",choice);
    printf("hello");
    if(strcmp(choice,"exit") ==0 )
        return ;
    if(strcmp(choice,"list") ==0 ){
    //    printList(head);
    }
    printf("debug");   
    // if(strstr(choice,"kill") != 0 );
    for(i=0;i<N;i++){
        printf("hello");
        printf("%s",s[i].command);
        if(strcmp(choice,s[i].command)==0){
            printf("hi1");
            // s[i].
            ret=spawn(s[i].command,s[i].arglist);
            insertProcess(&head,s[i].command,ret);
            printf("%d\n",ret);
            //char *arglist[]={"vlc","Dhuruvangal Pathinaaru - Uthira Kaayangal Song Making with Lyrics - Jakes Bejoy - Karthick Naren.mp3","&",NULL};
        }
        //  printf("It is done");
    }
    theBeginning(N);
    printf("End of story");

}



