#include "PlayerInput.h"

PlayerInput::PlayerInput(GameData *data, QWidget *parent)
    : QWidget(parent)
{
    this->m_data = data;



    m_inputControls = new QWidget(this);

    this->m_inputLayout = new QGridLayout(m_inputControls);

    //X Input
    XspinBoxField = new QWidget(this);
    xinputLayout = new QHBoxLayout(XspinBoxField);
    XspinBoxField->setLayout(xinputLayout);

    xInputLabel = new QLabel("X-Input : ");
    xinputLayout->addWidget(xInputLabel);

    this->m_xInput = new QSpinBox(XspinBoxField);
    xinputLayout->addWidget(this->m_xInput);
    this->m_xInput->setRange(1, m_data->GetField()->GetFieldSize());


    //Y Input
    YspinBoxField = new QWidget(this);
    yInputLayout = new QHBoxLayout(YspinBoxField);
    YspinBoxField->setLayout(yInputLayout);

    yInputLabel = new QLabel("Y-Input : ");
    yInputLayout->addWidget(yInputLabel);

    this->m_yInput = new QSpinBox(YspinBoxField);
    yInputLayout->addWidget(this->m_yInput);
    this->m_yInput->setRange(1, m_data->GetField()->GetFieldSize());

    // Input Confirm Button
    this->m_inputConfirm = new QPushButton("Confirm", this);
    QObject::connect(this->m_inputConfirm, &QPushButton::clicked, this, &PlayerInput::ApplyInputs);

    m_inputLayout->addWidget(XspinBoxField, 0, 0);
    m_inputLayout->addWidget(YspinBoxField, 0, 1);
    m_inputLayout->addWidget(this->m_inputConfirm, 1, 0, 1, 2);
}

void PlayerInput::ApplyInputs()
{
    if(this->m_data->GetCurrentPlayer()->GetType() == Player::Human)
    {
        try
        {
            Vector3 input(this->m_xInput->value() - 1, this->m_yInput->value() - 1, GetAvailablePosition(this->m_xInput->value()-1, this->m_yInput->value() - 1, this->m_data->GetField()));

            this->m_data->MakeMove(input);
        }
        catch(PlayingField::FieldExeptions)
        {
            Logger::GetLoggerIntance()->LogError("Input not Valid");
        }
        catch(std::out_of_range)
        {
            Logger::GetLoggerIntance()->LogError("Input Out of Range");
        }
    }
}
