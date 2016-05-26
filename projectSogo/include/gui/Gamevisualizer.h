#ifndef GAMEVISUALIZER_H
#define GAMEVISUALIZER_H

#include <QWidget>

#include <QStackedLayout>

#include "../include/core/GameData.h"
#include "../include/gui/GameView2D.h"

using namespace std;

class GameVisualizer : public QWidget, public IObserver
{
    Q_OBJECT
public:
     explicit GameVisualizer(GameData *data, QWidget *parent = 0);
    ~GameVisualizer();



    inline void Notify()
    {
        this->m_view2D->ViewUpdate();
    }

private:
    GameView2D *m_view2D;
    QStackedLayout *m_layout;

};

#endif // GAMEVISUALIZER_H
