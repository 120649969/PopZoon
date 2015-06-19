#include "PropNormal.h"
#include "Zoon.h"
//---------------------------------------------------
USING_NS_CC;
//---------------------------------------------------
PropNormal* PropNormal::s_instance = NULL;
//---------------------------------------------------
PropNormal* PropNormal::getInstance()
{
	if (s_instance == NULL)
	{
		s_instance = new PropNormal();
	}
	return s_instance;
}
//---------------------------------------------------
void PropNormal::onHandle(Zoo* pZoo, int iRow, int iCol)
{
	auto list = check(pZoo, iRow, iCol);

	if (list.empty() /*|| m_isPoping*/)	//���listû��Ԫ��
	{
		return;
	}

	float delay = 0.1f;

	//����ѡ�е�Zoon
	for (int i = 0; i < list.size(); i++)
	{
		if (i == 0)
		{
			//�ص�
			//onPopBegin();
		}

		//��������
		Sequence* seqAction = Sequence::create
			(
			DelayTime::create(i * delay),
			CallFunc::create([=]()
			{
				Zoon* zoon = pZoo->getZoon(list.at(i).Row, list.at(i).Col);
				zoon->retain();
				zoon->destory();
				pZoo->setZoon(list.at(i).Row, list.at(i).Col, NULL);

				//�ص�
				//onOnePoped(list.at(i).Row, list.at(i).Col, zoon);
				zoon->release();
			}),
			NULL
			);

		pZoo->runAction(seqAction);
	}

	//onAllPoped�ص���
	pZoo->scheduleOnce([=](float delay)
	{
		//onPopEnded();
		pZoo->order();

		pZoo->unschedule("ScheduleWithOnAllPoped");

	}, delay * list.size(), "ScheduleWithOnAllPoped");
}
//---------------------------------------------------
std::vector<ZoonPos> PropNormal::check(Zoo* pZoo, int iRow, int iCol)
{
	std::vector<ZoonPos> _zoons;

	if (pZoo->getZoon(iRow, iCol) == NULL)
	{
		return _zoons;
	}

	m_vOpen.push_back(ZoonPos(iRow, iCol));

	while (!_checkOpenList(pZoo))
	{
	}

	_zoons = m_vClose;

	m_vClose.clear();
	m_vOpen.clear();

	if (_zoons.size() < 2)
		_zoons.clear();

	return _zoons;
}
//---------------------------------------------------
bool PropNormal::_checkOpenList(Zoo* pZoo)
{
	if (m_vOpen.empty())
	{
		return true;
	}

	//��ȡ���һ��
	ZoonPos nowPos = m_vOpen.back();
	int iRow = nowPos.Row;
	int iCol = nowPos.Col;

	//����ձ�
	m_vClose.push_back(nowPos);

	//ɾ�����һ��
	m_vOpen.pop_back();

	//��ǰZoon
	Zoon* pNow = pZoo->getZoon(iRow, iCol);

	//�Ϸ�Zoon
	if (iCol < pZoo->getColSize() - 1)
	{
		Zoon* pBuf = pZoo->getZoon(iRow, iCol + 1);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow, iCol + 1));
	}

	//��Zoon
	if (iRow > 0)
	{
		Zoon* pBuf = pZoo->getZoon(iRow - 1, iCol);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow - 1, iCol));
	}

	//�·�Zoon
	if (iCol > 0)
	{
		Zoon* pBuf = pZoo->getZoon(iRow, iCol - 1);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow, iCol - 1));
	}

	//�ҷ�Zoon
	if (iRow < pZoo->getRowSize() - 1)
	{
		Zoon* pBuf = pZoo->getZoon(iRow + 1, iCol);

		if (pBuf && pNow->getType() == pBuf->getType())
			_pushInOpenList(ZoonPos(iRow + 1, iCol));
	}

	return false;
}
//---------------------------------------------------
bool PropNormal::_isCloseListHave(ZoonPos pos)
{
	for (int i = 0; i < m_vClose.size(); i++)
	{
		if (m_vClose.at(i) == pos)
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------------
bool PropNormal::_isOpenListHave(ZoonPos pos)
{
	for (int i = 0; i < m_vOpen.size(); i++)
	{
		if (m_vOpen.at(i) == pos)
		{
			return true;
		}
	}
	return false;
}
//---------------------------------------------------
void PropNormal::_pushInOpenList(ZoonPos pos)
{
	if (!_isCloseListHave(pos) && !_isOpenListHave(pos))
	{
		m_vOpen.push_back(pos);
	}
}
//---------------------------------------------------