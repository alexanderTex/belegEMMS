#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QMainWindow>
#include <QGridLayout>

#include "./GameView.h"
#include <QTextEdit>
#include "../include/core/PlayingField.h"
#include "../include/core/GameData.h"
#include "Player.h"
#include "PauseMenu.h"
#include "HighscoreMenu.h"
#include "NewSessionMenu.h"
#include "StartMenu.h"
#include <QEvent>

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    MainWindow(QTranslator *translator, QWidget *parent = 0);
    virtual ~MainWindow();

    inline GameView *GetGameView() const
    {
        return m_gameView;
    }

    /**
     * @brief ShowGameView
     */
    void ShowGameView();

    /**
     * @brief ShowPauseMenu
     */
    void ShowPauseMenu();

    void ChangeLanguage();

    inline void changeEvent(QEvent *event)
    {
        if (event->type() == QEvent::LanguageChange) {
            m_changeLanguageButton->setText(tr("changeButton"));
        } else
            QWidget::changeEvent(event);
    }

    void showNewSessionMenu();

    void showStartMenu();

    void showHighscoreMenu();

    void startNewGame();


signals:
    void QuitMainWindow();

private:
    bool m_languageEnglish = false;
    bool m_isFullscreen = false;

    QPushButton *m_changeLanguageButton;
    QTranslator *m_translator;

    QPushButton *m_fullscreenButton;

    QVBoxLayout *m_allAroundLayout;

    QStackedLayout *m_layout;

    GameView *m_gameView;
    PauseMenu *m_pauseMenu;

    StartMenu *m_startMenu;
    HighscoreMenu * m_highscoreMenu;
    NewSessionMenu *m_newSessionMenu;


    void FullscreenSwitch();

};

#endif // MAINWINDOW_H
