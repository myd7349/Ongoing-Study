#ifndef MOUSE_ACTION_BASE_HPP
#define MOUSE_ACTION_BASE_HPP

#include <functional>

#include <QtCore/QList>
#include <QtCore/QSharedPointer>
#include <QtGui/QMouseEvent>


class MouseActionBase
{
public:
    virtual bool mousePressEvent(QObject *sender, QMouseEvent *event)
    {
        Q_UNUSED(sender);
        Q_UNUSED(event);
        return false;
    }

    virtual bool mouseDoubleClickEvent(QObject *sender, QMouseEvent *event)
    {
        Q_UNUSED(sender);
        Q_UNUSED(event);
        return false;
    }

    virtual bool mouseReleaseEvent(QObject *sender, QMouseEvent *event)
    {
        Q_UNUSED(sender);
        Q_UNUSED(event);
        return false;
    }

    virtual bool mouseMoveEvent(QObject *sender, QMouseEvent *event)
    {
        Q_UNUSED(sender);
        Q_UNUSED(event);
        return false;
    }
};

using MouseActionSafePtr = QSharedPointer<MouseActionBase>;

class MouseActionList
{
public:
    void pushBack(MouseActionSafePtr action)
    {
        if (action)
            mouseActionList.push_back(action);
    }

    void popBack()
    {
        if (!mouseActionList.empty())
            mouseActionList.pop_back();
    }

    void pushFront(MouseActionSafePtr action)
    {
        if (action)
            mouseActionList.push_front(action);
    }

    void popFront()
    {
        if (!mouseActionList.empty())
            mouseActionList.pop_front();
    }

    bool mousePressEvent(QObject *sender, QMouseEvent *event)
    {
        return dispatchMouseEvent(sender, event,
            std::mem_fn(&MouseActionBase::mousePressEvent));
    }

    bool mouseDoubleClickEvent(QObject *sender, QMouseEvent *event)
    {
        return dispatchMouseEvent(sender, event,
            std::mem_fn(&MouseActionBase::mouseDoubleClickEvent));
    }

    bool mouseReleaseEvent(QObject *sender, QMouseEvent *event)
    {
        return dispatchMouseEvent(sender, event,
            std::mem_fn(&MouseActionBase::mouseReleaseEvent));
    }

    bool mouseMoveEvent(QObject *sender, QMouseEvent *event)
    {
        return dispatchMouseEvent(sender, event,
            std::mem_fn(&MouseActionBase::mouseMoveEvent));
    }

private:
    bool dispatchMouseEvent(QObject *sender, QMouseEvent *event,
        std::function<bool(MouseActionBase &, QObject *, QMouseEvent *)> responder)
    {
        Q_ASSERT(static_cast<bool>(responder));

        MouseActionSafePtr action;
        bool update = false;

        foreach (action, mouseActionList) {
            Q_ASSERT(action != nullptr);

            if (responder(*action, sender, event))
                update = true;
        }

        return update;
    }

    QList<MouseActionSafePtr> mouseActionList;
};

#endif
