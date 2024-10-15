#include "stdafx.h"
#include "GameScene.h"
#include "GApp.h"
#include "GDirectionalLight.h"

#include "SmallEnemy.h"
#include "LargeEnemy.h"
#include "Projectile.h"
#include "Explosion.h"

#include "GTextureManager.h"
#include "GModelManager.h"
#include "GMathUtils.h"

GameScene::GameScene() : score(0), enemyCooldown(0), restart(false), restartTime(0.0f) {
	LoadResources();

	text = new Text("Resources/Fonts/H2GTRE.TTF", new Shader("Resources/shaders/text.vs", "Resources/shaders/text.fs"),
		GApp().Instance()->GetWindowWidth(), GApp().Instance()->GetWindowHeight());

	dl = new GDirectionalLight();
	dl->ambient = glm::vec3(0.2f, 0.2f, 0.2f);
	dl->diffuse = glm::vec3(0.6f, 0.7f, 0.7f);
	dl->specular = glm::vec3(0.8f, 0.9f, 0.9f);
	AddObject(dl);
	this->dirLights[0] = dl;

	/*sl = new GSpotLight();
	sl->ambient = glm::vec3(0.2f, 0.2f, 0.0f);
	sl->diffuse = glm::vec3(0.7f, 0.0f, 0.0f);
	sl->specular = glm::vec3(1.0f, 0.0f, 0.0f);

	sl->cutOff = glm::cos(glm::radians(15.0f));
	sl->outerCutOff = glm::cos(glm::radians(20.0f));

	sl->transform.position.z = -3;
	sl->transform.position.y = 0.5;
	sl->transform.rotation.y = -180.0f;
	AddObject(sl);
	dl->AddChild(sl);
	this->spotLights[0] = sl;*/

	background = new GTexturedMesh();
	background->transform.position.z = -20.0f;
	background->AddVertices(
		{ {-10, -10, 0}, {10, -10, 0}, {10, 10, 0}, {-10, 10, 0} },
		{ {0, 0, 1}, {0, 0, 1}, {0, 0, 1}, {0, 0, 1} },
		{ {0, 0}, {12, 0}, {12, 12}, {12, 0} }
	);
	background->transform.scale = glm::vec3(30.0f);
	background->AddIndices({ 0,1,2, 0,2,3 });
	background->path = "Resources/ui/background.png";
	AddObject(background);

	player = new Player();
	AddObject(player);
	this->mainCamera = player->camera;

	enemies = new GObject();
	AddObject(enemies);

	projectiles = new GObject();
	AddObject(projectiles);

	explosions = new GObject();
	AddObject(explosions);

	glfwSetKeyCallback(GApp().Instance()->Window(), KeyCallback);
	glfwSetMouseButtonCallback(GApp::Instance()->Window(), MouseButtonCallback);
	glfwSetCursorPosCallback(GApp::Instance()->Window(), CursorPositionCallback);
}

void GameScene::Update(float deltaTime) {
	GScene::Update(deltaTime);
	//dl->transform.rotation.y += 60.0f * deltaTime;
	//model1->transform.rotation.z -= 600.0f * deltaTime;
	//camera->transform.position.z -= 5.0f * deltaTime;
	//model->transform.scale += glm::vec3(+0.4f * deltaTime);
	player->transform.position = glm::clamp(player->transform.position,
		glm::vec3(-140, -140, 0), glm::vec3(140, 140, 0));

	if (player->state != Player::DEAD) {
		enemyCooldown -= deltaTime;

		if (enemyCooldown <= 0.0f) {
			enemyCooldown += 1.5f;
			float randomAngle = MathUtil::RandomRange(0.0f, 2.0f * glm::pi<float>());
			if (spotLights[0] != nullptr || MathUtil::RandomRange(0.0f, 1.0f) < 0.9f) {
				SmallEnemy *enemy = new SmallEnemy();
				enemy->transform.position = player->WorldPos();
				enemy->transform.position.x += 30.0f * glm::cos(randomAngle);
				enemy->transform.position.y += 30.0f * glm::sin(randomAngle);
				enemies->AddChild(enemy);
			} else {
				LargeEnemy *enemy = new LargeEnemy();
				enemy->transform.position = player->WorldPos();
				enemy->transform.position.x += 30.0f * glm::cos(randomAngle);
				enemy->transform.position.y += 30.0f * glm::sin(randomAngle);
				enemies->AddChild(enemy);
				spotLights[0] = enemy->spotLight;
			}
		}
	}

	if (restart && (restartTime += deltaTime) >= 1.0f) {
		GApp::Instance()->SetScene(new GameScene());
	}
}

void GameScene::Render() {

	GScene::Render();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	background->Render();
	
	enemies->Render();
	player->Render();

	projectiles->Render();
	explosions->Render();

	glEnable(GL_STENCIL_TEST);
	glStencilFunc(GL_ALWAYS, 1, 0xff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	glStencilMask(0xff);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	int centerX = GApp::Instance()->GetWindowWidth() / 2;
	int centerY = GApp::Instance()->GetWindowHeight() / 2;

	float cdRatio = 1.0f - player->rushCooldown / player->rushMaxCool;
	for (int i = 0; i < 4; ++i) {
		if (cdRatio - 0.25f * i < 0) break;
		float beginAngle = (-i+1) * 0.5f * glm::pi<float>();
		float endAngle = beginAngle - glm::min(1.0f, ((cdRatio - 0.25f * i) / 0.25f)) * 0.5f * glm::pi<float>();
		canvas.Draw("Resources/ui/dummy.png",
			{
				{centerX, centerY},
				{centerX + glm::cos(endAngle) * 300, centerY + glm::sin(endAngle) * 300},
				{centerX + glm::cos(beginAngle) * 300, centerY + glm::sin(beginAngle) * 300},
			},
			{
				{0, 0}, {0, 0}, {0, 0}
			});
	}

	glStencilFunc(GL_EQUAL, 1, 0xff);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glEnable(GL_DEPTH_TEST);

	canvas.Draw("Resources/ui/Cooldown.png", centerX - 75, centerY - 75, 150, 150);

	glDisable(GL_STENCIL_TEST);
	glClear(GL_STENCIL_BUFFER_BIT);
	
	text->RenderText("Score:" + std::to_string(score), 25, 25, 1.0f, glm::vec3(0.9f, 0.9f, 0.9f));
}

void GameScene::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	GameScene* scene = dynamic_cast<GameScene*>(GApp::Instance()->Scene());
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		scene->player->moveVec.y += 1.0f;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		scene->player->moveVec.y -= 1.0f;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		scene->player->moveVec.x -= 1.0f;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		scene->player->moveVec.x += 1.0f;
	}
	if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		scene->player->moveVec.y -= 1.0f;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		scene->player->moveVec.y += 1.0f;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		scene->player->moveVec.x += 1.0f;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		scene->player->moveVec.x -= 1.0f;
	}

	if (scene->player->state == Player::DEAD && action == GLFW_PRESS) {
		scene->restart = true;
	}
	if (scene->player->state == Player::DEAD && action == GLFW_RELEASE) {
		scene->restart = false;
		scene->restartTime = 0.0f;
	}
}

void GameScene::MouseButtonCallback(GLFWwindow* window, int button, int action, int mode) {
	auto app = GApp::Instance();
	GameScene* scene = dynamic_cast<GameScene*>(app->Scene());

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
		double mouseX;
		double mouseY;
		glfwGetCursorPos(GApp::Instance()->Window(), &mouseX, &mouseY);

		float windowWidth = static_cast<float>(app->GetWindowWidth());
		float windowHeight = static_cast<float>(app->GetWindowHeight());

		mouseX = mouseX / (windowWidth  * 0.5f) - 1.0f;
		mouseY = 1.0f - mouseY / (windowHeight * 0.5f);

		glm::vec2 dir = glm::vec2(mouseX, mouseY);
		scene->player->BeginRush(dir);
	}
}

void GameScene::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos) {
	GameScene* scene = dynamic_cast<GameScene*>(GApp::Instance()->Scene());

}

void GameScene::LoadResources() {
	auto texMgr = GTextureManager::Instance();
	auto modelMgr = GModelManager::Instance();

	texMgr->Load("Resources/ui/dummy.png");
	texMgr->Load("Resources/ui/background.png", GL_REPEAT);
	texMgr->Load("Resources/ui/Cooldown.png");
	texMgr->Load("Resources/ui/explosion.png");
	texMgr->Load("Resources/ui/projectile.png");

	modelMgr->Load("Resources/models/spaceship/Intergalactic_Spaceship-(Wavefront).obj");
	modelMgr->Load("Resources/models/smallenemy/Luminaris OBJ.obj");
	modelMgr->Load("Resources/models/largeenemy/MK6_OBJ.obj");
}