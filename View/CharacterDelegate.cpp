#include "CharacterDelegate.h"
#include <QImage>
#include <QPainter>
#include <QBrush>
#include <QRect>

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
	
	QPoint health_place = option.rect.topLeft + QPoint((option.rect.width * 0.05), option.rect.height*0.7);
	painter->drawText(option.rect, values[3]);
	painter->restore();
}

QSize CharacterDelegate::sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const
{
	QVariant var = index.model()->data(index, Qt::SizeHintRole);
	QSize img_size = var.value<QSize>();
	return img_size;
}
