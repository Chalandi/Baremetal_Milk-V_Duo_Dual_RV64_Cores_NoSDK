@echo off

set vid_pid=32bf:b210

usbipd.exe detach --hardware-id %vid_pid%
usbipd.exe unbind --hardware-id %vid_pid%


pause