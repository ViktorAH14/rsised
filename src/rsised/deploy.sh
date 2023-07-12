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
echo "Deploy config = ${DEPLOY_CONFIG}"
VERSION="$2"
echo "VERSION = ${VERSION}"
NC='\033[0m' # No Color
RED='\033[0;31m'
SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" &>/dev/null && pwd -P)
echo "SCRIPT_DIR = "${SCRIPT_DIR}
TARGZ_DIR=../../distr/linux
echo "TARGZ_DIR = "${TARGZ_DIR}
ICONS_DIR=../../icons/hicolor
echo "ICONS_DIR = "${ICONS_DIR}
echo "PWD = $(pwd)"

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
        if [ -d "${TARGZ_DIR}/tar_gz" ]; then
            rm -rfv "${TARGZ_DIR}/tar_gz"
        fi

        if [ -f "${SCRIPT_DIR}/cqt_linux_targz.json" ]; then
            rm -fv "${SCRIPT_DIR}/cqt_linux_targz.json"
        fi

        if [ -f "${SCRIPT_DIR}/install.sh" ]; then
            rm -fv "${SCRIPT_DIR}/install.sh"
        fi

        if [ -f "${SCRIPT_DIR}/uninstall.sh" ]; then
            rm -fv "${SCRIPT_DIR}/uninstall.sh"
        fi

        if [ -f "${SCRIPT_DIR}/rsised.desktop" ]; then
            rm -fv "${SCRIPT_DIR}/rsised.desktop"
        fi

        if [ -f "${SCRIPT_DIR}/README" ]; then
            rm -fv "${SCRIPT_DIR}/README"
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
        echo "The assembly of the rsised_${VERSION}.tar.gz distribution kit for Linux has begun"
        cqtdeployer -confFile ${SCRIPT_DIR}/cqt_linux_targz.json
        mv -v install.sh ${TARGZ_DIR}/tar_gz
        mv -v uninstall.sh ${TARGZ_DIR}/tar_gz
        mv -v rsised.desktop ${TARGZ_DIR}/tar_gz
        mv -v README ${TARGZ_DIR}/tar_gz
        cp -v -r ${ICONS_DIR} ${TARGZ_DIR}/tar_gz/icons
        cd ${TARGZ_DIR}
        echo "PWD = $(pwd)"
        tar -zvcf rsised_${VERSION}.tar.gz tar_gz/
        cd ${SCRIPT_DIR}
        echo "PWD = $(pwd)"
        if [ -f "${TARGZ_DIR}/rsised_${VERSION}.tar.gz" ]; then
            echo "rsised_${VERSION}.tar.gz distribution completed successfully"
        else
            echo -e "${RED}rsised_${VERSION}.tar.gz distribution build failed${NC}"
        fi

        #[BUILD_LINUX_DEB]
#        cqtdeployer -confFile ./linux_deb.json
        #[BUILD_LINUX_QIF]
#       cqtdeployer -confFile ./linux_qif.json
       ;;
esac
exit 0
