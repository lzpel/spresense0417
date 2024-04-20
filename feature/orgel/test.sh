#!/usr/bin/env bash
set -eux
gcc main.c generator.c -o a.out
./a.out 100
python3 -m pipenv run ./test.py recording.csv