#include "buttons.h"

Buttons::Buttons(QWidget *parent) : QWidget(parent)
{
    QPushButton *easy_button = new QPushButton("Easy");
    QPushButton *medium_button = new QPushButton("Medium");
    QPushButton *hard_button = new QPushButton("Hard");
    QPushButton *song_button = new QPushButton("Song");
    QPushButton *pattern_button = new QPushButton("Tone Pattern");
 //   QPushButton *back = new QPushButton("Back");

    connect(easy_button, SIGNAL(clicked()), this, SLOT(easy()));
    connect(medium_button, SIGNAL(clicked()), this, SLOT(medium()));
    connect(hard_button, SIGNAL(clicked()), this, SLOT(hard()));
    connect(song_button, SIGNAL(clicked()), this, SLOT(song()));
    connect(pattern_button, SIGNAL(clicked()), this, SLOT(pattern()));
//    connect(back, SIGNAL(clicked()), this, SLOT(back()));

    QSize size(100, 100);
    easy_button->setMinimumSize(size);
    medium_button->setMinimumSize(size);
    hard_button->setMinimumSize(size);
    song_button->setMinimumSize(size);
    pattern_button->setMinimumSize(size);

    diff_buttons = new QHBoxLayout;
    diff_buttons->addWidget(easy_button);
    diff_buttons->addWidget(medium_button);
    diff_buttons->addWidget(hard_button);
    diff_buttons->setSpacing(3);

    mode_buttons = new QHBoxLayout;
    mode_buttons->addWidget(song_button);
    mode_buttons->addWidget(pattern_button);
    mode_buttons->setSpacing(3);
}

void Buttons::easy() {
    difficulty = EASY;
}
void Buttons::medium() {
    difficulty = MEDIUM;
}
void Buttons::hard() {
    difficulty = HARD;
}
void Buttons::song() {
    mode = SONG;
}
void Buttons::pattern() {
    mode = PATTERN;
}
