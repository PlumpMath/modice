#include "modice.h"

void sig_handler(int signo, siginfo_t *info, void *context){
  close_gpio();
}
/*void add_sine_wave(int16_t* buffer, int buffer_length, float frequency, float sampling_ratio, float amplitude)
{
    for (int i = 0; i < buffer_length; i++)
    {
        float theta = ((float)i / sampling_ratio) * M_PI;
        // make sure to correct for overflows and underflows
        buffer[i] += (int16_t)(sin(theta * frequency) * 32767.0f * amplitude);
    }
}*/
void setup_snd();
int main(int argc, char*argv[]){
//  int loc;
  unsigned i;
  int err;
  char c;
  struct sched_param sp;
  struct sigaction act = {.sa_sigaction=sig_handler, .sa_flags=SA_SIGINFO};

  // signal setting
  sigemptyset(&act.sa_mask);
  sigaction(SIGINT, &act, NULL);
  sigaction(SIGKILL, &act, NULL);
  sigaction(SIGSTOP, &act, NULL);

  //schedule priority setting
  memset(&sp, 0, sizeof(sp));
  sp.sched_priority = sched_get_priority_max(SCHED_FIFO);
  sched_setscheduler(0, SCHED_FIFO, &sp);
  mlockall(MCL_CURRENT | MCL_FUTURE);

  setup_gpio();

  _INIT_GPIO(GPJ0_) = 0x11111111; //OUT
  _INIT_GPIO(GPJ3_) = 0; //IN
  while((err = fread(&c, sizeof(char), sizeof(c), stdin))>0){
    GPIO_DAT(GPJ0_) = c;
    usleep(1); //wait FPGA to edit the data
    fwrite((char*)_GPIO_DAT(GPJ3_), sizeof(char), sizeof(char), stdout);
  }
  GPIO_DAT(GPJ0_) = 0;

  close_gpio();
  return 0;
}