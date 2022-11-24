#!/bin/bash

cd /home/swati/
mkdir copy1
cp linux-5.19.8.tar copy1/
cd copy1/
tar -xvf linux-5.19.8.tar
cd linux-5.19.8
cp ../../config-rev-9-gold .config
sudo make nconfig
sudo make bzImage
