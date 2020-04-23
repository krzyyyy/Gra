#include "CharacterViewData.h"
#include <QPainter>

CharacterViewData::CharacterViewData(const QString& name_) :name(name_), valid(false) 
{
	load(name_);
}

bool CharacterViewData::load(QString name_)
{
	auto background_size = QSize(300, 400);
	auto character_size = QSize(background_size.width()*0.9 , background_size.width() * 0.9);
	valid = false;
	QImage character_img = QImage(":/images/" + name_ + "/character");
	QImage background_img = QImage(":/images/" + name_ + "/background");
	if (!character_img.isNull() && !background_img.isNull()) {
		valid = true;
	}
	if (character_img.size() != character_size) {
		character_img =  character_img.scaled(character_size);
	}
	if (background_img.size() != background_size) {
		background_img = background_img.scaled(background_size);
	}
	img = QImage(background_img.size(), QImage::Format::Format_BGR30);
	QBrush brush = QBrush(background_img);
	QPainter painter(&img);
	painter.setBrush(brush);
	painter.drawRoundedRect(background_img.rect(), 15, 15);
	int width_margin = (background_img.width() - character_img.width()) / 2;
	auto move_pt = QPoint(width_margin, width_margin);
	int height_margin = (background_img.height() - character_img.height()) / 2;
	auto character_rect = QRect(character_img.rect().topLeft() + move_pt, character_img.rect().bottomRight() + move_pt);
	brush = QBrush(character_img);
	brush.setTransform(QTransform(1, 0, 0, 1, width_margin, width_margin));
	painter.setBrush(brush);
	painter.drawRoundedRect(character_rect, 15, 15);
	return valid;
}

void CharacterViewData::getQImage(QImage& img_)
{
	img_ = img.copy();
}
