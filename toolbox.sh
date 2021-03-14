#!/bin/sh

# TODO: make this some sort of fucking automaticly randomly chosen name. - allbombson
gdb="$(dirname "$0")/gdb9" # For using a gdb build such as the cathook one (The one included)
libname="libgamemode.so" # Pretend to be gamemode, change this to another lib that may be in /maps
csgo_pid=$(pidof csgo_linux64)
# Lets user set compiler to whatever they want
export CC="gcc"
export CXX="g++"

rm -rf /tmp/dumps
mkdir -p --mode=000 /tmp/dumps 

function unload {
    echo "Unloading cheat..."
    echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
    if grep -q "$libname" "/proc/$csgo_pid/maps"; then
        $gdb -n -q -batch -ex "attach $csgo_pid" \
            -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
            -ex "set \$dlclose = (int(*)(void*)) dlclose" \
            -ex "set \$library = \$dlopen(\"$(pwd)/build/$libname\", 6)" \
            -ex "call \$dlclose(\$library)" \
            -ex "call \$dlclose(\$library)" \
            -ex "detach" \
            -ex "quit"
    fi
    echo "unloaded!"
}

function load {
    echo "Loading cheat..."
    echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
    cp build/libgamesneeze.so build/$libname
    $gdb -n -q -batch \
        -ex "set auto-load safe-path $(pwd)/build/:/usr/lib/" \
        -ex "attach $csgo_pid" \
        -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
        -ex "call \$dlopen(\"$(pwd)/build/$libname\", 1)" \
        -ex "detach" \
        -ex "quit"
    echo "Successfully loaded!"
}

function load_debug {
    echo "Loading cheat..."
    echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
    cp build/libgamesneeze.so build/$libname
    $gdb -n -q -batch \
        -ex "set auto-load safe-path $(pwd)/build/:/usr/lib/" \
        -ex "attach $csgo_pid" \
        -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
        -ex "call \$dlopen(\"$(pwd)/build/$libname\", 1)" \
        -ex "detach" \
        -ex "quit"
    $gdb -p "$csgo_pid"
    echo "successfully loaded!"
}

function build {
    if [[ $EUID -eq 0 ]]; then
   	    echo "You cannot build as root." 
   	    exit 1
    fi
    echo "Building cheat..."
    mkdir -p build
    cd build
    cmake -D CMAKE_BUILD_TYPE=Release ..
    make -j $(nproc --all)
    cd ..
}

function build_debug {
    if [[ $EUID -eq 0 ]]; then
   	    echo "You cannot build as root." 
   	    exit 1
    fi
    echo "Building cheat..."
    mkdir -p build
    cd build
    cmake -D CMAKE_BUILD_TYPE=Debug ..
    make -j $(nproc --all)
    cd ..
}

function pull {
    if [[ $EUID -eq 0 ]]; then
   	    echo "You cannot pull as root" 
   	    exit 1
    fi
    git pull
}

function pullUpstream {
    if [[ $EUID -eq 0 ]]; then
   	    echo "You cannot pull as root" 
   	    exit 1
    fi
    git pull https://github.com/seksea/gamesneeze 
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
    -ld|--load_debug)
        load_debug
        shift
        ;;
    -b|--build)
        build
        shift
        ;;
    -bd|--build_debug)
        build_debug
        shift
        ;;
    -p|--pull)
        pull
        shift
        ;;
    -pu|--pullUp)
        pullUpstream
        shift
        ;;
    -h|--help)
        echo "
 help
Toolbox script for gamesneeze the beste lincuck cheat 2021
================================================================
| Argument           | Description                             |
| ------------------ | --------------------------------------- |
| -u (--unload)      | Unload the cheat from CS:GO if loaded.  |
| -l (--load)        | Load/inject the cheat via gdb.          |
| -ld (--load_debug) | Load/inject the cheat and debug via gdb.|
| -b (--build)       | Build to the build/ dir.                |
| -bd (--build_debug)| Build to the build/ dir as debug.       |
| -p (--pull)        | Update the cheat.                       |
| -pu (--pullUp)     | Update the cheat from main repo.        |
| -h (--help)        | Show help.                              |
================================================================

All args are executed in the order they are written in, for
example, \"-p -u -b -l\" would update the cheat, then unload, then build it, and
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
