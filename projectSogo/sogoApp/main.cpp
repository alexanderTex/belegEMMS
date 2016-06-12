#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "../include/gui/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;

    if(translator.load("sogoApp_de"))
    {
        std::cout << "translator loaded" << std::endl;
    }
    else
    {
        std::cout << "translator did not load...whyever!!!" << std::endl;
    }
    app.installTranslator(&translator);

    MainWindow w;

    return app.exec();
}
