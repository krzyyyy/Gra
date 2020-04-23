#include "CharacterDelegate.h"
#include <QImage>
#include <QPainter>
#include <QBrush>
#include <QRect>


void paintBar(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index, double width_margin,
	double bar_width, double bar_placement, Qt::GlobalColor color)
{
	QPoint health_place_top_left = option.rect.topLeft() + QPoint((option.rect.width() * width_margin), option.rect.height() * bar_placement);
	QPoint health_place_bottom_right = option.rect.topLeft() + QPoint((option.rect.width() * (1. - width_margin)), option.rect.height() * bar_placement + (option.rect.height() * bar_width));
	QRect health_rect = QRect(health_place_top_left, health_place_bottom_right);
	QBrush brush_bar = QBrush(color);
	painter->setBrush(brush_bar);
	painter->drawRoundedRect(health_rect, 10, 10);
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
	paintBar(painter, option, index, 0.05, 0.02, 0.75, Qt::GlobalColor::red);
	paintBar(painter, option, index, 0.05, 0.02, 0.8, Qt::GlobalColor::blue);

	painter->drawText(option.rect, values[3]);
	painter->restore();
}

QSize CharacterDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QVariant var = index.model()->data(index, Qt::SizeHintRole);
	QSize img_size = var.value<QSize>();
	return img_size;
}


