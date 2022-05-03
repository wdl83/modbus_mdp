# !/bin/bash

ZMQPP=zmqpp
MDP=mdp


if [ ! -d ${ZMQPP} ]
then
    git clone https://github.com/zeromq/zmqpp ${ZMQPP}
fi

if [ ! -d ${ZMQPP}/zmqpp-root ]
then
    pushd .
    cd ${ZMQPP}
    mkdir zmqpp-root
    make
    make PREFIX=${PWD}/zmqpp-root install
    popd
fi

if [ ! -d ${MDP} ]
then
    git clone https://github.com/wdl83/mdp ${MDP}
fi
