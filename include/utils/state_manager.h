#include "timer.h"

#include <QObject>
#include <QWidget>

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

template <typename Base>
class StateManager : public QObject
{
public:
    explicit StateManager(Base *startState, Timer *timerInst,
                          QObject *parent = nullptr)
    : QObject(parent)
    {
        switchToState(startState, timerInst);
    };

    template <typename Target>
    void switchToState(Target *newState, Timer *timerInst)
//    requires std::is_base_of_v<Base, Target>
    {
        if(obj && typeid(*newState) != typeid(*obj)) {
            disconnect(obj, &Base::switchRequest, this, nullptr);
            obj->deleteLater();
            obj=nullptr;
        }

        obj = newState;

        connect(
            newState, &Base::switchRequest, this,
            [this, timerInst](Base *newState){
                switchToState(newState, timerInst);
            });
    }

private:
    Base *obj = nullptr;
};

#endif

