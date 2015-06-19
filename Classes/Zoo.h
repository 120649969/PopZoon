#ifndef _ZOO_H_
#define _ZOO_H_

#include "cocos2d.h"
#include "PropBase.h"

class Zoon;

struct ZoonPos
{
	int Row;	//��
	int Col;	//��

	ZoonPos(int _r, int _c)
	{
		Row = _r;
		Col = _c;
	}

	inline bool operator==(const ZoonPos& pos) const
	{
		return (pos.Row == Row && pos.Col == Col);
	}
};


class Zoo : public cocos2d::Node
{
public:
	//����һ��iRow��iCol�еĶ���԰
	static Zoo* create(int iRow, int iCol);

	//��ȡ���д�С
	int getRowSize();
	int getColSize();

	//���ö���֮��ļ��
	void setSpace(float fSpace);

	//ͨ�������±��ȥ����
	Zoon* getZoon(int iRow, int iCol);

	//�ڶ���԰�����/����һ������
	void setZoon(int iRow, int iCol, Zoon* pZoon);

	//������������
	std::vector<ZoonPos> check(int iRow, int iCol);

	//������԰
	void order();

	//��⶯��԰�ܷ��������
	std::vector<ZoonPos> checkCanPop();

	//��ʼ����
	virtual void onPopBegin();

	//����������
	virtual void onPopEnded();

	//һ��Zoon��������
	virtual void onOnePoped(int iRow, int iCol, Zoon* zoon);

	//������Ϻ�
	virtual void onOrderBegin();

	//������Ϻ�
	virtual void onOrderEnded();

	//��ȡ�ٶ�
	float getSpeed();

	//���䶯��
	virtual cocos2d::ActionInterval* getColAction(int iCol);

	//���򶯻�
	virtual cocos2d::ActionInterval* getRowAction(int iRow);

protected:
	virtual bool init(int iRow, int iCol);

	Zoo();

	virtual ~Zoo();

	void _addZoon(int iType, int iRow, int iCol);
	
	void _addRandomZoon(int iRow, int iCol);

	bool onTouchBenginLisener(cocos2d::Touch* touch, cocos2d::Event* eve);

	//�������
	//@return �Ƿ�����ɣ�open���в�����ֵ
	bool _checkOpenList();

	//���ձ����Ƿ������Ԫ��
	bool _isCloseListHave(ZoonPos pos);

	//���Open�����Ƿ������Ԫ��
	bool _isOpenListHave(ZoonPos pos);

	//����Open����
	//����ձ����и�Ԫ�أ���ô����������Ԫ��
	void _pushInOpenList(ZoonPos pos);

protected:
	int m_iRowSize;			//��
	int m_iColSize;			//��

	float m_fWidth;			//Zoon��
	float m_fHeight;		//Zoon��

	float m_fSpace;			//���

	float m_fSpeed;			//�����ٶ�

	std::vector<Zoon*>		m_vZoons;		//���Ｏ��

	std::vector<ZoonPos>	m_vOpen;		//δ���Ľڵ�
	std::vector<ZoonPos>	m_vClose;		//�Լ��Ľڵ�

	bool m_isPoping;		//����������ʶ

	PropBase*				m_nowProp;		//now prop(null is normal)
};

#endif