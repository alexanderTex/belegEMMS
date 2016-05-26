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

    this->m_xInput = new QSpinBox(XspinBoxField);
    xinputLayout->addWidget(this->m_xInput);
    this->m_xInput->setRange(1, m_data->GetField()->GetFieldSize());

    //Y Input
    QWidget *YspinBoxField = new QWidget(this);
    QHBoxLayout *yInputLayout = new QHBoxLayout(YspinBoxField);
    YspinBoxField->setLayout(yInputLayout);

    QLabel *yInputLabel = new QLabel("Y-Input : ");
    yInputLayout->addWidget(yInputLabel);

    this->m_yInput = new QSpinBox(YspinBoxField);
    yInputLayout->addWidget(this->m_yInput);
    this->m_yInput->setRange(1, m_data->GetField()->GetFieldSize());

    // Input Confirm Button
    this->m_inputConfirm = new QPushButton("Confirm", this);
    QObject::connect(this->m_inputConfirm, &QPushButton::clicked, this, &GameInputArea::ApplyInputs);

    inputLayout->addWidget(XspinBoxField, 0, 0);
    inputLayout->addWidget(YspinBoxField, 0, 1);
    inputLayout->addWidget(this->m_inputConfirm, 1, 0, 1, 2);
}

void GameInputArea::ApplyInputs()
{
    if(this->m_data->GetCurrentPlayer()->GetType() == Player::Human)
    {
        Vector3 input(this->m_xInput->value() - 1, this->m_yInput->value() - 1, GetAvailablePosition(this->m_xInput->value()-1, this->m_yInput->value() - 1, this->m_data->GetField()));
        this->m_data->MakeMove(input);
    }
}
