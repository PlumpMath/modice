# Modice
Syslab2 embedded kit based realtime voice modifier

1. C linux app
2. FPGA modifier

## Directories
- document : Documentation - see Documentation section below
- fpga : FPGA implemented clock-free, interchangeable sound modification modules
- linux : C codes that needs cross-compile 
- TFT_LCD : Trial on FPGA to draw audio spectrum on LCD

## Documentation
- gpio_test_result.txt, xlsx : How pins are connected with memory space on SYS-LAB 2 test board
- gpio_mmap_test_J3.png : Digital probe test result with counting full 8 bits 0~0xFF
- gpio_mmap_test.png : Digital probe test result with mmap, without scheduling
- gpio_mmap_sched_test.png : Digital probe test result with schedule set maximum(sched.h)

## How to use
1. Record a wav file or convert from other audio type and remove it's header to make it raw audio file.
2. Rename it to audio.raw for ease.
3. `cat audio.raw | aplay` plays original file
4. `cat audio.raw | ./modice | aplay` plays sound modified by FPGA
5. `cat audio.raw | ./modice > out.raw` to save its output to another file named out.raw.
