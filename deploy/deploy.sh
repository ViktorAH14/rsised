#!/bin/bash

deployConfig=$1

echo "Deploy config = "$deployConfig

case $deployConfig in
#    win32 ) 
#        cqtdeployer -confFile ./win32_deploy.json;; 
#    win64 ) 
#        cqtdeployer -confFile ./win64_deploy.json;;
    linux )
        echo "Starting the deployment linux tar.gz"
        deployPrefix="../../deploy"
        distrPrefix="../../distr/linux"
        cqtdeployer -confFile $deployPrefix/linux/tar_gz/cqt_linux_targz.json
        cp -v $deployPrefix/linux/tar_gz/install.sh $distrPrefix/tar_gz
        cp -v $deployPrefix/linux/tar_gz/uninstall.sh $distrPrefix/tar_gz
        cp -v $deployPrefix/linux/tar_gz/rsised.desktop $distrPrefix/tar_gz
        cp -v -r $deployPrefix/icons $distrPrefix/tar_gz
        echo "Deploying linux tar.gz was successful"
        
#        cqtdeployer -confFile ./linux_deb.json
#       cqtdeployer -confFile ./linux_qif.json
       ;;
esac
 exit 0
