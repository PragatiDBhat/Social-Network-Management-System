//-------------------------------------------SOCIAL NETWORK MANAGEMENT-------------------------------------------
//using doubly linked list
#include <iostream>
#include <ctime>
#include <stdexcept>
using namespace std;
class MyException:public exception
{
    public:
    const char* myEx() const throw()
    {
        cout<<"invalid"<<endl;
    }
};
class User;
class Post;
class Comment;
class Group;
class Friendship
{
public:
    User* user1;
    User* user2;
    Friendship* prev;
    Friendship* next;
    time_t dateEstablished;
    Friendship():user1(user1),user2(user2),prev(nullptr),next(nullptr)
    {
        dateEstablished=time(nullptr);
    }
    Friendship(User* user1,User* user2):user1(user1),user2(user2),prev(nullptr),next(nullptr)
    {
        dateEstablished=time(nullptr);
    }

    time_t getDateEstablished()
    {
        return dateEstablished;
    }
};
class Notification
{
public:
    int notificationID;
    User* user;
    string message;
    time_t timestamp;
    Notification* prev;
    Notification* next;
    Notification(int notificationID,User* user,string message)
    : notificationID(notificationID),user(user),message(message),prev(nullptr),next(nullptr)
    {
        timestamp=time(nullptr);
    }
};
class Message
{
public:
    int messageID;
    User* sender;
    User* receiver;
    string content;
    time_t timestamp;
    Message* prev;
    Message* next;
    Message(int messageID,User* sender,User* receiver,string content)
        : messageID(messageID),sender(sender),receiver(receiver),content(content),prev(nullptr),next(nullptr)
    {
        timestamp=time(nullptr);
    }
    void editContent(string newContent)
    {
        content=newContent;
        cout<<"Message content updated successfully!"<<endl;
    }
    void sendMessage();
};

class User
{
public:
    string username;
    string password;
    string email;
    string profilePicture;
    Post* posts;
    Comment* comments;
    Friendship* friendships;
    Notification* notifications;
    Message* messages;
    User* prev;
    User* next;
    int postCount;
    int commentCount;
    int friendshipCount;
    int notificationCount;
    int messageCount;
    User(string username,string password,string email)
        : username(username),password(password),email(email),posts(nullptr),comments(nullptr),
        friendships(nullptr),notifications(nullptr),messages(nullptr),prev(nullptr),next(nullptr),
        postCount(0),commentCount(0),friendshipCount(0),notificationCount(0),messageCount(0) {}
    string getUsername()
    {
        return username;
    }
    void updateProfilePicture(string picture)
    {
        profilePicture=picture;
        cout<<"Profile picture updated successfully!"<<endl;
    }
    void createPost(string content);
    void deletePost(Post* post);
    void addFriend(User* user);
    void addReverseFriendship(Friendship* friendship);
    void removeFriend(User* user);
    void sendNotification(string message);
    void sendMessage(User* receiver, string content);
    void addReverseMessage(Message* message);
    void addReverseComment(Comment* comment);
    void displayFriendsList();
    void addComment(User* user, string content);
    void displayPosts();
    void displayNotifications();
    ~User();
};
class Comment
{
public:
    int commentID;
    User* user;
    Post* post;
    string content;
    time_t timestamp;
    Comment* prev;
    Comment* next;
    Comment(int commentID,User* user,Post* post,string content)
        : commentID(commentID),user(user),post(post),content(content),prev(nullptr),next(nullptr)
    {
        timestamp=time(nullptr);
    }
    void editContent(string newContent)
    {
        content=newContent;
        cout<<"Comment content updated successfully!"<<endl;
    }
    ~Comment()
    {
        delete post;
    }
};
class Post
{
public:
    int postID;
    User* user;
    string content;
    time_t timestamp;
    Comment* comments;
    Post* prev;
    Post* next;
    int commentCount;
    Post(int postID,User* user,string content)
        : postID(postID),user(user),content(content),comments(nullptr),prev(nullptr),next(nullptr)
    {
        timestamp=time(nullptr);
    }
    void editContent(string newContent)
    {
        content=newContent;
        cout<<"Post content updated successfully!"<<endl;
    }
    void addComment(User* user,string content);
    void deleteComment(Comment* comment);
    ~Post()
    {
        Comment* nextComment;
        while (comments != nullptr) {
            nextComment = comments->next;
            delete comments;
            comments = nextComment;
        }
    }
    void displayComment();
};
class Group
{
public:
    string groupName;
    User* members;
    //Group *group;
    Group* prev;
    Group* next;
    Group(string groupName=""):groupName(groupName),members(nullptr),prev(nullptr),next(nullptr) {}

    //Group* createGroup(string groupName);
    void addMember(User* user);
    void removeMember(User* user);
    void displayMembers();
};
class SocialNetwork
{
public:
    User* users;
    Group* groups;
    SocialNetwork():users(nullptr),groups(nullptr) {}
    User* createUser(string username,string password,string email)
    {
        User* user=new User(username,password,email);
        if (users==nullptr)
        {
            users=user;
        }
        else
        {
            user->next=users;
            users->prev=user;
            users=user;
        }
        return user;
    }
    Group* createGroup(string groupName);
    void deleteUser(User* user)
    {
        if (user==users)
        {
            users=user->next;
            if (users)
            {
                users->prev=nullptr;
            }
        }
        else
        {
            if (user->prev)
            {
                user->prev->next=user->next;
            }
            if (user->next)
            {
                user->next->prev=user->prev;
            }
        }
        delete user;
        cout << "User deleted successfully!" << endl;
    }
    Group* findGroupByName(string groupName);
    User* findUserByUsername(string username)
    {
        User* temp=users;
        while (temp!=nullptr)
        {
            if (temp->getUsername()==username)
            {
                return temp;
            }
            temp=temp->next;
        }
        return nullptr;
    }
    ~SocialNetwork()
    {
        User* nextUser;
        while (users!=nullptr)
        {
            nextUser=users->next;
            delete users;
            users=nextUser;
        }
    }
};
void Message::sendMessage()
{
    cout<<"Message sent from "<< sender->getUsername()<<" to "<< receiver->getUsername()<< endl;
}
void User::createPost(string content)
{
    Post* post=new Post(postCount+1,this,content);
    if(!posts)
    {
        posts = post;
    }
    else
    {
        post->next=posts;
        posts->prev=post;
        posts=post;
    }
    postCount++;
}
void User::deletePost(Post* post)
{
    if(post==posts)
    {
        posts=post->next;
        if (posts)
        {
            posts->prev=nullptr;
        }
    }
    else
    {
        if(post->prev)
        {
            post->prev->next=post->next;
        }
        if(post->next)
        {
            post->next->prev=post->prev;
        }
    }
    delete post;
    cout<<"Post deleted successfully!"<<endl;
}
void User::displayPosts()
{
        cout<<"Posts by "<<username<<":"<< endl;
        Post* currentPost=posts;
        while(currentPost)
        {
            cout<<"-"<<currentPost->postID<<"- "<<currentPost->content<<endl;
            currentPost=currentPost->next;
        }
        cout<<"-------------------------------------"<<endl;
}
void User::addFriend(User* user)
{
    Friendship* friendship=new Friendship(this, user);
    if (!friendships)
    {
        friendships = friendship;
    }
    else
    {
        friendship->next = friendships;
        friendships->prev = friendship;
        friendships = friendship;
    }
    friendshipCount++;
    user->addReverseFriendship(friendship);
    cout << "Friend added successfully!" << endl;
}
void User::addReverseFriendship(Friendship* friendship)
{
    if (!friendships)
    {
        friendships = friendship;
    } else
    {
        friendship->next = friendships;
        friendships->prev = friendship;
        friendships = friendship;
    }
    friendshipCount++;
}
void User::removeFriend(User* user)
{
    Friendship* currFriendship = friendships;
    while (currFriendship != nullptr)
    {
        if (currFriendship->user1 == this && currFriendship->user2 == user)
        {
            if (currFriendship->prev)
            {
                currFriendship->prev->next = currFriendship->next;
            }
            if (currFriendship->next)
            {
                currFriendship->next->prev = currFriendship->prev;
            }
            if (currFriendship == friendships)
            {
                friendships = currFriendship->next;
            }
            delete currFriendship;
            cout << "Friend removed successfully!" << endl;
            return;
        }
        if (currFriendship->user1 == user && currFriendship->user2 == this)
        {
            if (currFriendship->prev) {
                currFriendship->prev->next = currFriendship->next;
            }
            if (currFriendship->next) {
                currFriendship->next->prev = currFriendship->prev;
            }
            if (currFriendship == friendships) {
                friendships = currFriendship->next;
            }
            delete currFriendship;
            cout << "Friend removed successfully!" << endl;
            return;
        }
        currFriendship = currFriendship->next;
    }
}
void User::sendNotification(string message)
{
    Notification* notification = new Notification(notificationCount+1,this,message);
    if (!notifications)
    {
        notifications = notification;
    }
    else
    {
        notification->next = notifications;
        notifications->prev = notification;
        notifications = notification;
    }
    notificationCount++;
}
void User::displayNotifications()
{
        cout << "Notifications for " << username << ":" << endl;
        Notification* currentNotification = notifications;
        while (currentNotification)
        {
            cout <<currentNotification->notificationID<<"- " << currentNotification->message << endl;
            currentNotification = currentNotification->next;
        }
        cout << "-----------------------" << endl;
}
void User::sendMessage(User* receiver, string content)
{
    Message* message = new Message(messageCount+1,this,receiver,content);
    if (!messages)
    {
        messages = message;
    }
    else
    {
        message->next = messages;
        messages->prev = message;
        messages = message;
    }
    messageCount++;
    receiver->addReverseMessage(message);
    message->sendMessage();
}
void User::addReverseMessage(Message* message)
{
    if (!messages)
    {
        messages = message;
    }
    else
    {
        message->next = messages;
        messages->prev = message;
        messages = message;
    }
    messageCount++;
}
void User::addReverseComment(Comment* comment)
{
    if (!comments)
    {
        comments = comment;
    }
    else
    {
        comment->next = comments;
        comments->prev = comment;
        comments = comment;
    }
}
void User::displayFriendsList()
{
        cout << "Friends List for " << username << ":" << endl;
        Friendship* currFriendship = friendships;
        while (currFriendship != nullptr)
        {
            if (currFriendship->user1 == this)
            {
                cout << "- " << currFriendship->user2->username << endl;
            }
            else
            {
                cout << "- " << currFriendship->user1->username << endl;
            }
            currFriendship = currFriendship->next;
        }
    }
User::~User()
{
    Post* nextPost;
    while (posts != nullptr)
    {
        nextPost = posts->next;
        delete posts;
        posts = nextPost;
    }
    Comment* nextComment;
    while (comments != nullptr)
    {
        nextComment = comments->next;
        delete comments;
        comments = nextComment;
    }
    Friendship* nextFriendship;
    while (friendships != nullptr)
    {
        nextFriendship = friendships->next;
        delete friendships;
        friendships = nextFriendship;
    }
    Notification* nextNotification;
    while (notifications != nullptr)
    {
        nextNotification = notifications->next;
        delete notifications;
        notifications = nextNotification;
    }
    Message* nextMessage;
    while (messages != nullptr)
    {
        nextMessage = messages->next;
        delete messages;
        messages = nextMessage;
    }
}
void Post::addComment(User* user, string content)
{
    Comment* newComment = new Comment(commentCount + 1, user, this, content);
    if (!comments)
    {
        comments = newComment;
    }
    else
    {
        newComment->next = comments;
        comments->prev = newComment;
        comments = newComment;
    }
    commentCount++;
    user->addReverseComment(newComment);
    cout << "Comment added successfully!" << endl;
}

void Post::deleteComment(Comment* comment)
{
    if (comment == comments)
    {
        comments = comment->next;
        if (comments)
        {
            comments->prev = nullptr;
        }
    }
    else
    {
        if (comment->prev)
        {
            comment->prev->next = comment->next;
        }
        if (comment->next)
        {
            comment->next->prev = comment->prev;
        }
    }
    delete comment;
    cout << "Comment deleted successfully!" << endl;
}

void Post::displayComment()
{
    cout << "Comments for Post " << postID << ":" << endl;
    Comment* currentComment = comments;
    while (currentComment)
    {
        cout << "-" << currentComment->user->getUsername() << ":" << currentComment->content <<"-"<<currentComment->commentID<< endl;
        currentComment=currentComment->next;
    }
    cout << "-----------------------" << endl;
}

void Group::addMember(User* user)
{
    User* temp = members;
    while (temp != nullptr)
    {
        if (temp == user)
        {
            throw invalid_argument("User is already a member of the group.");
        }
        temp = temp->next;
    }
    User* newMember = new User(user->username, user->password, user->email);
    if (!members)
    {
        members = newMember;
    }
    else
    {
        newMember->next = members;
        members->prev = newMember;
        members = newMember;
    }
}
Group* SocialNetwork::createGroup(string groupName)
    {
        Group* newGroup = new Group(groupName);
        if (!groups)
        {
            groups = newGroup;
        }
        else
        {
            newGroup->next = groups;
            groups->prev = newGroup;
            groups = newGroup;
        }
        return newGroup;
    }
void Group::removeMember(User* user)
{
    User* temp = members;
    while (temp != nullptr)
    {
        if (temp == user)
        {
            if (temp == members)
            {
                members = temp->next;
                if (members)
                {
                    members->prev = nullptr;
                }
            }
            else
            {
                if (temp->prev)
                {
                    temp->prev->next = temp->next;
                }
                if (temp->next)
                {
                    temp->next->prev = temp->prev;
                }
            }
            delete temp;
            cout << "Member removed successfully!" << endl;
            return;
        }
        temp = temp->next;
    }
    throw invalid_argument("Member not found in the group.");
}
void Group::displayMembers()
{
    cout << "Members of Group: " << groupName << endl;
    User* temp = members;
    while (temp != nullptr)
    {
        cout << temp->getUsername() << endl;
        temp = temp->next;
    }
    cout << endl;
}

Group* SocialNetwork::findGroupByName(string groupName)
{
    Group* temp = groups;
    while (temp != nullptr)
    {
        if (temp->groupName == groupName)
        {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
int main()
{
    try{
    SocialNetwork socialNetwork;
    int choice;
    while(1)
    {
        cout << "----------FEATURES----------" << endl;
        cout << "1. Create User" << endl;
        cout << "2. Delete User" << endl;
        cout << "3. Create Post" << endl;
        cout << "4. Delete Post" << endl;
        cout << "5. Display Posts" << endl;
        cout << "6. Add Friend" << endl;
        cout << "7. Remove Friend" << endl;
        cout << "8. Display Friends List" << endl;
        cout << "9. Send Notification" << endl;
        cout << "10. Send Message" << endl;
        cout << "11. Display notification" << endl;
        cout << "12. Create Group" << endl;
        cout << "13. Add Member to Group" << endl;
        cout << "14. Print Group Members" << endl;
        cout << "15. Add Comment" << endl;
        cout << "16. Display Comment" << endl;
        cout << "17. Delete Comment" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:{
            string username, password, email;
               cout << "Enter username: ";
             cin >> username;
            cout << "Enter password: ";
            cin >> password;
            cout << "Enter email: ";
            cin >> email;
            User* newUser = socialNetwork.createUser(username, password, email);
            cout << "User created successfully!" << endl;
            break;
        }
        case 2:{
            string username;
            cout << "Enter the username of the user to delete: ";
            cin >> username;
            User* userToDelete = socialNetwork.findUserByUsername(username);
            if (userToDelete)
            {
                socialNetwork.deleteUser(userToDelete);
            }
            else
                throw MyException();
            break;
        }
        case 3:{
            string username, content;
            cout << "Enter your username: ";
            cin >> username;
            User* user = socialNetwork.findUserByUsername(username);
            if (!user)
            {
                throw("Create Post error");
            }
            cout << "Enter the content of the post: ";
            cin.ignore();
            getline(cin, content);
            user->createPost(content);
            cout << "Post created successfully!" << endl;
            break;
        }
        case 4: {
            string username;
            int postId;
            cout << "Enter your username: ";
            cin >> username;
            User* user = socialNetwork.findUserByUsername(username);
            if (!user)
            {
                throw("Delete Post error");
            }
            cout << "Enter the ID of the post to delete: ";
            cin >> postId;
            Post* post = user->posts;
            while (post)
            {
                if (post->postID == postId)
                {
                    user->deletePost(post);
                    break;
                }
                post = post->next;
            }
            break;
        }
         case 5: {
                string username;
                cout << "Enter your username: ";
                cin >> username;
                User* user = socialNetwork.findUserByUsername(username);
                if (user != nullptr)
                {
                    user->displayPosts();
                }
                else
                {
                    cout << "User not found!" << endl;
                }
                break;
            }
        case 6:{
            string username1, username2;
            cout << "Enter the username of the first user: ";
            cin >> username1;
            cout << "Enter the username of the second user: ";
            cin >> username2;
            User* user1 = socialNetwork.findUserByUsername(username1);
            User* user2 = socialNetwork.findUserByUsername(username2);
            if (!user1 || !user2)
            {
                throw("Adding friend error");
            }
            user1->addFriend(user2);
            break;
        }
        case 7:{
            string username1, username2;
            cout << "Enter the username of the first user: ";
            cin >> username1;
            cout << "Enter the username of the second user: ";
            cin >> username2;
            User* user1 = socialNetwork.findUserByUsername(username1);
            User* user2 = socialNetwork.findUserByUsername(username2);
            if (!user1 || !user2)
            {
                throw("Remove Friend Error");
            }
            user1->removeFriend(user2);
            break;
        }
        case 8: {
                string username;
                cout << "Enter your username: ";
                cin >> username;
                User* user = socialNetwork.findUserByUsername(username);
                if (user != nullptr)
                {
                    user->displayFriendsList();
                }
                else
                {
                    cout << "User not found!" << endl;
                }
                break;
            }
        case 9:{
            string username, message;
            cout << "Enter your username: ";
            cin >> username;
            User* user = socialNetwork.findUserByUsername(username);
            if (!user)
            {
                throw("Notification Error");
            }
            cout << "Enter the notification message: ";
            cin.ignore();
            getline(cin, message);
            user->sendNotification(message);
            break;
        }
        case 10:{
            string senderUsername, receiverUsername, message;
            cout << "Enter the username of the sender: ";
            cin >> senderUsername;
            cout << "Enter the username of the receiver: ";
            cin >> receiverUsername;
            User* sender = socialNetwork.findUserByUsername(senderUsername);
            User* receiver = socialNetwork.findUserByUsername(receiverUsername);
            if (!sender || !receiver)
            {
               throw("Sending Message Error");
            }
            cout << "Enter the message content: ";
            cin.ignore();
            getline(cin, message);
            sender->sendMessage(receiver, message);
            break;
        }
        case 11: {
                string username;
                cout << "Enter your username: ";
                cin >> username;
                User* user = socialNetwork.findUserByUsername(username);
                if (user != nullptr)
                {
                    user->displayNotifications();
                } else
                {
                    cout << "User not found!" << endl;
                }
                break;
            }
        case 12: {
            string groupName;
                cout << "Enter the group name: ";
                cin.ignore();
                getline(cin, groupName);
                Group* newGroup = socialNetwork.createGroup(groupName);
                if (newGroup)
                {
                    cout << "Group created successfully!" << endl;
                }
                else
                {
                    cout << "Failed to create the group!" << endl;
                }
                break;
        }
        case 13: {
            string username, groupName;
            cout << "Enter the username of the user to add: ";
            cin >> username;
            User* user = socialNetwork.findUserByUsername(username);
            if (!user)
            {
                throw("Adding Member Error");
            }
            cout << "Enter the group name: ";
            cin.ignore();
            getline(cin, groupName);
            Group* group = nullptr;
            group = socialNetwork.findGroupByName(groupName);
            if (!group)
            {
                cout << "Group not found!" << endl;
                break;
            }
            group->addMember(user);
            cout << "User added to the group successfully!" << endl;
            break;
        }
        case 14: {
            string groupName;
            cout << "Enter the group name: ";
            cin.ignore();
            getline(cin, groupName);
            Group* group = nullptr;
            group = socialNetwork.findGroupByName(groupName);
            if (group)
            {
                group->displayMembers();
            }
            else
            {
                cout << "Group not found!" << endl;
            }
            break;
            }
        case 15:{
            string commentContent,username;
            cout << "Enter username of author: ";
            cin >> username;
            User* user1 = socialNetwork.findUserByUsername(username);
            cout << "Enter your username: ";
            cin >> username;
            User* user2 = socialNetwork.findUserByUsername(username);
            if (!user1)
            {
                throw("Adding Comment Error");
            }
            int postID;
            cout << "Enter the ID of the post to add a comment to: ";
            cin >> postID;
            cout << "Enter the content of the comment: ";
            cin.ignore();
            getline(cin, commentContent);
            Post* post = user1->posts;
            while (post)
            {
                if (post->postID == postID)
                {
                    post->addComment(user2, commentContent);
                    break;
                }
                post = post->next;
            }
            break;
        }
        case 16:{
            string username;
                    cout << "Enter your username of author: ";
                    cin >> username;
                    User* user1 = socialNetwork.findUserByUsername(username);
                    if (user1 != nullptr)
                    {
                        user1->displayPosts();
                        int postId;
                        cout << "Enter the ID of the post to display comments: ";
                        cin >> postId;
                        Post* post = user1->posts;
                        while (post)
                        {
                            if (post->postID == postId)
                            {
                                post->displayComment();
                                break;
                            }
                            post = post->next;
                        }
                    }
                    else
                    {
                        cout << "User not found!" << endl;
                    }
                    break;
        }
        case 17:{
             string username;
                    cout << "Enter your username: ";
                    cin >> username;
                    User* user = socialNetwork.findUserByUsername(username);
                    if (user != nullptr)
                    {
                        user->displayPosts();
                        int postId;
                        cout << "Enter the ID of the post to delete a comment: ";
                        cin >> postId;
                        Post* post = user->posts;
                        while (post)
                        {
                            if (post->postID == postId)
                            {
                                post->displayComment();
                                int commentId;
                                cout << "Enter the ID of the comment to delete: ";
                                cin >> commentId;
                                Comment* comment = post->comments;
                                while (comment)
                                {
                                    if (comment->commentID == commentId)
                                    {
                                        post->deleteComment(comment); // To delete the selected comment
                                        break;
                                    }
                                    comment = comment->next;
                                }
                                break;
                            }
                            post = post->next;
                        }
                    }
                    else
                    {
                        cout << "User not found!" << endl;
                    }
                    break;
                }
        case 0:
            exit(0);
        default:{
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
      }
    }
    catch(MyException &e)
    {
    cout<<"------"<<e.myEx();
    }
    return 0;
}
