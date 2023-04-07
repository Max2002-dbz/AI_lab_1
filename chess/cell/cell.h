#ifndef CELL_H
#define CELL_H

#include <QWidget>
#include <functional>
#include <QEnterEvent>

QT_BEGIN_NAMESPACE
namespace Ui
{
class Cell;
}
QT_END_NAMESPACE

class Cell: public QWidget
{
Q_OBJECT

public:
    explicit Cell(QWidget *parent = nullptr, int w = 100, int h = 100, std::size_t pos = 0, std::function<void(bool, std::size_t)> callback = [](bool willBeSwitch, std::size_t pos){});
    ~Cell() override;

    enum Color{
        bread, white
    };

    void setQueen();
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void setColor(Color color);
    void setDot(std::size_t n);
    void removeDot();

private:
    Ui::Cell *ui;
    std::function<void(bool, std::size_t)> callback;
    bool isWithQueen = false;
    std::size_t pos;
    Color color;
};


#endif //CELL_H
