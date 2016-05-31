#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H

#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

#include "GameData.h"
#include "Vector2.h"

class PlayerInput : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerInput(GameData *data, QWidget *parent = 0);

private:
    //----- Input Controls
    QWidget *m_inputControls;
    QGridLayout *m_inputLayout;

    QWidget *XspinBoxField;
    QHBoxLayout *xinputLayout;
    QLabel *xInputLabel;
    QSpinBox *m_xInput;

    QWidget *YspinBoxField;
    QHBoxLayout *yInputLayout;
    QLabel *yInputLabel;
    QSpinBox *m_yInput;

    QPushButton *m_inputConfirm;
    //--------


    GameData *m_data;

    void ApplyInputs();
};

void InputConfirmed();
#endif // PLAYERINPUT_H
