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

bool rescan::UserList::AddEmptyUser(std::wstring username)
{
	if (Find(username) != -1)
	{
		return false;
	}
	User user;
	user.userName = username;
	user.lessonLevel = 0;
	user.moduleLevel = 1;
	for (int i = 0; i < 41; ++i) {
		user.scores[i] = { 0 };
	}
	user.userID = rescan::UserList::currID++;
	std::wstringstream wss;
	wss << user.userID << user.userName << L".dat";
	user.fileLocation = wss.str();
	users.push_back(user);
	writeToFile();
	return true;
}

void rescan::UserList::AddUserScore(BestScore score, int userID, int lesson)
{
	for (User& user : users)
	{
		if (user.userID == userID)
		{
			user.scores[lesson - 1] = score;
			break;
		}
	}
	writeToFile();
}

std::optional<std::reference_wrapper<rescan::User>> rescan::UserList::getUser(int userID)
{
	for (auto iter = users.begin(); iter != users.end(); ++iter)
	{
		if ((*iter).userID == userID)
		{
			return (*iter);
		}
	}
	return {};
}

void rescan::UserList::RemoveUser(int userID)
{
	for (auto iter = users.begin(); iter != users.end(); ++iter)
	{
		if ((*iter).userID == userID)
		{
			_wremove((*iter).fileLocation.c_str());
			users.erase(iter);
			break;
		}
	}
	writeToFile();
}

void rescan::UserList::UpdateProgress(int userID, int lessonLev)
{
	if (auto user = getUser(userID))
	{
		if (user->get().lessonLevel < lessonLev)
		{
			user->get().lessonLevel = lessonLev;
			if (lessonLev >= 12)
			{
				user->get().moduleLevel = user->get().moduleLevel >= 2 ? user->get().moduleLevel : 2;
			}
			else if (lessonLev >= 23)
			{
				user->get().moduleLevel = user->get().moduleLevel >= 3 ? user->get().moduleLevel : 3;
			}
			else if (lessonLev >= 27)
			{
				user->get().moduleLevel = user->get().moduleLevel >= 4 ? user->get().moduleLevel : 4;
			}
		}
		writeToFile();
	}
}

int rescan::UserList::Find(std::wstring userName) const
{
	int index = -1;
	for (int i = 0; i < users.size(); ++i)
	{
		User user = users[i];
		if (user.userName == userName)
		{
			index = i;
			break;
		}
	}
	return index;
}

rescan::User& rescan::UserList::operator[](unsigned index)
{
	return users[index];
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
			ofs << user.moduleLevel << std::endl;
			std::wofstream fs(user.fileLocation);
			if (fs.is_open())
			{
				for (int i = 0; i < 41; ++i)
				{
					fs << user.scores[i].parTime << std::endl;
					fs << user.scores[i].wordsPerMinute << std::endl;
					fs << user.scores[i].accuracy << std::endl;
					fs << user.scores[i].frequency << std::endl;
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
			wifs >> user.moduleLevel; wifs.get();
			std::wifstream fs(user.fileLocation);
			if (fs.is_open())
			{
				for (int j = 0; j < 41; ++j)
				{
					fs >> user.scores[j].parTime;
					fs >> user.scores[j].wordsPerMinute;
					fs >> user.scores[j].accuracy;
					fs >> user.scores[j].frequency;
				}
			}
			users[i] = user;
		}
	}
}
