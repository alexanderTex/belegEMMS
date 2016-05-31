#include "Gamevisualizer.h"

GameVisualizer::GameVisualizer(GameData *data, QWidget *parent)
    : QWidget(parent)
{
   this->m_view2D = new GameView2D(data, this);
   m_layout = new QStackedLayout(this);
   m_layout->addWidget(this->m_view2D);
}

GameVisualizer::~GameVisualizer()
{
    delete(this->m_view2D);
}


