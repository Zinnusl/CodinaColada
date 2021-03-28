#include <cstdio>

#include "../../networking/Network.h"

enum class CustomMsgTypes : uint32_t
{
	ServerAccept,
	ServerDeny,
	ServerPing,
	MessageAll,
	ServerMessage,
};


class CustomServer : public colada::network::Server<CustomMsgTypes>
{
public:
	CustomServer(uint16_t nPort) : colada::network::Server<CustomMsgTypes>(nPort)
	{

	}

protected:
	virtual bool OnClientConnect(std::shared_ptr<colada::network::Connection<CustomMsgTypes>> client)
	{
		colada::network::message<CustomMsgTypes> msg;
		msg.header.id = CustomMsgTypes::ServerAccept;
		client->Send(msg);
		return true;
	}

	// Called when a client appears to have disconnected
	virtual void OnClientDisconnect(std::shared_ptr<colada::network::Connection<CustomMsgTypes>> client)
	{
		printf("Removing client [%d]\n", client->GetID());
	}

	// Called when a message arrives
	virtual void OnMessage(std::shared_ptr<colada::network::Connection<CustomMsgTypes>> client, colada::network::message<CustomMsgTypes>& msg)
	{
		switch (msg.header.id)
		{
		case CustomMsgTypes::ServerPing:
		{
			printf("Server Ping [%d]\n", client->GetID());

			// Simply bounce message back to client
			client->Send(msg);
		}
		break;

		case CustomMsgTypes::MessageAll:
		{
			printf("Message All [%d]\n", client->GetID());

			// Construct a new message and send it to all clients
			colada::network::message<CustomMsgTypes> msg;
			msg.header.id = CustomMsgTypes::ServerMessage;
			msg << client->GetID();
			MessageAllClients(msg, client);
		}
		break;
		}
	}
};