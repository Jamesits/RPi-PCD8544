#!/bin/bash

echo "Building LCD program..."
cc -o lcd main.c PCD8544.c  -L/usr/local/lib -lwiringPi

echo "Installing..."
cp lcd /usr/local/bin
chmod +x /usr/local/bin/lcd
