#!/bin/bash

#CPU SETUP SCRIPT for Mini-EUSO
#Francesca Capel January 2017
#capel.francesca@gmail.com
#Please see README for correct setup procedure

ZYNQ_IP=192.168.7.10
CPU_IP=192.168.7.2
TEST_IP=8.8.8.8

echo "Mini-EUSO CPU setup"
echo "*******************"

#Download the necessary packages
if ping -q -c 1 -W 1 $TEST_IP > /dev/null 2>&1
then
   echo "Connected to internet..."
   echo "Downloading packages..."
   apt-get -y update 
   apt-get -y install build-essential vsftpd expect libraw1394-11 libgtk2.0-0 \
   libgtkmm-2.4-dev libglademm-2.4-dev libgtkglextmm-x11-1.2-dev libusb-1.0-0 \
   stress bridge-utils git-core
   echo "OK"
else
       echo "Could not connect to internet. Exiting..."
       exit 1
fi

#Setup the FTP server and necessary directories
echo "Setting up the FTP server and directories..."
mkdir /home/minieusouser/DATA > /dev/null 2>&1
chown minieusouser /home/minieusouser/DATA
mkdir /home/minieusouser/DONE > /dev/null 2>&1
chown minieusouser /home/minieusouser/DONE 
rm /etc/vsftpd.conf > /dev/null 2>&1
cp /home/software/CPU/CPUsetup/vsftpd.conf /etc/ > /dev/null 2>&1
mkdir /media/usb > /dev/null 2>&1
mkdir /home/minieusouser/log  > /dev/null 2>&1
echo "OK"

#Setup the test code
mkdir /home/software/CPU/test/bin > /dev/null 2>&1
make -C /home/software/CPU/test/src > /dev/null 2>&1

#Setup symlinks for commands
echo "Creating symlinks"
ln -s /home/software/CPU/zynq/scripts/acqstart_telnet.sh /usr/local/bin/acqstart_telnet
ln -s /home/software/CPU/zynq/scripts/cpu_poll.sh /usr/local/bin/cpu_poll
ln -s /home/software/zynq/scripts/send_telnet_cmd.sh /usr/local/bin/send_telnet_cmd
ln -s /home/software/test/bin/test_systems /usr/local/bin/test_systems
echo "OK"

#Network configuration (need to comment the previous setup)
echo "Setting up the network configuration..."
cp /home/software/CPU/CPUsetup/interfaces /etc/network/ > /dev/null 2>&1
echo "OK"

#Setup the cameras 
echo "Setting up the camera software..."
chmod +x /home/software/CPU/cameras/flycapture2-2.3.2.14-i386/install_flycapture.sh
(cd /home/software/CPU/cameras/flycapture2-2.3.2.14-i386 && sh install_flycapture.sh)
echo "GRUB_DISABLE_OS_PROBER=true" >> /etc/default/grub

#sh -c 'echo 1000 > /sys/module/usbcore/parameters/usbfs_memory_mb'
make -C /home/software/CPU/cameras/test/src
echo "OK"

#Setup the analog board
echo "Setting up the analog board software..."
rmmod rtd520
touch /etc/modprobe.d/blacklist.conf
> /etc/modprobe.d/blacklist.conf 
echo "blacklist rtd520" >> /etc/modprobe.d/blacklist.conf
echo "rtd_dm75xx" >> /etc/modules
make -C /home/software/CPU/analog/driver
(cd /home/software/CPU/analog/driver && make load)
mkdir /lib/modules/$(uname -r)/kernel/rtd/
cp /home/software/CPU/analog/driver/rtd-dm75xx.ko /lib/modules/$(uname -r)/kernel/rtd/
(cd /home/software/CPU/analog/driver && depmod -a)
echo "lsmod | grep rtd:"
lsmod | grep rtd
make -C /home/software/CPU/analog/lib
mkdir /home/software/CPU/analog/bin
make -C /home/software/CPU/analog/src
echo "OK"

#Press enter to continue
read -p "Press enter to continue"

#Setup autologin to root 
echo "Setting up autologin to root user on boot..."
mkdir /etc/systemd/system/getty@tty1.service.d
touch /etc/systemd/system/getty@tty1.service.d/autologin.conf
> /etc/systemd/system/getty@tty1.service.d/autologin.conf
echo "[Service]" >> /etc/systemd/system/getty@tty1.service.d/autologin.conf
echo "ExecStart=" >> /etc/systemd/system/getty@tty1.service.d/autologin.conf
echo "ExecStart=-/sbin/agetty -a root --noclear %I $TERM" >> /etc/systemd/system/getty@tty1.service.d/autologin.conf
echo "OK"

sleep 10
systemctl daemon-reload


#Restart the terminal
systemctl restart getty@tty1.service








   
   
       
   


