#include "NewSessionMenu.h"

NewSessionMenu::NewSessionMenu(QWidget *parent) : QWidget(parent)
{

    // pvc , pvp(local), pvp(network)



    this->m_controlLayout = new QVBoxLayout(this);

    this->m_mainMenueLabel = new QLabel(tr("New Session"));
    this->m_mainMenueLabel->setAlignment(Qt::AlignHCenter);
    this->m_mainMenueLabel->setFont(QFont("Times",18,QFont::Bold));

    // input field for player
    this->m_input1stPlayername = new QLineEdit();
    this->m_input1stPlayername->setPlaceholderText(tr("1st Playername"));

    // checkboxlayot(cluster) the checkbox which select the playfieldsize
    this->m_checkBoxPlayfieldLayout = new QVBoxLayout();
    this->m_checkBoxPlayfieldLabel = new QLabel(tr("Playfield"));


        // checkbox
        this->m_checkBoxPlayfieldSizeX3 = new QCheckBox("3x3x3");
        this->m_checkBoxPlayfieldSizeX4 = new QCheckBox("4x4x4");
        this->m_checkBoxPlayfieldSizeX5 = new QCheckBox("5x5x5");

        // add checkbox to layout
        this->m_checkBoxPlayfieldLayout->addWidget(m_checkBoxPlayfieldLabel);
        this->m_checkBoxPlayfieldLayout->addWidget(m_checkBoxPlayfieldSizeX3);
        this->m_checkBoxPlayfieldSizeX3->setChecked(true);
        this->m_checkBoxPlayfieldLayout->addWidget(m_checkBoxPlayfieldSizeX4);
        this->m_checkBoxPlayfieldLayout->addWidget(m_checkBoxPlayfieldSizeX5);

        // Buttongroup for exclusive click
        this->m_checkButtonGrp = new QButtonGroup();
        this->m_checkButtonGrp->addButton(m_checkBoxPlayfieldSizeX3);
        this->m_checkButtonGrp->addButton(m_checkBoxPlayfieldSizeX4);
        this->m_checkButtonGrp->addButton(m_checkBoxPlayfieldSizeX5);
        this->m_checkButtonGrp->setExclusive(true);

    Logger::GetLoggerIntance()->LogInfo("after ButtonGrp");

    this->m_input2ndPlayernameLayout = new QGridLayout();
    this->m_input2ndPlayername = new QLineEdit();
    this->m_input2ndPlayername->setPlaceholderText(tr("2nd Playername"));
    this->m_input2ndPlayernameLayout->addWidget(m_input2ndPlayername);

    // Network area
    this->m_checkBoxNetworkLayout = new QVBoxLayout();
    this->m_checkBoxNetworkLabel = new QLabel(tr("Netzwerk"));

        this->m_checkBoxPvC = new QCheckBox(tr("PvC"));
        this->m_checkBoxPvPnetwork = new QCheckBox(tr("PvP(network)"));
        this->m_checkBoxPvPlocal = new QCheckBox(tr("PvP(local)"));

        this->m_checkBoxNetworkLayout->addWidget(m_checkBoxNetworkLabel);
        this->m_checkBoxNetworkLayout->addWidget(m_checkBoxPvC);
        this->m_checkBoxPvC->setChecked(true);
        this->m_checkBoxNetworkLayout->addWidget(m_checkBoxPvPlocal);
        this->m_checkBoxNetworkLayout->addWidget(m_checkBoxPvPnetwork);

        // Buttongroup for exclusive click
        this->m_checkBoxNetworkGrp = new QButtonGroup();
        this->m_checkBoxNetworkGrp->addButton(m_checkBoxPvC);
        this->m_checkBoxNetworkGrp->addButton(m_checkBoxPvPlocal);
        this->m_checkBoxNetworkGrp->addButton(m_checkBoxPvPnetwork);
        this->m_checkBoxNetworkGrp->setExclusive(true);

    Logger::GetLoggerIntance()->LogInfo("after ButtonGrp");

    // Cluster input for network connection
    this->m_inputToHostlayout = new QGridLayout();

    this->m_pvpLocalWidget = new QWidget();
    this->m_pvpLocalWidget->setLayout(m_input2ndPlayernameLayout);
    this->m_pvpLocalWidget->setVisible(false);

    this->m_networkparameterWidget = new QWidget();
    this->m_networkparameterWidget->setLayout(m_inputToHostlayout);
    this->m_networkparameterWidget->setVisible(false);

    this->m_hostadress = new QLabel(tr("Hostadresse:"));
    this->m_inputHostaddress = new QLineEdit();
    this->m_inputHostaddress->setPlaceholderText(tr("Hostaddress"));


    this->m_hostport = new QLabel(tr("Port:"));
    this->m_inputHostport = new QLineEdit();
    this->m_inputHostport->setPlaceholderText(tr("Port"));

    this->m_connectButtion = new QPushButton(tr("Verbinden"));

    Logger::GetLoggerIntance()->LogInfo("after connectButton");

    this->m_inputToHostlayout->addWidget(m_hostadress,1,1,1,1,Qt::AlignCenter);
    this->m_inputToHostlayout->addWidget(m_inputHostaddress,1,2,1,1,Qt::AlignCenter);
    this->m_inputToHostlayout->addWidget(m_hostport,2,1,1,1,Qt::AlignCenter);
    this->m_inputToHostlayout->addWidget(m_inputHostport,2,2,1,1,Qt::AlignCenter);

    Logger::GetLoggerIntance()->LogInfo("after Hostlayout");

    this->m_playGameButton = new QPushButton(tr("Start Spiel"));

    this->m_backToMainButtonNS = new QPushButton(tr("Zurueck"));
    QObject::connect(m_backToMainButtonNS, &QPushButton::clicked, this, &NewSessionMenu::showStartMenu);

    //this->mergeGameData();

    this->setPlayfieldSize();
    /* test playfieldsize
    std::stringstream s;
    s << this->m_playingField->GetFieldSize();
    Logger::GetLoggerIntance()->LogInfo(s.str());
    */

    // add menu item to menue layout
    this->m_controlLayout->addWidget(m_mainMenueLabel);
    this->m_controlLayout->addWidget(m_input1stPlayername);
    this->m_controlLayout->addLayout(m_checkBoxPlayfieldLayout);
    this->m_controlLayout->addLayout(m_checkBoxNetworkLayout);
    this->m_controlLayout->addWidget(m_pvpLocalWidget);
    this->m_controlLayout->addWidget(m_networkparameterWidget);
    this->m_controlLayout->addWidget(m_playGameButton);
    this->m_controlLayout->addWidget(m_backToMainButtonNS);

    // Signals to switch between Solo- and Multiplayergame
    QObject::connect(m_checkBoxPvPnetwork, &QCheckBox::clicked, m_networkparameterWidget, &QWidget::show);
    QObject::connect(m_checkBoxPvPnetwork, &QCheckBox::clicked, m_pvpLocalWidget, &QWidget::hide);
    QObject::connect(m_checkBoxPvPlocal, &QCheckBox::clicked, m_networkparameterWidget, &QWidget::hide);
    QObject::connect(m_checkBoxPvPlocal, &QCheckBox::clicked, m_pvpLocalWidget, &QWidget::show );
    QObject::connect(m_checkBoxPvC, &QCheckBox::clicked, m_pvpLocalWidget, &QWidget::hide);
    QObject::connect(m_checkBoxPvC, &QCheckBox::clicked, m_networkparameterWidget, &QWidget::hide);

    QObject::connect(m_playGameButton, &QPushButton::clicked, this, &NewSessionMenu::startGame);

}

void NewSessionMenu::setPlayfieldSize()
{
    if(this->m_checkBoxPlayfieldSizeX3->isChecked())
    {
        this->m_playingField = new PlayingField(3);
    }
    if(this->m_checkBoxPlayfieldSizeX4->isChecked())
    {
        this->m_playingField = new PlayingField(4);
    }
    if(this->m_checkBoxPlayfieldSizeX5->isChecked())
    {
        this->m_playingField = new PlayingField(5);
    }
}

void NewSessionMenu::setPlayer()
{
   /*
    if (this->m_checkBoxPvC->isChecked())
    {
        this->m_player1 = new Player(Player::Human,this->m_input1stPlayername->text().toStdString(), PlayingField::Blue);
        this->m_player2 = new Player(Player::Ai, "Skynet", PlayingField::Red);
    }
    else if (this->m_checkBoxPvPlocal->isChecked())
    {
        this->m_player1 = new Player(Player::Human, this->m_input1stPlayername->text().toStdString(), PlayingField::Blue);
        this->m_player2 = new Player(Player::Human, this->m_input2ndPlayername->text().toStdString(), PlayingField::Red);
    }
*/

    this->m_player1 = new Player(Player::Human, "Alex", PlayingField::Blue);
    this->m_player2 = new Player(Player::Ai, "Skynet", PlayingField::Red);

    // TODO: Networkgame

}

void NewSessionMenu::mergeGameData()
{
    this->setPlayfieldSize();
    this->setPlayer();
    this->m_gameData = new GameData(this->m_playingField,
                                    this->m_player1,
                                    this->m_player2,
                                    this->m_player2);

    Logger::GetLoggerIntance()->LogInfo(this->m_player1->GetName());
    Logger::GetLoggerIntance()->LogInfo(this->m_player2->GetName());
    std::stringstream s;
    s << this->m_playingField->GetFieldSize();
    Logger::GetLoggerIntance()->LogInfo(s.str());

}


