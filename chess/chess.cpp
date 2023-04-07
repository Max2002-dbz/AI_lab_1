#include "chess.h"
#include "ui_chess.h"
#include <QSpacerItem>
#include <QGuiApplication>
#include <QScreen>
#include <QPushButton>
#include <thread>

Chess::Chess(QWidget *parent)
    :
    QWidget(parent), ui(new Ui::Chess)
{
    ui->setupUi(this);

    update_chess();

    ui->radioButton_vidpal->setChecked(true);

    connect(ui->pushButton, &QPushButton::clicked, this, [this]()
    {
        std::size_t t_n = ui->lineEdit->text().toInt();

        if (t_n && t_n < max_n) {
            ui->pushButton->setEnabled(false);
            this->repaint();
            if (ui->radioButton_vidpal->isChecked()){
                result = vidpal.get_vidpal(t_n);
            }
            else{
                result = myAlgorithm.get_result(t_n);
            }

            remove_cell();
            n = t_n;
            update_chess();
            ui->pushButton->setEnabled(true);
            ui->pushButton->setEnabled(true);
        }
        else{
            ui->label_result->setText("Result: Invalid N!");
            ui->label_result->setStyleSheet("color: red;");
        }
    });
}

Chess::~Chess()
{
    delete ui;
}

void Chess::update_chess()
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int screenHeight = screenGeometry.height();

    int size = (screenHeight - 40) / n;
    size = size > max_size ? max_size : size;

    vLayout.resize(n);
    for (std::size_t i = 0; i < n; ++i) {
        vLayout[i] = new QHBoxLayout();
    }

    vCell.resize(n * n);
    for (std::size_t i = 0; i < n * n; ++i) {
        vCell[i] = new Cell(this, size, size, i, [this](bool willBeSwitch, std::size_t pos){
            hover_effect(willBeSwitch, pos);
        });
    }

    for (std::size_t i = 0; i < n; ++i) {
        ui->verticalLayout_2->addLayout(vLayout[i]);
        for (std::size_t j = 0; j < n; ++j) {
            vLayout[i]->addWidget(vCell[i * n + j]);
            if ((i % 2 == 1 && j % 2 == 0) || (i % 2 == 0 && j % 2 == 1)) {
                vCell[i * n + j]->setColor(Cell::Color::bread);
            }
            else{
                vCell[i * n + j]->setColor(Cell::Color::white);
            }
        }
    }

    if (!result.empty()) {
        if (isSecondCall) {
            ui->label_result->setText("Result: Solution found");
            ui->label_result->setStyleSheet("color: green;");
        }
        else{
            isSecondCall = true;
        }

        for (std::size_t i = 0; i < n; ++i) {
            vCell[result[i] + i * n]->setQueen();
        }
    }
    else {
        if (isSecondCall) {
            ui->label_result->setText("Result: Solution not found");
            ui->label_result->setStyleSheet("color: red;");
        }
        else{
            isSecondCall = true;
        }
    }
}

void Chess::remove_cell()
{
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            vLayout[i]->removeWidget(vCell[i * n + j]);
            delete vCell[i * n + j];
        }
        ui->verticalLayout_2->removeItem(vLayout[i]);
        delete vLayout[i];
    }
    vCell.clear();
    vLayout.clear();
}

void Chess::hover_effect(bool willBeSwitch, std::size_t pos)
{
    size_t chess_i = pos / n;
    size_t chess_j = pos - n * chess_i;
    if (willBeSwitch){
        for (size_t i = 0; i < n; ++i) {
            if (chess_i != i){
                vCell[i * n + chess_j]->setDot(n);
            }
            if (chess_j != i){
                vCell[chess_i * n + i]->setDot(n);
            }
        }

        size_t next_n = chess_i > chess_j ? chess_j : chess_i;
        size_t next_i = chess_i - 1;
        size_t next_j = chess_j - 1;
        for (size_t i = 0; i < next_n; ++i) {
            vCell[next_i-- * n + next_j--]->setDot(n);
        }

        next_n = chess_i > (n - chess_j - 1) ? (n - chess_j - 1) : chess_i;
        next_i = chess_i - 1;
        next_j = chess_j + 1;
        for (size_t i = 0; i < next_n; ++i) {
            size_t pos_ = next_i-- * n + next_j++;
            vCell[pos_]->setDot(n);
        }

        next_n = (n - chess_i - 1) > (n - chess_j - 1) ? (n - chess_j - 1) : (n - chess_i - 1);
        next_i = chess_i + 1;
        next_j = chess_j + 1;
        for (size_t i = 0; i < next_n; ++i) {
            vCell[next_i++ * n + next_j++]->setDot(n);
        }

        next_n = (n - chess_i - 1) > chess_j ? chess_j : (n - chess_i - 1);
        next_i = chess_i + 1;
        next_j = chess_j - 1;
        for (size_t i = 0; i < next_n; ++i) {
            vCell[next_i++ * n + next_j--]->setDot(n);
        }
    }
    else{
        for (int i = 0; i < n; ++i) {
            if (chess_i != i){
                vCell[i * n + chess_j]->removeDot();
            }
            if (chess_j != i){
                vCell[chess_i * n + i]->removeDot();
            }
        }

        size_t next_n = chess_i > chess_j ? chess_j : chess_i;
        size_t next_i = chess_i - 1;
        size_t next_j = chess_j - 1;
        for (size_t i = 0; i < next_n; ++i) {
            vCell[next_i-- * n + next_j--]->removeDot();
        }

        next_n = chess_i > (n - chess_j - 1) ? (n - chess_j - 1) : chess_i;
        next_i = chess_i - 1;
        next_j = chess_j + 1;
        for (size_t i = 0; i < next_n; ++i) {
            size_t pos_ = next_i-- * n + next_j++;
            vCell[pos_]->removeDot();
        }

        next_n = (n - chess_i - 1) > (n - chess_j - 1) ? (n - chess_j - 1) : (n - chess_i - 1);
        next_i = chess_i + 1;
        next_j = chess_j + 1;
        for (size_t i = 0; i < next_n; ++i) {
            vCell[next_i++ * n + next_j++]->removeDot();
        }

        next_n = (n - chess_i - 1) > chess_j ? chess_j : (n - chess_i - 1);
        next_i = chess_i + 1;
        next_j = chess_j - 1;
        for (size_t i = 0; i < next_n; ++i) {
            vCell[next_i++ * n + next_j--]->removeDot();
        }
    }
}
