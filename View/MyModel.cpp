#include "MyModel.h"
#include <QImage>

MyModel::MyModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    QImage image = QImage();
    images.push_back(QImage(":/images/galadriela"));
    images.push_back(QImage(":/images/pomurnik"));
}

int MyModel::rowCount(const QModelIndex& /*parent*/) const
{
    return 2;
}

int MyModel::columnCount(const QModelIndex& /*parent*/) const
{
    return 3;
}

QVariant MyModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
        return QString("Row%1, Column%2")
        .arg(index.row() + 1)
        .arg(index.column() + 1);
    else if (role == Qt::BackgroundRole) {
        QVariant var;
        if (abs(index.row() - index.column()) % 2 == 0)
            return images[0];
        else
            return images[1];
        return var;
    }
    else if (role == Qt::SizeHintRole) {
        return images[0].size();
    }

    return QVariant();
}
