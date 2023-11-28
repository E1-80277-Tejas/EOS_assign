/*2. From a parent process (A) create a child process (B). The child (B) in turn creates new child process (C) and it (C) in turn create new child (D). All these
processes should run concurrently for 5 seconds and cleaned up properly upon termination.*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


int main() {
    int i, pidb, sb, pidc, sc ,pidd, sd;

    
    pidb = fork();
    if(pidb == 0) { 
        
        pidc = fork();
        if(pidc == 0) {
                pidd = fork();
                if(pidd == 0){
                for(i=1; i<=5; i++) {
                    printf("D. sunbeam karad: %d\n", i);
                    sleep(1);
                }
                _exit(0);
                }
            
            for(i=1; i<=5; i++) {
                printf("C. sunbeam desd: %d\n", i);
                sleep(1);
            }
            _exit(0);
        }
        
        
        for(i=1; i<=5; i++) {
            printf("B. sunbeam pune: %d\n", i);
            sleep(1);
        }
        waitpid(pidc, &sc, 0);
        _exit(0);
    }

    
    for(i=1; i<=5; i++) {
        printf("A. sunbeam: %d\n", i);
        sleep(1);
    }
    waitpid(pidb, &sb, 0);

    return 0;
}

	
