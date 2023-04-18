//1190880_Qays Safa
#include <stdio.h>
#include <stdlib.h>
#include <String.h>

typedef struct node* PNode; //Define stack;
typedef PNode Stack;

struct node{
char date[100];
PNode next;
};
//function to check stack is empty or not .
int IsEmpty( Stack S ){
    if (S->next == NULL){
        return 1 ;}
        else{
        return 0 ;
        }
}

//function to add element into stack  .
void Push(char input[], Stack S){
    PNode temp ;
    PNode last ;

    last = S ;

    temp = (Stack)malloc(sizeof(struct node)) ;

        strcpy(temp-> date , input) ;
        temp->next = NULL ;
        while(last->next != NULL)
            last = last->next;
        last->next = temp;
}

//function to delete the last element from stack .
void POP (Stack s){
    PNode del ;
    if(IsEmpty(s)){
    printf( "The stack does not contain elements!!\n" ) ;
    }
    else{
        del = s ;
        while(del->next != NULL){
            s = del ;
            del = del->next ;
        }
        if(del == s){
            s = NULL ;
        }
        else{
            s->next = NULL ;
        }
    }
        free(del) ;

}

//function to save output in file .
void save(FILE* filePointer, struct node* s)
{
    fprintf(filePointer,"result > \n");
        while(!IsEmpty(s)){
            s = s->next ;
           fprintf(filePointer,"%s\n",s->date);
        }

}
//function to get the last element was enter satck .
PNode Top (Stack s){
    if(IsEmpty(s)){
        printf("Stack is Empty!!\n") ;
    return 0 ;
    }
    else{
        while(s->next != NULL){
            s = s->next ;
        }
        return s ;
    }
     }


void printList(Stack s){//function to print the satck.

        while(!IsEmpty(s)){
            s = s->next ;
            printf("%s\n", s->date) ;
        }
}

//main function
int main()
{
  Stack s1 = (Stack)malloc(sizeof(struct node)) ; // Create stack (s1) to store the element.
s1->next = NULL;

Stack s2 = (Stack)malloc(sizeof(struct node)) ; // Create stack (s2) to store the element that deleted to get it back .
s2->next = NULL;


 printf("\n Please enter the date :- \n\n");

while (1){  //infinite loop to keep reading input Until the user enters the quit command .

    printf("\n MyCommand > ") ;
        char statement [100] ; // to store the date in char statement.
        gets(statement) ; // to read the date from user .

        if (strcmp("print",statement)==0 ){ // to check if user enter print to print data.
        if(IsEmpty(s1)){
        printf("result > \n");
        printf("No element in Stack \n") ;
    }
    else{
        printf("result > \n");
        printList(s1);}
        }
        else if (strcmp("undo",statement)==0 ) { // to check if user enter undo to delete the last element enterd.
                if(!IsEmpty(s1)){
                PNode last = Top(s1) ;
                Push(last->date , s2) ;
                POP(s1) ;
                printf("result > \n");
                printList(s1) ;
            }
             else{
                printf("result > \n");
                printf("It cannot be deleted because the stack does not contain any elements!!]\n");

            }

        }
        else if (strcmp("redo",statement)==0 ) { // to check if user enter redo to get back the last element deleted.
               if(!IsEmpty(s2)){
                PNode last = Top(s2) ;
                Push(last->date , s1) ;
                POP(s2) ;
                printf("result > \n");
                printList(s1) ;
            }
            else{
                printf("result > \n");
                printf("no element to get it back\n");
            }

        }
        else if (strcmp("save",statement)==0 ) { // to check if user enter save to save the element in file.
            FILE* filePointer;
            filePointer=fopen("output.txt","w");
            save(filePointer,s1);
            fclose(filePointer);
            printf(" result > Save done. \n");
        }
        else if (strcmp("quit",statement)==0 ) { // to check if user enter quit to save element in file and quit program.
           FILE* filePointer;
           filePointer=fopen("output.txt","w");
            save(filePointer,s1);
          fclose(filePointer);
           printf("result > Good Bye!\n");
            exit(0);
            break ;
        }
        else { //If user enter a statement other than the one above, program store it in the stack s1 .
       Push (statement,s1);

        }
}
    return 0;
}
