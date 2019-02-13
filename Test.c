#include <stdio.h> 
#include <unistd.h> 
#include<stdlib.h>
#include<sys/wait.h>
#define MSGSIZE 300 
char* msg1 = "hello, world #1"; 
char* msg2 = "hello, world #2"; 
char* msg3 = "hello, world #3"; 
  
int main() 
{ 
    char inbuf[MSGSIZE]; 
    int p[2], pid, nbytes; 
  
    if (pipe(p) < 0) 
        exit(1); 
  
    if ((pid = fork()) > 0) {
        close(p[0]); 
        write(p[1], "This is Pratik Parmar3w4sed5r6ftg7y8hui9jioooooouhiygtfydrtedrfytugyihu", MSGSIZE); 
        write(p[1], msg2, MSGSIZE); 
        write(p[1], msg3, MSGSIZE); 
        close(p[1]);
        wait(NULL); 
        
    } 
  
    else {
        close(p[1]);
        printf("I am a child"); 
        while ((nbytes = read(p[0], inbuf, MSGSIZE)) > 0) 
            printf("% s\n", inbuf); 
        close(p[0]);
        printf("Finished reading\n"); 
    } 
    return 0; 
} 