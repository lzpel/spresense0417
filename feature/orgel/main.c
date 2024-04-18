
//
// Created by 0107411268 on 2024/04/18.
//
#include "generator.h"
#include <stdio.h>
#include <stdlib.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))
int main(int argc, char *argv[]) {
    if(argc<2){
        return -1;
    }else{
        test(MIN(600, MAX(0, atoi(argv[1]))));
        return 0;
    }
}