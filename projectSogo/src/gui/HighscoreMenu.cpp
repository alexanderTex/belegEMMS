#include "HighscoreMenu.h"

HighscoreMenu::HighscoreMenu(QWidget *parent) : QWidget(parent)
{
    this->m_controlLayout = new QVBoxLayout(this);

    this->m_mainMenueLabel = new QLabel(tr("Highscore"));
    this->m_mainMenueLabel->setAlignment(Qt::AlignHCenter);
    this->m_mainMenueLabel->setFont(QFont("Times",18,QFont::Bold));
    this->m_controlLayout->addWidget(m_mainMenueLabel);

    this->m_backToMainButtonHS = new QPushButton(tr("Back"));
    QObject::connect(m_backToMainButtonHS, &QPushButton::clicked, this, &HighscoreMenu::showStartMenu);
    this->m_controlLayout->addWidget(m_backToMainButtonHS);
}

void HighscoreMenu::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        m_mainMenueLabel->setText(tr("Highscore"));
        m_backToMainButtonHS->setText(tr("Back"));
    } else
        QWidget::changeEvent(event);
}
