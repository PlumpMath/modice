#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <signal.h>

#include "ku_pir_lib.h"

int main(int argc, char *argv[]){
  int i, rst, fd;
  long unsigned start;
  ku_pir_data *(*fns[])(int, long unsigned int) = {ku_pir_asynchronous, ku_pir_nonblocking, ku_pir_blocking};
  char *fn_names[] = {"asynchronous","nonblocking","blocking"};
  struct sigaction act = {.sa_sigaction=sig_handler, .sa_flags=SA_SIGINFO};
  time_t now = time(NULL);

// initialization
  srand(now); //seed randoms

  sigemptyset(&act.sa_mask);
  sigaction(SIGUSR1, &act, NULL);

  fd = ku_pir_open();
// asserts action on no data situation
  for(i=0;i<sizeof(fns)/sizeof(int*);i++)
    assert(!fns[i](fd,now)); // fail : no data

  printf("assertions succeed. timestamp of now:%lu\n", (unsigned long) now);
  start = now - 1*DAY;
  for(i=0; i<1024;i++){
    long unsigned fall = RANDRANGE((start+=10*SEC), start + 10*SEC);
    long unsigned rise = fall - RANDRANGE(1*SEC, 7*SEC);
    if (fall >= now) break;
    printf("filling with %lu - %lu : %d, %d\n", rise, fall, ku_pir_insertData(fd, (long unsigned int)rise, RISING), ku_pir_insertData(fd, (long unsigned int)fall, FALLING));
  }

  for(i=0; i<sizeof(fns)/sizeof(int*); i++){
    int j;
    for(j=0;j<5;j++){
      time_t trgtime = start + 2*HOUR + j*40*MIN - 10*SEC;
      ku_pir_data *rst = 0;
      while ((rst=fns[i](fd, trgtime))==0); //auto retry on error
      //assert(0 != rst); // has returned a data
      printf("%s on %s is the nearest of %s which have read with %s\n", rf_flag_name(rst->rf_flag), ctime(&rst->timestamp), ctime(&trgtime), fn_names[i]);
    }
  }

  return ku_pir_close(fd);
}