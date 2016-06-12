#ifndef GAMEINPUTAREA_H
#define GAMEINPUTAREA_H

#include <QWidget>
#include <QStackedLayout>
#include <QTabWidget>

#include "PlayerInput.h"
#include "HistoryDisplay.h"


class GameInputArea : public QTabWidget
{
    Q_OBJECT
public:
    explicit GameInputArea(GameManager *gameManager, QWidget *parent = 0);

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
