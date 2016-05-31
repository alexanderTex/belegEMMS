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
                            this->m_sceneItems->at(i)->at(j)->at(k)->SetColor(Qt::cyan);
                        }
                        else if(m_data->GetField()->GetSlot(k,j,i)->Occupation == PlayingField::Red)
                        {
                            this->m_sceneItems->at(i)->at(j)->at(k)->SetColor(Qt::red);
                        }
                        else
                        {
                            this->m_sceneItems->at(i)->at(j)->at(k)->SetColor(Qt::white);
                        }
                        this->m_sceneItems->at(i)->at(j)->at(k)->update();
                    }
                }
                //this->m_scenes->at(i)->update();
            }
        }

    protected:
private:
        float m_squareDrawSize;

        GameData *m_data;

        vector<QGraphicsView*> *m_scenes;
        vector< vector< vector< GraphicsSlot2D * > *> *> *m_sceneItems;
    };

    QGraphicsScene *CreateGrid(int rectCount, float rectSize, vector< vector <GraphicsSlot2D * > *> * sceneView);

#endif // GAMEVIEW2D_H
