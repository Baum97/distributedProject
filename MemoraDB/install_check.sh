#!/bin/bash

# Check if Check is already installed
check_installed=$(dpkg-query -W -f='${Status}' check 2>/dev/null | grep -c "ok installed")

if [ $check_installed -eq 0 ]; then
    echo "Check is not installed. Installing..."
    
    # Add Check source to APT
    sudo sh -c 'echo "deb http://deb.debian.org/debian/ buster main" >> /etc/apt/sources.list'
    sudo sh -c 'echo "deb-src http://deb.debian.org/debian/ buster main" >> /etc/apt/sources.list'
    
    # Update APT package index
    sudo apt-get update -y

    # Install Check
    sudo apt-get install check -y
    echo "Check has been installed successfully."
else
    echo "Check is already installed."
fi
