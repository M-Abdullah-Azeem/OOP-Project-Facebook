#include<iostream>
#include<fstream>
using namespace std;
//Declaring all classes to ensure accessibility:
class Date;
class Post;
class Memory;
class Comment;
class Object;
class Page;
class User;
class Activity;
class SocialNetwork;
class Helper {
public:
	static int StringLenght(char* str) {
		int count = 0;
		for (int i = 0; str[i] != '\0'; i++)
			count++;
		return count;

	}
	static void StringCopy(char*& dest, char*& src) {
		int i;
		for (i = 0; src[i] != '\0'; i++)
			dest[i] = src[i];
		dest[i] = '\0';
	}
	static char* GetStringFromBuffer(char* str) {
		int l = StringLenght(str);
		char* newstr = new char[l + 1];
		StringCopy(newstr, str);
		return newstr;
	}
	static int StringLenght(const char* str) {
		int count = 0;
		for (int i = 0; str[i] != '\0'; i++)
			count++;
		return count;

	}
	static void StringCopy(char*& dest, const char*& src) {
		int i;
		for (i = 0; src[i] != '\0'; i++)
			dest[i] = src[i];
		dest[i] = '\0';
	}
	static char* GetStringFromBuffer(const char* str) {
		int l = StringLenght(str);
		char* newstr = new char[l + 1];
		StringCopy(newstr, str);
		return newstr;
	}
	static bool FindExactMatch(char* string, char* tofind) {
		int l = StringLenght(tofind);
		bool check = false;
		int i;
		for (i = 0; i < l; i++) {
			if (string[i] == tofind[i] || string[i] == tofind[i] + 32 || string[i] + 32 == tofind[i])
				check = true;
			else {
				check = false;
				break;
			}
		}
		return check;
	}
	static bool FindExactMatch(const char* string, const char* tofind) {
		int l = StringLenght(tofind);
		bool check = false;
		int i;
		for (i = 0; i < l; i++) {
			if (string[i] == tofind[i] || string[i] == tofind[i] + 32 || string[i] + 32 == tofind[i])
				check = true;
			else {
				check = false;
				break;
			}
		}
		return check;
	}
	static char* stringConcatenate(const char* s1, char*& s2) 
	{
		char* newstr = 0;
		int l1 = StringLenght(s1), l2 = StringLenght(s2);
		//Since s1 and s2 both are exactly equal in terms of size to what is stored in them, we create a new string equal to the lengths of s1+s2.
		newstr = new char[l1 + l2 + 1];
		int i;
		//Copying s1 into newstr.
		for (i = 0; s1[i] != '\0'; i++)
			newstr[i] = s1[i];
		int j;
		//Copying s2 into newstr, i helps in storing further data into newstr from where s1 left.
		for (j = i, i = 0; s2[i] != '\0'; j++, i++)
			newstr[j] = s2[i];//Storing a null at the end.
		newstr[l1 + l2] = '\0';
		delete[]s2;
		return newstr;
	}
	static char* IntToCharArray(int n)
	{	//Making 'a' a copy for n so we work on it without changing n. "count" will count the size for the newly generated array storing the integer n.
		int a = n, count = 0;
		//The following loop calculates the size of required array. 
		while (a > 0)
		{
			count++; //For each instance this loop runs, we increment the count(size) by one.
			a = a / 10; //Reducing the number to its lower form. For example if n is 100, then it drops to 10 and so on. 
		}
		char* arr = new char[count + 1];
		arr[count] = '\0';
		while (n > 0)
		{
			int b = n % 10; //Getting last digit in n.
			arr[--count] = b + '0'; //Storing b as ASCII in arr.
			n = n / 10; //Reducing the number to its lower form. For example if n is 100, then it drops to 10 and so on. 
		}
		return arr;
	}
	static char* GenerateNewID(const char* prefix, int postfix)
	{
		char* newIDNo = IntToCharArray(postfix);
		char* newID = stringConcatenate(prefix, newIDNo);
		return newID;
	}
};
class Date
{
	int day;
	int month;
	int year;
public:
	static Date Today;
		//Constructor:
	Date()
	{
		day = month = year = 0;
	}
	   //Setter:
	static void SetAsToday(int D, int M, int Y)
	{
		cout << "\n------------------------------------------------------------------------------------------------------------------------\n Command:\t\t\t\tSet Current System Date " << D << " " << M << " " << Y << "\nSystem Date\t";
		Today.day = D;
		Today.month = M;
		Today.year = Y;
		cout << Today;
	}
		//Comparison/Arithmetic operations:
	int operator-(Date d)
	{
		return year - d.year;
	}
	bool CompareDayAndMonth()
	{
		return (day == Today.day && month == Today.month);
	}
	bool operator==(Date date)
	{
		if ((day == date.day || day == (date.day - 1)) && month == date.month && year == date.year)
			return true;
		else if (date.month == month - 1 && day - 1 == 0)
			return true;
		else
			return false;
	}
		//File Reader:
	void ReadDateFromFile(ifstream& read)
	{
		read >> day;
		read >> month;
		read >> year;
	}
		// Overloaded extraction operator.
	friend ostream& operator<<(ostream& output, Date d)
	{
		output << " (" << d.day << "/" << d.month << "/" << d.year << ")";
		return output;
	}
		//Destructor:
	~Date()
	{
		//Empty as there is nothing to be deleted.
	}
};
class Object
{	//Object class is only created to facilitate Polymorphism between User and Page.
	char* ID;
public:
		//Constructor:
	Object()
	{
		ID = 0;
	}
		//Setter:
	void SetID(char* temp)
	{
		ID = Helper::GetStringFromBuffer(temp);
	}
		//Getter:
	char* GetID()
	{
		return ID;
	}
		//Printers:
		//Virtual to facilitate Polymorphism.
	virtual void DisplayCurrent() = 0; //Pure virtual as there is nothing really to do for them in this parrent class.
	virtual void PrintListView() = 0; //Pure virtual as there is nothing really to do for them in this parrent class.
		//virtual Adder to facilitate Polymorphism as timeLine can exist for both User and Page.
	virtual void AddToTimeLine(Post* shared) = 0; //Pure virtual as there is nothing really to do for them in this parrent class.
		//Destructor:
		//Virtual to call destructors of child classes(User/Page).
	virtual ~Object()
	{
		if (ID)
			delete[]ID;
	}
};
class Activity
{	//Class to store data regarding the activity of a Post.
	char* description;	//Stores Text of an Activity which can be excited, success etc.
	int type;	//Stores a numeric value that defines the activity which can be feeling, celebrating etc.
public:
		//Constructor:
	Activity()
	{
		description = 0;
		type = 0;
	}
		//File Reader:
	void ReadActivityDataFromFile(ifstream& read)
	{
		char buffer[40];
		read >> type;
		read.getline(buffer, 40);
		description = Helper::GetStringFromBuffer(buffer);
	}
		//Overloaded extraction operator:
	friend ostream& operator<<(ostream& output, Activity* a)
	{
		switch (a->type)
		{
		case 1:
			output << " is feeling ";
			break;
		case 2:
			output << " is thinking about ";
			break;
		case 3:
			output << " is makung ";
			break;
		case 4:
			output << " is celebrating ";
			break;
		}
		output << a->description;
		return output;
	}
		//Destructor:
	~Activity()
	{
		if (description)
			delete[]description;
	}
};
class Comment
{	//Storing Data for Comments of a Post:
	char* ID;
	char* text;
	Object* sharedBy;	//Specifying as an Object as a Comment can be posted by a User or a Page.
public:
	static int CommentCount;
		//Constructors:
	Comment()
	{
		text = ID = 0;
		sharedBy = 0;
	}
	Comment(const char* txt, Object* share)
	{
		ID = Helper::GenerateNewID("c", ++CommentCount);
		text = Helper::GetStringFromBuffer(txt);
		sharedBy = share;
	}
		//Setter:
	void SetValues(char* id, char* txt, Object* obj)
	{
		ID = Helper::GetStringFromBuffer(id);
		text = Helper::GetStringFromBuffer(txt);
		sharedBy = obj;
	}
		//Overloaded extraction operator:
	friend ostream& operator<<(ostream& output, Comment* c)
	{
		output << "\n\t";
		c->sharedBy->DisplayCurrent();
		output << " wrote:\t\"" << c->text << "\".";
		return output;
	}
		//Destructor:
	~Comment()
	{
		if (ID)
			delete[]ID;
		if (text)
			delete[]text;
	}
};
class Post
{	//Storing Data for each Post that is posted by a User or a Page.
	char* ID;
	char* description;
	int type;
	Activity* activity;
	Date sharedDate;
	Object* sharedBy;
	Object** likedByList;
	Comment** comments;
	int commentsCount;
	int likedByCount;
public:
	static int PostCount;
		//Constructor:
	Post()
	{
		ID = description = 0;
		activity = 0;
		likedByList = 0;
		sharedBy = 0;
		comments = 0;
		type = likedByCount = commentsCount = 0;
	}
		//Getters:
	char* GetText()
	{
		return description;
	}
	Object* GetSharedBy()
	{
		return sharedBy;
	}
	char* GetID()
	{
		return ID;
	}
	Date GetDate()
	{
		return sharedDate;
	}
		//File Reader:
	void ReadPostDataFromFile(ifstream& read)
	{
		read >> type;
		char buffer[100];
		read >> buffer;
		ID = Helper::GetStringFromBuffer(buffer);
		sharedDate.ReadDateFromFile(read);
		read.getline(buffer, 100);
		read.getline(buffer, 100);
		description = Helper::GetStringFromBuffer(buffer);
		if (type == 2)
		{
			activity = new Activity;
			activity->ReadActivityDataFromFile(read);
		}
	}
		//Adders:
	void AssignSharedBy(Object* shared)
	{	//If sharedBy does not exist, then assigns it.
		if(!sharedBy)
			sharedBy = shared;
	}
	void AddToLikedBy(Object* likedBy)
	{
		if (likedByList == 0 && likedBy)	//Declaration if likedByList is nullptr.
			likedByList = new Object * [10];
		if (likedBy && likedByCount < 10)	//Assignment if likedByCount is less then 10.
			likedByList[likedByCount++] = likedBy;
	}
	void AddComment(Comment* newComment)
	{
		if (newComment && comments == 0)	//Declaration if comments is nullptr.
			comments = new Comment * [10];
		if (newComment && commentsCount < 10)	//Assignment if commentsCount is less then 10.
			comments[commentsCount++] = newComment;
	}
		//Printers:
	virtual void PrintPost(bool dateCheck = true, bool commentCheck = true)
	{
		cout << "\n\n---";
		sharedBy->DisplayCurrent();
		if (activity)	//Overloaded extraction operator for Activity.
			cout << activity << "\n";
		else
			cout << " shared";
		cout << " \"" << description << "\"";
		if(dateCheck)
			cout << sharedDate; //Overloaded output operator for Date.
		if (commentCheck)
			for (int i = 0; i < commentsCount; i++)
				cout << comments[i];	//Overloaded extraction operator for Comment.
	}
	void ViewLikedByList()
	{
		if (likedByList)
		{
			cout << "\nCommand:\t\t\t\tView Liked By List: (" << ID << ")\nPost Liked By : \n";
			for (int i = 0; i < likedByCount; i++)
				likedByList[i]->PrintListView();
		}
		else
			cout << "\n No one liked this Post.";
	}
		//Setter:
	void SetValues(Post* temp, const char* text)
	{
		ID = Helper::GenerateNewID("post", ++PostCount);
		sharedBy = temp->sharedBy;
		sharedDate = Date::Today;
		description = Helper::GetStringFromBuffer(text);
	}
		//Destructor:
	~Post()
	{
		if (ID)
			delete[]ID;
		if (description)
			delete[]description;
		if (activity)
			delete activity;
		if (likedByList)
			delete[]likedByList;
		if (comments)	//If we delete a Post, its comments should also be deleted.
		{
			for (int i = 0; i < commentsCount; i++)
				delete comments[i];
			delete[]comments;
		}
	}
};
class Memory :public Post
{	//Memory is a special kind of Post. it is different in the way it works and prints on the scrreen.
	Post* originalPost;	//Post that is being shared as Memory.
public:
		//Constructors:
	Memory()
	{
		originalPost = 0;
	}
	Memory(Post* temp, const char* txt)
	{
		originalPost = temp;
		SetValues(temp, txt);
	}
		//Printers:
		//This function is being overloaded in child class(Memory) and is declared virtuak in parrent class(Post).
	void PrintPost(bool dateCheck = true, bool commentCheck = true)
	{
		cout << "\n\n~~~";
		GetSharedBy()->DisplayCurrent();
		cout << " shared a Memory~~~" << GetDate() << "\n \"" << GetText() << ".\"\n\t\t(" << Date::Today - originalPost->GetDate() << " Years Ago)";
		originalPost->PrintPost(true, false);
	}
		//Destructor:
	~Memory()
	{
		//Empty as there is nothing to be deleted.
	}
};
class Page : public Object
{	//Stores information of each Page in the Social Network.
	char* Tittle;
	Post** timeLine;	//Stores Posts shared by the Page.
	int timeLineCount;
public:
		//Constructor:
	Page()
	{
		Tittle = 0;
		timeLine = 0;
		timeLineCount = 0;
	}
		//File Reader:
	void ReadPagesDataFromFile(ifstream& read)
	{
		char temp[100];
		read >> temp;
		SetID(temp);
		read.getline(temp, 100);
		Tittle = Helper::GetStringFromBuffer(temp);
	}
		//Printers:
	void DisplayCurrent()
	{	//Displays only the Tittle.
		cout << Tittle;
	}
	void PrintListView()
	{	//Displays the ID as well as Tittle.
		cout << "\n" << GetID() << "\t-\t" << Tittle;
	}
	void ViewPage()
	{	//Displays timeLine of a Page.
		cout << "\n\nCommand:\t\t\t\tView Page(" << GetID() << "):\n" << Tittle << " - Timeline";
		if (timeLine)
			for (int i = 0; i < timeLineCount; i++)
				timeLine[i]->PrintPost();
	}
	void PrintLatestPost()
	{	//Displays Posts in timeLine which were posted either today or yesterday.
		for (int i = 0; i < timeLineCount; i++)
			if (timeLine[i]->GetDate() == Date::Today)
				timeLine[i]->PrintPost(false);
	}
		//Adder:
	void AddToTimeLine(Post* shared)
	{
		if (shared && timeLine == 0)	//If timeLine is nullptr, then declares the timeLine.
			timeLine = new Post * [10];
		if (shared && timeLineCount < 10)	//If timeLineCount is less than 10, adds the shared into it.
			timeLine[timeLineCount++] = shared;
	}
		//Destructor:
	~Page()
	{
		if (Tittle)
			delete[]Tittle;
		if (timeLine)
		{
			for (int i = 0; i < timeLineCount; i++)
				if (timeLine[i])
					delete timeLine[i];
			delete[]timeLine;
		}
	}
};
class User : public Object
{	//Stores Data of every User in the Social Network.
	char* firstName;
	char* lastName;
	User** friendsList;
	Page** likedPagesList;
	Post** timeLine;	//Stores Posts shared by the User.
	int timeLineCount;
	int likedPagesCount;
	int friendsCount;
public:
		//Constructor:
	User()
	{
		firstName = lastName = 0;
		likedPagesCount = friendsCount = timeLineCount = 0;
		friendsList = 0;
		likedPagesList = 0;
		timeLine = 0;
	}
		//File Reader
	void ReadUsersDataFromFile(ifstream& fin)
	{
		char temp[30];
		fin >> temp;
		SetID(temp);
		fin >> temp;
		firstName = Helper::GetStringFromBuffer(temp);
		fin >> temp;
		lastName = Helper::GetStringFromBuffer(temp);
	}
		//Adders:
	void AddToLikedPagesList(Page* liked)
	{
		if (liked && likedPagesCount == 0)	//If likedPagesCount is 0 (i.e its the first ever liked page for the User) then declares the likedPagesList.
			likedPagesList = new Page * [10];
		if (likedPagesCount < 10 && liked)	//If likedPagesCount has not reached the limit of 10, then adds the liked into the list.
			likedPagesList[likedPagesCount++] = liked;
	}
	void AddToFriendsList(User* friendUser)
	{
		if (friendUser && friendsCount == 0)	//If friendsCount is 0 (i.e its the first ever friend of the User) then declares the friendsList.
			friendsList = new User * [10];
		if (friendsCount < 10 && friendUser)	//If friendsCount has not reached the limit of 10, then adds the friendUser into the list.
			friendsList[friendsCount++] = friendUser;
	}
	void AddToTimeLine(Post* shared)
	{
		if (shared && timeLine == 0)	//If timeLine is NULL, then declares timeLine.
			timeLine = new Post * [10];
		if (shared && timeLineCount < 10)	//If timeLineCount is under 10 (limit), then adds shared into the timeLine.
			timeLine[timeLineCount++] = shared;
	}
		//Printers:
	void PrintListView()
	{	//Prints full name as well as the ID.
		cout << "\n" << GetID() << "\t-\t" << firstName << " " << lastName;
	}
	void DisplayCurrent()
	{	//Prints full name.
		cout << firstName << " " << lastName;
	}
	void DisplayCurrentUser()
	{	//Prints a message when a new User is Set as Current User.
		cout << firstName << " " << lastName << " Successfully Set As Current User.";
	}
	void DisplayLikedPagesList()
	{
		cout << "\n\nCommand:\t\t\t\tView Liked Pages.\n";
		cout << firstName << " " << lastName << " - Liked Pages:\n";
		if (likedPagesCount != 0)
			for (int i = 0; i < likedPagesCount; i++)
				likedPagesList[i]->PrintListView();
		else
			cout << "\n\n No Pages found in Liked Pages List.";
	}
	void DisplayFriendsList()
	{
		cout << "\n\nCommand:\t\t\t\tView Friend List.\n";
		cout << firstName << " " << lastName << " - Friend List:\n";
		if (friendsCount != 0)
			for (int i = 0; i < friendsCount; i++)
				friendsList[i]->PrintListView();
		else
			cout << "\n\n No Friends found in Friends List.";
	}
	void PrintLatestPost()
	{	//Prints all the Posts User shared Today or yesterday.
		if (timeLine)
			for (int i = 0; i < timeLineCount; i++)
				if (timeLine[i]->GetDate() == Date::Today)
					timeLine[i]->PrintPost(false);
	}
	void ViewHome()
	{	//Allows User to view his Home Page.
		cout << "\n\n Command:\t\t\t\tView Home\n" << firstName << " " << lastName << " - Home Page:\n";
		if (friendsList)	//NULL check.
			for (int i = 0; i < friendsCount; i++)
						friendsList[i]->PrintLatestPost();
		if (likedPagesList)	//NULL check.
			for (int i = 0; i < likedPagesCount; i++)
				likedPagesList[i]->PrintLatestPost();
	}
	void ViewTimeLine()
	{	//Prints the entire timeLine of the User.
		cout << "\n\nCommand:\t\t\t\tView Time Line:\n" << firstName << " " << lastName << " - Time Line";
		for (int i = 0; i < timeLineCount; i++)
			timeLine[i]->PrintPost();
	}
	void PostComment(Post* reqPost, const char* comment)
	{	//Allows User to Post a Xomment on a Post.
		cout << "\nCommand:\t\t\t\tPost Comment(" << reqPost->GetID() << ", \"" << comment << "\")";
		Comment* newComment = new Comment(comment, this);
		reqPost->AddComment(newComment);
	}
	void SeeYourMemories()
	{	//Allows the User to see Posts he Posted, on the same day and month, years ago.
		cout << "\nCommand:\t\t\t\tSeeYourMemories()\n\n  We hope you emjoy looking back and sharing your Memories on Facebook, from the most recent to those long ago.\n";
		int n = 0;
		for (int i = 0; i < timeLineCount; i++)
		{
			n = Date::Today - timeLine[i]->GetDate();
			if (n && timeLine[i]->GetDate().CompareDayAndMonth())	//If the year difference(n) is non-zero and the day and month is the same:
			{
				cout << "\nOn This Day\n" << n << " Years Ago:";
				timeLine[i]->PrintPost();
			}
		}
	}
		//Destructor:
	~User()
	{
		if (firstName)
			delete[]firstName;
		if (lastName)
			delete[]lastName;
		if (friendsList)
			delete[]friendsList;
		if (likedPagesList)
			delete[]likedPagesList;
		if (timeLine) 
		{
			for (int i = 0; i < timeLineCount; i++)
				if(timeLine[i])
					delete timeLine[i];
			delete[]timeLine;
		}
	}
};
class SocialNetwork
{
	Page** pagesList;
	User** usersList;
	Post** postsList;
	int userCount;
	int pageCount;
public:
		//Constructor:
	SocialNetwork()
	{
		pagesList = 0;
		usersList = 0;
		postsList = 0;
		pageCount = userCount = 0;
	}
		//Searchers
		//There are 2 of the Search functions for Users and Pages, this is just to deal with the const and non-const parameters. if we took inputs in the Execute functions, this would not have been required.
	Page* SearchPageByID(char* id)
	{
		if (id)
			for (int i = 0; i < pageCount; i++)
			{
				bool check = Helper::FindExactMatch(pagesList[i]->GetID(), id);
				if (check)
					return pagesList[i];
			}
		return 0;
	}
	Page* SearchPageByID(const char* id)
	{
		if (id)
			for (int i = 0; i < pageCount; i++)
			{
				bool check = Helper::FindExactMatch(pagesList[i]->GetID(), id);
				if (check)
					return pagesList[i];
			}
		return 0;
	}
	User* SearchUserByID(char* id)
	{
		if (id)
			for (int i = 0; i < userCount; i++)
			{
				bool check = Helper::FindExactMatch(usersList[i]->GetID(), id);
				if (check)
					return usersList[i];
			}
		return 0;
	}
	User* SearchUserByID(const char* id)
	{
		if (id)
			for (int i = 0; i < userCount; i++)
			{
				bool check = Helper::FindExactMatch(usersList[i]->GetID(), id);
				if (check)
					return usersList[i];
			}
		return 0;
	}
	Post* SearchPostByID(const char* id)
	{
		if (id)
			for (int i = 0; i < Post::PostCount; i++)
			{
				bool check = Helper::FindExactMatch(postsList[i]->GetID(), id);
				if (check)
					return postsList[i];
			}
		return 0;
	}
	Object* SearchObjectById(char* id)
	{	//Checks the first character in id. if its a 'p' then searches a Page, if its a 'u' then searches a User. 
		if (id[0] == 'u')
			return SearchUserByID(id);
		else
			return SearchPageByID(id);
	}
		//Expander:
	void ExpandPosts(Post* newPost)
	{	//Expands the postsList to accomodate the newest created Post.
		Post::PostCount++;	//Incrementing the PostCount to increase the size of the array.
		Post** newPostList = new Post * [Post::PostCount];	//Declaring newPostList with the incremented PostCount.
		for (int i = 0; i < Post::PostCount - 1; i++)
			newPostList[i] = postsList[i];	//Storing old Posts in the newPostList to avoid data loss.
		newPostList[Post::PostCount - 1] = newPost;	//Storing the newest Post in the last index of the newPostList.
		delete[]postsList;	//Deleting the old postsList.
		postsList = newPostList;	//Pointing the private member postsList to the newPostList.
	}
	void ShareMemory(Post* newMemory, const char* txt)
	{
		cout << "\nCommand:\t\t\t\tShareMemory(" << newMemory->GetID() << ", " << txt << ")\n";
		Memory* newPost = new Memory(newMemory, txt);
		ExpandPosts(newPost);
		cout << "------------------------------------------------------------------------------------------------------------------------";
	}
		//Loaders:
	void LoadPagesFromFile(const char* fileName)
	{
		ifstream read(fileName);
		if (read.is_open())
		{
			read >> pageCount;
			if (pageCount)
				pagesList = new Page * [pageCount];
			for (int i = 0; i < pageCount; i++)
			{
				pagesList[i] = new Page();
				pagesList[i]->ReadPagesDataFromFile(read);
			}
			read.close();
		}
		else
			cout << "\nFailed to Open File " << fileName;
	}
	void LoadUsersFromFile(const char* fileName)
	{
		ifstream read(fileName);
		char*** tempUserIds = new char** [userCount];
		if (read.is_open())
		{
			read >> userCount;
			usersList = new User * [userCount];
			char*** tempUserIds = new char** [userCount];
			for (int i = 0; i < userCount; i++)
			{
				usersList[i] = new User();
				usersList[i]->ReadUsersDataFromFile(read);
				tempUserIds[i] = new char* [10];
				char buffer[100];
				buffer[0] = ' ';
				int j = 0;
				while (buffer[0] != '-')
				{
					read >> buffer;
					tempUserIds[i][j] = Helper::GetStringFromBuffer(buffer);
					j++;
				}
				tempUserIds[i][j] = 0;
				buffer[0] = ' ';
				while (buffer[0] != '-')
				{
					read >> buffer;
					Page* liked = SearchPageByID(buffer);
					usersList[i]->AddToLikedPagesList(liked);
				}
			}
			read.close();
			for (int i = 0; i < userCount; i++)
			{
				int j = 0;
				while (tempUserIds[i][j] != 0) {
					User* befriend = SearchUserByID(tempUserIds[i][j]);
					usersList[i]->AddToFriendsList(befriend);
					delete[]tempUserIds[i][j];
					j++;
				}
				delete[]tempUserIds[i];
			}
			delete[]tempUserIds;
		}
		else
			cout << "\nFailed to Open File " << fileName;
	}
	void LoadPostsFromFile(const char* fileName)
	{
		ifstream read;
		read.open(fileName);
		if (read.is_open())
		{
			read >> Post::PostCount;
			if (Post::PostCount)
				postsList = new Post * [Post::PostCount];
			int i = 0;
			while (i < Post::PostCount)
			{
				postsList[i] = new Post;
				postsList[i]->ReadPostDataFromFile(read);
				char buffer[30];
				buffer[0] = ' ';
				read >> buffer;
				Object* obj = SearchObjectById(buffer);
				postsList[i]->AssignSharedBy(obj);
				obj->AddToTimeLine(postsList[i]);
				while (buffer[0] != '-')
				{
					read >> buffer;
					obj = SearchObjectById(buffer);
					postsList[i]->AddToLikedBy(obj);
				}
				i++;
			}
			read.close();
		}
		else
			cout << "\nFailed to Open File " << fileName;
	}
	void LoadCommentsFromFile(const char* fileName)
	{
		ifstream read;
		read.open(fileName);
		char id[10], text[100], buffer[30];
		if (read.is_open())
		{
			read >> Comment::CommentCount;
			for (int i = 0; i < Comment::CommentCount; i++)
			{
				Comment* newComment = new Comment;
				read >> id;
				read >> buffer;
				Post* searchedPost = SearchPostByID(buffer);
				read >> buffer;
				Object* searchedSharedBy = SearchObjectById(buffer);
				read.getline(text, 100);
				newComment->SetValues(id, text, searchedSharedBy);
				searchedPost->AddComment(newComment);
			}
			read.close();
		}
		else
			cout << "\nFailed to Open File " << fileName;
	}
	void LoadSocialNetwork() {
		LoadPagesFromFile("SocialNetworkPages.txt");
		LoadUsersFromFile("SocialNetworkUsers.txt");
		LoadPostsFromFile("SocialNetworkPosts.txt");
		LoadCommentsFromFile("SocialNetworkComments.txt");
	}
		//Running:
	void ExecuteSocialNetwork()
	{
		const char* id = "u7";
		Date::SetAsToday(15, 11, 2017);
		cout << "------------------------------------------------------------------------------------------------------------------------";
		cout << "\nCommand:\t\t\t\tSet Current User " << id;
		User* reqUser = SearchUserByID(id);
		if (reqUser)
		{
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->DisplayCurrentUser();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->DisplayFriendsList();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->DisplayLikedPagesList();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->ViewHome();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->ViewTimeLine();
			const char* postId = "post5";
			Post* reqPost = SearchPostByID(postId);
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqPost->ViewLikedByList();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			cout << "\n\nCommand:\t\t\t\tLike Post(" << reqPost->GetID() << ")\n\n";
			reqPost->AddToLikedBy(reqUser);
			reqPost->ViewLikedByList();
			postId = "post4";
			reqPost = SearchPostByID(postId);
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->PostComment(reqPost, "Good Luck for your Result");
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			cout << "\n\nCommand:\t\t\t\tView Post(" << reqPost->GetID() << ")";
			reqPost->PrintPost();
			postId = "post8";
			reqPost = SearchPostByID(postId);
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->PostComment(reqPost, "Thanks for all the wishes.");
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			cout << "\n\nCommand:\t\t\t\tView Post(" << reqPost->GetID() << ")";
			reqPost->PrintPost();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			postId = "post10";
			reqPost = SearchPostByID(postId);
			reqUser->SeeYourMemories();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			ShareMemory(reqPost, "Never thought I will be Specialized in this field.");
			reqUser->AddToTimeLine(postsList[Post::PostCount - 1]);
			reqUser->ViewTimeLine();
			const char* pageId = "p1";
			Page* reqPage = SearchPageByID(pageId);
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqPage->ViewPage();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
		}
		else
			cout << "\n User with ID " << id << " does not exist.";
		id = "u11";
		cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
		cout << "\n Command:\t\t\t\tSet Current User " << id << endl;
		reqUser = SearchUserByID(id);
		if (reqUser)
		{
			reqUser->DisplayCurrentUser();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->ViewHome();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
			reqUser->ViewTimeLine();
			cout << "\n------------------------------------------------------------------------------------------------------------------------\n";
		}
	}
		//Destructor:
	~SocialNetwork()
	{
		if (pagesList)
		{
			for (int i = 0; i < pageCount; i++)
				if (pagesList[i])
					delete pagesList[i];
			delete[]pagesList;
		}
		if (usersList)
		{
			for (int i = 0; i < userCount; i++)
				if (usersList[i])
					delete usersList[i];
			delete[]usersList;
		}
		if (postsList)
			delete[]postsList;
	}
};
//Initializing all static variables used/declared in various classes.
//We need static variables to store data that is same for every object of that class. This helps avoid duplication of common Data.
int Comment::CommentCount = 0;
int Post::PostCount = 0;
Date Date::Today = Date();
int main()
{
	SocialNetwork FaceBook;
	FaceBook.LoadSocialNetwork();
	FaceBook.ExecuteSocialNetwork();
	return 0;
}
