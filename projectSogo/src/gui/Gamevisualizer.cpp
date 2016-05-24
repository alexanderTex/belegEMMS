#include "Gamevisualizer.h"

GameVisualizer::GameVisualizer(GameData *data, QWidget *parent) : QWidget(parent)
{
   this->view2D = new GameView2D(data, this);
   QStackedLayout *layout = new QStackedLayout(this);
   layout->addWidget(this->view2D);
}

GameVisualizer::~GameVisualizer()
{
    delete(this->view2D);
}


