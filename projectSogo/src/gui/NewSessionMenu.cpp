#include "NewSessionMenu.h"

NewSessionMenu::NewSessionMenu(QWidget *parent) : QWidget(parent)
{
    // mainlayout
    m_controlLayout = new QVBoxLayout(this);

    // mainlabel with title
    m_mainMenueLabel = new QLabel(tr("New Session"));
    m_mainMenueLabel->setAlignment(Qt::AlignHCenter);
    m_mainMenueLabel->setFont(QFont("Times",18,QFont::Bold));

    // inputfields for players
    m_input1stPlayername = new QLineEdit();
    m_input1stPlayername->setPlaceholderText(tr("Player1"));



    // "Start Game" Button
    m_playGameButton = new QPushButton(tr("Start Game"));
    QObject::connect(m_playGameButton, &QPushButton::clicked, this, &NewSessionMenu::startGame);

    // "Back" Button
    m_backToMainButtonNS = new QPushButton(tr("Back"));
    QObject::connect(m_backToMainButtonNS, &QPushButton::clicked, this, &NewSessionMenu::showStartMenu);

    setPlayfield();

    checkPlayfieldSize();

    setMode();

    // Signals to switch between Solo- and Multiplayergame
    QObject::connect(m_checkBoxPvPnetwork, &QCheckBox::clicked, m_networkparameterWidget, &QWidget::show);
    QObject::connect(m_checkBoxPvPnetwork, &QCheckBox::clicked, m_pvpLocalWidget, &QWidget::hide);
    QObject::connect(m_checkBoxPvPnetwork, &QCheckBox::clicked, m_skillWidget, &QWidget::hide);

    QObject::connect(m_checkBoxPvPlocal, &QCheckBox::clicked, m_networkparameterWidget, &QWidget::hide);
    QObject::connect(m_checkBoxPvPlocal, &QCheckBox::clicked, m_skillWidget, &QWidget::hide);
    QObject::connect(m_checkBoxPvPlocal, &QCheckBox::clicked, m_pvpLocalWidget, &QWidget::show );

    QObject::connect(m_checkBoxPvC, &QCheckBox::clicked, m_skillWidget, &QWidget::show);
    QObject::connect(m_checkBoxPvC, &QCheckBox::clicked, m_pvpLocalWidget, &QWidget::hide);
    QObject::connect(m_checkBoxPvC, &QCheckBox::clicked, m_networkparameterWidget, &QWidget::hide);

    m_player1Starts = new QRadioButton(tr("Player1Start"), this);

    // add menu item to menue layout
    m_controlLayout->addWidget(m_mainMenueLabel);
    m_controlLayout->addWidget(m_input1stPlayername);
    m_controlLayout->addWidget(m_player1Starts);
    m_controlLayout->addWidget(m_playfieldGroupBox);
    m_controlLayout->addWidget(m_modeGroupBox);
    m_controlLayout->addWidget(m_skillWidget);
    m_controlLayout->addLayout(m_checkBoxNetworkLayout);
    m_controlLayout->addWidget(m_pvpLocalWidget);
    m_controlLayout->addWidget(m_networkparameterWidget);
    m_controlLayout->addWidget(m_playGameButton);
    m_controlLayout->addWidget(m_backToMainButtonNS);
}

void NewSessionMenu::setPlayfield()
{
    // checkboxlayot(cluster) the checkbox which select the playfieldsize
    m_checkBoxPlayfieldLayout = new QVBoxLayout();

    // checkboxes
    m_checkBoxPlayfieldSizeX3 = new QCheckBox("3x3x3");
    m_checkBoxPlayfieldSizeX4 = new QCheckBox("4x4x4");
    m_checkBoxPlayfieldSizeX5 = new QCheckBox("5x5x5");

    m_playfieldGroupBox = new QGroupBox(tr("Playfield"));
    m_playfieldGroupBox->setLayout(m_checkBoxPlayfieldLayout);

    // add checkbox to layout
    m_checkBoxPlayfieldLayout->addWidget(m_checkBoxPlayfieldSizeX3);
    m_checkBoxPlayfieldLayout->addWidget(m_checkBoxPlayfieldSizeX4);
    m_checkBoxPlayfieldSizeX4->setChecked(true);
    m_checkBoxPlayfieldLayout->addWidget(m_checkBoxPlayfieldSizeX5);
    m_checkBoxPlayfieldLayout->addStretch(1);

    // Buttongroup for exclusive click
    m_checkButtonGrp = new QButtonGroup();
    m_checkButtonGrp->addButton(m_checkBoxPlayfieldSizeX3);
    m_checkButtonGrp->addButton(m_checkBoxPlayfieldSizeX4);
    m_checkButtonGrp->addButton(m_checkBoxPlayfieldSizeX5);
    m_checkButtonGrp->setExclusive(true);

}

void NewSessionMenu::setMode()
{
    // Network area
    m_checkBoxNetworkLayout = new QVBoxLayout();
    m_modeGroupBox = new QGroupBox(tr("Mode"));
    m_modeGroupBox->setLayout(m_checkBoxNetworkLayout);

    // create checkboxes
    m_checkBoxPvC = new QCheckBox(tr("PvC"));
    m_checkBoxPvPnetwork = new QCheckBox(tr("PvP(network)"));
    m_checkBoxPvPlocal = new QCheckBox(tr("PvP(local)"));

    // add checkboxes to mainlayout
    m_checkBoxNetworkLayout->addWidget(m_checkBoxPvC);
    m_checkBoxPvC->setChecked(true);
    m_checkBoxNetworkLayout->addWidget(m_checkBoxPvPlocal);
    m_checkBoxNetworkLayout->addWidget(m_checkBoxPvPnetwork);

    // Buttongroup for exclusive click
    m_checkBoxNetworkGrp = new QButtonGroup();
    m_checkBoxNetworkGrp->addButton(m_checkBoxPvC);
    m_checkBoxNetworkGrp->addButton(m_checkBoxPvPlocal);
    m_checkBoxNetworkGrp->addButton(m_checkBoxPvPnetwork);
    m_checkBoxNetworkGrp->setExclusive(true);

    m_input2ndPlayernameLayout = new QGridLayout();
    m_input2ndPlayername = new QLineEdit();
    m_input2ndPlayername->setPlaceholderText(tr("Player2"));
    m_input2ndPlayernameLayout->addWidget(m_input2ndPlayername);

    // insert Player2 name
    m_pvpLocalWidget = new QWidget();
    m_pvpLocalWidget->setLayout(m_input2ndPlayernameLayout);
    m_pvpLocalWidget->setVisible(false);

    m_radioButtonskill1 = new QRadioButton(tr("1"));
    m_radioButtonskill2 = new QRadioButton(tr("2"));
    m_radioButtonskill3 = new QRadioButton(tr("3"));
    m_radioButtonskill1->setChecked(true);

    m_checkPlayerSkillGrp = new QButtonGroup();
    m_checkPlayerSkillGrp->addButton(m_radioButtonskill1);
    m_checkPlayerSkillGrp->addButton(m_radioButtonskill2);
    m_checkPlayerSkillGrp->addButton(m_radioButtonskill3);
    m_checkPlayerSkillGrp->setExclusive(true);

    // difficult mode
    m_skillBoxLayout = new QHBoxLayout();
    m_skillLabel = new QLabel(tr("AI - Skilllevel : "), this);
    m_skillBoxLayout->addWidget(m_skillLabel);
    m_skillBoxLayout->addWidget(m_radioButtonskill1);
    m_skillBoxLayout->addWidget(m_radioButtonskill2);
    m_skillBoxLayout->addWidget(m_radioButtonskill3);

    m_skillWidget = new QWidget();
    m_skillWidget->setLayout(m_skillBoxLayout);
    //m_skillWidget->setVisible(false);

    // network connection
    m_inputToHostlayout = new QGridLayout();

    // set networklayout
    m_networkparameterWidget = new QWidget();
    m_networkparameterWidget->setLayout(m_inputToHostlayout);
    m_networkparameterWidget->setVisible(false);

    // set hostaddress
    m_hostadress = new QLabel(tr("Hostaddress:"));
    m_inputHostaddress = new QLineEdit();
    m_inputHostaddress->setPlaceholderText(tr("Hostaddress"));

    // set port
    m_hostport = new QLabel(tr("Port:"));
    m_inputHostport = new QLineEdit();
    m_inputHostport->setPlaceholderText(tr("Port"));

    // connect button
    m_connectButtion = new QPushButton(tr("Connect"));

    // add item to networklayout
    m_inputToHostlayout->addWidget(m_hostadress,1,1,Qt::AlignCenter);
    m_inputToHostlayout->addWidget(m_inputHostaddress,1,2,Qt::AlignCenter);
    m_inputToHostlayout->addWidget(m_hostport,2,1,Qt::AlignCenter);
    m_inputToHostlayout->addWidget(m_inputHostport,2,2,Qt::AlignCenter);
}

void NewSessionMenu::checkPlayfieldSize()
{
    if(m_checkBoxPlayfieldSizeX3->isChecked())
    {
        m_playingField = new PlayingField(3);
    }
    if(m_checkBoxPlayfieldSizeX4->isChecked())
    {
        m_playingField = new PlayingField(4);
    }
    if(m_checkBoxPlayfieldSizeX5->isChecked())
    {
        m_playingField = new PlayingField(5);
    }
}

void NewSessionMenu::setPlayer()
{

    if (m_checkBoxPvC->isChecked())
    {
        if(m_player1Starts->isChecked())
        {
            if(m_input1stPlayername->text().toStdString().length() > 0 )
            {
                m_player1 = new Player(Player::HUMAN,m_input1stPlayername->text().toStdString(), PlayingField::BLUE);
            }
            else
            {
                m_player1 = new Player(Player::HUMAN,m_input1stPlayername->placeholderText().toStdString(), PlayingField::BLUE);
            }

            m_player2 = new Player(Player::AI, "Skynet", PlayingField::RED);
        }
        else
        {
            m_player1 = new Player(Player::AI, "Skynet", PlayingField::BLUE);

            if(m_input1stPlayername->text().toStdString().length() > 0 )
            {
                m_player2 = new Player(Player::HUMAN,m_input1stPlayername->text().toStdString(), PlayingField::RED);
            }
            else
            {
                m_player2 = new Player(Player::HUMAN,m_input1stPlayername->placeholderText().toStdString(), PlayingField::RED);
            }


        }

    }
    else if (m_checkBoxPvPlocal->isChecked())
    {
        if(m_player1Starts->isChecked())
        {
            m_player1 = new Player(Player::HUMAN, m_input1stPlayername->text().toStdString(), PlayingField::BLUE);
            m_player2 = new Player(Player::HUMAN, m_input2ndPlayername->text().toStdString(), PlayingField::RED);
        }
        else
        {
            m_player1 = new Player(Player::HUMAN, m_input2ndPlayername->text().toStdString(), PlayingField::BLUE);
            m_player2 = new Player(Player::HUMAN, m_input1stPlayername->text().toStdString(), PlayingField::RED);
        }
    }
}

void NewSessionMenu::checkSkill()
{
    if(m_radioButtonskill1->isChecked())
    {
        m_player2->SetSkill(1);
    }
    if(m_radioButtonskill2->isChecked())
    {
        m_player2->SetSkill(2);
    }
    if(m_radioButtonskill3->isChecked())
    {
        m_player2->SetSkill(3);
    }
}

void NewSessionMenu::mergeGameData()
{
    checkPlayfieldSize();
    setPlayer();
    checkSkill();
    m_gameData = new GameData(m_playingField, m_player1, m_player2, m_player1);
}

void NewSessionMenu::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::LanguageChange) {
        m_mainMenueLabel->setText(tr("New Session"));
        m_input1stPlayername->setText(tr("Player1"));
        m_player1Starts->setText(tr("Player1Start"));
        m_skillLabel->setText(tr("AI - Skilllevel : "));
        m_playfieldGroupBox->setTitle(tr("Playfield"));
        m_input2ndPlayername->setText(tr("Player2"));
        m_checkBoxPvPnetwork->setText(tr("PvP(network)"));
        m_checkBoxPvPlocal->setText(tr("PvP(local)"));
        m_hostadress->setText(tr("Hostaddress:"));
        m_inputHostaddress->setText(tr("Hostaddress"));
        m_hostport->setText(tr("Port:"));
        m_inputHostport->setText(tr("Port"));
        m_connectButtion->setText(tr("Connect"));
        m_playGameButton->setText(tr("Start Game"));
        m_backToMainButtonNS->setText(tr("Back"));
    } else
        QWidget::changeEvent(event);
}
