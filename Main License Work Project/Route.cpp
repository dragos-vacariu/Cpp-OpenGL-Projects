#include "Route.h"

Route::Route(const unsigned int Traveling_speed, const unsigned int ID,
             vector <Route> &cars):Car(Traveling_speed, ID) //This will call the base class constructor first
{
    routeNumber = (rand()% TOTAL_ROUTES) +1;
    setRouteStartCoordinates();
    addTimeGaps(cars, routeNumber);
}
Route::Route(const unsigned int Traveling_speed, const unsigned int routeN,
             const unsigned int ID, vector <Route> &cars): Car(Traveling_speed, ID) //This will call the base class constructor first
{
    //Validating the route:
    if(routeN < 1 && routeN > TOTAL_ROUTES)
    {
        routeNumber = 1; //let this be the default value
    }
    else
    {
        routeNumber = routeN;
    }
    setRouteStartCoordinates();
    addTimeGaps(cars, routeNumber);
}
Route::Route(const unsigned int Traveling_speed, const unsigned int routeN,
             const unsigned int ID): Car(Traveling_speed, ID) //This will call the base class constructor first
{
        //Validating the route:
    if(routeN < 1 && routeN > TOTAL_ROUTES)
    {
        routeNumber = 1; //let this be the default value
    }
    else
    {
        routeNumber = routeN;
    }
    routeNumber = routeN;
    setRouteStartCoordinates();
}
Route::Route(const unsigned int Traveling_speed,
             const unsigned int ID):Car(Traveling_speed, ID) //This will call the base class constructor first
{
    routeNumber = (rand()% TOTAL_ROUTES) +1;
    setRouteStartCoordinates();
}

Route::~Route()
{
    //dtor
}
