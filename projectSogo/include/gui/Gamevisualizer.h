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
        this->view2D->ViewUpdate();
    }

private:
    GameView2D *view2D;

};

#endif // GAMEVISUALIZER_H
