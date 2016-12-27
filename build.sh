#!/bin/bash

cd wiringPi
./build
cc -o lcd main.c PCD8544.c  -L/usr/local/lib -lwiringPi
