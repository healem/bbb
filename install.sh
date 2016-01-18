#!/bin/bash

dtc -O dtb -o BB-1WIRE-P9-22-00A0.dtbo -b 0 -@ BB-1WIRE-P9-22.dts
cp BB-1WIRE-P9-22-00A0.dtbo /lib/firmware/
echo "BB-1WIRE-P9-22" > /sys/devices/bone_capemgr.9/slots

