#include <Sparky.h>

using namespace Sparky;
using namespace Graphics;
using namespace Maths;

class Game : public SparkyClass {
private:
	Window* window;
	Layer* layer;
	Sprite* sprite;
	Shader* shader;
	Label* fps;
public:
	Game()
	{
		
	}

	~Game()
	{
		delete layer;
	}

	void init() override
	{
		window = createWindow("Prueba", 1280, 720);
		FontManager::get()->SetScale(window->GetWidth() / 32.0f, window->GetHeight() / 18.0f);

#ifdef SPARKY_EMSCRIPTEN
		shader = new Shader("res/shaders/basic.es3.vert", "res/shaders/basic.es3.frag");
#else
		shader = new Shader("shaders/basic.vert", "shaders/basic.frag");
#endif
		layer = new Layer(new BatchRenderer2D(), shader, Mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

#ifdef SPARKY_EMSCRIPTEN
		sprite = new Sprite(0.0f, 0.0f, 4.0f, 4.0f, new Texture("Tex", "res/testD.png"));
#else
		sprite = new Sprite(0.0f, 0.0f, 4.0f, 4.0f, new Texture("Tex", "res/testD.png"));
#endif
		fps = new Label("", -15.5f, 8.0f, Vec4f(1, 1, 1, 1));
		layer->add(sprite);

#ifdef SPARKY_EMSCRIPTEN
		sprite = new Sprite(-15.0f, 0.0f, 4.0f, 4.0f, new Texture("Tex", "res/testB.png"));
#else
		sprite = new Sprite(-15.0f, 0.0f, 4.0f, 4.0f, new Texture("Tex", "res/testB.png"));
#endif
		layer->add(sprite);
		layer->add(fps);

		Audio::SoundManager::add(new Audio::Sound("Test", "res/Evacuate.wav"))->play();
	}

	void tick() override
	{
		fps->text_ = std::to_string(getFPS()) + " fps";
		SPARKY_INFO("FPS: ", getFPS(), " UPS:", getUPS());
	}

	void render() override
	{
		Vec2f mouse = window->GetMousePosition();
		shader->enable();
		shader->SetUniform2f("light_pos", Vec2f((float)(mouse.x * 32.0f / window->GetWidth() - 16.0f), (float)(9.0f - mouse.y * 18.0f / window->GetHeight())));

		layer->render();
	}

	void update() override
	{
		float speed = 0.5f;

		if (window->isKeyPressed(GLFW_KEY_UP))
			sprite->Position_.y += speed;
		else if (window->isKeyPressed(GLFW_KEY_DOWN))
			sprite->Position_.y -= speed;
		if (window->isKeyPressed(GLFW_KEY_LEFT))
			sprite->Position_.x -= speed;
		else if (window->isKeyPressed(GLFW_KEY_RIGHT))
			sprite->Position_.x += speed;
	}
};

int main()
{
	Game game;
	game.start();

	return 0;
}