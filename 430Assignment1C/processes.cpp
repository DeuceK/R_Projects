#include <iostream>
#include <unistd.h>
//#include <sys/wait.h>
//#include <sys/types.h>

using namespace std;

int main(int argc, char *argv[]) 
{
    pid_t first, second, third;
    int arr1[2], arr2[2];

    //if argument count is not atleast two then print error
    if (argc < 2) 
    {
        perror("arg count error");
        return 1;
    }

    //grabs the pipe and fork values
    //int pipe1 = pipe(first);
    //int pipe2 = pipe(second);
    int forkParent = (first = fork());
    int forkChild = (second = fork());

    //checks and prints error if pipe wasn't properly ran
    if (pipe(arr1) < 0 || pipe(arr2) < 0)
    {
        perror("pipe");
        return 1;
    }
    
    //Parent Process
    if (forkParent < 0) 
    {
        perror("fork");
        return 1;
    }


    //Child Process
    if(first == 0)
    {
        if(forkChild == -1)
        {
            perror("fork");
            return 1;
        }
        else
        {
            //close each arr2
            close(arr2[0]);
            close(arr2[1]);
            //copy arr1[0] and then close each
            dup2(arr1[0], STDIN_FILENO);
            close(arr1[0]);
            close(arr1[1]);
            execlp("wc", "wc", "-l", '\0');
            //perror("execlp");
            return 1;
        }
    }

    //Grand Child Process
    if(first == 0 && second == 0)
    {
        //copy arr2[0] and then close descriptors
        dup2(arr2[0], STDIN_FILENO);
        close(arr2[0]);
        close(arr2[1]);
        //copy arr1[1] and then close descriptors
        dup2(arr1[1], STDOUT_FILENO);
        close(arr1[0]);
        close(arr1[1]);
        //replace current process with new one
        execlp("grep", "grep", argv[1], '\0');
        //perror("execlp");
        return 1;
    }

    //reached end of file. Print error and call wait
    third = wait(NULL);    
    perror("reached end of file");
    return 0;
}


//fork : creates a child process that differs from parent process only in terms of process ID's
//excelp : replaces current process image with a new process image that is loaded from file
//pipe : creates pair of file descriptors and puts them in array
//dup2 : creates copy of file descriptor 
//wait : waits for process termination
//close : closes file descriptor