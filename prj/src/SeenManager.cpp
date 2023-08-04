#include"WinMain.h"
#include "SeenManager.h"
#include "MapMake.h"
#include "GameMain.h"
#include "Titol.h"
#include "Results.h"
#include "Tutorial.h"


namespace {
	MapMake map_make;
	Titol titol;
	Results results;
	GameMain game;
	Tutorial tutorial;
};

SeenManager::SeenManager() :
	SeenBase()
{
	m_seen_num = TITOL;
	m_next_seen = TITOL;
}

void SeenManager::Init()
{
	map_make.Init();
	titol.Init();
	results.Init();
	game.Init();
	tutorial.Init();
}

void SeenManager::Update()
{
	if (m_seen_num != m_next_seen) {
		switch (m_seen_num)
		{
		case TITOL:
			titol.Exit();
			break;
		case GAME:
			game.Exit();
			break;
		case RESULTS:
			results.Exit();
			break;
		case MAPMAKE:
			map_make.Exit();
		case TUTORIAL:
			tutorial.Exit();
			break;
		default:
			break;
		}
		m_seen_num = m_next_seen;
		switch (m_seen_num)
		{
		case TITOL:
			titol.Init();
			break;
		case GAME:
			game.Init();
			break;
		case RESULTS:
			results.Init();
			results.SetClearTime(game.GetGoalTime(), "a");
			break;
		case MAPMAKE:
			map_make.Init();
			break;
		case TUTORIAL:
			tutorial.Init();
			break;
		default:
			break;
		}
	}
	switch (m_seen_num)
	{
	case TITOL:
		m_next_seen=titol.Update();
		break;
	case GAME:
		m_next_seen = game.Update();
		break;
	case RESULTS:
		m_next_seen = results.Update();
		break;
	case MAPMAKE:
		m_next_seen = map_make.Update();
		break;
	case TUTORIAL:
		m_next_seen = tutorial.Update();
		break;
	default:
		break;
	}
}

void SeenManager::Draw()
{

	switch (m_seen_num)
	{
	case TITOL:
		titol.Draw();
		break;
	case GAME:
		game.Draw();
		break;
	case RESULTS:
		results.Draw();
		break;
	case MAPMAKE:
		map_make.Draw();
		break;
	case TUTORIAL:
		tutorial.Draw();
		break;
	default:
		break;
	}
}

void SeenManager::Exit()
{
	map_make.Exit();
	results.Exit();
}
