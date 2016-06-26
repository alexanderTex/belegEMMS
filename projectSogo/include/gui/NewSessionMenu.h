#ifndef NEWSESSIONMENU_H
#define NEWSESSIONMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QGridLayout>
#include <QPushButton>
#include <QObject>


class NewSessionMenu : public QWidget
{
    Q_OBJECT
public:
    explicit NewSessionMenu(QWidget *parent = 0);

signals:

public slots:

private:
    QVBoxLayout *m_controlLayout;

    QLabel *m_mainMenueLabel;

    QLineEdit *m_inputPlayername;

    QVBoxLayout *m_checkBoxPlayfieldLayout;

    QLabel *m_checkBoxPlayfieldLabel;

    QCheckBox *m_checkBoxPlayfieldSizeX3;

    QCheckBox *m_checkBoxPlayfieldSizeX4;

    QCheckBox *m_checkBoxPlayfieldSizeX5;

    QButtonGroup *m_checkButtonGrp;

    QVBoxLayout *m_checkBoxNetworkLayout;

    QCheckBox *m_checkBoxNetworkSolo;

    QCheckBox *m_checkBoxNetworkMulti;

    QLabel *m_checkBoxNetworkLabel;

    QButtonGroup *m_checkBoxNetworkGrp;

    QGridLayout *m_inputToHostlayout;

    QWidget *m_networkparameterWidget;

    QLabel *m_hostadress;

    QLineEdit *m_inputHostaddress;

    QLabel *m_hostport;

    QLineEdit *m_inputHostport;

    QPushButton *m_connectButtion;

    QPushButton *m_backToMainButtonNS;
};

#endif // NEWSESSIONMENU_H
