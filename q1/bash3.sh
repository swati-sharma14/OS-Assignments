#!/bin/bash

cd /home/swati/
mkdir copy3
cp linux-5.19.8.tar copy3/
cd copy3/
tar -xvf linux-5.19.8.tar
cd linux-5.19.8
cp ../../config-rev-9-gold .config
sudo make nconfig
sudo make bzImage
