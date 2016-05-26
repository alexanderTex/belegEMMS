#ifndef GAMEINPUTAREA_H
#define GAMEINPUTAREA_H

#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

#include "../include/core/GameData.h"
#include "../include/core/Vector2.h"


class GameInputArea : public QWidget
{
    Q_OBJECT
public:
    explicit GameInputArea(GameData *data, QWidget *parent = 0);

private:
    QSpinBox *m_xInput;
    QSpinBox *m_yInput;
    QPushButton *m_inputConfirm;

    GameData *m_data;

    void ApplyInputs();
};

void InputConfirmed();

#endif // GAMEINPUTAREA_H
