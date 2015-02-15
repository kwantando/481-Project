#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "buttons.h"
/*
QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
QT_END_NAMESPACE*/

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
private slots:
    void easy();
    void medium();
    void hard();
    void song();
    void pattern();
    void back();
private:
    Difficulty difficulty;
    Mode mode;
    QHBoxLayout *diff_buttons;
    QHBoxLayout *mode_buttons;
    QWidget *diff_widget;
    QWidget *mode_widget;
    QVBoxLayout *grid;
    QLabel *button_info;
    QPushButton *back_button;
    void show_difficulty();
    void show_mode();
};

#endif // MAINWINDOW_H
