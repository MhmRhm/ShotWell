# ShotWell

This is the code for real time tracking system for non-fixed objects.

You need a [RealSense](https://www.intel.com/content/www/us/en/architecture-and-technology/realsense-overview.html) camera to run this code.

# Requirements

First you need latest CMake:

```bash
sudo apt-get install ca-certificates gpg wget

test -f /usr/share/doc/kitware-archive-keyring/copyright || echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ jammy main' | sudo tee /etc/apt/sources.list.d/kitware.list >/dev/null
sudo apt-get update
test -f /usr/share/doc/kitware-archive-keyring/copyright || sudo rm /usr/share/keyrings/kitware-archive-keyring.gpg
sudo apt-get install kitware-archive-keyring

sudo apt-get install cmake
cmake --version
```

To install RealSense SDK run:

```bash
cd ~/Downloads/

sudo apt-get update && sudo apt-get upgrade && sudo apt-get dist-upgrade
sudo apt-get install libssl-dev libusb-1.0-0-dev libudev-dev pkg-config libgtk-3-dev
sudo apt-get install git wget cmake build-essential
sudo apt-get install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev at

git clone https://github.com/IntelRealSense/librealsense.git
cd librealsense/
sudo apt install v4l-utils
./scripts/setup_udev_rules.sh
mkdir build && cd build
cmake ../ -DBUILD_EXAMPLES=true
sudo make uninstall && make clean && make -j $(nproc) && sudo make -j $(nproc) install
rs-enumerate-devices
```

To install OpenCV:

```bash
cd ~/Downloads/
git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git
cd opencv
mkdir build && cd build

cmake -DOPENCV_EXTRA_MODULES_PATH=../../opencv_contrib/modules/ ../../opencv
cmake --build . --parallel $(nproc)
sudo make install
```
