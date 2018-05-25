#include <iostream>

#include "../tree_node.hpp"

const int Indent = 2;


std::basic_ostream<wchar_t> &operator<<(std::basic_ostream<wchar_t> &out, const TreeNode &node)
{
    if (node.GetParent())
    {
        const std::wstring &parentPath = node.GetParentPath();
        if (parentPath.length() > 1)
            out << std::wstring(parentPath.length() / 2, L' ');
        
        out << std::wstring(node.GetParent()->GetLevel() * Indent, L' ');
        out << L'|' << std::wstring(node.GetLevel() * Indent, L'-');
    }

    out << node.GetText() << std::endl;

    for (NodePtrList::const_iterator it = node.GetChildren().cbegin();
        it != node.GetChildren().cend();
        ++it)
        out << **it;

    return out;
}


int main()
{
    TreeNodePtr c = TreeNode::Create(L"C:\\");
    TreeNodePtr windows = TreeNode::Create(L"Windows\\");
    TreeNodePtr system32 = TreeNode::Create(L"System32\\");
    TreeNodePtr systemWoW64 = TreeNode::Create(L"SystemWoW64\\");
    TreeNodePtr programFiles = TreeNode::Create(L"Program Files\\");
    TreeNodePtr programFilesX86 = TreeNode::Create(L"Program Files (x86)\\");

    windows->AddNode(system32);
    windows->AddNode(systemWoW64);
    c->AddNode(windows);
    c->AddNode(programFiles);
    c->AddNode(programFilesX86);

    std::wcout << *c;

    return 0;
}
