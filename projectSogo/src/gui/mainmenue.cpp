#include <mainmenue.h>
#include <QVBoxLayout>

using namespace std;

MainMenue::MainMenue(QMainWindow &mainWindow)
{
    fillWidgetStack();

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_widgetStack, 1);



    // Main Widget
    m_mainWidget->setLayout(mainLayout);
    mainWindow.setCentralWidget(m_mainWidget);

}

void MainMenue::fillWidgetStack()
{
    m_widgetStack = new QStackedWidget;

    m_widgetStack->addWidget(createStartMenueWidget());
    m_widgetStack->addWidget(createStartMenueWidget());
    m_widgetStack->addWidget(createPauseMenueWidget());
    /*
    m_widgetStack->addWidget(createNewSessionMenueWidget());
    m_widgetStack->addWidget(createHighscoreWidget());
    m_widgetStack->addWidget(createLoadWidget());
    m_widgetStack->addWidget(createSaveWidget());
    */
}

QWidget MainMenue::createStartMenueWidget()
{
    m_startMenue = new QWidget;

    QVBoxLayout *startMenueLayout = new QVBoxLayout;
    m_startMenue->setLayout(startMenueLayout);

    QPushButton *newSessionButton = new QPushButton;
    QPushButton *loadButton = new QPushButton;
    QPushButton *highscoreButton = new QPushButton;
    QPushButton *exitButton = new QPushButton;

    return &m_startMenue;
}


