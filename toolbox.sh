#!/bin/bash
# fuzion/aimtux

# name of library to inject cheat as via gdb
libname="libmenu.so"
libdirname="lib"
if [ $(getconf LONG_BIT) = 64 ]; then
    libdirname+="64"
fi

csgo_pid=$(pidof csgo_linux64)

rm -rf /tmp/dumps
mkdir --mode=000 /tmp/dumps 

function unload {
    echo "unloading cheat..."
    if grep -q "$libname" "/proc/$csgo_pid/maps"; then
        gdb -n -q -batch-silent \
            -ex "set logging on" \
            -ex "set logging file /dev/null" \
            -ex "set logging redirect on" \
            -ex "attach $csgo_pid" \
            -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
            -ex "set \$dlclose = (int(*)(void*)) dlclose" \
            -ex "set \$library = \$dlopen(\"/usr/lib/$libname\", 6)" \
            -ex "call \$dlclose(\$library)" \
            -ex "call \$dlclose(\$library)" \
            -ex "detach" \
            -ex "quit"
        echo "unloaded!"
    else
        echo "nothing to unload"
    fi
}

function load {
    echo "loading cheat..."
    cp build/libgamesneeze.so /usr/lib/$libname
    gdb -n -q -batch-silent \
        -ex "set logging on" \
        -ex "set logging file /dev/null" \
        -ex "set logging redirect on" \
        -ex "set auto-load safe-path /usr/share/gdb/auto-load/usr/$libdirname/:/usr/$libdirname/" \
        -ex "attach $csgo_pid" \
        -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
        -ex "call \$dlopen(\"/usr/lib/$libname\", 1)" \
        -ex "detach" \
        -ex "quit"
    echo "successfully loaded!"
}

function build {
    echo "building cheat..."
    mkdir build
    cd build
    cmake -D CMAKE_BUILD_TYPE=Release ..
    make -j $(nproc --all)
    cd ..
}

while [[ $# -gt 0 ]]
do
keys="$1"
case $keys in
    -u|--unload)
        unload
        shift
        ;;
    -l|--load)
        load
        shift
        ;;
    -b|--build)
        build
        shift
        ;;
    -h|--help)
        echo "
 help
Toolbox script for gamesneeze the beste lincuck cheat 2020
=============================================================
| Argument          | Description                           |
| ----------------- | ------------------------------------- |
| -u (--unload)     | Unload the cheat from CS:GO if loaded |
| -l (--load)       | Load/inject the cheat via gdb         |
| -b (--build)      | Build to the build/ dir               |
| -h (--help)       | Show help                             |
=============================================================

All args are executed in the order they are written in, for
example, \"-u -b -l\" would unload the cheat, build it, and
then load it back into csgo.
"
        exit
        ;;
    *)
        echo "Unknown arg $1, use -h for help"
        exit
        ;;
esac
done