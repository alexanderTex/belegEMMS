#ifndef GRAPHICSSLOT2D_H
#define GRAPHICSSLOT2D_H

#include <QGraphicsObject>
#include <QColor>
#include <QPainter>

class GraphicsSlot2D : public QGraphicsObject
{
    Q_OBJECT
public:
    GraphicsSlot2D(float x, float y, float width, float height, QColor color = Qt::white, QGraphicsItem *parent = 0);
    virtual ~GraphicsSlot2D()
    {

    }


    virtual QRectF boundingRect() const Q_DECL_OVERRIDE
    {
        return QRectF(m_x, m_y, m_width, m_height);
    }

    inline QColor GetColor() const
    {
        return m_Color;
    }

    inline void SetColor(QColor color)
    {
        m_Color = color;
    }

    inline virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR) Q_DECL_OVERRIDE
    {
        Q_UNUSED(option);
        Q_UNUSED(widget);
        painter->setPen(QPen(Qt::black, 1));
        painter->setBrush(QBrush(m_Color));
        painter->drawRect(m_x, m_y, m_width, m_height);
    }

    inline void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE
    {
        emit ClickedSignal(this);
        QGraphicsObject::mousePressEvent(event);
    }
signals:
    void ClickedSignal(GraphicsSlot2D *ref);

private:
    float m_x;
    float m_y;
    float m_width;
    float m_height;

    QColor m_Color;

};

#endif // GRAPHICSSLOT2D_H
