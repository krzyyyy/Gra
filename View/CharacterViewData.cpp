#include "CharacterViewData.h"
#include <QPainter>

CharacterViewData::CharacterViewData(const QString& name_) :name(name_), valid(false) 
{
	load(name_);
}

bool CharacterViewData::load(QString name_)
{
	valid = false;
	QImage character_img = QImage(":/images/" + name_ + "/character");
	QImage background_img = QImage(":/images/" + name_ + "/background");
	if (!character_img.isNull() && !background_img.isNull()) {
		valid = true;
	}
	if (character_img.size() != QSize(320, 320)) {
		character_img =  character_img.scaled(QSize(320, 320));
	}
	if (background_img.size() != QSize(350, 400)) {
		background_img = background_img.scaled(QSize(350, 400));
	}
	img = QImage(background_img.size(), QImage::Format::Format_BGR30);
	QBrush brush = QBrush(background_img);
	QPainter painter(&img);
	painter.setBrush(brush);
	painter.drawRoundedRect(background_img.rect(), 15, 15);
	brush = QBrush(character_img);
	painter.setBrush(brush);
	painter.drawRoundedRect(character_img.rect(), 15, 15);
	return valid;
}

void CharacterViewData::getQImage(QImage& img_)
{
	img_ = img.copy();
}
