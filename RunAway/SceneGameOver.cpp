#include"SceneGameOver.h"

#include"Console.h"
#include"Input.h"

#include"resource.h"

#include"SceneSelHero.h"
#include"SceneMain.h"

#include<iostream>

using namespace Core;

#define iRETRY	2
#define iMAIN	1
#define iEND	0

#define drawOption(index, color)\
	draw(Pos(39 - (index) * 4, 30), 102 + (index), "﹤", 2, color)
#define drawLeft(color)\
	render<const char*>(Pos(25, 32), "９", color)
#define drawRight(color)\
	render<const char*>(Pos(72, 32), "Ⅱ", color)

SceneGameOver::SceneGameOver(int stage) : m_stage(stage)
{
	system("cls");
	draw(Pos(0, 0), GameOver, "﹥", 2);
	drawLeft(WHITE); drawRight(WHITE);
	drawOption(m_nowIndex, WHITE);
	render<const char*>(Pos(40, 25), "忙式式式式式式式式忖", LIGHTYELLOW);
	render<const char*>(Pos(40, 26), "弛                弛", LIGHTYELLOW);
	render<const char*>(Pos(40, 27), "戌式式式式式式式式戎", LIGHTYELLOW);
	render<const char*>(Pos(44, 26), "蝶纔檜雖", BRIGHTWHITE);
	render<int>(Pos(53, 26), stage, BRIGHTWHITE);
}
SceneGameOver::~SceneGameOver(){}

void SceneGameOver::update(void)
{
	if (trigger(VK_LEFT))
		drawLeft(LIGHTRED);
	if (trigger(VK_RIGHT))
		drawRight(LIGHTRED);
	if (release(VK_LEFT))
		drawLeft(WHITE);
	if (release(VK_RIGHT))
		drawRight(WHITE);

	if (repeat(VK_RIGHT))
	{
		switch (m_nowIndex)
		{
		case iRETRY:
			clearRect(Rect(37, 32, 36, 30));
			clearRect(Rect(37, 66, 70, 30));
			m_nowIndex = iMAIN;
			break;
		case iMAIN:
			clearRect(Rect(37, 34, 38, 30));
			clearRect(Rect(37, 62, 66, 30));
			m_nowIndex = iEND;
			break;
		case iEND:
			m_nowIndex = iRETRY;
			break;
		}
		drawOption(m_nowIndex, WHITE);
	}
	else if (repeat(VK_LEFT))
	{
		switch (m_nowIndex)
		{
		case iRETRY:
			clearRect(Rect(37, 32, 36, 30));
			clearRect(Rect(37, 64, 68, 30));
			m_nowIndex = iEND;
			break;
		case iMAIN:	
			m_nowIndex = iRETRY;
			break;
		case iEND:	
			m_nowIndex = iMAIN;	
			break;
		}
		drawOption(m_nowIndex, WHITE);
	}
	else if (trigger(VK_SPACE))
	{
		drawOption(m_nowIndex, LIGHTRED);
		switch (m_nowIndex)
		{
		case iRETRY:
			changeScene(new SceneSelHero(m_stage));
			break;
		case iMAIN:
			changeScene(new SceneMain);
			break;
		case iEND:
			changeScene(NULL);
			break;
		}
	}
}