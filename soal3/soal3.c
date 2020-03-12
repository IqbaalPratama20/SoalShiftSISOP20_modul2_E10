#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h> 

#include <sys/stat.h>


int is_dir(const char* path) {
    struct stat buf;
    stat(path, &buf);
    return S_ISDIR(buf.st_mode);
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

int main() {
    pid_t child_id;
    int status;

    child_id = fork();
  
    if (child_id < 0) {
        exit(EXIT_FAILURE); // Jika gagal membuat proses baru, program akan berhenti
    }

    if (child_id == 0) {
        // this is child  
        char *argv[] = {"mkdir", "-p", "/home/iqbaal/praktikum2/indomie", NULL};
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
            char *argv[] = {"mkdir", "-p", "/home/iqbaal/praktikum2/sedaap", NULL};
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
                char *argvs[] = {"unzip", "/home/iqbaal/praktikum2/jpg.zip", "-d", "/home/iqbaal/praktikum2/", NULL};
                execv("/usr/bin/unzip", argvs);
            }else{
                while(wait(&another_status) > 0);
                struct dirent *de;  // Pointer for directory entry 
  
                // opendir() returns a pointer of DIR type.  
                DIR *dr = opendir("/home/iqbaal/praktikum2/jpg"); 
  
                if (dr == NULL)  // opendir returns NULL if couldn't open directory 
                { 
                    printf("Could not open current directory" ); 
                    return 0; 
                } 
  
                // Refer http://pubs.opengroup.org/onlinepubs/7990989775/xsh/readdir.html 
                // for readdir() 
                while ((de = readdir(dr)) != NULL){ 
                    char temp[100] = "\0";
                    strcpy(temp, "/home/iqbaal/praktikum2/jpg/");
                    strcat(temp, de->d_name);
                    char a[50];
                    char b[50];
                    strcpy(a, "/home/iqbaal/praktikum2/jpg/..");
                    strcpy(b, "/home/iqbaal/praktikum2/jpg/.");
                    if(strcmp(temp,a)==0 || strcmp(temp,b)==0)
                    {
                        continue;
                    }
                    if(is_dir(temp))
                    {
                        pid_t next_childs;
                        int next_status;
                        next_childs = fork();
                        if (next_childs < 0)
                        {
                            exit(EXIT_FAILURE);
                        }

                        if(next_childs == 0)
                        {
                            char *argss[] = {"mv", temp, "/home/iqbaal/praktikum2/indomie/", NULL};
                            subv("/bin/mv", argss);
                        }
                        else
                        {
                            while(wait(&next_status) > 0);
                            pid_t next_gen_childs;
                            int next_gen_status;
                            char aa[50];
                            strcpy(aa,"/home/iqbaal/praktikum2/indomie/");
                            strcat(aa, de->d_name);
                            strcat(aa,"/coba1.txt");
                            char bb[50];
                            strcpy(bb,"/home/iqbaal/praktikum2/indomie/");
                            strcat(bb, de->d_name);
                            strcat(bb,"/coba2.txt");

                            next_gen_childs = fork();

                            if (next_gen_childs < 0)
                            {
                                exit(EXIT_FAILURE);
                            }

                            if(next_gen_childs == 0)
                            {
                                char *argss[] = {"touch", aa, NULL};
                                execv("/bin/touch", argss);
                            }
                            else
                            {
                                while(wait(&next_gen_status) > 0);
                                sleep(3);
                                char *argss[] = {"touch", bb, NULL};
                                execv("/bin/touch", argss);
                            } 
                        }
                    }
                    else
                    {
                        char *argss[] = {"mv", temp, "/home/iqbaal/praktikum2/sedaap/", NULL};
                        subv("/bin/mv", argss); 
                    }
                }
                closedir(dr);
            }
        }
    }
}