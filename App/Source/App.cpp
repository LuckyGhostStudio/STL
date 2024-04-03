#include <Core.h>
#include <Tree.h>

#include <iostream>

int main()
{
    STL::Tree<std::string> tree = STL::Tree<std::string>(new STL::TreeNode<std::string>("Root"));

    tree.AddNode(tree.GetRoot(), new STL::TreeNode<std::string>("Node"));
    tree.AddNode(tree.GetRoot(), new STL::TreeNode<std::string>("Node"));
    tree.AddNode(tree.GetRoot(), new STL::TreeNode<std::string>("Node"));

    tree.AddNode(tree.GetRoot()->GetChild(0), new STL::TreeNode<std::string>("Node"));
    tree.AddNode(tree.GetRoot()->GetChild(0), new STL::TreeNode<std::string>("Node"));
    tree.AddNode(tree.GetRoot()->GetChild(0), new STL::TreeNode<std::string>("Node"));
    tree.AddNode(tree.GetRoot()->GetChild(0)->GetChild(0), new STL::TreeNode<std::string>("Node"));
    tree.AddNode(tree.GetRoot()->GetChild(0), new STL::TreeNode<std::string>("Node"));
    tree.AddNode(tree.GetRoot()->GetChild(1), new STL::TreeNode<std::string>("Node"));
    tree.AddNode(tree.GetRoot()->GetChild(1), new STL::TreeNode<std::string>("Node"));
    tree.AddNode(tree.GetRoot()->GetChild(1), new STL::TreeNode<std::string>("Node"));
    tree.AddNode(tree.GetRoot()->GetChild(2), new STL::TreeNode<std::string>("Node"));
    tree.AddNode(tree.GetRoot()->GetChild(2), new STL::TreeNode<std::string>("Node"));

    std::cout << tree.ToString() << std::endl;

    tree.SetRoot(tree.GetRoot()->GetChild(0));
    std::cout << tree.ToString() << std::endl;
    
    tree.Clear();
    std::cout << tree.ToString() << std::endl;

    return 0;
}