#ifndef GAMEVIEW2D_H
#define GAMEVIEW2D_H

#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QGraphicsView>
#include <QGraphicsScene>

#include <QPainter>

#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

#include "../include/core/GameData.h"
#include "../include/core/Vector3.h"
#include "../include/core/PlayingField.h"
#include "../include/IObserver.h"
#include "../include/gui/GraphicsSlot2d.h"



// maybe as a Graphicsscene overload
/**
 * @brief The GameView2D class
 */
class GameView2D : public QWidget
{
    Q_OBJECT
    public:
        explicit GameView2D(GameData *data, QWidget *parent = 0);
        virtual ~GameView2D();

        inline GraphicsSlot2D *GetRect(Vector3 vec)
        {
            return m_sceneItems->at(vec.X)->at(vec.Y)->at(vec.Z);
        }

        /**
         * @brief ViewUpdate
         */
        void ViewUpdate();

    protected:
private:
        float m_squareDrawSize;

        GameData *m_data;

        vector<QGraphicsView*> *m_scenes;
        vector< vector< vector< GraphicsSlot2D * > *> *> *m_sceneItems;
    };

    QGraphicsScene *CreateGrid(int rectCount, float rectSize, vector< vector <GraphicsSlot2D * > *> * sceneView);

#endif // GAMEVIEW2D_H
