/*WHO IS WHO*/
/* @author K*/
/*比赛前将photo.py中名字改为name，face.py中三个人的人名改为person0、1、2，删除主目录下的三张图片*/
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sound_play/SoundRequest.h>
#include <sound_play/sound_play.h>
#include <vector>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "xfyun_waterplus/IATSwitch.h"
#include <waterplus_map_tools/GetWaypointByName.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
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
#define STATE_CONFIRM 4
#define STATE_GOTO_EXIT 5
#define STATE_PHOTOGRAPH 6
#define STATE_GOTO_LOCATION 7
#define STATE_GOTO_CMD 8
#define STATE_WAIT_FACE 9
#define STATE_CATCH 10
#define STATE_FACE_RECO 11

#define STATE_PHOTO 12
#define STATE_WAIT_FACE_HW 13
int times = 0; //记录回来的次数
char obj[10][20];
int objnum = 0;
char per[10][20];
int pernum = 1;
char pla[10][20];
int planum = 0;
// clock_t start_time, end_time;//根据时间动态规划

static int nState = STATE_WAIT_ENTR; //程序启动时初始状态
//static int nState = STATE_WAIT_RECO ;

//识别关键词
static vector<string> arKWPerson;
static vector<string> arKWConfirm;
static vector<string> arKWPlacement_living_room;
static vector<string> arKWPlacement_kitchen;
static vector<string> arKWPlacement_bedroom;
static vector<string> arKWObject;
static void Init_keywords()
{
	//人名关键词(根据比赛前一天提供的人名列表进行修改)
	arKWPerson.push_back("daniel");
	arKWPerson.push_back("Michael");
	arKWPerson.push_back("jack");
	arKWPerson.push_back("fisher");
	arKWPerson.push_back("kevin");
	arKWPerson.push_back("Kevin");
	arKWPerson.push_back("rose");
	arKWPerson.push_back("john");
	arKWPerson.push_back("mary");
	arKWPerson.push_back("lucy");
	arKWPerson.push_back("tom");
	arKWPerson.push_back("Tom");

	//物品关键词
	arKWObject.push_back("tea");
	arKWObject.push_back("biscuits");
	arKWObject.push_back("chips");
	arKWObject.push_back("milk");
	arKWObject.push_back("apple");
	arKWObject.push_back("lemon");
	arKWObject.push_back("napkin");
	arKWObject.push_back("oreo");
	arKWObject.push_back("pepsi");
	arKWObject.push_back("porridge");
	//yes or no
	arKWConfirm.push_back("yes");
	arKWConfirm.push_back("Yes");
	arKWConfirm.push_back("Yeah");
	arKWConfirm.push_back("no");
	arKWConfirm.push_back("No");

	//living_room
	arKWPlacement_living_room.push_back("chips");
	arKWPlacement_living_room.push_back("lemon");
	arKWPlacement_living_room.push_back("tea");

	//bed_room
	arKWPlacement_kitchen.push_back("biscuits");
	arKWPlacement_kitchen.push_back("milk");

	//kitchen

	arKWPlacement_bedroom.push_back("apple");
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
	ROS_WARN("[WhoIsWho KeywordCB] - %s", msg->data.c_str());
	string strListen = msg->data;

	if (nState == STATE_WAIT_RECO)
	{
		string person = FindWord(strListen, arKWPerson);
		string object = FindWord(strListen, arKWObject);
		string pla1 = FindWord(strListen, arKWPlacement_living_room);
		string pla2 = FindWord(strListen, arKWPlacement_bedroom);
		string pla3 = FindWord(strListen, arKWPlacement_kitchen);
		if (person.length() > 0 && object.length() > 0)
		{
			nState = STATE_CONFIRM;

			printf("include name - %s \n", person.c_str());
			printf("include object - %s \n", object.c_str());
			if (pla1.length() > 0)
			{
				strcpy(pla[planum], "living room");
				printf("include place - living room \n");
			}
			else if (pla2.length() > 0)
			{
				strcpy(pla[planum], "bed room");
				printf("include place - bed room \n");
			}
			else if (pla3.length() > 0)
			{
				strcpy(pla[planum], "kitchen");
				printf("include place - kitchen \n");
			}
			else
			{
				printf("place error\n");
			}
			string strRepeat = "your name is " + person + "," + "you want " + object;
			strcpy(obj[objnum], object.c_str());
			strcpy(per[pernum], person.c_str());

			Speak(strRepeat);
			usleep(1 * 1000 * 1000);
			string where = "please confirm";
			Speak(where);
		}
	}
	if (nState == STATE_CONFIRM)
	{
		string confirm = FindWord(strListen, arKWConfirm);
		if (confirm == "yes" || confirm == "Yes" || confirm == "Yeah")
		{

			objnum++;
			pernum++;
			planum++;
			nState = STATE_PHOTO;
		}

		if (confirm == "no" || confirm == "No")
		{
			Speak("ok,Repeat your name and what you want");
			nState = STATE_WAIT_RECO;
		}
	}

	if (nState == STATE_PHOTO)
	{
		int n;
		char order[100];
		Speak("Please don't move");
		sprintf(order, "cd  ~/HWFace && python3 photo.py %s", per[pernum - 1]); //格式化命令，替换
		n = system(order);
		nPersonCount++;
		if (nPersonCount >= 3)
		{ //要识别的人名个数
			bGotoExit = true;
			{
				//修改人脸识别代码
				int n;
				char order[100];
				//修改输出pdf文件代码
				sprintf(order, "sed -i 's/person0/%s/g' ~/face/turn_pdf.sh", strcat(per[1], obj[0])); //格式化命令，替换
				n = system(order);
				sprintf(order, "sed -i 's/person1/%s/g' ~/face/turn_pdf.sh", strcat(per[2], obj[1])); //格式化命令，替换
				n = system(order);
				sprintf(order, "sed -i 's/person2/%s/g' ~/face/turn_pdf.sh", strcat(per[3], obj[2])); //格式化命令，替换
				n = system(order);

				//输出pdf
				n = system("sh /home/robot/face/turn_pdf.sh");
			}
			//识别完毕,关闭语音识别
			srvIAT.request.active = false;
			clientIAT.call(srvIAT);

			Speak("ok,I have memory you. I am leaving.");
			//n = system("sh /home/robot/left.sh"); //左转前进右转

			nState = STATE_GOTO_LOCATION;
		}
		else
		{

			//Speak("where is the "+object);
			Speak("ok,I have memory you. Next one, please");
			if (nPersonCount == 1)
				n = system("sh /home/robot/left.sh"); //左转前进右转
			if (nPersonCount == 2)
				n = system("sh /home/robot/left.sh "); //左转前进右转

			//n=system("sh /home/robot/faceunknown.sh");//需调试
			Speak("Please tell me your name and what you want");
			nState = STATE_WAIT_RECO;
		}
	}
}
int main(int argc, char **argv)
{

	ros::init(argc, argv, "wpb_home_WhoIsWho");
	Init_keywords();
	ros::NodeHandle n;
	ros::Subscriber sub_sr = n.subscribe("/xfyun/iat", 10, KeywordCB);
	clientIAT = n.serviceClient<xfyun_waterplus::IATSwitch>("xfyun_waterplus/IATSwitch");
	cliGetWPName = n.serviceClient<waterplus_map_tools::GetWaypointByName>("/waterplus/get_waypoint_name");
	spk_pub = n.advertise<sound_play::SoundRequest>("/robotsound", 20);
	ros::Rate r(10);
	//初始化
	{
		strcpy(per[0], "name");
	}
	Speak("OK");
	int k;
	k = system("sh /home/robot/whoiswho_clear.sh");

	while (ros::ok())
	{

		if (nState == STATE_WAIT_ENTR)
		{
			bool bArrived = Goto("cmd");
			//bool bArrived = true; //测试用
			if (bArrived == true)
			{
				int n;
				Speak("I am robot Doctor");
				Speak("Please tell me your name and what you want");
				nState = STATE_WAIT_RECO;
				srvIAT.request.active = true;
				srvIAT.request.duration = 6;
				clientIAT.call(srvIAT);
			}
		}
		if (nState == STATE_CATCH)
		{
			//int n;
			//n = system("sh /home/robot/zhua.sh&");
			//sleep(5);
			nState = STATE_GOTO_CMD;
		}
		if (nState == STATE_GOTO_LOCATION)
		{
			bool fArrived;
			string placestr = pla[times]; //去的地点通过times来控制 0、1、2
			placestr = "room";
			printf("\n----goto:%s----\n", pla[times]);
			fArrived = Goto(placestr);
			//fArrived = true; //测试用
			if (fArrived == true)
			{
				Speak("I am in the" + placestr);
				//usleep(2 * 1000 * 1000);
				nState = STATE_CATCH;
			}
		}

		if (nState == STATE_GOTO_CMD)
		{
			FILE *fp1 = NULL; //定义文件指针
			bool fArrived;
			fArrived = Goto("back");
			//fArrived = true;//测试用
			if (fArrived == true)
			{
				fp1 = fopen("/home/robot/face/face_person", "w"); //打开人脸识别写入要识别的人

				int n;
				if (times == 0)
				{ //第一个人

					n = fprintf(fp1, "%s", per[1]);
					//printf("per1 done\n");
				}
				else if (times == 1)
				{ //第二个人
					n = fprintf(fp1, "%s", per[2]);
					//printf("per2 done\n");
				}
				else
				{ //第三个人
					n = fprintf(fp1, "%s", per[3]);
					//printf("per3 done\n");
				}
				fclose(fp1);

				Speak("I am back");
				//usleep(2 * 1000 * 1000);
				//n = system("sh /home/robot/face/face.sh");
				char order[100];
				sprintf(order, "cd  ~/HWFace && python3 face_reco.py %s", per[times + 1]); //格式化命令，替换
				n = system(order);
				nState = STATE_WAIT_FACE;
			}
		}

		if (nState == STATE_WAIT_FACE_HW)
		{

			FILE *fp = NULL; //定义文件指针

			char buff[5];
			int n;
			string buf;
			fp = fopen("/home/robot/face_state", "r"); //打开人脸识别状态文件

			n = fscanf(fp, "%s", buff);
			buf = buff;
			if (buf == "exit")
			{

				if (times == 0)
				{
					times++;
					string object = obj[0];
					string person = per[1];
					Speak(person + " this is the" + object + "you want,all right?");
					//usleep(2 * 1000 * 1000);
					//n = system("sh /home/robot/fang.sh");
					//n = system("sh /home/robot/fang.sh"); //放爪
					//usleep(2 * 1000 * 1000);
					nState = STATE_GOTO_LOCATION;
				}
				else if (times == 1)
				{
					times++;
					string object = obj[1];
					string person = per[2];
					Speak(person + "this is the" + object + "you want,all right?");
					//usleep(2 * 1000 * 1000);
					//n = system("sh /home/robot/fang.sh"); //放爪
					//usleep(2 * 1000 * 1000);
					nState = STATE_GOTO_LOCATION;
				}
				else
				{
					string object = obj[2];
					string person = per[3];
					Speak(person + "this is the " + object + " you want,all right?");
					//usleep(1 * 1000 * 1000);
					//n = system("sh /home/robot/fang.sh"); //放爪
					//usleep(2 * 1000 * 1000);
					Speak("I am leaving to exit");
					nState = STATE_GOTO_EXIT;
				}
			}
		}

		if (nState == STATE_WAIT_FACE)
		{

			FILE *fp = NULL; //定义文件指针

			char buff[5];
			int n;
			string buf;
			fp = fopen("/home/robot/face_state", "r"); //打开人脸识别状态文件

			n = fscanf(fp, "%s", buff);
			buf = buff;
			if (buf == "exit")
			{

				if (times == 0)
				{
					times++;
					string object = obj[0];
					string person = per[1];
					Speak(person + " this is the" + object + "you want,all right?");
					//usleep(2 * 1000 * 1000);
					//n = system("sh /home/robot/fang.sh");
					//n = system("sh /home/robot/fang.sh"); //放爪
					//usleep(2 * 1000 * 1000);
					nState = STATE_GOTO_LOCATION;
				}
				else if (times == 1)
				{
					times++;
					string object = obj[1];
					string person = per[2];
					Speak(person + "this is the" + object + "you want,all right?");
					//usleep(2 * 1000 * 1000);
					//n = system("sh /home/robot/fang.sh"); //放爪
					//usleep(2 * 1000 * 1000);
					nState = STATE_GOTO_LOCATION;
				}
				else
				{
					string object = obj[2];
					string person = per[3];
					Speak(person + "this is the " + object + " you want,all right?");
					//usleep(1 * 1000 * 1000);
					//n = system("sh /home/robot/fang.sh"); //放爪
					//usleep(2 * 1000 * 1000);
					Speak("I am leaving to exit");
					nState = STATE_GOTO_EXIT;
				}
			}
		}

		if (nState == STATE_GOTO_EXIT && bGotoExit == true)
		{

			bGotoExit = false;
			/*
						//识别完毕,关闭语音识别
						srvIAT.request.active = false;
						clientIAT.call(srvIAT);
			*/
			Speak("I am leaving to exit.");
			//sleep(1);
			Goto("exit");
		}
		ros::spinOnce();
		r.sleep();
	}

	return 0;
}
