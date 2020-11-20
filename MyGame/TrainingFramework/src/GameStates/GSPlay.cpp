#include "GSPlay.h"
#include "Player.h"
#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"
#include "Player.h"
#include "enemy.h"
#include "gold.h"
#include "SkyGround.h"
#include"tree.h"


extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int xSpeed;
extern int ySpeed;
extern int score;
//extern int vantoc;
GSPlay::GSPlay()
{
	time = 0;
	TIME = 0;
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	xSpeed = 0;
	score = 0;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_1");
	auto texture1 = ResourceManagers::GetInstance()->GetTexture("background_2");



	//auto texture2 = ResourceManagers::GetInstance()->GetTexture("ground");
	//auto shader2 = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//m_Ground = std::make_shared<SkyGround>(model, shader2, texture2, 1000, 300, 200, 20);


	//auto texture3 = ResourceManagers::GetInstance()->GetTexture("tree1");
	//auto shader3 = ResourceManagers::GetInstance()->GetShader("TextureShader");
	//tree1 = std::make_shared<tree>(model, shader3, texture3, 1500, 300, 100, 100);

	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	BackGround_1 = std::make_shared<Sprite2D>(model, shader, texture);
	BackGround_2 = std::make_shared<Sprite2D>(model, shader, texture1);
	BackGround_1->SetSize(screenWidth, screenHeight);
	BackGround_2->SetSize(screenWidth, screenHeight);

	//text game title
	auto shader7 = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader7, font, "score: " + std::to_string(score), TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));


	texture = ResourceManagers::GetInstance()->GetTexture("back_button");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(400, 25);
	button->SetSize(200, 50);
	button->SetOnClick([]()
	{
		//PlaySounds("menu", true);
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(button);
	//button





	///////

	SetMap(model, shader);
	SetGold(model, shader);
	SetGround(model, shader);
	//SetEnemy(model);
	//Creat a new player
	m_Player = std::make_shared<Player>(model, shader, texture);


}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{
	m_Player->CheckGround();

	m_Player->CheckSkyLeftGround();

	for (auto item1 : m_listTree) {


		m_Player->CheckTree(item1);
		if (!m_Player->CheckAlive()) break;

	}
	for (auto item2 : m_listGround) {

		m_Player->CheckSkyGround(item2);
	}

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	m_Player->HandleKeyEvents(key, bIsPressed);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPlay::Update(float deltaTime)
{
	if (m_Player->CheckAlive()) {

		m_score->setText("score " + std::to_string(score));
		time += deltaTime;
		TIME += deltaTime;
		if (TIME > 100000) {
			auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
			auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
			SetMap(model, shader);
			SetGold(model, shader);
			SetGround(model, shader);
			TIME = 0;
		}
		if (vantoc * time > screenWidth) time = 0;
		BackGround_1->Set2DPosition(screenWidth / 2 - vantoc * time, screenHeight / 2);
		BackGround_2->Set2DPosition(3 * screenWidth / 2 - vantoc * time, screenHeight / 2);
		m_Player->Update(deltaTime);
		for (auto gr : m_listTree)
		{
			gr->Update(deltaTime);
		}
		for (auto Co : m_listGold)
		{
			Co->Update(deltaTime);
		}
		for (auto en : m_listEnemy)
		{
			en->Update(deltaTime);
		}
		for (auto en1 : m_listGround)
		{
			en1->Update(deltaTime);
		}



		HandleEvents();
		m_score->Update(deltaTime);
		for (auto it : m_listButton)
		{

			it->Update(deltaTime);
		}
	}
	else {


		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Finish);

	}

}


void GSPlay::Draw()
{
	BackGround_1->Draw();
	BackGround_2->Draw();


	m_Player->GetAnimation()->Draw();
	m_score->Draw();
	for (auto gr : m_listTree)
	{
		gr->Draw();
	}
	for (auto co : m_listGold)
	{

		m_Player->CheckGold(co);
		if (co->CheckAlive()) {
			co->Draw();
		}
	}
	for (auto en : m_listEnemy)
	{
		en->GetAnimation()->Draw();
	}
	for (auto gr1 : m_listGround)
	{
		gr1->Draw();
	}
	for (auto obj : m_listButton)
	{


		obj->Draw();

	}

}
void GSPlay::SetMap(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader)
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("tree1");
	std::shared_ptr<tree> m_Tree = std::make_shared<tree>(model, shader, texture, 1500, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 1800, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 3023, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 4800, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 5800, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 6600, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 7700, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 7700, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 9900, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 11234, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 12222, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 13131, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 14141, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 15151, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 16121, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 17892, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 119001, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 20010, 300, 100, 100);
	m_listTree.push_back(m_Tree);
	m_Tree = std::make_shared<tree>(model, shader, texture, 22111, 300, 100, 100);
	m_listTree.push_back(m_Tree);


}
void GSPlay::SetGround(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader)
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("ground");


	std::shared_ptr<SkyGround> m_Ground = std::make_shared<SkyGround>(model, shader, texture, 3000, 230, 150, 20);
	m_listGround.push_back(m_Ground);

	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 3500, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 4000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 5000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 6000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 7000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 8000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 9000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 10000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 10500, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 11000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 12000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 13000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 14000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 15000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 16000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 17000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 18000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 19000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 20000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 21000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 22000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 23000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 24000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 24500, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 25000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 25600, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 27000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 27700, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 28300, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 29000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 29700, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 28500, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 29000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 30100, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 30800, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 31400, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 32000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 33000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 34000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 35000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 36000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 37000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 38000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 39000, 230, 150, 20);
	m_listGround.push_back(m_Ground);
	m_Ground = std::make_shared<SkyGround>(model, shader, texture, 40000, 230, 150, 20);
	m_listGround.push_back(m_Ground);



}

void GSPlay::SetGold(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader)
{
	auto texture = ResourceManagers::GetInstance()->GetTexture("gold");
	std::shared_ptr<gold> m_Coin = std::make_shared<gold>(model, shader, texture, 800, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 800, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 900, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 988, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 1022, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 1500, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 1700, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 2003, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 2300, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 2500, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 2672, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 2888, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 3011, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 3300, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 4000, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 4150, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 5000, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 6033, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 6666, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 7077, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 8111, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 9088, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 11231, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 12211, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 13000, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 14021, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 15123, 300, 20, 20);
	m_listGold.push_back(m_Coin);
	m_Coin = std::make_shared<gold>(model, shader, texture, 16212, 300, 20, 20);
	m_listGold.push_back(m_Coin);
}



void GSPlay::SetNewPostionForBullet()
{
}