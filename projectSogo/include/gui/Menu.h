#ifndef MENUE_H
#define MENUE_H

#include <QLabel>
#include <QPushButton>
#include <QFont>
#include <QApplication>
#include <QObject>
#include <QMainWindow>
#include <QLayout>
#include <QVBoxLayout>
#include <QDesktopWidget>
#include <QDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QButtonGroup>
#include <QVBoxLayout>
#include <QPushButton>

#include "StartMenu.h"
#include "NewSessionMenu.h"
#include "HighscoreMenu.h"
#include "LoadMenu.h"

class Menu : public QMainWindow
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = 0);

signals:

public slots:

private:
};

#endif // MENUE_H
