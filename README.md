  Make sure you have cmake and boost libraries installed. In case you don't:

sudo apt-get install software-properties-common
sudo add-apt-repository ppa:george-edison55/cmake-3.x
sudo apt-get update
sudo apt-get install cmake
sudo apt-get upgrade

download package from http://sourceforge.net/projects/boost/files/boost/1.59.0/
tar -xzf boost_1_59_0.tar.gz
./boostrap.sh

Make sure you have Wt libraries installed. In case you don't:

sudo apt-get install witty witty-dev witty-doc witty-dbg witty-examples

Run ./build.sh
Wait for it to compile and visit localhost:8080
