using System;
using System.Threading;
using System.Net.Sockets;
using System.Text;
 
namespace ChatClient
{
    class Program
    {
        static void Main(string[] args)
        {
		Console.Write("Введите свое имя: ");
		if (args.Length == 2)
		{
			Chat chat = new Chat (Console.ReadLine(), args[0], Convert.ToInt32(args[1]));
			Console.WriteLine("Добро пожаловать, {0}", chat.UserName);
			for(int i = 0; i < 3; i++)
				chat.SendMessage(Console.ReadLine());
			Console.WriteLine("До свидания, {0}!", chat.UserName);
			chat.Disconnect();
		}
		else
		{
			Chat chat = new Chat (Console.ReadLine());
			Console.WriteLine("Добро пожаловать, {0}", chat.UserName);
			for(int i = 0; i < 3; i++)
				chat.SendMessage(Console.ReadLine());
			Console.WriteLine("До свидания, {0}!", chat.UserName);
			chat.Disconnect();
		}
        }
    }
}
