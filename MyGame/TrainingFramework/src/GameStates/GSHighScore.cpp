#include "GSHighScore.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine


extern int screenHeight;
extern int screenWidth;
extern int ySpeed;
extern int highScore[];



GSHighScore::GSHighScore()
{
}

GSHighScore::~GSHighScore()
{
}

void GSHighScore::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture("background_1");

    background = std::make_shared<Sprite2D>(model, shader, texture);
	background->Set2DPosition(screenWidth / 2, screenHeight / 2);
	background->SetSize(screenWidth, screenHeight);


	texture = ResourceManagers::GetInstance()->GetTexture("back_button");
	std::shared_ptr<GameButton> m_button = std::make_shared<GameButton>(model, shader, texture);
	m_button->Set2DPosition(350, 25);
	m_button->SetOnClick([]()
	{
		GameStateMachine::GetInstance()->PopState();
	});
	m_listButton.push_back(m_button);
	auto shader7 = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");

	m_text = std::make_shared<Text>(shader7, font, "High score", TEXT_COLOR::RED, 2.0);
	m_text->Set2DPosition(Vector2(120, 100));

	m_text1 = std::make_shared<Text>(shader7, font, "Score " + std::to_string(highScore[0]), TEXT_COLOR::RED, 1);
	m_text1->Set2DPosition(Vector2(180, 150));

	m_text2 = std::make_shared<Text>(shader7, font, "Score " + std::to_string(highScore[1]), TEXT_COLOR::RED, 1);
	m_text2->Set2DPosition(Vector2(180, 180));

	m_text3 = std::make_shared<Text>(shader7, font, "Score " + std::to_string(highScore[2]), TEXT_COLOR::RED, 1);
	m_text3->Set2DPosition(Vector2(180, 210));


}

void GSHighScore::Exit()
{
}

void GSHighScore::Pause()
{
}

void GSHighScore::Resume()
{
}

void GSHighScore::HandleEvents()
{
}

void GSHighScore::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSHighScore::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSHighScore::Update(float deltaTime)
{

	for (auto it : m_background)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	m_text->Update(deltaTime);
	m_text1->Update(deltaTime);
	m_text2->Update(deltaTime);
	m_text3->Update(deltaTime);
}

void GSHighScore::Draw()
{
	background->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	m_text->Draw();
	m_text1->Draw();
	m_text2->Draw();
	m_text3->Draw();

}