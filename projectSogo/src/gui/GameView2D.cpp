#include "GameView2D.h"

GameView2D::GameView2D(GameData *data, const QWidget *parent)
{
    //ctor
    this->m_data = data;

    this->m_SquareDrawSize = 20;

    this->m_Scenes = new vector<QGraphicsView *>();

    this->m_SceneItems = new vector<vector< vector <QGraphicsRectItem * > *> *>();

    QHBoxLayout *sceneViewLayout = new QHBoxLayout(this);
    for(int i = 0; i < m_data->GetField()->GetFieldSize(); i++)
    {

        QWidget *sceneArea = new QWidget(this);
        sceneArea->setMinimumSize(sceneViewLayout->spacing() + m_data->GetField()->GetFieldSize() * this->m_SquareDrawSize, sceneViewLayout->spacing() + m_data->GetField()->GetFieldSize() * this->m_SquareDrawSize);
        sceneViewLayout->addWidget(sceneArea);

        this->m_SceneItems->push_back(new vector< vector <QGraphicsRectItem * > *>());

        QGraphicsScene *graphicsScene = CreateGrid(m_data->GetField()->GetFieldSize(), this->m_SquareDrawSize, this->m_SceneItems->at(i));
        this->m_Scenes->push_back(new QGraphicsView(graphicsScene, sceneArea));
        this->m_Scenes->at(i)->ensureVisible(graphicsScene->sceneRect());
        this->m_Scenes->at(i)->show();
    }
}

GameView2D::~GameView2D()
{
    //dtor
    for(int i = 0; i < this->m_SceneItems->size(); i++)
    {
        // iterates through the depth lines
        for(int j = 0; j < this->m_SceneItems->at(i)->size() ;j++)
        {
            // iterates through the horizontal lines
            for(int k = 0; k < this->m_SceneItems->at(i)->at(j)->size(); k++)
            {
                delete(this->m_SceneItems->at(i)->at(j)->at(k));
            }
            delete(this->m_SceneItems->at(i)->at(j));
        }
        delete(this->m_SceneItems->at(i));
    }
    delete(this->m_SceneItems);
    for(int i = 0; i < this->m_Scenes->size(); i++)
    {
        delete(m_Scenes->at(i));
    }

    delete(m_Scenes);
}

QGraphicsScene *CreateGrid(int rectCount, float rectSize, vector< vector <QGraphicsRectItem * > *> *sceneView)
{
    QGraphicsScene *scene = new QGraphicsScene();

    float yDrawCoord = 0;

    // iterates through the depth lines
    for(int i = 0; i < rectCount ;i++)
    {
        sceneView->push_back(new vector <QGraphicsRectItem * >());
        float xDrawCoord = 0;
        // iterates through the horizontal lines
        for(int k = 0; k < rectCount; k++)
        {
            sceneView->at(i)->push_back(scene->addRect(xDrawCoord, yDrawCoord, rectSize, rectSize));
            xDrawCoord += rectSize;
        }

        yDrawCoord += rectSize;
    }
    return scene;
}
