#include "PlayerInput.h"

PlayerInput::PlayerInput(GameManager *gameManager, QWidget *parent)
    : QWidget(parent)
{
    this->m_gameManager = gameManager;


    this->m_inputLayout = new QVBoxLayout((this));

    this->m_infoText = new QLabel(tr("Info : You select a slot on the base layer where you want to drop a setpiece,\n\t which will then be placed at the lowest possible place in that slot."));
    this->m_inputLayout->addWidget(this->m_infoText);

    this->m_inputFields = new QWidget(this);
    this->m_inputFieldLayout = new QHBoxLayout(this->m_inputFields);
    this->m_inputFieldLayout->setContentsMargins(-1, 0, -1, 0);

    //X Input
    this->XspinBoxField = new QWidget(m_inputFields);
    this->m_inputFieldLayout->addWidget(this->XspinBoxField);


    this->xinputLayout = new QHBoxLayout(this->XspinBoxField);
    this->xinputLayout->setContentsMargins(1, 0, 1, 0);

    this->xInputLabel = new QLabel(tr("X-Input : "));
    this->xinputLayout->addWidget(this->xInputLabel);

    this->m_xInput = new QSpinBox(this->XspinBoxField);
    this->xinputLayout->addWidget(this->m_xInput);
    this->m_xInput->setRange(1, this->m_gameManager->GetGameData()->GetField()->GetFieldSize());


    //Y Input
    this->YspinBoxField = new QWidget(m_inputFields);
    this->m_inputFieldLayout->addWidget(this->YspinBoxField);


    this->yInputLayout = new QHBoxLayout(this->YspinBoxField);

    this->yInputLabel = new QLabel(tr("Y-Input : "));
    this->yInputLayout->addWidget(this->yInputLabel);

    this->m_yInput = new QSpinBox(this->YspinBoxField);
    this->yInputLayout->addWidget(this->m_yInput);
    this->m_yInput->setRange(1, this->m_gameManager->GetGameData()->GetField()->GetFieldSize());



    // Input Confirm Button
    this->m_inputConfirm = new QPushButton(tr("Confirm"), this);
    QObject::connect(this->m_inputConfirm, &QPushButton::clicked, this, &PlayerInput::ApplyInputs);

    this->m_inputLayout->addWidget(this->m_inputFields);
    this->m_inputLayout->addWidget(this->m_inputConfirm);

}

PlayerInput::~PlayerInput()
{
    delete(m_inputLayout);
    delete(m_inputFieldLayout);

}

void PlayerInput::ApplyInputs()
{
    if(this->m_gameManager->GetGameData()->GetCurrentPlayer()->GetType() == Player::HUMAN)
    {
        Vector2 input(this->m_xInput->value() - 1, this->m_yInput->value() - 1);
        emit InputConfirmed(input);

    }
}
