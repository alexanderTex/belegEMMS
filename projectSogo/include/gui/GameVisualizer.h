#ifndef GAMEVISUALIZER_H
#define GAMEVISUALIZER_H

#include <QWidget>
#include <QTimer>

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

    inline void UpdateViews()
    {
        UpdateView2D();
        UpdateView3D();
    }

    inline void UpdateView2D()
    {
        this->m_view2D->ViewUpdate();
    }

    inline void UpdateView3D()
    {
        this->m_view3D->update();
        this->m_view3D->setFocus();
    }


    inline void GameChanged()
    {
        this->m_view2D->RecalculateGrid();
    }

signals:
    void InputDetected(Vector2 pos);


private:
    GameView2D *m_view2D;
    GameView3D *m_view3D;

};

#endif // GAMEVISUALIZER_H
