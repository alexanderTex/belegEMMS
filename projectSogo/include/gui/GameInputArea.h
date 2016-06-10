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
    explicit GameInputArea(GameManager *gameManager, QWidget *parent = 0);

    virtual ~GameInputArea();

    inline void SelectHistoryView()
    {
        this->m_inputAreaLayout->setCurrentWidget(this->m_historyDisplay);
    }


    inline void SelectInputView()
    {
        this->m_inputAreaLayout->setCurrentWidget(this->m_playerInput);
    }

    inline HistoryDisplay *GetHistoryDisplay() const
    {
        return this->m_historyDisplay;
    }

    inline PlayerInput *GetPlayerInputControls() const
    {
        return this->m_playerInput;
    }

private:

    QVBoxLayout *m_main;

    QWidget *m_viewSelectionArea;

    QHBoxLayout *m_selectionLayout;
    QPushButton *m_historyView;
    QPushButton *m_inputView;

    QWidget *m_inputInfoDisplayArea;

    QStackedLayout *m_inputAreaLayout;

    HistoryDisplay *m_historyDisplay;

    PlayerInput *m_playerInput;


};

#endif // GAMEINPUTAREA_H
