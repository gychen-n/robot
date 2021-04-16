/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2017-2020, Waterplus http://www.6-robot.com

*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the WaterPlus nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  FOOTPRINTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/
/* @author K                                             */
#include <ros/ros.h>
#include <std_msgs/String.h>
//#include "wpb_home_tutorials/Follow.h"
#include "xfyun_waterplus/IATSwitch.h"
#include <geometry_msgs/Twist.h>
#include <sound_play/SoundRequest.h>
//#include "wpb_home_tutorials/Follow.h"
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseStamped.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <tf/transform_listener.h>
#include <waterplus_map_tools/GetWaypointByName.h>
#include <waterplus_map_tools/Waypoint.h>
#include <sound_play/sound_play.h>
#include <unistd.h>

using namespace std;

#define STATE_READY 0
#define STATE_FOLLOW 1
#define STATE_ASK 2
#define STATE_GOTO 3
#define STATE_GRAB 4
#define STATE_COMEBACK 5
#define STATE_PASS 6
//#define STATE_GOTO_LOCATION 7
#define STATE_END 8

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
static string strGoto;
static sound_play::SoundRequest spk_msg;
static ros::Publisher spk_pub;
static ros::Publisher vel_pub;
static string strToSpeak = "";
static string strKeyWord = "";
static ros::ServiceClient clientIAT;
static xfyun_waterplus::IATSwitch srvIAT;
static ros::ServiceClient cliGetWPName;
static waterplus_map_tools::GetWaypointByName srvName;
static ros::Publisher add_waypoint_pub;
static ros::ServiceClient follow_start;
static ros::ServiceClient follow_stop;
static ros::ServiceClient follow_resume;
//static wpb_home_tutorials::Follow srvFlw;
static ros::Publisher behaviors_pub;
static std_msgs::String behavior_msg;

static ros::Subscriber grab_result_sub;
static ros::Subscriber pass_result_sub;
static bool bGrabDone;
static bool bPassDone;

static int nState = STATE_READY;
static int times = 0; //去拿东西的次数
static int asktimes = 0;
static int nDelay = 0;

static vector<string> arKeyword;
static vector<string> arStop;
// 添加航点关键词
void InitKeyword()
{
	arKeyword.push_back("start");
	arKeyword.push_back("herbal tea");	 //新加的
	arKeyword.push_back("lemon tea");	 //新加的
	arKeyword.push_back("water");		 //新加的
	arKeyword.push_back("cola");		 //新加的
	arKeyword.push_back("red bull");	 //新加的
	arKeyword.push_back("bath cream");	 //新加的
	arKeyword.push_back("best cream");	 //新加的
	arKeyword.push_back("milk tea");	 //新加的
	arKeyword.push_back("toothpaste");	 //新加的
	arKeyword.push_back("biscuits");	 //新加的
	arKeyword.push_back("chips");		 //新加的
	arKeyword.push_back("sprite");		 //新加的
	arKeyword.push_back("beer");		 //新加的
	arKeyword.push_back("napkins");		 //新加的
	arKeyword.push_back("bill");		 //新加的(beer)
	arKeyword.push_back("to space");	 //新加的(toothpaste)
	arKeyword.push_back("surprise");	 //新加的(sprite)
	arKeyword.push_back("spirit");		 //新加的(sprite)
	arKeyword.push_back("sport");		 //新加的(sprite)
	arKeyword.push_back("spread");		 //新加的(sprite)
	arKeyword.push_back("not the case"); //新加的(napkins)
	arKeyword.push_back("base case");	 //新加的(biscuits)
	arKeyword.push_back("biscuit");		 //新加的(biscuits)
	arKeyword.push_back("cool");		 //新加的(cola)

	arKeyword.push_back("bathroom");  //新加的(bath cream)
	arKeyword.push_back("bus cream"); //新加的(bath cream)
	arKeyword.push_back("icecream");  //新加的(bath cream)
	arKeyword.push_back("her tea");	  //新加的(herbal tea)
	arKeyword.push_back("her body");  //新加的(herbal tea)
	arKeyword.push_back("napkin");	  //新加的(napkins)

	//大写
	// arKeyword.push_back("Herbal tea"); //新加的
	// arKeyword.push_back("Lemon tea");  //新加的
	// arKeyword.push_back("Water");	   //新加的
	// arKeyword.push_back("Cola");	   //新加的
	// arKeyword.push_back("Red bull");   //新加的
	// arKeyword.push_back("Best cream"); //新加的
	// arKeyword.push_back("Milk tea");   //新加的
	// arKeyword.push_back("Toothpaste"); //新加的
	// arKeyword.push_back("Biscuits");   //新加的
	// arKeyword.push_back("Chips");	   //新加的
	// arKeyword.push_back("Sprite");	   //新加的
	// arKeyword.push_back("Beer");	   //新加的
	// arKeyword.push_back("Napkins");	   //新加的
	// arKeyword.push_back("Bill");	   //新加的

	arStop.push_back("stop");
	arStop.push_back("Stop");
}

static string FindWord(string inSentence, vector<string> &arWord)
{
	string strRes = "";
	int nNum = arWord.size();
	for (int i = 0; i < nNum; i++)
	{
		int tmpIndex = inSentence.find(arWord[i]);
		if (tmpIndex >= 0)
		{
			strRes = arWord[i];
			break;
		}
	}
	return strRes;
}
// 从句子里找arKeyword里存在的关键词
static string FindKeyword(string inSentence)
{
	string res = "";
	int nSize = arKeyword.size();
	for (int i = 0; i < nSize; i++)
	{
		int nFindIndex = inSentence.find(arKeyword[i]);
		if (nFindIndex >= 0)
		{
			res = arKeyword[i];
			break;
		}
	}
	return res;
}

// 将机器人当前位置保存为新航点
void AddNewWaypoint(string inStr)
{
	tf::TransformListener listener;
	tf::StampedTransform transform;
	try
	{
		listener.waitForTransform("/map", "/base_link", ros::Time(0), ros::Duration(10.0));
		listener.lookupTransform("/map", "/base_link", ros::Time(0), transform);
	}
	catch (tf::TransformException &ex)
	{
		ROS_ERROR("[lookupTransform] %s", ex.what());
		return;
	}

	float tx = transform.getOrigin().x();
	float ty = transform.getOrigin().y();
	tf::Stamped<tf::Pose> p = tf::Stamped<tf::Pose>(tf::Pose(transform.getRotation(), tf::Point(tx, ty, 0.0)), ros::Time::now(), "map");
	geometry_msgs::PoseStamped new_pos;
	tf::poseStampedTFToMsg(p, new_pos);

	waterplus_map_tools::Waypoint new_waypoint;
	new_waypoint.name = inStr;
	new_waypoint.pose = new_pos.pose;
	add_waypoint_pub.publish(new_waypoint);

	ROS_WARN("[New Waypoint] %s ( %.2f , %.2f )", new_waypoint.name.c_str(), tx, ty);
}

// // 语音说话
// void Speak(string inStr) {
// 	spk_msg.arg = inStr;
// 	spk_pub.publish(spk_msg);
// }

// static void Speak(string inStr)
// {
// 	int tmp;
// 	char order[100];
// 	sprintf(order, "rosrun sound_play say.py '%s'", inStr.c_str());
// 	printf("order:%s\n", order);
// 	int n = system(order);
// }
static void Speak(string inStr)
{
	sound_play::SoundClient sc;
	sc.say(inStr);
	sleep(2);
}

static bool Goto(string inStr)
{
	string strGoto = inStr;

	srvName.request.name = strGoto;
	if (cliGetWPName.call(srvName))
	{
		std::string name = srvName.response.name;
		float x = srvName.response.pose.position.x;
		float y = srvName.response.pose.position.y;
		ROS_INFO("Get_wp_name: name = %s (%.2f,%.2f)", strGoto.c_str(), x, y);

		MoveBaseClient ac("move_base", true);
		if (!ac.waitForServer(ros::Duration(5.0)))
		{
			ROS_INFO("The move_base action server is no running. action abort...");
			return false;
		}
		else
		{
			move_base_msgs::MoveBaseGoal goal;
			goal.target_pose.header.frame_id = "map";
			goal.target_pose.header.stamp = ros::Time::now();
			goal.target_pose.pose = srvName.response.pose;
			ac.sendGoal(goal);
			ac.waitForResult();
			if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
			{
				ROS_INFO("Arrived at %s!", strGoto.c_str());
				return true;
			}
			else
			{
				ROS_INFO("Failed to get to %s ...", strGoto.c_str());
				return false;
			}
		}
	}
	else
	{
		ROS_ERROR("Failed to call service GetWaypointByName");
		return false;
	}
}
// 跟随模式开关
static void FollowSwitch(bool inActive, float inDist)
{
	/*if(inActive == true)
	{
	    srvFlw.request.thredhold = inDist;
	    if (!follow_start.call(srvFlw))
	    {
	        ROS_WARN("[CActionManager] - follow start failed...");
	    }
	}
	else
	{
	    if (!follow_stop.call(srvFlw))
	    {
	        ROS_WARN("[CActionManager] - failed to stop following...");
	    }
	}*/

	//开follow
}

// 物品抓取模式开关
static void GrabSwitch(bool inActive)
{
	if (inActive == true)
	{
		behavior_msg.data = "grab start";
		behaviors_pub.publish(behavior_msg);
	}
	else
	{
		behavior_msg.data = "grab stop";
		behaviors_pub.publish(behavior_msg);
	}
}

// 物品递给开关
static void PassSwitch(bool inActive)
{
	if (inActive == true)
	{
		behavior_msg.data = "pass start";
		behaviors_pub.publish(behavior_msg);
	}
	else
	{
		behavior_msg.data = "pass stop";
		behaviors_pub.publish(behavior_msg);
	}
}

// 语音识别结果处理函数
void KeywordCB(const std_msgs::String::ConstPtr &msg)
{
	ROS_WARN("------ Keyword = %s ------", msg->data.c_str());
	if (nState == STATE_FOLLOW)
	{
		// 从识别结果句子中查找物品（航点）关键词
		string strKeyword = FindKeyword(msg->data);
		int nLenOfKW = strlen(strKeyword.c_str());
		if (nLenOfKW > 0)
		{
			// 发现物品（航点）关键词
			//加入best cream假设，将bath cream赋值给strKeyword,下同
			if (strKeyword == "best cream")
			{
				strKeyword = "bath cream";
			}
			if (strKeyword == "bill")
			{
				strKeyword = "beer";
			}
			if (strKeyword == "to space")
			{
				strKeyword = "toothpaste";
			}
			if (strKeyword == "not the case")
			{
				strKeyword = "napkins";
			}
			if (strKeyword == "spread" || strKeyword == "spirit" || strKeyword == "sport" || strKeyword == "surprise")
			{
				strKeyword = "sprite";
			}
			if (strKeyword == "base case")
			{
				strKeyword = "biscuits";
			}
			if (strKeyword == "biscuit")
			{
				strKeyword = "biscuits";
			}
			if (strKeyword == "cool")
			{
				strKeyword = "cola";
			}
			if (strKeyword == "bathroom" || strKeyword == "bus cream" || strKeyword == "icecream")
			{
				strKeyword = "bathcream";
			}
			if (strKeyword == "her tea" || strKeyword == "her body")
			{
				strKeyword = "herbal tea";
			}
			if (strKeyword == "napkin")
			{
				strKeyword = "napkins";
			}

			AddNewWaypoint(strKeyword);
			string strSpeak = strKeyword + " I have memoried. Next one";
			Speak(strSpeak);
		}

		// 停止跟随的指令
		//int nFindIndex = msg->data.find("Stop");
		string stop = FindWord(msg->data, arStop);
		int nFindIndex = strlen(stop.c_str());
		int n;
		if (nFindIndex > 0)
		{ /*stop、保存地图、保存点信息(xml)、关follow、关creat_map和开导航、转圈定位、将点插入到地图中、再开始询问*/
			//FollowSwitch(false, 0);
			AddNewWaypoint("master");
			//save the map

			Speak("OK Stop!"); //听到ok人再走动
			printf("OK Stop!\n");
			n = system("bash /home/robot/savemap.sh");
			//usleep(0.5 * 1000 * 1000);

			//save the point (xml)
			n = system("bash /home/robot/savepoint.sh");
			//usleep(0.5 * 1000 * 1000);

			//stop follow and video1
			n = system("bash /home/robot/kill_follow.sh");
			//usleep(0.5 * 1000 * 1000);

			//stop mapping and start navigation
			n = system("bash /home/robot/kill_mapping.sh");
			//usleep(0.5 * 1000 * 1000);

			// //insert the points to map
			// n = system("bash /home/robot/add_waypoint.sh");
			// Speak("insert the points to map!");
			// usleep(2 * 1000 * 1000);
			n = system("bash /home/robot/navigation.sh");
			usleep(1.5 * 1000 * 1000);

			//take turn转两圈，矫正，
			n = system("sh /home/robot/zhuanquan.sh");

			//n = system("sh /home/robot/kill_all_action.sh");//daixie
			//calibration the start point
			//n = system("sh /home/robot/calibration.sh &");
			//usleep(2*1000*1000);
			//n = system("sh /home/robot/kill_all_action.sh");
			//take turn
			//n = system("sh /home/robot/turn_left.sh");
			//usleep(18*1000*1000);
			//n = system("sh /home/robot/back.sh");
			//usleep(2*1000*100);
			//Speak("What do you want?");
			//usleep(3*1000*1000);
			//00
			//n = system("sh /home/robot/stop.sh");
			//n = system("sh /home/robot/kill_all_action.sh");
			//usleep(3*1000*1000);
			nState = STATE_ASK;
			Speak("state ask!");

			// usleep(1 * 1000 * 1000);

			//nDelay = 0;
		}
	}
	//询问要哪些东西
	if (nState == STATE_ASK)
	{
		if (asktimes < 1)
		{
			Speak("OK.What do you want?");
			asktimes++;
		}

		// printf("OK.What do you want?\n");

		// 从识别结果句子中查找物品（航点）关键词
		string strKeyword = FindKeyword(msg->data);
		int nLenOfKW = strlen(strKeyword.c_str());
		if (nLenOfKW > 0)
		{
			// 发现物品（航点）关键词
			if (strKeyword == "best cream")
			{
				strKeyword = "bath cream";
			}
			if (strKeyword == "bill")
			{
				strKeyword = "beer";
			}
			if (strKeyword == "to space")
			{
				strKeyword = "toothpaste";
			}
			if (strKeyword == "not the case")
			{
				strKeyword = "napkins";
			}

			if (strKeyword == "base case")
			{
				strKeyword = "biscuits";
			}
			if (strKeyword == "biscuit")
			{
				strKeyword = "biscuits";
			}
			if (strKeyword == "surprise" || strKeyword == "spirit" || strKeyword == "sport" || strKeyword == "spread")
			{
				strKeyword = "sprite";
			}
			if (strKeyword == "cool")
			{
				strKeyword = "cola";
			}
			if (strKeyword == "bathroom" || strKeyword == "bus cream" || strKeyword == "icecream")
			{
				strKeyword = "bathcream";
			}
			if (strKeyword == "her tea" || strKeyword == "her body")
			{
				strKeyword = "herbal tea";
			}
			if (strKeyword == "napkin")
			{
				strKeyword = "napkins";
			}

			strGoto = strKeyword;
			string strSpeak = strKeyword + "  OK";

			Speak(strSpeak);
			printf(" OK. I will go to get it for you.\n");

			nState = STATE_GOTO;
		}
	}
}

// 物品抓取状态
void GrabResultCallback(const std_msgs::String::ConstPtr &res)
{
	int nFindIndex = 0;
	nFindIndex = res->data.find("done");
	if (nFindIndex >= 0)
	{
		bGrabDone = true;
	}
}

// 物品递给状态
void PassResultCallback(const std_msgs::String::ConstPtr &res)
{
	int nFindIndex = 0;
	nFindIndex = res->data.find("done");
	if (nFindIndex >= 0)
	{
		bPassDone = true;
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "wpb_home_shopping"); /*是否要改wpb_home_shopping*/

	ros::NodeHandle n;
	ros::Subscriber sub_sr = n.subscribe("/xfyun/iat", 10, KeywordCB); //  /*是否全程都在开着？？*/
	//follow_start = n.serviceClient<wpb_home_tutorials::Follow>("wpb_home_follow/start");
	//follow_stop = n.serviceClient<wpb_home_tutorials::Follow>("wpb_home_follow/stop");
	//follow_resume = n.serviceClient<wpb_home_tutorials::Follow>("wpb_home_follow/resume");
	cliGetWPName = n.serviceClient<waterplus_map_tools::GetWaypointByName>("/waterplus/get_waypoint_name");
	add_waypoint_pub = n.advertise<waterplus_map_tools::Waypoint>("/waterplus/add_waypoint", 1);
	spk_pub = n.advertise<sound_play::SoundRequest>("/robotsound", 20);
	spk_msg.sound = sound_play::SoundRequest::SAY;
	spk_msg.command = sound_play::SoundRequest::PLAY_ONCE;
	vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	clientIAT = n.serviceClient<xfyun_waterplus::IATSwitch>("xfyun_waterplus/IATSwitch");
	behaviors_pub = n.advertise<std_msgs::String>("/wpb_home/behaviors", 30);
	grab_result_sub = n.subscribe<std_msgs::String>("/wpb_home/grab_result", 30, &GrabResultCallback);
	pass_result_sub = n.subscribe<std_msgs::String>("/wpb_home/pass_result", 30, &PassResultCallback);

	InitKeyword();

	ROS_WARN("[main] wpb_home_shopping");
	ros::Rate r(30);
	srvIAT.request.active = true;
	srvIAT.request.duration = 5; //每隔5秒发一次提示音
	clientIAT.call(srvIAT);

	while (ros::ok())
	{
		// 1、刚启动，准备
		if (nState == STATE_READY)
		{
			// 启动后延迟一段时间然后开始跟随
			nDelay++;
			// ROS_WARN("[STATE_READY] - nDelay = %d", nDelay);
			if (nDelay > 100)
			{
				AddNewWaypoint("start");
				nDelay = 0;
				nState = STATE_FOLLOW;
			}
		}

		// 2、跟随阶段(放到语音处理函数里面去了)
		// if (nState == STATE_FOLLOW)
		// {
		// 	// if (nDelay == 0)
		// 	// {
		// 	// 	FollowSwitch(true, 0.7);
		// 	// }
		// 	//nDelay++;
		// }

		// if (nState == STATE_GOTO_LOCATION)
		// {
		// 	bool fArrived = Goto(strGoto);
		// 	if (fArrived == true)
		// 	{
		// 		Speak("OK. I am taking it.");
		// 		nState = STATE_GRAB;
		// 		nDelay = 0;
		// 	}
		// }
		// 4、导航去指定航点
		if (nState == STATE_GOTO)
		{
			srvName.request.name = strGoto;
			if (cliGetWPName.call(srvName))
			{
				std::string name = srvName.response.name;
				float x = srvName.response.pose.position.x;
				float y = srvName.response.pose.position.y;
				ROS_INFO("[STATE_GOTO] Get_wp_name = %s (%.2f,%.2f)", strGoto.c_str(), x, y);

				MoveBaseClient ac("move_base", true);
				if (!ac.waitForServer(ros::Duration(5.0)))
				{
					ROS_INFO("The move_base action server is no running. action abort...");
				}
				else
				{
					move_base_msgs::MoveBaseGoal goal;
					goal.target_pose.header.frame_id = "map";
					goal.target_pose.header.stamp = ros::Time::now();
					goal.target_pose.pose = srvName.response.pose;
					ac.sendGoal(goal);
					ac.waitForResult();
					if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
					{
						ROS_INFO("Arrived at %s!", strGoto.c_str());
						Speak("arrive");
						printf("OK. I am taking it.\n");
						asktimes = 0;
						nState = STATE_GRAB;
						//nDelay = 0;
					}
					else
					{
						ROS_INFO("Failed to get to %s ...", strGoto.c_str());
						Speak("Failed to go to the waypoint.");
						//nState = STATE_ASK;
					}
				}
			}
			else
			{
				ROS_ERROR("Failed to call service GetWaypointByName");
				Speak("There is no this waypoint.");
				//nState = STATE_ASK;
			}
		}

		// 5、抓取物品
		if (nState == STATE_GRAB)
		{
			// if (nDelay == 0)
			// {
			// 	//bGrabDone = false;
			// 	//GrabSwitch(true);

			// 	int n;

			// 	n = system("sh /home/robot/turn_table.sh");
			// 	usleep(5 * 1000 * 1000);
			// 	//start yolo
			// 	n = system("sh /home/robot/get_things.sh");
			// 	//n=system("sh /home/robot/zhua.sh");
			// 	usleep(20 * 1000 * 1000);
			// 	n = system("sh /home/robot/kill_all_action.sh");
			// 	bGrabDone = true;
			// }
			//nDelay++;

			// if (bGrabDone == true)
			// 	// {
			// 	// 	//GrabSwitch(false);

			// 	// }

			//int n = system("bash /home/robot/zhua.sh");
			//usleep(8 * 1000 * 1000);
			//Speak("I got it.");
			nState = STATE_COMEBACK;
		}

		// 6、抓完物品回来
		if (nState == STATE_COMEBACK)
		{
			/*int e;
			bool fArrived = Goto("last");
			if(fArrived == true) {
				e = system("sh /home/robot/back.sh");
				usleep(2*1000*1000);
				//turn right position
				e = system("sh /home/robot/turn_back.sh");
				usleep(8*1000*1000);
			}*/
			srvName.request.name = "master";
			if (cliGetWPName.call(srvName))
			{
				std::string name = srvName.response.name;
				float x = srvName.response.pose.position.x;
				float y = srvName.response.pose.position.y;
				ROS_INFO("[STATE_COMEBACK] Get_wp_name = %s (%.2f,%.2f)", strGoto.c_str(), x, y);

				MoveBaseClient ac("move_base", true);
				if (!ac.waitForServer(ros::Duration(5.0)))
				{
					ROS_INFO("The move_base action server is no running. action abort...");
				}
				else
				{
					move_base_msgs::MoveBaseGoal goal;
					goal.target_pose.header.frame_id = "map";
					goal.target_pose.header.stamp = ros::Time::now();
					goal.target_pose.pose = srvName.response.pose;
					ac.sendGoal(goal);
					ac.waitForResult();

					if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
					{
						ROS_INFO("Arrived at %s!", strGoto.c_str());
						Speak("Hi. I'm back.");
						nState = STATE_PASS;
						//nDelay = 0;
					}
					else
					{
						ROS_INFO("Failed to get to %s ...", strGoto.c_str());
						Speak("Failed to go to the master.");
						//nState = STATE_ASK;
					}
				}
			}
			else
			{
				ROS_ERROR("Failed to call service GetWaypointByName");
				Speak("There is no waypoint named master.");
				//nState = STATE_ASK;
			}
		}

		// 7、将物品给主人
		if (nState == STATE_PASS)
		{
			/* if(nDelay == 0)
			 {
			     bPassDone = false;
			     PassSwitch(true);
			 }
			 nDelay ++;*/
			bPassDone = true;
			if (bPassDone == true)
			{
				//PassSwitch(false);
				//int n;
				//n = system("bash /home/robot/fang.sh");
				//usleep(3 * 1000 * 1000);
				//Speak("OK. What do you want next?");
				printf("OK. What do you want next?\n");
				times++;
				if (times < 2)
				{
					nState = STATE_ASK;
				}
				else
				{
					nState = STATE_END;
				}
			}
		}
		if (nState == STATE_END)
		{
			Speak("Mission accomplished");
			printf("Mission accomplished\nMission accomplished\n");
		}

		ros::spinOnce();
		r.sleep();
	}

	return 0;
}
