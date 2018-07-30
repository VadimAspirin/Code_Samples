using System;
using System.Threading;
using System.Net.Sockets;
using System.Text;
 
namespace ChatClient
{
    class Chat
    {
        public readonly string UserName;
        private string host;
        private int port;
	private Thread receiveThread;
        private TcpClient client;
        private NetworkStream stream;

	public Chat (string userName, string host = "127.0.0.1", int port = 8888)
	{
		if (userName.Length == 0)
			throw new ArgumentException ("error: Неверно задано имя");
		UserName = userName;
		this.host = host;
		this.port = port;
		client = new TcpClient();
		try
		{
			client.Connect(this.host, this.port); //подключение клиента
		}
		catch (SocketException)
		{
			throw new ArgumentException ("error: Сервер недоступен. Повторите позднее");
		}
		stream = client.GetStream(); // получаем поток

		byte[] data = Encoding.Unicode.GetBytes(UserName);
		stream.Write(data, 0, data.Length);

		// запускаем новый поток для получения данных
		receiveThread = new Thread(new ThreadStart(receiveMessage));
		receiveThread.Start(); //старт потока
	}

	private void receiveMessage()
        {
            while (true)
            {
		byte[] data = new byte[64]; // буфер для получаемых данных
		StringBuilder builder = new StringBuilder();
		int bytes = 0;
		do
		{
			bytes = stream.Read(data, 0, data.Length);
			builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
		}
		while (stream.DataAvailable);

		string message = builder.ToString();
		Console.WriteLine(message);//вывод сообщения
            }
        }

        public void SendMessage(string message)
        {
		byte[] data = Encoding.Unicode.GetBytes(message);
		stream.Write(data, 0, data.Length);
        }

        public void Disconnect()
        {
		receiveThread.Abort();
		if(stream!=null)
			stream.Close();//отключение потока
		if(client!=null)
			client.Close();//отключение клиента
		Environment.Exit(0); //завершение процесса
        }
    }
}
