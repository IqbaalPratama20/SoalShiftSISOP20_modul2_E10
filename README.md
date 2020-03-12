# SoalShiftSISOP20_modul2_E10
**soal 1 :**  
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan
ketentuan sebagai berikut:
**a.** Program menerima 4 argumen berupa:

 1. Detik: 0-59 atau * (any value)
 2. Menit: 0-59 atau * (any value)
 3. Jam: 0-23 atau * (any value)
 4. Path file .sh
 
**b.** Program akan mengeluarkan pesan error jika argumen yang diberikan tidak
sesuai

**c.** Program hanya menerima 1 config cron

**d.** Program berjalan di background (daemon)

**e.** Tidak boleh menggunakan fungsi system()

Contoh: ./program \* 34 7 /home/somi/test.sh
Program dengan argumen seperti contoh di atas akan menjalankan script test.sh setiap
detik pada jam 07:34.

**Source Code :**

**Penjelasan :**

**Screenshot Run :**
<hr>

**soal 2 :** 
Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia
merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat
sebuah program.
**a.** Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat
sebuah program C yang per 30 detik membuat sebuah folder dengan nama
timestamp [YYYY-mm-dd_HH:ii:ss].

**b.** Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari
https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap
gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah
detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-
mm-dd_HH:ii:ss].

**c.** Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan
folder akan di delete(sehingga hanya menyisakan .zip).

**d.** Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men-
generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri.

**e.** Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu
MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan
dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen
-b. Ketika dijalankan dalam MODE_A, program utama akan langsung
menghentikan semua operasinya ketika program killer dijalankan. Untuk
MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi
membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua
folder terisi gambar, terzip lalu di delete).

Kiwa lalu terbangun dan sedih karena menyadari programnya hanya sebuah mimpi.
Buatlah program dalam mimpi Kiwa jadi nyata!
Catatan:
- Tidak boleh memakai system().
- Program utama harus ter-detach dari terminal
Hint:
- Gunakan fitur picsum.photos untuk mendapatkan gambar dengan ukuran
tertentu
- Epoch Unix bisa didapatkan dari time()

**Source Code :**

**Penjelasan :**

**Screenshot Run :**
<hr>

**soal 3 :** 
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia
memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan
(multiprocessing).

**a.** Program buatan jaya harus bisa membuat dua direktori di
“/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu
lima detik kemudian membuat direktori yang kedua bernama “sedaap”.

**b.** Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori
“/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak
hanya itu tugasnya.

**c.** Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di
dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan
pengelompokan, semua file harus dipindahkan ke
“/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke
“/home/[USER]/modul2/indomie/”.

**d.** Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/”
harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu
3 detik kemudian membuat file bernama “coba2.txt”.
(contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).
Karena Jaya terlalu banyak tugas dia jadi stress, jadi bantulah Jaya agar bisa membuat
program tersebut.
Catatan :
- Tidak boleh memakai system().
- Tidak boleh memakai function C mkdir() ataupun rename().
- Gunakan exec dan fork
- Direktori “.” dan “..” tidak termasuk

**Source Code :**
```c
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
```

**Penjelasan :**
```c
while ((de = readdir(dr)) != NULL){ 
        char temp[100] = "\0";
        strcpy(temp,"/home/iqbaal praktikum2/jpg/");
        strcat(temp, de->d_name);
```
Perintah tersebut yaitu dilakukan perulangan dengan membaca semua setiap isi (file ataupun directory) dari directory jpg tersebut dan nama isi directory tersebut (file ataupun directory) akan ada di d_name pada struct de. Setelah itu dibuat string temp yang isinya path dari setiap isi directory jpg tersebut

```c
        char a[50];
        char b[50];
        strcpy(a, "/home/iqbaal/praktikum2/jpg/..");
        strcpy(b, "/home/iqbaal/praktikum2/jpg/.");
        if(strcmp(temp,a)==0 || strcmp(temp,b)==0)
        {
            continue;
        }
```
Untuk kode tersebut dideklarasikan string a dan string b dimana string a ini memuat path ``/home/iqbaal/praktikum2/jpg/.`` dan ``/home/iqbaal/praktikum2/jpg/..`` dimana pada kedua directory tersebut dilakukan pengecualian sehingga tidak dilakukan apa-apa. Hal tersebut akan jalan ketika perbandingan antara string a atau b dengan string path temp bernilai 0, dilakukan ``continue`` agar langsung masuk ke perulangan selanjutnya

**Screenshot Run :**
<hr>
