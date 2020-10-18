#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        return 1;
    }
    else
    {
        struct timeval timeStart;
        struct timeval timeFinish;
        gettimeofday(&timeStart, NULL);
        int rc = fork();
        if (rc < 0)
        {
            fprintf(stderr, "fork failed\n");
            return 1;
        }
        else if (rc == 0)
        {
            char *myargs[argc];
            for (int i = 0; i < argc - 1; i++)
            {
                myargs[i] = argv[i + 1];
            }
            myargs[argc - 1] = NULL;
            execvp(myargs[0], myargs);
        }
        else
        {
            wait(NULL);
            gettimeofday(&timeFinish, NULL);
            printf("micro seconds elapsed time: %ld\n",
                   (timeFinish.tv_usec - timeStart.tv_usec));
        }
    }
    return 0;
}