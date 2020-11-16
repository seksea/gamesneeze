#!/bin/sh

mkdir build
cd build
cmake -D CMAKE_BUILD_TYPE=Debug ..
make -j $(nproc --all)
mv liblinuxBase.so /usr/lib/libthrift_c_glib.so
cd ..