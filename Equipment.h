#pragma once

struct EquInfo
{
	int			id;
	std::string	name;
	int			atk;
	int			def;
	int			price;
	Image*		icon;
};

class Equipment : public SingletonBase<Equipment>
{
	EquInfo*	equipment[9];

public:
	Equipment();
	~Equipment();

	bool Init();
	void Release();

	void TxtLoad(const TCHAR * loadFileName);
	void XmlLoad();
	EquInfo* GetInfo(int _id);
};

