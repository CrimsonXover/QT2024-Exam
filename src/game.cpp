#include "game.h"
#include <QRandomGenerator>

Game::Game(int rows, int cols) : m_rows(rows), m_cols(cols), m_board(rows * cols) {
    spawnRandomCell(2);
}

void Game::resetBoard()
{
    for(auto i = 0; i < m_board.size(); i++)
        m_board[i] = "";

    spawnRandomCell(2);
}

void Game::spawnRandomCell(int count)
{
    if (isBoardFull())
        return;

    for (int i = 0; i < count;)
    {
        int row = QRandomGenerator::global()->bounded(m_rows);
        int col = QRandomGenerator::global()->bounded(m_cols);
        if (getCell(row, col).isEmpty()) {
            int val = QRandomGenerator::global()->bounded(100) < 75 ? 2 : 4;
            setCell(row, col, QString::number(val));
            i++;
        }
    }
}

void Game::setCell(int row, int col, const QString &val)
{
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
        throw std::out_of_range("setCell called on an out of range cell");
    m_board[row * m_cols + col] = val;
}

const QString& Game::getCell(int row, int col) const
{
    if (row < 0 || row >= m_rows || col < 0 || col >= m_cols)
        throw std::out_of_range("getCell called on an out of range cell");
    return m_board[row * m_cols + col];
}

bool Game::isBoardFull() const
{
    for (auto i = 0; i < m_board.size(); i++)
        if (m_board[i].isEmpty()) return false;

    return true;
}

bool Game::isGameOver() const
{
    if (!isBoardFull()) return false;

    for (int row = 0; row < m_rows; row++)
        for (int col = 0; col < m_cols; col++)
        {
            QString current = getCell(row, col);
            if (col < m_cols - 1 && current == getCell(row, col + 1)) return false;
            if (row < m_rows - 1 && current == getCell(row + 1, col)) return false;
        }
    return true;
}

void Game::moveCell(int orgRow, int orgCol, int desRow, int desCol)
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
        setCell(desRow, desCol, QString::number(orgValue.toInt() * 2));
        setCell(orgRow, orgCol, "");
    }
}

void Game::moveLeft()
{
    for (int pass = 1; pass < m_cols; pass++)
        for (int row = 0; row < m_rows; row++)
            for (int col = 1; col < m_cols; col++)
                moveCell(row, col, row, col - 1);
}

void Game::moveRight()
{
    for (int pass = 1; pass < m_cols; pass++)
        for (int row = 0; row < m_rows; row++)
            for (int col = m_cols - 2; col >= 0; col--)
                moveCell(row, col, row, col + 1);
}

void Game::moveUp()
{
    for (int pass = 1; pass < m_rows; pass++)
        for (int row = 1; row < m_rows; row++)
            for (int col = 0; col < m_cols; col++)
                moveCell(row, col, row - 1, col);
}

void Game::moveDown()
{
    for (int pass = 1; pass < m_rows; pass++)
        for (int row = m_rows - 2; row >= 0; row--)
            for (int col = 0; col < m_cols; col++)
                moveCell(row, col, row + 1, col);
}

int Game::rows() const { return m_rows; }
int Game::cols() const { return m_cols; }
