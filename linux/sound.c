#include "modice.h"

// Audio assertion macro
#define snd_assert(e, v, msg, ...) \
 if ((e = v)<0){ \
    fprintf(stderr, msg, ##__VA_ARGS__, snd_strerror(e)); \
    exit(1); \
  }
/*int playback_callback (snd_pcm_sframes_t nframes){
  int err;

//  printf ("playback callback called with %u frames\n", nframes);
  snd_assert(err, snd_pcm_writei (playback_handle, sndbuf, nframes), "write failed (%s)\n", snd_strerror(err));
  return err;
}*/
void setup_sound(){
	snd_pcm_hw_params_t *hw_params;
//  snd_pcm_sw_params_t *sw_params;
  snd_pcm_sframes_t frames_to_deliver;
  int nfds;
  int err;
  struct pollfd *pfds;
  unsigned rate = 8000;
  char *audio_dev_name = "default";

  snd_assert(err, snd_pcm_open (&playback_handle, audio_dev_name, SND_PCM_STREAM_PLAYBACK, 0), "cannot open audio device %s (%s)\n", audio_dev_name);
  snd_assert(err, snd_pcm_hw_params_malloc (&hw_params), "cannot allocate hardware parameter structure (%s)\n");
  snd_assert(err, snd_pcm_hw_params_any (playback_handle, hw_params), "cannot initialize hardware parameter structure (%s)\n");
  snd_assert(err, snd_pcm_hw_params_set_access (playback_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED), "cannot set access type (%s)\n");
  snd_assert(err, snd_pcm_hw_params_set_format (playback_handle, hw_params, SND_PCM_FORMAT_S8), "cannot set sample format (%s)\n");
  snd_assert(err, snd_pcm_hw_params_set_rate_near (playback_handle, hw_params, &rate, 0), "cannot set sample rate (%s)\n");
  snd_assert(err, snd_pcm_hw_params_set_channels (playback_handle, hw_params, 1), "cannot set channel count (%s)\n");
  snd_assert(err, snd_pcm_hw_params (playback_handle, hw_params), "cannot set parameters (%s)\n");
  snd_pcm_hw_params_free (hw_params);
/* tell ALSA to wake us up whenever 4096 or more frames
     of playback data can be delivered. Also, tell
     ALSA that we'll start the device ourselves.
  */
  /*snd_assert(err, snd_pcm_sw_params_malloc (&sw_params), "cannot allocate software parameters structure (%s)\n");
  snd_assert(err, snd_pcm_sw_params_current (playback_handle, sw_params), "cannot initialize software parameters structure (%s)\n");
  snd_assert(err, snd_pcm_sw_params_set_avail_min (playback_handle, sw_params, 1), "cannot set minimum available count (%s)\n");
  snd_assert(err, snd_pcm_sw_params_set_start_threshold (playback_handle, sw_params, 0U), "cannot set start mode (%s)\n");
  snd_assert(err, snd_pcm_sw_params (playback_handle, sw_params), "cannot set software parameters (%s)\n");*/

  /*snd_assert(err, snd_pcm_open (&capture_handle, audio_dev_name, SND_PCM_STREAM_CAPTURE, 0), "cannot open audio device %s (%s)\n", audio_dev_name);
  snd_assert(err, snd_pcm_hw_params_malloc (&hw_params), "cannot allocate hardware parameter structure (%s)\n");
  snd_assert(err, snd_pcm_hw_params_any (capture_handle, hw_params), "cannot initialize hardware parameter structure (%s)\n");
  snd_assert(err, snd_pcm_hw_params_set_access (capture_handle, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED), "cannot set access type (%s)\n");
  snd_assert(err, snd_pcm_hw_params_set_format (capture_handle, hw_params, SND_PCM_FORMAT_S8), "cannot set sample format (%s)\n");
  rate = 8000;
  snd_assert(err, snd_pcm_hw_params_set_rate_near (capture_handle, hw_params, &rate, 0), "cannot set sample rate (%s)\n");
  snd_assert(err, snd_pcm_hw_params_set_channels (capture_handle, hw_params, 1), "cannot set channel count (%s)\n");
  snd_assert(err, snd_pcm_hw_params (capture_handle, hw_params), "cannot set parameters (%s)\n");
  snd_pcm_hw_params_free (hw_params);*/

/* the interface will interrupt the kernel every 4096 frames, and ALSA
     will wake up this program very soon after that.
  */
  snd_assert(err, snd_pcm_prepare (playback_handle), "cannot prepare audio interface for use (%s)\n");
//  snd_assert(err, snd_pcm_prepare (capture_handle), "cannot prepare audio interface for use (%s)\n");
/*
  while (1) {
*//* wait till the interface is ready for data, or 1 second
       has elapsed.
    *//*
    snd_assert(err, snd_pcm_wait (playback_handle, 1000), "poll failed (%s)\n");
*//* find out how much space is available for playback data *//*
    if ((frames_to_deliver = snd_pcm_avail_update (playback_handle)) < 0) {
      if (frames_to_deliver == -EPIPE) {
        fprintf (stderr, "an xrun occured\n");
        break;
      } else {
        fprintf (stderr, "unknown ALSA avail update return value (%d)\n", frames_to_deliver);
        break;
      }
    }
    frames_to_deliver = frames_to_deliver > 4096 ? 4096 : frames_to_deliver;
*//* deliver the data *//*
    if (playback_callback (frames_to_deliver) != frames_to_deliver) {
            fprintf (stderr, "playback callback failed\n");
      break;
    }
  }*/
}
void close_sound(){
  snd_pcm_close (playback_handle);
  snd_pcm_close (capture_handle);
  exit (0);
}
