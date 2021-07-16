#!/bin/bash
# board: WL37, scenario: INDUSTRY-0602, uos: WINDOWS
# pci devices for passthru
declare -A passthru_vpid
declare -A passthru_bdf

passthru_vpid=(
["usb_xdci"]="8086 9ded"
["ethernet"]="8086 157b"
["gpu"]="8086 3ea0"
)
passthru_bdf=(
["usb_xdci"]="0000:00:14.0"
["ethernet"]="0000:02:00.0"
["gpu"]="0000:00:02.0"
)

function launch_windows()
{
#vm-name used to generate uos-mac address
mac=$(cat /sys/class/net/e*/address)
vm_name=post_vm_id$1
mac_seed=${mac:0:17}-${vm_name}

#check if the vm is running or not
vm_ps=$(pgrep -a -f acrn-dm)
result=$(echo $vm_ps | grep -w "${vm_name}")
if [[ "$result" != "" ]]; then
  echo "$vm_name is running, can't create twice!"
  exit
fi

echo ${passthru_vpid["gpu"]} > /sys/bus/pci/drivers/pci-stub/new_id
echo ${passthru_bdf["gpu"]} > /sys/bus/pci/devices/${passthru_bdf["gpu"]}/driver/unbind
echo ${passthru_bdf["gpu"]} > /sys/bus/pci/drivers/pci-stub/bind
modprobe pci_stub
# Passthrough USB_XDCI
echo ${passthru_vpid["usb_xdci"]} > /sys/bus/pci/drivers/pci-stub/new_id
echo ${passthru_bdf["usb_xdci"]} > /sys/bus/pci/devices/${passthru_bdf["usb_xdci"]}/driver/unbind
echo ${passthru_bdf["usb_xdci"]} > /sys/bus/pci/drivers/pci-stub/bind

# Passthrough ETHERNET
echo ${passthru_vpid["ethernet"]} > /sys/bus/pci/drivers/pci-stub/new_id
echo ${passthru_bdf["ethernet"]} > /sys/bus/pci/devices/${passthru_bdf["ethernet"]}/driver/unbind
echo ${passthru_bdf["ethernet"]} > /sys/bus/pci/drivers/pci-stub/bind

mem_size=4096M
#interrupt storm monitor for pass-through devices, params order:
#threshold/s,probe-period(s),intr-inject-delay-time(ms),delay-duration(ms)
intr_storm_monitor="--intr_monitor 10000,10,1,100"

#logger_setting, format: logger_name,level; like following
logger_setting="--logger_setting console,level=4;kmsg,level=3;disk,level=5"

#   -s 0:20:0,passthru,00/14/0 \
#   -s 7,passthru,0/14/0,d3hot_reset \
#   -s 7,xhci,1-4:1-5 \
#   -s 5,virtio-blk,./win10-1909.img,writeback \
acrn-dm -A -m $mem_size -s 0:0,hostbridge -U d2795438-25d6-11e8-864e-cb7a18b34643 \
   --windows \
   $logger_setting \
   -s 2,passthru,0/2/0,gpu  \
   --ovmf /usr/share/acrn/bios/OVMF.fd \
   --cpu_affinity 0,1 \
   $intr_storm_monitor \
   -s 1:0,lpc \
   -l com1,stdio \
   -s 4,passthru,02/00/0 \
   -s 7,passthru,00/14/0,d3hot_reset \
   -s 5,virtio-blk,./win10-1909.img \
   $vm_name
}

# offline SOS CPUs except BSP before launch UOS
for i in `ls -d /sys/devices/system/cpu/cpu[1-99]`; do
        online=`cat $i/online`
        idx=`echo $i | tr -cd "[1-99]"`
        echo cpu$idx online=$online
        if [ "$online" = "1" ]; then
                echo 0 > $i/online
                # during boot time, cpu hotplug may be disabled by pci_device_probe during a pci module insmod
               while [ "$online" = "1" ]; do
                        sleep 1
                        echo 0 > $i/online
                        online=`cat $i/online`
                done
                echo $idx > /sys/class/vhm/acrn_vhm/offline_cpu
        fi
done

launch_windows 1
