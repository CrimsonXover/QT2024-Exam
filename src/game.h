#pragma once

#include <QString>
#include <QVector>

class Game
{
public:
    Game(quint32 rows = 4, quint32 cols = 4);

    void resetBoard();
    void spawnRandomCell(quint32 count = 1);

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    bool isBoardFull() const;
    bool isGameOver() const;

    const quint32& score() const;
    void resetScore();

    void setCell(quint32 row, quint32 col, const QString& value);
    const QString& getCell(quint32 row, quint32 col) const;

    quint32 rows() const;
    quint32 cols() const;

private:
    quint32 m_rows;
    quint32 m_cols;
    quint32 m_score;

    void moveCell(quint32 orgRow, quint32 orgCol, quint32 desRow, quint32 desCol);

    QVector<QString> m_board;
};
