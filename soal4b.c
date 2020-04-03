#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>

int jmlh[10][10];

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
