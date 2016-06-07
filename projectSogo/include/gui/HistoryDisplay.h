#ifndef HISTORYDISPLAY_H
#define HISTORYDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>
#include "../IObserver.h"
#include "GameData.h"

class HistoryDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryDisplay(const GameData *data, QWidget *parent = 0);

    virtual ~HistoryDisplay();

    void UpdateHistory();

    void DisplayText(std::string entry);

private:
    QVBoxLayout *m_layout;
    QLabel *m_label;
    QTextEdit *m_display;

    const GameData *m_data;
};

#endif // HISTORYDISPLAY_H
