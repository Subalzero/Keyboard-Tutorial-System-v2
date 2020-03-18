#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <optional>

namespace rescan
{
	struct BestScore
	{
		double parTime;
		double wordsPerMinute;
		double accuracy;
		int frequency;
	};

	struct User
	{
		std::wstring userName;
		int userID;
		std::wstring fileLocation;
		int lessonLevel;
		int moduleLevel;
		BestScore scores[41];
	};

	class UserList
	{
	public:
		UserList();
		~UserList();
		bool AddEmptyUser(std::wstring username);
		void AddUserScore(BestScore score, int userID, int lesson);
		std::optional<std::reference_wrapper<User>> getUser(int userID);
		void RemoveUser(int userID);
		void UpdateProgress(int userID, int lessonLev);
		int Find(std::wstring userName) const;
		User& operator[] (unsigned index);
	public:
		std::vector<User> users;
	private:
		void writeToFile();
		void readFromFile();
	private:
		static int currID;
		
	};
}
