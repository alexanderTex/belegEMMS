#include "StartMenu.h"

StartMenu::StartMenu(QWidget *parent) : QWidget(parent)
{
    m_controlLayout = new QVBoxLayout(this);

    m_mainMenueLabel = new QLabel(tr("Sogo"));
    m_mainMenueLabel->setAlignment(Qt::AlignHCenter);
    m_mainMenueLabel->setFont(QFont("Times",18,QFont::Bold));

    m_newSessionButton = new QPushButton(tr("new session"));
    m_newSessionButton->setGeometry(30,10,400,30);
    QObject::connect(this->m_newSessionButton, &QPushButton::clicked, this, &StartMenu::switchToNewSession);

    m_highscoreButton = new QPushButton(tr("highscore"));
    m_highscoreButton->setGeometry(30,90,1,30);
    QObject::connect(m_highscoreButton, &QPushButton::clicked, this, &StartMenu::switchToHighscore);

    m_exitButton = new QPushButton(tr("exit"));
    m_exitButton->setGeometry(30,90,400,30);
    QObject::connect(m_exitButton, &QPushButton::clicked, this, &StartMenu::quitGame);

    m_controlLayout->addWidget(m_mainMenueLabel);
    m_controlLayout->addWidget(m_newSessionButton);
    m_controlLayout->addWidget(m_highscoreButton);
    m_controlLayout->addWidget(m_exitButton);
}
