#ifndef GAMEINPUTAREA_H
#define GAMEINPUTAREA_H

#include <QWidget>
#include <QStackedLayout>
#include <QTabWidget>
#include <QEvent>

#include "PlayerInput.h"
#include "HistoryDisplay.h"

/**
 * @brief The GameInputArea class.
 *
 * @author Nils Brandt
 * @author Alexander Luedke
 *
 * @date 08. August 2016
 *
 * @version 1.0
 * Add Documentation
 */
class GameInputArea : public QTabWidget
{
    Q_OBJECT
public:
    explicit GameInputArea(GameManager *gameManager, QWidget *parent = 0);

    /**
     * @brief Change the language
     * @param event which change
     */
    inline void changeEvent(QEvent *event)
    {
        if (event->type() == QEvent::LanguageChange) {
            this->setTabText(0,tr("Player Input"));
            this->setTabText(1, tr("History Display"));

        } else
            QWidget::changeEvent(event);
    }

    virtual ~GameInputArea();

    inline HistoryDisplay *GetHistoryDisplay() const
    {
        return this->m_historyDisplay;
    }

    inline PlayerInput *GetPlayerInputControls() const
    {
        return this->m_playerInput;
    }

private:

    HistoryDisplay *m_historyDisplay;   /**< Using object to documentation and display the history. */

    PlayerInput *m_playerInput;         /**< Get the playerinput. /*


};

#endif // GAMEINPUTAREA_H
