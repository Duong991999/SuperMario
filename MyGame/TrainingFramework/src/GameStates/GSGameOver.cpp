#include "GSGameOver.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


extern int screenHeight;
extern int screenWidth;
extern int ySpeed;
extern int score;
extern int highScore[];



GSGameOver::GSGameOver()
{
}

GSGameOver::~GSGameOver()
{
	HighScore();

}

void GSGameOver::Init()
{


	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_1");

	m_background = std::make_shared<Sprite2D>(model, shader, texture);
	m_background->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_background->SetSize(screenWidth, screenHeight);

	//button menu
	texture = ResourceManagers::GetInstance()->GetTexture("home_button");
	std::shared_ptr<GameButton> m_button = std::make_shared<GameButton>(model, shader, texture);
	m_button->Set2DPosition(150, 200);
	m_button->SetSize(200, 200);
	m_button->SetOnClick([]()
	{

		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(m_button);

	//button replay
	texture = ResourceManagers::GetInstance()->GetTexture("replay_button");
	m_button = std::make_shared<GameButton>(model, shader, texture);
	m_button->SetSize(200, 200);
	m_button->Set2DPosition(550,200);
	m_button->SetOnClick([]()
	{
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->PopState();
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
	});
	m_listButton.push_back(m_button);



	auto shader7 = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader7, font, "Your score is " + std::to_string(score), TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(250, 100));


}

void GSGameOver::HighScore()
{
	for (int i = 0; i < 3; i++)
	{
		if (score >= highScore[i])
		{
			int t = highScore[i];
			highScore[i] = score;
			score = t;
		}
	}

	fstream f;                      // (2)
	f.open("highscore.txt", ios::out); // (2)

	for (int i = 0; i < 3; i++)
	{

		f << highScore[i] << endl;
	}                        // (3)

	f.close();
}

void GSGameOver::Exit()
{
}

void GSGameOver::Pause()
{
}

void GSGameOver::Resume()
{
}

void GSGameOver::HandleEvents()
{
}

void GSGameOver::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSGameOver::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSGameOver::Update(float deltaTime)
{
	m_score->setText("Your score is " + std::to_string(score));
	/*Vector2 pos = m_animation->Get2DPosition();
	m_animation->Set2DPosition(pos.x, pos.y + ySpeed * deltaTime);*/

	/*m_animation->Update(deltaTime);*/

//	m_background->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
//	m_text->Update(deltaTime);
	m_score->Update(deltaTime);
}

void GSGameOver::Draw()
{
	m_background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
//	m_text->Draw();
    m_score->Draw();
	//m_animation->Draw();
}
