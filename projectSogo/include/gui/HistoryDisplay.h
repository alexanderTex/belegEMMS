#ifndef HISTORYDISPLAY_H
#define HISTORYDISPLAY_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QTextEdit>

class HistoryDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit HistoryDisplay(QWidget *parent = 0);

    inline void WriteToDisplay(std::string entry)
    {
        m_display->append(QString(entry.c_str()));
    }

private:
    QVBoxLayout *m_layout;
    QLabel *m_label;
    QTextEdit *m_display;
};

#endif // HISTORYDISPLAY_H
