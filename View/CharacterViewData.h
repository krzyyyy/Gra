#pragma once
#include <iostream>
#include <QString>
#include <QImage>

class CharacterViewData {
public:
	CharacterViewData(const QString& name_);
	CharacterViewData() :name(""), valid(false) {};
	bool load(QString name_);
	void getQImage(QImage& img_);
private:
	bool valid;
	QImage img;
	QString name;





};