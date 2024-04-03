#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <string>
#include <sstream>

namespace STL
{
    template <typename T>
    class TreeNode
    {
    private:
        T m_Value;                              // 节点值
        uint32_t m_Level;                       // 层级
        TreeNode<T>* m_Parent;                  // 父节点
        std::vector<TreeNode<T>*> m_Children;   // 子节点列表
    public:
        TreeNode(T value) : m_Value(value), m_Level(0), m_Parent(nullptr) {}

        TreeNode(const TreeNode&) = delete;
        TreeNode& operator=(const TreeNode&) = delete;

        ~TreeNode()
        {
            // 释放子节点内存  
            for (TreeNode<T>* child : m_Children){
                delete child;
            }
        }

        T GetValue() const { return m_Value; }
        void SetValue(T value) { m_Value = value; }

        uint32_t GetLevel() const { return m_Level; }
        void SetLevel(uint32_t level) { m_Level = level; }

        TreeNode<T>* GetParent() const { return m_Parent; }
        void SetParent(TreeNode<T>* parent) { m_Parent = parent; }

        bool IsLeaf() const { return m_Children.empty(); }

        const std::vector<TreeNode<T>*>& GetChildren() const { return m_Children; }
        uint32_t GetChildCount() const { return m_Children.size(); }
        
        /// <summary>
        /// 返回子节点
        /// </summary>
        /// <param name="index">index</param>
        /// <returns>子节点</returns>
        TreeNode<T>* GetChild(size_t index) const
        {
            if (index >= 0 && index < GetChildCount()) {
                return m_Children[index];
            }
            return nullptr;
        }

        /// <summary>
        /// 添加子节点
        /// </summary>
        /// <param name="child">待添加节点</param>
        void AddChild(TreeNode<T>* child)
        {
            if (child != nullptr) {
                child->SetParent(this);                                 // 设置子节点的父节点为当前节点
                child->SetLevel(child->GetParent()->GetLevel() + 1);    // 设置节点层级
                m_Children.push_back(child);                            // 添加到子节点列表
            }
        }

        /// <summary>
        /// 返回子节点 index
        /// </summary>
        /// <returns></returns>
        uint32_t GetIndex() const
        {
            if (!m_Parent) return 0;

            for (uint32_t i = 0; i < m_Parent->GetChildCount(); i++) {
                if (this == m_Parent->GetChild(i)) {
                    return i;
                }
            }

            return 0;
        }

        std::string ToString() const
        {
            std::stringstream ss;
            ss <<  m_Value << "[" << GetLevel() << "]" << "(" << GetIndex() << ")";
            return ss.str();
        }
    };

    template <typename T>
    class Tree
    {
    private:
        TreeNode<T>* m_Root;

        /// <summary>
        /// 广度优先遍历
        /// </summary>
        /// <param name="VisitNode">节点访问方法</param>
        template <typename VisitFunc>
        void BFS(VisitFunc VisitNode)
        {
            if (!m_Root) return;

            std::queue<TreeNode<T>*> q; // 队列存储节点和层级
            q.push(m_Root);             // 初始化队列，根节点

            while (!q.empty()) {
                TreeNode<T>* node = q.front();
                uint32_t level = node->GetLevel();
                q.pop();

                VisitNode(node);    // 访问节点

                // 将子节点加入队列
                for (TreeNode<T>* child : node->GetChildren()) {
                    q.push(child);
                }
            }
        }

        /// <summary>
        /// 深度优先遍历
        /// </summary>
        /// <param name="VisitNode">节点访问方法</param>
        template <typename VisitFunc>
        void DFS(VisitFunc VisitNode)
        {
            if (!m_Root) return;

            std::unordered_set<TreeNode<T>*> visited;
            std::stack<TreeNode<T>*> stk;
            stk.push(m_Root);

            while (!stk.empty()) {
                TreeNode<T>* node = stk.top();
                stk.pop();

                VisitNode(node);    // 访问节点

                // 将未访问过的子节点入栈  
                for (TreeNode<T>* child : node->GetChildren()) {
                    if (visited.find(child) == visited.end()) {
                        stk.push(child);
                        visited.insert(child);
                    }
                }
            }
        }
    public:
        Tree(TreeNode<T>* root) : m_Root(root) {}

        TreeNode<T>* GetRoot() const { return m_Root; }
        void SetRoot(TreeNode<T>* root)
        {
            m_Root = root;
            m_Root->SetLevel(0);
            m_Root->SetParent(nullptr);

            // 修改节点层级
            BFS([&](TreeNode<T>* node)
            {
                if (node != m_Root) {
                    node->SetLevel(node->GetParent()->GetLevel() + 1);    // 设置节点层级
                }
            });
        }

        void Clear() { m_Root = nullptr; }

        /// <summary>
        /// 查找目标节点
        /// </summary>
        /// <param name="target">目标节点</param>
        /// <returns></returns>
        bool FindNode(TreeNode<T>* target)
        {
            if (!target) return false;

            bool found = false;

            BFS([&](TreeNode<T>* node)
            {
                if (node == target) {
                    found = true;
                }
            });

            return found;
        }

        /// <summary>
        /// 添加子节点到当前节点
        /// </summary>
        /// <param name="current">当前节点</param>
        /// <param name="node">待添加节点</param>
        /// <returns></returns>
        bool AddNode(TreeNode<T>* current, TreeNode<T>* node)
        {
            if (!node) return false;

            if (FindNode(current)) {
                current->AddChild(node);
                return true;
            }

            return false;
        }

        std::string ToString()
        {
            std::stringstream ss;

            if (!m_Root) return "";

            DFS([&](TreeNode<T>* node)
            {
                uint32_t level = node->GetLevel();

                // 输出表示层级
                for (uint32_t i = 0; i < level; i++) {
                    ss << "  ";
                }
                ss << node->ToString() << "\n";    // 输出节点  
            });

            return ss.str();
        }
    };
}