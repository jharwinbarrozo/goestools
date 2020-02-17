# Linux
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
make
sudo make install
goesrecv --version

# Windows
rm -rf *
printf '1\n\n' | sudo update-alternatives --config i686-w64-mingw32-g++
printf '1\n\n' | sudo update-alternatives --config x86_64-w64-mingw32-g++
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local -DCMAKE_SYSTEM_NAME="Windows"
make
