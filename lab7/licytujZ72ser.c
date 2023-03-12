#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define N_AGENTS 20
#define N_ITEMS 20
#define OPENING_BID 100
#define MAX_RAISE 10
#define BIDDING_ROUNDS 10


#define SHM_ID  259550 
#define MEM_SIZE  4096

static clock_t st_time;
static clock_t en_time;
static struct tms st_cpu;
static struct tms en_cpu;

#define GNIAZDKO_SERWERA "/tmp/QWERTYuiop123"

void start_clock()
{
	st_time = times(&st_cpu);
}

void end_clock()
{
	en_time = times(&en_cpu);
	

	float RTC_TIME =  (float)(en_time - st_time)/(float)sysconf(_SC_CLK_TCK);
	float CPU_TIME =  (float)(en_cpu.tms_utime + en_cpu.tms_cutime)/(float)sysconf(_SC_CLK_TCK);
	float CPU_SYSTEM = (float)(en_cpu.tms_stime + en_cpu.tms_cstime)/(float)sysconf(_SC_CLK_TCK);


	printf("Czas RTC: %.3f s\nCzas CPU USER %.3f s\nCzas CPU SYSTEM: %.3f s\n",RTC_TIME,CPU_TIME,CPU_SYSTEM);

}






struct common_struct {
	 int  Bids[N_ITEMS];
	 int Nbids[N_ITEMS];
};




int main(int argc , char *argv[]) 
{
	 int *Bids , *NBids;
	int i, j, k,sock;
	long int sum = 0, sum_Bids = 0;	
	int num,numer;
	long int wart;
	long int licznik = 0;	
	socklen_t serv_len, cli_len;
	struct sockaddr_un serv_addrstr, cli_addrstr;
	char buf[BUFSIZ]; /* bufor o domysl.rozm.*/
	Bids = (int *) malloc(sizeof(int)*N_ITEMS);	
	NBids = (int *) malloc(sizeof(int)*N_ITEMS);	

	sock = socket(PF_UNIX,SOCK_DGRAM,0);
	serv_addrstr.sun_family = AF_UNIX;
	strcpy(serv_addrstr.sun_path,GNIAZDKO_SERWERA);		


	serv_len = sizeof(serv_addrstr);
	if (-1==bind(sock, (struct sockaddr *)&serv_addrstr, serv_len)) {
    		perror("blad bind");
    		exit(-1);
  	}	
	for (int i = 0; i < N_ITEMS; i++)
	{
		Bids[i] = OPENING_BID;
		NBids[i] = 0;
	}
	
	start_clock();
	
	

		
	
	

	while(1) {

	  recvfrom(sock, buf, sizeof(buf),0,(struct sockaddr *)&serv_addrstr,&serv_len);
	  memcpy((void *)&num,(void *)buf,sizeof(int));
	  memcpy((void *)&wart,(void *)buf+sizeof(int),sizeof(int));
	  if(num == -1){
	        printf("Otrzymano Wiadomosc zakonczenia licytacji\n");
       		 break;
          }

	  Bids[num] += wart;
          ++NBids[num];
          licznik = licznik + 1;
//	  printf("Otrzymane podbicie przedmiot =%d wartosc = %d numer podbicia: %d\n", num, wart,licznik);
//	if(num == -1){
//	printf("Otrzymano Wiadomosc zakonczenia licytacji");
//	exit(0);
//	}
	
	  
	}
	
	end_clock();

	for (int k = 0; k < N_ITEMS; k++)
	{	
		sum += Bids[k];
		sum_Bids += NBids[k]; 
		printf("Wartosc przedmiotu nr %d wynosi %d liczba podbic tego przedmiotu wynosi %d \n", k,Bids[k],NBids[k]);
	}
 
	printf("suma wartosci przedmitow wynosi: %d\n",sum);
	printf("suma podbic wszystkich uzytkownikow wynosi %d\n",sum_Bids );
	return 0;
}




