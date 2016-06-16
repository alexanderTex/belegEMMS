#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class PauseMenu : public QWidget
{
    Q_OBJECT
public:
    explicit PauseMenu(QWidget *parent = 0);

signals:
    void ResumeButtonPressed();
    void SaveButtonPressed();
    void OptionButtonPressed();
    void QuitButtonPressed();

public slots:

private:
    QVBoxLayout *m_pauseMenuLayout;

    QPushButton *m_resumeButton;
    QPushButton *m_saveButton;
    QPushButton *m_optionsButton;
    QPushButton *m_quitButton;

};

#endif // PAUSEMENU_H
