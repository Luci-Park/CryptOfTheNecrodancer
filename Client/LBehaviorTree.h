#pragma once
#include "CommonInclude.h"
#include <iostream>
namespace cl
{
    // Node class representing a generic node in the behavior tree
    class Node {
    public:
        virtual bool Run() = 0;
    };

    // Action node representing a behavior to perform
    class Action : public Node {
    public:
        Action(std::function<bool()> actionFunc);

        bool Run() override;

    private:
        std::function<bool()> action;
    };

    // Selector node representing a choice between multiple behaviors
    class Selector : public Node {
    public:
        virtual ~Selector();
        void AddChild(Node* child);

        bool Run() override;

    private:
        std::vector<Node*> children;
    };

    // Sequence node representing a series of behaviors to perform
    class Sequence : public Node {
    public:
        virtual ~Sequence();
        void AddChild(Node* child) {
            children.push_back(child);
        }

        bool Run() override;

    private:
        std::vector<Node*> children;
    };
    class Conditional : public Node {
    public:
        Conditional(std::function<bool()> condition, Node* child);
        virtual ~Conditional();

        bool Run() override;

    private:
        std::function<bool()> condition;
        Node* child;
    };
}


