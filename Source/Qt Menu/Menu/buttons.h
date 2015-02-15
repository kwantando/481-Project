#ifndef BUTTONS_H
#define BUTTONS_H

#include <QWidget>
#include <QtWidgets>

enum Difficulty {
    EASY,
    MEDIUM,
    HARD
};

enum Mode {
    SONG,
    PATTERN
};

class Buttons : public QWidget
{
    Q_OBJECT
public:
    Buttons(QWidget *parent = 0);
    QHBoxLayout *diff_buttons;
    QHBoxLayout *mode_buttons;
    //void show_difficulty();
    //void show_mode();
private slots:
    void easy();
    void medium();
    void hard();
    void song();
    void pattern();
private:
    Difficulty difficulty;
    Mode mode;
};

#endif // BUTTONS_H
