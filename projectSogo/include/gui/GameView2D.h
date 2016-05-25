#ifndef GAMEVIEW2D_H
#define GAMEVIEW2D_H

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

#include "../include/core/GameData.h"
#include "../include/core/Vector3.h"
#include "../include/core/PlayingField.h"
#include "../include/IObserver.h"

class GameView2D : public QWidget
{
    public:
        explicit GameView2D(GameData *data, const QWidget *parent = 0);
        virtual ~GameView2D();

        inline QGraphicsRectItem *GetRect(Vector3 vec)
        {
            return m_SceneItems->at(vec.X)->at(vec.Y)->at(vec.Z);
        }

        inline void ViewUpdate()
        {
           for(int i = 0; i < m_data->GetField()->GetFieldSize(); i++)
            {
                for(int j = 0; j < m_data->GetField()->GetFieldSize(); j++)
                {
                    for(int k = 0; k < m_data->GetField()->GetFieldSize(); k++)
                    {
                        if(m_data->GetField()->GetSlot(k,j,i)->Occupation == PlayingField::Blue)
                        {
                            this->m_SceneItems->at(i)->at(j)->at(k)->setBrush(QBrush(Qt::cyan));
                        }
                        else if(m_data->GetField()->GetSlot(k,j,i)->Occupation == PlayingField::Red)
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
                this->m_Scenes->at(i)->update();
            }
        }

    protected:
private:
        float m_SquareDrawSize;

        GameData *m_data;

        vector<QGraphicsView*> *m_Scenes;
        vector< vector< vector< QGraphicsRectItem * > *> *> *m_SceneItems;
    };

    QGraphicsScene *CreateGrid(int rectCount, float rectSize, vector< vector <QGraphicsRectItem * > *> *sceneView);

#endif // GAMEVIEW2D_H
