#ifndef SPACECUBE_HH
#define SPACECUBE_HH

#include "customexception.hh"
#include "point.hh"
#include "solidgameobject.hh"

#include <vector>
#include <algorithm>
#include <typeindex>
#include <set>
#include <qDebug>


using namespace std;

class SpaceCube;

using Space = vector<vector<vector<SpaceCube*>>>;
using Plane = vector<vector<SpaceCube*>>;
using Column = vector<SpaceCube*>;

const unsigned int NEIGHBOR_SPACE_DIMENSION = 3;
const int MAX_NEIGHBOR_INDEX = NEIGHBOR_SPACE_DIMENSION - 1;

class SpaceCube
{
public:
    SpaceCube();

    bool add(GameObject* object);
    bool remove(GameObject* object);

    set<GameObject *> getOccupants() const;
    bool setOccupants(set<GameObject *> newOccupants);

    Space getNeighbors() const;
    void setNeighbors(Space newNeighbors);

    SpaceCube* getNeighbor(Point point) const;

    class OutOfBoundsException : public CustomException {
        public:
            OutOfBoundsException(const string& message) : CustomException(message) {}
    };

    class InvalidSpaceException : public CustomException {
        public:
            InvalidSpaceException(const string& message) : CustomException(message) {}
    };

protected:
    set<GameObject*> occupants_;
    Space neighbors_;


private:
    bool validNeighborSpace(Space space);
};

#endif // SPACECUBE_HH
