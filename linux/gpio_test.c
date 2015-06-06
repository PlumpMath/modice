#include <stdio.h>
//#include <stdlib.h>
//#include <fcntl.h>
//#include <sys/mman.h>
//#include <unistd.h>
//#include <sched.h>
//#include <string.h>
#include <signal.h>
//#include <asm-generic/bug.h>
//#include <stdbool.h> // type bool is needed for linux/gpio.h
//#include <linux/gpio.h>

void sig_handler(int signo, siginfo_t *info, void *context);
int do_gpio();
unsigned gpio;
int main(int argc, char **argv)
{
  struct sigaction act = {.sa_sigaction=sig_handler, .sa_flags=SA_SIGINFO};
  if (argc != 2) {
    printf("usage: %s [gpio num]\n", argv[0]);
  	return 1;
  }
  gpio = atoi(argv[1]);
  if(!gpio_is_valid(gpio)){
    printf("gpio is not valid\n");
    return 1;
  }
  // register signal
  sigemptyset(&act.sa_mask);
  sigaction(SIGUSR1, &act, NULL);
  sigaction(SIGKILL, &act, NULL);
  sigaction(SIGINT, &act, NULL);

  gpio_request(gpio, "GPIO");

  while(do_gpio());

  return 0;
}

void sig_handler(int signo, siginfo_t *info, void *context){
//  gpio_free(gpio);
}
int do_gpio(){
  gpio_set_value(gpio, 1);
  sleep(1);
  gpio_set_value(gpio, 0);
  sleep(1);
  return 1;
}