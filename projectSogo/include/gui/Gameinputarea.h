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
public:
    explicit GameInputArea(GameData *data, QWidget *parent = 0);

private:
    QSpinBox *m_XInput;
    QSpinBox *m_YInput;
    QPushButton *m_InputConfirm;

    GameData *m_data;

    void ApplyInputs();
};

void InputConfirmed();

#endif // GAMEINPUTAREA_H
