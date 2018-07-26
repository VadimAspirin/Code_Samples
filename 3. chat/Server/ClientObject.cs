using System;
using System.Net.Sockets;
using System.Text;
 
namespace ChatServer
{
    public class ClientObject
    {
        protected internal string Id { get; private set; }
        protected internal NetworkStream Stream {get; private set;}
        private string userName;
        private TcpClient client;
        private ServerObject server; // объект сервера
 
        public ClientObject(TcpClient tcpClient, ServerObject serverObject)
        {
            Id = Guid.NewGuid().ToString();
            client = tcpClient;
            server = serverObject;
            server.AddConnection(this);
        }
 
        public void Process()
        {
			Stream = client.GetStream();
			// получаем имя пользователя
			string message = GetMessage();
			userName = message;

			message = userName + " вошел в чат";
			// посылаем сообщение о входе в чат всем подключенным пользователям
			server.BroadcastMessage(message, this.Id);
			Console.WriteLine(message);
			// в бесконечном цикле получаем сообщения от клиента
			while (true)
			{
				message = GetMessage();
				if (message.Length != 0)
				{
					message = String.Format("{0}: {1}", userName, message);
					Console.WriteLine(message);
					server.BroadcastMessage(message, this.Id);
				}
				else
				{
					message = String.Format("{0} покинул чат", userName);
					Console.WriteLine(message);
					server.BroadcastMessage(message, this.Id);

					server.RemoveConnection(this.Id);
					Close();
					break;
				}
			}
        }
 
        // чтение входящего сообщения и преобразование в строку
        private string GetMessage()
        {
            byte[] data = new byte[64]; // буфер для получаемых данных
            StringBuilder builder = new StringBuilder();
            int bytes = 0;
            do
            {
                bytes = Stream.Read(data, 0, data.Length);
                builder.Append(Encoding.Unicode.GetString(data, 0, bytes));
            }
            while (Stream.DataAvailable);
 
            return builder.ToString();
        }
 
        // закрытие подключения
        protected internal void Close()
        {
            if (Stream != null)
                Stream.Close();
            if (client != null)
                client.Close();
        }
    }
}
