#!/bin/bash

g++ -std=c++20 networking/server.cpp -o server

if [ $? -eq 0 ]; then
    ./server
fi

#!/bin/bash

g++ -std=c++20 networking/server.cpp -o server

if [ $? -eq 0 ]; then
    ./server
fi
