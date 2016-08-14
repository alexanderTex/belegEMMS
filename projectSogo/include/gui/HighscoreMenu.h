#ifndef HIGHSCOREMENU_H
#define HIGHSCOREMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QEvent>
#include <QWidget>
#include <QScrollArea>

#include "GameView.h"
#include "stringutlities.h"

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

    void LoadHighScores();

signals:
    void showStartMenu();

public slots:

private:
    QVBoxLayout *m_controlLayout;

    QLabel *m_mainMenueLabel;

    QScrollArea *m_scoresDisplayScroll;
    QWidget *m_scoreDisplay;
    QVBoxLayout *m_scoreLayout;

    QLabel *nummer;
    QLabel *name1;
    QLabel *name2;
    QLabel *winner;
    QLabel *moveCount;

    std::vector<QWidget*> *scores;

    QPushButton *m_backToMainButtonHS;

    QLabel  *nummer,
            *name1,
            *name2,
            *winner,
            *moveCount;
};

#endif // HIGHSCOREMENU_H
