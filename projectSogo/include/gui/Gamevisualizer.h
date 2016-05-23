#ifndef GAMEVISUALIZER_H
#define GAMEVISUALIZER_H

#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPainter>

#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

#include "../include/core/Gamedata.h"
#include "../include/core/Vector3.h"
#include "../include/core/Playingfield.h"
#include "../include/Observer.h"

using namespace std;

class GameVisualizer : public QWidget, public Observer
{
    Q_OBJECT
public:
     explicit GameVisualizer(GameData *data, QWidget *parent = 0);
    ~GameVisualizer();

    inline QGraphicsRectItem *GetRect(Vector3 vec)
    {
        return m_SceneItems->at(vec.X)->at(vec.Y)->at(vec.Z);
    }

    inline void Notify()
    {
        Update();
    }

    inline void Update()
    {
       for(int i = 0; i < m_data->GetField()->GetFieldSize(); i++)
        {
            for(int j = 0; j < m_data->GetField()->GetFieldSize(); j++)
            {
                for(int k = 0; k < m_data->GetField()->GetFieldSize(); k++)
                {
                    if(m_data->GetField()->GetSlot(i,j,k)->Occupation == PlayingField::Blue)
                    {
                        this->m_SceneItems->at(i)->at(j)->at(k)->setBrush(QBrush(Qt::cyan));
                    }
                    else if(m_data->GetField()->GetSlot(i,j,k)->Occupation == PlayingField::Red)
                    {
                        this->m_SceneItems->at(i)->at(j)->at(k)->setBrush(QBrush(Qt::red));
                    }
                    else
                    {
                        this->m_SceneItems->at(i)->at(j)->at(k)->setBrush(QBrush(Qt::white));
                    }
                    this->m_SceneItems->at(i)->at(j)->at(k)->update();
                }
            }
        }
    }

private:
    float m_SquareDrawSize;

    GameData *m_data;

    vector<QGraphicsView*> *m_Scenes;
    vector< vector< vector< QGraphicsRectItem * > *> *> *m_SceneItems;
};

QGraphicsScene *CreateGrid(int rectCount, float rectSize, vector< vector <QGraphicsRectItem * > *> *sceneView);

#endif // GAMEVISUALIZER_H
