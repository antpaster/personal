#include "route.h"
#include <map>
#include <random>
#include <ctime>

const double cSqMinDist = 0.000001;
const double cAxisShift = 10.0;
const double cSceneSide = 500.0;
const double cPointDiam = 10.0;
//const size_t cPointsOnRoute = 50;
const size_t cSpeedsWindowSize = 10;
const size_t cPointsBetween = 4;
const size_t cRoutesCount = 10;

std::default_random_engine gen;
std::uniform_real_distribution<double> speedDistr(2.0, 5.0);
std::uniform_real_distribution<double> coordDistr(-1.0, 1.0);

Route::Route(QGraphicsScene * parent)
{
    _mainWidget = parent;
    _roads = new std::set<Road>;
    _prevRoads = new std::vector<Road>;
    _currRoads = new std::vector<Road>;
    _prevPoints = new std::vector<Point2d>;
    _currPoints = new std::vector<Point2d>;
    _coordsIndexes = new std::vector<size_t>;
    _coordsEndIndexes = new std::vector<size_t>;
    _speeds = new std::vector<double>;
    _speedsWindows = new std::vector<std::deque<double>>;
    _routeLines = new std::vector<std::vector<QGraphicsLineItem*>>;
    _coordsPositions = new std::vector<std::vector<QGraphicsLineItem*>>;
    _forecastsPositions = new std::vector<std::vector<QGraphicsLineItem*>>;

    _pen.setColor(Qt::red);
    _pen.setWidth(2);
    double scale = cSceneSide / cAxisShift;
    std::vector<Road> roadsVect =
    {
        {{6.0, 2.0}, {10.0, 2.0}},
        {{0.0, 4.0}, {10.0, 4.0}},
        {{0.0, 7.0}, {6.0, 7.0}},
        {{3.0, 8.0}, {8.0, 8.0}},
        {{3.0, 0.0}, {3.0, 10.0}},
        {{4.0, 0.0}, {4.0, 10.0}},
        {{6.0, 2.0}, {6.0, 7.0}},
        {{8.0, 0.0}, {8.0, 8.0}},
        {{5.0, 10.0}, {8.0, 6.0}},
        {{1.0, 10.0}, {5.0, 10.0}},
        {{1.0, 3.0}, {1.0, 10.0}},
        {{1.0, 9.0}, {4.0, 5.0}},
        {{1.0, 3.0}, {5.0, 3.0}},
        {{5.0, 3.0}, {6.0, 4.0}},
        {{10.0, 2.0}, {10.0, 4.0}}
    };
    for (size_t i = 0; i < roadsVect.size(); ++i)
    {
        roadsVect[i].first.first *= scale;
        roadsVect[i].first.second *= scale;
        roadsVect[i].second.first *= scale;
        roadsVect[i].second.second *= scale;

        _mainWidget->addLine(roadsVect[i].first.first, roadsVect[i].first.second, roadsVect[i].second.first, roadsVect[i].second.second,
                             _pen);
        _roads->insert(roadsVect[i]);
    }

    _coords = new std::vector<std::vector<Point2d>>
    {
        {
            {2.8, 2.1},
            {2.7, 3.3},
            {3.1, 4.0},
            {2.9, 5.5},
            {3.05, 6.1},
            {2.85, 6.9},
            {4.0, 7.0},
            {5.0, 7.1},
            {5.8, 6.6},
            {6.1, 4.4},
            {5.0, 3.9},
            {3.9, 4.1},
            {4.1, 5.2},
//            {7.0, 3.9},
//            {7.8, 4.1},
//            {8.1, 6.3},
//            {7.5, 7.8},
//            {6.3, 8.2},
//            {4.5, 7.9},
//            {4.1, 7.1},
//            {3.9, 6.5},
            {3.8, 5.1},
            {2.1, 7.6},
            {0.9, 8.8},
            {1.1, 7.2},
            {0.8, 5.0},
            {1.1, 3.1},
            {2.0, 2.9},
            {4.9, 3.1},
            {5.4, 3.4}
        },
        {
            {7.9, 0.5},
            {8.1, 1.9},
            {7.8, 3.9},
            {8.5, 4.2},
            {9.9, 3.9},
            {9.8, 1.9},
            {9.1, 2.1},
            {6.5, 1.8}
        }
    };
    std::vector<std::vector<Point2d>> coordsCopy = *_coords;
    for (size_t i = coordsCopy.size(); i < cRoutesCount; ++i)
    {
        _coords->push_back(coordsCopy[i % coordsCopy.size()]);
    }
    _time = 0.1;

    // Making more coords
    std::vector<Point2d> route;
    double segmentPart;
    size_t routeLastIndex;
    for (size_t r = 0; r < cRoutesCount; ++r)
    {
        routeLastIndex = (*_coords)[r].size() - 1;
        for (size_t i = 0; i < routeLastIndex; ++i)
        {
            route.emplace_back((*_coords)[r][i].first * scale, (*_coords)[r][i].second * scale);
            for (size_t j = 0; j < cPointsBetween; ++j)
            {
                segmentPart = 1.0 * (j + 1) / (cPointsBetween + 1);
                route.emplace_back(((*_coords)[r][i].first + segmentPart * ((*_coords)[r][i + 1].first - (*_coords)[r][i].first)) * scale,
                                   ((*_coords)[r][i].second + segmentPart * ((*_coords)[r][i + 1].second - (*_coords)[r][i].second)) * scale);
            }
        }
        route.emplace_back((*_coords)[r][routeLastIndex].first * scale, (*_coords)[r][routeLastIndex].second * scale);
        _coordsEndIndexes->push_back(route.size());
        addBackwardPointsToRoute(route);
        (*_coords)[r] = route;
        route.clear();

        _prevRoads->push_back(Road{});
        _currRoads->push_back(Road{});
        _coordsIndexes->push_back(0);
        _speeds->push_back(0.0);
        _speedsWindows->push_back(std::deque<double>{});
        _prevPoints->push_back(getPointOnRoad(*_roads, (*_coords)[r][0], (*_prevRoads)[r]));
        _currPoints->push_back(Point2d{});
        _routeLines->push_back(std::vector<QGraphicsLineItem*>{});
        _coordsPositions->push_back(std::vector<QGraphicsLineItem*>{});
        _forecastsPositions->push_back(std::vector<QGraphicsLineItem*>{});

//        _routePoint = _vertices[0];
//        _forward = true;
//        _prevIsegment = 0;
//        _prevCoordsPos = nullptr;
    }

//    _vertices =
//    {
//        {-6.0, 2.0},
//        {-2.0, 5.0},
//        {0.0, 0.0},
//        {5.0, 2.0},
//        {4.0, -3.0},
//        {1.0, -4.0},
//        {2.0, -2.0},
//        {2.0, 3.0}
//    };
////    {
////        {-6.0, 2.0},
////        {6.0, 2.0}
////    };

//    _forward = true;

//    _routePoint = _vertices[0];
//    while (_forward)
////    for (size_t i = 0; i < cPointsOnRoute; ++i)
//    {
//        _currIsegment = getSegmentIndexOnRoute(_vertices, _routePoint, _forward);
//        _speed = speedDistr(gen);
//        _routePoint = getNextRoutePoint(_vertices, _currIsegment, _routePoint, _speed, _dt, _forward);
//        if (_forward)
//        {
//            _coords.emplace_back(_routePoint.first + coordDistr(gen), _routePoint.second + coordDistr(gen));
//        }
//    }

//    // Making ring buffer from vector
//    _coordsCount = _coords.size();
//    for (size_t i = _coordsCount - 2; i > 0; --i)
//    {
//        _coords.push_back(_coords[i]);
//    }
//    _coordsCount = _coords.size();

    setRect(0.5 * cSceneSide, 0.5 * cSceneSide, cPointDiam, cPointDiam);
}

Route::~Route()
{
    delete _roads;
    delete _prevRoads;
    delete _currRoads;
    delete _coords;
    delete _prevPoints;
    delete _currPoints;
    delete _coordsIndexes;
    delete _coordsEndIndexes;
    delete _speeds;
    delete _speedsWindows;
    delete _routeLines;
    delete _coordsPositions;
    delete _forecastsPositions;
}

void Route::advance(int phase)
{
    if (phase)
    {
        bool endOfRoute;
        bool toSecond = false;
        double prevDistToFirst, currDistToFirst;
        double partDistance = 0.0;
        Point2d intersection;
        Road forecastRoad;
        Point2d forecastPoint;
        std::vector<Point2d> forecastPoints;
        std::map<size_t, Point2d> iRoutesToIntersections;
        clock_t calcStartTime = clock();
        clock_t drawStartTime = calcStartTime;
        clock_t calcTime, drawTime;

        //Calc loop
        for (size_t r = 0; r < cRoutesCount; ++r)
        {
            ++(*_coordsIndexes)[r];
            endOfRoute = !(((*_coordsIndexes)[r] % (*_coordsEndIndexes)[r])
                           && ((*_coordsIndexes)[r] % (2 * (*_coordsEndIndexes)[r])));

            (*_currPoints)[r] = getPointOnRoad(*_roads, (*_coords)[r][(*_coordsIndexes)[r] % (2 * (*_coordsEndIndexes)[r])],
                                               (*_currRoads)[r]);

            toSecond = false;
            partDistance = 0.0;
            if ((*_prevRoads)[r] == (*_currRoads)[r])
            {
                prevDistToFirst = getSegmentLength((*_currRoads)[r].first, (*_prevPoints)[r]);
                currDistToFirst = getSegmentLength((*_currRoads)[r].first, (*_currPoints)[r]);
                if (prevDistToFirst < currDistToFirst)
                {
                    toSecond = true;
                }

                partDistance = getSegmentLength((*_prevPoints)[r], (*_currPoints)[r]);
//                if (!endOfRoute)
//                {
//                    (*_routeLines)[r].push_back(_mainWidget->addLine((*_prevPoints)[r].first, (*_prevPoints)[r].second,
//                                                                     (*_currPoints)[r].first, (*_currPoints)[r].second, _pen));
//                }
            }
            else
            {
                if (twoRoadsIntersect((*_prevRoads)[r], (*_currRoads)[r], intersection))
                {
                    iRoutesToIntersections.emplace(r, intersection);
                    prevDistToFirst = getSegmentLength((*_currRoads)[r].first, intersection);
                    currDistToFirst = getSegmentLength((*_currRoads)[r].first, (*_currPoints)[r]);
                    if (prevDistToFirst < currDistToFirst)
                    {
                        toSecond = true;
                    }

                    partDistance = getSegmentLength((*_prevPoints)[r], intersection) + getSegmentLength(intersection, (*_currPoints)[r]);
//                    if (!endOfRoute)
//                    {
//                        (*_routeLines)[r].push_back(_mainWidget->addLine((*_prevPoints)[r].first, (*_prevPoints)[r].second,
//                                                                         intersection.first, intersection.second, _pen));
//                        (*_routeLines)[r].push_back(_mainWidget->addLine(intersection.first, intersection.second, (*_currPoints)[r].first,
//                                                                         (*_currPoints)[r].second, _pen));
//                    }
                }
            }

            (*_speeds)[r] = calcMovingAverageSpeed((*_speedsWindows)[r], cSpeedsWindowSize, partDistance, _time);

            forecastPoint = getForecastPoint(*_roads, (*_currPoints)[r], (*_currRoads)[r], toSecond, (*_speeds)[r], _time, forecastRoad);
            forecastPoints.push_back(forecastPoint);
//            _pen.setColor(Qt::magenta);
//            _pen.setWidth(7);
//            (*_forecastsPositions)[r].push_back(_mainWidget->addLine(forecastPoint.first, forecastPoint.second, forecastPoint.first,
//                                                                     forecastPoint.second, _pen));

//            (*_prevPoints)[r] = (*_currPoints)[r];
//            (*_prevRoads)[r] = (*_currRoads)[r];
            --(*_coordsIndexes)[r];

    //        _currIsegment = getSegmentIndexOnRoute(_vertices, _routePoint, _forward);

    //        if (_prevIsegment < _currIsegment)
    //        {
    //            for (size_t iSegment = _prevIsegment + 1; iSegment < _currIsegment + 1; ++iSegment)
    //            {
    //                partDistance += getSegmentLength(_prevCoords, _vertices[iSegment]);
    //            }
    //        }
    //        partDistance += getSegmentLength(_vertices[_currIsegment], _currCoords);
    //        _routePoint = getNextRoutePoint(_vertices, _currIsegment, _currCoords, _speed, _dt, _forward);
    //        _pen.setColor(Qt::blue);
    //        _pen.setWidth(5);
    //        _prevForecastPos = _mainWidget->addLine(_routePoint.first, _routePoint.second, _routePoint.first, _routePoint.second, _pen);
    //        forecastPoint = getNextRoutePoint(vertices, currIsegment, *coordsIt, avgSpeed, dt, forwardDirection);
    //        std::cout << "Current point (" << coordsIt->first << ", " << coordsIt->second << "), snapped to route point (" << currPoint.first
    //                  << ", " << currPoint.second << "), forecast point (" << forecastPoint.first << ", " << forecastPoint.second
    //                  << "), average speed " << avgSpeed << ", time delta " << dt << ", partial distance " << partDistance << ", elapsed time "
    //                  << totalTime << ", total distance " << totalDistance << '\n';
    //        _prevIsegment = _currIsegment;
    //        ++_coordIndex;
        }
        calcTime = clock() - calcStartTime;

        // Draw loop
        auto intersectionIt = iRoutesToIntersections.begin();
        for (size_t r = 0; r < cRoutesCount; ++r)
        {
            _pen.setColor(Qt::blue);
            _pen.setWidth(7);
            (*_coordsPositions)[r].push_back(_mainWidget->addLine((*_coords)[r][(*_coordsIndexes)[r] % (2 * (*_coordsEndIndexes)[r])].first,
                                                               (*_coords)[r][(*_coordsIndexes)[r] % (2 * (*_coordsEndIndexes)[r])].second,
                                                               (*_coords)[r][(*_coordsIndexes)[r] % (2 * (*_coordsEndIndexes)[r])].first,
                                                               (*_coords)[r][(*_coordsIndexes)[r] % (2 * (*_coordsEndIndexes)[r])].second,
                                                                _pen));
            ++(*_coordsIndexes)[r];
            endOfRoute = !(((*_coordsIndexes)[r] % (*_coordsEndIndexes)[r])
                           && ((*_coordsIndexes)[r] % (2 * (*_coordsEndIndexes)[r])));
            if (endOfRoute)
            {
                for (auto item : (*_routeLines)[r])
                {
                    _mainWidget->removeItem(item);
                }
                (*_routeLines)[r].clear();

                for (auto pos : (*_coordsPositions)[r])
                {
                    _mainWidget->removeItem(pos);
                }
                (*_coordsPositions)[r].clear();

                for (auto pos : (*_forecastsPositions)[r])
                {
                    _mainWidget->removeItem(pos);
                }
                (*_forecastsPositions)[r].clear();
            }
//            this->setPos(_prevPoints[r].first - 0.5 * (cSceneSide + cPointDiam), _prevPoints[r].second - 0.5 * (cSceneSide + cPointDiam));

            _pen.setColor(Qt::green);
            _pen.setWidth(3);
            if ((*_prevRoads)[r] == (*_currRoads)[r] && !endOfRoute)
            {
                (*_routeLines)[r].push_back(_mainWidget->addLine((*_prevPoints)[r].first, (*_prevPoints)[r].second,
                                                                 (*_currPoints)[r].first, (*_currPoints)[r].second, _pen));
            }
            else
            {
                intersectionIt = iRoutesToIntersections.find(r);
                if (intersectionIt != iRoutesToIntersections.end() && !endOfRoute)
                {
                    (*_routeLines)[r].push_back(_mainWidget->addLine((*_prevPoints)[r].first, (*_prevPoints)[r].second,
                                                                     intersectionIt->second.first, intersectionIt->second.second, _pen));
                    (*_routeLines)[r].push_back(_mainWidget->addLine(intersectionIt->second.first, intersectionIt->second.second,
                                                                     (*_currPoints)[r].first, (*_currPoints)[r].second, _pen));
                }
            }

            _pen.setColor(Qt::magenta);
            _pen.setWidth(7);
            (*_forecastsPositions)[r].push_back(_mainWidget->addLine(forecastPoints[r].first, forecastPoints[r].second,
                                                                     forecastPoints[r].first, forecastPoints[r].second, _pen));

            (*_prevPoints)[r] = (*_currPoints)[r];
            (*_prevRoads)[r] = (*_currRoads)[r];
        }
        drawTime = clock() - drawStartTime;

        double calcTimeSec = 1.0 * calcTime / CLOCKS_PER_SEC;
        double drawTimeSec = 1.0 * drawTime / CLOCKS_PER_SEC;

        double dou = drawTimeSec;
    }
}

bool Route::twoRoadsIntersect(const Road & road1, const Road & road2, Point2d & intersection)
{
    bool result = false;
    double a1, b1, c1, a2, b2, c2, delta;
    getCanonicalCoeffsFromSegment(road1.first, road1.second, a1, b1, c1);
    getCanonicalCoeffsFromSegment(road2.first, road2.second, a2, b2, c2);
    delta = a1 * b2 - b1 * a2;
    if (!doublesAreEqual(delta, 0.0))
    {
        result = true;
        double deltaX = -c1 * b2 + b1 * c2;
        double deltaY = -a1 * c2 + c1 * a2;
        intersection.first = deltaX / delta;
        intersection.second = deltaY / delta;
    }

    return result;
}

double Route::calcMovingAverageSpeed(std::deque<double> & speedsWindow, size_t windowSize, double distance, double time)
{
    if (speedsWindow.size() == windowSize)
    {
        speedsWindow.pop_front();
    }
    speedsWindow.push_back(distance / time);

    double result = 0.0;
    return std::accumulate(speedsWindow.begin(), speedsWindow.end(), result) / speedsWindow.size();
}

Point2d Route::snapPointToRoute(const std::vector<Point2d> & vertices, const Point2d & point)
{
    Point2d result;

    std::multimap<double, size_t> distancesToSegments;
    for (size_t i = 0; i < vertices.size() - 1; ++i)
    {
        distancesToSegments.emplace(getDistanceToSegment(vertices[i], vertices[i + 1], point), i);
    }

    size_t minDistanceIndex = distancesToSegments.begin()->second;
    Point2d nearestPoint = getNearestPointOnSegmentLine(vertices[minDistanceIndex], vertices[minDistanceIndex + 1], point);
    if (onSegmentCollinear(vertices[minDistanceIndex], vertices[minDistanceIndex + 1], nearestPoint))
    {
        result = nearestPoint;
    }
    else
    {
        double sBeginDistance = getSegmentLength(vertices[minDistanceIndex], nearestPoint);
        result = (sBeginDistance > getSegmentLength(vertices[minDistanceIndex + 1], nearestPoint)) ? vertices[minDistanceIndex + 1]
                : vertices[minDistanceIndex];
    }

    return result;
}

Point2d Route::getPointOnRoad(const std::set<Road> & roads, const Point2d & point, Road & road)
{
    Point2d result;

    std::multimap<double, Road> distancesToRoads;
    for (auto & road : roads)
    {
        distancesToRoads.emplace(getDistanceToSegment(road.first, road.second, point), road);
    }

    Point2d nearestPoint;
    bool gotPoint = false;
    for (auto & distanceToRoad : distancesToRoads)
    {
        nearestPoint = getNearestPointOnSegmentLine(distanceToRoad.second.first, distanceToRoad.second.second, point);
        if (onSegmentCollinear(distanceToRoad.second.first, distanceToRoad.second.second, nearestPoint))
        {
            gotPoint = true;
            road = distanceToRoad.second;
            result = nearestPoint;
            break;
        }
    }

    if (!gotPoint)
    {
        road = distancesToRoads.begin()->second;
        nearestPoint = getNearestPointOnSegmentLine(road.first, road.second, point);
        double sBeginDistance = getSegmentLength(road.first, nearestPoint);
        result = (sBeginDistance > getSegmentLength(road.second, nearestPoint)) ? road.second : road.first;
    }

    return result;
}

Point2d Route::getNearestPointOnSegmentLine(const Point2d & sBegin, const Point2d & sEnd, const Point2d & point)
{
    double a, b, c;
    getCanonicalCoeffsFromSegment(sBegin, sEnd, a, b, c);
    double denom = a * a + b * b;
    return {(b * (b * point.first - a * point.second) - a * c) / denom, (a * (-b * point.first + a * point.second) - b * c) / denom};
}

size_t Route::getSegmentIndexOnRoute(const std::vector<Point2d> & vertices, const Point2d & point, bool forward)
{
    size_t iCurr, iNext;
    Point2d nearestPoint;
    if (forward)
    {
        for (iCurr = 0; iCurr < vertices.size() - 1; ++iCurr)
        {
            iNext = iCurr + 1;
            nearestPoint = getNearestPointOnSegmentLine(vertices[iCurr], vertices[iNext], point);
            if (onSegmentCollinear(vertices[iCurr], vertices[iNext], nearestPoint) && pointsCoincide(point, nearestPoint))
            {
                if (pointsCoincide(nearestPoint, vertices[iNext]) && iNext != vertices.size() - 1)
                {
                    ++iCurr;
                }
                break;
            }
        }
    }
    else
    {
        for (iCurr = vertices.size() - 1; iCurr > 1; --iCurr)
        {
            iNext = iCurr - 1;
            nearestPoint = getNearestPointOnSegmentLine(vertices[iCurr], vertices[iNext], point);
            if (onSegmentCollinear(vertices[iCurr], vertices[iNext], nearestPoint) && pointsCoincide(point, nearestPoint))
            {
                if (pointsCoincide(nearestPoint, vertices[iNext]) && iNext != 0)
                {
                    --iCurr;
                }
                break;
            }
        }
    }

    return iCurr;
}

Point2d Route::traverseRoute(const std::vector<Point2d> & vertices, size_t & iSegment, const Point2d & currPoint, double & distance,
                             bool & forward, bool & pointReached)
{
    Point2d result;

    double segmentLength;
    double segmentPart;
    if (forward)
    {
        if (iSegment < vertices.size() - 1)
        {
            segmentLength = getSegmentLength(currPoint, vertices[iSegment + 1]);
            if (distance > segmentLength)
            {
                ++iSegment;
                distance -= getSegmentLength(currPoint, vertices[iSegment]);
                if (iSegment < vertices.size() - 1)
                {
                    segmentLength = getSegmentLength(vertices[iSegment], vertices[iSegment + 1]);
                    while (distance > segmentLength)
                    {
                        distance -= segmentLength;
                        if (iSegment < vertices.size() - 1)
                        {
                            ++iSegment;
                            segmentLength = getSegmentLength(vertices[iSegment], vertices[iSegment + 1]);
                        }
                        else
                        {
                            result = vertices[vertices.size() - 1];
                            forward = !forward;
                            break;
                        }
                    }

                    if (distance < segmentLength)
                    {
                        segmentPart = distance / segmentLength;
                        result =
                        {
                            vertices[iSegment].first + segmentPart * (vertices[iSegment + 1].first - vertices[iSegment].first),
                            vertices[iSegment].second + segmentPart * (vertices[iSegment + 1].second - vertices[iSegment].second),
                        };
                        pointReached = true;
                    }
                }
                else
                {
                    result = vertices[vertices.size() - 1];
                    forward = !forward;
                }
            }
            else
            {
                segmentPart = 1.0 - (segmentLength - distance) / getSegmentLength(vertices[iSegment], vertices[iSegment + 1]);
                result =
                {
                    vertices[iSegment].first + segmentPart * (vertices[iSegment + 1].first - vertices[iSegment].first),
                    vertices[iSegment].second + segmentPart * (vertices[iSegment + 1].second - vertices[iSegment].second),
                };
                pointReached = true;
            }
        }
        else
        {
            result = vertices[vertices.size() - 1];
            forward = !forward;
        }
    }
    else
    {
        if (iSegment > 0)
        {
            segmentLength = getSegmentLength(currPoint, vertices[iSegment - 1]);
            if (distance > segmentLength)
            {
                --iSegment;
                distance -= getSegmentLength(currPoint, vertices[iSegment]);
                if (iSegment > 0)
                {
                    segmentLength = getSegmentLength(vertices[iSegment], vertices[iSegment - 1]);
                    while (distance > segmentLength)
                    {
                        distance -= segmentLength;
                        if (iSegment > 0)
                        {
                            --iSegment;
                            segmentLength = getSegmentLength(vertices[iSegment], vertices[iSegment - 1]);
                        }
                        else
                        {
                            result = vertices[0];
                            forward = !forward;
                            break;
                        }
                    }

                    if (distance < segmentLength)
                    {
                        segmentPart = distance / segmentLength;
                        result =
                        {
                            vertices[iSegment].first + segmentPart * (vertices[iSegment - 1].first - vertices[iSegment].first),
                            vertices[iSegment].second + segmentPart * (vertices[iSegment - 1].second - vertices[iSegment].second),
                        };
                        pointReached = true;
                    }
                }
                else
                {
                    result = vertices[0];
                    forward = !forward;
                }
            }
            else
            {
                segmentPart = 1.0 - (segmentLength - distance) / getSegmentLength(vertices[iSegment], vertices[iSegment - 1]);
                result =
                {
                    vertices[iSegment].first + segmentPart * (vertices[iSegment - 1].first - vertices[iSegment].first),
                    vertices[iSegment].second + segmentPart * (vertices[iSegment - 1].second - vertices[iSegment].second),
                };
                pointReached = true;
            }
        }
        else
        {
            result = vertices[0];
            forward = !forward;
        }
    }

    return result;
}

Point2d Route::getNextRoutePoint(const std::vector<Point2d> & vertices, size_t iSegment, const Point2d & currPoint, double speed,
                                 double time, bool & forward)
{
    Point2d result = currPoint;

    double distance = speed * time;
    bool pointReached = false;
    while (!pointReached)
    {
        result = traverseRoute(vertices, iSegment, result, distance, forward, pointReached);
    }

    return result;
}

Road Route::getRoadByEnd(const std::set<Road>& roads, const Road & currRoad, const Point2d & roadEnd, bool & first)
{
    Road result = currRoad;
    bool success = false;
    for (auto & road : roads)
    {
        if (pointsCoincide(roadEnd, road.first) && road != currRoad)
        {
            success = true;
            result = road;
            first = true;
            break;
        }

        if (pointsCoincide(roadEnd, road.second) && road != currRoad)
        {
            success = true;
            result = road;
            first = false;
            break;
        }
    }

    if (!success)
    {
        first = pointsCoincide(roadEnd, result.first) ? true : false;
    }

    return result;
}

Point2d Route::getForecastPoint(const std::set<Road> & roads, const Point2d & currPoint, const Road & currRoad, bool toSecond, double speed,
                                double time, Road & forecastRoad)
{
    Point2d result = currRoad.second;

    double distance = speed * time;
    Point2d roadEnd = (toSecond) ? currRoad.second : currRoad.first;
    double roadRest = getSegmentLength(currPoint, roadEnd);
    double segmentPart;

    if (distance < roadRest)
    {
        forecastRoad = currRoad;
        segmentPart = distance / roadRest;
        result =
        {
            currPoint.first + segmentPart * (roadEnd.first - currPoint.first),
            currPoint.second + segmentPart * (roadEnd.second - currPoint.second),
        };
    }
    else
    {
        distance -= roadRest;
        forecastRoad = getRoadByEnd(roads, currRoad, roadEnd, toSecond);
        Point2d roadBegin = (toSecond) ? forecastRoad.first : forecastRoad.second;
        roadEnd = (toSecond) ? forecastRoad.second : forecastRoad.first;
        roadRest = getSegmentLength(forecastRoad.first, forecastRoad.second);
        if (distance < roadRest)
        {
            segmentPart = distance / roadRest;
            result =
            {
                roadBegin.first + segmentPart * (roadEnd.first - roadBegin.first),
                roadBegin.second + segmentPart * (roadEnd.second - roadBegin.second),
            };
        }
        else
        {
            result = roadEnd;
        }
    }

    return result;
}
