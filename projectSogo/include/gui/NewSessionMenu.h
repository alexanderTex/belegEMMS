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

/**
 * @brief The NewSessionMenu class. To set additional options for a new Game.
 *
 * @author Nils Brandt
 * @author Alexander Luedke
 *
 * @date 08. August 2016
 *
 * @version 1.0
 * Add Documentation
 */
class NewSessionMenu : public QWidget
{
    Q_OBJECT
public:
    /**
     * @brief The area for the size of the playfield.
     */
    void setPlayfield();

    /**
     * @brief The area to set the severity.
     */
    void setMode();

    /**
     * @brief To handle the translator.
     * @param event The "change language" event.
     */
    void changeEvent(QEvent *event);

    /**
     * @brief The constructor
     * @param parent
     */
    explicit NewSessionMenu(QWidget *parent = 0);

    /**
     * @brief Set the gamedata object.
     * @see checkPlayfieldSize()
     * @see setPlayer()
     * @see checkSkill()
     */
    void mergeGameData();

    /**
     * @brief Set the playfieldsize.
     */
    void checkPlayfieldSize();

    /**
     * @brief Check and set the type of player.
     */
    void setPlayer();

    /**
     * @brief Check and set the severity.
     */
    void checkSkill();

    GameData *m_gameData;   /**< Holds a reference to the PlayingField to both players and which one is the currentplayer. */

signals:
    /**
     * @brief The signal for QStackedWidget to show the startmenu.
     */
    void showStartMenu();

    /**
     * @brief The signal to create a gamedata object.
     * @param gameData Holds a reference to the PlayingField to both players and which one is the currentplayer.
     */
    void createGameData(GameData gameData);

    /**
     * @brief The signal to start the game.
     */
    void startGame();

private:
    QVBoxLayout *m_controlLayout,               /**< Menulayout */
                *m_checkBoxPlayfieldLayout,     /**< Layout to set the playfieldsize */
                *m_checkBoxNetworkLayout;       /**< Layout to set the network settings */

    QHBoxLayout *m_skillBoxLayout;              /**< Layout to set severity. */

    QLabel  *m_mainMenueLabel,                  /**< Mainlabel */
            *m_checkBoxNetworkLabel,            /**< Networkchekboxlabel */
            *m_hostadress,                      /**< Hostadresslabel */
            *m_hostport;                        /**< Portlabel */

    QLineEdit   *m_input1stPlayername,          /**< Nameinput for player one */
                *m_input2ndPlayername,          /**< Nameinput for plaer two */
                *m_inputHostaddress,            /**< Hostaddressinput */
                *m_inputHostport;               /**< Portinput */

    QCheckBox   *m_checkBoxPlayfieldSizeX3,     /**< Checkbox for playfield */
                *m_checkBoxPlayfieldSizeX4,     /**< Checkbox for playfield */
                *m_checkBoxPlayfieldSizeX5,     /**< Checkbox for playfield */
                *m_checkBoxPvC,                 /**< Checkbox for pvc game */
                *m_checkBoxPvPlocal,            /**< Checkbox for pvp(local) game */
                *m_checkBoxPvPnetwork;          /**< Checkbox for pvc(network) game */

    QRadioButton    *m_radioButtonskill1,       /**< Set the severity to 1 */
                    *m_radioButtonskill2,       /**< Set the severity to 2 */
                    *m_radioButtonskill3;       /**< Set the severity to 3 */

    QGroupBox   *m_playfieldGroupBox,           /**< Groupbox to set the exclusiv option for playfield. */
                *m_modeGroupBox,                /**< Groupbox to set the exclusiv option for playmode. */
                *m_skillGroupBox;               /**< Groupbox to set the exclusiv option for severity. */

    QButtonGroup    *m_checkButtonGrp,          /**< To encapsulate the buttons */
                    *m_checkPlayerSkillGrp,     /**< To encapsulate the playerskills */
                    *m_checkBoxNetworkGrp;      /**< To encapsulate the networkoptions */

    QGridLayout *m_inputToHostlayout,           /**< Grid for the hostinput */
                *m_input2ndPlayernameLayout;    /**< Grid for the second playername */

    QWidget *m_networkparameterWidget,          /**< Widget for networkparameter */
            *m_skillWidget,                     /**< Widget for severityparameter */
            *m_pvpLocalWidget;                  /**< Widget for local game */

    QPushButton *m_connectButtion,              /**< Networkconnect button */
                *m_backToMainButtonNS,          /**< Back to mainmenu button */
                *m_playGameButton;              /**< Start the game button */

    PlayingField *m_playingField;               /**< The playingfield. @see PayingField */

    Player  *m_player1,                         /**< Player one. @see Player */
            *m_player2;                         /**< Player two. @see Player */

    HistorySave *m_historySave;                 /**< Save game data in the history */
};

#endif // NEWSESSIONMENU_H
