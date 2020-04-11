Kelompok D02
- 5111840000120	-	Aflakah Nur Farhana
- 5111840000165	-	Muhammad Fikri Rabbani


**Soal 1**


**Soal 2**


**Soal 3**
Buatlah sebuah program dari C untuk mengkategorikan file. Program ini akan memindahkan file sesuai ekstensinya (tidak case sensitive. JPG dan jpg adalah sama) ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan

opsi `-f`

Pada opsi -f tersebut, user bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang user inginkan seperti contoh di atas.Pada program kategori tersebut, folder jpg,c,zip tidak dibuat secara manual, melainkan melalui program c. Semisal ada file yang tidak memiliki ekstensi,maka dia akan disimpan dalam folder “Unknown”.
```
else if(strcmp(argv[1], "-f") == 0) {
		for(i = 2; i < argc; i++) {
			if(isdir(argv[i])) {
				//membuat thread
				pthread_create(&(tid[i-2]), NULL, pindah, (void *)argv[i]);
			}
		}
		for(i = 0; i < argc - 2; i++) {
			//join thread
			pthread_join(tid[i], NULL);
		}
	}
```

opsi `*`

Mengkategori seluruh file yang ada di working directory ketika menjalankan program C tersebut.
```
if(strcmp(argv[1], "*") == 0 && argc == 2) {
		DIR *dr;
		struct dirent *d;
		dr = opendir(".");

		//jika direktori ada
		if (dr != NULL) {
		i = 0;
			char workd[1024], subdir[1024];
			getcwd(workd, sizeof(workd));
			while((d = readdir(dr)) != NULL){
				//if ( !strcmp(d->d_name, ".") || !strcmp(d->d_name, "..") )continue;
				if(isdir(d->d_name)) {
					strcpy(subdir, workd);
					strcat(subdir, "/");
					strcat(subdir, d->d_name);
					//printf("%s", subdir);
					//membuat thread
					pthread_create(&(tid[i]), NULL, pindah, (void *)subdir);
					//join thread
					pthread_join(tid[i], NULL);
					i++;
				}
			}
			closedir(dr);
		}
		//jika direktori tidak ada
		else if (dr == NULL) {
			printf("Direktori tidak dapat ditemukan" );
		}
	}
```

opsi `-d`

Hasilnya perintah di atas adalah mengkategorikan file di /path/to/directory dan hasilnya akan disimpan di working directory di mana program C tersebut berjalan (hasil kategori filenya bukan di /path/to/directory).
```
else if(strcmp(argv[1], "-d") == 0 && argc == 3) {
		chdir(argv[2]);
		DIR *dr;
		struct dirent *d;
		dr = opendir(".");

		//jika direktori ada
		if (dr != NULL) {
			i = 0;
			char workd[1024], subdir[1024];
			getcwd(workd, sizeof(workd));
			while((d = readdir(dr)) != NULL){
				//if ( !strcmp(d->d_name, ".") || !strcmp(d->d_name, "..") )continue;
				if(isdir(d->d_name)) {
					strcpy(subdir, workd);
					strcat(subdir, "/");
					strcat(subdir, d->d_name);
					//membuat thread
					pthread_create(&(tid[i]), NULL, pindahd, (void *)subdir);
					//join thread
					pthread_join(tid[i], NULL);
					i++;
				}
			}
			closedir(dr);
		}
```

Program ini tidak rekursif. Semisal di directory yang mau dikategorikan, atau menggunakan `*` terdapat folder yang berisi file, maka file dalam folder tersebut tidak dihiraukan, cukup file pada 1 level saja.
Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat. Dilarang menggunakan fork-exec dan system.
fungsi untuk mengecek apakah sebuah direktori atau bukan
```
int isdir(const char *path)
{
	struct stat stat_t;
	stat(path, &stat_t);
	return S_ISREG(stat_t.st_mode);
}
```

fungsi untuk mengecek dan memindahan file
Dimana nantinya akan membuka kedua path yang sudah di dapatkan sebelumnya. file yang lama dibuka dalam mode read dan file baru kemudian akan dibuat dengan menggunakan write. Lalu semua isi yang ada pada file lama akan dipindah kan dengan menggunakan `fputc( )`. kemudian delet file lama dengan `remove()`.
```
void* pindah(void *arg) {
	char *path;
	char format[100], dirname[100], a[100], b[100], namafile[100];
	
	path = (char *) arg;
	strcpy(a, arg); //copy string arg ke dalam a
	strcpy(b, arg);//copy string arg ke dalam b
	
	char *tmp, *arr[5], *tmp2, *arr2[5];
	int n = 0;
	tmp = strtok(path, "."); //mengambil path .

	while(tmp != NULL) {
		arr[n] = tmp;
		n++;
		tmp = strtok(NULL, "."); //memisahkan path .
	}
	//file memiliki format
	if(n != 1) {
		int a;
		for(a = 0; a < strlen(arr[n-1]); a++) {
		format[a] = tolower(arr[n-1][a]);
	}
	
	}
	//jika file tidak memiliki format
	else if (n == 1) {
		strcpy(format, "Unknown");
		//printf("masuk\n");
	}

	n = 0;
	tmp2 = strtok(b, "/"); //mengambil path /
	while(tmp2 != NULL) {
		arr2[n] = tmp2;
		n++;
		tmp2 = strtok(NULL, "/"); //memisahkan path /
	}
	strcpy(namafile, arr2[n-1]);//mengcopy isi dari arr ke dalam namafile

	char workdir[1024];
	getcwd(workdir, sizeof(workdir));//mendapatkan alamat  current work directory
	strcpy(dirname, workdir);//mengcopy isi workdir ke dirname
	strcat(dirname, "/");//menggabung string
	strcat(dirname, format);//menggabung string

	printf("|-%s\n", format);//mencetak format file
	printf("|--%s\n", namafile);//mencetak nama file beserta ekstensinya

	memset(format, 0, 100);
	mkdir(dirname, 0777); //membuat direktori

	FILE *pread, *pwrite;
	pread = fopen(a, "r");
	strcat(dirname, "/");
	strcat(dirname, namafile);
	//printf("|--%s\n", namafile);
	pwrite = fopen(dirname, "w");

	int ch;
	while ((ch = fgetc(pread)) != EOF) {
		fputc(ch, pwrite);
	}
	fclose(pread); //tutup file yang ditunjukpointer pread 
	fclose(pwrite); //tutup file yang ditunjuk pointer write
	remove(a);

	return NULL;
}
```
fungsi untuk meengecek dan meindahkan dile dari direktori lain ke direktori tempat file soal3.c disimpan
```
void* pindahd(void *arg) {
	char *path;
	char format[100], dirname[100], a[100], b[100], namafile[100];
	path = (char *) arg;
	strcpy(a, arg);
	strcpy(b, arg);
	char *tmp, *arr[5], *tmp2, *arr2[5];
	int n = 0;
	tmp = strtok(path, ".");
	while(tmp != NULL) {
		arr[n] = tmp;
		n++;
		tmp = strtok(NULL, ".");
	}
	if(n != 1) {
		int a;
		for(a = 0; a < strlen(arr[n-1]); a++) {
			format[a] = tolower(arr[n-1][a]);
			//printf("masuk\n");
		}
		
	}
	else if ( n == 1) {
		strcpy(format, "Unknown");
		//printf("masuk\n");
	}

	n = 0;
	tmp2 = strtok(b, "/");
	while(tmp2 != NULL) {
		arr2[n] = tmp2;
		n++;
		tmp2 = strtok(NULL, "/");
		//printf("pppp\n");
	}
	strcpy(namafile, arr2[n-1]);

	strcpy(dirname, cwd);
	strcat(dirname, "/");
	strcat(dirname, format);
	printf("|-%s\n", format); //mencetak format file
	printf("|--%s\n", namafile); //mencetak namafile beserta ekstensinya
	memset(format, 0, 100);
	mkdir(dirname, 0777);

	FILE *pread, *pwrite;
	pread = fopen(a, "r");
	strcat(dirname, "/");
	strcat(dirname, namafile);
	pwrite = fopen(dirname, "w");
	return NULL;
	int ch;
	while ((ch = fgetc(pread)) != EOF) {
		fputc(ch, pwrite);
	}
	fclose(pread);
	fclose(pwrite);
	remove(a);

	return NULL;
}
```
**Soal 4**

4a.Buatlah program C dengan nama "4a.c", yang berisi program untuk melakukan perkalian matriks. Ukuran matriks pertama adalah 4x2, dan matriks kedua 2x5. Isi dari matriks didefinisikan di dalam kodingan. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).Tampilkan matriks hasil perkalian tadi ke layar.

dibuat 3 variable matriks, 2 matriks digunakan untuk menyimpam nilai matriks yang akan dikalikan, matriks satu lagi digunakan untuk menyimpan hasil dari kedua matriks yang telah dikalikan.

```
int matA[4][2] = {{1, 2}, 
		  {3, 4}, 
		  {1, 1},
		  {1, 6}};
int matB[2][5] = {{5, 6, 7, 8, 1},
		  {9, 1, 8, 1, 1}};
int matC[4][5];
```
Dibuat sebuah struct untuk menyimpan indeks matriks.
```
struct matriks
{
    int i;
    int j; 
};
```
fungsi untuk melakukan perkalian dua buah matriks.
```
void *mult(void *ptr)
{    
    struct matriks *data = ptr;
    int i, sum = 0;
    
    for(i = 0; i < 2; i++)
    {  
//	printf("%d %d\n", data->i, data->j); 
        sum += matA[data->i][i] * matB[i][data->j];
    }
    
    matC[data->i][data->j] = sum;
    pthread_exit(0);
}
```
fungsi main
```
int main(int argc, char **argv)
{
    int i, j ,n = 0,cnt = 0, *nilai;
    key_t key = 1234;

    printf ("Matriks A\n");
    for (i = 0; i < 4; i++){
	for (j = 0; j < 2; j++){
        printf ("%d\t", matA[i][j]);
    }
	printf("\n");
    }

    printf ("\nMatriks B\n");
    for (i = 0; i < 2; i++){
	for (j = 0; j < 5; j++){
        printf ("%d\t", matB[i][j]);
    }
	printf("\n");
    }

    int shmid = shmget(key, 20, IPC_CREAT | 0666);
    nilai = (int *)shmat(shmid, 0, 0);

    pthread_t tid;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++) 
        {
            struct matriks *data = (struct matriks *) malloc(sizeof(struct matriks));
            data->i = i;
            data->j = j;
	
            pthread_create(&tid, NULL, mult, data);
            pthread_join(tid, NULL);
        }
    }

    printf ("\nHasil perkalian matriks\n");
    for(i = 0; i < 4; i++)
    { 
        for(j = 0; j < 5; j++)
        { 
            printf("%d\t", matC[i][j]);
            nilai[n] = matC[i][j];
            n++;
        }
        printf("\n");
    }

    shmdt((void *) nilai);

    return 0;
}

```
mendeklarasi `shmid` yang digunakan sebagai id memori bersama saat dilakukan shared memory.
```
int shmid = shmget(key, 20, IPC_CREAT | 0666);
nilai = (int *)shmat(shmid, 0, 0);
```

` pthread_t tid;` deklarasi thread.
thread akan digunakan untuk mengambil nilai yang ada pada struct yang kemudian akan digunakan untuk variable dan hasil nya disimpan dalam `matC[][]` .
```
 for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 5; j++) 
        {
            struct matriks *data = (struct matriks *) malloc(sizeof(struct matriks));
            data->i = i;
            data->j = j;
	
            pthread_create(&tid, NULL, mult, data);
            pthread_join(tid, NULL);
        }
    }
```
mencetak hasil perkalian 2 matriks
```
printf ("\nHasil perkalian matriks\n");
    for(i = 0; i < 4; i++)
    { 
        for(j = 0; j < 5; j++)
        { 
            printf("%d\t", matC[i][j]);
            nilai[n] = matC[i][j];
            n++;
        }
        printf("\n");
    }
 ```
` shmdt((void *) nilai);` digunakan untuk melepaskan shared memori.

4b.Buatlah program C kedua dengan nama "4b.c". Program ini akan mengambil variabel hasil perkalian matriks dari program "4a.c" (program sebelumnya), dan tampilkan hasil matriks tersebut ke layar.(Catatan!: gunakan shared memory).Setelah ditampilkan, berikutnya untuk setiap angka dari matriks tersebut, carilah nilai faktorialnya, dan tampilkan hasilnya ke layar dengan format seperti matriks.Harus menggunakan Thread dalam penghitungan
faktorial)

Deklarasi variable global
`int jmlh[10][10];`
Fungsi untuk melakukan penjumlahan
```
void *sum(void *arg)
{
    key_t key = 1234;
    int (*matriks)[10];
	int *nilai;
	int i,j,k,angka;
        int shmid = shmget(key, 20, IPC_CREAT | 0666);
        nilai =(int *) shmat(shmid, 0, 0);
	int n = 0;
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 5; j++) {
		matriks[i][j] = nilai[n];
		n++;	
		while( n == 19 )break;
		}
	}
	
	int tmp = 1;
	for(i = 0; i < 4; i++)
	{ 
		for(j = 0; j < 5; j++)
		{
			angka = matriks[i][j];
			for(k = 1; k <= angka; k++)
			{
				tmp+=k;
				jmlh[i][j] = tmp;
	
			}
			tmp = 1;
		}
	}
```
deklarasi `shmid` pada fungsi `*sum` dengan id yang sama dengan file yang lain sehingga shared memori dapat dilakukan.
```
int shmid = shmget(key, 20, IPC_CREAT | 0666);
nilai = (int *) shmat(shmid, 0, 0);
```
Untuk mencetak hasil penjumlahan
```
	printf("\nHasil penjumlahan\n");
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 5; j++)
		{
			printf("%d\t", jmlh[i][j]);
		}
		printf("\n");
	}
}
```
Fungnsi main
```
void main()
{
    key_t key = 1234;
    int (*matriks)[10], i, j, *nilai, n = 0;

	int shmid = shmget(key, 20, IPC_CREAT | 0666);
    nilai = (int *) shmat(shmid, 0, 0);
	
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 5; j++) {
		matriks[i][j]= nilai[n];
		n++;
	while( n == 19 )break;
	}
}
	printf("MATRIKS\n");

	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 5; j++)
		{
			printf("%d\t", matriks[i][j]);
		}
		printf("\n");
	}

	pthread_t tid;

	pthread_create(&tid, NULL,&sum, NULL);
	pthread_join(tid,NULL);

}
```
deklarasi `shmid` dengan id yang sama dengan file yang lain sehingga shared memori dapat dilakukan.
```
int shmid = shmget(key, 20, IPC_CREAT | 0666);
nilai = (int *) shmat(shmid, 0, 0);
```
Pembuatan hread yang digunakan untuk pehitungan matriks.
```
pthread_t tid;

pthread_create(&tid, NULL,&sum, NULL);
pthread_join(tid,NULL);
```

4c.Buatlah program C ketiga dengan nama "4c.c". Program ini tidak memiliki hubungan terhadap program yang lalu.Pada program ini, Norland diminta mengetahui jumlah file dan folder di direktori saat ini dengan command "ls | wc -l". Karena sudah belajar IPC, Norland mengerjakannya dengan semangat.(Catatan! : Harus menggunakan IPC Pipes)
```
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    int folder[2];
    pid_t id;

    if (pipe(folder)==-1){
        fprintf(stderr, "pipe gagal dilakukan" );
        return 1;
    }
    id = fork();

    if (id < 0){
        fprintf(stderr, "fork gagal dilakukan" );
        return 1;
    }

    else if (id == 0){
        close(1);
        dup(folder[1]);
        close(folder[0]);
        
        char *argm1[] = {"ls", NULL};
        execv("/bin/ls", argm1);
    }
    else{
        wait(NULL);
        close(0);
        dup(folder[0]);
        close(folder[1]);
 
	char *argm2[] = {"wc", "-l", NULL};
        execv("/usr/bin/wc", argm2);
    }
}
```
