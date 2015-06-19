/************************************************************************** 
* Copyright (c) 2015, pxbomb, All rights reserved. 

* File		: PropNormal.h
* Date		: 2015/06/17 22:16  
* Author	: WilhanTian
* Email		: wilhan.tian@gmail.com
* Depict	: 
**************************************************************************/
#ifndef _PROPNORMAL_H_
#define _PROPNORMAL_H_

#include "cocos2d.h"
#include "PropBase.h"
#include "Zoo.h"

class PropNormal : public PropBase
{
public:
	static PropNormal* getInstance();

	virtual void onHandle(Zoo* pZoo, int iRow, int iCol);

protected:
	//������������
	std::vector<ZoonPos> check(Zoo* pZoo, int iRow, int iCol);

	//�������
	//@return �Ƿ�����ɣ�open���в�����ֵ
	bool _checkOpenList(Zoo* pZoo);

	//���ձ����Ƿ������Ԫ��
	bool _isCloseListHave(ZoonPos pos);

	//���Open�����Ƿ������Ԫ��
	bool _isOpenListHave(ZoonPos pos);

	//����Open����
	//����ձ����и�Ԫ�أ���ô����������Ԫ��
	void _pushInOpenList(ZoonPos pos);

protected:
	std::vector<ZoonPos>	m_vOpen;		//δ���Ľڵ�
	std::vector<ZoonPos>	m_vClose;		//�Լ��Ľڵ�

	static PropNormal* s_instance;
};

#endif // _PROPNORMAL_H_/