/*

	PROJECT:		mod_sa
	LICENSE:		See LICENSE in the top level directory
	COPYRIGHT:		Copyright we_sux, BlastHack

	mod_sa is available from https://github.com/BlastHackNet/mod_s0beit_sa/

	mod_sa is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	mod_sa is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with mod_sa.  If not, see <http://www.gnu.org/licenses/>.

*/

#define RAKNET_MAX_PACKET	256

extern class RakClient *g_RakClient;

typedef unsigned int RakNetTime;
typedef long long RakNetTimeNS;

enum RPCEnumeration
{
	RPC_ClickPlayer					= 23,
	RPC_ClientJoin					= 25,
	RPC_EnterVehicle				= 26,
	RPC_EnterEditObject				= 27,
	RPC_ScriptCash					= 31,
	RPC_ServerCommand				= 50,
	RPC_Spawn						= 52,
	RPC_Death						= 53,
	RPC_NPCJoin						= 54,
	RPC_DialogResponse				= 62,
	RPC_ClickTextDraw				= 83,
	RPC_SCMEvent					= 96,
	RPC_Chat						= 101,
	RPC_SrvNetStats					= 102,
	RPC_ClientCheck					= 103,
	RPC_DamageVehicle				= 106,
	RPC_GiveTakeDamage				= 115,
	RPC_EditAttachedObject			= 116,
	RPC_EditObject					= 117,
	RPC_SetInteriorId				= 118,
	RPC_MapMarker					= 119,
	RPC_RequestClass				= 128,
	RPC_RequestSpawn				= 129,
	RPC_PickedUpPickup				= 131,
	RPC_MenuSelect					= 132,
	RPC_VehicleDestroyed			= 136,
	RPC_MenuQuit					= 140,
	RPC_ExitVehicle					= 154,
	RPC_UpdateScoresPingsIPs		= 155,

	// server RPC's
	RPC_SetPlayerName				= 11,
	RPC_SetPlayerPos				= 12,
	RPC_SetPlayerPosFindZ			= 13,
	RPC_SetPlayerHealth				= 14,
	RPC_TogglePlayerControllable	= 15,
	RPC_PlaySound					= 16,
	RPC_SetPlayerWorldBounds		= 17,
	RPC_GivePlayerMoney				= 18,
	RPC_SetPlayerFacingAngle		= 19,
	RPC_ResetPlayerMoney			= 20,
	RPC_ResetPlayerWeapons			= 21,
	RPC_GivePlayerWeapon			= 22,
	RPC_SetVehicleParamsEx			= 24,
	RPC_CancelEdit					= 28,
	RPC_SetPlayerTime				= 29,
	RPC_ToggleClock					= 30,
	RPC_WorldPlayerAdd				= 32,
	RPC_SetPlayerShopName			= 33,
	RPC_SetPlayerSkillLevel			= 34,
	RPC_SetPlayerDrunkLevel			= 35,
	RPC_Create3DTextLabel			= 36,
	RPC_DisableCheckpoint			= 37,
	RPC_SetRaceCheckpoint			= 38,
	RPC_DisableRaceCheckpoint		= 39,
	RPC_GameModeRestart				= 40,
	RPC_PlayAudioStream				= 41,
	RPC_StopAudioStream				= 42,
	RPC_RemoveBuildingForPlayer		= 43,
	RPC_CreateObject				= 44,
	RPC_SetObjectPos				= 45,
	RPC_SetObjectRot				= 46,
	RPC_DestroyObject				= 47,
	RPC_DeathMessage				= 55,
	RPC_SetPlayerMapIcon			= 56,
	RPC_RemoveVehicleComponent		= 57,
	RPC_Update3DTextLabel			= 58,
	RPC_ChatBubble					= 59,
	RPC_UpdateSystemTime			= 60,
	RPC_ShowDialog					= 61,
	RPC_DestroyPickup				= 63,
	RPC_WeaponPickupDestroy			= 64,
	RPC_LinkVehicleToInterior		= 65,
	RPC_SetPlayerArmour				= 66,
	RPC_SetPlayerArmedWeapon		= 67,
	RPC_SetSpawnInfo				= 68,
	RPC_SetPlayerTeam				= 69,
	RPC_PutPlayerInVehicle			= 70,
	RPC_RemovePlayerFromVehicle		= 71,
	RPC_SetPlayerColor				= 72,
	RPC_DisplayGameText				= 73,
	RPC_ForceClassSelection			= 74,
	RPC_AttachObjectToPlayer		= 75,
	RPC_InitMenu					= 76,
	RPC_ShowMenu					= 77,
	RPC_HideMenu					= 78,
	RPC_CreateExplosion				= 79,
	RPC_ShowPlayerNameTagForPlayer	= 80,
	RPC_AttachCameraToObject		= 81,
	RPC_InterpolateCamera			= 82,
	RPC_SetObjectMaterial			= 84,
	RPC_GangZoneStopFlash			= 85,
	RPC_ApplyAnimation				= 86,
	RPC_ClearAnimations				= 87,
	RPC_SetPlayerSpecialAction		= 88,
	RPC_SetPlayerFightingStyle		= 89,
	RPC_SetPlayerVelocity			= 90,
	RPC_SetVehicleVelocity			= 91,
	RPC_SetPlayerDrunkVisuals		= 92,
	RPC_ClientMessage				= 93,
	RPC_SetWorldTime				= 94,
	RPC_CreatePickup				= 95,
	RPC_SetVehicleTireStatus		= 98,
	RPC_MoveObject					= 99,
	RPC_EnableStuntBonusForPlayer	= 104,
	RPC_TextDrawSetString			= 105,
	RPC_SetCheckpoint				= 107,
	RPC_GangZoneCreate				= 108,
	RPC_PlayCrimeReport				= 112,
	RPC_SetPlayerAttachedObject		= 113,
	RPC_GangZoneDestroy				= 120,
	RPC_GangZoneFlash				= 121,
	RPC_StopObject					= 122,
	RPC_SetNumberPlate				= 123,
	RPC_TogglePlayerSpectating		= 124,
	RPC_PlayerSpectatePlayer		= 126,
	RPC_PlayerSpectateVehicle		= 127,
	RPC_SetPlayerWantedLevel		= 133,
	RPC_ShowTextDraw				= 134,
	RPC_TextDrawHideForPlayer		= 135,
	RPC_ServerJoin					= 137,
	RPC_ServerQuit					= 138,
	RPC_InitGame					= 139,
	RPC_RemovePlayerMapIcon			= 144,
	RPC_SetPlayerAmmo				= 145,
	RPC_SetPlayerGravity			= 146,
	RPC_SetVehicleHealth			= 147,
	RPC_AttachTrailerToVehicle		= 148,
	RPC_DetachTrailerFromVehicle	= 149,
	RPC_SetPlayerDrunkHandling		= 150,
	RPC_DestroyPickups				= 151,
	RPC_SetWeather					= 152,
	RPC_SetPlayerSkin				= 153,
	RPC_SetPlayerInterior			= 156,
	RPC_SetPlayerCameraPos			= 157,
	RPC_SetPlayerCameraLookAt		= 158,
	RPC_SetVehiclePos				= 159,
	RPC_SetVehicleZAngle			= 160,
	RPC_SetVehicleParamsForPlayer	= 161,
	RPC_SetCameraBehindPlayer		= 162,
	RPC_WorldPlayerRemove			= 163,
	RPC_WorldVehicleAdd				= 164,
	RPC_WorldVehicleRemove			= 165,
	RPC_WorldPlayerDeath 			= 166,
};

enum PacketEnumeration
{
	ID_INTERNAL_PING = 6,
	ID_PING,
	ID_PING_OPEN_CONNECTIONS,
	ID_CONNECTED_PONG,
	ID_REQUEST_STATIC_DATA,
	ID_CONNECTION_REQUEST,
	ID_AUTH_KEY,
	ID_BROADCAST_PINGS = 15,
	ID_SECURED_CONNECTION_RESPONSE,
	ID_SECURED_CONNECTION_CONFIRMATION,
	ID_RPC_MAPPING,
	ID_SET_RANDOM_NUMBER_SEED = 21,
	ID_RPC,
	ID_RPC_REPLY,
	ID_DETECT_LOST_CONNECTIONS,
	ID_OPEN_CONNECTION_REQUEST,
	ID_OPEN_CONNECTION_REPLY,
	ID_RSA_PUBLIC_KEY_MISMATCH = 28,
	ID_CONNECTION_ATTEMPT_FAILED,
	ID_NEW_INCOMING_CONNECTION,
	ID_NO_FREE_INCOMING_CONNECTIONS,
	ID_DISCONNECTION_NOTIFICATION,
	ID_CONNECTION_LOST,
	ID_CONNECTION_REQUEST_ACCEPTED,
	ID_INITIALIZE_ENCRYPTION,
	ID_CONNECTION_BANNED,
	ID_INVALID_PASSWORD,
	ID_MODIFIED_PACKET,
	ID_PONG,
	ID_TIMESTAMP,
	ID_RECEIVED_STATIC_DATA,
	ID_REMOTE_DISCONNECTION_NOTIFICATION,
	ID_REMOTE_CONNECTION_LOST,
	ID_REMOTE_NEW_INCOMING_CONNECTION,
	ID_REMOTE_EXISTING_CONNECTION,
	ID_REMOTE_STATIC_DATA,
	ID_ADVERTISE_SYSTEM = 56,

	ID_VEHICLE_SYNC = 200,
	ID_AIM_SYNC = 203,
	ID_BULLET_SYNC = 206,
	ID_PLAYER_SYNC = 207,
	ID_MARKERS_SYNC,
	ID_UNOCCUPIED_SYNC,
	ID_TRAILER_SYNC,
	ID_PASSENGER_SYNC,
	ID_SPECTATOR_SYNC,
	ID_RCON_COMMAND,
	ID_RCON_RESPONCE,
	ID_WEAPONS_UPDATE,
	ID_STATS_UPDATE,
};

/// These enumerations are used to describe when packets are delivered.
enum PacketPriority
{
	SYSTEM_PRIORITY,   /// \internal Used by RakNet to send above-high priority messages.
	HIGH_PRIORITY,   /// High priority messages are send before medium priority messages.
	MEDIUM_PRIORITY,   /// Medium priority messages are send before low priority messages.
	LOW_PRIORITY,   /// Low priority messages are only sent when no other messages are waiting.
	NUMBER_OF_PRIORITIES
};

/// These enumerations are used to describe how packets are delivered.
/// \note  Note to self: I write this with 3 bits in the stream.  If I add more remember to change that
enum PacketReliability
{
	UNRELIABLE = 6,   /// Same as regular UDP, except that it will also discard duplicate datagrams.  RakNet adds (6 to 17) + 21 bits of overhead, 16 of which is used to detect duplicate packets and 6 to 17 of which is used for message length.
	UNRELIABLE_SEQUENCED,  /// Regular UDP with a sequence counter.  Out of order messages will be discarded.  This adds an additional 13 bits on top what is used for UNRELIABLE.
	RELIABLE,   /// The message is sent reliably, but not necessarily in any order.  Same overhead as UNRELIABLE.
	RELIABLE_ORDERED,   /// This message is reliable and will arrive in the order you sent it.  Messages will be delayed while waiting for out of order messages.  Same overhead as UNRELIABLE_SEQUENCED.
	RELIABLE_SEQUENCED /// This message is reliable and will arrive in the sequence you sent it.  Out or order messages will be dropped.  Same overhead as UNRELIABLE_SEQUENCED.
};

typedef unsigned short PlayerIndex;

#pragma pack(push, 1)
struct PlayerID
{
	///The peer address from inet_addr.
	unsigned int binaryAddress;
	///The port number
	unsigned short port;

	PlayerID& operator = (const PlayerID& input)
	{
		binaryAddress = input.binaryAddress;
		port = input.port;
		return *this;
	}

	bool operator==(const PlayerID& right) const;
	bool operator!=(const PlayerID& right) const;
	bool operator > (const PlayerID& right) const;
	bool operator < (const PlayerID& right) const;
};

struct NetworkID
{
	bool peerToPeer;
	PlayerID playerId;
	unsigned short localSystemId;
};

/// This represents a user message from another system.
struct Packet
{
	/// Server only - this is the index into the player array that this playerId maps to
	PlayerIndex playerIndex;

	/// The system that send this packet.
	PlayerID playerId;

	/// The length of the data in bytes
	/// \deprecated You should use bitSize.
	unsigned int length;

	/// The length of the data in bits
	unsigned int bitSize;

	/// The data from the sender
	unsigned char* data;

	/// @internal
	/// Indicates whether to delete the data, or to simply delete the packet.
	bool deleteData;
};

/// All RPC functions have the same parameter list - this structure.
struct RPCParameters
{
	/// The data from the remote system
	unsigned char *input;

	/// How many bits long \a input is
	unsigned int numberOfBitsOfData;

	/// Which system called this RPC
	PlayerID sender;

	/// Which instance of RakPeer (or a derived RakServer or RakClient) got this call
	void *recipient;

	/// You can return values from RPC calls by writing them to this BitStream.
	/// This is only sent back if the RPC call originally passed a BitStream to receive the reply.
	/// If you do so and your send is reliable, it will block until you get a reply or you get disconnected from the system you are sending to, whichever is first.
	/// If your send is not reliable, it will block for triple the ping time, or until you are disconnected, or you get a reply, whichever is first.
	BitStream *replyToSender;
};

struct RPCNode
{
	uint8_t uniqueIdentifier;
	void(*staticFunctionPointer) (RPCParameters *rpcParms);
};

/// Store Statistics information related to network usage 
struct RakNetStatisticsStruct
{
	///  Number of Messages in the send Buffer (high, medium, low priority)
	unsigned messageSendBuffer[NUMBER_OF_PRIORITIES];
	///  Number of messages sent (high, medium, low priority)
	unsigned messagesSent[NUMBER_OF_PRIORITIES];
	///  Number of data bits used for user messages
	unsigned messageDataBitsSent[NUMBER_OF_PRIORITIES];
	///  Number of total bits used for user messages, including headers
	unsigned messageTotalBitsSent[NUMBER_OF_PRIORITIES];

	///  Number of packets sent containing only acknowledgements
	unsigned packetsContainingOnlyAcknowlegements;
	///  Number of acknowledgements sent
	unsigned acknowlegementsSent;
	///  Number of acknowledgements waiting to be sent
	unsigned acknowlegementsPending;
	///  Number of acknowledgements bits sent
	unsigned acknowlegementBitsSent;

	///  Number of packets containing only acknowledgements and resends
	unsigned packetsContainingOnlyAcknowlegementsAndResends;

	///  Number of messages resent
	unsigned messageResends;
	///  Number of bits resent of actual data
	unsigned messageDataBitsResent;
	///  Total number of bits resent, including headers
	unsigned messagesTotalBitsResent;
	///  Number of messages waiting for ack (// TODO - rename this)
	unsigned messagesOnResendQueue;

	///  Number of messages not split for sending
	unsigned numberOfUnsplitMessages;
	///  Number of messages split for sending
	unsigned numberOfSplitMessages;
	///  Total number of splits done for sending
	unsigned totalSplits;

	///  Total packets sent
	unsigned packetsSent;

	///  Number of bits added by encryption
	unsigned encryptionBitsSent;
	///  total bits sent
	unsigned totalBitsSent;

	///  Number of sequenced messages arrived out of order
	unsigned sequencedMessagesOutOfOrder;
	///  Number of sequenced messages arrived in order
	unsigned sequencedMessagesInOrder;

	///  Number of ordered messages arrived out of order
	unsigned orderedMessagesOutOfOrder;
	///  Number of ordered messages arrived in order
	unsigned orderedMessagesInOrder;

	///  Packets with a good CRC received
	unsigned packetsReceived;
	///  Packets with a bad CRC received
	unsigned packetsWithBadCRCReceived;
	///  Bits with a good CRC received
	unsigned bitsReceived;
	///  Bits with a bad CRC received
	unsigned bitsWithBadCRCReceived;
	///  Number of acknowledgement messages received for packets we are resending
	unsigned acknowlegementsReceived;
	///  Number of acknowledgement messages received for packets we are not resending
	unsigned duplicateAcknowlegementsReceived;
	///  Number of data messages (anything other than an ack) received that are valid and not duplicate
	unsigned messagesReceived;
	///  Number of data messages (anything other than an ack) received that are invalid
	unsigned invalidMessagesReceived;
	///  Number of data messages (anything other than an ack) received that are duplicate
	unsigned duplicateMessagesReceived;
	///  Number of messages waiting for reassembly
	unsigned messagesWaitingForReassembly;
	///  Number of messages in reliability output queue
	unsigned internalOutputQueueSize;
	///  Current bits per second
	double bitsPerSecond;
	///  connection start time
	RakNetTime connectionStartTime;
};
#pragma pack(pop)

class RakClientInterface
{
public:
	virtual ~RakClientInterface() {};
	virtual bool Connect(const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer);
	virtual void Disconnect(unsigned int blockDuration, unsigned char orderingChannel = 0);
	virtual void InitializeSecurity(const char *privKeyP, const char *privKeyQ);
	virtual void SetPassword(const char *_password);
	virtual bool HasPassword(void) const;
	virtual bool Send(const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel);
	virtual bool Send(BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel);
	virtual Packet* Receive(void);
	virtual void DeallocatePacket(Packet *packet);
	virtual void PingServer(void);
	virtual void PingServer(const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections);
	virtual int GetAveragePing(void);
	virtual int GetLastPing(void) const;
	virtual int GetLowestPing(void) const;
	virtual int GetPlayerPing(const PlayerID playerId);
	virtual void StartOccasionalPing(void);
	virtual void StopOccasionalPing(void);
	virtual bool IsConnected(void) const;
	virtual unsigned int GetSynchronizedRandomInteger(void) const;
	virtual bool GenerateCompressionLayer(unsigned int inputFrequencyTable[256], bool inputLayer);
	virtual bool DeleteCompressionLayer(bool inputLayer);
	virtual void RegisterAsRemoteProcedureCall(int* uniqueID, void(*functionPointer) (RPCParameters *rpcParms));
	virtual void RegisterClassMemberRPC(int* uniqueID, void *functionPointer);
	virtual void UnregisterAsRemoteProcedureCall(int* uniqueID);
	virtual bool RPC(int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp);
	virtual bool RPC(int* uniqueID, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp);
	virtual bool RPC_(int* uniqueID, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp, NetworkID networkID);
	virtual void SetTrackFrequencyTable(bool b);
	virtual bool GetSendFrequencyTable(unsigned int outputFrequencyTable[256]);
	virtual float GetCompressionRatio(void) const;
	virtual float GetDecompressionRatio(void) const;
	virtual void AttachPlugin(void *messageHandler);
	virtual void DetachPlugin(void *messageHandler);
	virtual BitStream * GetStaticServerData(void);
	virtual void SetStaticServerData(const char *data, const int length);
	virtual BitStream * GetStaticClientData(const PlayerID playerId);
	virtual void SetStaticClientData(const PlayerID playerId, const char *data, const int length);
	virtual void SendStaticClientDataToServer(void);
	virtual PlayerID GetServerID(void) const;
	virtual PlayerID GetPlayerID(void) const;
	virtual PlayerID GetInternalID(void) const;
	virtual const char* PlayerIDToDottedIP(const PlayerID playerId) const;
	virtual void PushBackPacket(Packet *packet, bool pushAtHead);
	virtual void SetRouterInterface(void *routerInterface);
	virtual void RemoveRouterInterface(void *routerInterface);
	virtual void SetTimeoutTime(RakNetTime timeMS);
	virtual bool SetMTUSize(int size);
	virtual int GetMTUSize(void) const;
	virtual void AllowConnectionResponseIPMigration(bool allow);
	virtual void AdvertiseSystem(const char *host, unsigned short remotePort, const char *data, int dataLength);
	virtual RakNetStatisticsStruct * const GetStatistics(void);
	virtual void ApplyNetworkSimulator(double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance);
	virtual bool IsNetworkSimulatorActive(void);
	virtual PlayerIndex GetPlayerIndex(void);
};

enum NetPatchType
{
	INCOMING_RPC,
	OUTCOMING_RPC,
	INCOMING_PACKET,
	OUTCOMING_PACKET,
};

struct stNetPatch
{
	const char *name;
	int hotkey;
	bool enabled;
	byte id;
	NetPatchType type;
};

class RakClient
{
public:
	RakClient(void *pRakClientInterface);
	bool RPC(int rpcId, BitStream *bitStream, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED, char orderingChannel = 0, bool shiftTimestamp = false);
	bool Send(BitStream *bitStream, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = UNRELIABLE_SEQUENCED, char orderingChannel = 0);
	void SendDeath(uint16_t killerId, uint8_t reason);
	void RequestClass(int classId);
	void SendSCMEvent(int vehicleID, int eventId, int param1, int param2);
	void SendSpawn(void);
	void SendPickUp(int pickupId);
	RakClientInterface *GetInterface(void) { return pRakClient; };

private:
	RakClientInterface *pRakClient;
};