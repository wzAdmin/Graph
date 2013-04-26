#include "FontEngine.h"
#include "Graphics.h"
#include "Transfrom.h"
#include "PtAlongLine.h"
void CGraphics::DrawTextW(const wchar_t* str ,int left , int bottom,const Font& ft,float rotation,const CBound* clipBuond /*= NULL*/ )
{
	if(!str)
		return;
	CBound dest,bound;
	CTransfrom tf;
	int orgleft = left , orgbottom = bottom;
	tf.SetRotation(rotation);
	while (L'\0' !=*str)
	{
		FontImage ftImage = CFontEngine::Instance().GetFont(*str, ft.width,ft.height);
		dest.Top(bottom - ftImage.top);
		dest.Left(left+ftImage.left);
		dest.Right(dest.Left() + ftImage.bound.Width() - 1);
		dest.Bottom(dest.Top() + ftImage.bound.Height() -1);
		tf.SetAnchorPoint(float(ftImage.bound.Left() + orgleft - dest.Left()),
			float(ftImage.bound.Bottom() + orgbottom - dest.Bottom()) );
		tf.SetPosition(float(orgleft) , float(orgbottom));
		tf.Update();
		if(!clipBuond)
			DrawImage(ftImage.pGrayImage,tf,ft.color,&ftImage.bound);
		else
			DrawImage(ftImage.pGrayImage,tf,ft.color,&ftImage.bound,clipBuond);
		left += ftImage.advanceX;
		bottom += ftImage.advanceY;
		str++;
	}
}
void CGraphics::DrawTextW(const wchar_t* str,int left , int bottom,const Font& ft,const CBound* clipBuond /*= NULL*/)
{
	if(!str)
		return;
	CBound oldclip = GetClipBound();
	if(clipBuond)
	{
		CBound newclip = oldclip;
		if(CBound::Intersect(newclip , *clipBuond ,newclip))
			SetClipBound(newclip);
		else
			return ;
	}
	CBound dest,bound;
	while (L'\0' !=*str)
	{
		FontImage ftImage = CFontEngine::Instance().GetFont(*str, ft.width,ft.height);
		dest.Top(bottom - ftImage.top);
		dest.Left(left+ftImage.left);
		dest.Right(dest.Left() + ftImage.bound.Width() - 1);
		dest.Bottom(dest.Top() + ftImage.bound.Height() -1);
		if(!clipBuond)
			DrawGrayImage(ftImage.pGrayImage,ftImage.bound,dest,ft.color);
		else if(CBound::Intersect(dest,*clipBuond,bound))
			DrawGrayImage(ftImage.pGrayImage,ftImage.bound,dest,ft.color);
		left += ftImage.advanceX;
		bottom += ftImage.advanceY;
		str++;
	}
	SetClipBound(oldclip);
}
void CGraphics::DrawTextW( const wchar_t* str ,const CBound& dest, const Font& ft ,ALIGN align)
{
	if(!str)
		return;
	CBound src;
	int bottom = 0;
	const wchar_t* srcStr = str;
	if(L'\0' != *str)
	{
		FontImage ftImage = CFontEngine::Instance().GetFont(*str, ft.width,ft.height);
		src.Right(src.Right() + ftImage.advanceX);
		src.Top(bottom - ftImage.top);
		src.Bottom(src.Top() + ftImage.bound.Height() - 1);
		bottom += ftImage.advanceY;
		str++;
	}
	while (L'\0' != *str)
	{
		FontImage ftImage = CFontEngine::Instance().GetFont(*str, ft.width,ft.height);
		src.Right(src.Right() + ftImage.advanceX);
		src.Top(MIN(src.Top(),bottom - ftImage.top));
		src.Bottom(MAX(src.Bottom(),bottom - ftImage.top + ftImage.bound.Height() - 1));
		bottom += ftImage.advanceY;
		str++;
	}
	CPosition pos = GetAlignPostion(dest,src,align);
	DrawTextW(srcStr , pos.X() , pos.Y() ,ft,&dest);
}

void CGraphics::DrawTextW( const wchar_t* str ,const CPosition* pts,int ptsCount,const Font& ft, float space, float firstDis /*= .0f*/ ,bool loop/* = false*/)
{
	int len =wcslen(str);
	int index = 0;
	wchar_t Ch[2]={0};
	CPtAlongLine aline;
	aline.Initialize(pts,5,6.0f,50.0f);
	while (aline.Next())
	{
		Ch[0]= str[index++];
		DrawTextW(Ch,aline.X(),aline.Y(),ft,aline.GetRotation() - MATH_PI /2);
		if(len == index)
		{
			if(loop)
				index = 0;
			else
				return;
		}	
	}
}

CPosition CGraphics::GetAlignPostion(const CBound& dest, const CBound& src,ALIGN align)
{
	CPosition postion;
	switch(align)
	{
	case LEFT:
		postion.X(dest.Left() - src.Left());
		postion.Y((dest.Top() + dest .Bottom() - src.Top() - src.Bottom()) / 2);
		break;
	case LEFTTOP:
		postion.X(dest.Left() - src.Left());
		postion.Y(dest.Top() - src.Top());
		break;
	case LEFTBOTTOM:
		postion.X(dest.Left() - src.Left());
		postion.Y(dest.Bottom() - src.Bottom());
		break;
	case RIGHT:
		postion.X(dest.Right() - src.Right());
		postion.Y((dest.Top() + dest .Bottom() - src.Top() - src.Bottom()) / 2);
		break;
	case RIGHTTOP:
		postion.X(dest.Right() - src.Right());
		postion.Y(dest.Top() - src.Top());
		break;
	case RIGHTBOTTOM:
		postion.X(dest.Right() - src.Right());
		postion.Y(dest.Bottom() - src.Bottom());
		break;
	case TOP:
		postion.X((dest.Left() + dest.Right() - src.Left() - src.Right())/2);
		postion.Y(dest.Top() - src.Top());
		break;
	case BOTTOM:
		postion.X((dest.Left() + dest.Right() - src.Left() - src.Right())/2);
		postion.Y(dest.Bottom() - src.Bottom());
		break;
	case CENTER:
		postion.X((dest.Left() + dest.Right() - src.Left() - src.Right())/2);
		postion.Y((dest.Top() + dest .Bottom() - src.Top() - src.Bottom()) / 2);
		break;
	default:
		postion.X(dest.Left() - src.Left());
		postion.Y((dest.Top() + dest .Bottom() - src.Top() - src.Bottom()) / 2);
	}
	return postion;
}

unsigned int CGraphics::GetCharWidthW( wchar_t ch, const Font& ft )
{
	FontImage fim = sFontEngine.GetFont(ch,ft.width,ft.height);
	return fim.advanceX ;
}
