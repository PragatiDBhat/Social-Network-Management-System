

# Social Network Management System

The Social Network Management System is designed to manage users, posts, comments, friendships, messages, groups, and notifications within a social network. The system includes several classes, each with specific attributes and methods to handle various functionalities.

### Classes and Their Descriptions

#### 1. Social Network
The `Social Network` class serves as the primary container for all users within the system.
- **Attributes**:
  - `users: vector<user*>`: A vector containing pointers to all user objects.
- **Methods**:
  - `+create user(user*): void`: Method to create a new user.
  - `+delete user(user*): void`: Method to delete an existing user.
  - `+finduserbyname(user*): user*`: Method to find a user by their username.

#### 2. User
The `User` class represents an individual user in the social network.
- **Attributes**:
  - `+username: string`: The username of the user.
  - `+password: string`: The user's password.
  - `+email: string`: The user's email address.
  - `+profile pic: string`: The user's profile picture.
  - `+posts: post*`: A collection of posts made by the user.
  - `+comment: comment*`: A collection of comments made by the user.
  - `+friendship: friend*`: A collection of friends associated with the user.
  - `+notification: notification*`: A collection of notifications received by the user.
  - `+messages: message*`: A collection of messages sent or received by the user.
- **Methods**:
  - `+getusername()`: Returns the username of the user.
  - `+updateprofilepic()`: Updates the user's profile picture.
  - `+createpost()`: Creates a new post.
  - `+deletepost()`: Deletes an existing post.
  - `+addfriend()`: Adds a new friend.
  - `+removefriend()`: Removes an existing friend.
  - `+sendnotification()`: Sends a notification.
  - `+sendmessage()`: Sends a message.
  - `+User()`: Constructor for the User class.

#### 3. Post
The `Post` class represents a post made by a user.
- **Attributes**:
  - `+user: user*`: The user who made the post.
  - `+content: string`: The content of the post.
  - `+timestamp: string`: The time when the post was made.
  - `+comment: comment*`: A collection of comments associated with the post.
- **Methods**:
  - `+editContent()`: Edits the content of the post.
  - `+Post()`: Constructor for the Post class.
  - `+addComment()`: Adds a comment to the post.

#### 4. Comment
The `Comment` class represents a comment made on a post.
- **Attributes**:
  - `+user: user*`: The user who made the comment.
  - `+Post: post*`: The post on which the comment was made.
  - `+timestamp: string`: The time when the comment was made.
  - `+content: string`: The content of the comment.
- **Methods**:
  - `+editContent()`: Edits the content of the comment.
  - `+comment()`: Constructor for the Comment class.

#### 5. Friendship
The `Friendship` class represents a friendship between two users.
- **Attributes**:
  - `+User1: user*`: The first user in the friendship.
  - `+User2: user*`: The second user in the friendship.
  - `+dateEstablished: string`: The date when the friendship was established.
  - `+friendshipStatus: string`: The status of the friendship.
- **Methods**:
  - `+getdateestablin()`: Gets the date when the friendship was established.
  - `+Friendship()`: Constructor for the Friendship class.
  - `+getstatus()`: Gets the status of the friendship.
  - `+viewfriends()`: Views the friends associated with a user.

#### 6. Message
The `Message` class represents a message sent between users.
- **Attributes**:
  - `+send: user*`: The user who sent the message.
  - `+receiver: user*`: The user who received the message.
  - `+content: string`: The content of the message.
  - `+timestamp: string`: The time when the message was sent.
- **Methods**:
  - `+message()`: Constructor for the Message class.
  - `+editcontent()`: Edits the content of the message.
  - `+sendmessage()`: Sends the message.

#### 7. Group
The `Group` class represents a group within the social network.
- **Attributes**:
  - `+groupname: string`: The name of the group.
  - `+member: user*`: A collection of users who are members of the group.
- **Methods**:
  - `+Group()`: Constructor for the Group class.
  - `+viewmember()`: Views the members of the group.
  - `+addmember()`: Adds a member to the group.
  - `+deletemember()`: Deletes a member from the group.

#### 8. Notification
The `Notification` class represents a notification received by a user.
- **Attributes**:
  - `+user: user*`: The user who received the notification.
  - `+timestamp: string`: The time when the notification was received.
  - `+mess: string`: The message content of the notification.
- **Methods**:
  - `+Notification()`: Constructor for the Notification class.
  - `+viewNotification()`: Views the notification.

