#pragma once
class Attributes
{
public:
	Attributes(double life_, double concentration_, double armor_,
		double damage_, double dodge_);
	Attributes& operator =(const Attributes&) = default;
	~Attributes();
	void passRound();
	bool isAlive();
	//get group
	double getLife() { return life; }
	double getConcentration() { return concentration; }
	double getArmor() { return armor; }
	double getDamage() { return damage; }
	double getDodge() { return dodge; }
	//get modificators group
	double getLifeM() { return lifeM; }
	double getConcentrationM() { return  concentrationM; }
	double getArmorM() { return  armorM; }
	double getDamageM() { return  damageM; }
	double getDodgeM() { return  damageM; }
	//get time action group
	double getLifeT() { return lifeT; }
	double getConcentrationT() { return  concentrationT; }
	double getArmorT() { return  armorT; }
	double getDamageT() { return  damageT; }
	double getDodgeT() { return  damageT; }
	//get current attributes 
	double getLifeC() { return life*(1 + lifeM); }
	double getConcentrationC() { return concentration*(1 + concentrationM); }
	double getArmorC() { return armor*(1 + armorM); }
	double getDamageC() { return damage*(1 + damage); }
	double getDodgeC() { return dodge*(1 + damage); }
	//set group
	void setLife(double l) { life = l; }
	void setConcentration(double c) { concentration = c; }
	void setArmor(double a) { armor = a; }
	void setDamage(double d) { damage = d; }
	void setDodge(double d) { dodge = d; }
	// sets modificators group
	void setLifeM(double l) { lifeM = l; }
	void setConcentrationM(double c) { concentrationM = c; }
	void setArmorM(double a) { armorM = a; }
	void setDamageM(double d) { damageM = d; }
	void setDodgeM(double d) { dodgeM = d; }
	// sets time action group
	void setLifeT(int l) { lifeT = l; }
	void setConcentrationT(int c) { concentrationT = c; }
	void setArmorT(int a) { armorT = a; }
	void setDamageT(int d) { damageT = d; }
	void setDodgeT(int d) { dodgeT = d; }
	
private:
	//attributes
	double life;
	double concentration;
	double armor;
	double damage;
	double dodge;
	//attributes modificators 0-1
	double lifeM;
	double concentrationM;
	double armorM;
	double damageM;
	double dodgeM;
	// time of modificators action
	int lifeT;
	int concentrationT;
	int armorT;
	int damageT;
	int dodgeT;

};

