# goestools

**This is a modified version of goestools for the COMS-1 LRIT downlink ([original README here](README.old.md)). See [github.com/sam210723/COMS-1](https://github.com/sam210723/COMS-1) for the rest of the COMS-1 project.**

## Changes
  * [Update LRIT and HRIT symbol rates](https://github.com/sam210723/goestools/commit/9fd004cc2aef0f7620703321314443f4c8d6b634)
  * [Disable building of goeslrit, goesproc and goespackets](https://github.com/sam210723/goestools/commit/73bae4e01bebd3b3bf347f8afc731bda2549dfe8)

## Building
```
sudo apt-get update
sudo apt-get install -y build-essential cmake
git clone --recursive https://github.com/sam210723/goestools
cd goestools
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
make install
```
