#include "MyModel.h"
#include <QImage>
#include <QString>
#include "CharacterViewData.h"
#include "..\Gra\Pomurnik.h"
//#include "..\Gra\Character.h"
#include "..\Gra\Galadriela.h"

MyModel::MyModel(QObject* parent)
    : QAbstractTableModel(parent)
{
    //std::unique_ptr<ICharacter> ptr = std::make_unique<Pomurnik>();
    auto first_elem = std::make_pair(CharacterViewData("galadriela"), std::make_unique<Pomurnik>());
    auto second_elem = std::make_pair(CharacterViewData("pomurnik"), std::make_unique<Galadriela>());

    characters.emplace_back(move(second_elem));
    characters.emplace_back(move(first_elem));
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
    if (role == Qt::DisplayRole) {
        int healt = characters[index.column()].second->getAttribVal(attributC::live);
        int healt_max = characters[index.column()].second->getAttribDefVal(attributC::live);
        int concentration = characters[index.column()].second->getAttribVal(attributC::concentration);
        int concentration_max = characters[index.column()].second->getAttribDefVal(attributC::concentration);
        QString variables = QString::number(healt)+","+ QString::number(healt_max)+","+ QString::number(concentration)+","+ QString::number(concentration_max);
        return variables;

    }
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
