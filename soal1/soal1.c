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

void service_maker(char * second, char * minutes, char * hour, char * path_file){
    // pid_t pid, sid;        // Variabel untuk menyimpan PID
    // pid = fork();     // Menyimpan PID dari Child Process

    // /* Keluar saat fork gagal
    // * (nilai variabel pid < 0) */
    // if (pid < 0) {
    //     exit(EXIT_FAILURE);
    // }

    // /* Keluar saat fork berhasil
    // * (nilai variabel pid adalah PID dari child process) */
    // if (pid > 0) {
    //     exit(EXIT_SUCCESS);
    // }

    // umask(0);

    // sid = setsid();
    // if (sid < 0) {
    //     exit(EXIT_FAILURE);
    // }

    // if ((chdir("/")) < 0) {
    //     exit(EXIT_FAILURE);
    // }

    // close(STDIN_FILENO);
    // close(STDOUT_FILENO);
    // close(STDERR_FILENO);

    // while (1) {
        
    //     sleep(1);
    // }
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ( "Current local time and date: %s", asctime (timeinfo) );
}

int pattern_check(char * paths){
    int counter = 0;
    int totsize = strlen(paths) - 22;
    for (int i=0; i<strlen(paths); i++){
        if (paths[i] == '/'){
            counter++;   
        }
    }
    
    regex_t regex;
    int return_value;
    int sub_return_value;
    return_value = regcomp(&regex,"/home/syubban/Desktop/",0);
    return_value = regexec(&regex, paths, 0, NULL, 0);   
    if (return_value == 0 && counter == 4) {
        char subbuff[totsize];
        memcpy( subbuff, &paths[22], totsize);
        sub_return_value = regcomp(&regex,".sh",0);
        sub_return_value = regexec(&regex, subbuff, 0, NULL, 0);
        if (sub_return_value == 0){
            return 1;
        }
    } 
    return 0;
}


int main(int argc, char **argv){
    //printf("%d", argc);
    if (argc-1 > 4){
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