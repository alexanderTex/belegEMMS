#ifndef HISTORYDISPLAY_H
#define HISTORYDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QEvent>
#include "../IObserver.h"
#include "GameData.h"


/**
 * @brief The HistoryDisplay class
 */
class HistoryDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryDisplay(const GameData *data, QWidget *parent = 0);

    virtual ~HistoryDisplay();

    /**
     * @brief UpdateHistory
     * clears display
     * reevaluates past moves
     * and displays new text
     */
    void UpdateHistory();

    /**
     * @brief RedrawHistory
     * clears and redraws history
     */
    void RedrawHistory();

    /**
     * @brief DisplayText
     * Called to change the text in the Display box
     * @param entry
     */
    void SetDisplayText(std::string entry);

    inline void changeEvent(QEvent *event)
    {
        if (event->type() == QEvent::LanguageChange) {
            m_label->setText(tr("History :"));
        } else
            QWidget::changeEvent(event);
    }

private:
    QVBoxLayout *m_layout;
    QLabel *m_label;
    QTextEdit *m_display;

    const GameData *m_data;
};

#endif // HISTORYDISPLAY_H
