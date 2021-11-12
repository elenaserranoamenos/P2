#ifndef _VAD_H
#define _VAD_H
#include <stdio.h>
#include "pav_analysis.h"

/* TODO: add the needed states */
<<<<<<< HEAD
typedef enum {ST_UNDEF=0, ST_SILENCE, ST_VOICE, ST_INIT,ST_MAYBESILENCE,ST_MAYBEVOICE} VAD_STATE;
=======
typedef enum {ST_UNDEF=0, ST_SILENCE, ST_VOICE, ST_INIT, ST_MAYBESILENCE, ST_MAYBEVOICE} VAD_STATE;
>>>>>>> 359e42a6265e8fd96118efb725e987ea16febfc5

/* Return a string label associated to each state */
const char *state2str(VAD_STATE st);

/* TODO: add the variables needed to control the VAD 
   (counts, thresholds, etc.) */

typedef struct {
  VAD_STATE state,last_state;
  float sampling_rate,k0,k1,k2;
  int alpha1, alpha2, ncont, contvoz,contsilencio;
  unsigned int voice, silence; //calcular las tramas que estamos en silencio o en voz para determinar si es maybe o si es de verdad
  unsigned int frame_length,aux; //Ninit numero de tramas para calcular k0
  float last_feature; /* for debuggin purposes */
<<<<<<< HEAD
  float k0; //umbral de referencia
  float k1; //umbral de sonido sonoro
  float k2; //umbral de sonido sordo
  int tiempo_SILENCE; 
  int tiempo_VOICE;
  int trama;
=======
>>>>>>> 359e42a6265e8fd96118efb725e987ea16febfc5
} VAD_DATA;

/* Call this function before using VAD: 
   It should return allocated and initialized values of vad_data
   sampling_rate: ... the sampling rate */
<<<<<<< HEAD
VAD_DATA *vad_open(float sampling_rate);
=======
VAD_DATA *vad_open(float sampling_rate,int alfa1,int alfa2, int contvoice, int contsilence, int ninit);
>>>>>>> 359e42a6265e8fd96118efb725e987ea16febfc5

/* vad works frame by frame.
   This function returns the frame size so that the program knows how
   many samples have to be provided */
unsigned int vad_frame_size(VAD_DATA *);

/* Main function. For each 'time', compute the new state 
   It returns:
    ST_UNDEF   (0) : undefined; it needs more frames to take decission
    ST_SILENCE (1) : silence
    ST_VOICE   (2) : voice
<<<<<<< HEAD
=======
    ST_MAYBESILENCE (3) : maybe silence
    ST_MAYBEVOICE (4) : maybe voice
>>>>>>> 359e42a6265e8fd96118efb725e987ea16febfc5
    x: input frame
       It is assumed the length is frame_length */
VAD_STATE vad(VAD_DATA *vad_data, float *x);

/* Free memory
   Returns the state of the last (undecided) states. */
VAD_STATE vad_close(VAD_DATA *vad_data);

/* Print actual state of vad, for debug purposes */
void vad_show_state(const VAD_DATA *, FILE *);

#endif