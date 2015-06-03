#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>
#include <string.h>
#include <signal.h>
#include <time.h>

#include "ku_pir_lib.h"

static ku_pir_data data = {};

void sig_handler(int signo, siginfo_t *info, void *context){
    if (!info->si_code) return;
    printf("asynchronous signal received with time stamp:%s, type:", ctime((time_t*)&info->si_code), rf_flag_name(info->si_value.sival_int));
}
int ku_pir_open(){
    int fd=open("/dev/"DEV_NAME_STR, O_RDWR | O_NONBLOCK);
    printf("new fd %d opened\n", fd);
    return fd;
}
int ku_pir_close(int fd){
    return close(fd);
}
//int ku_pir_ioctl(int oflag, int type, unsigned long data){
int ku_pir_ioctl(int fd, int type, unsigned long data){
    int rst;
    //int fd = open("/dev/"DEV_NAME_STR, O_RDWR | oflag);

//    printf("asking near %s frm lib\n", ctime((time_t*)&((ku_pir_data*)data)->timestamp));
    if(!fd) return 0; // fail
    rst = ioctl(fd, type, data);
//    close(fd);
    return rst;
}

int ku_pir_insertData(int fd, long unsigned int ts, int rf_flag){
    ku_pir_data data = {ts, rf_flag};
//    printf("inserting %s %s frm lib\n", ctime((time_t*)&data.timestamp), rf_flag_name(data.rf_flag));
    return ku_pir_ioctl(fd, IOCTL_SET, (unsigned long)&data); // fail:0, success:1
}

// no need to free result. same memory address and space is going to used on next comm
ku_pir_data *ku_pir_asynchronous(int fd, long unsigned int ts){
//    int rst = ku_pir_ioctl(O_ASYNC, IOCTL_ASK, (unsigned long)&data);
    int rst = ku_pir_ioctl(fd, IOCTL_ASK, (unsigned long)&data);
    return rst ? &data : 0;
}

ku_pir_data *ku_pir_nonblocking(int fd, long unsigned int ts){
//    int rst = ku_pir_ioctl(O_NONBLOCK, IOCTL_ASK, (unsigned long)&data);
    int rst = ku_pir_ioctl(fd, IOCTL_ASK, (unsigned long)&data);
    return rst ? &data : 0;
}

ku_pir_data *ku_pir_blocking(int fd, long unsigned int ts){
//    int rst = ku_pir_ioctl(0, IOCTL_ASK, (unsigned long)&data);
    int rst = ku_pir_ioctl(fd, IOCTL_ASK, (unsigned long)&data);
    return rst ? &data : 0;
}