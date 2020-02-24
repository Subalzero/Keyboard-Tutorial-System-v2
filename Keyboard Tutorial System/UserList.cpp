#include "stdafx.h"
#include "UserList.h"

int rescan::UserList::currID = 0;

rescan::UserList::UserList()
{
	readFromFile();
}

rescan::UserList::~UserList()
{
}

void rescan::UserList::AddEmptyUser(std::wstring username)
{
	User user;
	user.userName = username;
	user.lessonLevel = 0;
	for (int i = 0; i < 43; ++i) {
		user.scores[i] = { 0 };
	}
	user.userID = rescan::UserList::currID++;
	std::wstringstream wss;
	wss << user.userID << user.userName << L".dat";
	user.fileLocation = wss.str();
	writeToFile();
}

void rescan::UserList::AddUserScore(BestScore score, int userID, int lesson)
{
	for (User user : users)
	{
		if (user.userID == userID)
		{
			user.scores[lesson - 1] = score;
			break;
		}
	}
	writeToFile();
}

void rescan::UserList::RemoveUser(int userID)
{
	for (auto iter = users.begin(); iter != users.end(); ++iter)
	{
		if ((*iter).userID == userID)
		{
			users.erase(iter);
			break;
		}
	}
	writeToFile();
}

void rescan::UserList::writeToFile()
{
	std::wofstream ofs(L"users.dat");
	if (ofs.is_open())
	{
		ofs << rescan::UserList::currID << std::endl;
		ofs << users.size() << std::endl;
		for (User user : users)
		{
			ofs << user.userName << std::endl;
			ofs << user.userID << std::endl;
			ofs << user.fileLocation << std::endl;
			ofs << user.lessonLevel << std::endl;
			std::wofstream fs(user.fileLocation);
			if (fs.is_open())
			{
				for (int i = 0; i < 43; ++i)
				{
					fs << user.scores[i].parTime << std::endl;
					fs << user.scores[i].wordsPerMinute << std::endl;
					fs << user.scores[i].accuracy << std::endl;
				}
			}
		}
	}
}

void rescan::UserList::readFromFile()
{
	std::wifstream wifs(L"users.dat");
	if (wifs.is_open())
	{
		wifs >> UserList::currID;
		int n = 0;
		wifs >> n;
		users = std::vector<User>(n);
		wifs.get();
		for (int i = 0; i < n; ++i)
		{
			User user;
			std::getline(wifs, user.userName);
			wifs >> user.userID; wifs.get();
			std::getline(wifs, user.fileLocation);
			wifs >> user.lessonLevel; wifs.get();
			std::wifstream fs(user.fileLocation);
			if (fs.is_open())
			{
				for (int j = 0; j < 43; ++j)
				{
					fs >> user.scores[j].parTime;
					fs >> user.scores[j].wordsPerMinute;
					fs >> user.scores[j].accuracy;
				}
			}
			users[i] = user;
		}
	}
}
