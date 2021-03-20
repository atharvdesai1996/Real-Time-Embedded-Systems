


#define _GNU_SOURCE
#include <pthread.h>
#include <sched.h>
#include <semaphore.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define NSEC_PER_SEC (1000000000)
#define NSEC_PER_MSEC (1000000)
#define NSEC_PER_MICROSEC (1000)
#define DELAY_TICKS (1)
#define ERROR (-1)
#define OK (0)

unsigned int idx = 0, jdx = 1;
#define FIB_LIMIT_FOR_32_BIT 47
#define FIB_LIMIT (10)
sem_t semFib1,semFib2;
unsigned int seqiterations = FIB_LIMIT_FOR_32_BIT
unsigned int fib = 0, fib0 = 0, fib1 = 1;
int rt_max_prio, rt_min_prio;
pid_t mainpid;
pthread_t fib10msec, fib20msec;
pthread_attr_t attfi_1;
pthread_attr_t attfi_2;
pthread_attr_t main_att;
struct sched_param paramrt_fib1;
struct sched_param paramrt_fib2;
struct sched_param main_param;
int abort_10 = 0, abort_20;
#define FIB_TEST(seqCnt, iterCnt)      \
   for(idx=0; idx < iterCnt; idx++)    \
   {                                   \
      fib = fib0 + fib1;               \
      while(jdx < seqCnt)              \
      {                                \
         fib0 = fib1;                  \
         fib1 = fib;                   \
         fib = fib0 + fib1;            \
         jdx++;                        \
      }                                \
   }                                   \

typedef struct
{
    int threadIdx;
} threadParams_t;


double current_time(void) 
{   
struct timer t;   
double counter=0.0;      
counter = ((double)(((double)t.tv_sec) + (((double)t.tv_usec) / 1000000.0)));      
return counter; 
}

int delta_t(struct timespec *stop, struct timespec *start, struct timespec *delta_t)
{
  int dt_sec=stop->tv_sec - start->tv_sec;
  int dt_nsec=stop->tv_nsec - start->tv_nsec;

  if(dt_sec >= 0)
  {
    if(dt_nsec >= 0)
    {
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }
    else
    {
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }
  else
  {
    if(dt_nsec >= 0)
    {
      delta_t->tv_sec=dt_sec;
      delta_t->tv_nsec=dt_nsec;
    }
    else
    {
      delta_t->tv_sec=dt_sec-1;
      delta_t->tv_nsec=NSEC_PER_SEC+dt_nsec;
    }
  }

  return(1);
}

void *fibo_10ms(void *threadno) 
{ 
struct sched_param param; 
int j; 
double start_t = 0.0; 
double stop_t = 0.0;
unsigned long proc_0 = 1;

while(! abort_10)
{
	sem_wait(&semFib1);
	self_thread = pthread_self();
	FIB_TEST( seqIterations , 100000);
	pthread_setaffinity_np(self_thread, sizeof(proc_0),&proc_0);
	stop_t = current_time();
	total_exec = current_time() - start_t;

}
}

void *fibo_20ms(void *threadno) 
{ 
struct sched_param param; 
int j; 
double start_t = 0.0; 
double stop_t = 0.0;
unsigned long proc_0 = 1;

while(! abort_20)
{
	sem_wait(&semFib2);
	self_thread = pthread_self();
	FIB_TEST( seqIterations , 200000);
	pthread_setaffinity_np(self_thread, sizeof(proc_0),&proc_0);
	stop_t = current_time();
	total_exec = current_time() - start_t;

}
}

void print_scheduler(void)
{
   int schedType;

   schedType = sched_getscheduler(getpid());

   switch(schedType)
   {
     case SCHED_FIFO:
           printf("Pthread Policy is SCHED_FIFO\n");
           break;
     case SCHED_OTHER:
           printf("Pthread Policy is SCHED_OTHER\n");
       break;
     case SCHED_RR:
           printf("Pthread Policy is SCHED_OTHER\n");
           break;
     default:
       printf("Pthread Policy is UNKNOWN\n");
   }

}


int main(void)
{

int var1, scope, j;
micro_sec f_10=10000,f_20=20000;

sem_init(&semFib1,0,1);     
sem_init(&semFib2,0,1); 

rt_max_prio = sched_get_priority_max(SCHED_FIFO);   
rt_min_prio = sched_get_priority_min(SCHED_FIFO); 
pthread_attr_init(& attfi_1 ); 
pthread_attr_init(& attfi_2 );   
pthread_attr_init(& main_att );   
pthread_attr_setinheritsched(& attfi_1 , PTHREAD_EXPLICIT_SCHED);  
pthread_attr_setschedpolicy(& attfi_1 , SCHED_FIFO);   
pthread_attr_setinheritsched(& attfi_2 , PTHREAD_EXPLICIT_SCHED);   
pthread_attr_setschedpolicy(& attfi_2 , SCHED_FIFO);   
pthread_attr_setinheritsched(& main_att , PTHREAD_EXPLICIT_SCHED);   
pthread_attr_setschedpolicy(& main_att , SCHED_FIFO); 

pthread_create(&fib10msec,&attfi_1,&fibo_10ms(void *)0);

pthread_create(&fib20msec,&attfi_2,&fibo_20ms(void *)0);

usleep  (f_20);       
sem_post  (&semFib1);    
usleep  (f_20);    
sem_post  (&semFib1);    
usleep  (f_10);    
abortTest_20 = 1;  
sem_post  (&semFib2);    
usleep  (f_10);    
sem_post  (&semFib1);    
usleep  (f_20);    
abort_10 = 1;  
sem_post  (&semFib1);    
usleep  (f_20);    
}