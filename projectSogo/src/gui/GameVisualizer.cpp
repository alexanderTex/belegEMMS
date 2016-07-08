#include "GameVisualizer.h"

GameVisualizer::GameVisualizer(GameManager *manager, QWidget *parent)
    : QTabWidget(parent)
{
    this->m_view2D = new GameView2D(manager, this);

    this->addTab(m_view2D, tr("2D"));

    this->m_view3D = new GameView3D(this);
    this->addTab(m_view3D, tr("3D"));
}

GameVisualizer::~GameVisualizer()
{
    delete(m_view2D);
    delete(m_view3D);
}

