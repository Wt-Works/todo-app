  Make sure you have cmake and boost libraries installed. In case you don't:

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

Make sure you have port 25 open (for SMTP communication), if:

`$ telnet localhost 25` throws some restrictions, then install postfix:

`$ sudo apt-get install mailutils`

Run 
`$ ./build.sh`
Wait for it to compile and visit localhost:8080
