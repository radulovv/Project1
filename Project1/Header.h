
#ifndef Header_H
#define Header_H
public class Callback : App42Callback
{
	String gameName = "<Enter_your_game/level_name>";
	String userName = "Nick";
	double gameScore = 3500;
	scoreBoardService.SaveUserScore(gameName, userName, gameScore, this);
	void App42Callback.OnException(App42Exception exception)
	{
		Console.WriteLine("Exception Message" + exception);
	}
	void App42Callback.OnSuccess(Object response)
	{
		Game game = (Game)response;
		Console.WriteLine("gameName is " + game.GetName());
		for (int i = 0; i<game.GetScoreList().Count; i++)
		{
			Console.WriteLine("userName is : " + game.GetScoreList()[i].GetUserName());
			Console.WriteLine("score is : " + game.GetScoreList()[i].GetValue());
			Console.WriteLine("scoreId is : " + game.GetScoreList()[i].GetScoreId());
		}
	}
}

#endif
