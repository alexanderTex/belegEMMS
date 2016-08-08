#include "PauseMenu.h"

#include <QApplication>
#include "Logger.h"

PauseMenu::PauseMenu(QWidget *parent) : QWidget(parent)
{
    m_pauseMenuLayout = new QVBoxLayout(this);

    this->m_resumeButton = new QPushButton(tr("Resume"), this);
    QObject::connect(this->m_resumeButton, &QPushButton::clicked, this, &PauseMenu::ResumeButtonPressed);
    this->m_pauseMenuLayout->addWidget(this->m_resumeButton);

    this->m_saveButton = new QPushButton(tr("Save"), this);
    QObject::connect(this->m_saveButton, &QPushButton::clicked, this, &PauseMenu::SaveButtonPressed);
    this->m_pauseMenuLayout->addWidget(this->m_saveButton);

    this->m_quitGameButton = new QPushButton(tr("Quit"), this);
    QObject::connect(this->m_quitGameButton, &QPushButton::clicked, this, &PauseMenu::QuitGameButtonPressed);
    this->m_pauseMenuLayout->addWidget(this->m_quitGameButton);

}

void PauseMenu::changeEvent(QEvent *event)
    {
        if (event->type() == QEvent::LanguageChange) {
            m_resumeButton->setText(tr("Resume"));
            m_saveButton->setText(tr(("Save")));
            m_quitGameButton->setText(tr("Quit"));

        } else
            QWidget::changeEvent(event);
    }
