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

/**
 * @brief The StartMenu class. It is the first screnn to choose an option.
 *
 * @author Nils Brandt
 * @author Alexander Luedke
 *
 * @date 08. August 2016
 *
 * @version 1.0
 * Add Documentation
 */
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
    /**
     * @brief Switch to NewSessionMenu when the m_newSessionButton is pressed.
     */
    void switchToNewSession();

    /**
     * @brief Switch to Highscore when the m_highscoreButton is pressed.
     */
    void switchToHighscore();

    /**
     * @brief Quit the game when the button is pushed.
     */
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
