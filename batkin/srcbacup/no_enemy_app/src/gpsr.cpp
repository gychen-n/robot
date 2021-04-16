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
	arKWPlacement.push_back("kitchen");
	arKWPlacement.push_back("bedroom");
	arKWPlacement.push_back("hallway");

	//地点关键词2
	arKWPlacement2.push_back("kitchen table");
	arKWPlacement2.push_back("tea table");
	arKWPlacement2.push_back("fridge");
	arKWPlacement2.push_back("kitchen counter");
	arKWPlacement2.push_back("cupboard");
	arKWPlacement2.push_back("trashbin");
	arKWPlacement2.push_back("bar");
	arKWPlacement2.push_back("couch table");
	arKWPlacement2.push_back("dinner table");
	arKWPlacement2.push_back("sofa");
	arKWPlacement2.push_back("left bedside table");
	arKWPlacement2.push_back("right bedside table");
	arKWPlacement2.push_back("desk");
	arKWPlacement2.push_back("bed");
	arKWPlacement2.push_back("bookcase");
	arKWPlacement2.push_back("hallway table");
	arKWPlacement2.push_back("me");
	arKWPlacement2.push_back("shelf");

	//物品关键词
	arKWObject.push_back("Toothpaste");
	arKWObject.push_back("Sponge");
	arKWObject.push_back("apple");
	arKWObject.push_back("lemon");
	arKWObject.push_back("pear");
	arKWObject.push_back("peer");
	arKWObject.push_back("pair");
	arKWObject.push_back("cream");
	arKWObject.push_back("milk tea");
	arKWObject.push_back("biscuits");
	arKWObject.push_back("napkin");
	arKWObject.push_back("chips");
	arKWObject.push_back("trip");
	arKWObject.push_back("oreo");
	arKWObject.push_back("area");
	arKWObject.push_back("grean tea");
	arKWObject.push_back("pepsi");
	arKWObject.push_back("herbal tea");
	arKWObject.push_back("porridge");
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
	arKWQuestion.push_back("German");
	arKWQuestion.push_back("president");
	arKWQuestion.push_back("Emperor");
	arKWQuestion.push_back("Titanic");
	arKWQuestion.push_back("Victoria");
	arKWQuestion.push_back("French");
	arKWQuestion.push_back("Empire");
	arKWQuestion.push_back("film");
	arKWQuestion.push_back("king of Belgium");
	arKWQuestion.push_back("former");
	arKWQuestion.push_back("Latin");
	arKWQuestion.push_back("capital");
	arKWQuestion.push_back("fossils");
	arKWQuestion.push_back("dragonflies");
	arKWQuestion.push_back("centimeters");
	arKWQuestion.push_back("Bison");
	arKWQuestion.push_back("snake");
	arKWQuestion.push_back("Canadian");
	arKWQuestion.push_back("species");
	arKWQuestion.push_back("Marilyn");
	arKWQuestion.push_back("house");
	arKWQuestion.push_back("restricted");
	arKWQuestion.push_back("director");
	arKWQuestion.push_back("Herbiev");
	arKWQuestion.push_back("parody");
	arKWQuestion.push_back("commander");
	arKWQuestion.push_back("actress");
	arKWQuestion.push_back("domain");
	arKWQuestion.push_back("MP3");
	arKWQuestion.push_back("Ram");
	arKWQuestion.push_back("earth");
	arKWQuestion.push_back("hemisphere");
	arKWQuestion.push_back("cobalt");
	arKWQuestion.push_back("vulcanized");
	arKWQuestion.push_back("look");
	arKWQuestion.push_back("intensity");
	arKWQuestion.push_back("barometer");
	arKWQuestion.push_back("in space");
	arKWQuestion.push_back("surname");
	arKWQuestion.push_back("engine");
	arKWQuestion.push_back("Henry");
	arKWQuestion.push_back("metal");
	arKWQuestion.push_back("primary");
	arKWQuestion.push_back("nearest");
	arKWQuestion.push_back("Great");
	arKWQuestion.push_back("digits");
	arKWQuestion.push_back("fractured");
	arKWQuestion.push_back("Venice");
	arKWQuestion.push_back("feature");
	arKWQuestion.push_back("white");
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
				printf("%s", str2.c_str());
				string location1 = FindWord(str1, arKWPlacement); //找第一个地点在pla中
				if (location1.length() > 0)
				{
					if (strstr(str1.c_str(), "kitchen table") != NULL)
						strcpy(pla, "kitchen table");
					else if (strstr(str1.c_str(), "kitchen counter") != NULL)
						strcpy(pla, "kitchen counter");
					else if (strstr(str1.c_str(), "hallway table") != NULL)
						strcpy(pla, "hallway table");
					else if (strstr(str1.c_str(), "bedroom") != NULL)
						strcpy(pla, "bedroom");
					else if (strstr(str1.c_str(), "left bedside table") != NULL)
						strcpy(pla, "left bedside table");
					else if (strstr(str1.c_str(), "right bedside table") != NULL)
						strcpy(pla, "right bedside table");
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
					if (strstr(str1.c_str(), "kitchen table") != NULL)
						strcpy(pla, "kitchen table");
					else if (strstr(str1.c_str(), "kitchen counter") != NULL)
						strcpy(pla, "kitchen counter");
					else if (strstr(str1.c_str(), "hallway table") != NULL)
						strcpy(pla, "hallway table");
					else if (strstr(str1.c_str(), "bedroom") != NULL)
						strcpy(pla, "bedroom");
					else if (strstr(str1.c_str(), "left bedside table") != NULL)
						strcpy(pla, "left bedside table");
					else if (strstr(str1.c_str(), "right bedside table") != NULL)
						strcpy(pla, "right bedside table");
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

			{
				if (question == "German")
				{
					Speak("Count von Zeppelin");
				}
				else if (question == "president")
				{
					Speak("George Washington");
				}
				else if (question == "emperor")
				{
					Speak("Pork");
				}
				else if (question == "Titanic")
				{
					Speak("Belfast");
				}
				else if (question == "victoria")
				{
					Speak("Nine children");
				}
				else if (question == "French")
				{
					Speak("Louis XIV");
				}
				else if (question == "empire")
				{
					Speak("Hadrians wall");
				}
				else if (question == "film")
				{
					Speak("Alien");
				}
				else if (question == "first king")
				{
					Speak("Leopold I");
				}
				else if (question == "former")
				{
					Speak("New Amsterdam");
				}
				else if (question == "Paris")
				{
					Speak("Lutetia");
				}
				else if (question == "capital")
				{
					Speak("Melbourne");
				}
				else if (question == "fossils")
				{
					Speak("Paleontology");
				}
				else if (question == "dragonflies")
				{
					Speak("Mosquitoes");
				}
				else if (question == "centimeters")
				{
					Speak("Fleas");
				}
				else if (question == "european")
				{
					Speak("Wisent");
				}
				else if (question == "snake")
				{
					Speak("Eel fish");
				}
				else if (question == "contain")
				{
					Speak("Maple");
				}
				else if (question == "tiger")
				{
					Speak("Siberian tiger");
				}
				else if (question == "born")
				{
					Speak("Six toes");
				}
				else if (question == "house")
				{
					Speak("Number 742");
				}
				else if (question == "restricted ")
				{
					Speak("Pekinese");
				}
				else if (question == "director")
				{
					Speak("Quentin Tarantino");
				}
				else if (question == "Herbie")
				{
					Speak("Fifty-three");
				}
				else if (question == "parody")
				{
					Speak("Austin Powers");
				}
				else if (question == "commander")
				{
					Speak("Captain Picard");
				}
				else if (question == "actress")
				{
					Speak("Whoopi Goldberg");
				}
				else if (question == "domain")
				{
					Speak("The .be domain");
				}
				else if (question == "MP3")
				{
					Speak("Kbps");
				}
				else if (question == "computing")
				{
					Speak("Random Access Memory");
				}
				else if (question == "earth")
				{
					Speak("Yuri Gagarin");
				}
				else if (question == "hemisphere")
				{
					Speak("The northern hemisphere");
				}
				else if (question == "cobalt")
				{
					Speak("Blue");
				}
				else if (question == "rubber")
				{
					Speak("Goodyear");
				}
				else if (question == "look")
				{
					Speak("Telescope");
				}
				else if (question == "intensity")
				{
					Speak("Candela");
				}
				else if (question == "barometer")
				{
					Speak("Torricelli");
				}
				else if (question == "in space")
				{
					Speak("Alan Shepard");
				}
				else if (question == "brother")
				{
					Speak("Montgolfier");
				}
				else if (question == "engine")
				{
					Speak("James Watt");
				}
				else if (question == "by")
				{
					Speak("The typewriter");
				}
				else if (question == "metal")
				{
					Speak("Aluminium");
				}
				else if (question == "primary")
				{
					Speak("Blue, yellow and red");
				}
				else if (question == "nearest")
				{
					Speak("Mercury");
				}
				else if (question == "Great")
				{
					Speak("6259 kilometers");
				}
				else if (question == "digits")
				{
					Speak("99999");
				}
				else if (question == "human")
				{
					Speak("Clavicle");
				}
				else if (question == "South")
				{
					Speak("Venezuela");
				}
				else if (question == "feature")
				{
					Speak("Four stars");
				}
				else if (question == "white")
				{
					Speak("Pink");
				}
				else
				{
					printf("error");
				}
			}

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
			// bool bArrived = true;//test
			usleep(3 * 1000 * 1000);
			if (bArrived == true)
			{
				Speak("Tell me the command.");
				nState = STATE_WAIT_RECO;
				srvIAT.request.active = true;
				srvIAT.request.duration = 10;
				clientIAT.call(srvIAT);
			}
		}
		if (nState == STATE_GOTO_LOCATION)
		{

			string placestr = pla;
			bool fArrived1, fArrived2, fArrived3;
			fArrived1 = true;
			printf("\n\nGOTO:%s\n\n",placestr.c_str());
			if (fArrived1 == true)
			{
				fArrived2 = Goto(placestr);
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
						printf("smallQ: %s\n", smallQ.c_str());
						printf("order: %s\n", strOrder);
						if (smallQ == "your team")
						{
							Speak("SDJU team");
							//sleep(3*1000*1000);
						}
						else if (smallQ == "your name")
						{
							Speak("my name is Doctor");
							//sleep(3*1000*1000);
						}
						else if (smallQ == "time")
						{
							Speak("It's " + now_time + " p.m now");
							//sleep(3*1000*1000);
						}
						else if (smallQ == "day")
						{
							if (strstr(strOrder, "tomorrow") != NULL)
							{
								Speak("tomorrow is Sunday");
								//sleep(3*1000*1000);
							}
							else
							{
								Speak("today is Saturday");
								//sleep(3*1000*1000);
							}
						}
						else if (smallQ == "date")
						{
							if (strstr(strOrder, "tomorrow") != NULL)
							{
								Speak("tomorrow is November 1, 2020");
								//sleep(3*1000*1000);
							}
							else
							{
								Speak("today is October 30, 2020");
								//sleep(1*1000*1000);
							}
						}
						else
							printf("SmallQuestion Error!");
						nState = STATE_GOTO_EXIT;
						bGotoExit = true;
					}
					else if (taskflag == 3)
					{ //follow

						int n;
						n = system("bash /home/robot/11.sh");
						nState = STATE_GOTO_EXIT;
						bGotoExit = true;
					}
					else if (taskflag == 4)
					{ //拿东西
						int n;
						n = system("bash /home/robot/zhua.sh");
						usleep(5 * 1000 * 1000);

						nState = STATE_GOTO_LOCATION2;
					}
					else if (taskflag == 5)
					{ //找东西
						if (strstr(strOrder, "cream") != NULL)
							fArrived3 = Goto("kitchen table"); //去小地点
						else if (strstr(strOrder, "milk") != NULL)
							fArrived3 = Goto(""); //去小地点
						else if (strstr(strOrder, "biscuit") != NULL)
							fArrived3 = Goto(""); //去小地点
						else if (strstr(strOrder, "napkin") != NULL)
							fArrived3 = Goto(""); //去小地点
						else if (strstr(strOrder, "chips") != NULL || strstr(obj, "trip") != NULL)
							fArrived3 = Goto(""); //去小地点
						else if (strstr(strOrder, "area") != NULL)
							fArrived3 = Goto(""); //去小地点
						else if (strstr(strOrder, "green tea") != NULL)
							fArrived3 = Goto(""); //去小地点
						else if (strstr(strOrder, "pepsi") != NULL)
							fArrived3 = Goto(""); //去小地点
						else if (strstr(strOrder, "herbal tea") != NULL)
							fArrived3 = Goto(""); //去小地点
						else if (strstr(strOrder, "porridge") != NULL)
							fArrived3 = Goto(""); //去小地点
						else if (strstr(strOrder, "jelly") != NULL)
							fArrived3 = Goto(""); //去小地点

						//识别完毕,关闭语音识别

						if (fArrived3 == true)
						{
							string strRepeat = strOrder;
							string object = FindWord(strRepeat, arKWObject);
							string answer = object + "is found";
							Speak(answer);
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
			if (fArrived == true)
			{
				Speak("Here you are!");
				n = system("bash /home/robot/fang.sh");

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

			Speak("I am leaving to exit.");
			Goto("exit");
		}
		ros::spinOnce();
		r.sleep();
	}
	return 0;
}
