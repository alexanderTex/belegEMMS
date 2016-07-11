#include "GameView3D.h"

GameView3D::GameView3D(QWidget *parent) : QOpenGLWidget(parent)
{
    //setFixedSize(1024, 600);
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(true);
}
