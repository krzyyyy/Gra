#include "MyModel.h"
#include <QImage>
#include "CharacterViewData.h"

MyModel::MyModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    auto first_elem = std::pair<CharacterViewData, int>(CharacterViewData("galadriela"), 1);
    auto second_elem = std::pair<CharacterViewData, int>(CharacterViewData("pomurnik"), 1);

    characters.push_back(first_elem);
    characters.push_back(second_elem);
    characters.push_back(second_elem);
    characters.push_back(second_elem);
    characters.push_back(first_elem);
}

int MyModel::rowCount(const QModelIndex& /*parent*/) const
{
    return 1;
}

int MyModel::columnCount(const QModelIndex& /*parent*/) const
{
    return characters.size();
}

QVariant MyModel::data(const QModelIndex& index, int role) const
{
    if (role == Qt::DisplayRole)
        return QString("Row%1, Column%2")
        .arg(index.row() + 1)
        .arg(index.column() + 1);
    else if (role == Qt::BackgroundRole) {
        QImage img;
        auto character_data = characters[index.column()].first;
        character_data.getQImage(img);
        return img;
    }
    else if (role == Qt::SizeHintRole) {
        QImage img;
        auto character_data = characters[index.column()].first;
        character_data.getQImage(img);
        return img.size();
    }

    return QVariant();
}
