#include "palindromemodel.h"

PalindromeModel::PalindromeModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}

int PalindromeModel::rowCount(const QModelIndex& /*parent*/) const
{
    return m_values.count();
}

int PalindromeModel::columnCount(const QModelIndex& /*parent*/) const
{
    return m_columCount;
}

QVariant PalindromeModel::data(const QModelIndex& index, int role) const
{
    QVariant ret;

    if(!index.isValid())
    {
        return ret;
    }

    if(role != Qt::DisplayRole)
    {
        return ret;
    }

    switch(index.column()) {
    case 0:
        if(m_values.keys().count() > index.row())
        {
            ret = m_values.keys().at(index.row());
        }
        break;
    case 1:
        if(m_values.keys().count() > index.row())
        {
            ret = m_values.value(m_values.keys().at(index.row()));
        }
        break;
    default:
        break;
    }

    return ret;
}

QVariant PalindromeModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant ret;

    if(role != Qt::DisplayRole)
    {
        return ret;
    }

    if(orientation == Qt::Horizontal)
    {
        switch(section) {
        case 0:
            ret = "Word";
            break;
        case 1:
            ret = "Count";
            break;
        default:
            ret = QString::number(section);
            break;
        }
    }
    else
    {
        ret = QString::number(section);
    }

    return ret;
}

void PalindromeModel::clear()
{
    beginRemoveRows(QModelIndex(), 0, m_values.count() - 1);

    m_values.clear();

    endRemoveRows();
}

void PalindromeModel::append(const QString &word)
{
    if(m_values.contains(word))
    {
        ++m_values[word];
        int index{0};
        for(const QString& key: m_values.keys())
        {
            if(key == word)
            {
                emit dataChanged(this->index(index, 1), this->index(index, 1));
            }
            ++index;
        }
    }
    else
    {
        beginInsertRows(QModelIndex(), m_values.count(), m_values.count());
        m_values[word] = 1;
        endInsertRows();
    }
}
