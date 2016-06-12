#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "../include/gui/mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;

    translator.load("sogoApp_de");
    app.installTranslator(&translator);


    MainWindow w;

    return app.exec();
}
