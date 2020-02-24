#pragma once

#include <vector>
#include <string>
#include <fstream>

namespace rescan
{
	struct BestScore
	{
		double parTime;
		double wordsPerMinute;
		double accuracy;
	};

	struct User
	{
		std::wstring userName;
		int userID;
		std::wstring fileLocation;
		int lessonLevel;
		BestScore scores[43];
	};

	class UserList
	{
	public:
		UserList();
		~UserList();
		void AddEmptyUser(std::wstring username);
		void AddUserScore(BestScore score, int userID, int lesson);
		void RemoveUser(int userID);
	private:
		void writeToFile();
		void readFromFile();
	private:
		static int currID;
		std::vector<User> users;
	};
}
