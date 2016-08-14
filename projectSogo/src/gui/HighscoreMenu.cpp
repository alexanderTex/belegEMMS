#include "HighscoreMenu.h"

HighscoreMenu::HighscoreMenu(QWidget *parent) : QWidget(parent)
{
    this->m_controlLayout = new QVBoxLayout(this);

    this->m_mainMenueLabel = new QLabel(tr("Highscore"), this);
    this->m_mainMenueLabel->setAlignment(Qt::AlignHCenter);
    this->m_mainMenueLabel->setFont(QFont("Times",18,QFont::Bold));
    this->m_controlLayout->addWidget(m_mainMenueLabel);

    QWidget *main = new QWidget(this);

    this->m_controlLayout->addWidget(main);

    QHBoxLayout *layout = new QHBoxLayout(main);
/*
    QLabel *nummer = new QLabel(tr("GameNumber"), main);
    layout->addWidget(nummer);
    QLabel *name1 = new QLabel(tr("PlayerName1"), main);
    layout->addWidget(name1);
    QLabel *name2 = new QLabel(tr("PlayerName2"), main);
    layout->addWidget(name2);
    QLabel *winner = new QLabel(tr("Winner"), main);
    layout->addWidget(winner);
    QLabel *moveCount = new QLabel(tr("MoveCount"), main);
    layout->addWidget(moveCount);
*/

    this->nummer = new QLabel(tr("GameNumber"), main);
    layout->addWidget(nummer);
    this->name1 = new QLabel(tr("PlayerName1"), main);
    layout->addWidget(name1);
    this->name2 = new QLabel(tr("PlayerName2"), main);
    layout->addWidget(name2);
    this->winner = new QLabel(tr("Winner"), main);
    layout->addWidget(winner);
    this->moveCount = new QLabel(tr("MoveCount"), main);
    layout->addWidget(moveCount);

    this->m_scoresDisplayScroll = new QScrollArea(this);
    this->m_controlLayout->addWidget(m_scoresDisplayScroll);

    this->m_scoreDisplay = new QWidget(m_scoresDisplayScroll);

    this->m_scoresDisplayScroll->setWidget(m_scoreDisplay);

    this->m_scoreLayout = new QVBoxLayout(m_scoreDisplay);

    this->scores = new std::vector<QWidget*>();

    LoadHighScores();

    this->m_backToMainButtonHS = new QPushButton(tr("Back"), this);
    QObject::connect(m_backToMainButtonHS, &QPushButton::clicked, this, &HighscoreMenu::showStartMenu);
    this->m_controlLayout->addWidget(m_backToMainButtonHS);
}

void HighscoreMenu::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        m_mainMenueLabel->setText(tr("Highscore"));
        m_backToMainButtonHS->setText(tr("Back"));

        nummer->setText(tr("GameNumber"));
        name1->setText(tr("PlayerName1"));
        name2->setText(tr("PlayerName2"));
        winner->setText(tr("Winner"));
        moveCount->setText(tr("MoveCount"));
    } else
        QWidget::changeEvent(event);
}


void HighscoreMenu::LoadHighScores()
{
    for(int i = 0; i < scores->size(); i++)
    {
        delete(scores->at(i));
    }


    ifstream saveFile;
    saveFile.open (GameView::HIGHSCOREFILENAME);


    if(saveFile.is_open())
    {
        string s;
        getline (saveFile,s);
        saveFile.close();

        if(s.size() > 0)
        {

            std::vector<string> elems;

            split(s, '|', elems);

            for(int i = 0; i < elems.size(); i++)
            {

                std::vector<string> tempElems;
                split(elems.at(i), ';', tempElems);

                QWidget *main = new QWidget(this->m_scoreDisplay);

                m_scoreLayout->addWidget(main);

                QHBoxLayout *layout = new QHBoxLayout(main);

                std::stringstream s;

                Logger::GetLoggerIntance()->LogInfo(s.str(), __FILE__, __LINE__);

                QLabel *nummer = new QLabel(s.str().c_str(), main);
                layout->addWidget(nummer);
                QLabel *name1 = new QLabel(tempElems.at(0).c_str(), main);
                layout->addWidget(name1);
                QLabel *name2 = new QLabel(tempElems.at(1).c_str(), main);
                layout->addWidget(name2);
                QLabel *winner = new QLabel(tempElems.at(2).c_str(), main);
                layout->addWidget(winner);
                QLabel *moveCount = new QLabel(tempElems.at(3).c_str(), main);
                layout->addWidget(moveCount);

                scores->push_back(main);
            }
        }
    }
}
