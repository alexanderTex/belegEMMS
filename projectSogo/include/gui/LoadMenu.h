#ifndef LOADMENU_H
#define LOADMENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>

class LoadMenu : public QWidget
{
    Q_OBJECT
public:
    explicit LoadMenu(QWidget *parent = 0);

signals:

public slots:

private:
    QVBoxLayout *m_controlLayout;

    QLabel *m_mainMenueLabel;

    QPushButton *m_backToMainButtonLG;

    QPushButton *m_loadGameButton;

    QHBoxLayout *m_controlButton;
};

#endif // LOADMENU_H
