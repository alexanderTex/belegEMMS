#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTranslator>
#include <QEvent>

class PauseMenu : public QWidget
{
    Q_OBJECT
public:
    explicit PauseMenu(QWidget *parent = 0);

    void changeEvent(QEvent *event);

signals:
    void ResumeButtonPressed();
    void SaveButtonPressed();
    void QuitGameButtonPressed();

public slots:

private:
    QVBoxLayout *m_pauseMenuLayout;

    QPushButton *m_resumeButton;
    QPushButton *m_saveButton;
    QPushButton *m_quitGameButton;

};

#endif // PAUSEMENU_H
