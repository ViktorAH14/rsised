#!/bin/bash

deployConfig=$1
RED='\033[0;31m'
NC='\033[0m' # No Color

echo "Deploy config = "$deployConfig

case $deployConfig in
#    win32 ) 
#        cqtdeployer -confFile ./win32_deploy.json;; 
#    win64 ) 
#        cqtdeployer -confFile ./win64_deploy.json;;
    linux )
        echo "The assembly of the rsised.tar.gz distribution kit for Linux has begun"
        deployPrefix="../../deploy"
        distrPrefix="../../distr/linux"
        cqtdeployer -confFile $deployPrefix/linux/tar_gz/cqt_linux_targz.json
        cp -v $deployPrefix/linux/tar_gz/install.sh $distrPrefix/tar_gz
        cp -v $deployPrefix/linux/tar_gz/uninstall.sh $distrPrefix/tar_gz
        cp -v $deployPrefix/linux/tar_gz/rsised.desktop $distrPrefix/tar_gz
        cp -v -r $deployPrefix/icons $distrPrefix/tar_gz
        cd $distrPrefix
        tar -zcvf rsised.tar.gz tar_gz/
#        rm -rfv tar_gz/
        if [ -f rsised.tar.gz ]; then
            echo "rsised.tar.gz distribution completed successfully"
        else
            echo -e "${RED}rsised.tar.gz distribution build failed${NC}"
        fi
        
#        cqtdeployer -confFile ./linux_deb.json
#       cqtdeployer -confFile ./linux_qif.json
       ;;
esac
 exit 0
