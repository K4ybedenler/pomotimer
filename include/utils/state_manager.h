#include "timer.h"

#include <QObject>
#include <QWidget>

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

template <typename Base>
class StateManager : public QObject
{
public:
    explicit StateManager(Base *startState, Timer *timerInst){
        switchToState(startState, timerInst);
    };

    template <typename Target>
    void switchToState(Target *newState, Timer *timerInst)
//    requires std::is_base_of_v<Base, Target>
    {
        if(typeid(*newState) == typeid(Target)) {
            newState->close();
        }

        newState = newState;

        connect(newState, &Base::switchRequest, this, [this, timerInst](Base *newState){
            switchToState(newState, timerInst);
        });
    }

private:
};

#endif

