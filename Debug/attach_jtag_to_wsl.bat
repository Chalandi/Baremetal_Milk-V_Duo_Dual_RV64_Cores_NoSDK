@echo off

set vid_pid=32bf:b210

usbipd bind --hardware-id %vid_pid% --force
usbipd.exe attach -w --hardware-id %vid_pid%

pause

