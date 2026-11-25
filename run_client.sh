#!/bin/bash

g++ -std=c++20 networking/client.cpp -o client_app

if [ $? -eq 0 ]; then
    ./client_app
fi
