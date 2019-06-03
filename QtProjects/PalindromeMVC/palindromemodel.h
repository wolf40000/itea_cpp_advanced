#pragma once

#include <QtWidgets>

class PalindromeModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit PalindromeModel(QObject* parent = nullptr);
    ~PalindromeModel() override = default;

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    void clear();

    void append(const QString& word);

private:
    const int m_columCount{2};

    QHash<QString, int> m_values;
};

