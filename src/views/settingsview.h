#pragma once

#include <QWidget>

class QVBoxLayout;
class QPushButton;
class QLabel;
class QSpinBox;
class QLineEdit;

class SettingsView : public QWidget
{
    Q_OBJECT

public:
    SettingsView();
    void setDimensions(quint32 rows, quint32 cols);

signals:
    void settingsConfirmed(quint32 newRows, quint32 newCols, const QString& playerName);

private slots:
    void handleSettingsConfirmed();

private:
    QVBoxLayout *m_layout;

    QLabel *m_titleLabel;
    QLabel *m_nameLabel;
    QLabel *m_rowsLabel;
    QLabel *m_colsLabel;

    QLineEdit *m_nameLine;

    QSpinBox *m_rowsSpinBox;
    QSpinBox *m_colsSpinBox;

    QPushButton *m_confirmButton;

    const QString& playerName() const;
};
