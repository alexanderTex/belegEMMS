#include "NewSessionMenu.h"

NewSessionMenu::NewSessionMenu(QWidget *parent) : QWidget(parent)
{
    this->m_controlLayout = new QVBoxLayout(this);

    this->m_mainMenueLabel = new QLabel(tr("New Session"));
    this->m_mainMenueLabel->setAlignment(Qt::AlignHCenter);
    this->m_mainMenueLabel->setFont(QFont("Times",18,QFont::Bold));

    // input field for player
    this->m_inputPlayername = new QLineEdit();
    this->m_inputPlayername->setPlaceholderText(tr("Playername"));

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
        this->m_checkBoxPlayfieldLayout->addWidget(m_checkBoxPlayfieldSizeX4);
        this->m_checkBoxPlayfieldLayout->addWidget(m_checkBoxPlayfieldSizeX5);

        // Buttongroup for exclusive click
        this->m_checkButtonGrp = new QButtonGroup();
        this->m_checkButtonGrp->addButton(m_checkBoxPlayfieldSizeX3);
        this->m_checkButtonGrp->addButton(m_checkBoxPlayfieldSizeX4);
        this->m_checkButtonGrp->addButton(m_checkBoxPlayfieldSizeX5);
        this->m_checkButtonGrp->setExclusive(true);

    // Network area
    this->m_checkBoxNetworkLayout = new QVBoxLayout();
    this->m_checkBoxNetworkLabel = new QLabel(tr("Netzwerk"));

        this->m_checkBoxNetworkSolo = new QCheckBox("SP");
        this->m_checkBoxNetworkMulti = new QCheckBox("MP");

        this->m_checkBoxNetworkLayout->addWidget(m_checkBoxNetworkLabel);
        this->m_checkBoxNetworkLayout->addWidget(m_checkBoxNetworkSolo);
        this->m_checkBoxNetworkLayout->addWidget(m_checkBoxNetworkMulti);

        // Buttongroup for exclusive click
        this->m_checkBoxNetworkGrp = new QButtonGroup();
        this->m_checkBoxNetworkGrp->addButton(m_checkBoxNetworkSolo);
        this->m_checkBoxNetworkGrp->addButton(m_checkBoxNetworkMulti);
        this->m_checkBoxNetworkGrp->setExclusive(true);

    // Cluster input for network connection
    this->m_inputToHostlayout = new QGridLayout();

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

    this->m_inputToHostlayout->addWidget(m_hostadress,1,1,1,1,Qt::AlignCenter);
    this->m_inputToHostlayout->addWidget(m_inputHostaddress,1,2,1,1,Qt::AlignCenter);
    this->m_inputToHostlayout->addWidget(m_hostport,2,1,1,1,Qt::AlignCenter);
    this->m_inputToHostlayout->addWidget(m_inputHostport,2,2,1,1,Qt::AlignCenter);
    this->m_inputToHostlayout->addWidget(m_connectButtion,3,1,1,1,Qt::AlignCenter);


    this->m_backToMainButtonNS = new QPushButton(tr("Zurueck"));

    // add menue item to menue layout
    this->m_controlLayout->addWidget(m_mainMenueLabel);
    this->m_controlLayout->addWidget(m_inputPlayername);
    this->m_controlLayout->addLayout(m_checkBoxPlayfieldLayout);
    this->m_controlLayout->addLayout(m_checkBoxNetworkLayout);
    this->m_controlLayout->addWidget(m_networkparameterWidget);
    //newSessionControlLayout->addLayout(inputToHostlayout);
    this->m_controlLayout->addWidget(m_backToMainButtonNS);

    // Signals to switch between Solo- and Multiplayergame
    QObject::connect(m_checkBoxNetworkMulti, SIGNAL(clicked()) , m_networkparameterWidget, SLOT(show()));
    QObject::connect(m_checkBoxNetworkSolo, SIGNAL(clicked()), m_networkparameterWidget, SLOT(hide()));
}
