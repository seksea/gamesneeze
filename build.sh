#!/bin/bash
# gdb injector (inspired by fuzion's)

bash uninject.sh

echo "======================="
echo "building..."

mkdir build
cd build
if [ $1 = "d" ]; then
  cmake -D CMAKE_BUILD_TYPE=Debug ..
else
  cmake -D CMAKE_BUILD_TYPE=Release ..
fi
make -j $(nproc --all)
cp libgamesneeze.so /usr/lib/libthrift_c_glib.so
cd ..

read -p "Inject? (y/n)" -n 1 -r
echo    # (optional) move to a new line
if [[ $REPLY =~ ^[Yy]$ ]]
then
  bash inject.sh
fi