//Include standard ROS library
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>	//sending Command to AR.Drone

//#include <std_msgs/Empty.h>			//for takeoff and landing masih ragu ini tuh bener ga librarynya
//#include <ardrone_autonomy/Navdata.h>
//#include <ardrone_autonomy/ardrone_sdk.h>
//#include <ardrone_autonomy/teleop_twist.h>


//Standard C++ library
#include <iostream>
#include <cstdlib>
using namespace std;


//ROS TF library
//#include <tf/transform_broadcaster.h>


class ARDroneDriver
{
private:

//declare node handle 
 ros::NodeHandle nh_;
 
 //publishing to base control command
 ros::Publisher cmd_vel_pub_;
 ros::Publisher x;
 ros::Publisher msgs;  //publishing navigation data control for ardrone takeoff and landing
 
public:
 //Initialization for ROS
 ARDroneDriver(ros::NodeHandle &nh)
 {
	nh_ = nh;
	//set up for cmd_vel command control topic
	cmd_vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/ardrone/cmd_vel",1);
	msgs = nh_.advertise<std_msgs::Empty>("/ardrone/std_msgs",1);
	/* msgs = nh_.advertise<std_msgs::Empty>("/ardrone/ardrone1/takeoff",1,true); */
 }
	
//Looping forever while sending driver command on keyboard input
bool driveKeyboard();
{
	std::cout << "Ketik perintah dan tekan enter. "
	"gunakan 'w' untuk maju, 'a' untuk kekiri, 'd' untuk ke kanan, dan 'q' untuk exit";
	//cout << "ketik perintah dan tekan enter. "
	//			"gunakan 'w' untuk maju, 'a' untuk ke kiri, 'd' untuk ke kanan, dan 'q' untuk exit";

	//sending data through cmd_vel twist command
	geometry_msgs::Twist fn;
	
	
	//std_msgs::Empty ff;
	
	char cmd[50];
	while(nh_.ok())
	{
		std::cin.getline(cmd, 50);
		if(cmd[0]!='w' && cmd[0]!='a' && cmd[0]!='d' && cmd[0]!='q' && cmd[0]!='p' && cmd[0]!='o')
		{
			std::cout <<"perintah tidak diketahui: " << cmd << "\n";
			continue;
		}
		
		fn.linear.x = fn.linear.y = fn.linear.z = 0;
		
		//to make AR.Drone move forward
		if(cmd[0] == 'w')
		{
			fn.linear.x = 1.0;
		}
		
		//to make AR.Drone yawing to left and pitch forward simultaneously
		else if(cmd[0] == 'a')
		{
			fn.linear.z = 1.0;
			fn.linear.x = 1.0;
		}
		
		//to make yawing to right and pitching forward simultaneously
		else if(cmd[0] == 'd')
		{
			fn.linear.z = -1.0;
			fn.linear.x = 1.0;
		}
		
		//to make AR.Drone flying like a 8-pattern movement not in manuver
		else if(cmd[0] == 'p')
		{
			fn.linear.z = 1.0; fn.linear.x = 1.0;
			fn.linear.z = 1.0; fn.linear.x = 1.0;
			fn.linear.z = 1.0; fn.linear.x = 1.0;
			fn.linear.z = 1.0; fn.linear.x = 1.0;
			
			fn.linear.z = -1.0; fn.linear.x = 1.0;
			fn.linear.z = -1.0; fn.linear.x = 1.0;
			fn.linear.z = -1.0; fn.linear.x = 1.0;
			fn.linear.z = -1.0; fn.linear.x = 1.0;
		}
		
		//move like through an O-pattern circuit
		else if(cmd[0] == 'o')
		{
			fn.linear.z = 1.0; fn.linear.x = 1.0;
			fn.linear.z = 1.0; fn.linear.x = 1.0;
			fn.linear.z = 1.0; fn.linear.x = 1.0;
			fn.linear.z = 1.0; fn.linear.x = 1.0;
		}
		
		//terminated the topic
		else if(cmd[0] == 'q')
		{
			break;
		}
		
		//publish the command
		cmd_vel_pub_.publish(fn);
		
		ros::spinOnce();
		loop_rate.sleep();
	}
	
	return true;
	
	
}; // ending of the while program

} //ending of the class


int main (int argc, char **argv)
{
	//Initialization ROS, and set up node
	ros::init(argc, argv, "ardrone_script_commands");
	ros::Nodehandle nh;
	
	ARDroneDriver driver(nh);
	driver.driveKeyboard();
}
