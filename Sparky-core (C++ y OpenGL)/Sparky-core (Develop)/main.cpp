#if 0

#include "src\utils\Timer.h"
#include <time.h>

#include "src\graphics\Window.h"

#include "src\graphics\BatchRenderer2D.h"

#include "src\graphics\Sprite.h"
#include "src\graphics\layers\Group.h"
#include "src\graphics\Texture.h"

#include "src\graphics\Label.h"

#include "TileLayer.h"

int main()
{
	using namespace Sparky;
	using namespace Graphics;
	using namespace Audio;
	using namespace Maths;
	
	Window window("Sparky!", 1280, 720);
	//glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	
	Shader* shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");

	TileLayer layer(shader);
	srand(time(NULL));

	Texture* textures[] =
	{
		new Texture("src/test.png"),
		new Texture("src/testB.png"),
		new Texture("src/testC.png")
	};

	for (float y = -9.0f; y < 9.0f; y++) {
		for (float x = -16.0f; x < 16.0f; x++) {
			layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}

	Group *group = new Group(Maths::Mat4::Translation(Maths::Vec3f(-15.5f, 7.0f, 0.0f)));
	group->add(new Sprite(0.0f, 0.0f, 4.0f, 1.5f, Vec4f(0.2f, 0.2f, 0.2f, 0.9f)));
	Label *fps = new Label("", 0.5f, 0.5f, Vec4f(1, 1, 1, 1));
	group->add(fps);
	layer.add(group);

	shader->enable();
	shader->SetUniformMat4("pr_matrix", Maths::Mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	SoundManager::add(new Sound("Evacuate", "Evacuate.wav"));
	SoundManager::get("Evacuate")->play();

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	float gain = 0.5f;

	while (!window.isClosed())
	{
		window.clear();

		double x, y;
		window.MousePosition(x, y);
		shader->SetUniform2f("light_pos", Vec2f((float)(x * 32.0f / window.GetWidth() - 16.0f), (float)(9.0f - y * 18.0f / window.GetHeight())));
		
		layer.render();

		window.Update();

		if (window.isKeyTyped(GLFW_KEY_P))
			SoundManager::get("Evacuate")->play();
		
		if (window.isKeyTyped(GLFW_KEY_L))
			SoundManager::get("Evacuate")->loop();
		
		if (window.isKeyTyped(GLFW_KEY_S))
			SoundManager::get("Evacuate")->stop();
		
		if (window.isKeyTyped(GLFW_KEY_1))
			SoundManager::get("Evacuate")->pause();
		
		if (window.isKeyTyped(GLFW_KEY_2))
			SoundManager::get("Evacuate")->resume();
		
		if (window.isKeyTyped(GLFW_KEY_UP))
		{
			gain += 0.05f;
			SoundManager::get("Evacuate")->SetGain(gain);
		}
		
		if (window.isKeyTyped(GLFW_KEY_DOWN))
		{
			gain -= 0.05f;
			SoundManager::get("Evacuate")->SetGain(gain);
		}

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d FPS\n", frames);
			fps->text_ = std::to_string(frames) + " fps";
			frames = 0;
		}
	}

	for (auto texture : textures)
		delete texture;
}
#endif