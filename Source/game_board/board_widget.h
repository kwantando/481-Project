#ifndef BOARD_WIDGET_H
#define BOARD_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QtWidgets>
#include <random>

enum Button_Position {
    TOP_LEFT,
    TOP_MIDDLE,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_MIDDLE,
    BOTTOM_RIGHT
};

class Board_Widget : public QWidget
{
    Q_OBJECT
public:
    Board_Widget();
    void trigger(Button_Position butt_pos);
    void demo();
private slots:
    // for controller signals
    void trigger_Top_L();
    void trigger_Top_M();
    void trigger_Top_R();
    void trigger_Bottom_L();
    void trigger_Bottom_M();
    void trigger_Bottom_R();
    // for user responses
    void top_L();
    void top_M();
    void top_R();
    void bottom_L();
    void bottom_M();
    void bottom_R();
private:
    void fail();
    QPushButton *top_left;
    QPushButton *top_middle;
    QPushButton *top_right;
    QPushButton *bottom_left;
    QPushButton *bottom_middle;
    QPushButton *bottom_right;
};

#endif // BOARD_WIDGET_H
