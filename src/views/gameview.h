#pragma once

#include <QWidget>
#include <QVector>
#include "../game.h"

class QGridLayout;
class QPushButton;

class GameView : public QWidget
{
    Q_OBJECT

public:
    GameView(int rows, int cols, QWidget *parent = nullptr);

    void renderBoard(const Game &);

    void updateCell(int row, int col, const QString& value);

    void clearBoard();

private:
    int m_rows;
    int m_cols;
    QGridLayout *m_layout;
    QVector<QPushButton*> m_cells;

    void setCellColor(QPushButton *cell);
};
