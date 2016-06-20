#include "GameView2D.h"

GameView2D::GameView2D(GameData *data, QWidget *parent)
    : QWidget(parent)
{
    //ctor
    this->m_data = data;

    this->m_squareDrawSize = 20;

    this->m_scenes = new vector<QGraphicsView *>();

    this->m_sceneItems = new vector<vector< vector <GraphicsSlot2D * > *> *>();

    sceneViewLayout = new QHBoxLayout(this);
    for(int i = 0; i < m_data->GetField()->GetFieldSize(); i++)
    {
        QWidget *sceneArea = new QWidget(this);
        sceneArea->setMinimumSize(sceneViewLayout->spacing() + m_data->GetField()->GetFieldSize() * this->m_squareDrawSize, sceneViewLayout->spacing() + m_data->GetField()->GetFieldSize() * this->m_squareDrawSize);
        sceneViewLayout->addWidget(sceneArea);

        this->m_sceneItems->push_back(new vector< vector <GraphicsSlot2D * > *>());

        QGraphicsScene *graphicsScene = CreateGrid(data->GetField()->GetFieldSize(), this->m_squareDrawSize, this->m_sceneItems->at(i));

        QGraphicsView *view = new QGraphicsView(graphicsScene, sceneArea);
        view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        this->m_scenes->push_back(view);
        this->m_scenes->at(i)->ensureVisible(graphicsScene->sceneRect());
        this->m_scenes->at(i)->show();
    }
}

GameView2D::~GameView2D()
{
    //dtor
    for(int i = 0; i < this->m_sceneItems->size(); i++)
    {
        // iterates through the depth lines
        for(int j = 0; j < this->m_sceneItems->at(i)->size() ;j++)
        {
            // iterates through the horizontal lines
            for(int k = 0; k < this->m_sceneItems->at(i)->at(j)->size(); k++)
            {
                delete(this->m_sceneItems->at(i)->at(j)->at(k));
            }
            delete(this->m_sceneItems->at(i)->at(j));
        }
        delete(this->m_sceneItems->at(i));
    }
    delete(this->m_sceneItems);
    for(int i = 0; i < this->m_scenes->size(); i++)
    {
        delete(m_scenes->at(i));
    }

    delete(m_scenes);
}

void GameView2D::ViewUpdate()
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

QGraphicsScene *CreateGrid(int rectCount, float rectSize, vector< vector <GraphicsSlot2D * > *> * sceneView)
{
    QGraphicsScene *scene = new QGraphicsScene();

    float yDrawCoord = 0;

    // iterates through the depth lines
    for(int i = 0; i < rectCount;i++)
    {
        sceneView->push_back(new vector <GraphicsSlot2D * >());
        float xDrawCoord = 0;
        // iterates through the horizontal lines
        for(int k = 0; k < rectCount; k++)
        {
            GraphicsSlot2D *rect = new GraphicsSlot2D(xDrawCoord, yDrawCoord, rectSize, rectSize);
            scene->addItem(rect);
            //rect->setFlag(QGraphicsObject::ItemIsSelectable);
            //rect->setAcceptHoverEvents(true);
            sceneView->at(i)->push_back(rect);
            xDrawCoord += rectSize;
        }

        yDrawCoord += rectSize;
    }
    return scene;
}
