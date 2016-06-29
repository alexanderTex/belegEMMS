#include "Menu.h"

Menu::Menu(QWidget *parent) : QMainWindow(parent)
{
    QWidget *mainWidget = new QWidget();
    mainWidget = new QWidget();
    mainWidget->setGeometry(200,100,450,150);
    //QGridLayout *mainLayout = new QGridLayout();
    QVBoxLayout *mainLayout = new QVBoxLayout();

    StartMenu *startMenu = new StartMenu(mainWidget);
    NewSessionMenu *newSessionMenu =new NewSessionMenu(mainWidget);
    HighscoreMenu *highscoreMenu = new HighscoreMenu(mainWidget);

    mainLayout->addWidget(newSessionMenu);

    // Zuweisung mainLayout dem mainWidget (mywidget)
    mainWidget->setLayout(mainLayout);
    // Setzt mywidget als zentrales Widget
    setCentralWidget(mainWidget);

    // show menu
    this->show();

 /*
    //--------------------------------------------\
    //  MainWidget
    //--------------------------------------------/
    QWidget* mywidget = new QWidget();
    mywidget->setGeometry(200,100,450,150);

    //--------------------------------------------\
    //  SubWidget
    //--------------------------------------------/
    QWidget* mainControlWidget = new QWidget();
    //mainControlWidget->setVisible(false);

    QWidget* highscoreControlWidget = new QWidget();
    highscoreControlWidget->setVisible(false);

    QWidget* newSessionControlWidget = new QWidget();
    newSessionControlWidget->setVisible(false);

    QWidget* loadControlWidget = new QWidget();
    loadControlWidget->setVisible(false);

    QWidget* saveControlWidget = new QWidget();



    //--------------------------------------------\
    //  SubWidget Layouts
    //--------------------------------------------/
    QVBoxLayout *mainControlLayout = new QVBoxLayout();
    QVBoxLayout *highscoreControlLayout = new QVBoxLayout();
    QVBoxLayout *newSessionControlLayout = new QVBoxLayout();
    QVBoxLayout *loadControlLayout = new QVBoxLayout();
    QVBoxLayout *saveControlLayout = new QVBoxLayout();

    // assignment widget -> layout
    mainControlWidget->setLayout(mainControlLayout);
    highscoreControlWidget->setLayout(highscoreControlLayout);
    newSessionControlWidget->setLayout(newSessionControlLayout);
    loadControlWidget->setLayout(loadControlLayout);
    saveControlWidget->setLayout(saveControlLayout);

    //--------------------------------------------\
    //  Menue Content
    //--------------------------------------------/

    //-----------------------\
    // Main Menue
    //-----------------------/
    QLabel *mainMenueLabel = new QLabel("</ Sogo >", mainControlWidget);
    mainMenueLabel->setAlignment(Qt::AlignHCenter);
    mainMenueLabel->setFont(QFont("Times",18,QFont::Bold));

    QPushButton *newSessionButton = new QPushButton("</ new session >", mainControlWidget);
    newSessionButton->setGeometry(30,10,400,30);
    QObject::connect(newSessionButton, SIGNAL(clicked()),mainControlWidget, SLOT(hide()));
    QObject::connect(newSessionButton, SIGNAL(clicked()),newSessionControlWidget, SLOT(show()));

    QPushButton *loadButton = new QPushButton("</ load >", mainControlWidget);
    loadButton->setGeometry(30,90,400,30);
    QObject::connect(loadButton, SIGNAL(clicked()), mainControlWidget, SLOT(hide()));
    QObject::connect(loadButton, SIGNAL(clicked()), loadControlWidget, SLOT(show()));

    QPushButton *highscoreButton = new QPushButton("</ highscore >", mainControlWidget);
    highscoreButton->setGeometry(30,90,1,30);
    QObject::connect(highscoreButton, SIGNAL(clicked()), mainControlWidget, SLOT(hide()));
    QObject::connect(highscoreButton, SIGNAL(clicked()), highscoreControlWidget, SLOT(show()));

    QPushButton *exitButton = new QPushButton("</ exit >", mainControlWidget);
    exitButton->setGeometry(30,90,400,30);
    QObject::connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));

    mainControlLayout->addWidget(mainMenueLabel);
    mainControlLayout->addWidget(newSessionButton);
    mainControlLayout->addWidget(loadButton);
    mainControlLayout->addWidget(highscoreButton);
    mainControlLayout->addWidget(exitButton);

    //-----------------------\
    // NewSession Menue
    //-----------------------/
    // menue name (label)
    QLabel *newSessionMenueLabel = new QLabel("</ New Session >", newSessionControlWidget);
    newSessionMenueLabel->setAlignment(Qt::AlignHCenter);
    newSessionMenueLabel->setFont(QFont("Times",18,QFont::Bold));

    // input field for player
    QLineEdit *inputPlayername = new QLineEdit();
    inputPlayername->setPlaceholderText("Playername");

    // checkboxlayot(cluster) the checkbox which select the playfieldsize
    QVBoxLayout *checkBoxPlayfieldLayout = new QVBoxLayout();
    QLabel *checkBoxPlayfieldLabel = new QLabel("Playfield");


        // checkbox
        QCheckBox *checkBoxPlayfieldSizeX3 = new QCheckBox("3x3x3");
        QCheckBox *checkBoxPlayfieldSizeX4 = new QCheckBox("4x4x4");
        QCheckBox *checkBoxPlayfieldSizeX5 = new QCheckBox("5x5x5");

        // add checkbox to layout
        checkBoxPlayfieldLayout->addWidget(checkBoxPlayfieldLabel);
        checkBoxPlayfieldLayout->addWidget(checkBoxPlayfieldSizeX3);
        checkBoxPlayfieldLayout->addWidget(checkBoxPlayfieldSizeX4);
        checkBoxPlayfieldLayout->addWidget(checkBoxPlayfieldSizeX5);

        // Buttongroup for exclusive click
        QButtonGroup *checkButtonGrp = new QButtonGroup();
        checkButtonGrp->addButton(checkBoxPlayfieldSizeX3);
        checkButtonGrp->addButton(checkBoxPlayfieldSizeX4);
        checkButtonGrp->addButton(checkBoxPlayfieldSizeX5);
        checkButtonGrp->setExclusive(true);

    // Network area
    QVBoxLayout *checkBoxNetworkLayout = new QVBoxLayout();
    QLabel *checkBoxNetworkLabel = new QLabel("Network");

        QCheckBox *checkBoxNetworkSolo = new QCheckBox("SP");
        QCheckBox *checkBoxNetworkMulti = new QCheckBox("MP");

        checkBoxNetworkLayout->addWidget(checkBoxNetworkLabel);
        checkBoxNetworkLayout->addWidget(checkBoxNetworkSolo);
        checkBoxNetworkLayout->addWidget(checkBoxNetworkMulti);

        // Buttongroup for exclusive click
        QButtonGroup *checkBoxNetworkGrp = new QButtonGroup();
        checkBoxNetworkGrp->addButton(checkBoxNetworkSolo);
        checkBoxNetworkGrp->addButton(checkBoxNetworkMulti);
        checkBoxNetworkGrp->setExclusive(true);

    // Cluster input for network connection
    QGridLayout *inputToHostlayout = new QGridLayout();

    QWidget *networkparameterWidget = new QWidget();
    networkparameterWidget->setLayout(inputToHostlayout);
    networkparameterWidget->setVisible(false);

    QLabel *hostadress = new QLabel("Hostaddress:");
    QLineEdit *inputHostaddress = new QLineEdit();
    inputHostaddress->setPlaceholderText("Hostaddress");

    QLabel *hostport = new QLabel("Hostport:");
    QLineEdit *inputHostport = new QLineEdit();
    inputHostport->setPlaceholderText("Hostport");

    QPushButton *connectButtion = new QPushButton(tr("Connect"), networkparameterWidget);

    inputToHostlayout->addWidget(hostadress,1,1,1,1,Qt::AlignCenter);
    inputToHostlayout->addWidget(inputHostaddress,1,2,1,1,Qt::AlignCenter);
    inputToHostlayout->addWidget(hostport,2,1,1,1,Qt::AlignCenter);
    inputToHostlayout->addWidget(inputHostport,2,2,1,1,Qt::AlignCenter);
    inputToHostlayout->addWidget(connectButtion,3,1,1,1,Qt::AlignCenter);


    QPushButton *backToMainButtonNS = new QPushButton("</ back >", newSessionControlWidget);

    // Signals
    QObject::connect(backToMainButtonNS, SIGNAL(clicked()), newSessionControlWidget, SLOT(hide()));
    QObject::connect(backToMainButtonNS, SIGNAL(clicked()), mainControlWidget, SLOT(show()));
    QObject::connect(checkBoxNetworkMulti, SIGNAL(clicked()) , networkparameterWidget, SLOT(show()));
    QObject::connect(checkBoxNetworkSolo, SIGNAL(clicked()), networkparameterWidget, SLOT(hide()));

    // add menue item to menue layout
    newSessionControlLayout->addWidget(newSessionMenueLabel);
    newSessionControlLayout->addWidget(inputPlayername);
    newSessionControlLayout->addLayout(checkBoxPlayfieldLayout);
    newSessionControlLayout->addLayout(checkBoxNetworkLayout);
    newSessionControlLayout->addWidget(networkparameterWidget);
    //newSessionControlLayout->addLayout(inputToHostlayout);
    newSessionControlLayout->addWidget(backToMainButtonNS);

    //-----------------------\
    // Highscore Menue
    //-----------------------/
    QLabel *highscoreMenueLabel = new QLabel("</ Highscore >", highscoreControlWidget);
    highscoreMenueLabel->setAlignment(Qt::AlignHCenter);
    highscoreMenueLabel->setFont(QFont("Times",18,QFont::Bold));

    QPushButton *backToMainButtonHS = new QPushButton("</ back >", highscoreControlWidget);
    QObject::connect(backToMainButtonHS, SIGNAL(clicked()), highscoreControlWidget, SLOT(hide()));
    QObject::connect(backToMainButtonHS, SIGNAL(clicked()), mainControlWidget, SLOT(show()));

    highscoreControlLayout->addWidget(highscoreMenueLabel);
    highscoreControlLayout->addWidget(backToMainButtonHS);

    //-----------------------\
    // Load Menue
    //-----------------------/
    QLabel *loadMenueLabel = new QLabel("</ Load >", loadControlWidget);
    loadMenueLabel->setAlignment(Qt::AlignHCenter);
    loadMenueLabel->setFont(QFont("Times",18,QFont::Bold));

    QPushButton *backToMainButtonLG = new QPushButton("</ back >", loadControlWidget);
    QObject::connect(backToMainButtonLG, SIGNAL(clicked()), loadControlWidget, SLOT(hide()));
    QObject::connect(backToMainButtonLG, SIGNAL(clicked()), mainControlWidget, SLOT(show()));

    QPushButton *loadGameButton = new QPushButton("</ load >", loadControlWidget);

    QHBoxLayout *controlButton = new QHBoxLayout();
    controlButton->addWidget(backToMainButtonLG);
    controlButton->addWidget(loadGameButton);

    loadControlLayout->addWidget(loadMenueLabel);
    loadControlLayout->addLayout(controlButton);

    //--------------------------------------------\
    //  MainLayouts
    //      addWidgets
    //--------------------------------------------/
    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->addWidget(mainControlWidget,5, 1, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(newSessionControlWidget,5, 1, 1, 1, Qt::AlignCenter);
    mainLayout->addWidget(highscoreControlWidget,5,1,1,1,Qt::AlignCenter);
    mainLayout->addWidget(loadControlWidget,5,1,1,1,Qt::AlignCenter);

    // Zuweisung mainLayout dem mainWidget (mywidget)
    mywidget->setLayout(mainLayout);
    // Setzt mywidget als zentrales Widget
    setCentralWidget(mywidget);

    //ui->setupUi(this);
 */
}
