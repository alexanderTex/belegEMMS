#include "GameVisualizer.h"

GameVisualizer::GameVisualizer(GameData *data, QWidget *parent)
    : QTabWidget(parent)
{
    this->m_view2D = new GameView2D(data, this);

    this->addTab(m_view2D, tr("2D"));

    this->m_view3D = new QWidget(this);
    this->addTab(m_view3D, tr("3D"));
}

GameVisualizer::~GameVisualizer()
{
    delete(m_view2D);
    delete(m_view3D);
}

