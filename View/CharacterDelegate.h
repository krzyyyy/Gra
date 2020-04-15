#pragma once
#include <QtWidgets/QWidget>
#include <QAbstractItemDelegate>
class CharacterDelegate : public QAbstractItemDelegate
{
public:
	CharacterDelegate(QWidget* parent = nullptr) :QAbstractItemDelegate(parent) {};
	void paint(QPainter* painter, const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;
	QSize sizeHint(const QStyleOptionViewItem& option,
		const QModelIndex& index) const override;
};

