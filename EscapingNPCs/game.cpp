#include "game.hh"


Game::Game(unsigned int width, unsigned int length, unsigned int height) :
    width_(width),
    length_(length),
    height_(height)
{
    grid_ = {};
    allGameObjects_ = {};

    // creating terrain
    Plane terrain = createPlane<SolidGameObject>();
    grid_.push_back(terrain);

    // creating air
    for (unsigned int z = 1; z < height; z++) {
        Plane air = createPlane<GameObject>();
        grid_.push_back(air);
    }

    connectGrid();


    hero_ = new Avatar();
    hero_->setSurroundings(getAdjacentCubes(2, length-2, 0));
    allGameObjects_.push_back(hero_);

    enemy_ = new Avatar();
    enemy_->setSurroundings(getAdjacentCubes(2, length-2, 0));
    allGameObjects_.push_back(enemy_);

}

Game::~Game()
{
    for (Plane plane : grid_) {
        for (Column column : plane) {
            for (SpaceCube* cube : column) {
                delete cube;
            }
        }
    }

    for (auto object : allGameObjects_) {
        delete object;
    }
}

bool Game::moveTo(GameObject* object, SpaceCube* from, SpaceCube* to, bool selfCall)
{
    assert (object != nullptr && from != nullptr && to != nullptr);

    if (to->add(object)) {

        if (from->remove(object)) {

            // reset surroundings
            Avatar* avatar = dynamic_cast<Avatar*>(object);
            if (avatar != nullptr) {
                avatar->setSurroundings(to->getNeighbors());
            }

            return true;

        } else {

            // if not function calling itself, try to move object back
            if (!selfCall) {
                if(!moveTo(object, to, from, true)) {
                    throw new MovementErrorException(
                                "Moving from one to another failed and cannot revert"
                    );
                }
                return false;
            }
            int maxSelfCalls = 3;
            if (selfCall < maxSelfCalls) {
            }
            return false;
        }
    }

    return false;
}

bool Game::moveAvatarInDirection(Avatar* avatar, Direction direction)
{
    SpaceCube* currentSpot = avatar->getCurrentSpaceCube();

    SpaceCube* spot = avatar->getNeighboringSpaceCube(
              DIRECTIONS.at(direction)
    );

    if (spot == nullptr) {
        return false;
    }

    if (moveTo(avatar, currentSpot, spot)) {
        return true;
    }

    return false;

}


pair<Point, bool> Game::find(SpaceCube* otherCube, Point startingLocation, unsigned int maxRange)
{
    assert(otherCube != nullptr);

    if (getCubeAt(startingLocation) == otherCube) {
        return {startingLocation, true};
    }

    unsigned int searchRange = 1;

    while (searchRange <= maxRange) {
        for (int z : {startingLocation.getZ()-searchRange, startingLocation.getZ()+searchRange}) {
            if (z < 0 || z > (int) height_) {
                continue;
            }

            for (int y : {startingLocation.getY()-searchRange, startingLocation.getY()+searchRange}) {
                if (y < 0 || y > (int) length_) {
                    continue;
                }

                for (int x : {startingLocation.getX()-searchRange, startingLocation.getX()+searchRange}) {
                    if (x < 0 || x > (int) width_) {
                        continue;
                    }

                    if (getCubeAt(x,y,z) == otherCube) {
                        return {Point(x,y,z), true};
                    }
                }
            }
        }

        searchRange += 1;
    }

    return {Point(), false};
}

Space Game::getAdjacentCubes(unsigned int centerX, unsigned int centerY, unsigned int centerZ)
{
    Space adjacents;
    for (int dz = -1; dz <= 1; dz++) {

        Plane plane;
        for (int dy = -1; dy <= 1; dy++) {

            Column column;
            for (int dx = -1; dx <= 1; dx++) {

                int x = centerX + dx;
                int y = centerY + dy;
                int z = centerZ + dz;

                if (
                    (x < 0 || y < 0 || z < 0) ||
                    (x > (int) width_ || y > (int) length_ || z > (int) height_)
                )
                {
                    column.push_back(nullptr);
                } else {
                    column.push_back(grid_.at(z).at(y).at(x));
                }
            }
            plane.push_back(column);
        }
        adjacents.push_back(plane);
    }

    return adjacents;
}

void Game::connectGrid()
{
    for (unsigned int z = 0; z < height_; z++) {
        for (unsigned int y = 0; y < length_; y++) {
            for(unsigned int x = 0; x < width_; x++) {
                SpaceCube* cube = getCubeAt(x,y,z);
                cube->setNeighbors(
                    getAdjacentCubes(x,y,z)
                );
            }
        }
    }
}

SpaceCube* Game::getCubeAt(unsigned int x, unsigned int y, unsigned int z) const
{
    return grid_.at(z).at(y).at(x);
}

SpaceCube* Game::getCubeAt(Point point) const
{
    return getCubeAt(point.getX(), point.getY(), point.getZ());
}

template<typename T>
Plane Game::createPlane(unsigned int width, unsigned int length)
{
    Plane plane;
    for (unsigned int y = 0; y < length; y++) {
        Column column;
        for (unsigned int x = 0; x < width; x++) {
            SpaceCube* cube = new SpaceCube();
            T* gameObject = new T();

            allGameObjects_.push_back(gameObject);
            if (!cube->add(gameObject)) {
                throw new MovementErrorException("Not really this type of exception but this will do for now.");
            }
            column.push_back(cube);
        }
        plane.push_back(column);
    }

    return plane;
}

template<typename T>
Plane Game::createPlane()
{
    return createPlane<T>(width_, height_);
}
