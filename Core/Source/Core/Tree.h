#pragma once

#include <vector>
#include <queue>
#include <stack>
#include <unordered_set>
#include <string>
#include <sstream>

namespace STL
{
    enum class SerializeMode
    {
        All,
        Value
    };

    template <typename T>
    class TreeNode
    {
    private:
        T m_Value;                              // �ڵ�ֵ
        uint32_t m_Level;                       // �㼶
        TreeNode<T>* m_Parent;                  // ���ڵ�
        std::vector<TreeNode<T>*> m_Children;   // �ӽڵ��б�
    public:
        TreeNode(T value) : m_Value(value), m_Level(0), m_Parent(nullptr) {}

        TreeNode(const TreeNode&) = delete;
        TreeNode& operator=(const TreeNode&) = delete;

        ~TreeNode()
        {
            // �ͷ��ӽڵ��ڴ�
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
        /// �����ӽڵ�
        /// </summary>
        /// <param name="index">index</param>
        /// <returns>�ӽڵ�</returns>
        TreeNode<T>* GetChild(size_t index) const
        {
            if (index >= 0 && index < GetChildCount()) {
                return m_Children[index];
            }
            return nullptr;
        }

        /// <summary>
        /// ����ӽڵ�
        /// </summary>
        /// <param name="child">����ӽڵ�</param>
        bool AddChild(TreeNode<T>* child)
        {
            if (child != nullptr) {
                child->SetParent(this);                                 // �����ӽڵ�ĸ��ڵ�Ϊ��ǰ�ڵ�
                child->SetLevel(child->GetParent()->GetLevel() + 1);    // ���ýڵ�㼶
                m_Children.push_back(child);                            // ��ӵ��ӽڵ��б�

                return true;
            }

            return false;
        }

        /// <summary>
        /// ɾ���ӽڵ�
        /// </summary>
        /// <param name="child">��ɾ���ӽڵ�</param>
        bool RemoveChild(TreeNode<T>* child)
        {
            if (child != nullptr) {
                auto it = std::find(m_Children.begin(), m_Children.end(), child);
                if (it != m_Children.end()) {
                    m_Children.erase(it);
                    child = nullptr;

                    return true;
                }
            }

            return false;
        }

        /// <summary>
        /// ɾ����ǰ�ڵ�
        /// </summary>
        void Remove()
        {
            // �ͷ��ӽڵ��ڴ�
            for (TreeNode<T>* child : m_Children) {
                delete child;
            }

            m_Parent->RemoveChild(this);   // �Ӹ��ڵ�����б�ɾ���ýڵ�
        }

        /// <summary>
        /// �����ӽڵ� index
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

        std::string ToString(SerializeMode mode = SerializeMode::Value) const
        {
            std::stringstream ss;
            ss << m_Value;
            
            if (mode == SerializeMode::All) {
                ss << "[" << GetLevel() << "]" << "(" << GetIndex() << ")";
            }

            return ss.str();
        }
    };

    template <typename T>
    class Tree
    {
    private:
        TreeNode<T>* m_Root;

        /// <summary>
        /// ������ȱ���
        /// </summary>
        /// <param name="VisitNode">�ڵ���ʷ���</param>
        template <typename VisitFunc>
        void BFS(VisitFunc VisitNode)
        {
            if (!m_Root) return;

            std::queue<TreeNode<T>*> q; // ���д洢�ڵ�Ͳ㼶
            q.push(m_Root);             // ��ʼ�����У����ڵ�

            while (!q.empty()) {
                TreeNode<T>* node = q.front();
                uint32_t level = node->GetLevel();
                q.pop();

                VisitNode(node);    // ���ʽڵ�

                // ���ӽڵ�������
                for (TreeNode<T>* child : node->GetChildren()) {
                    q.push(child);
                }
            }
        }

        /// <summary>
        /// ������ȱ���
        /// </summary>
        /// <param name="VisitNode">�ڵ���ʷ���</param>
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

                VisitNode(node);    // ���ʽڵ�

                // ����
                for (int i = node->GetChildCount() - 1; i >= 0; --i) {
                    // δ���ʹ��Ľڵ���ջ
                    if (visited.find(node->GetChild(i)) == visited.end()) {
                        stk.push(node->GetChild(i));
                        visited.insert(node->GetChild(i));
                    }
                }
            }
        }
    public:
        Tree(TreeNode<T>* root) : m_Root(root) {}
        Tree(T value) : m_Root(new TreeNode<T>(value)) {}

        TreeNode<T>* GetRoot() const { return m_Root; }

        void SetRoot(TreeNode<T>* root)
        {
            m_Root = root;
            m_Root->SetLevel(0);
            m_Root->SetParent(nullptr);

            // �޸Ľڵ�㼶
            BFS([&](TreeNode<T>* node)
            {
                if (node != m_Root) {
                    node->SetLevel(node->GetParent()->GetLevel() + 1);    // ���ýڵ�㼶
                }
            });
        }

        void Clear() { m_Root = nullptr; }

        /// <summary>
        /// ����Ŀ��ڵ�
        /// </summary>
        /// <param name="target">Ŀ��ڵ�</param>
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
        /// ����ӽڵ㵽��ǰ�ڵ�
        /// </summary>
        /// <param name="current">��ǰ�ڵ�</param>
        /// <param name="node">����ӽڵ�</param>
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

        /// <summary>
        /// ����ӽڵ㵽��ǰ�ڵ�
        /// </summary>
        /// <param name="current">��ǰ�ڵ�</param>
        /// <param name="value">����ӽڵ�ֵ</param>
        /// <returns></returns>
        bool AddNode(TreeNode<T>* current, T value)
        {
            if (FindNode(current)) {
                current->AddChild(new TreeNode<T>(value));
                return true;
            }

            return false;
        }

        /// <summary>
        /// ɾ�����
        /// </summary>
        /// <param name="node">��ɾ�����</param>
        /// <returns></returns>
        bool RemoveNode(TreeNode<T>* node)
        {
            if (!node) return false;

            if (FindNode(node)) {
                node->Remove();
                node = nullptr;

                return true;
            }

            return false;
        }

        std::string ToString(SerializeMode mode = SerializeMode::Value)
        {
            std::stringstream ss;

            if (!m_Root) return "";

            DFS([&](TreeNode<T>* node)
            {
                uint32_t level = node->GetLevel();

                // �����ʾ�㼶
                for (uint32_t i = 0; i < level; i++) {
                    ss << "  ";
                }
                ss << node->ToString(mode) << "\n";    // ����ڵ�  
            });

            return ss.str();
        }
    };
}