#include "LoadMenu.h"

LoadMenu::LoadMenu(QWidget *parent) : QWidget(parent)
{
    this->m_controlLayout = new QVBoxLayout(this);
    this->m_controlButton = new QHBoxLayout();
    this->m_controlLayout->addLayout(m_controlButton);

    this->m_mainMenueLabel = new QLabel(tr("Load"));
    this->m_mainMenueLabel->setAlignment(Qt::AlignHCenter);
    this->m_mainMenueLabel->setFont(QFont("Times",18,QFont::Bold));
    this->m_controlLayout->addWidget(m_mainMenueLabel);

    this->m_backToMainButtonLG = new QPushButton(tr("Zrueck"));
    this->m_controlButton->addWidget(m_backToMainButtonLG);

    this->m_loadGameButton = new QPushButton(tr("Laden"));
    this->m_controlButton->addWidget(m_loadGameButton);

}
