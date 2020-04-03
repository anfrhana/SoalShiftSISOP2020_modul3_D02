#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<dirent.h>

pthread_t tid[100];
char cwd[1024];

int isdir(const char *path)
{
	struct stat stat_t;
	stat(path, &stat_t);
	return S_ISREG(stat_t.st_mode);
}
//fungsi untu mengecek dan memindahkan file
void* pindah(void *arg) {
//	strcpy(abc,arg);
//	char *flag,*flag2;

//	unsigned long i=0;
//	pthread_t id = pthread_self();
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
//fungsi untuk memindahkan file dari direktori a ke directori tempat file
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

//	char source[1024], target[1024];

//	strcpy(source,arg);
//	strcpy(target,workdir);
//	strcat(target,"/");
//	if(n == 1 ){
//		strcat(target,"Unknown");
//	}
//	else{
//		strcat(target,namafile);
//	}
//		strcat(target,"/");
//		strcat(target,arr3);
//		rename(source,target);

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

int main(int argc, char *argv[]) {

	getcwd(cwd, sizeof(cwd));
	//print letak direktori saat ini
	if(getcwd(cwd, sizeof(cwd)) != NULL) {
		printf("%s\n", cwd);
	}

	int i;
	//jika argumen yang dimasukkan *
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
	//jika argumen yang dimasukkan -f
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
	//jika argumen yang dimasukkan -d
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
		//jika direktori tidak ada
		else if (dr == NULL) {
			printf("Direktori tidak dapat ditemukan" );
		}
	}
	//jika argumen yang diinputkan tidak sesuai
	else {
		printf("argumen salah\n");
	}

	return 0;
}
