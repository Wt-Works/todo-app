#!/bin/sh
mkdir build
cd build
rm -rf *
cmake ..
make
cd ..
cd source
cp todo.* ~/develop/cpp/todo-app/build/source/
cd ..
cd build
cd source
./todo-app.wt --http-address 0.0.0.0 --http-port 8080 --docroot=.
