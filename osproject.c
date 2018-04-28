//There are two primary participants; One Teacher(T) and three students(S1,S2 and S3). A student needs four resources to complete a drawing: pencil,paper,sharpener and eraser.Initially, S1 is issued a paper,sharpener and eraser. S2 is issued paper,pencil and eraser. S3 is issued paper,eraser and pencil.Teacher puts any one of the three resources(pencil,eraser and sharpener) on a table and all three students try to take that resource. Only one student will be able to complete the drawing. Teacher keeps repeating the process until all of the students completed their drawing operation.

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

//Algorithm followed: Similar to Dining Philospher's Problem using Semaphores/Moderator
sem_t teacher;//mutex
sem_t SN[3];//Students array
int resources[]={0,0,0};//pencil,sharpener and eraser
int S[3][3]={{0,1,1},//student 1
             {1,0,1},//student 2
             {1,0,1}};//student 3
int studentfull[]={0,0,0};
int x,y,i;

int resourcefull(){
   int flag=1;
   printf("\n");
   for(i=0;i<3;i++){
      if(studentfull[i]==0){
        flag=0;
      }
   }
   return flag;
}

void *takeitem(){                      //each student check if they require this item if yes the student has completed the work
    sem_wait(&teacher);
    sleep(1);
    //printf("\n%d",studentfull[i]);
    if(studentfull[i]!=1)
        printf("\nStudent %d is trying to access",i+1);
        sleep(1);
        if(S[i][y]!=resources[y]){
                sem_wait(&SN[i]);
                printf("\nStudent %d needs the item",i+1);
                sleep(1);
                printf("\nStudent %d has completed his work",i+1);
                sleep(1);
                printf("\nStudent %d has put back the item",i+1);
                studentfull[i]=1;
                sleep(1);
                sem_post(&SN[i]);
            }
         else{
                sleep(1);
                sem_wait(&SN[i]);
                printf("\nStudent %d doesn't need it",i+1);
                sem_post(&SN[i]);
                sleep(1);
            }
    sem_post(&teacher);
}

void randomitem(){                       //generates random item
    if(x==0){                            //pencil
        resources[0]=1;
        y=0;
        printf("pencil ");
     }
     if(x==1){                           //sharpener
        resources[1]=1;
        y=1;
        printf("sharpener ");
     }
     if(x==2){                           //eraser
        resources[2]=1;
        y=2;
        printf("eraser ");
     }
     printf("on the table\n");
}


int main(){                              //O(T)=n^(21)
    pthread_t thread_id[3];
    printf("Welcome to Drawing Competition Problem\n");
    sem_init(&teacher,0,1);
    for(i=0;i<3;i++)
        sem_init(&SN[i],0,1);
    while(resourcefull()!=1){
        sleep(1);
        printf("\nTeacher has put ");
        x=rand()%3;
        randomitem();
        for(i=0;i<3;i++)
            pthread_create(&thread_id[i],NULL,takeitem,&S[i][0]);
        for(i=0;i<3;i++)
            pthread_join(thread_id[i],NULL);
    }
    return 0;
}
