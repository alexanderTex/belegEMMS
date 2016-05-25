#ifndef SUBJECT_H
#define SUBJECT_H

#include <vector>
#include "./IObserver.h"

class Subject
{
    public:
        Subject()
        {
            m_observer = new vector<IObserver*>();
        }

        ~Subject()
        {
            for(int i= 0; i < this->m_observer->size(); i++)
            {
                delete(this->m_observer->at(i));
            }

            delete(this->m_observer);
        }
        inline void AddListener(IObserver *obs)
        {
            m_observer->push_back(obs);
        }

        //remove(Observer) method later

    protected:
        virtual inline void NotifyAllObserver()
        {
            for(int i= 0; i < this->m_observer->size(); i++)
            {
                this->m_observer->at(i)->Notify();
            }

        }


    private:

        vector<IObserver*> *m_observer;
};

#endif // SUBJECT_H
