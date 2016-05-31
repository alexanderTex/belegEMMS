#ifndef GAMEINPUTAREA_H
#define GAMEINPUTAREA_H

#include <QWidget>
#include <QStackedLayout>

#include "PlayerInput.h"
#include "HistoryDisplay.h"


class GameInputArea : public QWidget
{
    Q_OBJECT
public:
    explicit GameInputArea(GameData *data, QWidget *parent = 0);

private:

    QStackedLayout *m_inputAreaLayout;

    HistoryDisplay *m_historyDisplay;

    PlayerInput *m_playerInput;


};

#endif // GAMEINPUTAREA_H
