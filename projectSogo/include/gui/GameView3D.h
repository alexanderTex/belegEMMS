#ifndef GAMEVIEW3D_H
#define GAMEVIEW3D_H

#include <QWidget>
#include <QOpenGLWidget>

class GameView3D : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit GameView3D(QWidget *parent = 0);

protected:
    inline virtual void initializeGL()
    {
        //this is where all the code before the graphics loop goes
    }

    inline virtual void paintGL()
    {

    }

    inline virtual void resizeGL(int w, int h)
    {

    }

signals:

public slots:
};

#endif // GAMEVIEW3D_H
