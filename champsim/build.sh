#!/bin/bash

if [ "$#" -lt 1 ]; then
    echo "Give Core Numbers."
    exit 1
fi

NUM=${1}

./build_champsim.sh perceptron sangam_dpc3 sangam_dpc3 sangam_dpc3 lru $NUM
./build_champsim.sh perceptron ipcp ipcp ipcp lru $NUM
./build_champsim.sh perceptron no no no lru $NUM
./build_champsim.sh perceptron team_12 team_12 team_12 lru $NUM
./build_champsim.sh perceptron bingo_dpc3 next_line next_line lru $NUM
./build_champsim.sh perceptron pangloss pangloss no lru $NUM
./build_champsim.sh perceptron T_SKID190509.021 spp.021 no.021 lru $NUM
./build_champsim.sh perceptron no spp_dev no lru $NUM

