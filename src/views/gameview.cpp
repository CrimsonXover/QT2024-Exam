#include "gameview.h"
#include <QGridLayout>
#include <QPushButton>

GameView::GameView(int rows, int cols, QWidget *parent) : QWidget(parent), m_rows(rows), m_cols(cols)
{
    m_layout = new QGridLayout(this);
    m_cells.resize(rows * cols);

    for (int row = 0; row < rows; ++row)
        for (int col = 0; col < cols; ++col)
        {
            int index = row * cols + col;
            QPushButton *cell = new QPushButton;
            cell->setFixedSize(50, 50);
            cell->setFocusPolicy(Qt::NoFocus);
            m_layout->addWidget(cell, row, col);
            m_cells[index] = cell;
        }
}

void GameView::renderBoard(const Game &game)
{
    for (int row = 0; row < game.rows(); ++row)
    {
        for (int col = 0; col < game.cols(); ++col)
        {
            QString value = game.getCell(row, col);
            updateCell(row, col, value);
        }
    }
}

void GameView::updateCell(int row, int col, const QString &value)
{
    int index = row * m_cols + col;
    QPushButton *cell = m_cells[index];
    cell->setText(value);
    setCellColor(cell);
}

void GameView::clearBoard()
{
    for (int i = 0; i < m_cells.size(); i++) {
        m_cells[i]->setText("");
        setCellColor(m_cells[i]);
    }
}

void GameView::setCellColor(QPushButton *cell)
{
    const int value = cell->text().toInt();
    QString color = "lightgray";
    QString textColor = "black";

    switch (value) {
    case 2:    color = "#fbfced"; break;
    case 4:    color = "#ecefc6"; break;
    case 8:    color = "#ffb296"; break;
    case 16:   color = "#ff7373"; break;
    case 32:   color = "#f6546a"; textColor = "white"; break;
    case 64:   color = "#8b0000"; textColor = "white"; break;
    case 128:  color = "#794044"; textColor = "white"; break;
    case 256:  color = "#31698a"; textColor = "white"; break;
    case 512:  color = "#297A76"; textColor = "white"; break;
    case 1024: color = "#2D8A68"; textColor = "white"; break;
    case 2048: color = "#1C9F4E"; textColor = "white"; break;
    }

    cell->setStyleSheet(QString("background-color: %1; color: %2; border: 1px solid #ccc;")
                            .arg(color)
                            .arg(textColor));
}
