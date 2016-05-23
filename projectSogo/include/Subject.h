#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "./Observer.h"

class Subject
{
    public:
        Subject()
        {
            m_observer = new vector<Observer*>();
        }

        ~Subject()
        {
            for(int i= 0; i < this->m_observer->size(); i++)
            {
                delete(this->m_observer->at(i));
            }

            delete(this->m_observer);
        }
        inline void AddListener(Observer *obs)
        {
            m_observer->push_back(obs);
        }

        //remove(Observer) method later


        inline void NotifyAllObserver()
        {
            for(int i= 0; i < this->m_observer->size(); i++)
            {
                this->m_observer->at(i)->Notify();
            }

        }

    protected:
    private:

        vector<Observer*> *m_observer;
};

#endif // SUBJECT_H
