#include <stdio.h>
#include <math.h>
#include "pav_analysis.h"

//int sign(float x){
    //if(x>=0){
        //return 1;
    //}else{
        //return 0;
    //}
//}

float compute_power(const float *x, unsigned int N) {
    float sum = 1e-9;
        for(int i=0; i<N; i++){
            sum = sum + (x[i]*x[i]);
        }
        float p = 10*log10(sum/N); // Potencia media [dB]
    return p;
}

float compute_am(const float *x, unsigned int N) {
    float sum = 0;
        for(int i=0; i<N; i++){
            sum = sum + fabs(x[i]);
        }
        float p = sum/N;  //Amplitud media
    return p;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    float sum = 0;
        for(int i = 1; i<N; i++){
            if(x[i]*x[i-1]<0){
                sum = sum+1;
            }
        }
        float p = 2*fm*sum/(N-1); //Tasa de cruces
    return p;
}

float hamming_window(int n, int N){
    return (0.54-0.46*cos(2*n*N*M_PI));
}

float compute_power_hamming(const float *x, unsigned int N, float fm){
    float numerador = 0;
    float denominador = 0;
    for(int i=0; i<N; i++){
        numerador = numerador + pow(x[i]*hamming_window(i,N),2);
        denominador = denominador + pow(hamming_window(i,N),2);
    }
    return 10*log10(numerador/denominador);
}

