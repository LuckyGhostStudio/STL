#include <Core.h>
#include <iostream>

void TreeTest()
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

void VectorTest()
{
    STL::List<int> arr = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90 };

    std::cout << "Size: " << arr.GetSize() << std::endl;
    std::cout << "Capacity: " << arr.GetCapacity() << std::endl;
    std::cout << arr.ToString() << std::endl;

    arr.Add(520);
    std::cout << arr.ToString() << std::endl;

    arr[3] = 1314;
    std::cout << arr.ToString() << std::endl;

    arr.RemoveAt(1);
    std::cout << arr.ToString() << std::endl;

    arr[arr.Find(1314)] = 90;
    std::cout << arr.ToString() << std::endl;

    arr.RemoveLast();

    std::cout << "Size: " << arr.GetSize() << std::endl;
    std::cout << "Capacity: " << arr.GetCapacity() << std::endl;

    std::cout << arr[111] << std::endl;
}

int main()
{
    try {
        VectorTest();
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}