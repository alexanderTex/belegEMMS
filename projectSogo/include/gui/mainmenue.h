#ifndef MAINMENUE_H
#define MAINMENUE_H

#include <QDialog>
#include <QStackedWidget>
#include <QWidget>
#include <QPushButton>
#include <QMainWindow>



//using namespace std;

class MainMenue : public QDialog
{
    Q_OBJECT
public:
    MainMenue(QMainWindow &mainWindow);

protected:

private:

    QStackedWidget *m_widgetStack;

    QWidget *m_mainWidget;
    QWidget *m_startMenue;
    QWidget *m_pauseMenue;
    QWidget *m_newSessionMenue;
    QWidget *m_highscoreMenue;
    QWidget *m_loadMenue;
    QWidget *m_saveMenue;

    void fillWidgetStack();

    QWidget createStartMenueWidget();
    QWidget createPauseMenueWidget();
    QWidget createNewSessionMenueWidget();
    QWidget createHighscoreWidget();
    QWidget createLoadWidget();
    QWidget createSaveWidget();

};

#endif // MAINMENUE_H
