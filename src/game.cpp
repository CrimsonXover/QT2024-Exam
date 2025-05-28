#include "game.h"
#include <QRandomGenerator>

Game::Game(quint32 rows, quint32 cols) : m_rows(rows), m_cols(cols), m_board(rows * cols) {
    resetScore();
    spawnRandomCell(2);
}

void Game::resetBoard()
{
    for(qint32 i = 0; i < m_board.size(); i++)
        m_board[i] = "";

    resetScore();
    spawnRandomCell(2);
}

void Game::spawnRandomCell(quint32 count)
{
    if (isBoardFull())
        return;

    for (qint32 i = 0; i < count;)
    {
        auto row = QRandomGenerator::global()->bounded(m_rows);
        auto col = QRandomGenerator::global()->bounded(m_cols);
        if (getCell(row, col).isEmpty()) {
            auto val = QRandomGenerator::global()->bounded(100) < 75 ? 2 : 4;
            setCell(row, col, QString::number(val));
            i++;
        }
    }
}

void Game::setCell(quint32 row, quint32 col, const QString &val)
{
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
        throw std::out_of_range("setCell called on an out of range cell");
    m_board[row * m_cols + col] = val;
}

const QString& Game::getCell(quint32 row, quint32 col) const
{
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
        throw std::out_of_range("getCell called on an out of range cell");
    return m_board[row * m_cols + col];
}

bool Game::isBoardFull() const
{
    for (qint32 i = 0; i < m_board.size(); i++)
        if (m_board[i].isEmpty()) return false;

    return true;
}

bool Game::isGameOver() const
{
    if (!isBoardFull()) return false;

    for (qint32 row = 0; row < m_rows; row++)
        for (qint32 col = 0; col < m_cols; col++)
        {
            QString current = getCell(row, col);
            if (col < m_cols - 1 && current == getCell(row, col + 1)) return false;
            if (row < m_rows - 1 && current == getCell(row + 1, col)) return false;
        }
    return true;
}

void Game::moveCell(quint32 orgRow, quint32 orgCol, quint32 desRow, quint32 desCol)
{
    QString orgValue = getCell(orgRow, orgCol);
    QString desValue = getCell(desRow, desCol);

    if (!orgValue.isEmpty() && desValue.isEmpty())
    {
        setCell(desRow, desCol, orgValue);
        setCell(orgRow, orgCol, "");
    }
    else if (!orgValue.isEmpty() && orgValue == desValue)
    {
        auto mergedValue = orgValue.toInt() * 2;
        setCell(desRow, desCol, QString::number(mergedValue));
        setCell(orgRow, orgCol, "");
        m_score += mergedValue;
    }
}

void Game::moveLeft()
{
    for (qint32 pass = 1; pass < m_cols; pass++)
        for (qint32 row = 0; row < m_rows; row++)
            for (qint32 col = 1; col < m_cols; col++)
                moveCell(row, col, row, col - 1);
}

void Game::moveRight()
{
    for (qint32 pass = 1; pass < m_cols; pass++)
        for (qint32 row = 0; row < m_rows; row++)
            for (qint32 col = m_cols - 2; col >= 0; col--)
                moveCell(row, col, row, col + 1);
}

void Game::moveUp()
{
    for (qint32 pass = 1; pass < m_rows; pass++)
        for (qint32 row = 1; row < m_rows; row++)
            for (qint32 col = 0; col < m_cols; col++)
                moveCell(row, col, row - 1, col);
}

void Game::moveDown()
{
    for (qint32 pass = 1; pass < m_rows; pass++)
        for (qint32 row = m_rows - 2; row >= 0; row--)
            for (qint32 col = 0; col < m_cols; col++)
                moveCell(row, col, row + 1, col);
}

quint32 Game::rows() const { return m_rows; }

quint32 Game::cols() const { return m_cols; }

const quint32& Game::score() const { return m_score; }

void Game::resetScore(){ m_score = 0; }
