#include <Core.h>

#include <iostream>
#include <graphics.h>
#include <conio.h>

#include "UI/UIManager.h"
#include "UI/Text.h"

void TreeText()
{
    STL::Tree<std::string> scene = STL::Tree<std::string>("Scene");

    scene.AddNode(scene.GetRoot(), "Main Camera");
    scene.AddNode(scene.GetRoot(), "Light");
    scene.AddNode(scene.GetRoot(), "Player");
    scene.AddNode(scene.GetRoot(), "Enemy");
    scene.AddNode(scene.GetRoot(), "Environment");

    scene.AddNode(scene.GetRoot()->GetChild(2), "Body");
    scene.AddNode(scene.GetRoot()->GetChild(2)->GetChild(0), "Mesh");
    scene.AddNode(scene.GetRoot()->GetChild(2)->GetChild(0), "Collider");
    scene.AddNode(scene.GetRoot()->GetChild(2), "Weapon");
    scene.AddNode(scene.GetRoot()->GetChild(2)->GetChild(1), "Muzzle");

    scene.AddNode(scene.GetRoot()->GetChild(3), "Body");
    scene.AddNode(scene.GetRoot()->GetChild(3)->GetChild(0), "Mesh");
    scene.AddNode(scene.GetRoot()->GetChild(3)->GetChild(0), "Collider");

    scene.AddNode(scene.GetRoot()->GetChild(4), "Background");
    scene.AddNode(scene.GetRoot()->GetChild(4), "Plantform");
    scene.AddNode(scene.GetRoot()->GetChild(4), "Foreground");
    scene.AddNode(scene.GetRoot()->GetChild(4)->GetChild(0), "Tree");
    scene.AddNode(scene.GetRoot()->GetChild(4)->GetChild(0), "Tree");
    scene.AddNode(scene.GetRoot()->GetChild(4)->GetChild(1), "Water");
    scene.AddNode(scene.GetRoot()->GetChild(4)->GetChild(1), "Door");

    std::cout << scene.ToString() << std::endl;

    scene.RemoveNode(scene.GetRoot()->GetChild(4));

    std::cout << scene.ToString() << std::endl;

    scene.Clear();
    std::cout << scene.ToString() << std::endl;
}

int main()
{
    initgraph(1024, 640);

    BeginBatchDraw();

    UI::UIManager& uiManager = UI::UIManager::GetInstance();    // UI Manager

    UI::Text* normal = new UI::Text();
    UI::Text* bold = new UI::Text(Vector2(0, 100), Vector2(100, 50), "Text", "Consolas", UI::FontStyle::Bold, 30, { UI::TextFormat::Left, UI::TextFormat::Top });
    UI::Text* bold1 = new UI::Text(Vector2(0, 200), Vector2(100, 50), "Text", "Consolas", UI::FontStyle::Italic, 30, { UI::TextFormat::Right, UI::TextFormat::Bottom });

    uiManager.AddUIElement(normal);
    uiManager.AddUIElement(bold);
    uiManager.AddUIElement(bold1);

    while (true) {
        // 处理用户输入事件
        //UI::Event event = GetNextEvent(); // 假设有获取事件的函数
        //uiManager.HandleInput(event);

        cleardevice();

        uiManager.RenderUI();

        FlushBatchDraw();
    }

    EndBatchDraw();
    closegraph();

    return 0;
}