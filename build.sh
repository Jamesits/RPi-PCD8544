#!/bin/bash

echo "Building support library..."
cd wiringPi
./build

echo "Building LCD program..."
cd ..
cc -o lcd main.c PCD8544.c  -L/usr/local/lib -lwiringPi
