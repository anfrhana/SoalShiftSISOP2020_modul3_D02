#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int folder[2];
    pid_t id;

    if (pipe(folder)==-1){
        fprintf(stderr, "pipe gagal dilakukan" );
        return 1;
    }
    id = fork();

    if (id < 0){
        fprintf(stderr, "fork gagal dilakukan" );
        return 1;
    }

    else if (id == 0){
        close(1);
        dup(folder[1]);
        close(folder[0]);
        
        char *argm1[] = {"ls", NULL};
        execv("/bin/ls", argm1);
    }
    else{
        wait(NULL);
        close(0);
        dup(folder[0]);
        close(folder[1]);
 
	char *argm2[] = {"wc", "-l", NULL};
        execv("/usr/bin/wc", argm2);
    }
}
