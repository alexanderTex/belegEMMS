#include "PlayerInput.h"

PlayerInput::PlayerInput(GameManager *gameManager, QWidget *parent)
    : QWidget(parent)
{
    this->m_gameManager = gameManager;


    this->m_inputLayout = new QVBoxLayout((this));



    m_currentPlayerDisplay = new QWidget();
    m_inputLayout->addWidget(m_currentPlayerDisplay);

    m_currentPlayerLayout = new QHBoxLayout(m_currentPlayerDisplay);

    m_currentPlayerLabel = new QLabel("CurrentPlayer : ");

    m_currentPlayerName = new QLabel();

    m_currentPlayerColorScene = new QGraphicsScene();

    m_currentPlayerColorView = new QGraphicsView(m_currentPlayerColorScene, this);

    m_currentPlayerColorScene->setBackgroundBrush(Qt::white);

    this->m_infoText = new QLabel(tr("Info : You select a slot on the base layer where you want to drop a setpiece,\n\t which will then be placed at the lowest possible place in that slot."));
    this->m_inputLayout->addWidget(this->m_infoText);

    m_currentPlayerLayout->addWidget(m_currentPlayerName);
    m_currentPlayerLayout->addWidget(m_currentPlayerLabel);
    m_currentPlayerLayout->addWidget(m_currentPlayerColorView);



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

    QObject::connect(this->m_gameManager, &GameManager::TurnFinished, this, &PlayerInput::ApplyPlayerChange);
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

void PlayerInput::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        xInputLabel->setText(tr("X-Input : "));
        yInputLabel->setText(tr("Y-Input : "));
        m_inputConfirm->setText(tr("Confirm"));
        m_infoText->setText(tr("Info : You select a slot on the base layer where you want to drop a setpiece,\n\t which will then be placed at the lowest possible place in that slot."));

    } else
        QWidget::changeEvent(event);
}

void PlayerInput::ApplyPlayerChange()
{

    m_currentPlayerName->setText(QString(m_gameManager->GetGameData()->GetCurrentPlayer()->GetName().c_str()));

    if(m_gameManager->GetGameData()->GetCurrentPlayer()->GetColor() == PlayingField::BLUE)
    {
        m_currentPlayerColorScene->setBackgroundBrush(Qt::blue);
    }
    else if(m_gameManager->GetGameData()->GetCurrentPlayer()->GetColor() == PlayingField::RED)
    {
        m_currentPlayerColorScene->setBackgroundBrush(Qt::red);
    }
}
