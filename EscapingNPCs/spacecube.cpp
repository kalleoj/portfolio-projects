#include "spacecube.hh"

SpaceCube::SpaceCube()
{

}


bool SpaceCube::add(GameObject* object) {
    // check if there is a solid gameobject in the space
    for (auto occupant : occupants_) {
        if (typeid(occupant) == typeid(SolidGameObject)) {
            return false;
        }
    }

    occupants_.push_back(object);
    return true;
}

bool SpaceCube::remove(GameObject* object) {
    unsigned int oldSize = occupants_.size();

    occupants_.erase(
        std::remove(occupants_.begin(), occupants_.end(), object),
        occupants_.end()
    );

    if (occupants_.size() == oldSize) {
        return false;
    }

    return true;
}

vector<GameObject *> SpaceCube::getOccupants() const
{
    return occupants_;
}

bool SpaceCube::setOccupants(vector<GameObject *> newOccupants)
{
    vector<GameObject*> oldOccupants = occupants_;

    occupants_ = {};
    for (GameObject* occupant : newOccupants) {
        if(!add(occupant)) {

            // if add is unsuccessful, revert to old occupants
            occupants_ = oldOccupants;
            return false;
        }
    }

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
