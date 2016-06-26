#ifndef STARTMENU_H
#define STARTMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

class StartMenu : public QWidget
{
    Q_OBJECT
public:
    explicit StartMenu(QWidget *parent = 0);

signals:

public slots:

private:
    QVBoxLayout *m_controlLayout;

    QLabel *m_mainMenueLabel;

    QPushButton *m_newSessionButton;

    QPushButton *m_loadButton;

    QPushButton *m_highscoreButton;

    QPushButton *m_exitButton;
};

#endif // STARTMENU_H
