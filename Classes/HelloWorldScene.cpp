#include "HelloWorldScene.h"
#include "CCImGui/ImGuiManager.h"
#include "CCImGui/ImGuiLayer.h"
#include "CCImGui/imgui/imgui_impl_glfw.h"

USING_NS_CC;

static bool show_test_window = true;
static bool show_another_window = false;
static ImVec4 clear_color = ImColor(114, 144, 154);

Scene* HelloWorldScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = HelloWorldScene::create();

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorldScene::init()
{
	//////////////////////////////
	// 1. super init first
	if ( !Scene::init() )
	{
		return false;
	}

	auto director = Director::getInstance();
	auto size = director->getWinSize();

	auto rootNode = Sprite::create("HelloWorld.png");
	rootNode->setPosition(size.width/2, size.height/2);
	addChild(rootNode);

	// Check if the touches or the mouse input are touching the background
	//auto listener = EventListenerTouchOneByOne::create();
	//listener->onTouchBegan = [](Touch* touch, Event*) -> bool {
	//	CCLOG("touch bg node");
	//	return true;
	//};
	//Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, rootNode);

	// Create the IMGUI windows here. This is the main IMGUI Loop where you can
	// keep adding callbacks to be added:
	ImGuiManager::getInstance()->addImGuiCallback(
		std::move(
			[]() -> void
			{
				// 1. Show a simple window
				// Tip: if we don't call ImGui::Begin()/ImGui::End() the widgets appears in a window automatically called "Debug"
				{
					static float f = 0.0f;
					ImGui::Text("Hello, world!");
					ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
					ImGui::ColorEdit3("clear color", (float*)&clear_color);
					if (ImGui::Button("Test Window")) show_test_window ^= 1;
					if (ImGui::Button("Another Window")) show_another_window ^= 1;
					ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				}

				// 2. Show another simple window, this time using an explicit Begin/End pair
				if (show_another_window)
				{
					ImGui::SetNextWindowSize(ImVec2(200,100), ImGuiSetCond_FirstUseEver);
					ImGui::Begin("Another Window", &show_another_window);

					ImGui::Text("Hello");
					ImGui::End();
				}

				// 3. Show the ImGui test window. Most of the sample code is in ImGui::ShowTestWindow()
				if (show_test_window)
				{
					ImGui::SetNextWindowPos(ImVec2(650, 20), ImGuiSetCond_FirstUseEver);
					ImGui::ShowTestWindow(&show_test_window);
				}
			}
	), "demoid");

	//// Create the IMGUI cocos2d-x Layer to draw ImGui, and add it as child.
	auto imgui = ImGuiLayer::create();
	this->addChild(imgui, INT_MAX,   "ImGUILayer");

	return true;
}
