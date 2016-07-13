#ifndef NEWSESSIONMENU_H
#define NEWSESSIONMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QGridLayout>
#include <QPushButton>
#include <QObject>
#include <QEvent>
#include <QGroupBox>
#include <QRadioButton>
#include <QHBoxLayout>

#include "GameData.h"
#include "PlayingField.h"
#include "Player.h"
#include "HistorySave.h"
#include "Logger.h"


class NewSessionMenu : public QWidget
{
    Q_OBJECT
public:
    void setPlayfield();

    void setMode();

    inline void changeEvent(QEvent *event)
    {
        if (event->type() == QEvent::LanguageChange) {
            m_mainMenueLabel->setText(tr("New Session"));
            m_input1stPlayername->setText(tr(("Player1")));
            m_playfieldGroupBox->setTitle(tr("Playfield"));
            m_input2ndPlayername->setText(tr("Player2"));
            m_checkBoxPvPnetwork->setText(tr("PvP(network)"));
            m_checkBoxPvPlocal->setText(tr("PvP(local)"));
            m_hostadress->setText(tr("Hostaddress:"));
            m_inputHostaddress->setText(tr("Hostaddress"));
            m_hostport->setText(tr("Port:"));
            m_inputHostport->setText(tr("Port"));
            m_connectButtion->setText(tr("Connect"));
            m_playGameButton->setText(tr("Start Game"));
            m_backToMainButtonNS->setText(tr("Back"));
        } else
            QWidget::changeEvent(event);
    }

    explicit NewSessionMenu(QWidget *parent = 0);

    GameData *m_gameData;

    void mergeGameData();

    void checkPlayfieldSize();

    void setPlayer();

    void checkSkill();

    // network / solo
    void setGameEnviorment();

signals:
    void showStartMenu();

    void createGameData(GameData gameData);

    void startGame();

public slots:

private:
    QVBoxLayout *m_controlLayout,
                *m_checkBoxPlayfieldLayout,
                *m_checkBoxNetworkLayout;

    QHBoxLayout *m_skillBoxLayout;


    QLabel  *m_mainMenueLabel,
            *m_checkBoxNetworkLabel,
            *m_hostadress,
            *m_hostport;


    QLineEdit   *m_input1stPlayername,
                *m_input2ndPlayername,
                *m_inputHostaddress,
                *m_inputHostport;



    QCheckBox   *m_checkBoxPlayfieldSizeX3,
                *m_checkBoxPlayfieldSizeX4,
                *m_checkBoxPlayfieldSizeX5,
                *m_checkBoxPvC,
                *m_checkBoxPvPlocal,
                *m_checkBoxPvPnetwork;

    QRadioButton    *m_radioButtonskill1,
                    *m_radioButtonskill2,
                    *m_radioButtonskill3;

    QGroupBox   *m_playfieldGroupBox,
                *m_modeGroupBox,
                *m_skillGroupBox;

    QButtonGroup    *m_checkButtonGrp,
                    *m_checkPlayerSkillGrp,
                    *m_checkBoxNetworkGrp;

    QGridLayout *m_inputToHostlayout,
                *m_input2ndPlayernameLayout;

    QWidget *m_networkparameterWidget,
            *m_skillWidget,
            *m_pvpLocalWidget;

    QPushButton *m_connectButtion,
                *m_backToMainButtonNS,
                *m_playGameButton;

    // GameData collection


    PlayingField *m_playingField;

    Player  *m_player1,
            *m_player2;

    HistorySave *m_historySave;
};

#endif // NEWSESSIONMENU_H
