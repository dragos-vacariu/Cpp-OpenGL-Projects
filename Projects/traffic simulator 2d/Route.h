#ifndef ROUTE_H
#define ROUTE_H

/*User defined headers:*/
#include "Car.h"

/*defining constants*/
#define TOTAL_ROUTES 19

class Route: public Car
{
    public:
        Route(const unsigned int Traveling_speed, const unsigned int ID, vector <Route> &cars);
        Route(const unsigned int Traveling_speed, const unsigned int routeN, const unsigned int ID, vector <Route> &cars);
        Route(const unsigned int Traveling_speed, const unsigned int routeN, const unsigned int ID);
        Route(const unsigned int Traveling_speed, const unsigned int ID);
        virtual ~Route();
        //Route fields:
        void FollowingRoute()
        {
            switch(routeNumber)
            {
                case 1:{
                    RouteNr1();
                    break;
                }
                case 2:{
                    RouteNr2();
                    break;
                }
                case 3:{
                    RouteNr3();
                    break;
                }
                case 4: {
                    RouteNr4();
                    break;
                }
                case 5: {
                    RouteNr5();
                    break;
                }
                case 6: {
                    RouteNr6();
                    break;
                }
                case 7: {
                    RouteNr7();
                    break;
                }
                case 8: {
                    RouteNr8();
                    break;
                }
                case 9:
                {
                    RouteNr9();
                    break;
                }
                case 10:
                {
                    RouteNr10();
                    break;
                }
                case 11:
                {
                    RouteNr11();
                    break;
                }
                case 12:
                {
                    RouteNr12();
                    break;
                }
                case 13:
                {
                    RouteNr13();
                    break;
                }
                case 14:
                {
                    RouteNr14();
                    break;
                }
                case 15:
                {
                    RouteNr15();
                    break;
                }
                case 16:
                {
                    RouteNr16();
                    break;
                }
                case 17:
                {
                    RouteNr17();
                    break;
                }
                case 18:
                {
                    RouteNr18();
                    break;
                }
                case 19:
                {
                    RouteNr19();
                    break;
                }
            }
        }
        void CollisionDetection(vector <Route> cars)
        {
            for(unsigned int i=0; i<cars.size(); i++)
            {
                if( uniqueID != cars[i].uniqueID)
                {
                    //Perpendicular collision
                    if(  (getCarCoordinates(7) < cars[i].getCarCoordinates(7) + 50 && getCarCoordinates(7) > cars[i].getCarCoordinates(7) - 50)
                        && ( getCarCoordinates(6) > cars[i].getCarCoordinates(0) - 50 && getCarCoordinates(6) < cars[i].getCarCoordinates(0) + 50)
                       &&( getCarCoordinates(6) > cars[i].getCarCoordinates(5) - 50 && getCarCoordinates(6) < cars[i].getCarCoordinates(5) + 50)
                       && CarRotatedPosition%2==1  && cars[i].CarRotatedPosition%2==0)
                    {
                        if(isCarMoving && cars[i].isCarMoving)
                        {
                            StopTheCar();
                        }
                    }
                    else if(  (getCarCoordinates(6) < cars[i].getCarCoordinates(6) + 50 && getCarCoordinates(6) > cars[i].getCarCoordinates(6) - 50)
                        && ( getCarCoordinates(7) > cars[i].getCarCoordinates(7) - 50 && getCarCoordinates(7) < cars[i].getCarCoordinates(7) + 50)
                        && ( getCarCoordinates(7) > cars[i].getCarCoordinates(0) - 50 && getCarCoordinates(7) < cars[i].getCarCoordinates(0) + 50)
                       && CarRotatedPosition%2==0 && cars[i].CarRotatedPosition%2==1)
                    {
                        if(isCarMoving && cars[i].isCarMoving)
                        {
                            StopTheCar();
                        }
                    }
                    //Running into collision:
                    /*else if(  (getCarCoordinates(6) > cars[i].getCarCoordinates(0) - 50 && getCarCoordinates(6) < cars[i].getCarCoordinates(6) + 50)
                        && ( getCarCoordinates(7) < cars[i].getCarCoordinates(1) + 50 && getCarCoordinates(5) > cars[i].getCarCoordinates(5) - 50)
                       && CarRotatedPosition%2==0 && CarRotatedPosition==cars[i].CarRotatedPosition)
                    {
                        if(isCarMoving && cars[i].isCarMoving)
                        {
                            StopTheCar();
                        }
                    }*/
                    else
                    {
                        StartTheCar();
                    }
                }
            }
        }
        //Getters:
        GLfloat getCarCoordinates(const int index) //This will make the CarCoordinate field be read-only outside this class.
        {
            if(index < 0 || index > 7)
            {
                cout << "Wrong value had been entered for reading the Car Coordinate." << endl;
                exit(1);
            }
            return CarCoordinates[index];
        }
        unsigned int getRouteNumber() //turn routeNumber to read-only outside this class.
        {
            return routeNumber;
        }
        unsigned int getCarRotatedPosition()
        {
            return CarRotatedPosition;
        }
    protected:
    /*Nothing to add in here, this class will not be inherited.*/

    private:
        //Private fields:
        int routeNumber;
        //Route functionality:
        void RouteNr1()
        {
            //The magic of the track1 happens here:
            if( CarCoordinates[1] < 120 )
            {
               MovingCarUp();
            }
            else
            {
                if(CarCoordinates[2] < 570)
                {
                    RotateCarHorizontally();
                    CarRotatedPosition = 2;
                    MovingCarRight();
                }
                else
                {
                    if(CarCoordinates[1] < 640)
                    {
                        RotateCarVertically();
                        CarRotatedPosition = 1;
                        MovingCarUp();
                    }
                }
            }
        }
        void RouteNr2()
        {
            if( CarCoordinates[2] < 1030)
            {
               MovingCarRight();
            }
        }
        void RouteNr3()
        {
            if( CarCoordinates[1] > -60)
            {
               MovingCarLeft();
            }
        }
        void RouteNr4()
        {
            if( CarCoordinates[1] < 650)
            {
               MovingCarUp();
            }
        }
        void RouteNr5()
        {
            if( CarCoordinates[2] > 540)
            {
               MovingCarLeft();
               checkStopageSign();
            }
            else
            {
                RotateCarVertically();
                CarRotatedPosition = 3;
                MovingCarDown();
            }
        }
        void RouteNr6()
        {
            if( CarCoordinates[1] < 120 && CarCoordinates[2] < 30)
            {
               MovingCarUp();
            }
            else
            {
                if( CarCoordinates[2] < 530)
                {
                    RotateCarHorizontally();
                    CarRotatedPosition = 2;
                    MovingCarRight();
                }
                else
                {
                    if( CarCoordinates[1] > 40 && CarCoordinates[2] < 600)
                    {
                        RotateCarVertically();
                        CarRotatedPosition = 3;
                        MovingCarDown();
                    }
                    else
                    {
                        if( CarCoordinates[2] < 860 )
                        {
                            RotateCarHorizontally();
                            CarRotatedPosition = 2;
                            MovingCarRight();
                        }
                        else
                        {
                            if( CarCoordinates[1] < 324 )
                            {
                               RotateCarVertically();
                               CarRotatedPosition = 1;
                               MovingCarUp();
                            }
                            else
                            {
                                RotateCarHorizontally();
                                CarRotatedPosition = 2;
                                MovingCarRight();
                            }
                        }

                    }
                }
            }
        }
        void RouteNr7()
        {
            if( CarCoordinates[1] < 120 && CarCoordinates[2] < 30)
            {
               MovingCarUp();
            }
            else
            {
                if( CarCoordinates[2] < 570 )
                {
                    RotateCarHorizontally();
                    CarRotatedPosition = 2;
                    MovingCarRight();
                }
                else
                {
                    if( CarCoordinates[1] < 325 )
                    {
                        RotateCarVertically();
                        CarRotatedPosition = 1;
                        MovingCarUp();
                    }
                    else
                    {
                        RotateCarHorizontally();
                        CarRotatedPosition = 2;
                        MovingCarRight();
                    }
                }
            }
        }
        void RouteNr8()
        {
            if( CarCoordinates[1] < 120 && CarCoordinates[2] < 30 )
            {
               MovingCarUp();
            }
            else
            {
                if( CarCoordinates[2] < 570 && CarCoordinates[1] < 250)
                {
                    RotateCarHorizontally();
                    CarRotatedPosition = 2;
                    MovingCarRight();
                }
                else
                {
                    if( CarCoordinates[1] < 365 )
                    {
                        RotateCarVertically();
                        CarRotatedPosition = 1;
                        MovingCarUp();
                    }
                    else
                    {
                        RotateCarHorizontally();
                        CarRotatedPosition = 4;
                        MovingCarLeft();
                    }
                }
            }
        }
        void RouteNr9()
        {
            if( CarCoordinates[2] < 265 )
            {
               MovingCarRight();
            }
            else
            {
                if( CarCoordinates[1] > 320 )
                {
                    RotateCarVertically();
                    CarRotatedPosition = 3;
                    MovingCarDown();
                }
                else
                {
                    RotateCarHorizontally();
                    CarRotatedPosition = 2;
                    MovingCarRight();
                }
            }
        }
        void RouteNr10()
        {
            if( CarCoordinates[2] < 255 && CarCoordinates[1] > 380)
            {
               MovingCarRight();
            }
            else
            {
                if( CarCoordinates[1] > 370 )
                {
                    RotateCarVertically();
                    CarRotatedPosition = 3;
                    MovingCarDown();
                }
                else
                {
                    RotateCarHorizontally();
                    CarRotatedPosition = 4;
                    MovingCarLeft();
                }
            }
        }
        void RouteNr11()
        {
            if( CarCoordinates[2] < 255)
            {
               MovingCarRight();
            }
            else
            {
                if( CarCoordinates[1] > 320)
                {
                    RotateCarVertically();
                    CarRotatedPosition = 3;
                    MovingCarDown();
                }
                else
                {
                    if( CarCoordinates[2] < 525)
                    {
                        RotateCarHorizontally();
                        CarRotatedPosition = 2;
                        MovingCarRight();
                    }
                    else
                    {
                        RotateCarVertically();
                        CarRotatedPosition = 3;
                        MovingCarDown();
                    }
                }
            }
        }
        void RouteNr12()
        {
            if( CarCoordinates[2] < 255)
            {
               MovingCarRight();
            }
            else
            {
                if( CarCoordinates[1] > 320 && CarCoordinates[2] < 300 )
                {
                    RotateCarVertically();
                    CarRotatedPosition = 3;
                    MovingCarDown();
                }
                else
                {
                    if( CarCoordinates[2] < 575 )
                    {
                        RotateCarHorizontally();
                        CarRotatedPosition = 2;
                        MovingCarRight();
                    }
                    else
                    {
                        RotateCarVertically();
                        CarRotatedPosition = 1;
                        MovingCarUp();
                    }
                }
            }
        }
        void RouteNr13()
        {
            if( CarCoordinates[2] > 530 )
            {
               MovingCarLeft();
               checkStopageSign();
            }
            else
            {   if( CarCoordinates[1] > 360 )
                {
                    RotateCarVertically();
                    CarRotatedPosition = 3;
                    MovingCarDown();
                }
                else
                {
                    RotateCarHorizontally();
                    CarRotatedPosition=4;
                    MovingCarLeft();
                }
            }
        }
        void RouteNr14()
        {
            if( CarCoordinates[2] > 530 && CarCoordinates[1] > 350 )
            {
               MovingCarLeft();
               checkStopageSign();
            }
            else
            {   if( CarCoordinates[1] > 320 )
                {
                    RotateCarVertically();
                    CarRotatedPosition = 3;
                    MovingCarDown();
                }
                else
                {
                    RotateCarHorizontally();
                    CarRotatedPosition=2;
                    MovingCarRight();
                }
            }
        }
        void RouteNr15()
        {
            if( CarCoordinates[1] > -50 )
            {
               MovingCarDown();
            }
        }
        void RouteNr16()
        {
            if( CarCoordinates[1] > 370 )
            {
               MovingCarDown();
            }
            else
            {
                RotateCarHorizontally();
                CarRotatedPosition=4;
                MovingCarLeft();
            }
        }
        void RouteNr17()
        {
            if( CarCoordinates[1] > 330 && CarCoordinates[2] > 500)
            {
               MovingCarDown();
            }
            else
            {
                RotateCarHorizontally();
                CarRotatedPosition=2;
                MovingCarRight();
            }
        }
        void RouteNr18()
        {
            if( CarCoordinates[1] > 30 && (CarCoordinates[2] > 500 && CarCoordinates[2] < 800) )
            {
               MovingCarDown();
            }
            else
            {
                if( CarCoordinates[2] < 870 )
                {
                    RotateCarHorizontally();
                    CarRotatedPosition=2;
                    MovingCarRight();
                }
                else
                {
                    if( CarCoordinates[1] < 330)
                    {
                        RotateCarVertically();
                        CarRotatedPosition=1;
                        MovingCarUp();
                    }
                    else
                    {
                        RotateCarHorizontally();
                        CarRotatedPosition=2;
                        MovingCarRight();
                    }
                }

            }
        }
        void RouteNr19()
        {
            if( CarCoordinates[1] > 30 && CarRotatedPosition == 3 )
            {
               MovingCarDown();
            }
            else
            {
                if( CarCoordinates[2] < 870 && CarCoordinates[1] < 300)
                {
                    RotateCarHorizontally();
                    CarRotatedPosition=2;
                    MovingCarRight();
                }
                else
                {
                    if( CarCoordinates[1] < 360)
                    {
                        RotateCarVertically();
                        CarRotatedPosition=1;
                        MovingCarUp();
                    }
                    else
                    {
                        RotateCarHorizontally();
                        CarRotatedPosition=4;
                        MovingCarLeft();
                    }
                }

            }
        }
        void checkStopageSign()
        {
           if(CarCoordinates[0] > 588 && CarCoordinates[0] < 589) //If the car meets STOP sign
           {
                StopTheCar();
                if( getStopageTime() ) //Make sure it waited for 2 seconds:
                {
                    StartTheCar();
                }
            }
        }
        void setRouteStartCoordinates()
        {
            switch(routeNumber)
            {
                case 1:{
                    CarCoordinates[0] = 20.1;
                    CarCoordinates[1] = 14.3;
                    CarCoordinates[2] = 20.1;
                    CarCoordinates[7] = 14.3;
                    CarRotatedPosition = 1; // 1. means heading to the top of the screen.
                    RotateCarVertically();
                    break;
                }
                case 2:{
                    CarCoordinates[0] = 10.1;
                    CarCoordinates[1] = 324.3;
                    CarCoordinates[2] = 10.1;
                    CarCoordinates[7] = 324.3;
                    CarRotatedPosition = 2; // 2. means heading to the right of the screen.
                    RotateCarHorizontally();
                    break;
                }
                case 3:{
                    CarCoordinates[0] = 940.1;
                    CarCoordinates[1] = 354.3;
                    CarCoordinates[2] = 940.1;
                    CarCoordinates[7] = 354.3;
                    CarRotatedPosition = 4; // 4. means heading to the left of the screen.
                    RotateCarHorizontally();
                    break;
                }
                case 4:{
                    CarCoordinates[0] = 560.1;
                    CarCoordinates[1] = 11.3;
                    CarCoordinates[2] = 560.1;
                    CarCoordinates[7] = 11.3;
                    CarRotatedPosition = 1;
                    RotateCarVertically();
                    break;
                }
                case 5:{
                    CarCoordinates[0] = 960.1;
                    CarCoordinates[1] = 560.3;
                    CarCoordinates[2] = 960.1;
                    CarCoordinates[7] = 560.3;
                    CarRotatedPosition = 4;
                    RotateCarHorizontally();
                    break;
                }
                case 6:
                case 7:
                case 8:
                    {
                    CarCoordinates[0] = 20.1;
                    CarCoordinates[1] = 14.3;
                    CarCoordinates[2] = 20.1;
                    CarCoordinates[7] = 14.3;
                    CarRotatedPosition = 1; // 1. means heading to the top of the screen.
                    RotateCarVertically();
                    break;
                }
                case 9:
                case 10:
                case 11:
                case 12:
                {
                    CarCoordinates[0] = 10.1;
                    CarCoordinates[1] = 524.3;
                    CarCoordinates[2] = 10.1;
                    CarCoordinates[7] = 524.3;
                    CarRotatedPosition = 2;
                    RotateCarHorizontally();
                    break;
                }
                case 13:
                case 14: {
                    CarCoordinates[0] = 960.1;
                    CarCoordinates[1] = 560.3;
                    CarCoordinates[2] = 960.1;
                    CarCoordinates[7] = 560.3;
                    CarRotatedPosition = 4; // 4. means heading to the right of the screen.
                    RotateCarHorizontally();
                    break;
                }
                case 15:
                case 16:
                case 17:
                case 18:
                case 19:
                {
                    CarCoordinates[0] = 530.1;
                    CarCoordinates[1] = 560.3;
                    CarCoordinates[2] = 530.1;
                    CarCoordinates[7] = 560.3;
                    CarRotatedPosition = 3; // 3. means heading to the bottom of the screen.
                    RotateCarVertically();
                    break;
                }
            }
        }
        void addTimeGaps(vector <Route> &cars, const unsigned int routeNumber)
        {
            /*This function will be used to add time gaps between cars following the same route.
            This will avoid car overlapping.*/
            int gap=2;
            for (unsigned int i=0; i<cars.size(); i++)
            {
                if(uniqueID != cars[i].uniqueID)
                {
                    if(routeNumber==1 || (routeNumber>5 && routeNumber<9) ) //for 1, 6, 7,8
                    {
                        if (cars[i].getRouteNumber() == 1 || (cars[i].getRouteNumber() > 5 &&
                             cars[i].getRouteNumber() < 9) )
                        {
                            cars[i].setTimeGap(gap);
                        }
                    }
                    else if(routeNumber > 1 && routeNumber < 5) //for 2,3,4
                    {
                        if (cars[i].getRouteNumber() == routeNumber )
                        {
                            cars[i].setTimeGap(gap);
                        }
                    }
                    else if(routeNumber>8 && routeNumber<13) //for 9,10,11,12
                    {
                        if (cars[i].getRouteNumber() > 8 &&  cars[i].getRouteNumber() < 13)
                        {
                            cars[i].setTimeGap(gap);
                        }
                    }
                    else if( routeNumber==5 || (routeNumber > 12 && routeNumber < 15) ) //for 5,13,14
                    {
                        if (cars[i].getRouteNumber() == 5 || (cars[i].getRouteNumber() > 12 &&  cars[i].getRouteNumber() < 15) )
                        {
                            cars[i].setTimeGap(gap);
                        }
                    }
                    else if(routeNumber>14 || routeNumber < 20) //for 17.18.19
                    {
                        if (cars[i].getRouteNumber() > 14 &&  cars[i].getRouteNumber() < 20)
                        {
                            cars[i].setTimeGap(gap);
                        }
                    }
                }
            }
        }
};

#endif // ROUTE_H
