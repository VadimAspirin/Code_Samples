using System;
using System.Threading;
 
namespace ChatServer
{
    class Program
    {
        static void Main(string[] args)
        {
		if (args.Length == 1)
		{
			ServerObject server = new ServerObject(Convert.ToInt32(args[0]));
			//server.Disconnect();
		}
		else
		{
			ServerObject server = new ServerObject();
			//server.Disconnect();
		}
        }
    }
}
