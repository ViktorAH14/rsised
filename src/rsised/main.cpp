/*
 * Copyright (c) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 *
 * This file is part of the RSiSed project, a editor of the alignment of forces
 * and means in extinguishing a fire. (RSiSed)
 *
 * RSiSed is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RSiSed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

/*!
 * \mainpage
 * \brief This application is designed for the alignment of forces  and means
 * in case of fire.
 * \date Jun 10 2021
 * \author Ermolov V.A.
 * \copyright Copyright (c) 2022 by Viktor Ermolov <ermolovva@gmail.com>.
 * **RSiSed** is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.<br> **RSiSed** is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details.<br> You should have received a copy of the
 * GNU General Public License along with this program. If not,
 * see <https://www.gnu.org/licenses/>.
 *
 * \section Building
 * Requirements:
 *  QT 5.15.2 <br>
 *  You need to add the following dirrectories:
 *  \list
 *  \li bin/debug
 *  \li bin/profile
 *  \li bin/release
 *  \li build/debug
 *  \li build/profile
 *  \li build/release
 *  \endlist
 *
 *  In QtCreator, you need to disable shadow assembly for all configurations.
 *  \section Bug Bug reports
 *  [GitHub issues]( https://github.com/ViktorAH14/rsised/issues)
 *  \section Requests Requests
 *  [GitHub pull requests](https://github.com/ViktorAH14/rsised/pulls)
 */

#include "mainwindow.h"
#include "config.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication rsised(argc, argv);
    rsised.setApplicationVersion(VERSION);
    rsised.setApplicationDisplayName(APPLICATION_NAME);
    rsised.setApplicationName(APPLICATION_NAME);

    QTranslator rsisedTranslator;
    if (rsisedTranslator.load(QString(":/i18n/rsised_" + QLocale::system().name())))
        rsised.installTranslator(&rsisedTranslator);
    QTranslator libshapesTranslator;
    if (libshapesTranslator.load(QString(":/i18n/libshapes_" + QLocale::system().name())))
        rsised.installTranslator(&libshapesTranslator);

    MainWindow mainwindow;
    mainwindow.show();
    return rsised.exec();
}
