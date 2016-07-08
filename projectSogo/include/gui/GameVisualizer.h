#ifndef GAMEVISUALIZER_H
#define GAMEVISUALIZER_H

#include <QWidget>

#include <QTabWidget>

#include "../include/core/GameData.h"
#include "../include/gui/GameView2D.h"
#include "../include/gui/GameView3D.h"

using namespace std;

/**
 * @brief The GameVisualizer class
 */
class GameVisualizer : public QTabWidget
{
    Q_OBJECT
public:
     explicit GameVisualizer(GameManager *manager, QWidget *parent = 0);
     virtual ~GameVisualizer();

    /**
     * @brief UpdateView
     */
    inline void UpdateView()
    {
        this->m_view2D->ViewUpdate();
    }


    inline void GameChanged()
    {
        this->m_view2D->RecalculateGrid();
    }


private:
    GameView2D *m_view2D;
    GameView3D *m_view3D;

};

#endif // GAMEVISUALIZER_H
