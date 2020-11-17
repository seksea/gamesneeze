#!/bin/bash
# fuzion/aimtux

echo "======================="
echo "uninjecting..."

csgo_pid=$(pidof csgo_linux64)
echo "csgo pid: $csgo_pid"

if grep -q "libthrift_c_glib.so" /proc/"$csgo_pid"/maps; then
  sudo gdb -n -q -batch-silent \
    -ex "set logging on" \
    -ex "set logging file /dev/null" \
    -ex "set logging redirect on" \
    -ex "attach $csgo_pid" \
    -ex "set \$dlopen = (void*(*)(char*, int)) dlopen" \
    -ex "set \$dlclose = (int(*)(void*)) dlclose" \
    -ex "set \$library = \$dlopen(\"/usr/lib/libthrift_c_glib.so\", 6)" \
    -ex "call \$dlclose(\$library)" \
    -ex "call \$dlclose(\$library)" \
    -ex "detach" \
    -ex "quit"
else
  echo "nothing to uninject"
  exit 0
fi

echo "uninjected"