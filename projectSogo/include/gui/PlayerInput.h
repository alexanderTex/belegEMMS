#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H

#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QSpinBox>
#include <QPushButton>
#include <QLabel>

#include "GameManagerThread.h"
#include "Vector2.h"

/**
 * @brief The PlayerInput class
 */
class PlayerInput : public QWidget
{
    Q_OBJECT
public:
    explicit PlayerInput(GameManager *gameManager, QWidget *parent = 0);

    virtual ~PlayerInput();

signals:
    /**
     * @brief InputConfirmed
     * @param pos
     */
    void InputConfirmed(Vector2 pos);

private:
    QVBoxLayout *m_inputLayout;

    QWidget *m_inputFields;
    QHBoxLayout *m_inputFieldLayout;

    QWidget *XspinBoxField;
    QHBoxLayout *xinputLayout;
    QLabel *xInputLabel;
    QSpinBox *m_xInput;

    QWidget *YspinBoxField;
    QHBoxLayout *yInputLayout;
    QLabel *yInputLabel;
    QSpinBox *m_yInput;

    QPushButton *m_inputConfirm;

    GameManager *m_gameManager;

    /**
     * @brief ApplyInputs
     */
    void ApplyInputs();
};

/**
 * @brief InputConfirmed
 */
void InputConfirmed();
#endif // PLAYERINPUT_H
