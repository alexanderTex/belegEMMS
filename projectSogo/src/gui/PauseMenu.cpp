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

    this->m_optionsButton = new QPushButton(tr("Options"), this);
    QObject::connect(this->m_optionsButton, &QPushButton::clicked, this, &PauseMenu::OptionButtonPressed);
    this->m_pauseMenuLayout->addWidget(this->m_optionsButton);

    this->m_quitButton = new QPushButton(tr("Quit"), this);
    QObject::connect(this->m_quitButton, &QPushButton::clicked, this, &PauseMenu::QuitButtonPressed);
    this->m_pauseMenuLayout->addWidget(this->m_quitButton);

}
