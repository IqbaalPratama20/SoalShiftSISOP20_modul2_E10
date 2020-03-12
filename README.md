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
```c
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

```

**Penjelasan :**
```c
int main(int argc, char **argv){
    1) if (argc-1 > 4 || argc-1 < 4){
        printf("Terjadi kesalahan input\n");
    2) else{
    3)   if ( (strcmp(argv[1], "*") == 0) || (strcmp(argv[1], "0") >= 0 && strcmp(argv[1],"59") <= 0) )
    4)    if ( (strcmp(argv[2], "*") == 0) || (strcmp(argv[2], "0") >= 0 && strcmp(argv[2],"59") <= 0) )
    5)     if ( (strcmp(argv[3], "*") == 0) || (strcmp(argv[3], "0") >= 0 && strcmp(argv[3],"23") <= 0) )
    6)      if (pattern_check(argv[4]) == 1)
             service_maker(argv[1], argv[2], argv[3], argv[4]);
     
}
```
Pertama kita melakukan input melalui argumen pada terminal, pada c kita menambahkan **int argc** sebagai penampung banyaknya argumen pada terminal dan **char \*\*argv** sebagai array dari setiap argumen (dipisahkan dengan spasi untuk setiap insert nya) contoh nya ./program \* 34 7 /home/somi/test.sh maka :
1)./program adalah isi dari argv[0]
2) \* adalah isi dari argv[1] 
3) 34 adalah isi dari argv[2]
4) 7 adalah isi dari argv[3]
5) /home/somi/test.sh adalah isi dari argv[4]
kemudian  dilakukan pengecekan pertama untuk yang nomor 1) yaitu jika argumen-1 yang diberikan > 4 atau argumen-1 yang diberikan < 4 maka akan mencetak "Terjadi kesalahan input", argc -1 kami anggap dikurangi dengan ./program nya.
Ketika program program sukses melewati pengecekan pertama lalu lanjut ke :

1 ) pengecekan kedua ( pada no 2) ) yaitu  melakukan cek ke argumen ke 1 (bagian detik) dengan kondisi input akan diterima ketika sama dengan "*" atau diantara 0 dan 59 dengan membandingkan (strcmp) input dengan karakter 0 dan 59. Ketika hasil strcmp dengan "0" >= 0 (0 sendiri atau 1, ketika -1 maka itu kurang dari 0) maka input dianggap benar dengan batasan strcmp dengan "59" <= 0 (hasil strcmp diterima ketika 0 atau -1, ketika 1 maka itu melebihi 59) . Jika tidak memenuhi salah satu dari kedua pengecekan maka akan output "Terjadi kesalahan pada argumen 1".

2 ) pengecekan ketiga ( pada no 3) ) dengan syarat pengecekan kedua berhasil, yaitu  melakukan cek ke argumen ke 2 (bagian menit) dengan kondisi input akan diterima ketika sama dengan "*" atau diantara 0 dan 59 dengan membandingkan (strcmp) input dengan karakter 0 dan 59. Ketika hasil strcmp dengan "0" >= 0 (0 sendiri atau 1, ketika -1 maka itu kurang dari 0) maka input dianggap benar dengan batasan strcmp dengan "59" <= 0 (hasil strcmp diterima ketika 0 atau -1, ketika 1 maka itu melebihi 59) . Jika tidak memenuhi salah satu dari kedua pengecekan maka akan output "Terjadi kesalahan pada argumen 2".

3 ) pengecekan keempat ( pada no 4) ) dengan syarat pengecekan ketiga berhasil, yaitu  melakukan cek ke argumen ke 3 (bagian jam) dengan kondisi input akan diterima ketika sama dengan "*" atau diantara 0 dan 23 dengan membandingkan (strcmp) input dengan karakter 0 dan 59. Ketika hasil strcmp dengan "0" >= 0 (0 sendiri atau 1, ketika -1 maka itu kurang dari 0) maka input dianggap benar dengan batasan strcmp dengan "23" <= 0 (hasil strcmp diterima ketika 0 atau -1, ketika 1 maka itu melebihi 23) . Jika tidak memenuhi salah satu dari kedua pengecekan maka akan output "Terjadi kesalahan pada argumen 3".

4 ) Ketika argumen ke 1, 2, dan 3 mendapat input huruf atau kata sudah pasti gagal karena ascii minimum untuk huruf kecil adalah 97 dan huruf besar 65 ( otomatis melebihi ) sedangkan maksimum hanya 59. 

5 ) pengecekan terakhir ( pada no 5) ) dengan syarat pengecekan keempat berhasil, yaitu melakukan cek ke argumen ke 4 (bagian path) dengan kondisi input akan dipassing pada fungsi :
```c
pattern_check(argv[4]) //isinya
pattern_check(char *paths){
	1) FILE *file;
    2) if ((file = fopen(paths, "r")))
	   {
    3)    fclose(file);
    4)    return 1;
	   }
    5) return 0;
}
```
kami menggunakan FILE *file default
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

```c
    if(is_dir(temp))
    {
        pid_t next_childs;
        int next_status;
        next_childs = fork();
```
Pada kode tersebut dicek apakah isi dari ``/home/iqbaal/praktikum2/jpg/.`` merupakan file atau directory dengan fungsi ``is_dir`` dan parameter string path ``temp`` dan jika isi tersebut merupakan directory maka dibuat lagi process anak baru dengan pid ``next_childs``

```c
       if (next_childs < 0)
        {
            exit(EXIT_FAILURE);
        }
        if(next_childs == 0)
        {
            char *argss[] = {"mv", temp, "/home/iqbaal/praktikum2/indomie/", NULL};
            subv("/bin/mv", argss);
        }
```
Pada kode tersebut dicek apakah pembuatan proses baru berhasil, jika ternyata berhasil maka directory tersebut akan dipindah ke ``/home/iqbaal/praktikum2/indomie/`` dengan menggunakan fungsi subv dan argumen yang dimasukkan yaitu selain perintah ``mv`` yaitu string temp sebagai directory asal dan ``/home/iqbaal/praktikum2/indomie/`` sebagai directory tujuan

```c
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
```
Ketika ternyata proses masih ada di parent dilakukan perintah di atas, dimana perintah  ``while(wait(&next_status) > 0);`` digunakan untuk menunggu anak menyelesaikan prosesnya (memindahkan ke directory indomie) kemudian dideklarasikan pid baru ``next_gen_childs`` untuk nantinya digunakan membuat proses baru lagi. Setelah itu dideklarasikan dua string baru ``aa`` dan ``bb`` untuk nantinya menyimpan string path file yang akan dimasukkan ke directory. Setelah itu 
``strcpy(aa,"/home/iqbaal/praktikum2/indomie/");`` digunakan untuk meletakkan string path ``/home/iqbaal/praktikum2/indomie/`` ke string ``aa``, ``strcat(aa, de->d_name);`` digunakan untuk meng-append nama directory yang akan diisi ke string aa. Dan ``strcat(aa,"/coba1.txt");`` digunakan untuk meng-append nama file ke string aa. Hal yang sama juga dilakukan untuk string ``bb``. Dimana perbedaannya string ``bb`` digunakan untuk file ``coba2.txt``. Setelah itu baru dilakukan fork() untuk membuat proses baru

```c
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
```
Setelah itu dilakukan pengecekan lagi proses baru tersebut berhasil dibuat atau tidak. Jika berhasil atau ``next_gen_childs == 0`` maka dilakukan perintah ``touch`` dengan ``execv`` untuk membuat file ``coba1.txt`` dengan parameter yang digunakan perintah ``touch`` sendiri dan string ``aa`` yang berisi path tujuan pembuatan file ``coba1.txt``. Namun jika ternyata pid masih ada di parent, maka dilakukan perintah di bagian ``else`` tersebut dimana ``while(wait(&next_gen_status) > 0);`` digunakan untuk menunggu proses anak selesai (membuat file coba1). ``sleep(3)`` digunakan untuk mendelay proses pada parent selama 3 detik sesuai ketentuan soal dan kemudian baru dibuat file ``coba2.txt`` dengan bantuan perintah ``touch`` dengan ``execv`` dengan parameter yang digunakan perintah ``touch`` sendiri dan string ``bb`` yang berisi path tujuan pembuatan file ``coba2.txt``.
```c
    else
    {
        char *argss[] = {"mv", temp, "/home/iqbaal/praktikum2/sedaap/", NULL};
        subv("/bin/mv", argss); 
    }
```
Sedangkan perintah terakhir diatas digunakan ketika isi dari directory ``/home/iqbaal/praktikum2/jpg/`` adalah file bukan directory sehingga dilakukan pemindahan file tersebut ke folder ``/home/iqbaal/praktikum2/sedaap/`` dengan bantuan ``execv`` dengan parameter yang digunakan yaitu perintah ``mv`` , ``temp`` sebagai string path file yang akan dipindah dan ``/home/iqbaal/praktikum2/sedaap/`` sebagai directory tujuan.

**Screenshot Run :**
<hr>
