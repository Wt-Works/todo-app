  Make sure you have cmake and boost libraries installed. In case you don't:

  UBUNTU:

1. `$ sudo apt-get install software-properties-common`
2. `$ sudo add-apt-repository ppa:george-edison55/cmake-3.x`
3. `$ sudo apt-get update`
4. `$ sudo apt-get install cmake`
5. `$ sudo apt-get upgrade`

download package from http://sourceforge.net/projects/boost/files/boost/1.59.0/
1. `$ tar -xzf boost_1_59_0.tar.gz`
2. `$ cd boost_1_59_0`
3. `$ ./boostrap.sh`

Make sure you have Wt libraries installed. In case you don't:

`$ sudo apt-get install witty witty-dev witty-doc witty-dbg witty-examples`

<<<<<<< 827a5316ebd14766768d3d0d36027d9d00ec0124
Make sure you have port 25 open (for SMTP communication), if:

`$ telnet localhost 25` throws some restrictions, then install postfix:

`$ sudo apt-get install mailutils`

Run 
=======
Run
>>>>>>> some validators and autocomplete
`$ ./build.sh`
Wait for it to compile and visit localhost:8080

  OS X EL CAPITAN:

In case you don't have homebrew installed:

1. `$ ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" `
2. `$ brew install cmake`
3. `$ brew install boost`
4. `$ git clone git://github.com/kdeforche/wt.git`
5. `$ cd wt`
6. `$ mkdir build`
7. `$ cd build`
8. `$ cmake \
     -DCMAKE_CXX_FLAGS='-stdlib=libc++' -DCMAKE_EXE_LINKER_FLAGS='-stdlib=libc++' \
     -DCMAKE_MODULE_LINKER_FLAGS='-stdlib=libc++' -DWT_CPP_11_MODE='-std=c++11' \
     ../`
9. `$ make`
10. `$ sudo make install`
Run `$ ./build.sh`
