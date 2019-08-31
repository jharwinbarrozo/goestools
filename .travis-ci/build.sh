git clone --recursive https://github.com/sam210723/goestools
cd goestools
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
sudo make install
