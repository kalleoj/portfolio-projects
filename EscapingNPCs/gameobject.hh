#ifndef GAMEOBJECT_HH
#define GAMEOBJECT_HH

#include <string>

using namespace std;

class GameObject
{
public:
    GameObject();
    virtual ~GameObject();
    virtual string whatIsThis();

private:

};

#endif // GAMEOBJECT_HH
