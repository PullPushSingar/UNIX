#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>







#define N_AGENTS 20
#define N_ITEMS 20
#define OPENING_BID 100
#define MAX_RAISE 10
#define BIDDING_ROUNDS 1000000
#define SHM_ID  259550 
#define MEM_SIZE  4096


struct common_struct {
	 int  Bids[N_ITEMS];
	 int Nbids[N_ITEMS];
};


int main(int argc , char *argv[]) 
{
	 int *Bids , *NBids;
	void *common_memory = (void *)0;
	struct common_struct *common;
	int shmid;
	int i, j, k;
	long int sum = 0, sum_Bids = 0;	
	srand((unsigned int)getpid());
	
	key_t shmkey = ftok("/home/hkowalcz/ezi_unix/lab_6_programy/licytuj.c",2);

	shmid = shmget(shmkey , MEM_SIZE, 0666 | IPC_CREAT);

	if (shmid == -1) 
	{
		exit(1);
	}


	common = (struct common_struct *) shmat(shmid, (void *)0,0);
	if (common == (void *)-1)
	{
		exit(2);
	}
	
	
	Bids = common -> Bids;
        NBids = common -> Nbids;

	
	for (int i = 0; i < N_ITEMS; i++)
	{
		Bids[i] = OPENING_BID;
		NBids[i] = 0;
	}

	




	for (j = 0; j < BIDDING_ROUNDS; j ++)
	{		
		int  N = rand() %  N_ITEMS ;
		int  R = rand() % (MAX_RAISE + 1);
		Bids[N] = Bids[N] + R;
		NBids[N] = NBids[N] + 1 ;

	}

	for (k = 0; k < N_ITEMS; k++)
	{	
		sum += Bids[k];
		sum_Bids += NBids[k]; 
		printf("Wartosc przedmiotu nr %d wynosi %d liczba podbic tego przedmiotu wynosi %d \n", k,Bids[k],NBids[k]);
	}
 
	printf("suma wartosci przedmitow wynosi: %d\n",sum);
	printf("suma podbic wszystkich uzytkownikow wynosi %d\n",sum_Bids );
	return 0;
}

