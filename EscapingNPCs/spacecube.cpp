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

bool SpaceCube::setNeighbors(Space newNeighbors)
{
    neighbors_ = newNeighbors;
}
