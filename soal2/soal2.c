#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <syslog.h>
#include <sys/stat.h>


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

void killer(char *asiap)
{
    FILE *fp;
    fp = fopen("/home/iqbaal/praktikum2/killer", "w+");
    if(strcmp(asiap,"-a")==0)
    {
        fprintf(fp,"#!/bin/bash\nkill -9 -%d\nrm $0", getpid());
    }
    else if(strcmp(asiap,"-b")==0)
    {
        fprintf(fp,"#!/bin/bash\nkill %d\nrm $0", getpid());
    }
    else
    {
        printf("Argumen yang dimasukkan kurang tepat");
        exit(1);
    }
    
    char *argv[]={"chmod", "+x", "/home/iqbaal/praktikum2/killer", NULL};
    subv("/bin/chmod", argv);
    fclose(fp);
}

int main(int argc, char ** argv)
{
    pid_t pid, sid;        // Variabel untuk menyimpan PID

    pid = fork();     // Menyimpan PID dari Child Process

    /* Keluar saat fork gagal
    * (nilai variabel pid < 0) */
    if (pid < 0) {
      exit(EXIT_FAILURE);
    }

    /* Keluar saat fork berhasil
    * (nilai variabel pid adalah PID dari child process) */
    if (pid > 0) {
      exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
      exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0) {
      exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    killer(argv[1]);
    while(1)
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
            while ((wait(&status)) > 0);
            pid_t child_next;
            int status_next;
            child_next = fork(); 
            if (child_next < 0) 
            {
                exit(EXIT_FAILURE); 
            }
            if (child_next == 0) 
            {
                for(int i=0;i<20;i++)
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
                    int waktu = ((int)time(NULL)%1000) + 100;
                    sprintf(str,"%d", waktu);
                    strcpy(web,"https://picsum.photos/");
                    strcat(web, str);
                    char *args[] = {"wget", "-qO",b, web, NULL};
                    subv("/usr/bin/wget", args);
                    sleep(5);
                }
                char *args[] = {"zip", "-r", dest, dest, NULL};
                char *arglp[]= { "rm", "-r", dest, NULL};
                subv("/usr/bin/zip", args);
                subv("/bin/rm", arglp);
                exit(0);
            } 
            else 
            {
                sleep(30);    
            }
        }
    }
}
