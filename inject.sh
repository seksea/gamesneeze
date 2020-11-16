#!/bin/bash
# fuzion/aimtux

if [ $1 = "u" ] || [ $2 = "u" ] ; then
  bash uninject.sh
fi

if [ $1 = "b" ] || [ $2 = "b" ] ; then
  bash build.sh
fi

if [ $1 = "bd" ] || [ $2 = "bd" ] ; then
  bash build.sh d
fi

echo "injecting"

csgo_pid=$(pidof csgo_linux64)
echo "csgo pid: $csgo_pid"

sudo killall -19 steam
sudo killall -19 steamwebhelper

lib_dir_name="lib"
if [ $(getconf LONG_BIT) = 64 ]; then
    lib_dir_name+="64"
fi

input="$(
sudo gdb -n -q -batch-silent \
  -ex "set logging on" \
  -ex "set logging file /dev/null" \
  -ex "set logging redirect on" \
  -ex "set auto-load safe-path /usr/share/gdb/auto-load/usr/$lib_dir_name/:/usr/$lib_dir_name/" \
  -ex "attach $csgo_pid" \
  -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
  -ex "call \$dlopen(\"/usr/lib/libthrift_c_glib.so\", 1)" \
  -ex "detach" \
  -ex "quit"
)"

sleep 1
sudo killall -18 steamwebhelper
sudo killall -18 steam

last_line="${input##*$'\n'}"

if [ "$last_line" != "\$1 = (void *) 0x0" ]; then
  echo "success"
else
  echo "FAILED TO INJECT: $input"
fi
