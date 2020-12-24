git clone https://github.com/steve-m/librtlsdr.git /home/runner/work/goestools/librtlsdr
cd /home/runner/work/goestools/librtlsdr
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX:PATH=/usr -DINSTALL_UDEV_RULES=ON ..
sudo make -j2 install
sudo cp ../rtl-sdr.rules /etc/udev/rules.d/
sudo ldconfig
echo 'blacklist dvb_usb_rtl28xxu' | sudo tee --append /etc/modprobe.d/blacklist-dvb_usb_rtl28xxu.conf
