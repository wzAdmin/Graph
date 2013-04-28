#include "ScoreCalculater.h"
#include "Game.h"

CScoreCalculater::CScoreCalculater(CGame* game):
m_Game(game)
{
	m_Comboed = new bool[game->s_ItemColunm * game->s_ItemRowCount];
	memset(m_Comboed,0,game->s_ItemColunm * game->s_ItemRowCount);
}


CScoreCalculater::~CScoreCalculater(void)
{
	delete[] m_Comboed;
	m_Comboed = 0;
}

unsigned int CScoreCalculater::Calculate()
{
	unsigned int Score = 0;
	memset(m_Comboed,0,m_Game->s_ItemColunm * m_Game->s_ItemRowCount);
	for(unsigned int i = 0 ; i < m_Game->s_ItemColunm ; i ++)
	{
		for(unsigned int j = 0 ; j < m_Game->s_ItemRowCount ; j ++)
		{
			if(m_Game->m_Items[i][j] != NOTHING &&!m_Comboed[i * m_Game->s_ItemRowCount + j])
				Score += Calculate(i ,j );
		}
	}

	for(unsigned int i = 0 ; i < m_Game->s_ItemColunm ; i ++)
	{
		for(unsigned int j = 0 ; j < m_Game->s_ItemRowCount ; j ++)
		{
			if(m_Comboed[i * m_Game->s_ItemRowCount + j])
				m_Game->m_Items[i][j] = NOTHING;
		}
	}
	return Score > 0 ? Score : -1;
}

unsigned int CScoreCalculater::Calculate(unsigned int colunm ,unsigned int row)
{
	unsigned int ComboNum= 1;
	unsigned int Score = 0;
	for( int i = colunm - 1 ; i >= 0;i --)
	{
		if(m_Game->m_Items[colunm][row] != m_Game->m_Items[i][row])
			break;
		else
			ComboNum++;
	}
	for( int i = colunm + 1 ; i < m_Game->s_ItemColunm ; i ++)
	{
		if(m_Game->m_Items[colunm][row] != m_Game->m_Items[i][row])
			break;
		else
			ComboNum++;
	}
	if(ComboNum >= s_ComboLeast)
	{
		Score += ComboNum * s_ComboLeast;
		for( int i = colunm - 1 ; i >= 0;i --)
		{
			if(m_Game->m_Items[colunm][row] != m_Game->m_Items[i][row])
				break;
			else
				this->m_Comboed[i * m_Game->s_ItemRowCount + row] = true;
		}
		for( int i = colunm ; i < m_Game->s_ItemColunm ; i ++)
		{
			if(m_Game->m_Items[colunm][row] != m_Game->m_Items[i][row])
				break;
			else
				this->m_Comboed[i * m_Game->s_ItemRowCount + row] = true;
		}
	}

	ComboNum = 1;
	for( int i = row - 1 ; i >= 0;i --)
	{
		if(m_Game->m_Items[colunm][row] != m_Game->m_Items[colunm][i])
			break;
		else
			ComboNum++;
	}
	for( int i = row + 1 ; i < m_Game->s_ItemRowCount ; i ++)
	{
		if(m_Game->m_Items[colunm][row] != m_Game->m_Items[colunm][i])
			break;
		else
			ComboNum++;
	}
	if(ComboNum >= s_ComboLeast)
	{
		Score += ComboNum * s_ComboLeast;
		for( int i = row - 1 ; i >= 0;i --)
		{
			if(m_Game->m_Items[colunm][row] != m_Game->m_Items[colunm][i])
				break;
			else
				this->m_Comboed[colunm * m_Game->s_ItemRowCount + i] = true;
		}
		for( int i = row ; i < m_Game->s_ItemRowCount ; i ++)
		{
			if(m_Game->m_Items[colunm][row] != m_Game->m_Items[colunm][i])
				break;
			else
				this->m_Comboed[colunm * m_Game->s_ItemRowCount + i] = true;
		}
	}
	return Score;
}
