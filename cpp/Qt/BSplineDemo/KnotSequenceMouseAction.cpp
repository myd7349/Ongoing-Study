#include "KnotSequenceMouseAction.h"

#include "../../DesignPatterns/Singleton.hpp"
#include "knotsequence.h"


bool KnotSequenceMouseAction::mouseDoubleClickEvent(QObject *sender, QMouseEvent *event)
{
    Q_UNUSED(sender);

    Q_ASSERT(event != nullptr);

    auto &sequence = Singleton<KnotSequence>::GetInstance();

    if (event->button() == Qt::LeftButton)
    {
        sequence.push_back(event->pos());
        return true;
    }
    else if (event->button() == Qt::RightButton)
    {
        if (sequence.empty())
            return false;

        sequence.pop_back();
        return true;
    }
    else if (event->button() == Qt::MidButton)
    {
        if (sequence.empty())
            return false;

        sequence.clear();
        return true;
    }
    else
    {
        return false;
    }
}
