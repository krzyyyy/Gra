#include "CharacterDelegate.h"
#include <QImage>
#include <QPainter>
#include <QBrush>
#include <QRect>


void paintBar(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, double width_margin,
	double bar_width, double bar_placement, int value, int max_value, Qt::GlobalColor color)
{
	QPoint health_place_top_left = option.rect.topLeft() + QPoint((option.rect.width() * width_margin), option.rect.height() * bar_placement);
	int bar_length = option.rect.width() * (1. - (2 * width_margin))*(value/max_value);
	QPoint health_place_bottom_right = health_place_top_left + QPoint(bar_length,  (option.rect.height() * bar_width));
	QRect health_rect = QRect(health_place_top_left, health_place_bottom_right);
	QBrush brush_bar = QBrush(color);
	painter->setBrush(brush_bar);
	painter->drawRoundedRect(health_rect, 10, 10);
	painter->drawText(QPoint(health_place_top_left.x()+ bar_length/2, health_place_bottom_right.y()), QString::number(value)+"/"+QString::number(max_value));
}
void CharacterDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QVariant data = index.model()->data(index, Qt::DisplayRole);
	QStringList values = data.toString().split(",");
	QVariant var = index.model()->data(index, Qt::BackgroundRole);
	QImage img = var.value<QImage>();
	QBrush brush  = QBrush(img);
	painter->save();
	painter->setBrush(brush);
	painter->drawRoundedRect(option.rect, 10, 15);
	paintBar(painter, option, index, 0.05, 0.03, 0.75, values[1].toInt(), values[0].toInt(), Qt::GlobalColor::red);
	paintBar(painter, option, index, 0.05, 0.03, 0.8, values[3].toInt(), values[2].toInt(), Qt::GlobalColor::blue);

	painter->restore();
}

QSize CharacterDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QVariant var = index.model()->data(index, Qt::SizeHintRole);
	QSize img_size = var.value<QSize>();
	return img_size;
}


