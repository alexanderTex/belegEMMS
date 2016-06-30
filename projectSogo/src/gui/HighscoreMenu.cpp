#include "HighscoreMenu.h"

HighscoreMenu::HighscoreMenu(QWidget *parent) : QWidget(parent)
{
    this->m_controlLayout = new QVBoxLayout(this);

    this->m_mainMenueLabel = new QLabel(tr("Highscore"));
    this->m_mainMenueLabel->setAlignment(Qt::AlignHCenter);
    this->m_mainMenueLabel->setFont(QFont("Times",18,QFont::Bold));
    this->m_controlLayout->addWidget(m_mainMenueLabel);

    this->m_backToMainButtonHS = new QPushButton(tr("back"));
    QObject::connect(m_backToMainButtonHS, &QPushButton::clicked, this, &HighscoreMenu::showStartMenu);
    this->m_controlLayout->addWidget(m_backToMainButtonHS);
}
