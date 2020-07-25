#include <iostream>
#include <vector>

class IObserver
{
public:
   virtual void update() = 0;
};


class IObservable
{
public:
   virtual void takeObservers(std::vector<IObserver *> obss) = 0;

   virtual int takeMeasurement() = 0;

   virtual void pushNotif() = 0;
};

class Observable : public IObservable
{
   std::vector<IObserver *> observers;
   int temp_measured = 0;
public:
   // Observable(std::vector<IObserver> obss):observers(std::move(obss)){};
   void takeObservers(std::vector<IObserver *> obss) override
   {
      observers = obss;
   }

   int takeMeasurement() override;

   void pushNotif() override
   {
      for (auto o : observers)
      {
         o->update();
      }
   }
};

int Observable::takeMeasurement()
{
   return ++temp_measured;
}

class Observer : public IObserver
{
   Observable *observable;

public:
   int temp;

   Observer(Observable *obss, int t) : observable(obss), temp(t)
   {};

   void update() override
   {
      temp = observable->takeMeasurement();
   }
};

int main()
{
   Observable theObservable;
   Observer observer1(&theObservable,0);
   Observer observer2(&theObservable,0);
   Observer observer3(&theObservable,0);
   std::vector<IObserver *> obss = {&observer1, &observer2, &observer3};
   theObservable.takeObservers(obss);
   theObservable.pushNotif();
   std::cout << observer1.temp << " " << observer2.temp << " " << observer3.temp;
   return 0;
}
