#include "HistoryDisplay.h"

HistoryDisplay::HistoryDisplay(QWidget *parent)
{
    this->m_layout = new QVBoxLayout(this);
    this->m_label = new QLabel("History :");
    this->m_display = new QTextEdit(this);

    m_layout->addWidget(m_label);
    m_layout->addWidget(m_display);
}
