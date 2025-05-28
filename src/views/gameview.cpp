#include "gameview.h"
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>

GameView::GameView(quint32 rows, quint32 cols, QWidget *parent) : QWidget(parent), m_rows(rows), m_cols(cols)
{
    m_mainLayout = new QGridLayout(this);
    m_controlsLayout = new QHBoxLayout();

    m_scoreLabel = new QLabel("Score:");
    m_scoreLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    m_scoreValue = new QLabel("0");
    m_scoreValue->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

    m_resetButton = new QPushButton("Reset");
    m_resetButton->setFocusPolicy(Qt::NoFocus);
    m_backButton = new QPushButton("Back");
    m_backButton->setFocusPolicy(Qt::NoFocus);

    m_controlsLayout->addWidget(m_scoreLabel);
    m_controlsLayout->addWidget(m_scoreValue);
    m_controlsLayout->addWidget(m_resetButton);
    m_controlsLayout->addWidget(m_backButton);

    connect(m_resetButton, &QPushButton::clicked, this, &GameView::resetClicked);
    connect(m_backButton, &QPushButton::clicked, this, &GameView::backClicked);


    m_mainLayout->addLayout(m_controlsLayout, 0, 0, 1, cols);

    m_cells.resize(rows * cols);

    for (quint32 row = 0; row < rows; row++)
        for (quint32 col = 0; col < cols; col++)
        {
            quint32 index = row * cols + col;
            QPushButton *cell = new QPushButton;

            qint32 width = 200 / rows;
            qint32 height = 200 / cols;

            cell->setFixedSize(width, height);
            cell->setFocusPolicy(Qt::NoFocus);
            m_mainLayout->addWidget(cell, row + 1, col);
            m_cells[index] = cell;
        }
}

void GameView::renderBoard(const Game &game)
{
    for (quint32 row = 0; row < game.rows(); ++row)
    {
        for (quint32 col = 0; col < game.cols(); ++col)
        {
            QString value = game.getCell(row, col);
            updateCell(row, col, value);
        }
    }
    updateScore(game.score());
}

void GameView::updateCell(quint32 row, quint32 col, const QString &value)
{
    quint32 index = row * m_cols + col;
    QPushButton *cell = m_cells[index];
    cell->setText(value);
    setCellColor(cell);
}

void GameView::clearBoard()
{
    for (quint32 i = 0; i < m_cells.size(); i++) {
        m_cells[i]->setText("");
        setCellColor(m_cells[i]);
    }
}

void GameView::setCellColor(QPushButton *cell)
{
    const quint32 value = cell->text().toInt();
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

void GameView::updateScore(quint32 score)
{
    m_scoreValue->setText(QString::number(score));
}
