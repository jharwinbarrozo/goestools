# Linux
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
sudo make install
goesrecv --version

# Windows
rm -rf *
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_SYSTEM_NAME="Windows"
make
goesrecv --version
