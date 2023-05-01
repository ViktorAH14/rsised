 
#!/bin/bash

#########
set -e # stop on error

#Variable
APP=rsised
EXT=rse
COMMENT=Drawing up schemes for the arrangement of forces and means in case of fire
EXEC=/usr/bin/$APP
LOGO=./icons/hicolor/48x48/rsised.png
ICONS_PATH="/usr/share/icons/hicolor"
DESKTOP_PATH="/usr/share/applications"
INSTALL_PATH="/opt/rsised"
LINK_PATH="/usr/bin/rsised"

#Check user
if [[ $EUID -ne 0 ]]; then
    echo "This script must be run as root"
    exit 1
fi

#Remove old version
if [ -d $INSTALL_PATH ]; then
    $INSTALL_PATH'/uninstall.sh' > /dev/null
fi

xdg-icon-resource install --context mimetypes --size 48 $LOGO application-x-$APP

echo "<?xml version=\"1.0\" encoding=\"UTF-8\"?>
<mime-info xmlns=\"http://www.freedesktop.org/standards/shared-mime-info\">
    <mime-type type=\"application/x-$APP\">
        <comment>$COMMENT</comment>
        <icon name=\"application-x-$APP\"/>
        <glob pattern=\"*.$EXT\"/>
    </mime-type>
</mime-info>" > $APP-mime.xml

xdg-mime install $APP-mime.xml
rm $APP-mime.xml
update-mime-database $HOME/.local/share/mime

#echo "[Desktop Entry]
#Name=$APP
#Name[ru_RU]=РСиСед
#GenericName=Vector editor for firefighters
#GenericName[ru_RU]=Векторный редактор для пожарных
#Exec=$EXEC %U
#MimeType=application/x-$APP
#Icon=application-x-$APP
#Terminal=false
#Type=Application
#Categories=Graphics;Qt
#Comment=$COMMENT
#Comment[ru_RU]=Составление схем расстановки сил и средств при пожаре
#Path=/home/
#StartupNotify=true
#Version=0.1.0
#X-KDE-SubstituteUID=false
#"> $APP.desktop
desktop-file-install --dir=$DESKTOP_PATH $APP.desktop
rm $APP.desktop
#update-desktop-database $HOME/.local/share/applications
##############

echo "rsised install..."
mkdir -v $INSTALL_PATH
cp -v rsised.sh $INSTALL_PATH
chmod u+x uninstall.sh
cp -v uninstall.sh $INSTALL_PATH
cp -rv plugins $INSTALL_PATH
cp -rv lib $INSTALL_PATH
cp -rv bin $INSTALL_PATH
#cp -v rsised.desktop $DESKTOP_PATH
ln -sv $INSTALL_PATH'/rsised.sh' $LINK_PATH
chmod a+x $LINK_PATH
echo "---"
cp -v icons/hicolor/32x32/rsised.png $ICONS_PATH'/32x32/apps'
cp -v icons/hicolor/48x48/rsised.png $ICONS_PATH'/48x48/apps'
cp -v icons/hicolor/64x64/rsised.png $ICONS_PATH'/64x64/apps'
cp -v icons/hicolor/72x72/rsised.png $ICONS_PATH'/72x72/apps'
cp -v icons/hicolor/96x96/rsised.png $ICONS_PATH'/96x96/apps'
cp -v icons/hicolor/128x128/rsised.png $ICONS_PATH'/128x128/apps'
cp -v icons/hicolor/256x256/rsised.png $ICONS_PATH'/256x256/apps'
cp -v icons/hicolor/512x512/rsised.png $ICONS_PATH'/512x512/apps'
cp -v icons/hicolor/scalable/rsised.svg $ICONS_PATH'/scalable/apps'

gtk-update-icon-cache $ICONS_PATH
update-desktop-database $DESKTOP_PATH
xdg-mime default $APP.desktop application/x-$APP

echo "...finished!"
