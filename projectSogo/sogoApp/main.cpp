#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "../include/gui/mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QTranslator translator;

    if(translator.load(":/de/sogoapp_de/sogoapp_de.qm"))
    {
        std::cout << "translator loaded" << std::endl;
    }
    else
    {
        std::cout << "translator did not load...whyever!!!" << std::endl;
    }

    // qm datei muss in Ressource ordner sein um geladen werden
    //

    app.installTranslator(&translator);

    MainWindow w;

    QObject::connect(&w, &MainWindow::QuitMainWindow, &app, &QApplication::quit);

    return app.exec();
}
