#include <QApplication>
#include "../include/gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    return a.exec();
}
