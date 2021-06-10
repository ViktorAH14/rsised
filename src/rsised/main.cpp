#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication rsised(argc, argv);
    MainWindow mainwindow;
    mainwindow.show();
    return rsised.exec();
}
