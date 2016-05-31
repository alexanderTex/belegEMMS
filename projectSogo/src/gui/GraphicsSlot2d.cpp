#include "GraphicsSlot2d.h"

GraphicsSlot2D::GraphicsSlot2D(float x, float y, float width, float height, QColor color, QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    this->m_x = x;
    this->m_y = y;
    this->m_width = width;
    this->m_height = height;
    this->m_Color = color;
}
