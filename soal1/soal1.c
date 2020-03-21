#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <regex.h>
#include <time.h>
#include <sys/wait.h>

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

void service_maker(char * second, char * minutes, char * hour, char * path_file){
    pid_t pid, sid; // Variabel untuk menyimpan PID

pid = fork(); // Menyimpan PID dari Child Process

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

close(STDIN_FILENO);
close(STDOUT_FILENO);
close(STDERR_FILENO);
    while (1) {
        time_t times;
        struct tm* tm_info;  
        times = time(NULL);
        tm_info = localtime(&times);
        char skrg_jam[5];
        sprintf(skrg_jam,"%d", tm_info->tm_hour);
        char skrg_menit[5]; 
        sprintf(skrg_menit, "%d", tm_info->tm_min);
        char skrg_detik[5];
        sprintf(skrg_detik, "%d", tm_info->tm_sec);
        if( strcmp(hour, "*")==0)
        {
            if(strcmp(minutes,"*") == 0)
            {
                if(strcmp(second,"*")==0)
                {
                    char *args[] = {"bash", path_file, NULL};
                    subv("/bin/bash", args);
                }
                else if(strcmp(skrg_detik, second)==0)
                {
                    char *args[] = {"bash", path_file, NULL};
                    subv("/bin/bash", args);
                }
            }
            else if(strcmp(skrg_menit, minutes))
            {
                if(strcmp(second, "*")==0)
                {
                    char *args[] = {"bash", path_file, NULL};
                    subv("/bin/bash", args);
                }
                else if(strcmp(skrg_detik,second)==0)
                {
                    char *args[] = {"bash", path_file, NULL};
                    subv("/bin/bash", args);
                }
            }
        }
        else if( strcmp(hour,skrg_jam)==0)
        {
            if(strcmp(minutes,"*") == 0)
            {
                if(strcmp(second,"*")==0)
                {
                    char *args[] = {"bash", path_file, NULL};
                    subv("/bin/bash", args);
                }
                else if(strcmp(skrg_detik,path_file)==0)
                {
                    char *args[] = {"bash", path_file, NULL};
                    subv("/bin/bash", args);
                }
            }
            else if(strcmp(skrg_menit, minutes)==0)
            {
                if(strcmp(second,"*")==0)
                {
                    char *args[] = {"bash", path_file, NULL};
                    subv("/bin/bash", args);
                }
                else if(strcmp(skrg_detik,second)==0)
                {
                    char *args[] = {"bash", path_file, NULL};
                    subv("/bin/bash", args);
                }
             }
        }   
        sleep(1);
    }
}

int pattern_check(char * paths){
    FILE *file;
    if ((file = fopen(paths, "r")))
    {
        fclose(file);
        return 1;
    }
    return 0;
}

int main(int argc, char **argv){
    if (argc-1 > 4 || argc-1 < 4){
        printf("Terjadi kesalahan input\n");
    }else{
        if ( (strcmp(argv[1], "*") == 0) || (strcmp(argv[1], "0") >= 0 && strcmp(argv[1],"59") <= 0) ){
            if ( (strcmp(argv[2], "*") == 0) || (strcmp(argv[2], "0") >= 0 && strcmp(argv[2],"59") <= 0) ){
                if ( (strcmp(argv[3], "*") == 0) || (strcmp(argv[3], "0") >= 0 && strcmp(argv[3],"23") <= 0) ){
                    if (pattern_check(argv[4]) == 1){
                        service_maker(argv[1], argv[2], argv[3], argv[4]);
                    }else{
                        printf("Terjadi kesalahan pada argumen 4\n");    
                    }
                }else{
                    printf("Terjadi kesalahan pada argumen 3\n");    
                }
            }else{
                printf("Terjadi kesalahan pada argumen 2\n");    
            }
        }else{
            printf("Terjadi kesalahan pada argumen 1\n");
        }
    }
    return 0;
}
