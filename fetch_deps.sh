# !/bin/bash

MDP=mdp

if [ ! -d ${MDP} ]
then
    git clone https://github.com/wdl83/mdp ${MDP}
fi
