#!/bin/bash

echo "Building LCD program..."
cc -o lcd main.c PCD8544.c  -L/usr/local/lib -lwiringPi
