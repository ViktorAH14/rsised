 
#!/bin/bash

iconsPath="/usr/share/icons/hicolor"
desktopPath="/usr/share/applications" 
installPath="/opt/rsised"
linkPath="/usr/bin/rsised"

#Check user
if [[ $EUID -ne 0 ]]; then
    echo "This script must be run as root"
    exit 1
fi

#Remove old version
if [ -d $installPath ]; then
    $installPath'/uninstall.sh' > /dev/null   
fi
    
echo "rsised install..."
mkdir -v $installPath
cp -v rsised.sh $installPath
cp -v uninstall.sh $installPath
cp -rv plugins $installPath
cp -rv lib $installPath
cp -rv bin $installPath
cp -v rsised.desktop $desktopPath
ln -sv $installPath'/rsised.sh' $linkPath
chmod a+x $linkPath
echo "---"
cp -v icons/32x32/rsised.png $iconsPath'/32x32/apps'
cp -v icons/48x48/rsised.png $iconsPath'/48x48/apps'
cp -v icons/64x64/rsised.png $iconsPath'/64x64/apps'
cp -v icons/72x72/rsised.png $iconsPath'/72x72/apps'
cp -v icons/96x96/rsised.png $iconsPath'/96x96/apps'
cp -v icons/128x128/rsised.png $iconsPath'/128x128/apps'
cp -v icons/256x256/rsised.png $iconsPath'/256x256/apps'
cp -v icons/512x512/rsised.png $iconsPath'/512x512/apps'
cp -v icons/scalable/rsised.png $iconsPath'/scalable/apps'
gtk-update-icon-cache /usr/share/icons/hicolor
update-desktop-database

echo "...finished!"
