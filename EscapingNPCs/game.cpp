#include "game.hh"
#include "customexception.hh"
#include "grass.hh"


Game::Game(unsigned int width, unsigned int length, unsigned int height) :
    width_(width),
    length_(length),
    height_(height),
    stateChanged_(false)
{

    grid_ = {};
    allGameObjects_ = {};

    // creating terrain
    Plane terrain = createPlane<Grass>();
    grid_.push_back(terrain);

    // creating air
    for (unsigned int z = 1; z < height; z++) {
        Plane air = createEmptyPlane();
        grid_.push_back(air);
    }

    validateGrid();

    connectGrid();

    SpaceCube* heroLocation = getCubeAt(2, length_-1, 1);
    hero_ = new Avatar(heroLocation);
    allGameObjects_.push_back(hero_);

    SpaceCube* enemyLocation = getCubeAt(width_-2, 2, 1);
    enemy_ = new Avatar(enemyLocation);
    allGameObjects_.push_back(enemy_);


}

Game::~Game()
{
    for (Plane& plane : grid_) {
        for (Column& column : plane) {
            for (SpaceCube* cube : column) {
                delete cube;
            }
        }
    }

    for (auto object : allGameObjects_) {
        delete object;
    }
}

Space Game::getSpace() const
{
    return grid_;
}

bool Game::moveTo(GameObject* object, SpaceCube* from, SpaceCube* to, bool selfCall)
{

    if (object == nullptr) {
        throw new NullObjectException("Attempt to move object that does not exist.");
    }

    if (to == nullptr) {
        string message = "Attempt to move " + string(typeid(object).name()) + " to a location";
        throw new MovementException(message);
    }

    if (to->add(object)) {

        if (from == nullptr || from->remove(object)) {
            // set location if avatar
            Avatar* avatar = dynamic_cast<Avatar*>(object);
            if (avatar != nullptr) {
                avatar->setLocation(to);
            }

            // once movement has happened, the state has changed
            stateChanged_ = true;

            return true;

        } else {
            // try to move object back, selfcall is there to avoid a cycle of moving back and fourth
            if (!selfCall) {
                if(!moveTo(object, to, from, true)) {
                    throw new MovementException(
                                "Moving from one to another failed and cannot revert"
                    );
                }
                return false;
            }

            return false;
        }
    }

    return false;
}

bool Game::moveAvatarInDirection(Avatar* avatar, Direction direction)
{
    // ignore if not a flying avatar and the direction is up or down
    if (
            dynamic_cast<FlyingAvatar*>(avatar) == nullptr
            && ( direction == Up || direction == Down )

    ) {
        return false;
    }

    SpaceCube* currentSpot = avatar->getLocation();

    SpaceCube* spot = currentSpot->getNeighbor(
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

bool Game::stateHasChanged()
{
    if (stateChanged_) {
        stateChanged_ = false;
        return true;
    } else {
        return false;
    }
}

Space Game::getAdjacentCubes(unsigned int centerX, unsigned int centerY, unsigned int centerZ)
{
    Space adjacents = {};
    for (int dz = -1; dz <= 1; dz++) {

        Plane plane = {};
        for (int dy = -1; dy <= 1; dy++) {

            Column column = {};
            for (int dx = -1; dx <= 1; dx++) {

                int x = centerX + dx;
                int y = centerY + dy;
                int z = centerZ + dz;

                if (isWithinBoundaries(x,y,z)) {
                    column.push_back(getCubeAt(x,y,z));
                } else {
                    column.push_back(nullptr);
                }
            }
            plane.push_back(column);
        }
        adjacents.push_back(plane);
    }

    return adjacents;
}

void Game::validateGrid() const
{
    if (grid_.size() != height_) {
        throw new GridSizeError("The grid is of the wrong height!");
    }

    for (const Plane& plane : grid_) {
        if (plane.size() != length_) {
            throw new GridSizeError("The grid is of the wrong length!");
        }

        for (const Column& column : plane) {
            if (column.size() != width_) {
                throw new GridSizeError("The grid is of the wrong width!");
            }

        }
    }
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

bool Game::isWithinBoundaries(int x, int y, int z) const {

    if (x >= (int) width_ || y >= (int) length_ || z >= (int) height_) {
        return false;
    }

    if (x < 0 || y < 0 || z < 0) {
        return false;
    }

    return true;
}

SpaceCube* Game::getCubeAt(unsigned int x, unsigned int y, unsigned int z) const
{
    if (!isWithinBoundaries(x, y, z)) {
        throw new OutOfBoundsException("Attempt to access cube outside of boundaries");
    }

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
                throw new MovementException("Not really this type of exception but this will do for now.");
            }
            column.push_back(cube);
        }
        plane.push_back(column);
    }

    return plane;
}

Plane Game::createEmptyPlane(unsigned int width, unsigned int length)
{
    qDebug("createEmptyPlane");
    Plane plane;
    for (unsigned int y = 0; y < length; y++) {
        Column column;
        for (unsigned int x = 0; x < width; x++) {
            SpaceCube* cube = new SpaceCube();
            column.push_back(cube);
        }
        plane.push_back(column);
    }

    qDebug("endof createEmptyPlane");

    return plane;
}

Plane Game::createEmptyPlane()
{
    return createEmptyPlane(width_, length_);
}

template<typename T>
Plane Game::createPlane()
{
    return createPlane<T>(width_, height_);
}
