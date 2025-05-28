#include "settingsview.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>

SettingsView::SettingsView()
{
    m_layout = new QVBoxLayout(this);

    m_titleLabel = new QLabel("Settings");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-size: 12px; font-weight: bold;");
    m_layout->addWidget(m_titleLabel);

    QHBoxLayout *nameLayout = new QHBoxLayout();
    m_nameLabel = new QLabel("Name");
    m_nameLine = new QLineEdit();
    m_nameLine->setText("player");
    nameLayout->addWidget(m_nameLabel);
    nameLayout->addWidget(m_nameLine);
    m_layout->addLayout(nameLayout);

    QHBoxLayout *rowsLayout = new QHBoxLayout();
    m_rowsLabel = new QLabel("Rows:");
    m_rowsSpinBox = new QSpinBox();
    m_rowsSpinBox->setRange(4, 10);
    m_rowsSpinBox->setValue(4);
    rowsLayout->addWidget(m_rowsLabel);
    rowsLayout->addWidget(m_rowsSpinBox);
    m_layout->addLayout(rowsLayout);

    QHBoxLayout *columnsLayout = new QHBoxLayout();
    m_colsLabel = new QLabel("Columns:");
    m_colsSpinBox = new QSpinBox();
    m_colsSpinBox->setRange(4, 10);
    m_colsSpinBox->setValue(4);
    columnsLayout->addWidget(m_colsLabel);
    columnsLayout->addWidget(m_colsSpinBox);
    m_layout->addLayout(columnsLayout);

    m_confirmButton = new QPushButton("Confirm");
    m_layout->addWidget(m_confirmButton);

    connect(m_confirmButton, &QPushButton::clicked, this, &SettingsView::handleSettingsConfirmed);
}

void SettingsView::handleSettingsConfirmed()
{
    emit settingsConfirmed(m_rowsSpinBox->value(), m_colsSpinBox->value(), m_nameLine->text());
}

void SettingsView::setDimensions(quint32 rows, quint32 cols)
{
    m_rowsSpinBox->setValue(rows);
    m_colsSpinBox->setValue(cols);
}

const QString& SettingsView::playerName() const
{
    return m_nameLine->text();
}
