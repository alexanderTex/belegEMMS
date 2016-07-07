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

    inline void changeEvent(QEvent *event)
    {
        if (event->type() == QEvent::LanguageChange) {
            m_resumeButton->setText(tr("Resume"));
            m_saveButton->setText(tr(("Save")));
            m_quitGameButton->setText(tr("Quit"));

        } else
            QWidget::changeEvent(event);
    }

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
