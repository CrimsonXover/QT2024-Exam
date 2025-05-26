#pragma once

#include <QString>
#include <QVector>

class Game
{
public:
    Game(int rows = 4, int cols = 4);

    void resetBoard();
    void spawnRandomCell(int count = 1);

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    bool isBoardFull() const;
    bool isGameOver() const;

    void setCell(int row, int col, const QString& value);
    const QString& getCell(int row, int col) const;

    int rows() const;
    int cols() const;

private:
    int m_rows;
    int m_cols;

    void moveCell(int orgRow, int orgCol, int desRow, int desCol);

    QVector<QString> m_board;
};
