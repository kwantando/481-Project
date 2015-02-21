#include "board_widget.h"
#include <iostream>

static bool DEMO = true;

Board_Widget::Board_Widget()
{
    top_left = new QPushButton("Q");
    top_middle = new QPushButton("W");
    top_right = new QPushButton("E");
    bottom_left = new QPushButton("R");
    bottom_middle = new QPushButton("T");
    bottom_right = new QPushButton("Y");

    top_left->setShortcut(Qt::Key_Q);
    top_middle->setShortcut(Qt::Key_W);
    top_right->setShortcut(Qt::Key_E);
    bottom_left->setShortcut(Qt::Key_R);
    bottom_middle->setShortcut(Qt::Key_T);
    bottom_right->setShortcut(Qt::Key_Y);

    connect(top_left, SIGNAL(clicked()), this, SLOT(top_L()));
    connect(top_middle, SIGNAL(clicked()), this, SLOT(top_M()));
    connect(top_right, SIGNAL(clicked()), this, SLOT(top_R()));
    connect(bottom_left, SIGNAL(clicked()), this, SLOT(bottom_L()));
    connect(bottom_middle, SIGNAL(clicked()), this, SLOT(bottom_M()));
    connect(bottom_right, SIGNAL(clicked()), this, SLOT(bottom_R()));

    QGridLayout *button_grid = new QGridLayout;

    button_grid->addWidget(top_left, 0, 0);
    button_grid->addWidget(top_middle, 0, 1);
    button_grid->addWidget(top_right, 0, 2);
    button_grid->addWidget(bottom_left, 1, 0);
    button_grid->addWidget(bottom_middle, 1, 1);
    button_grid->addWidget(bottom_right, 1, 2);

    QSize size(100, 100);
    top_left->setMinimumSize(size);
    top_middle->setMinimumSize(size);
    top_right->setMinimumSize(size);
    bottom_left->setMinimumSize(size);
    bottom_middle->setMinimumSize(size);
    bottom_right->setMinimumSize(size);

    setLayout(button_grid);
    if (DEMO) {
        demo();
    }
}

// Receives input from the controller to light
// up one of the buttons.
void Board_Widget::trigger(Button_Position butt_pos) {
    switch(butt_pos) {
        case TOP_LEFT:
            trigger_Top_L();
            break;
        case TOP_MIDDLE:
            trigger_Top_M();
            break;
        case TOP_RIGHT:
            trigger_Top_R();
            break;
        case BOTTOM_LEFT:
            trigger_Bottom_L();
            break;
        case BOTTOM_MIDDLE:
            trigger_Bottom_M();
            break;
        case BOTTOM_RIGHT:
            trigger_Bottom_R();
            break;
        default:
            fail();
    }
}

void Board_Widget::trigger_Top_L() {
    top_left->setStyleSheet("background-color: orange");
}

void Board_Widget::trigger_Top_M() {
    top_middle->setStyleSheet("background-color: yellow");
}

void Board_Widget::trigger_Top_R() {
    top_right->setStyleSheet("background-color: green");
}

void Board_Widget::trigger_Bottom_L() {
    bottom_left->setStyleSheet("background-color: blue");
}

void Board_Widget::trigger_Bottom_M() {
    bottom_middle->setStyleSheet("background-color: indigo");
}

void Board_Widget::trigger_Bottom_R() {
    bottom_right->setStyleSheet("background-color: violet");
}

void Board_Widget::top_L() {
    top_left->setStyleSheet("");
    if (DEMO) demo();
}

void Board_Widget::top_M() {
    top_middle->setStyleSheet("");
    if (DEMO) demo();
}

void Board_Widget::top_R() {
    top_right->setStyleSheet("");
    if (DEMO) demo();
}

void Board_Widget::bottom_L() {
    bottom_left->setStyleSheet("");
    if (DEMO) demo();
}

void Board_Widget::bottom_M() {
    bottom_middle->setStyleSheet("");
    if (DEMO) demo();
}

void Board_Widget::bottom_R() {
    bottom_right->setStyleSheet("");
    if (DEMO) demo();
}

void Board_Widget::fail() {
    top_left->setStyleSheet("background-color: red");
    top_middle->setStyleSheet("background-color: red");
    top_right->setStyleSheet("background-color: red");
    bottom_left->setStyleSheet("background-color: red");
    bottom_middle->setStyleSheet("background-color: red");
    bottom_right->setStyleSheet("background-color: red");
}

void Board_Widget::demo() {
    std::mt19937 gen(time(NULL));
    std::uniform_int_distribution<> dis(0, 5);
    Button_Position bp = static_cast<Button_Position>(dis(gen));
    trigger(bp);
}
