#ifndef GAMEVIEW2D_H
#define GAMEVIEW2D_H

#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>

#include <QPainter>

#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

#include "../include/core/GameManagerThread.h"
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
        explicit GameView2D(GameManager *manager, QWidget *parent = 0);
        virtual ~GameView2D();

        inline GraphicsSlot2D *GetRect(Vector3 vec)
        {
            return m_sceneItems->at(vec.X)->at(vec.Y)->at(vec.Z);
        }

        void ClearGrid();

        void RecalculateGrid();

        /**
         * @brief ViewUpdate
         */
        void ViewUpdate();

 protected:
        /*
        inline virtual void resizeEvent(QResizeEvent *event)
        {
            float diff ;
            if(event->size().height() <  event->size().width())
            {
                diff = event->oldSize().height() % event->size().height();
            }
            else
            {
                diff = event->oldSize().width() % event->size().width();
            }

            this->m_sceneItems->at(0)->at(0)->at(0)->SetSize(m_squareDrawSize -1, m_squareDrawSize -1);

            for(int i = 0; i < this->m_sceneItems->size(); i++)
            {
                // iterates through the depth lines
                for(int j = 0; j < this->m_sceneItems->at(i)->size(); j++)
                {
                    // iterates through the horizontal lines
                    for(int k = 0; k < this->m_sceneItems->at(i)->at(j)->size(); k++)
                    {
                        //this->m_sceneItems->at(i)->at(j)->at(k)->SetSize(m_squareDrawSize * diff, m_squareDrawSize * diff);
                    }
                }
                this->m_scenes->at(i)->update();
            }
            this->update();
            QWidget::resizeEvent(event);
        }
        */
private:
        float m_squareDrawSize;

        GameManager *m_manager;

        QHBoxLayout *sceneViewLayout;

        QLabel *m_label;

        vector<QLabel *> *m_sceneLabels;
        vector<QGraphicsView*> *m_scenes;
        vector< vector< vector< GraphicsSlot2D * > *> *> *m_sceneItems;
    };

    QGraphicsScene *CreateGrid(int rectCount, float rectSize, vector< vector <GraphicsSlot2D * > *> * sceneView);

#endif // GAMEVIEW2D_H
