#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QEvent>
#include <QPalette>
#include <QPixmap>
#include "Logger.h"

class StartMenu : public QWidget
{
    Q_OBJECT
public:
    explicit StartMenu(QWidget *parent = 0);

    inline void changeEvent(QEvent *event)
    {
        if (event->type() == QEvent::LanguageChange) {
            m_newSessionButton->setText(tr("New Session"));
            m_highscoreButton->setText(tr(("Highscore")));
            m_exitButton->setText(tr("Exit"));

        } else
            QWidget::changeEvent(event);
    }

signals:
    void switchToNewSession();

    void switchToHighscore();

    void quitGame();

public slots:

private:
    QVBoxLayout *m_controlLayout;

    QLabel *m_mainMenueLabel;

    QPushButton *m_newSessionButton;

    QPushButton *m_highscoreButton;

    QPushButton *m_exitButton;

    QGridLayout *m_gridLayout;
};

#endif // STARTMENU_H
