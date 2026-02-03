# mousemover
A program that moves the mouse randomly using libevdev

> [!WARNING]
> Anyone releated to the development of this application can not be held accountable for any user or third-party service using this application
> For any malicious or unlawful purposes

Inspired from: Daniel Hirish

# Installation

**Arch Linux**: ```sudo pacman -S libevdev```
**Fedora**: ```sudo dnf install libevdev libevdev-devel```
**Debian**: ```sudo apt install libevdev-dev```

# Compiling from source

**NOTE: This application already contains a pre-compiled binary, But if you want to compile from source. Here is how**

**Arch Linux**: ```sudo pacman -S gcc```
**Fedora**: ```sudo dnf install gcc```
**Debian**: ```sudo apt install gcc```

On all systems, ```gcc -Wall -Wextra -I/usr/include/libevdev-1.0 -levdev -o mousemover mousemover.c```


