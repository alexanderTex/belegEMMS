#ifndef GAMEVISUALIZER_H
#define GAMEVISUALIZER_H

#include <QWidget>

#include <QStackedLayout>
#include <QComboBox>

#include "../include/core/GameData.h"
#include "../include/gui/GameView2D.h"

using namespace std;

class GameVisualizer : public QWidget
{
    Q_OBJECT
public:
     explicit GameVisualizer(GameData *data, QWidget *parent = 0);
     virtual ~GameVisualizer();

    inline void UpdateView()
    {
        this->m_view2D->ViewUpdate();
    }

    void SetTo2DView();

    void SetTo3DView();






private:

    QVBoxLayout *m_overallLayout;
    QWidget *m_viewSelectionArea;
    QWidget *m_viewArea;

    QHBoxLayout *m_selectionLayout;
    QPushButton *m_viewSelect2D;
    QPushButton *m_viewSelect3D;

    QStackedLayout *m_viewLayout;
    GameView2D *m_view2D;
    QWidget *m_view3D;

};

#endif // GAMEVISUALIZER_H
