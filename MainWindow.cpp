#include "MainWindow.hpp"
#include "ui_MainWindow.h"
#include <QGridLayout>
#include <QDebug>
#include <QSignalMapper>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mMaper = new QSignalMapper(this);

    ls  = {ui->pushButton, ui->pushButton_2, ui->pushButton_3, ui->pushButton_4,
           ui->pushButton_5, ui->pushButton_6, ui->pushButton_7, ui->pushButton_8, ui->pushButton_9};

    firstMove = ui->label->text();

    for(int i = 0; i< ls.size(); i++)
    {
        connect(ls[i], &QPushButton::clicked, mMaper, static_cast<void (QSignalMapper::*)()>(&QSignalMapper::map));
    }
    setCrossOrNull();
    connect(mMaper, static_cast<void (QSignalMapper::*)(const QString&)>(&QSignalMapper::mapped), this, &MainWindow::intializeButton);
    connect(ui->newGame, &QPushButton::clicked, this, &MainWindow::pushNewGame);
}

void MainWindow::pushNewGame()
{
    for(int i = 0; i < ls.size(); i++)
    {
        ls[i]->setText("");
        ls[i]->setEnabled(true);
    }

    if(firstMove == "Player 1")
    {
        ui->label->setText("Player 2");
        firstMove = ui->label->text();
    }
    else if(firstMove == "Player 2")
    {
        ui->label->setText("Player 1");
        firstMove = ui->label->text();
    }
    setCrossOrNull();
}
void MainWindow::findWinner()
{
    textChange();
    QPushButton* board[8][3] = {{ui->pushButton, ui->pushButton_2, ui->pushButton_3},
                                {ui->pushButton_6, ui->pushButton_4, ui->pushButton_5},
                                {ui->pushButton_7, ui->pushButton_8, ui->pushButton_9},
                                {ui->pushButton, ui->pushButton_6, ui->pushButton_7},
                                {ui->pushButton_2, ui->pushButton_4, ui->pushButton_8},
                                {ui->pushButton_3, ui->pushButton_5, ui->pushButton_9},
                                {ui->pushButton, ui->pushButton_4, ui->pushButton_9},
                                {ui->pushButton_7, ui->pushButton_4, ui->pushButton_3}};
    for (int i = 0; i < 8; i++)
    {
        if(board[i][0]->text() == board[i][1]->text() && board[i][1]->text() == board[i][2]->text()
                &&board[i][2]->text() == board[i][0]->text())
        {
            if(board[i][0]->text() == "X")
            {
                ui->label->setText("WINNER is Player 1");
                for (int i = 0; i < ls.size(); i++)
                {
                    ls[i]->setEnabled(false);
                }
            }
            else if (board[i][0]->text() == "O")
            {
                ui->label->setText("WINNER is Player 2");
                for (int i = 0; i < ls.size(); i++)
                {
                    ls[i]->setEnabled(false);
                }
            }

        }
    }
}


void MainWindow::textChange()
{
    if(ui->label->text() == "Player 1")
    {
        ui->label->setText("Player 2");
    }
    else if(ui->label->text() == "Player 2")
    {
        ui->label->setText("Player 1");
    }

    setCrossOrNull();
}


void MainWindow::intializeButton(const QString &str)
{

    auto list = str.split(":");
    auto but = ls.at(list.at(1).toInt());
    but->setText(list.at(0));
    but->setEnabled(false);

    findWinner();

    //    textChange();
}

void MainWindow::setCrossOrNull()
{
    if (ui->label->text() == "Player 1")
    {
        for (int i = 0; i < ls.size(); i++)
        {
            mMaper->setMapping(ls[i], QString("X:%1").arg(i));
        }
    }

    if(ui->label->text() == "Player 2")
    {
        for (int i = 0; i < ls.size(); i++)
        {
            mMaper->setMapping(ls[i], QString("O:%1").arg(i));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
