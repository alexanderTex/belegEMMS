#include "Gamevisualizer.h"

GameVisualizer::GameVisualizer(GameData *data, QWidget *parent)
    : QWidget(parent)
{

    this->m_overallLayout = new QVBoxLayout(this);

    m_viewSelectionArea = new QWidget(this);
    m_overallLayout->addWidget(m_viewSelectionArea);

    m_selectionLayout = new QHBoxLayout(m_viewSelectionArea);

    m_viewSelect2D = new QPushButton("2D",this);
    m_selectionLayout->addWidget(this->m_viewSelect2D, Qt::AlignLeft | Qt::AlignBottom);

    QObject::connect(this->m_viewSelect2D, &QPushButton::clicked, this, &GameVisualizer::SetTo2DView);

    m_viewSelect3D = new QPushButton("3D",this);
    m_selectionLayout->addWidget(this->m_viewSelect3D, Qt::AlignLeft | Qt::AlignBottom);

    QObject::connect(this->m_viewSelect3D, &QPushButton::clicked, this, &GameVisualizer::SetTo3DView);


    m_viewArea = new QWidget(this);
    m_overallLayout->addWidget(m_viewArea);

    m_viewLayout = new QStackedLayout(m_viewArea);
    this->m_view2D = new GameView2D(data, this);
    m_viewLayout->addWidget(this->m_view2D);

    this->m_view3D = new QWidget(this);
    m_viewLayout->addWidget(this->m_view3D);
}

GameVisualizer::~GameVisualizer()
{
    delete(this->m_viewSelectionArea);
    delete(this->m_viewArea);
}

void GameVisualizer::SetTo2DView()
{
    this->m_viewLayout->setCurrentWidget(this->m_view2D);
}

void GameVisualizer::SetTo3DView()
{
    this->m_viewLayout->setCurrentWidget(this->m_view3D);
}
