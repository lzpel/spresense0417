//
// Created by 0107411268 on 2024/04/18.
//
#include <stdio.h>
#include "generator.h"
//#define A for(int i=0;i<9;++i){int y=p>>((p>>19)+i&3),z=p*((878086607>>(i&7)*4)&15)*(510+i%5)>>14;if((p>>15&1<<(i&15))>0)s.y+=float(((y>>7&z*3|y>>11&z*6)&1023)-512)/3e4;}
//vec2 mainSound(float t){int p=int(t*144e3);vec2 s;A;s.yx=s;p-=65536;A;return s*mat2(7,1,5,-3);}
#define A(s) for(int i=0;i<9;++i){int y=p>>((p>>19)+i&3),z=p*((878086607>>(i&7)*4)&15)*(510+i%5)>>14;if((p>>15&1<<(i&15))>0)s+=(((y>>7&z*3|y>>11&z*6)&1023)-512);}
void mainSound(int s144000, short o[2]){
    int p=s144000;
    short s[2]={0};
    A(s[0]);
    p-=65536;
    A(s[1]);
    //mixing
    o[0]=s[0]*7+s[1]*1;
    o[1]=s[0]*5-s[1]*3;
}
void test(int seconds){
    FILE *fp = fopen("recording.csv","wt");
    for(int i=0;i<44100*seconds;i++){
        float t=i/44100.0;
        short o[2]={0};
        mainSound((int)(t*144000), o);
        fprintf(fp, "%d %d\n", o[0], o[1]);
    }
    fclose(fp);
}