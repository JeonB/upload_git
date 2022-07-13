#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include <iostream>

#define RAD2DEG(x) ((x)*180./M_PI)
int set_degree = 0;

void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    int count = scan->scan_time / scan->time_increment;
    printf("[YDLIDAR INFO]: I heard a laser scan %s[%d]:\n", scan->header.frame_id.c_str(), count);
    printf("[YDLIDAR INFO]: angle_range : [%f, %f]\n", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));
    
    for(int i = 0; i < count; i++) {
        float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
	if(degree > -set_degree && degree< set_degree)
        printf("[YDLIDAR INFO]: angle-distance : [%f, %f, %i]\n", degree, scan->ranges[i], i);
    }
}

int main(int argc, char **argv)
{
    using std::cin;
    ros::init(argc, argv, "ydlidar_client");
    ros::NodeHandle n;
    printf("Set degree -> ");
    cin >> set_degree;
    ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("/scan", 1000, scanCallback);
    ros::spin();

    return 0;
}