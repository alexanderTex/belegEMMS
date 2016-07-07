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

    inline void ChangeLanguage()
    {
        qApp->removeTranslator(m_translator);

        delete(m_translator);

        m_translator = new QTranslator();

        if(m_languageEnglish)
        {
            if(m_translator->load(":/sprache/Translations/sogoapp_de.qm"))
            {
                std::cout << "translator loaded" << std::endl;
            }
            else
            {
                std::cout << "translator did not load...whyever!!!" << std::endl;
            }
            m_languageEnglish = false;
        }
        else
        {
            if(m_translator->load(":/sprache/Translations/sogoapp_en.qm"))
            {
                std::cout << "translator loaded" << std::endl;
            }
            else
            {
                std::cout << "translator did not load...whyever!!!" << std::endl;
            }
            m_languageEnglish = true;
        }
        // qm datei muss in Ressource ordner sein um geladen werden

        qApp->installTranslator(m_translator);

    }

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

    QPushButton *m_changeLanguageButton;
    QTranslator *m_translator;

    QVBoxLayout *m_allAroundLayout;

    QStackedLayout *m_layout;

    GameView *m_gameView;
    PauseMenu *m_pauseMenu;

    StartMenu *m_startMenu;
    HighscoreMenu * m_highscoreMenu;
    NewSessionMenu *m_newSessionMenu;

};

#endif // MAINWINDOW_H
