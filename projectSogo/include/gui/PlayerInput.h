#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H

#include <QWidget>

#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>

#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QEvent>
#include <QGraphicsScene>
#include <QGraphicsView>

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

    inline void changeEvent(QEvent *event)
    {
        if (event->type() == QEvent::LanguageChange) {
            xInputLabel->setText(tr("X-Input : "));
            yInputLabel->setText(tr("Y-Input : "));
            m_inputConfirm->setText(tr("Confirm"));

        } else
            QWidget::changeEvent(event);
    }

    virtual ~PlayerInput();

    void ApplyPlayerChange();


signals:
    /**
     * @brief InputConfirmed
     * @param pos
     */
    void InputConfirmed(Vector2 pos);

private:
    QVBoxLayout *m_inputLayout;

    QWidget *m_currentPlayerDisplay;
    QHBoxLayout *m_currentPlayerLayout;

    QLabel *m_currentPlayerLabel;
    QLabel *m_currentPlayerName;
    QGraphicsView *m_currentPlayerColorView;
    QGraphicsScene *m_currentPlayerColorScene;


    QLabel *m_infoText;

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
