// 2017-04-26T19:41:20+08:00
#include <cassert>
#include <iostream>
#include <string>

#include "../../common.h"
#include "../Composite.hpp"

class Leaf : public Composite
{
public:
    Leaf(const char *text)
    {
        assert(text != nullptr);
        text_ = text;
    }

    Leaf(const std::string &text)
        : Leaf(text.c_str())
    {
    }

    Leaf(int id)
        : Leaf(std::to_string(id))
    {
    }

    std::string GetText() const { return text_; }

private:
    std::string text_;
};

int main()
{
    // BFS test
    {
        Leaf root(1);
            auto leaf2 = std::make_shared<Leaf>(2);
            root.Add(leaf2);
                auto leaf5 = std::make_shared<Leaf>(5);
                leaf2->Add(leaf5);
                    leaf5->Add(std::make_shared<Leaf>(9));
                    leaf5->Add(std::make_shared<Leaf>(10));
                leaf2->Add(std::make_shared<Leaf>(6));
            root.Add(std::make_shared<Leaf>(3));
            auto leaf4 = std::make_shared<Leaf>(4);
            root.Add(leaf4);
                auto leaf7 = std::make_shared<Leaf>(7);
                    leaf7->Add(std::make_shared<Leaf>(11));
                    leaf7->Add(std::make_shared<Leaf>(12));
                leaf4->Add(leaf7);
                leaf4->Add(std::make_shared<Leaf>(8));

        auto iterator = root.CreateIterator(BFS);
        for (iterator->First(); !iterator->IsDone(); iterator->MoveNext())
        {
            Leaf *leaf = dynamic_cast<Leaf *>(iterator->Current().get());
            std::cout << leaf->GetText() << " ";
        }
        std::cout << std::endl;
    }

    // DFS test
    {

    }

    PAUSE();
    return 0;
}