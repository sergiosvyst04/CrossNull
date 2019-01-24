#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPushButton>
#include <QSignalMapper>
#include <ui_MainWindow.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    //    void playerChange();
    void textChange();
    void setCrossOrNull();
    void intializeButton(const QString &str);
    void findWinner();
    void pushNewGame();

private:
    Ui::MainWindow *ui;
    QSignalMapper *mMaper;
    QString firstMove;
    QList<QPushButton *> ls;
};

#endif // MAINWINDOW_HPP
