// RPG-控制台版.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "GameMgr.h"
#include "ConfigMgr.h"

/*
10.9进度: 完成了和敌人战斗,背包,装备功能.
TODO: 宠物, 升级, 金币.
10.12进度: 完成宠物,金币,升级,技能.
TODO: 任务系统
10.15进度：完成任务系统。战斗界面玩家和敌人都能发动物理攻击和魔法攻击。并且都会移动。
TODO: 战斗胜利的奖励。
10.16: 完成战斗胜利奖励。修复了->会“消失”(m_nindex没有及时复原)的bug。
TODO: 加一个能个花钱一招消灭敌人的大招。加入一个能够花钱逃跑的技能。
10.17: 完成氪金技能。
TODO：买卖物品。装备升级。
装备升级：加入一个铸剑师的npc，管理装备的升级锻造。
10.19：完成买卖系统

10.26:TODO 敌人的移动。可以加一个int变量代表方向：0-上，1-下，2-左，3-右。
这样可以根据出生点和方向加移动步数达到完美的不相撞的自动移动。
*/

int _tmain(int argc, _TCHAR* argv[])
{
	system("mode con: cols=119 lines=35");	// 修改控制台的宽度为120，高度为20
	CGameMgr* pGameMgr = CGameMgr::getInstance();
	while (true)
	{
		
		pGameMgr->update();
		pGameMgr->render();
		system("cls");
	}
	CGameMgr::destroy();
	CConfigMgr::destroy();
	return 0;
}

