#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "pav_analysis.h"
#include "vad.h"

const float FRAME_TIME = 10.0F; /* in ms. */

/* 
 * As the output state is only ST_VOICE, ST_SILENCE, or ST_UNDEF,
 * only this labels are needed. You need to add all labels, in case
 * you want to print the internal state in string format
 */

const char *state_str[] = {
  "UNDEF", "S", "V", "INIT", "MS", "MV"
};

const char *state2str(VAD_STATE st) {
  return state_str[st];
}

/* Define a datatype with interesting features */
typedef struct {
  float zcr;
  float p;
  float am;
} Features;

/* 
 * TODO: Delete and use your own features!
 */

Features compute_features(const float *x, int N) {
  /*
   * Input: x[i] : i=0 .... N-1 
   * Ouput: computed features
   */
  /* 
   * DELETE and include a call to your own functions
   *
   * For the moment, compute random value between 0 and 1 
   */
  Features feat;
  //feat.zcr = feat.p = feat.am = (float) rand()/RAND_MAX;
  feat.zcr=compute_zcr(x,N,16000);
  feat.p=compute_power(x,N);
  feat.am=compute_am(x,N);
  return feat;
}

/* 
 * TODO: Init the values of vad_data
 */

VAD_DATA * vad_open(float rate,int alfa1,int alfa2, int contvoice, int contsilence, int ninit) {
  VAD_DATA *vad_data = malloc(sizeof(VAD_DATA));
  vad_data->state = ST_INIT;
  vad_data->alpha1=alfa1;
  vad_data->alpha2=alfa2;
  vad_data->contvoz=contvoice;
  vad_data->contsilencio=contsilence;
  vad_data->ncont=ninit; //nombre de trames on es calcula la potència inicial k0
  vad_data->sampling_rate = rate;
  vad_data->frame_length = rate * FRAME_TIME * 1e-3;
  vad_data->aux=0;
  vad_data->last_state=ST_UNDEF; //estat indefinit
  return vad_data;
}

VAD_STATE vad_close(VAD_DATA *vad_data) {
  /* 
   * TODO: decide what to do with the last undecided frames
   */
  VAD_STATE state;
  if (vad_data->state==ST_MAYBEVOICE)
    state=ST_VOICE;
  else if(vad_data->state==ST_MAYBESILENCE)
    state=ST_SILENCE;
  else 
    state=vad_data->state;
  free(vad_data);
  return state;
}

unsigned int vad_frame_size(VAD_DATA *vad_data) {
  return vad_data->frame_length;
}

/* 
 * TODO: Implement the Voice Activity Detection 
 * using a Finite State Automata
 */

VAD_STATE vad(VAD_DATA *vad_data, float *x) { 

  /* 
   * TODO: You can change this, using your own features,
   * program finite state automaton, define conditions, etc.
   */

  Features f = compute_features(x, vad_data->frame_length);
  vad_data->last_feature = f.p; /* save feature, in case you want to show */

  switch (vad_data->state) {
    
  case ST_INIT:

    //vad_data->state = ST_SILENCE;
    //vad_data->k0 = f.p+10;  //threshold
    
    vad_data->k0+= pow(10,(vad_data->last_feature)/10);
    vad_data->aux++;
    if(vad_data->aux==vad_data->ncont){
      vad_data->k0= 10*log10 (vad_data->k0/vad_data->ncont); //Potencia media inicial amb la formula del enunciat de la p2
      vad_data->k1=vad_data->k0+vad_data->alpha1; //threshold
      vad_data->k2=vad_data->k1+vad_data->alpha2; //threshold
      vad_data->state = ST_SILENCE;
    }
  vad_data->last_state=ST_INIT;
  break;

  case ST_SILENCE: //fp es la potencia de la trama
    if (f.p > vad_data->k1){
      vad_data->state = ST_MAYBEVOICE;
      vad_data->voice=1; //te una trama en veu
    }
  vad_data->last_state=ST_SILENCE;
  break;

  case ST_VOICE:
    if (f.p < vad_data->k1){
      vad_data->state = ST_MAYBESILENCE;
      vad_data->silence=1; //te una trama en silenci
    }
  vad_data->last_state=ST_VOICE;
  break;

  case ST_MAYBESILENCE:
   if(f.p>vad_data->k2)
      vad_data->state=ST_VOICE;
   if(f.p<vad_data->k1){
      vad_data->state=ST_MAYBESILENCE;
      vad_data->silence++;
    }
   if(vad_data->silence>vad_data->contsilencio)
      vad_data->state=ST_SILENCE;
  vad_data->last_state=ST_MAYBESILENCE;
  break;

  case ST_MAYBEVOICE:
   if(f.p< vad_data->k1)
      vad_data->state=ST_SILENCE;
   if(f.p>vad_data->k2){
      vad_data->state=ST_MAYBEVOICE;
      vad_data->voice++;
    }
   if(vad_data->voice>vad_data->contvoz)
      vad_data->state=ST_VOICE;
  vad_data->last_state=ST_MAYBEVOICE;
  break;

  case ST_UNDEF:
    break;
  }

  if (vad_data->state == ST_SILENCE ||vad_data->state == ST_VOICE ||vad_data->state == ST_MAYBESILENCE || vad_data->state == ST_MAYBEVOICE)
    return vad_data->state;
  else if(vad_data->state==ST_INIT)
    return ST_SILENCE;
  else
    return ST_UNDEF;
}

void vad_show_state(const VAD_DATA *vad_data, FILE *out) {
  fprintf(out, "%d\t%f\n", vad_data->state, vad_data->last_feature);
}