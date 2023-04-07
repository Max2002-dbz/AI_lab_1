#ifndef CHESS_H
#define CHESS_H

#include <QWidget>
#include <cell.h>
#include <QHBoxLayout>
#include "vidpal.h"
#include "MyAlgorithm.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
class Chess;
}
QT_END_NAMESPACE

class Chess: public QWidget
{
Q_OBJECT

public:
    explicit Chess(QWidget *parent = nullptr);
    ~Chess() override;

    void update_chess();
    void remove_cell();
    void hover_effect(bool willBeSwitch, std::size_t pos);
private:
    Ui::Chess *ui;
    std::size_t n = 8;
    std::size_t max_size = 250;
    std::size_t max_n = 30;
    QVector<QHBoxLayout*> vLayout;
    QVector<Cell*> vCell;
    bool isSecondCall = false;
    Vidpal vidpal;
    MyAlgorithm myAlgorithm;
    std::vector<int> result;
};


#endif //CHESS_H
