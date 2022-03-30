#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>

void main(int argc, char** argv)
{
    int n = argc - 2;
    int main_tube[2];

    pipe(main_tube);

    for(int i = 0; i < n; i++)
    {
        if(fork() == 0)
        {
            // fils
            int tube[2]; 
            pipe(tube);
            
            close(main_tube[0]);

            if(fork() == 0)
            {
                //fils du fils
                dup2(tube[1], 1);
                close(tube[1]);
                close(main_tube[1]);
                close(tube[0]);
                execlp("grep", "grep", "-o", argv[1], argv[i + 2], NULL);
            }
            else
            {
                // fils
                dup2(main_tube[1], 1);
                dup2(tube[0], 0);
                close(main_tube[1]);
                close(tube[1]);
                close(tube[0]);
                execlp("wc", "wc", "-l", NULL);

            }
        }
    }
    close(main_tube[1]);

    int total = 0; 
    char buffer;
    int curr_num = 0;
    for(int i = 0; i < n; )
    {
        read(main_tube[0], &buffer, sizeof(char));
        if(48 <= buffer && buffer <= 57) {
	    curr_num *= 10 ;
	    curr_num += buffer -48;
	} else {
	    total += curr_num;
	    curr_num = 0;
	    i++;
	}
		
    }
    printf("%d\n", total);
}

    
