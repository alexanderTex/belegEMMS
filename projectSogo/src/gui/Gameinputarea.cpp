#include "Gameinputarea.h"

GameInputArea::GameInputArea(GameData *data, QWidget *parent) : QWidget(parent)
{
    this->m_data = data;

    QGridLayout *inputLayout = new QGridLayout(this);

    //X Input
    QWidget *XspinBoxField = new QWidget(this);
    QHBoxLayout *xinputLayout = new QHBoxLayout(XspinBoxField);
    XspinBoxField->setLayout(xinputLayout);

    QLabel *xInputLabel = new QLabel("X-Input : ");
    xinputLayout->addWidget(xInputLabel);

    this->m_XInput = new QSpinBox(XspinBoxField);
    xinputLayout->addWidget(this->m_XInput);
    this->m_XInput->setRange(0, m_data->GetField()->GetFieldSize() - 1);

    //Y Input
    QWidget *YspinBoxField = new QWidget(this);
    QHBoxLayout *yInputLayout = new QHBoxLayout(YspinBoxField);
    YspinBoxField->setLayout(yInputLayout);

    QLabel *yInputLabel = new QLabel("Y-Input : ");
    yInputLayout->addWidget(yInputLabel);

    this->m_YInput = new QSpinBox(YspinBoxField);
    yInputLayout->addWidget(this->m_YInput);
    this->m_YInput->setRange(0, m_data->GetField()->GetFieldSize() - 1);

    // Input Confirm Button
    this->m_InputConfirm = new QPushButton("Confirm", this);
    QObject::connect(this->m_InputConfirm, &QPushButton::clicked, this, &GameInputArea::ApplyInputs);

    inputLayout->addWidget(XspinBoxField, 0, 0);
    inputLayout->addWidget(YspinBoxField, 0, 1);
    inputLayout->addWidget(this->m_InputConfirm, 1, 0, 1, 2);
}

void GameInputArea::ApplyInputs()
{
    Vector2 input(this->m_XInput->value(), this->m_YInput->value());
    this->m_data->MakeMove(&input);
}
