#ifndef GAME_HH
#define GAME_HH

#include "point.hh"
#include "spacecube.hh"
#include "flyingavatar.hh"

#include <vector>
#include <assert.h>
#include <algorithm>
#include <typeinfo>
#include <iostream>

using namespace std;

enum Direction {
    Up, Down, Right, Left, Back, Front, None
};
const map<Direction, Point> DIRECTIONS {
    {Up, Point(1,1,2)},
    {Down, Point(1,1,0)},
    {Left, Point(0,1,1)},
    {Right, Point(2,1,1)},
    {Back, Point(1,0,1)},
    {Front, Point(1,2,1)},
};

class Game
{
public:
    Game(unsigned int width, unsigned int length, unsigned int height);
    ~Game();

    Space getSpace() const;

    SpaceCube* getCubeAt(unsigned int x, unsigned int y, unsigned int z = 0) const;
    SpaceCube* getCubeAt(Point point) const;


    bool moveTo(GameObject* object, SpaceCube* from, SpaceCube* to, bool selfCall = 0);
    bool moveAvatarInDirection(Avatar* avatar, Direction direction);

    bool stateHasChanged();

    template<typename T>
    Avatar* createAvatar(unsigned int x, unsigned int y, unsigned int z);

    pair<Point, bool> find(SpaceCube *spaceCube,
            Point startingLocation = Point(0,0,0),
            unsigned int maxRange = numeric_limits<int>::max()
    );


    bool isWithinBoundaries(int x, int y, int z) const;

    class OutOfBoundsException : public CustomException {
        public:
            OutOfBoundsException(const string& message) : CustomException(message) {}
    };

    class NullObjectException : public CustomException {
        public:
            NullObjectException(const string& message) : CustomException(message) {}
    };

    class MovementException : public CustomException {
        public:
            MovementException(const string& message) : CustomException(message) {}
    };

    class GridSizeError : public CustomException {
        public:
            GridSizeError(const string& message) : CustomException(message) {}
    };

private:
    Space grid_;
    unsigned int width_;
    unsigned int length_;
    unsigned int height_;

    Avatar* hero_;
    Avatar* enemy_;

    bool stateChanged_;

    vector<GameObject*> allGameObjects_;

    void connectGrid();

    Space getAdjacentCubes(unsigned int x, unsigned int y, unsigned int z);

    template<typename T>
    Plane createPlane(unsigned int width, unsigned int length);

    template<typename T>
    Plane createPlane();

    Plane createEmptyPlane(unsigned int width, unsigned int length);

    Plane createEmptyPlane();


    void validateGrid() const;

};

#endif // GAME_HH
