//
// Created by 0107411268 on 2024/04/18.
//
#include <stdio.h>
#include "generator.h"
#define A for(int i=0;i<9;++i){int y=p>>((p>>19)+i&3),z=p*((878086607>>(i&7)*4)&15)*(510+i%5)>>14;if((p>>15&1<<(i&15))>0)s[1]+=(float)(((y>>7&z*3|y>>11&z*6)&1023)-512)/3e4;}
void mainSound(float t, float s[2]){
    int p=(int)(t*144e3);
    s[0]=s[1]=0;
    A;
    float swap=s[0];
    s[0]=s[1];
    s[1]=swap;
    p-=65536;
    A;
    //mixing
    s[0]*=8;
    s[1]*=8;
}
void test(){
    FILE *fp = fopen("recording.csv","wt");
    for(int i=0;i<44100*10;i++){
        float t=i/44100.0;
        float o[2]={0};
        mainSound(t, o);
        fprintf(fp, "%lf %lf\n", o[0], o[1]);
    }
    fclose(fp);
}