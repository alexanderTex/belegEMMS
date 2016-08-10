#include "GameView2D.h"

GameView2D::GameView2D(GameManager *manager, QWidget *parent)
    : QWidget(parent)
{
    //ctor
    this->m_manager = manager;

    this->m_squareDrawSize = 20;

    this->m_scenes = new vector<QGraphicsView *>();

    this->m_sceneItems = new vector<vector< vector <GraphicsSlot2D * > *> *>();

    this->sceneViewLayout = new QHBoxLayout(this);
    this->m_sceneLabels = new vector<QLabel *>();
    for(int i = 0; i < m_manager->GetGameData()->GetField()->GetFieldSize(); i++)
    {
        this->m_sceneItems->push_back(new vector< vector <GraphicsSlot2D * > *>());

        QGraphicsScene *graphicsScene = CreateGrid(m_manager->GetGameData()->GetField()->GetFieldSize(), this->m_squareDrawSize, this->m_sceneItems->at(i));

        QGraphicsView *view = new QGraphicsView(graphicsScene, this);
        view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        this->m_scenes->push_back(view);
        this->m_scenes->at(i)->ensureVisible(graphicsScene->sceneRect());
        this->m_scenes->at(i)->show();

        QVBoxLayout *sceneLayout = new QVBoxLayout();
        stringstream s;
        s << "Layer " << i ;

        QLabel *label = new QLabel(tr(s.str().c_str()));
        m_sceneLabels->push_back(label);

        sceneLayout->addWidget(label);
        sceneLayout->addWidget(view);

        sceneViewLayout->addLayout(sceneLayout);


    }


    Logger::GetLoggerIntance()->LogInfo("GameView2D constr");
}

GameView2D::~GameView2D()
{
    //dtor
    ClearGrid();
}

void GameView2D::ClearGrid()
{

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
        delete(m_sceneLabels->at(i));
        delete(m_scenes->at(i));
    }

    delete(m_scenes);
}

void GameView2D::RecalculateGrid()
{
    this->ClearGrid();
    this->m_scenes = new vector<QGraphicsView *>();

    this->m_sceneItems = new vector<vector< vector <GraphicsSlot2D * > *> *>();

    this->m_sceneLabels = new vector<QLabel *>();

    for(int i = 0; i < m_manager->GetGameData()->GetField()->GetFieldSize(); i++)
    {
        this->m_sceneItems->push_back(new vector< vector <GraphicsSlot2D * > *>());


        QGraphicsScene *graphicsScene = CreateGrid(m_manager->GetGameData()->GetField()->GetFieldSize(), this->m_squareDrawSize, this->m_sceneItems->at(i));

        QGraphicsView *view = new QGraphicsView(graphicsScene, this);
        view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
        this->m_scenes->push_back(view);
        this->m_scenes->at(i)->ensureVisible(graphicsScene->sceneRect());
        this->m_scenes->at(i)->show();


        QVBoxLayout *sceneLayout = new QVBoxLayout();
        stringstream s;
        s << "Layer " << i ;

        m_label = new QLabel(tr(s.str().c_str()));
        m_sceneLabels->push_back(m_label);

        sceneLayout->addWidget(m_label);
        sceneLayout->addWidget(view);

        sceneViewLayout->addLayout(sceneLayout);


    }
}

void GameView2D::ViewUpdate()
{
   for(int i = 0; i < m_manager->GetGameData()->GetField()->GetFieldSize(); i++)
    {
        for(int j = 0; j < m_manager->GetGameData()->GetField()->GetFieldSize(); j++)
        {
            for(int k = 0; k < m_manager->GetGameData()->GetField()->GetFieldSize(); k++)
            {
                if(m_manager->GetGameData()->GetField()->GetSlot(k,j,i)->Occupation == PlayingField::BLUE)
                {
                    this->m_sceneItems->at(i)->at(j)->at(k)->SetColor(Qt::blue);
                }
                else if(m_manager->GetGameData()->GetField()->GetSlot(k,j,i)->Occupation == PlayingField::RED)
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
