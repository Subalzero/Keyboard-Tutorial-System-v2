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
		void AddEmptyUser();
		void AddUserScore(BestScore score, int userID);
		void RemoveUser(int userID);
	private:
		std::vector<User> users;
		std::wfstream wFileStream;
	};
}
