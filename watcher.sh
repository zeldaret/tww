#!/bin/sh

mkdir -p /cores

sleep 20

for pid in $(pgrep wibo); do
    state=$(awk '/State:/ { print $2 }' /proc/$pid/status 2>/dev/null || echo "X")
    echo "Process $pid state: $state"
    if [ "$state" = "T" ]; then
        echo "Process $pid stopped. Dumping core..."
        gdb -q -n -batch \
        -p "$pid" \
        -ex "gcore /cores/core.${pid}.dump" \
        -ex "detach" \
        -ex "quit"
        echo "Done."
        kill -9 "$pid"
        exit 0
    fi
done
