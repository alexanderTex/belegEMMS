#ifndef HIGHSCOREMENU_H
#define HIGHSCOREMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include <QWidget>

class HighscoreMenu : public QWidget
{
    Q_OBJECT
public:
    explicit HighscoreMenu(QWidget *parent = 0);

    inline void changeEvent(QEvent *event)
    {
        if (event->type() == QEvent::LanguageChange) {
            m_mainMenueLabel->setText(tr("Highscore"));
            m_backToMainButtonHS->setText(tr("Back"));
        } else
            QWidget::changeEvent(event);
    }

signals:
    void showStartMenu();

public slots:

private:
    QVBoxLayout *m_controlLayout;

    QLabel *m_mainMenueLabel;

    QPushButton *m_backToMainButtonHS;
};

#endif // HIGHSCOREMENU_H
