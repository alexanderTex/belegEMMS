#ifndef GRAPHICSTHREAD_H
#define GRAPHICSTHREAD_H

#include <QThread>

class GraphicsThread : public QThread
{
    Q_OBJECT
    public:
        GraphicsThread();

        void run();
};

#endif // GRAPHICSTHREAD_H
