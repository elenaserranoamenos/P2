#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sndfile.h>

#include "vad.h"
#include "vad_docopt.h"

#define DEBUG_VAD 0x1

int main(int argc, char *argv[]) {
  int verbose = 0; /* To show internal state of vad: verbose = DEBUG_VAD; */

  SNDFILE *sndfile_in, *sndfile_out = 0;
  SF_INFO sf_info;
  FILE *vadfile;
  int n_read = 0, i;
<<<<<<< HEAD
  int n_write= 0, j;

=======
  int n_write = 0;
  int alfa1, alfa2, ncont, contsilencio, contvoz;
>>>>>>> 359e42a6265e8fd96118efb725e987ea16febfc5
  VAD_DATA *vad_data;
  VAD_STATE state, last_state,last_state_merge;

  float *buffer, *buffer_zeros;
  int frame_size;         /* in samples */
  float frame_duration;   /* in seconds */
<<<<<<< HEAD
  unsigned int t, last_t; /* in frames */
=======
  unsigned int t, last_t, time; /* in frames */
>>>>>>> 359e42a6265e8fd96118efb725e987ea16febfc5

  char	*input_wav, *output_vad, *output_wav;

  DocoptArgs args = docopt(argc, argv, /* help */ 1, /* version */ "2.0");
  alfa1 = atoi(args.alfa1);
  alfa2 = atoi(args.alfa2);
  ncont = atoi(args.ninit);
  contsilencio = atoi(args.contsilence);
  contvoz = atoi(args.contvoice);
  verbose    = args.verbose ? DEBUG_VAD : 0;
  input_wav  = args.input_wav;
  output_vad = args.output_vad;
  output_wav = args.output_wav;
<<<<<<< HEAD
=======
  
>>>>>>> 359e42a6265e8fd96118efb725e987ea16febfc5

  if (input_wav == 0 || output_vad == 0) {
    fprintf(stderr, "%s\n", args.usage_pattern);
    return -1;
  }

  /* Open input sound file */
  if ((sndfile_in = sf_open(input_wav, SFM_READ, &sf_info)) == 0) {
    fprintf(stderr, "Error opening input file %s (%s)\n", input_wav, strerror(errno));
    return -1;
  }

  if (sf_info.channels != 1) {
    fprintf(stderr, "Error: the input file has to be mono: %s\n", input_wav);
    return -2;
  }

  /* Open vad file */
  if ((vadfile = fopen(output_vad, "wt")) == 0) {
    fprintf(stderr, "Error opening output vad file %s (%s)\n", output_vad, strerror(errno));
    return -1;
  }

  /* Open output sound file, with same format, channels, etc. than input */
  if (output_wav) {
    if ((sndfile_out = sf_open(output_wav, SFM_WRITE, &sf_info)) == 0) {
      fprintf(stderr, "Error opening output wav file %s (%s)\n", output_wav, strerror(errno));
      return -1;
    }
  }

<<<<<<< HEAD
  vad_data = vad_open(sf_info.samplerate);
=======
  vad_data = vad_open(sf_info.samplerate,alfa1,alfa2,contvoz,contsilencio,ncont);
>>>>>>> 359e42a6265e8fd96118efb725e987ea16febfc5
  /* Allocate memory for buffers */
  frame_size   = vad_frame_size(vad_data);
  buffer       = (float *) malloc(frame_size * sizeof(float));
  buffer_zeros = (float *) malloc(frame_size * sizeof(float));
  for (i=0; i< frame_size; ++i) buffer_zeros[i] = 0.0F;

  frame_duration = (float) frame_size/ (float) sf_info.samplerate;
<<<<<<< HEAD
  last_state = ST_SILENCE;
=======
  last_state = ST_UNDEF;
  last_state_merge=ST_SILENCE;
>>>>>>> 359e42a6265e8fd96118efb725e987ea16febfc5

  for (t = last_t = 0; ; t++) { /* For each frame ... */
    /* End loop when file has finished (or there is an error) */
    if  ((n_read = sf_read_float(sndfile_in, buffer, frame_size)) != frame_size) break;

    /*if (sndfile_out != 0) {
      // TODO: copy all the samples into sndfile_out //
      n_write=sf_write_float(sndfile_out,buffer,frame_size);
    }*/

    state = vad(vad_data, buffer);
    if (verbose & DEBUG_VAD) 
      vad_show_state(vad_data, stdout);

    /* TODO: print only SILENCE and VOICE labels */
    
    if((last_state_merge!=state) &&(state==ST_MAYBEVOICE || state==ST_MAYBESILENCE ) && (last_state==ST_SILENCE ||last_state==ST_VOICE)){
      last_state_merge=last_state;
      time=t;
    }
    
    /* As it is, it prints UNDEF segments but is should be merge to the proper value */
<<<<<<< HEAD
    if( (state==ST_SILENCE || state==ST_VOICE) && last_state==ST_MAYBESILENCE){ // si hi ha un maybesilence decidim si es silence o voice depenent del que hi hagi a la trama de despres
      last_state=state;
    }
    if( (state==ST_SILENCE || state==ST_VOICE) && last_state==ST_MAYBEVOICE){ 
      last_state=state;
    }
    //if (state != last_state) {
    if(state!=last_state){
      if (t != last_t)
        fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration, state2str(last_state));
      last_state = state;
      last_t = t;
=======
    if (state != last_state) {
      if (t != last_t){
        if((last_state_merge!=state) && (state==ST_VOICE||state==ST_SILENCE) && (last_state==ST_MAYBEVOICE || last_state==ST_MAYBESILENCE)){
          fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, time * frame_duration, state2str(last_state_merge));
          last_state_merge = state;
          last_t=time;
        }
      }
>>>>>>> 359e42a6265e8fd96118efb725e987ea16febfc5
    }

    if (sndfile_out != 0) {
      /* TODO: go back and write zeros in silence segments */
<<<<<<< HEAD
      if(state==ST_SILENCE){
        n_write=sf_write_float(sndfile_out,buffer_zeros,frame_size);//poner a zero lo que se escribe en el sndfileout
=======
     if(last_state==ST_SILENCE){
        n_write=sf_write_float(sndfile_out,buffer_zeros,frame_size);
>>>>>>> 359e42a6265e8fd96118efb725e987ea16febfc5
      }
      else{
        n_write=sf_write_float(sndfile_out,buffer,frame_size);
      }
    }
    last_state=state;
  }

  state = vad_close(vad_data);
  /* TODO: what do you want to print, for last frames? */
  if (t != last_t)
    fprintf(vadfile, "%.5f\t%.5f\t%s\n", last_t * frame_duration, t * frame_duration + n_read / (float) sf_info.samplerate, state2str(state));

  /* clean up: free memory, close open files */
  free(buffer);
  free(buffer_zeros);
  sf_close(sndfile_in);
  fclose(vadfile);
  if (sndfile_out) sf_close(sndfile_out);
  return 0;
}