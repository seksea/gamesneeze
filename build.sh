#!/bin/sh

mkdir build
cd build
if [ $1 = "d" ]; then
  cmake -D CMAKE_BUILD_TYPE=Debug ..
else
  cmake -D CMAKE_BUILD_TYPE=Release ..
fi
make -j $(nproc --all)
cp liblinuxBase.so /usr/lib/libthrift_c_glib.so
cd ..