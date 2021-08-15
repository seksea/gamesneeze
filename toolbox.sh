#!/bin/bash

gdb="$(dirname "$0")/gdb" # For using a gdb build such as the cathook one (The one included)

if [ -f libname ]; then
	libname=$(cat libname) # Check if random_name was used
else
	libname="libgamemodeauto.so.0" # Pretend to be gamemode, change this to another lib that may be in /maps (if already using real gamemode, I'd suggest using libMangoHud.so)
fi

csgo_pid=$(pidof csgo_linux64)

# Set to true to compile with clang. (if changing to true, make sure to delete the build directory from gcc)
export USE_CLANG="false"

if [[ $EUID -eq 0 ]]; then
    echo "You cannot run this as root." 
    exit 1
fi

rm -rf /tmp/dumps
mkdir -p --mode=000 /tmp/dumps

function random_name {
	# Get a Random name from the build_names file.
	libname=$(shuf -n 1 build_names)

	# In case this file exists, get another one. ( checked it works )
	while [ -f "/usr/lib/${libname}" ] || grep -q ${libname} /proc/$csgo_pid/maps; do	
		libname=$(shuf -n 1 build_names)
	done
	
	if [ -f libname ]; then
	    filename=$(cat libname)
	    rm "$filename"
	    if [ -f "/usr/lib/${filename}" ]; then
	    	echo -e "Note: Old file found at /usr/lib/${filename}\n"
		#sudo rm "/usr/lib/${filename}"

	    fi
	    chmod 660 libname
	    mv libname libname_old
	fi

	echo $libname > libname
	chmod 400 libname # Make the libname read-only for safety.
}

function unload {
    echo "Unloading cheat..."
    echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
    if grep -q "$libname" "/proc/$csgo_pid/maps"; then
        $gdb -n -q -batch -ex "attach $csgo_pid" \
            -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
            -ex "set \$dlclose = (int(*)(void*)) dlclose" \
            -ex "set \$library = \$dlopen(\"/usr/lib/$libname\", 6)" \
            -ex "call \$dlclose(\$library)" \
            -ex "call \$dlclose(\$library)" \
            -ex "detach" \
            -ex "quit"
    fi
    echo "Unloaded!"
}

function load {
    echo "Loading cheat..."
    echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope > /dev/null
    sudo cp build/libgamesneeze.so /usr/lib/$libname
    gdbOut=$(
      $gdb -n -q -batch \
      -ex "set auto-load safe-path /usr/lib/" \
      -ex "attach $csgo_pid" \
      -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
      -ex "call \$dlopen(\"/usr/lib/$libname\", 1)" \
      -ex "detach" \
      -ex "quit" 2> /dev/null
    )
    lastLine="${gdbOut##*$'\n'}"
    if [[ "$lastLine" != "\$1 = (void *) 0x0" ]]; then
      echo "Successfully injected!"
    else
      echo "Injection failed, make sure you have compiled."
    fi
}

function load_debug {
    echo "Loading cheat..."
    echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope
    sudo cp build/libgamesneeze.so /usr/lib/$libname
    $gdb -n -q -batch \
        -ex "set auto-load safe-path /usr/lib:/usr/lib/" \
        -ex "attach $csgo_pid" \
        -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
        -ex "call \$dlopen(\"/usr/lib/$libname\", 1)" \
        -ex "detach" \
        -ex "quit"
    $gdb -p "$csgo_pid"
    echo "Successfully loaded!"
}

function build {
    echo "Building cheat..."
    mkdir -p build
    cd build
    cmake -D CMAKE_BUILD_TYPE=Release ..
    make -j $(nproc --all)
    cd ..
}

function build_debug {
    echo "Building cheat..."
    mkdir -p build
    cd build
    cmake -D CMAKE_BUILD_TYPE=Debug ..
    make -j $(nproc --all)
    cd ..
}

function pull {
    git pull
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
    -r|--random_name)
        random_name
        shift
        ;;
    -p|--pull)
        pull
        shift
        ;;
    -h|--help)
        echo "
 help
Toolbox script for gamesneeze the beste lincuck cheat 2021
=======================================================================
| Argument             | Description                                  |
| -------------------- | -------------------------------------------- |
| -u (--unload)        | Unload the cheat from CS:GO if loaded.       |
| -l (--load)          | Load/inject the cheat via gdb.               |
| -ld (--load_debug)   | Load/inject the cheat and debug via gdb.     |
| -b (--build)         | Build to the build/ dir.                     |
| -bd (--build_debug)  | Build to the build/ dir as debug.            |
| -r (--random_name)   | Use random build name.                       |
| -p (--pull)          | Update the cheat.                            |
| -h (--help)          | Show help.                                   |
=======================================================================

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
