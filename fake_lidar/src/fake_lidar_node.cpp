#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

int main(int argc, char** argv){
    ros::init(argc, argv, "fake_lidar");

    ros::NodeHandle n;
    ros::Publisher scan_pub = n.advertise<sensor_msgs::LaserScan>("scan", 10);

    unsigned int num_readings = 180;
    double laser_frequency = 1;
    double ranges[num_readings];
    double intensities[num_readings];
    sensor_msgs::LaserScan scan;
    bool test = true;

    ros::Rate r(1.0);
    while(n.ok())
    {
        //generate some fake data for our laser scan
        for(unsigned int i = 0; i < num_readings; ++i)
        {
            ranges[i] = 5;
            intensities[i] = 0;
        }
        
        if(test == true)
        {
            ranges[0] = 6;
        }
        else
        {
            ranges[num_readings-1] = 4;
        }
        
    
        ros::Time scan_time = ros::Time::now();

        //populate the LaserScan message        
        scan.header.stamp = scan_time;
        scan.header.frame_id = "laser_frame";
        if(test == true)
        {
            scan.angle_min = -1.571;
            scan.angle_max = 1.553;
            scan.angle_increment = (3.142 / num_readings);
            test = false;
        }
        else
        {
            scan.angle_min = 1.553;
            scan.angle_max = -1.571;
            scan.angle_increment = -(3.142 / num_readings);   
            test = true;     
        }
        scan.time_increment = (1 / laser_frequency) / (num_readings);
        scan.range_min = 0.0;
        scan.range_max = 30.0;

        scan.ranges.resize(num_readings);
        scan.intensities.resize(num_readings);
        for(unsigned int i = 0; i < num_readings; ++i)
        {
            scan.ranges[i] = ranges[i];
            scan.intensities[i] = intensities[i];
        }

        scan_pub.publish(scan);        
        r.sleep();
    }
}

