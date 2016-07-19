#include "GameView3D.h"

GameView3D::GameView3D(QWidget *parent) : QOpenGLWidget(parent)
{
    //setFixedSize(1024, 600);
    setFocusPolicy(Qt::ClickFocus);
    setMouseTracking(true);
    setUpdateBehavior(NoPartialUpdate);
    m_hoveredSlotPosition.X = -1;
    m_hoveredSlotPosition.Y = -1;
    m_castHit = false;
    m_mouseMoved = false;

}


GameView3D::GameView3D(GameManager *gm, QWidget *parent)
    : GameView3D(parent)
{
    this->m_gm = gm;
}
