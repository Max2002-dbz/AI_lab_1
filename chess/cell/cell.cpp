#include "cell.h"
#include "ui_cell.h"

Cell::Cell(QWidget *parent, int w, int h, std::size_t pos, std::function<void(bool willBeSwitch, std::size_t pos)> callback)
    :
    QWidget(parent), ui(new Ui::Cell)
{
    ui->setupUi(this);

    this->pos = pos;
    this->callback = callback;
    this->setFixedSize(w, h);
    this->show();
}

Cell::~Cell()
{
    delete ui;
}

void Cell::setQueen()
{
    ui->label->setStyleSheet("image: url(:/images/queen.png);");
    isWithQueen = true;
}

void Cell::enterEvent(QEvent *event)
{
    if (isWithQueen){
        callback(true, pos);
    }
}

void Cell::leaveEvent(QEvent *event)
{
    if (isWithQueen){
        callback(false, pos);
    }
}

void Cell::setColor(Color color)
{
    switch (color)
    {
        case Color::bread: {
            this->setStyleSheet("background: #94533f;");
            this->color = color;
            break;
        }
        case Color::white:
        {
            this->setStyleSheet("background: #e8e8e8;");
            this->color = color;
            break;
        }
    }
}

void Cell::setDot(std::size_t n)
{
    if (n < 8){
        ui->label->setStyleSheet("image: url(:/images/dot.png); padding: 30%;");
    }
    else if (n < 12){
        ui->label->setStyleSheet("image: url(:/images/dot.png); padding: 23%;");
    }
    else if (n < 18){
        ui->label->setStyleSheet("image: url(:/images/dot.png); padding: 15%;");
    }
    else{
        ui->label->setStyleSheet("image: url(:/images/dot.png); padding: 10%;");
    }
}

void Cell::removeDot()
{
    ui->label->setStyleSheet("");
}


