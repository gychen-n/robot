/*********************************************************************
* Software License Agreement (BSD License)
*K
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
#include <sound_play/SoundRequest.h>
#include <sound_play/sound_play.h>
#include <vector>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "xfyun_waterplus/IATSwitch.h"
#include <waterplus_map_tools/GetWaypointByName.h>
#include <time.h>
using namespace std;

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;
static ros::Publisher spk_pub;
static ros::ServiceClient clientIAT;
static xfyun_waterplus::IATSwitch srvIAT;
static ros::ServiceClient cliGetWPName;
static waterplus_map_tools::GetWaypointByName srvName;
static int nPersonCount = 0;

//有限状态机
#define STATE_READY 0
#define STATE_WAIT_ENTR 1
#define STATE_GOTO_RECO 2
#define STATE_WAIT_RECO 3
#define STATE_GOTO_LOCATION 4
#define STATE_ACTION 5
#define STATE_WAIT_ASK 6
#define STATE_CONFIRM 7
#define STATE_GOTO_SECOND 8
#define STATE_GOTO_THIRD 9
#define STATE_GOTO_CMD 10
#define STATE_ANSWER 11
#define STATE_GOTO_EXIT 12
#define STATE_GOTO_LOCATION2 13

int taskflag = 0;					 //任务标志 1-回答问题  2- 回答小问题 3-follow 4-抓取物品 5-找东西
char strOrder[100];					 //记录听到的命令
char obj[20];						 //记录物品
char pla[20];						 //记录地点
char pla2[20];						 //记录拆分地点2
static int nState = STATE_WAIT_ENTR; //程序启动时初始状态
//static int nState = STATE_WAIT_ASK;

//识别关键词
static vector<string> arKWPerson;
static vector<string> arKWConfirm;
static vector<string> arKWPlacement;
static vector<string> arKWPlacement2;
static vector<string> arKWObject;
static vector<string> arKWAction1;
static vector<string> arKWAction2;
static vector<string> arKWQuestion;
static vector<string> arKWSmallQuestion;

static void Init_keywords()
{
	//人名关键词(根据比赛前一天提供的人名列表进行修改)
	arKWPerson.push_back("jack");
	arKWPerson.push_back("tom");
	arKWPerson.push_back("lucy");
	arKWPerson.push_back("david");
	//地点关键词1
	arKWPlacement.push_back("living room");
	arKWPlacement.push_back("Living room");
	arKWPlacement.push_back("kitchen");
	arKWPlacement.push_back("Kitchen");
	arKWPlacement.push_back("bedroom");
	arKWPlacement.push_back("Bedroom");
	arKWPlacement.push_back("dining room");
	arKWPlacement.push_back("Dining room");

	//地点关键词2
	// arKWPlacement2.push_back("kitchen shelf");
	// arKWPlacement2.push_back("tea table");
	// arKWPlacement2.push_back("fridge");
	// arKWPlacement2.push_back("kitchen counter");
	// arKWPlacement2.push_back("cupboard");
	// arKWPlacement2.push_back("");
	// arKWPlacement2.push_back("bar");
	// arKWPlacement2.push_back("couch table");
	// arKWPlacement2.push_back("dinner table");
	// arKWPlacement2.push_back("sofa");
	// arKWPlacement2.push_back("left cooking bench");
	// arKWPlacement2.push_back("right cooking bench");
	// arKWPlacement2.push_back("desk");
	// arKWPlacement2.push_back("bed");
	// arKWPlacement2.push_back("bookcase");
	// arKWPlacement2.push_back("sink");
	arKWPlacement2.push_back("me");
	arKWPlacement2.push_back("Me");
	arKWPlacement2.push_back("fridge");
	arKWPlacement2.push_back("Fridge");
	arKWPlacement2.push_back("left cooking bench");
	arKWPlacement2.push_back("Left cooking bench");
	arKWPlacement2.push_back("kitchen shelf");
	arKWPlacement2.push_back("Kitchen shelf");
	arKWPlacement2.push_back("right cooking bench");
	arKWPlacement2.push_back("Right cooking bench");
	arKWPlacement2.push_back("cupboard");
	arKWPlacement2.push_back("Cupboard");
	arKWPlacement2.push_back("sink");
	arKWPlacement2.push_back("Sink");
	arKWPlacement2.push_back("long sofa");
	arKWPlacement2.push_back("Long sofa");
	arKWPlacement2.push_back("left end table");
	arKWPlacement2.push_back("Left end table");
	arKWPlacement2.push_back("round table");
	arKWPlacement2.push_back("Round table");
	arKWPlacement2.push_back("left short sofa");
	arKWPlacement2.push_back("Left short sofa");
	arKWPlacement2.push_back("right short sofa");
	arKWPlacement2.push_back("Right short sofa");
	arKWPlacement2.push_back("right end table");
	arKWPlacement2.push_back("Right end table");
	arKWPlacement2.push_back("TV bench");
	arKWPlacement2.push_back("Tv bench");
	arKWPlacement2.push_back("tv bench");
	arKWPlacement2.push_back("computer desk");
	arKWPlacement2.push_back("Computer desk");
	arKWPlacement2.push_back("dresser");
	arKWPlacement2.push_back("Dresser");
	arKWPlacement2.push_back("bookcase");
	arKWPlacement2.push_back("Bookcase");
	arKWPlacement2.push_back("bed");
	arKWPlacement2.push_back("Bed");
	arKWPlacement2.push_back("desk");
	arKWPlacement2.push_back("Desk");
	arKWPlacement2.push_back("dining shelf");
	arKWPlacement2.push_back("Dining shelf");
	arKWPlacement2.push_back("dining table");
	arKWPlacement2.push_back("Dining table");
	arKWPlacement2.push_back("food table");
	arKWPlacement2.push_back("Food table");


	//物品关键词
	// arKWObject.push_back("Toothpaste");
	// arKWObject.push_back("Sponge");
	// arKWObject.push_back("apple");
	// arKWObject.push_back("lemon");
	// arKWObject.push_back("pear");
	// arKWObject.push_back("peer");
	// arKWObject.push_back("pair");
	// arKWObject.push_back("cream");
	// arKWObject.push_back("milk tea");
	// arKWObject.push_back("biscuits");
	// arKWObject.push_back("napkin");
	// arKWObject.push_back("chips");
	// arKWObject.push_back("trip");
	// arKWObject.push_back("oreo");
	// arKWObject.push_back("area");
	// arKWObject.push_back("grean tea");
	// arKWObject.push_back("pepsi");
	// arKWObject.push_back("herbal tea");
	// arKWObject.push_back("porridge");
	arKWObject.push_back("drinks");
	arKWObject.push_back("milk tea");
	arKWObject.push_back("cola");
	arKWObject.push_back("water");
	arKWObject.push_back("sprite");
	arKWObject.push_back("beer");
	arKWObject.push_back("red bull");
	arKWObject.push_back("lemon tea");
	arKWObject.push_back("herbal tea");
	arKWObject.push_back("food");
	arKWObject.push_back("biscuits");
	arKWObject.push_back("chips");
	arKWObject.push_back("cleaning stuff");
	arKWObject.push_back("bath cream");
	arKWObject.push_back("toothpaste");
	arKWObject.push_back("napkins");
	//物品关键词大写
	arKWObject.push_back("Drinks");
	arKWObject.push_back("Milk tea");
	arKWObject.push_back("Cola");
	arKWObject.push_back("Water");
	arKWObject.push_back("Sprite");
	arKWObject.push_back("Beer");
	arKWObject.push_back("Red bull");
	arKWObject.push_back("Lemon tea");
	arKWObject.push_back("Herbal tea");
	arKWObject.push_back("Food");
	arKWObject.push_back("Biscuits");
	arKWObject.push_back("Chips");
	arKWObject.push_back("Cleaning stuff");
	arKWObject.push_back("Bath cream");
	arKWObject.push_back("Toothpaste");
	arKWObject.push_back("Napkins");



	//行为关键词1
	arKWAction1.push_back("look for");
	arKWAction1.push_back("Look for");
	arKWAction1.push_back("find");
	arKWAction1.push_back("Find");
	arKWAction1.push_back("take");
	arKWAction1.push_back("tell");
	arKWAction1.push_back("navigate");
	arKWAction1.push_back("Navigate");
	arKWAction1.push_back("reach");
	arKWAction1.push_back("go");
	arKWAction1.push_back("Go");
	arKWAction1.push_back("Reach");
	//行为关键词2
	arKWAction2.push_back("answer");
	arKWAction2.push_back("follow");
	arKWAction2.push_back("followed");
	arKWAction2.push_back("carry");
	arKWAction2.push_back("Carry");
	arKWAction2.push_back("take");
	arKWAction2.push_back("Take");
	arKWAction2.push_back("tell");
	arKWAction2.push_back("get");
	arKWAction2.push_back("Get");
	arKWAction2.push_back("look for");
	arKWAction2.push_back("Grasp");
	arKWAction2.push_back("grasp");
	arKWAction2.push_back("speak");
	arKWAction2.push_back("say");
	arKWAction2.push_back("Get into");

	//yes or no
	arKWConfirm.push_back("yes");
	arKWConfirm.push_back("Yes");
	arKWConfirm.push_back("Yeah");
	arKWConfirm.push_back("no");
	arKWConfirm.push_back("No");

	//小问题关键词
	arKWSmallQuestion.push_back("your team");
	arKWSmallQuestion.push_back("time");
	arKWSmallQuestion.push_back("date"); //tomorrow today
	arKWSmallQuestion.push_back("day");	 //tomorrow today
	arKWSmallQuestion.push_back("your name");

	//问题关键词
	arKWQuestion.push_back("German"); //count von zeppelin
	arKWQuestion.push_back("german");
	arKWQuestion.push_back("president"); //george washington
	arKWQuestion.push_back("reserved");	 //pork
	arKWQuestion.push_back("emperor");
	arKWQuestion.push_back("Titanic"); //belfast
	arKWQuestion.push_back("titanic");
	arKWQuestion.push_back("Victoria"); //nine children
	arKWQuestion.push_back("victoria");
	arKWQuestion.push_back("French"); //louis XIV
	arKWQuestion.push_back("french");
	arKWQuestion.push_back("Empire"); //hadrians wall
	arKWQuestion.push_back("empire");
	arKWQuestion.push_back("film");		  //Alien
	arKWQuestion.push_back("first king"); //Leopold I
	arKWQuestion.push_back("former");	  //new amsterdam
	arKWQuestion.push_back("Paris");	  //lutetia
	arKWQuestion.push_back("paris");
	arKWQuestion.push_back("capital");		//melbourne
	arKWQuestion.push_back("fossils");		//paleontology
	arKWQuestion.push_back("dragon flies"); //mosquitoes
	arKWQuestion.push_back("Dragon flies");
	arKWQuestion.push_back("centimeters"); //fleas
	arKWQuestion.push_back("european");	   //wisent
	arKWQuestion.push_back("snake");	   //eel fish
	arKWQuestion.push_back("contain");	   //maple
	arKWQuestion.push_back("tiger");	   //siberian tiger
	arKWQuestion.push_back("born");		   //six toes
	arKWQuestion.push_back("house");	   //number 742
	arKWQuestion.push_back("restricted");  //peknese
	arKWQuestion.push_back("director");	   //quentin tarantino
	arKWQuestion.push_back("Herbie");	   //fifty-three
	arKWQuestion.push_back("herbie");
	arKWQuestion.push_back("James");	 //austin powers
	arKWQuestion.push_back("james");	 //austin powers
	arKWQuestion.push_back("commander"); //captain picard
	arKWQuestion.push_back("actress");	 //whoopi goldberg
	arKWQuestion.push_back("domain");	 //the .be domain
	arKWQuestion.push_back("MP three");	 //kbps
	arKWQuestion.push_back("mp three");
	arKWQuestion.push_back("computing");  //random access memory
	arKWQuestion.push_back("earth");	  //yuri gagarin
	arKWQuestion.push_back("hemisphere"); //the northern hemisphere
	arKWQuestion.push_back("cobalt");	  //bule
	arKWQuestion.push_back("rubber");	  //goodyear
	arKWQuestion.push_back("look");		  //telescope
	arKWQuestion.push_back("intensity");  //candela
	arKWQuestion.push_back("barometer");  //torricelli
	arKWQuestion.push_back("in space");	  //alan shepard
	arKWQuestion.push_back("brother");	  //montgolfier
	arKWQuestion.push_back("engine");	  //james watt
	arKWQuestion.push_back("by");		  //the typewriter
	arKWQuestion.push_back("metal");	  //aluminium
	arKWQuestion.push_back("primary");	  //bule, yellow and red
	arKWQuestion.push_back("nearest");	  //mercury
	arKWQuestion.push_back("Great");	  //6259 kilometers
	arKWQuestion.push_back("great");
	arKWQuestion.push_back("digits"); //99999
	arKWQuestion.push_back("human");  //clavicle
	arKWQuestion.push_back("South");  //venezuela
	arKWQuestion.push_back("south");
	arKWQuestion.push_back("feature"); //four stars
	arKWQuestion.push_back("white");   //pink
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

/*static void Speak(string inStr) {
	sound_play::SoundRequest sp;
	sp.sound = sound_play::SoundRequest::SAY;
	sp.command = sound_play::SoundRequest::PLAY_ONCE;
	sp.arg = inStr;
	spk_pub.publish(sp);
}
*/
// static void Speak(string  inStr) {
// 	int n;
// 	char order[100];
// 	sprintf(order,"rosrun sound_play say.py  \"%s\"",inStr.c_str()); //格式化命令，替换
// 	printf("order:%s\n",order);
// 	n=system(order);
// }
void sleepok(int t)
{
	sleep(t);
}
static void Speak(string inStr)
{
	sound_play::SoundClient sc;
	sc.say(inStr);
	sleepok(2);
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

static int nOpenCount = 0;
void EntranceCB(const std_msgs::String::ConstPtr &msg)
{
	//ROS_WARN("[WhoIsWho EntranceCB] - %s",msg->data.c_str());
	string strDoor = msg->data;
	if (strDoor == "door open")
	{
		nOpenCount++;
	}
	else
	{
		nOpenCount = 0;
	}
}

static bool bGotoExit = false;
void KeywordCB(const std_msgs::String::ConstPtr &msg)
{
	ROS_WARN("[GPSR KeywordCB] - %s", msg->data.c_str());
	string strListen = msg->data;

	if (nState == STATE_WAIT_RECO)
	{
		string location = FindWord(strListen, arKWPlacement);
		string location2 = FindWord(strListen, arKWPlacement2);
		string action1 = FindWord(strListen, arKWAction1);
		string action2 = FindWord(strListen, arKWAction2);
		string object = FindWord(strListen, arKWObject);
		//从听到的句子里找地点行为物品
		if ((location.length() > 0 && action1.length() > 0) || (location.length() > 0 && action2.length() > 0))
		{
			nState = STATE_CONFIRM;
			//strcpy(pla,location.c_str());
			string strRepeat = strListen;
			printf("order - %s \n", strRepeat.c_str());
			printf("include placement1 - %s \n", location.c_str());
			printf("include placement2 - %s \n", location2.c_str());
			printf("include action 1 - %s \n", action1.c_str());
			printf("include action 2 - %s \n", action2.c_str());
			printf("include object - %s \n", object.c_str());
			Speak(strRepeat);

			strcpy(strOrder, strRepeat.c_str());
			usleep(5 * 1000 * 1000);
			Speak("Please confirm!");
			usleep(2 * 1000 * 1000);
			/*if(action=="answer")//回答问题
			{
				taskflag=1;
			}
			else if(action=="look for"||action=="find") //找东西或者找人
			{

			}
			usleep(3*1000*1000);*/
		}
		else if ((location2.length() > 0 && action1.length() > 0) || (location2.length() > 0 && action2.length() > 0))
		{
			nState = STATE_CONFIRM;
			//strcpy(pla,location.c_str());
			string strRepeat = strListen;
			printf("order - %s \n", strRepeat.c_str());
			printf("include placement1 - %s \n", location.c_str());
			printf("include placement2 - %s \n", location2.c_str());
			printf("include action 1 - %s \n", action1.c_str());
			printf("include action 2 - %s \n", action2.c_str());
			printf("include object - %s \n", object.c_str());
			Speak(strRepeat);

			strcpy(strOrder, strRepeat.c_str());
			usleep(5 * 1000 * 1000);
			Speak("Please confirm!");
			usleep(2 * 1000 * 1000);
		}
	}
	if (nState == STATE_CONFIRM)
	{
		string confirm = FindWord(strListen, arKWConfirm);
		if (confirm == "yes" || confirm == "Yes" || confirm == "Yeah")
		{
			nState = STATE_GOTO_LOCATION;
			string strRepeat = strOrder;
			FILE *fp1 = NULL; //定义文件指针
			int m;
			fp1 = fopen("/home/robot/gpsrorder/order.txt", "w");
			m = fprintf(fp1, "Order : %s\n", strOrder);
			fclose(fp1);
			string location = FindWord(strRepeat, arKWPlacement);
			string location2 = FindWord(strRepeat, arKWPlacement2);
			string action1 = FindWord(strRepeat, arKWAction1);
			string action2 = FindWord(strRepeat, arKWAction2);
			string object = FindWord(strRepeat, arKWObject);
			printf("order - %s \n", strRepeat.c_str());
			printf("include placement1 - %s \n", location.c_str());
			printf("include placement2 - %s \n", location2.c_str());
			printf("include action 1 - %s \n", action1.c_str());
			printf("include action 2 - %s \n", action2.c_str());
			printf("include object - %s \n", object.c_str());
			if (location.length() > 0)
			{
				strcpy(pla, location.c_str());
			}

			else
			{
				strcpy(pla, location2.c_str());
			}

			if (strstr(strOrder, "answer") != NULL)
			{
				taskflag = 1; //回答大问题
			}
			else if (strstr(strOrder, "say") != NULL || strstr(strOrder, "tell") != NULL || strstr(strOrder, "speak") != NULL)
			{
				taskflag = 2; //回答小问题
			}
			else if (action2 == "follow" || action2 == "followed")
			{
				taskflag = 3; //follow
				//以“and”为分隔符，分隔两个地点
				char *p = NULL, *q = NULL;
				char Band[100], Aand[100];
				int i = 0;
				p = strOrder;				 //首部
				q = strstr(strOrder, "and"); //and前
				while (p < q)
				{
					Band[i++] = *p++;
				} //保存and前的地点到Band
				q = strOrder;
				q = q + strlen(strOrder) + 1; //获取长度
				p = strstr(strOrder, "and");
				i = 0;
				while (p < q)
				{
					Aand[i++] = *p++;
				} //保存and后的地点到Aand
				string str1 = Band;
				string str2 = Aand;
				string location1 = FindWord(str1, arKWPlacement); //找第一个地点在pla中
				if (location1.length() > 0)
				{
					strcpy(pla, location1.c_str());
				}
			}
			else if (strstr(strOrder, "look for") != NULL || strstr(strOrder, "find") != NULL || strstr(strOrder, "Get into") != NULL)
			{
				taskflag = 5; //找东西
			}
			else if (action2 == "take" || action2 == "Take" || action2 == "carry" || action2 == "Carry" || action2 == "get" || action2 == "Get" || action2 == "grasp" || action2 == "Grasp")
			{
				taskflag = 4; //拿东西
				//识别完毕,关闭语音识别
				srvIAT.request.active = false;
				clientIAT.call(srvIAT);
				//以“and”为分隔符，分隔两个地点
				char *p = NULL, *q = NULL;
				char Band[100], Aand[100];
				int i = 0;
				p = strOrder;				 //首部
				q = strstr(strOrder, "and"); //and前
				while (p < q)
				{
					Band[i++] = *p++;
				} //保存and前的地点到Band
				q = strOrder;
				q = q + strlen(strOrder) + 1; //获取长度
				p = strstr(strOrder, "and");
				i = 0;
				while (p < q)
				{
					Aand[i++] = *p++;
				} //保存and后的地点到Aand
				string str1 = Band;
				string str2 = Aand;
				//printf("%s\n", str2.c_str());
				string location1 = FindWord(str1, arKWPlacement); //找第一个地点在pla中
				if (location1.length() > 0)
				{
					if (strstr(str1.c_str(), "kitchen shelf") != NULL)
						strcpy(pla, "kitchen shelf");
					else if (strstr(str1.c_str(), "bedroom") != NULL)
						strcpy(pla, "bedroom");
					else if (strstr(str1.c_str(), "left cooking table") != NULL)
						strcpy(pla, "left cooking table");
					else if (strstr(str1.c_str(), "right cooking table") != NULL)
						strcpy(pla, "right cooking table");
					else if (strstr(str1.c_str(), "long sofa") != NULL)
						strcpy(pla, "long sofa");
					else if (strstr(str1.c_str(), "left end table") != NULL)
						strcpy(pla, "left end table");
					else if (strstr(str1.c_str(), "right end table") != NULL)
						strcpy(pla, "right end table");
					else if (strstr(str1.c_str(), "left short sofa") != NULL)
						strcpy(pla, "left short sofa");
					else if (strstr(str1.c_str(), "right short sofa") != NULL)
						strcpy(pla, "right short sofa");
					else if (strstr(str1.c_str(), "computer desk") != NULL)
						strcpy(pla, "computer desk");
					else if (strstr(str1.c_str(), "dining shelf") != NULL)
						strcpy(pla, "dining shelf");
					else if (strstr(str1.c_str(), "dining table") != NULL)
						strcpy(pla, "dining table");
					else if (strstr(str1.c_str(), "food table") != NULL)
						strcpy(pla, "food table");
					else
						strcpy(pla, location1.c_str());
				}
				else
				{
					location1 = FindWord(str1, arKWPlacement2); //找第一个地点在pla2中
					strcpy(pla, location1.c_str());
				}

				string location2 = FindWord(str2, arKWPlacement); //找第二个地点在pla中
				if (location2.length() > 0)
				{
					if (strstr(str2.c_str(), "kitchen shelf") != NULL)
						strcpy(pla2, "kitchen shelf");
					else if (strstr(str2.c_str(), "bedroom") != NULL)
						strcpy(pla2, "bedroom");
					else if (strstr(str2.c_str(), "left cooking table") != NULL)
						strcpy(pla2, "left cooking table");
					else if (strstr(str2.c_str(), "right cooking table") != NULL)
						strcpy(pla2, "right cooking table");
					else if (strstr(str1.c_str(), "long sofa") != NULL)
						strcpy(pla, "long sofa");
					else if (strstr(str2.c_str(), "left end table") != NULL)
						strcpy(pla2, "left end table");
					else if (strstr(str2.c_str(), "right end table") != NULL)
						strcpy(pla2, "right end table");
					else if (strstr(str2.c_str(), "left short sofa") != NULL)
						strcpy(pla2, "left short sofa");
					else if (strstr(str2.c_str(), "right short sofa") != NULL)
						strcpy(pla2, "right short sofa");
					else if (strstr(str2.c_str(), "computer desk") != NULL)
						strcpy(pla2, "computer desk");
					else if (strstr(str2.c_str(), "dining shelf") != NULL)
						strcpy(pla2, "dining shelf");
					else if (strstr(str2.c_str(), "dining table") != NULL)
						strcpy(pla2, "dining table");
					else if (strstr(str2.c_str(), "food table") != NULL)
						strcpy(pla2, "food table");
					else
						strcpy(pla2, location2.c_str());
				}
				else
				{
					string location2 = FindWord(str2, arKWPlacement2); //找第二个地点在pla2中
					strcpy(pla2, location2.c_str());
				}

				printf("pla:%s\n", pla);

				printf("pla2:%s\n", pla2);
			}
			else
				printf("action error");
		}

		if (confirm == "no" || confirm == "No")
		{
			Speak("ok,tell me the command again");
			nState = STATE_WAIT_RECO;
		}
	}

	if (nState == STATE_WAIT_ASK)
	{
		string question = FindWord(strListen, arKWQuestion);
		//从听到的句子里找问题关键词
		if (question.length() > 0)
		{
			//nState = STATE_ANSWER;
			FILE *fp1 = NULL; //定义文件指针
			int m;
			fp1 = fopen("/home/robot/gpsrorder/order.txt", "a+");
			printf("%s\n",strListen.c_str());
			m = fprintf(fp1, "question: %s\n", strListen.c_str());

			if (question == "German" || question == "german")
			{
				Speak("Count von Zeppelin");
				printf("Count von Zeppelin");
				m = fprintf(fp1, "answer: %s\n", "Count von Zeppelin");
			}
			else if (question == "president")
			{
				Speak("George Washington");
				printf("George Washington");
				m = fprintf(fp1, "answer: %s\n", "George Washington");
			}
			else if (question == "reserved")
			{
				Speak("Pork");
				printf("Pork");
				m = fprintf(fp1, "answer: %s\n", "Pork");
			}
			else if (question == "Titanic" || question == "titanic")
			{
				Speak("Belfast");
				printf("Belfast");
				m = fprintf(fp1, "answer: %s\n", "Belfast");
			}
			else if (question == "Victoria" || question == "victoria")
			{
				Speak("Nine children");
				printf("Nine children");
				m = fprintf(fp1, "answer: %s\n", "Nine children");
			}
			else if (question == "French" || question == "french")
			{
				Speak("Louis XIV");
				printf("Louis XIV");
				m = fprintf(fp1, "answer: %s\n", "Louis XIV");
			}
			else if (question == "empire" || question == "Empire")
			{
				Speak("Hadrians wall");
				printf("Hadrians wall");
				m = fprintf(fp1, "answer: %s\n", "Hadrians wall");
			}
			else if (question == "film")
			{
				Speak("Alien");
				printf("Alien");
				m = fprintf(fp1, "answer: %s\n", "Alien");
			}
			else if (question == "first king")
			{
				Speak("Leopold I");
				printf("Leopold I");
				m = fprintf(fp1, "answer: %s\n", "Leopold I");
			}
			else if (question == "former")
			{
				Speak("New Amsterdam");
				printf("New Amsterdam");
				m = fprintf(fp1, "answer: %s\n", "New Amsterdam");
			}
			else if (question == "Paris" || question == "paris")
			{
				Speak("Lutetia");
				printf("Lutetia");
				m = fprintf(fp1, "answer: %s\n", "Lutetia");
			}
			else if (question == "capital")
			{
				Speak("Melbourne");
				printf("Melbourne");
				m = fprintf(fp1, "answer: %s\n", "Melbourne");
			}
			else if (question == "fossils")
			{
				Speak("Paleontology");
				printf("Paleontology");
				m = fprintf(fp1, "answer: %s\n", "Paleontology");
			}
			else if (question == "dragon flies" || question == "dragon flies")
			{
				Speak("Mosquitoes");
				printf("Mosquitoes");
				m = fprintf(fp1, "answer: %s\n", "Mosquitoes");
			}
			else if (question == "centimeters")
			{
				Speak("Fleas");
				printf("Fleas");
				m = fprintf(fp1, "answer: %s\n", "Fleas");
			}
			else if (question == "european")
			{
				Speak("Wisent");
				printf("Wisent");
				m = fprintf(fp1, "answer: %s\n", "Wisent");
			}
			else if (question == "snake")
			{
				Speak("Eel fish");
				printf("Eel fish");
				m = fprintf(fp1, "answer: %s\n", "Eel fish");
			}
			else if (question == "contain")
			{
				Speak("Maple");
				printf("Maple");
				m = fprintf(fp1, "answer: %s\n", "Maple");
			}
			else if (question == "tiger")
			{
				Speak("Siberian tiger");
				printf("Siberian tiger");
				m = fprintf(fp1, "answer: %s\n", "Siberian tiger");
			}
			else if (question == "born")
			{
				Speak("Six toes");
				printf("Six toes");
				m = fprintf(fp1, "answer: %s\n", "Six toes");
			}
			else if (question == "house")
			{
				Speak("Number 742");
				printf("Number 742");
				m = fprintf(fp1, "answer: %s\n", "Number 742");
			}
			else if (question == "restricted")
			{
				Speak("Pekinese");
				printf("Pekinese");
				m = fprintf(fp1, "answer: %s\n", "Pekinese");
			}
			else if (question == "director")
			{
				Speak("Quentin Tarantino");
				printf("Quentin Tarantino");
				m = fprintf(fp1, "answer: %s\n", "Quentin Tarantino");
			}
			else if (question == "Herbie" || question == "herbie")
			{
				Speak("Fifty-three");
				printf("Fifty-three");
				m = fprintf(fp1, "answer: %s\n", "Fifty-three");
			}
			else if (question == "James" || question == "james")
			{
				Speak("Austin Powers");
				printf("Austin Powers");
				m = fprintf(fp1, "answer: %s\n", "Austin Powers");
			}
			else if (question == "commander")
			{
				Speak("Captain Picard");
				printf("Captain Picard");
				m = fprintf(fp1, "answer: %s\n", "Captain Picard");
			}
			else if (question == "actress")
			{
				Speak("Whoopi Goldberg");
				printf("Whoopi Goldberg");
				m = fprintf(fp1, "answer: %s\n", "Whoopi Goldberg");
			}
			else if (question == "domain")
			{
				Speak("The .be domain");
				printf("The .be domain");
				m = fprintf(fp1, "answer: %s\n", "The .be domain");
			}
			else if (question == "MP three" || question == "mp three")
			{
				Speak("Kbps");
				printf("Kbps");
				m = fprintf(fp1, "answer: %s\n", "Kbps");
			}
			else if (question == "computing")
			{
				Speak("Random Access Memory");
				printf("Random Access Memory");
				m = fprintf(fp1, "answer: %s\n", "Random Access Memory");
			}
			else if (question == "earth")
			{
				Speak("Yuri Gagarin");
				printf("Yuri Gagarin");
				m = fprintf(fp1, "answer: %s\n", "Yuri Gagarin");
			}
			else if (question == "hemisphere")
			{
				Speak("The northern hemisphere");
				printf("The northern hemisphere");
				m = fprintf(fp1, "answer: %s\n", "The northern hemisphere");
			}
			else if (question == "cobalt")
			{
				Speak("Blue");
				printf("Blue");
				m = fprintf(fp1, "answer: %s\n", "Blue");
			}
			else if (question == "rubber")
			{
				Speak("Good year");
				printf("Good year");
				m = fprintf(fp1, "answer: %s\n", "Good year");
			}
			else if (question == "look")
			{
				Speak("Telescope");
				printf("Telescope");
				m = fprintf(fp1, "answer: %s\n", "Telescope");
			}
			else if (question == "intensity")
			{
				Speak("Candela");
				printf("Candela");
				m = fprintf(fp1, "answer: %s\n", "Candela");
			}
			else if (question == "barometer")
			{
				Speak("Torricelli");
				printf("Torricelli");
				m = fprintf(fp1, "answer: %s\n", "Torricelli");
			}
			else if (question == "in space")
			{
				Speak("Alan Shepard");
				printf("Alan Shepard");
				m = fprintf(fp1, "answer: %s\n", "Alan Shepard");
			}
			else if (question == "brother")
			{
				Speak("Montgolfier");
				printf("Montgolfier");
				m = fprintf(fp1, "answer: %s\n", "Montgolfier");
			}
			else if (question == "engine")
			{
				Speak("James Watt");
				printf("James Watt");
				m = fprintf(fp1, "answer: %s\n", "James Watt");
			}
			else if (question == "by")
			{
				Speak("The typewriter");
				printf("The typewriter");
				m = fprintf(fp1, "answer: %s\n", "The typewriter");
			}
			else if (question == "metal")
			{
				Speak("Aluminium");
				printf("Aluminium");
				m = fprintf(fp1, "answer: %s\n", "Aluminium");
			}
			else if (question == "primary")
			{
				Speak("Blue, yellow and red");
				printf("Blue, yellow and red");
				m = fprintf(fp1, "answer: %s\n", "Blue, yellow and red");
			}
			else if (question == "nearest")
			{
				Speak("Mercury");
				printf("Mercury");
				m = fprintf(fp1, "answer: %s\n", "Mercury");
			}
			else if (question == "Great" || question == ".c_str()great")
			{
				Speak("6259 kilometers");
				printf("6259 kilometers");
				m = fprintf(fp1, "answer: %s\n", "6259 kilometers");
			}
			else if (question == "digits")
			{
				Speak("99999");
				printf("99999");
				m = fprintf(fp1, "answer: %s\n", "99999");
			}
			else if (question == "human")
			{
				Speak("Clavicle");
				printf("Clavicle");
				m = fprintf(fp1, "answer: %s\n", "Clavicle");
			}
			else if (question == "South" || question == "south")
			{
				Speak("Venezuela");
				printf("Venezuela");
				m = fprintf(fp1, "answer: %s\n", "Venezuela");
			}
			else if (question == "feature")
			{
				Speak("Four stars");
				printf("Four stars");
				m = fprintf(fp1, "answer: %s\n", "Four stars");
			}
			else if (question == "white")
			{
				Speak("Pink");
				printf("Pink");
				m = fprintf(fp1, "answer: %s\n", "Pink");
			}
			else
			{
				printf("error");
			}
			fclose(fp1);

			usleep(3 * 1000 * 1000);
			nState = STATE_GOTO_EXIT;
			bGotoExit = true;
		}
	}
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "wpb_home_gpsr");
	Init_keywords();

	ros::NodeHandle n;
	ros::Subscriber sub_sr = n.subscribe("/xfyun/iat", 10, KeywordCB);
	ros::Subscriber sub_ent = n.subscribe("/wpb_home/entrance_detect", 10, EntranceCB);
	clientIAT = n.serviceClient<xfyun_waterplus::IATSwitch>("xfyun_waterplus/IATSwitch");
	cliGetWPName = n.serviceClient<waterplus_map_tools::GetWaypointByName>("/waterplus/get_waypoint_name");
	spk_pub = n.advertise<sound_play::SoundRequest>("/robotsound", 20);

	ROS_INFO("[main] wpb_home_GPSR");
	ros::Rate r(10);
	Speak("");
	while (ros::ok())
	{

		if (nState == STATE_WAIT_ENTR)
		{
			bool bArrived = Goto("me");
			// bool bArrived = true; //test
			usleep(3 * 1000 * 1000);
			if (bArrived == true)
			{
				Speak("Tell me the command.");
				nState = STATE_WAIT_RECO;
				srvIAT.request.active = true;
				srvIAT.request.duration = 12;
				clientIAT.call(srvIAT);
			}
		}
		if (nState == STATE_GOTO_LOCATION)
		{

			string placestr = pla;
			bool fArrived1, fArrived2, fArrived3;
			fArrived1 = true;
			printf("\n\nGOTO:%s\n\n", placestr.c_str());
			if (fArrived1 == true)
			{
				fArrived2 = Goto(placestr);
				// fArrived2 = true;
				if (fArrived2 == true)
				{
					Speak("I am in the " + placestr);
					usleep(1 * 1000 * 1000);

					if (taskflag == 1)
					{ //大问题
						Speak("I have found you");
						usleep(1 * 1000 * 1000);
						Speak("Please tell me the question");
						nState = STATE_WAIT_ASK;
						bGotoExit = true;
					}
					else if (taskflag == 2)
					{ //小问题
						//识别完毕,关闭语音识别
						srvIAT.request.active = false;
						clientIAT.call(srvIAT);
						//time
						char T[40];
						int i = 3;
						time_t timep;
						time(&timep);
						printf("%s", ctime(&timep));
						strcpy(T, ctime(&timep));
						int len = strlen(T);
						T[len + 1] = '\0';
						puts(T);

						char *p = strtok(T, " ");
						while (i--)
						{
							//printf("%s\n",p);
							p = strtok(NULL, " ");
						}
						printf("%s\n", p);
						string now_time = p;

						//判断小问题
						string strRepeat = strOrder;
						string smallQ = FindWord(strRepeat, arKWSmallQuestion);
						FILE *fp1 = NULL; //定义文件指针
						int m;
						fp1 = fopen("/home/robot/gpsrorder/order.txt", "a+");
						printf("smallQ: %s\n", smallQ.c_str());
						printf("order: %s\n", strOrder);
						if (smallQ == "your team")
						{
							Speak("SDJU team");
							printf("SDJU team");
							m = fprintf(fp1, "answer: %s\n", "SDJU team");
							//sleep(3*1000*1000);
						}
						else if (smallQ == "your name")
						{
							Speak("my name is Doctor");
							printf("my name is Doctor");
							m = fprintf(fp1, "answer: %s\n", "my name is Doctor");
							//sleep(3*1000*1000);
						}
						else if (smallQ == "time")
						{
							Speak("It's " + now_time + " now");
							printf("It's %s now\n",now_time.c_str());
							m = fprintf(fp1, "answer: It's %s now\n",now_time.c_str());
							//sleep(3*1000*1000);
						}
						else if (smallQ == "day")
						{
							if (strstr(strOrder, "tomorrow") != NULL)
							{
								Speak("tomorrow is Sunday");
								printf("tomorrow is Sunday");
							m = fprintf(fp1, "answer: %s\n", "tomorrow is Sunday");
								//sleep(3*1000*1000);
							}
							else
							{
								Speak("today is Saturday");
								printf("today is Saturday");
							m = fprintf(fp1, "answer: %s\n", "today is Saturday");
								//sleep(3*1000*1000);
							}
						}
						else if (smallQ == "date")
						{
							if (strstr(strOrder, "tomorrow") != NULL)
							{
								Speak("tomorrow is November 22, 2020");
								printf("tomorrow is November 22, 2020");
							m = fprintf(fp1, "answer: %s\n", "tomorrow is November 22, 2020");
								//sleep(3*1000*1000);
							}
							else
							{
								Speak("today is November 21, 2020");
								printf("today is November 21, 2020");
							m = fprintf(fp1, "answer: %s\n", "today is November 21, 2020");
								//sleep(1*1000*1000);
							}
						}
						else
							printf("SmallQuestion Error!");
						fclose(fp1);
						nState = STATE_GOTO_EXIT;
						bGotoExit = true;
					}
					else if (taskflag == 3)
					{ //follow

						int n;
						n = system("bash /home/robot/bash/11.sh");
						nState = STATE_GOTO_EXIT;
						bGotoExit = true;
					}
					else if (taskflag == 4)
					{ //拿东西
						int n;
						// n = system("bash /home/robot/zhua.sh");
						usleep(5 * 1000 * 1000);

						nState = STATE_GOTO_LOCATION2;
					}
					else if (taskflag == 5)
					{ //找东西
						// fArrived3 = true;
						// if (strstr(strOrder, "kitchen") != NULL)
						// 	fArrived3 = Goto("cupboard"); //去小地点
						// 	printf("Goto cupboard\n");
						// else if (strstr(strOrder, "bedroom") != NULL)
						// 	fArrived3 = Goto("bookcase"); //去小地点
						// 	printf("Goto bookcase\n");
						// else if (strstr(strOrder, "dining room") != NULL)
						// 	fArrived3 = Goto("dining table"); //去小地点
						// 	printf("Goto dining table\n");

						//识别完毕,关闭语音识别

						if (fArrived3 == true)
						{
							string strRepeat = strOrder;
							string object = FindWord(strRepeat, arKWObject);
							string answer = object + " is found";
							printf("\n\n%s\n\n",answer.c_str());
							Speak(answer);
							printf("\n%s\n",answer.c_str());
							usleep(4 * 1000 * 1000);
							srvIAT.request.active = false;
							clientIAT.call(srvIAT);
							nState = STATE_GOTO_EXIT;
							bGotoExit = true;
						}
					}
				}
			}
		}
		if (nState == STATE_GOTO_LOCATION2)
		{
			int n;
			bool fArrived;
			string placestr2 = pla2;
			printf("pla2:%s\n", pla2);

			fArrived = Goto(placestr2);
			// fArrived = true;
			if (fArrived == true)
			{
				Speak("Here you are!");
				// n = system("bash /home/robot/fang.sh");

				nState = STATE_GOTO_EXIT;
				bGotoExit = true;
			}
		}

		/*if(nState == STATE_GOTO_CMD) {

			bool fArrived = Goto("cmd");
			if(fArrived == true) {
				Speak("I am back");
				usleep(2*1000*1000);
				printf("%d\n",times);
				if(times==0) {
					times++;
					nState = STATE_GOTO_SECOND;
				} else if(times==1) {
					times++;
					nState = STATE_GOTO_THIRD;
				} else {
					Speak("I am leaving to exit");
					nState = STATE_GOTO_EXIT;
				}


			}

		}*/

		if (nState == STATE_GOTO_EXIT && bGotoExit == true)
		{

			bGotoExit = false;

			//识别完毕,关闭语音识别
			srvIAT.request.active = false;
			clientIAT.call(srvIAT);

			//Speak("I am leaving to exit.");
			system("cd /home/robot/gpsrorder && sh gpsr_pdf.sh");
			//Goto("exit");
		}
		ros::spinOnce();
		r.sleep();
	}
	return 0;
}
