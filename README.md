# goestools

**This is a modified version of goestools (originally by [Pieter Noordhuis](https://github.com/pietern/goestools)) for the GK-2A and COMS-1 LRIT downlinks ([original README here](README.old.md)).**

**The rest of the xRIT receiver project for GK-2A can be found in the [xrit-rx repo](https://github.com/sam210723/xrit-rx). Older code for COMS-1 (recently retired) can be found [here](https://github.com/sam210723/COMS-1).**

## Changes
  * [Update LRIT and HRIT symbol rates](https://github.com/sam210723/goestools/commit/9fd004cc2aef0f7620703321314443f4c8d6b634)
  * [Disable building of goeslrit, goesproc and goespackets](https://github.com/sam210723/goestools/commit/73bae4e01bebd3b3bf347f8afc731bda2549dfe8)
  * [Change LRIT frequency](https://github.com/sam210723/goestools/commit/af7cfc9a8ee08d096f50b07bde59101be3635a43)

## Building from source
```
sudo apt-get update
sudo apt-get install -y build-essential cmake zlib1g-dev libairspy-dev librtlsdr-dev
git clone --recursive https://github.com/sam210723/goestools
cd goestools
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
sudo make install
cd ..
cd ..
cp goestools/etc/goesrecv.conf goesrecv.conf
```

## Running
The ```-i``` option specifies the interval (in seconds) that goesrecv will output information to the console. The ```-c``` option specifies a path to the goesrecv config file.

```
goesrecv -i 1 -c goesrecv.conf
```
