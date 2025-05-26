#pragma once
#include<QWidget>

class QVBoxLayout;
class QLabel;
class QPushButton;

class LeaderboardView : public QWidget
{
    Q_OBJECT
public:
    LeaderboardView();

signals:
    void backClicked();

private:
    QVBoxLayout *m_layout;

    QLabel *m_titleLabel;
    QPushButton *m_backButton;
};
