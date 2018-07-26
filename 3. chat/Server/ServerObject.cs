using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using System.Net;
using System.Text;
using System.Threading;
 
namespace ChatServer
{
	public class ServerObject
	{
        	private TcpListener tcpListener; // сервер для прослушивания
        	private List<ClientObject> clients; // все подключения
		private Thread listenThread;
		private int port;

		public ServerObject (int port = 8888)
		{
			this.port = port;
			clients = new List<ClientObject>();
			listenThread = new Thread(new ThreadStart(Listen));
			listenThread.Start();
		}
 
        protected internal void AddConnection(ClientObject clientObject)
        {
		clients.Add(clientObject);
        }
        protected internal void RemoveConnection(string id)
        {
		// получаем по id закрытое подключение
		ClientObject client = clients.FirstOrDefault(c => c.Id == id);
		// и удаляем его из списка подключений
		if (client != null)
			clients.Remove(client);
        }
        // прослушивание входящих подключений
        private void Listen()
        {
		tcpListener = new TcpListener(IPAddress.Any, port);
		tcpListener.Start();
		Console.WriteLine("Сервер запущен. Ожидание подключений...");

		while (true)
		{
			TcpClient tcpClient = tcpListener.AcceptTcpClient();

			ClientObject clientObject = new ClientObject(tcpClient, this);
			Thread clientThread = new Thread(new ThreadStart(clientObject.Process));
			clientThread.Start();
		}
        }
 
        // трансляция сообщения подключенным клиентам
        protected internal void BroadcastMessage(string message, string id)
        {
		byte[] data = Encoding.Unicode.GetBytes(message);
		for (int i = 0; i < clients.Count; i++)
		{
			if (clients[i].Id!= id) // если id клиента не равно id отправляющего
			{
		    	clients[i].Stream.Write(data, 0, data.Length); //передача данных
			}
		}
        }
        // отключение всех клиентов
        public void Disconnect()
        {
		listenThread.Abort();
		tcpListener.Stop(); //остановка сервера

		for (int i = 0; i < clients.Count; i++)
		{
			clients[i].Close(); //отключение клиента
		}
		Environment.Exit(0); //завершение процесса
        }
    }
}
