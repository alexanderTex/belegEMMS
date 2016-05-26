#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <vector>


#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include "../include/core/GameData.h"
#include "../include/core/Vector3.h"
#include "Gamevisualizer.h"
#include "Gameinputarea.h"

using namespace std;

class GameView : public QWidget
{
    Q_OBJECT
public:
    explicit GameView(GameData *data, QWidget *parent = 0);
    ~GameView();

    inline GameVisualizer *GetVisualizer() const
    {
        return m_gameVis;
    }

private:
    QGridLayout *m_mainLayout;

    GameVisualizer *m_gameVis;
    GameData *m_data;
    GameInputArea *m_inputArea;

signals:

public slots:


};

#endif // GAMEVIEW_H
