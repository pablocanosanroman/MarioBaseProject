#include "GameScreenVictory.h"

GameScreenVictory::GameScreenVictory(SDL_Renderer* renderer) : GameScreen(renderer)
{
	SetUpVictoryScreen();
}

GameScreenVictory::~GameScreenVictory()
{
	delete m_background_texture;

	m_background_texture = nullptr;

	delete m_victory_text;
}

bool GameScreenVictory::SetUpVictoryScreen()
{
	//Variables for the text
	victory_text_x = (SCREEN_WIDTH / 4) + 25;
	victory_text_y = (SCREEN_HEIGHT / 2) - 20;
	restart_text_x = (SCREEN_WIDTH / 4) - 15;
	restart_text_y = (SCREEN_HEIGHT / 2) + 20;
	text_width = 0;
	text_height = 0;
	font_size_victory = 25;
	font_size_restart = 20;
	text_color = { 255, 255, 255 };

	//Font Path
	font_path = "Fonts/MarioFont.ttf";

	//Game over message
	game_over_message = "You WON!";
	restart_message = "Press Y to restart";

	//Initialize Text boxes
	m_victory_text = new TextManager(m_renderer, font_size_victory, font_path, game_over_message, text_color);
	m_restart_text = new TextManager(m_renderer, font_size_restart, font_path, restart_message, text_color);

	//load background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/black.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
}

void GameScreenVictory::Render()
{

	m_background_texture->Render(Vector2D(-3, 0), SDL_FLIP_NONE);
	m_victory_text->Render(victory_text_x, victory_text_y, m_renderer);
	m_restart_text->Render(restart_text_x, restart_text_y, m_renderer);
}

void GameScreenVictory::Update(float deltaTime, SDL_Event e)
{

}
