#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "../include/gui/mainwindow.h"

#include "Menu.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    QSurfaceFormat glFormat;
    glFormat.setVersion(3,3);
    glFormat.setProfile(QSurfaceFormat::CoreProfile);
    QSurfaceFormat::setDefaultFormat(glFormat);


    QTranslator *translator = new QTranslator();

    if(translator->load(":/sprache/Translations/sogoapp_de.qm"))
    {
        std::cout << "translator loaded" << std::endl;
    }
    else
    {
        std::cout << "translator did not load...whyever!!!" << std::endl;
    }

    // qm datei muss in Ressource ordner sein um geladen werden

    app.installTranslator(translator);

    MainWindow w(translator);

    QObject::connect(&w, &MainWindow::QuitMainWindow, &app, &QApplication::quit);

    Menu m;

    return app.exec();
}
