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
private:
	//void paintBar(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index,
	//	double width_margin, double bar_width, double bar_placement, Qt::GlobalColor color = Qt::GlobalColor::red);
};

