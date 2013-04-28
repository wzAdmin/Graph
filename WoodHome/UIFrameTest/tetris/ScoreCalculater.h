#pragma once
class CGame;
class CScoreCalculater
{
public:
	CScoreCalculater(CGame* game);
	~CScoreCalculater(void);
public:
	unsigned int Calculate();
private:
	unsigned int Calculate(unsigned int colunm ,unsigned int row);
private:
	const static unsigned int s_ComboLeast = 5;
	const static unsigned int s_SigleScore = 5;
	CGame *m_Game;
	bool *m_Comboed;
};

