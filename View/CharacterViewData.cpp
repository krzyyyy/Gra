#include "CharacterViewData.h"

CharacterViewData::CharacterViewData(const QString& name_) :name(name_), valid(false) 
{
	load(name_);
}

bool CharacterViewData::load(QString name_)
{
	valid = false;
	img = QImage(":/images/" + name_);
	if (!img.isNull()) {
		valid = true;
	}
	return valid;
}

void CharacterViewData::getQImage(QImage& img_)
{
	img_ = img.copy();
}
