#include <iostream>
#include "mainwindow.h"

using namespace std;

MainWindow::MainWindow()
{
    button_info = new QLabel;
    QFont font("Arial", 16, QFont::Bold);
    button_info->setFont(font);
    button_info->setAlignment(Qt::AlignCenter);

    grid = new QGridLayout;
    grid->addWidget(button_info);

    QPushButton *easy_button = new QPushButton("Easy");
    QPushButton *medium_button = new QPushButton("Medium");
    QPushButton *hard_button = new QPushButton("Hard");
    QPushButton *song_button = new QPushButton("Song");
    QPushButton *pattern_button = new QPushButton("Tone Pattern");
    back_button = new QPushButton("Back");

    connect(easy_button, SIGNAL(clicked()), this, SLOT(easy()));
    connect(medium_button, SIGNAL(clicked()), this, SLOT(medium()));
    connect(hard_button, SIGNAL(clicked()), this, SLOT(hard()));
    connect(song_button, SIGNAL(clicked()), this, SLOT(song()));
    connect(pattern_button, SIGNAL(clicked()), this, SLOT(pattern()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(back()));

    QSize mode_size(100, 100);
    easy_button->setMinimumSize(mode_size);
    medium_button->setMinimumSize(mode_size);
    hard_button->setMinimumSize(mode_size);

    QSize diff_size(140, 100);
    song_button->setMinimumSize(diff_size);
    pattern_button->setMinimumSize(diff_size);
    back_button->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    diff_buttons = new QHBoxLayout;
    diff_buttons->addWidget(easy_button);
    diff_buttons->addWidget(medium_button);
    diff_buttons->addWidget(hard_button);
    diff_buttons->setSpacing(3);

    mode_buttons = new QHBoxLayout;
    mode_buttons->addWidget(song_button);
    mode_buttons->addWidget(pattern_button);
    mode_buttons->setSpacing(3);

    diff_widget = new QWidget;
    diff_widget->setLayout(diff_buttons);
    grid->addWidget(diff_widget);

    mode_widget = new QWidget;
    mode_widget->setLayout(mode_buttons);
    grid->addWidget(mode_widget);
    grid->addWidget(back_button);

    grid->setRowMinimumHeight(1, button_info->sizeHint().rheight());
    grid->setRowMinimumHeight(3, back_button->sizeHint().rheight());

    QWidget *central = new QWidget;
    central->setLayout(grid);
    setCentralWidget(central);
    setWindowTitle("MelodiMemorí");
    setMinimumSize(175, 200);
    show_difficulty();
}

void MainWindow::show_difficulty() {
    mode_widget->hide();
    button_info->setText("Select Difficulty");
    grid->setRowMinimumHeight(1, 100);
    grid->setRowMinimumHeight(2, 0);
    diff_widget->show();
    back_button->hide();
    //back_button->setEnabled(false);
}

void MainWindow::show_mode() {
    diff_widget->hide();
    button_info->setText("Select Mode");
    grid->setRowMinimumHeight(1, 0);
    grid->setRowMinimumHeight(2, 100);
    mode_widget->show();
    back_button->show();
    //back_button->setEnabled(true);
}

void MainWindow::show_gameplay() {
    button_info->setText("Game Running");
    mode_widget->hide();
    back_button->hide();
}

void MainWindow::easy() {
    difficulty = EASY;
    show_mode();
}
void MainWindow::medium() {
    difficulty = MEDIUM;
    show_mode();
}
void MainWindow::hard() {
    difficulty = HARD;
    show_mode();
}
void MainWindow::song() {
    mode = SONG;
    show_gameplay();
}
void MainWindow::pattern() {
    mode = PATTERN;
    show_gameplay();
}

void MainWindow::back() {
    show_difficulty();
}
