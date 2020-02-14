# goestools

[![Build Status](https://travis-ci.org/sam210723/goestools.svg?branch=master)](https://travis-ci.org/sam210723/goestools)

**This is a modified version of goesrecv (originally by [Pieter Noordhuis](https://github.com/pietern/goestools)) for the LRIT downlink transmitted by GEO-KOMPSAT-2A (GK-2A) at 128.2°E.**

**The rest of the xRIT receiver project for GK-2A can be found in the [xrit-rx repo](https://github.com/sam210723/xrit-rx). Older code for the now retired COMS-1 satellite can be found [here](https://github.com/sam210723/COMS-1).**

## Building
Install dependencies for ```librtlsdr``` and ```goesrecv```:
```
sudo apt-get update
sudo apt-get install -y build-essential pkg-config cmake git zlib1g-dev libairspy-dev libusb-1.0-0-dev
```

Build ```librtlsdr``` from source:
```
# Download, compile, and install librtlsdr
git clone https://github.com/steve-m/librtlsdr.git
cd librtlsdr
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr -DINSTALL_UDEV_RULES=ON ..
sudo make -j2 install

# Load udev rules and blacklist the DVB driver shipped with the OS
sudo cp ../rtl-sdr.rules /etc/udev/rules.d/
sudo ldconfig
echo 'blacklist dvb_usb_rtl28xxu' | sudo tee --append /etc/modprobe.d/blacklist-dvb_usb_rtl28xxu.conf

sudo reboot
```

Build ```goesrecv``` from source:
```
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
The ```-i``` option specifies the interval (in seconds) that goesrecv will output information to the console.

The ```-c``` option specifies a path to the goesrecv config file.

```
goesrecv -i 1 -c goesrecv.conf
```

## Changes
  * [Update LRIT and HRIT symbol rates](https://github.com/sam210723/goestools/commit/9fd004cc2aef0f7620703321314443f4c8d6b634)
  * [Disable building of goeslrit, goesproc and goespackets](https://github.com/sam210723/goestools/commit/73bae4e01bebd3b3bf347f8afc731bda2549dfe8)
  * [Change LRIT frequency](https://github.com/sam210723/goestools/commit/af7cfc9a8ee08d096f50b07bde59101be3635a43)
