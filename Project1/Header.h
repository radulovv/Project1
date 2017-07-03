#pragma once
ServiceAPI api = new ServiceAPI("b0f3a390ab9423bc7ffacafea3978faafe5bebc7fcd18645f9f6ae68e7a77ec3", "b6a0e6a49dcb58c145a53a68da163cff3143235b65ea713dbc667d32962a9fdc");

//Build User Service  
UserService userService = serviceAPI.BuildUserService();
// Using userService reference, you should be able to call all its method like create user/update user/authenticate etc.  
//Build Storage Service  
StorageService storageService = serviceAPI.BuildStorageService();

String userName = "Nick";
String pwd = "********";
String emailId = "nick@shephertz.com";
User user = userService.CreateUser(userName, pwd, emailId);
/* This will create user in App42 cloud and will return User object */
Console.WriteLine("userName is " + user.GetUserName());
Console.WriteLine("emailId is " + user.GetEmail());

String gameName = "<Enter_your_game/level_name>";
String userName = "Nick";
double gameScore = 3500;
Game game = scoreBoardService.SaveUserScore(gameName, userName, gameScore);
Console.WriteLine("gameName is " + game.GetName());
for (int i = 0; i<game.GetScoreList().Count; i++)
{
	Console.WriteLine("userName is : " + game.GetScoreList()[i].GetUserName());
	Console.WriteLine("score is : " + game.GetScoreList()[i].GetValue());
	Console.WriteLine("scoreId is : " + game.GetScoreList()[i].GetScoreId());
}