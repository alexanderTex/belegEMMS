#include "StartMenu.h"

StartMenu::StartMenu(QWidget *parent) : QWidget(parent)
{
    m_controlLayout = new QVBoxLayout(this);

    m_mainMenueLabel = new QLabel(tr("Sogo"));
    m_mainMenueLabel->setAlignment(Qt::AlignHCenter);
    m_mainMenueLabel->setFont(QFont("Times",18,QFont::Bold));

    m_newSessionButton = new QPushButton(tr("new session"));
    m_newSessionButton->setGeometry(30,10,400,30);

    m_loadButton = new QPushButton(tr("load"));
    m_loadButton->setGeometry(30,90,400,30);

    m_highscoreButton = new QPushButton(tr("highscore"));
    m_highscoreButton->setGeometry(30,90,1,30);

    m_exitButton = new QPushButton(tr("exit"));
    m_exitButton->setGeometry(30,90,400,30);

    m_controlLayout->addWidget(m_mainMenueLabel);
    m_controlLayout->addWidget(m_newSessionButton);
    m_controlLayout->addWidget(m_loadButton);
    m_controlLayout->addWidget(m_highscoreButton);
    m_controlLayout->addWidget(m_exitButton);
}
