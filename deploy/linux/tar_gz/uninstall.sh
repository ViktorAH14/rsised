 
#!/bin/bash

iconsPath="/usr/share/icons/hicolor"
desktopPath="/usr/share/applications" 
installPath="/opt/rsised"
linkPath="/usr/bin/rsised"
echo "rsised uninstall"

#Check user
if [[ $EUID -ne 0 ]]; then
    echo "This script must be run as root"
    exit 1
fi

#rm -v $iconsPath'/32x32/apps/myapp.png'
#rm -v $iconsPath'/48x48/apps/myapp.png'
#rm -v $iconsPath'/64x64/apps/myapp.png'
#rm -v $iconsPath'/128x128/apps/myapp.png'
#rm -v $iconsPath'/256x256/apps/myapp.png'
#rm -v $desktopPath'/myapp.desktop'

#Remove app folder
echo "---"
rm -rfv $installPath
rm -v  $linkPath

echo "Uninstall finished!"
