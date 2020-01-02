#include <unistd.h>     // read(), write(), close(), fork(), pipe(), getpid(), nice()
#include <stdio.h>      // printf(), perror()
#include <sys/wait.h>   // wait()
#include <stdlib.h>     // exit()

#define ESC 0x1B

int main(void) {
    int fd1[2];     // redirect will write to filter
    int fd2[2];     // redirect will read from filter
    pid_t pid_parent, pid_child, pid_catched;   // these will store de process id's from the parent and the child process
    int exitStatus;

    // The two pipes will be created, and error message will be displayed if the pipe creeation has failed.
    if(pipe(fd1) == -1) {
        perror("### pipe 1 failed\n");
        exit(1);
    }

    if(pipe(fd2) == -1) {
        perror("### pipe 2 failed\n");
        exit(1);
    }

    // the creation of the child process
    switch(fork()){
    
    // fork error handling
    case -1:
        perror("### the forking of the child has failed\n");
        exit(1);

    // The created child process
    case 0:
        pid_child = getpid();
        printf("--- child pid: %d\n", pid_child);
        
        //assigns the output of fd1 to the stdin of the child process
        dup2(fd1[0], 0);    
        close(fd1[0]);

        //assigns the input of fd2 to the stdout of the child process
        dup2(fd2[1], 1);
        close(fd2[1]);

        execl("filter", "filter", NULL);
        printf("--- ERROR: the function execl should not return");
        exit(1);

        break;

    // The continuation of the parent process
    default:
        pid_parent = getpid();
        printf("### parent pid: %d\n", pid_parent);

        char request = 'o';
        char response = 'o';

        sleep(1);
        printf("### Please write some text to be processed\n\n");
        read(0, &request, 1);          // read first char from stdin
  
        while(1) {        // ESC = Ctrl-[ in shell

            // check wheter the initial command before the while loop is not the exit command
            if(request == ESC) {
                break;
            }

            write(fd1[1], &request, 1);     // write char to stdout
            read(fd2[0], &response, 1);     // Read the response char from filter
            write(1, &response, 1);         // Write the response char to the screen
            read(0, &request, 1);           // Read the next charachter

            // check wether the command given is the exit command
            if(request == ESC) {
                break;
            }
        }

        printf("### parent has stopped redirecting characters to filter\n");
        printf("### parent is now sending a terminate command to the child process\n");
        kill(pid_child, SIGTERM);
        // write(fd1[1], "test", 5);
        // read(fd2[0], message, 5);
        // printf("### the response from filter was %s\n", message);

        pid_catched = wait(&exitStatus);
        printf("### child with pid %d has exited with status 0x%x\n", pid_catched, exitStatus);
    }   // end of witch case statement
    return(0);
}   // end of main