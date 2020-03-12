#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h> 

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

int main() {
    pid_t child_id;
    int status;

    child_id = fork();
  
    if (child_id < 0) {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child_id == 0) {
        // this is child  
        char *argv[] = {"mkdir", "-p", "/home/syubban/modul2/indomie", NULL};
        execv("/bin/mkdir", argv);
    } else {
        // this is parent
        sleep(5);
        while ((wait(&status)) > 0);
        pid_t other_child;
        int second_status;
        other_child = fork();
        
        if (other_child < 0){
            exit(EXIT_FAILURE);
        }

        if (other_child == 0){
            char *argv[] = {"mkdir", "-p", "/home/syubban/modul2/sedaap", NULL};
            execv("/bin/mkdir", argv);
        }else{
            while(wait(&second_status) > 0);
            pid_t another_childs;
            int another_status;
            another_childs = fork();
        
            if (another_childs < 0){
                exit(EXIT_FAILURE);
            }

            if(another_childs == 0){
                char *argvs[] = {"unzip", "/home/syubban/modul2/jpg.zip", "-d", "/home/syubban/modul2/", NULL};
                execv("/usr/bin/unzip", argvs);
            }else{
                while(wait(&another_status) > 0);
                struct dirent *de;  // Pointer for directory entry 
  
                // opendir() returns a pointer of DIR type.  
                DIR *dr = opendir("/home/syubban/modul2/jpg"); 
  
                if (dr == NULL)  // opendir returns NULL if couldn't open directory 
                { 
                    printf("Could not open current directory" ); 
                    return 0; 
                } 
  
                // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
                // for readdir() 
                while ((de = readdir(dr)) != NULL){ 
                    // printf("%s\n", de->d_name);
                    char temp[100] = "\0";
                    strcpy(temp, "/home/syubban/modul2/jpg/");
                    strcat(temp, de->d_name);
                    char *argss[] = {"mv", temp, "/home/syubban/modul2/indomie/", NULL};
                    execv("/bin/mv", argss); 
                }
                closedir(dr);
            }
        }
    }
}
