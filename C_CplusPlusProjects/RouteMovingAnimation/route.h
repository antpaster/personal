#ifndef ROUTE_H
#define ROUTE_H

#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <vector>
#include <deque>
#include <set>

using Point2d = std::pair<double, double>;
using Road = std::pair<Point2d, Point2d>;

extern const double cSqMinDist;
extern const double cAxisShift;
extern const double cSceneSide;

class Route : public QGraphicsEllipseItem
{
public:
    Route(QGraphicsScene * parent);
    ~Route();
    void advance(int phase);

private:
    QGraphicsScene * _mainWidget;
    std::set<Road> * _roads;
    std::vector<Road> * _prevRoads;
    std::vector<Road> * _currRoads;
    std::vector<std::vector<Point2d>> * _coords;
    std::vector<Point2d> * _prevPoints;
    std::vector<Point2d> * _currPoints;
    std::vector<size_t> * _coordsIndexes;
    std::vector<size_t> * _coordsEndIndexes;
    double _time;
    std::vector<double> * _speeds;
    std::vector<std::deque<double>> * _speedsWindows;
    QPen _pen;
    std::vector<std::vector<QGraphicsLineItem*>> * _routeLines;
    std::vector<std::vector<QGraphicsLineItem*>> * _coordsPositions;
    std::vector<std::vector<QGraphicsLineItem*>> * _forecastsPositions;

//    std::vector<Point2d> _vertices;
//    size_t _prevIsegment, _currIsegment;
//    Point2d _routePoint;
//    bool _forward;
//    QGraphicsLineItem * _prevCoordsPos;

    inline bool doublesAreEqual(double a, double b)
    {
        return fabs(a - b) < cSqMinDist;
    }

    inline bool pointsCoincide(const Point2d & p1, const Point2d & p2)
    {
        return pow(p2.first - p1.first, 2.0) + pow(p2.second - p1.second, 2.0) < cSqMinDist;
    }

    inline double getSegmentLength(const Point2d & sBegin, const Point2d & sEnd)
    {
        return sqrt(pow(sEnd.first - sBegin.first, 2.0) + pow(sEnd.second - sBegin.second, 2.0));
    }

    inline bool onSegmentCollinear(const Point2d & sBegin, const Point2d & sEnd, const Point2d & point)
    {
        bool xCondition;
        if (sBegin.first < sEnd.first)
        {
            xCondition = sBegin.first <= point.first && point.first <= sEnd.first;
        }
        else
        {
            xCondition = sEnd.first <= point.first && point.first <= sBegin.first;
        }

        bool yCondition;
        if (sBegin.second < sEnd.second)
        {
            yCondition = sBegin.second <= point.second && point.second <= sEnd.second;
        }
        else
        {
            yCondition = sEnd.second <= point.second && point.second <= sBegin.second;
        }

        return xCondition && yCondition;
    }

    inline void getCanonicalCoeffsFromSegment(const Point2d & sBegin, const Point2d & sEnd, double & a, double & b, double & c)
    {
        a = sEnd.second - sBegin.second;
        b = sBegin.first - sEnd.first;
        c = sBegin.first * (sBegin.second - sEnd.second) + sBegin.second * (sEnd.first - sBegin.first);
    }

    inline double getDistanceToSegment(const Point2d & sBegin, const Point2d & sEnd, const Point2d & point)
    {
        double a, b, c;
        getCanonicalCoeffsFromSegment(sBegin, sEnd, a, b, c);
        return fabs(a * point.first + b * point.second + c) / sqrt(a * a + b * b);
    }

    inline void addBackwardPointsToRoute(std::vector<Point2d> & route)
    {
        std::vector<Point2d> routeCopy = route;
        size_t startIndex = routeCopy.size() - 1;
        for (int i = startIndex; i >= 0; --i)
        {
            route.push_back(routeCopy[i]);
        }
    }

    bool twoRoadsIntersect(const Road & road1, const Road & road2, Point2d & intersection);
    double calcMovingAverageSpeed(std::deque<double> & speedsWindow, size_t windowSize, double distance, double time);
    Point2d snapPointToRoute(const std::vector<Point2d> & vertices, const Point2d & point);
    Point2d getPointOnRoad(const std::set<Road> & roads, const Point2d & point, Road &road);
    Point2d getNearestPointOnSegmentLine(const Point2d & sBegin, const Point2d & sEnd, const Point2d & point);
    size_t getSegmentIndexOnRoute(const std::vector<Point2d> & vertices, const Point2d & point, bool forward);
    Point2d traverseRoute(const std::vector<Point2d> & vertices, size_t & iSegment, const Point2d & currPoint, double & distance,
                          bool & forward, bool & pointReached);
    Point2d getNextRoutePoint(const std::vector<Point2d> & vertices, size_t iSegment, const Point2d & currPoint, double speed, double time,
                              bool & forward);
    Road getRoadByEnd(const std::set<Road>& roads, const Road &currRoad, const Point2d & roadEnd, bool & first);
    Point2d getForecastPoint(const std::set<Road> & roads, const Point2d & currPoint, const Road & currRoad, bool toSecond, double speed,
                             double time, Road & forecastRoad);
};

#endif // ROUTE_H
