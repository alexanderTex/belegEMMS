#ifndef GAMEVISUALIZER_H
#define GAMEVISUALIZER_H

#include <QWidget>

#include <QTabWidget>

#include "../include/core/GameData.h"
#include "../include/gui/GameView2D.h"

using namespace std;

/**
 * @brief The GameVisualizer class
 */
class GameVisualizer : public QTabWidget
{
    Q_OBJECT
public:
     explicit GameVisualizer(GameData *data, QWidget *parent = 0);
     virtual ~GameVisualizer();

    /**
     * @brief UpdateView
     */
    inline void UpdateView()
    {
        this->m_view2D->ViewUpdate();
    }





private:
    GameView2D *m_view2D;
    QWidget *m_view3D;

};

#endif // GAMEVISUALIZER_H
