#ifndef HIGHSCOREMENU_H
#define HIGHSCOREMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include <QWidget>

/**
 * @brief The HighscoreMenu class.
 *
 * @author Nils Brandt
 * @author Alexander Luedke
 *
 * @date 08. August 2016
 *
 * @version 1.0
 * Add Documentation
 */
class HighscoreMenu : public QWidget
{
    Q_OBJECT
public:
    explicit HighscoreMenu(QWidget *parent = 0);

    void changeEvent(QEvent *event);

signals:
    void showStartMenu();

public slots:

private:
    QVBoxLayout *m_controlLayout;

    QLabel *m_mainMenueLabel;

    QPushButton *m_backToMainButtonHS;
};

#endif // HIGHSCOREMENU_H
