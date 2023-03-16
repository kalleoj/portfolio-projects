#include "spacecube.hh"


SpaceCube::SpaceCube() : occupants_({}), neighbors_({})
{

}


bool SpaceCube::add(GameObject* object) {
    qDebug() << "add";

    // check if there is a solid gameobject in the space
    for (auto occupant : occupants_) {
        if (dynamic_cast<SolidGameObject*>(occupant) != nullptr) {
            qDebug() << "endof add";

            return false;
        }
    }

    occupants_.insert(object);

    qDebug() << "endof add";
    return true;
}

bool SpaceCube::remove(GameObject* object) {
    qDebug() << "remove";

    unsigned int oldSize = occupants_.size();

    occupants_.erase(object);

    if (occupants_.size() == oldSize) {
        qDebug() << "endof remove";
        return false;
    }

    qDebug() << "endof remove";
    return true;
}

set<GameObject *> SpaceCube::getOccupants() const
{
    qDebug() << "getOccupants";
    qDebug() << "endof getOccupants";

    return occupants_;
}

bool SpaceCube::setOccupants(set<GameObject *> newOccupants)
{
    qDebug() << "setOccupants";
    set<GameObject*> oldOccupants = occupants_;

    occupants_ = {};
    for (auto occupant : newOccupants) {
        if(!add(occupant)) {

            // if add is unsuccessful, revert to old occupants
            occupants_ = oldOccupants;
            qDebug() << "endof setOccupants";
            return false;
        }
    }

    qDebug() << "endof setOccupants";
    return true;

}

Space SpaceCube::getNeighbors() const
{
    return neighbors_;
}

bool SpaceCube::validNeighborSpace(Space space) {
    if (space.size() != NEIGHBOR_SPACE_DIMENSION) {
        return false;
    } else if (space.at(0).size() != NEIGHBOR_SPACE_DIMENSION) {
        return false;
    } else if (space.at(0).at(0).size() != NEIGHBOR_SPACE_DIMENSION) {
        return false;
    }

    return true;
}

void SpaceCube::setNeighbors(Space newNeighbors)
{
    if (!validNeighborSpace(newNeighbors)) {
        throw new InvalidSpaceException("Neighbor space dimensions are not correct");
    }

    neighbors_ = newNeighbors;
}

SpaceCube* SpaceCube::getNeighbor(Point point) const
{
    int x = point.getX();
    int y = point.getY();
    int z = point.getZ();

    if (
            x > MAX_NEIGHBOR_INDEX ||
            y > MAX_NEIGHBOR_INDEX ||
            z > MAX_NEIGHBOR_INDEX ||
            x < 0 ||
            y < 0 ||
            z < 0
    )
    {
        throw new OutOfBoundsException("Tried to index neighbor that is out of range");
    }

    return neighbors_.at(z).at(y).at(x);

}
