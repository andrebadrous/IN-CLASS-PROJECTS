/**
 * filecopy.c
 * 
 * This program copies files using a pipe.
 *
 */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

#define READ_END 0
#define WRITE_END 1
int main(int argc, char *argv[])
{
    // argv[1] is the parent file
    // argv[2] is the child file
    // argc is 3
    if (argc != 3) {
        printf("ERROR: there should be 3 parameters\n");
        return 1;
    }
    // this is for the pipe 
    int fd[2];
    // open the files
    FILE *parent = fopen(argv[1], "r");
    FILE *child = fopen(argv[2], "w");
    // error checking
    if (parent == NULL) {
        printf("ERROR: Unable to open source file %s\n", argv[1]);
    }
    if (child == NULL) {
        printf("ERROR: Unable to open destination file %s\n", argv[2]);
    }
    // create the pipe
    if (pipe(fd) == -1) {
        printf("ERROR: pipe function has failed\n");
        return 1;
    }
    // create the fork
    int fork_process = fork();


    if (fork_process > 0) {
        // parent process
        close(fd[READ_END]);
        char buffer[100];
        // read from the parent file and write to the pipe
        while (fgets(buffer, 100, parent) != NULL) {
            write(fd[WRITE_END], buffer, sizeof(buffer));
        }

        close(fd[WRITE_END]);
        fclose(parent);
        fclose(child);
        wait(NULL);
        printf("File successfully copied to %s.\n", argv[2]);

    } else if (fork_process == 0) {
        // child process
        close(fd[WRITE_END]);
        char buffer[100];
        // read from the pipe and write to the child file
        while ((read(fd[READ_END], buffer, 100)) > 0) {
            fprintf(child, "%s", buffer);
        }

        close(fd[READ_END]);
        fclose(parent);
        fclose(child);

    } else {
        printf("ERROR: fork function has failed\n");
        return 1;
    }
    
    return 0;
}
