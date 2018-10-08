# PSoCCommunication

Requirements for use:

On raspberry:

call in console: systemctl disable hciuart

Add "dtoverlay=pi3-disable-bt" to /boot/config.txt

Maybe:
Remove "console=ttyAMA0,115200" in /boot/cmdline.txt
Might be ttyS0, or serial0 etc.

Reboot. 
