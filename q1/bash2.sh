#!/bin/bash

cd /home/swati/
mkdir copy2
cp linux-5.19.8.tar copy2/
cd copy2/
tar -xvf linux-5.19.8.tar
cd linux-5.19.8
cp ../../config-rev-9-gold .config
sudo make nconfig
sudo make bzImage
