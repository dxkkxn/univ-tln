#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#define N 3


// int  main()
// {
// 	execl( "/bin/ls", "/bin/ls", "-a", "/home", NULL);	 
// 	printf("Succes");
	 
// 	// char *binaryPath = "/bin/ls";
// 	// char *arg1 = "-lh";
// 	// char *arg2 = "/home";

// 	// execl(binaryPath, binaryPath, arg1, arg2, NULL);

// 	return 0;
// }

int main ()
{
	char* com[3] = {"whoami", "ls", "pwd"};
	pid_t xd;
	for (int i = 0; i < N; i++)
	{
		if (fork() != 0)
		{
			// father 
			printf("papa tranquilou \n");
			xd = wait(NULL);

		}
		else
		{
			sleep(10);
			printf("command num %d \n", i);
			execlp(com[i], com[i], NULL);
			exit(0);
			printf("never printed \n");
		}
	}
}


