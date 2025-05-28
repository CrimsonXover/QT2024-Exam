#pragma once

#include <QWidget>

#include "../game.h"

class QGridLayout;
class QPushButton;
class QLabel;
class QHBoxLayout;

class GameView : public QWidget
{
    Q_OBJECT

public:
    GameView(quint32 rows, quint32 cols, QWidget *parent = nullptr);

    void renderBoard(const Game &);

    void updateCell(quint32 row, quint32 col, const QString& value);

    void clearBoard();

    void updateScore(quint32 score);

signals:
    void resetClicked();
    void backClicked();

private:
    quint32 m_rows;
    quint32 m_cols;
    QGridLayout *m_mainLayout;
    QHBoxLayout *m_controlsLayout;

    QLabel *m_scoreLabel;
    QLabel *m_scoreValue;
    QPushButton *m_resetButton;
    QPushButton *m_backButton;

    QVector<QPushButton*> m_cells;

    void setCellColor(QPushButton *cell);
};
