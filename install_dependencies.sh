#!/bin/sh

# Check distro base
if [ -f /etc/os-release ]; then
    # freedesktop.org and systemd
    . /etc/os-release
    OS=$NAME
    VER=$VERSION_ID
elif type lsb_release >/dev/null 2>&1; then
    # linuxbase.org
    OS=$(lsb_release -si)
    VER=$(lsb_release -sr)
elif [ -f /etc/lsb-release ]; then
    # For some versions of Debian/Ubuntu without lsb_release command
    . /etc/lsb-release
    OS=$DISTRIB_ID
    VER=$DISTRIB_RELEASE
elif [ -f /etc/debian_version ]; then
    # Older Debian/Ubuntu/etc.
    OS=Debian
    VER=$(cat /etc/debian_version)
elif [ -f /etc/SuSe-release ]; then
    # Older SuSE/etc.
    OS="Not supported"
    VER="Not supported"
elif [ -f /etc/redhat-release ]; then
    # Older Red Hat, CentOS, etc.
    OS="Not supported"
    VER="Not supported"
else
    # Fall back to uname, e.g. "Linux <version>", also works for BSD, etc.
    OS=$(uname -s)
    VER=$(uname -r)
fi

# Show found info
echo "OS info: $OS $VER"

# Install dependencies
if [ "$OS" =  "Arch Linux" ]; then
     echo "Using Pacman"
     manager="pacman"
elif [ "$OS" =  "Debian" ]; then
    echo "Using Aptitude"
    manager="aptitude"
elif [ "$OS" =  "Raspbian GNU/Linux" ]; then
    echo "Using aptitude"
    manager="aptitude"
else
    echo "This distro is not officially supported by us."
    echo "However if you know your distribution should work you can select packet manager manually:"
    while true
    do
        read -r -p "1.Aptitude 2.Pacman 3.Quit [1/2/q] " managerMan

        case $managerMan in
        [1])
            echo "Using aptitude"
            manager="aptitude"
            break
            ;;
        [2])
            echo "Using pacman"
            manager="pacman"
            break
            ;;
        [qQ])
            exit
            ;;
        *)
            echo "Invalid input."
            break
            ;;
        esac
    done
fi

if [ "$manager" = "aptitude" ]; then
    sudo apt-get update && sudo apt-get -y install\
                g++ libxcursor-dev libxrandr-dev libxinerama-dev\
                libxi-dev libopenal-dev libglu1-mesa-dev libxxf86vm-dev

else
    sudo pacman  -Sy base-devel --needed --noconfirm
fi
