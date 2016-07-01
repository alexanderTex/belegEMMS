#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>

class StartMenu : public QWidget
{
    Q_OBJECT
public:
    explicit StartMenu(QWidget *parent = 0);

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
