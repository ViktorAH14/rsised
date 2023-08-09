#!/bin/bash

#########################################################################################
# File: deploy.sh                                                                       #
#                                                                                       #
# Description: The deploy.sh file is a bash script that creates distributions           #
# of the RSiSed application for Linux and Windows. The script is run from the           #
# rsised.pro file (Deploy section) during the release build. Depending on which         #
# compiler is used when building the application, the distribution kit for the          #
# corresponding operating system will be built. To extract dependent libraries,         #
# the script uses the CQtDeployer utility <https://github.com/QuasarApp/CQtDeployer>.   #
#                                                                                       #
# Created: Mar 18 2023                                                                  #
#                                                                                       #
# Copyright: (c) 2022 by Viktor Ermolov <ermolovva@gmail.com>.                          #
#                                                                                       #
# This file is part of the RSiSed project, a editor of the alignment of forces          #
# and means in extinguishing a fire. (RSiSed)                                           #
#                                                                                       #
# RSiSed is free software: you can redistribute it and/or modify                        #
# it under the terms of the GNU General Public License as published by                  #
# the Free Software Foundation, either version 3 of the License, or                     #
# (at your option) any later version.                                                   #
#                                                                                       #
# RSiSed is distributed in the hope that it will be useful,                             #
# but WITHOUT ANY WARRANTY; without even the implied warranty of                        #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                          #
# GNU General Public License for more details.                                          #
#                                                                                       #
# You should have received a copy of the GNU General Public License                     #
# along with this program.  If not, see <https://www.gnu.org/licenses/>.                #
#                                                                                       #
# Email: <ermolovva@gmail.com>                                                          #
#########################################################################################

set -Eeuo pipefail # stop on error

# [VARIABLE]
DEPLOY_CONFIG="$1"
VERSION="$2"
APP="$3"
NC='\033[0m' # No Color
RED='\033[0;31m'
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd -P)
TARGZ_DIR=../../distr/linux
ICONS_DIR=../../icons/hicolor

cleanup () {
    case "${DEPLOY_CONFIG}" in
#        win32 )
            #[CLEAN_WIN32]
#            ;;
#        win64 )
            #[CLEAN_WIN64]
#            ;;
        linux )
        #[CLEAN_LINUX_TARGZ]
        if [ -d ${TARGZ_DIR}/${APP}-${VERSION} ]; then
            rm -rfv ${TARGZ_DIR}/${APP}-${VERSION}
        fi

        if [ -f ${SCRIPT_DIR}/cqt_linux_targz.json ]; then
            rm -fv ${SCRIPT_DIR}/cqt_linux_targz.json
        fi

        if [ -f ${TARGZ_DIR}/rsised-${VERSION}.tar.gz ]; then
            echo "The build of the ${APP}-${VERSION}.tar.gz distribution completed successfully"
        else
            echo -e "${RED} ${APP}-${VERSION}.tar.gz distribution build failed${NC}"
        fi
        #[CLEAN_LINUX_DEB]
        #[CLEAN_LINUX_QIF]
        ;;
    esac
}

trap cleanup SIGINT SIGTERM ERR EXIT # Clearing when signals are received

# [BUILD_DISTR]
case "${DEPLOY_CONFIG}" in
#    win32 ) 
        #[BUILD_WIN32]
#        cqtdeployer -confFile ./win32_deploy.json;; 
#    win64 ) 
        #[BUILD_WIN64]
#        cqtdeployer -confFile ./win64_deploy.json;;
    linux )
        #[BUILD_LINUX_TARGZ]
        echo "The assembly of the ${APP}-${VERSION}.tar.gz distribution kit for Linux has begun"
        mkdir ${TARGZ_DIR}/${APP}-${VERSION}
        cqtdeployer -confFile ${SCRIPT_DIR}/cqt_linux_targz.json
        mv -v install.sh ${TARGZ_DIR}/${APP}-${VERSION}
        mv -v uninstall.sh ${TARGZ_DIR}/${APP}-${VERSION}
        mv -v ${APP}.desktop ${TARGZ_DIR}/${APP}-${VERSION}
        mv -v ${APP}-mime.xml ${TARGZ_DIR}/${APP}-${VERSION}
        mv -v README ${TARGZ_DIR}/${APP}-${VERSION}
        cp -v -r ${ICONS_DIR} ${TARGZ_DIR}/${APP}-${VERSION}/icons
        cd ${TARGZ_DIR}
        tar -zvcf ${APP}-${VERSION}.tar.gz ${APP}-${VERSION}/
        cd ${SCRIPT_DIR}

        #[BUILD_LINUX_DEB]
#        cqtdeployer -confFile ./linux_deb.json
        #[BUILD_LINUX_QIF]
#       cqtdeployer -confFile ./linux_qif.json
       ;;
esac
exit 0
