#ifndef TREE_NODE_HPP_
#define TREE_NODE_HPP_

#ifndef TREE_NODE_HPP_
#define TREE_NODE_HPP_

#include <algorithm>
#include <cassert>
#include <deque>
#include <memory>
#include <numeric>
#include <string>

struct TreeNode;

typedef std::shared_ptr<TreeNode> TreeNodePtr;
typedef std::deque<TreeNodePtr>   NodePtrList;


struct TreeNode : public std::enable_shared_from_this<TreeNode>
{
    static TreeNodePtr Create(const std::wstring &text, bool collapsed = false)
    {
        return std::make_shared<TreeNode>(text, collapsed);
    }

    explicit TreeNode(const std::wstring &text, bool collapsed = false)
        : level_(0), collapsed_(collapsed), index_(-1), item_(-1), text_(text)
    {
    }

    int GetItem() const
    {
        return item_;
    }

    void SetItem(int item)
    {
        item_ = item;
    }

    bool IsVisible() const
    {
        if (!parent_)
            return true;

        if (parent_->IsCollapsed())
            return false;

        return parent_->IsVisible();
    }

    bool IsCollapsed() const
    {
        return collapsed_;
    }

    bool IsExpanded() const
    {
        return !collapsed_;
    }

    const std::wstring &GetText() const
    {
        return text_;
    }

    std::wstring GetParentPath() const
    {
        if (parent_)
            return parent_->GetParentPath() + parent_->GetText();
        else
            return L"";
    }

    std::wstring GetFullPath() const
    {
        return GetParentPath() + GetText();
    }

    const std::wstring &SetText(const std::wstring &text)
    {
        return text_ = text;
    }

    TreeNodePtr GetParent() const
    {
        return parent_;
    }

    const NodePtrList &GetChildren() const
    {
        return children_;
    }

    NodePtrList &GetChildren()
    {
        return children_;
    }

    int AddNode(TreeNodePtr node, int index = -1)
    {
        bool preCondition = node && node.get() != this && !node->IsAncestorOf(shared_from_this());
        assert(preCondition);
        if (!preCondition)
            return -1;

        assert(!node->GetParent() && node->index_ == -1);
        node->parent_ = shared_from_this();

        if (index < 0 || index >= static_cast<int>(children_.size()))
        {
            children_.push_back(node);
            node->index_ = static_cast<int>(children_.size()) - 1;
            return node->index_;
        }
        else
        {
            NodePtrList::iterator pos = children_.begin();
            std::advance(pos, index);
            children_.insert(pos, node);
            node->index_ = index;
            return index;
        }
    }

    void RemoveNode(TreeNodePtr node)
    {
        bool preCondition = node && node.get() != this;
        assert(preCondition);
        if (!preCondition)
            return;

        NodePtrList::iterator it = std::find(children_.begin(), children_.end(), node);
        if (it != children_.end())
        {
            TreeNodePtr child = *it;
            assert(child->parent_.get() == this);
            assert(child->index_ >= 0 && child->index_ < GetChildrenCount());
            child->parent_ = nullptr;
            child->index_ = -1;
            children_.erase(it);
        }
    }

    int GetLevel() const
    {
        return parent_ ? parent_->GetLevel() + 1 : 0;
    }

    bool IsDescendantOf(TreeNodePtr node)
    {
        if (!node)
            return false;

        return node->IsAncestorOf(shared_from_this());
    }

    bool IsAncestorOf(TreeNodePtr node)
    {
        if (!node)
            return false;

        for (NodePtrList::const_iterator it = children_.cbegin();
            it != children_.cend();
            ++it)
        {
            TreeNodePtr child = *it;
            if (child == node || child->IsAncestorOf(node))
                return true;
        }

        return false;
    }

    int GetChildrenCount() const
    {
        return static_cast<int>(children_.size());
    }

    int GetNodeCount(bool recursively = false) const
    {
        int count = GetChildrenCount();

        if (recursively)
        {
            count = std::accumulate(children_.cbegin(), children_.cend(), count,
                [recursively](int init, TreeNodePtr node) { return init + node->GetNodeCount(recursively); }
            );
        }

        return count;
    }

    TreeNodePtr GetPrevNode()
    {
        assert((parent_ == nullptr && index_ == -1)
            || (parent_ != nullptr && index_ >= 0 && index_ < parent_->GetChildrenCount()));
        if (parent_ && index_ > 0)
            return parent_->children_[index_ - 1];

        return nullptr;
    }

    TreeNodePtr GetPrevVisibleNode()
    {
        TreeNodePtr prevNode = GetPrevNode();
        while (prevNode && !prevNode->IsVisible())
            prevNode = prevNode->GetPrevNode();

        return prevNode;
    }

    TreeNodePtr GetNextNode()
    {
        assert((parent_ == nullptr && index_ == -1)
            || (parent_ != nullptr && index_ >= 0 && index_ < parent_->GetChildrenCount()));
        if (parent_ && index_ < parent_->GetChildrenCount() - 1)
            return parent_->children_[index_ + 1];

        return nullptr;
    }

    TreeNodePtr GetNextVisibleNode()
    {
        TreeNodePtr nextNode = GetNextNode();
        if (nextNode)
        {
            if (nextNode->IsVisible())
                return nextNode;

            return nextNode->GetNextVisibleNode();
        }
        else
        {
            return nullptr;
        }
    }

    void Collapse()
    {
        collapsed_ = true;
    }

    void Expand()
    {
        collapsed_ = false;
    }

private:
    int level_;
    bool collapsed_;
    int index_;
    int item_;
    std::wstring text_;
    TreeNodePtr parent_;
    NodePtrList children_;
};

#endif // TREE_NODE_HPP_

// References:
// System.Windows.Forms.TreeNode
// https://stackoverflow.com/questions/31924396/why-shared-from-this-cant-be-used-in-constructor-from-technical-standpoint
