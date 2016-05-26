#ifndef GRAPHICSSLOT2D_H
#define GRAPHICSSLOT2D_H

#include <QGraphicsObject>

class GraphicsSlot2D : public QGraphicsObject
{
public:
    GraphicsSlot2D(float x, float y, float z);

    virtual QRectF boundingRect() const
    {
        return QRectF();
    }

    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

signals:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void Cicked(GraphicsSlot2D ref);

private:
    float m_x;
    float m_y;
    float m_z;
};

#endif // GRAPHICSSLOT2D_H
