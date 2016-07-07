#ifndef GAMEINPUTAREA_H
#define GAMEINPUTAREA_H

#include <QWidget>
#include <QStackedLayout>
#include <QTabWidget>
#include <QEvent>

#include "PlayerInput.h"
#include "HistoryDisplay.h"

/**
 * @brief The GameInputArea class
 */
class GameInputArea : public QTabWidget
{
    Q_OBJECT
public:
    explicit GameInputArea(GameManager *gameManager, QWidget *parent = 0);

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

    HistoryDisplay *m_historyDisplay;

    PlayerInput *m_playerInput;


};

#endif // GAMEINPUTAREA_H
