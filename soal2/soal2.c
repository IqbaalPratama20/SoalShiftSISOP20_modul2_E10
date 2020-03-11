#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <string.h>

char* itoa(int val, int base){
	
	static char buf[32] = {0};
	
	int i = 30;
	
	for(; val && i ; --i, val /= base)
	
		buf[i] = "0123456789abcdef"[val % base];
	
	return &buf[i+1];
	
}

void subv(char *path, char * const argv[])
{
    int ret;
    pid_t a_pid = fork();
    if (a_pid == -1) return;
    if (a_pid != 0) 
    { 
        wait(&ret); 
        return; 
    }
    execv(path, argv);
}

int main()
{
    pid_t child_id;
    int status;
    time_t rawtime;
    struct tm *info;
    char folder[80];
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(folder,80,"%Y-%m-%d_%X", info);
    char dest[80];
    strcpy(dest, "/home/iqbaal/");
    strcat(dest,folder);
    child_id = fork(); 
    if (child_id < 0) 
    {
        exit(EXIT_FAILURE); 
    }
    if (child_id == 0) 
    {
        char *argv[] = {"mkdir", "-p", dest, NULL};
        execv("/bin/mkdir", argv);
    } 
    else 
    {
        wait(0);
        for(int i=0;i<2;i++)
        {
            char a[50];
            char str[100];
            char web[100];
            time(&rawtime);
            info = localtime(&rawtime);
            strftime(a,50,"%Y-%m-%d_%X", info);
            char b[80];
            strcpy(b,"/home/iqbaal/");
            strcat(b,folder);
            strcat(b,"/");
            strcat(b, a);
            int waktu = (time(0)%1000) + 100;
            strcpy(str, itoa(waktu, 10));
            strcpy(web,"https://picsum.photos/");
            strcat(web, str);
            char *args[] = {"wget", "-O",b, web, NULL};
            subv("/usr/bin/wget", args);
            // sleep(5);
        }
        char asiap[50];
        strcat(asiap, dest);
        char *args[] = {"zip", "-r", dest, dest, NULL};
        char *arglp[]= { "rm", "-r", dest, NULL};
        subv("/usr/bin/zip", args);
        subv("/bin/rm", arglp);
    }
}
