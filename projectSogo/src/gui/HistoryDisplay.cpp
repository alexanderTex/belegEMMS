#include "HistoryDisplay.h"

HistoryDisplay::HistoryDisplay(const GameData *data, QWidget *parent)
    : QWidget(parent)
{
    this->m_layout = new QVBoxLayout(this);
    this->m_label = new QLabel(tr("History :"));
    this->m_display = new QTextEdit(this);
    this->m_display->setReadOnly(true);

    m_layout->addWidget(m_label);
    m_layout->addWidget(m_display);

    this->m_data = data;    
}

HistoryDisplay::~HistoryDisplay()
{
    delete(m_layout);
    delete(m_label);
    delete(m_display);
}


void HistoryDisplay::UpdateHistory()
{
    this->m_display->clear();

    stringstream s;

    for(int i = 0; i < this->m_data->GetHistory()->GetMoveCount(); i++)
    {
        stringstream posStream;
        posStream << *(this->m_data->GetHistory()->GetLastMove()->position) << endl;

        s << this->m_data->GetHistory()->GetMove(i)->player->GetName() << " : " << *(this->m_data->GetHistory()->GetMove(i)->position) << endl;
    }

    this->DisplayText(s.str());
}

void HistoryDisplay::DisplayText(std::string entry)
{
    this->m_display->setText(QString(entry.c_str()));
}
