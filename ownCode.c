#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM_LENGTH 4
#define NUM_WAIT_INTERVAL 2

int getNum(){
int num;
srand(getpid() + getppid());
int secret = num + rand() % 2;
return secret;
}

int main(void){
while(1){
int pipefds[2];
int num;
int pin[NUM_LENGTH + 1];
int buffer[NUM_LENGTH + 1];

pid_t pid = fork();
pipe(pipefds);

printf("Please enter a number: \n");
scanf("%d",&num);

if(pid==0){
getNum(num); //generate number
close(pipefds[0]); //close read fd
write(pipefds[1],&num,sizeof (num)); //write number to pipe

printf("Generating Number...\n");

sleep(NUM_WAIT_INTERVAL); //delaying number generation intentionally

exit(EXIT_SUCCESS);
}

if(pid>0){
wait(NULL); //waiting for number generation

close(pipefds[1]);
read(pipefds[0],&num,sizeof (num)); //read number from pipe
close(pipefds[0]); //close read fd

num==getNum();

if(num==0)
printf("Even number is %d\n\n",num);

else
printf("Odd number is %d\n\n",num);

exit(EXIT_SUCCESS);
}
}
return EXIT_SUCCESS;
}
