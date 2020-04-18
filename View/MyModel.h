#pragma once
#include <QAbstractTableModel>
class MyModel : public QAbstractTableModel {
    Q_OBJECT
public:
    MyModel(QObject* parent = nullptr);
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
private:
    std::vector<QImage> images;
};

