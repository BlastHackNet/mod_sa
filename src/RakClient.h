/* 
 * PROJECT: mod_sa
 * COPYRIGHT: FYP
 * DATE: 21.02.2013
 * FILE: RakClient.h
*/

extern class RakClient *g_RakClient;

typedef unsigned int RakNetTime;
typedef long long RakNetTimeNS;

enum RPCEnumeration
{
	RPC_ClickPlayer = 23,
	RPC_ClientJoin = 25,
	RPC_EnterVehicle = 26,
	RPC_EnterEditObject = 27,
	RPC_ScriptCash = 31,
	RPC_ServerCommand = 50,
	RPC_Spawn = 52,
	RPC_Death = 53,
	RPC_NPCJoin = 54,
	RPC_DialogResponse = 62,
	RPC_ClickTextDraw = 83,
	RPC_ScmEvent = 96,
	RPC_WeaponPickupDestroy = 97,
	RPC_Chat = 101,
	RPC_SrvNetStats = 102,
	RPC_ClientCheck = 103,
	RPC_DamageVehicle = 106,
	RPC_GiveTakeDamage = 115,
	RPC_EditAttachedObject = 116,
	RPC_EditObject = 117,
	RPC_SetInteriorId = 118,
	RPC_MapMarker = 119,
	RPC_RequestClass = 128,
	RPC_RequestSpawn = 129,
	RPC_PickedUpPickup = 131,
	RPC_MenuSelect = 132,
	RPC_VehicleDestroyed = 136,
	RPC_MenuQuit = 140,
	RPC_ExitVehicle = 154,
	RPC_UpdateScoresPingsIPs = 155
};

enum ScriptRPCEnumeration
{
	RPC_ScrSetPlayerName = 11,
	RPC_ScrSetPlayerPos = 12,
	RPC_ScrSetPlayerPosFindZ = 13,
	RPC_ScrSetPlayerHealth = 14,
	RPC_ScrTogglePlayerControllable = 15,
	RPC_ScrPlaySound = 16,
	RPC_ScrSetPlayerWorldBounds = 17,
	RPC_ScrGivePlayerMoney = 18,
	RPC_ScrSetPlayerFacingAngle = 19,
	RPC_ScrResetPlayerMoney = 20,
	RPC_ScrResetPlayerWeapons = 21,
	RPC_ScrGivePlayerWeapon = 22,
	RPC_ScrSetVehicleParamsEx = 24,
	RPC_ScrCancelEdit = 28,
	RPC_ScrSetPlayerTime = 29,
	RPC_ScrToggleClock = 30,
	RPC_ScrWorldPlayerAdd = 32,
	RPC_ScrSetPlayerShopName = 33,
	RPC_ScrSetPlayerSkillLevel = 34,
	RPC_ScrSetPlayerDrunkLevel = 35,
	RPC_ScrCreate3DTextLabel = 36,
	RPC_ScrDisableCheckpo= 37,
	RPC_ScrSetRaceCheckpo= 38,
	RPC_ScrDisableRaceCheckpo= 39,
	RPC_ScrGameModeRestart = 40,
	RPC_ScrPlayAudioStream = 41,
	RPC_ScrStopAudioStream = 42,
	RPC_ScrRemoveBuildingForPlayer = 43,
	RPC_ScrCreateObject = 44,
	RPC_ScrSetObjectPos = 45,
	RPC_ScrSetObjectRot = 46,
	RPC_ScrDestroyObject = 47,
	RPC_ScrDeathMessage = 55,
	RPC_ScrSetPlayerMapIcon = 56,
	RPC_ScrRemoveVehicleComponent = 57,
	RPC_ScrUpdate3DTextLabel = 58,
	RPC_ScrChatBubble = 59,
	RPC_ScrSomeupdate = 60,
	RPC_ScrShowDialog = 61,
	RPC_ScrDestroyPickup = 63,
	RPC_ScrLinkVehicleToInterior = 65,
	RPC_ScrSetPlayerArmour = 66,
	RPC_ScrSetPlayerArmedWeapon = 67,
	RPC_ScrSetSpawnInfo = 68,
	RPC_ScrSetPlayerTeam = 69,
	RPC_ScrPutPlayerInVehicle = 70,
	RPC_ScrRemovePlayerFromVehicle = 71,
	RPC_ScrSetPlayerColor = 72,
	RPC_ScrDisplayGameText = 73,
	RPC_ScrForceClassSelection = 74,
	RPC_ScrAttachObjectToPlayer = 75,
	RPC_ScrInitMenu = 76,
	RPC_ScrShowMenu = 77,
	RPC_ScrHideMenu = 78,
	RPC_ScrCreateExplosion = 79,
	RPC_ScrShowPlayerNameTagForPlayer = 80,
	RPC_ScrAttachCameraToObject = 81,
	RPC_ScrInterpolateCamera = 82,
	RPC_ScrSetObjectMaterial = 84,
	RPC_ScrGangZoneStopFlash = 85,
	RPC_ScrApplyAnimation = 86,
	RPC_ScrClearAnimations = 87,
	RPC_ScrSetPlayerSpecialAction = 88,
	RPC_ScrSetPlayerFightingStyle = 89,
	RPC_ScrSetPlayerVelocity = 90,
	RPC_ScrSetVehicleVelocity = 91,
	RPC_ScrClientMessage = 93,
	RPC_ScrSetWorldTime = 94,
	RPC_ScrCreatePickup = 95,
	RPC_ScrMoveObject = 99,
	RPC_ScrEnableStuntBonusForPlayer = 104,
	RPC_ScrTextDrawSetString = 105,
	RPC_ScrSetCheckpo= 107,
	RPC_ScrGangZoneCreate = 108,
	RPC_ScrPlayCrimeReport = 112,
	RPC_ScrSetPlayerAttachedObject = 113,
	RPC_ScrGangZoneDestroy = 120,
	RPC_ScrGangZoneFlash = 121,
	RPC_ScrStopObject = 122,
	RPC_ScrSetNumberPlate = 123,
	RPC_ScrTogglePlayerSpectating = 124,
	RPC_ScrPlayerSpectatePlayer = 126,
	RPC_ScrPlayerSpectateVehicle = 127,
	RPC_ScrSetPlayerWantedLevel = 133,
	RPC_ScrShowTextDraw = 134,
	RPC_ScrTextDrawHideForPlayer = 135,
	RPC_ScrServerJoin = 137,
	RPC_ScrServerQuit = 138,
	RPC_ScrInitGame = 139,
	RPC_ScrRemovePlayerMapIcon = 144,
	RPC_ScrSetPlayerAmmo = 145,
	RPC_ScrSetGravity = 146,
	RPC_ScrSetVehicleHealth = 147,
	RPC_ScrAttachTrailerToVehicle = 148,
	RPC_ScrDetachTrailerFromVehicle = 149,
	RPC_ScrSetWeather = 152,
	RPC_ScrSetPlayerSkin = 153,
	RPC_ScrSetPlayerInterior = 156,
	RPC_ScrSetPlayerCameraPos = 157,
	RPC_ScrSetPlayerCameraLookAt = 158,
	RPC_ScrSetVehiclePos = 159,
	RPC_ScrSetVehicleZAngle = 160,
	RPC_ScrSetVehicleParamsForPlayer = 161,
	RPC_ScrSetCameraBehindPlayer = 162,
	RPC_ScrWorldPlayerRemove = 163,
	RPC_ScrWorldVehicleAdd = 164,
	RPC_ScrWorldVehicleRemove = 165,
	RPC_ScrWorldPlayerDeath = 166
};

enum PacketEnumeration
{
	ID_INTERNAL_PING = 7,
	ID_PING,
	ID_PING_OPEN_CONNECTIONS,
	ID_CONNECTED_PONG,
	ID_REQUEST_STATIC_DATA,
	ID_CONNECTION_REQUEST,
	ID_AUTH_KEY,
	ID_BROADCAST_PINGS = 16,
	ID_SECURED_CONNECTION_RESPONSE,
	ID_SECURED_CONNECTION_CONFIRMATION,
	ID_RPC_MAPPING,
	ID_SET_RANDOM_NUMBER_SEED = 21,
	ID_RPC,
	ID_RPC_REPLY,
	ID_DETECT_LOST_CONNECTIONS,
	ID_OPEN_CONNECTION_REQUEST,
	ID_OPEN_CONNECTION_REPLY,
	ID_RSA_PUBLIC_KEY_MISMATCH = 29,
	ID_CONNECTION_ATTEMPT_FAILED,
	ID_NEW_INCOMING_CONNECTION,
	ID_NO_FREE_INCOMING_CONNECTIONS,
	ID_DISCONNECTION_NOTIFICATION,	
	ID_CONNECTION_LOST,
	ID_CONNECTION_REQUEST_ACCEPTED,
	ID_CONNECTION_BANNED = 37,
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

	ID_PLAYER_SYNC = 212,
	ID_MARKERS_SYNC = 213,
	ID_UNOCCUPIED_SYNC = 214,
	ID_TRAILER_SYNC = 215,
	ID_PASSENGER_SYNC = 216,
	ID_SPECTATOR_SYNC = 217,
	ID_AIM_SYNC = 218,
	ID_VEHICLE_SYNC = 219,
	ID_RCON_COMMAND = 220,
	ID_RCON_RESPONCE = 221,
	ID_WEAPONS_UPDATE = 222,
	ID_STATS_UPDATE = 223,
	ID_BULLET_SYNC = 224,
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

struct PlayerID
{
	///The peer address from inet_addr.
	unsigned int binaryAddress;
	///The port number
	unsigned short port;

	PlayerID& operator = ( const PlayerID& input )
	{
		binaryAddress = input.binaryAddress;
		port = input.port;
		return *this;
	}

	bool operator==( const PlayerID& right ) const;
	bool operator!=( const PlayerID& right ) const;
	bool operator > ( const PlayerID& right ) const;
	bool operator < ( const PlayerID& right ) const;
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

/// Store Statistics information related to network usage 
struct RakNetStatisticsStruct
{
	///  Number of Messages in the send Buffer (high, medium, low priority)
	unsigned messageSendBuffer[ NUMBER_OF_PRIORITIES ];
	///  Number of messages sent (high, medium, low priority)
	unsigned messagesSent[ NUMBER_OF_PRIORITIES ];
	///  Number of data bits used for user messages
	unsigned messageDataBitsSent[ NUMBER_OF_PRIORITIES ];
	///  Number of total bits used for user messages, including headers
	unsigned messageTotalBitsSent[ NUMBER_OF_PRIORITIES ];
	
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

class RakClientInterface
{
public:
	virtual ~RakClientInterface() { };
	virtual bool Connect( const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer );
	virtual void Disconnect( unsigned int blockDuration, unsigned char orderingChannel=0 );
	virtual void InitializeSecurity( const char *privKeyP, const char *privKeyQ );
	virtual void SetPassword( const char *_password );
	virtual bool HasPassword( void ) const;
	virtual bool Send( const char *data, const int length, PacketPriority priority, PacketReliability reliability, char orderingChannel );
	virtual bool Send( BitStream * bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel );
	virtual Packet* Receive( void );
	virtual void DeallocatePacket( Packet *packet );
	virtual void PingServer( void );
	virtual void PingServer( const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections );
	virtual int GetAveragePing( void );
	virtual int GetLastPing( void ) const;
	virtual int GetLowestPing( void ) const;
	virtual int GetPlayerPing( const PlayerID playerId );
	virtual void StartOccasionalPing( void );
	virtual void StopOccasionalPing( void );
	virtual bool IsConnected( void ) const;
	virtual unsigned int GetSynchronizedRandomInteger( void ) const;
	virtual bool GenerateCompressionLayer( unsigned int inputFrequencyTable[ 256 ], bool inputLayer );
	virtual bool DeleteCompressionLayer( bool inputLayer );
	virtual void RegisterAsRemoteProcedureCall( int* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) );
	virtual void RegisterClassMemberRPC( int* uniqueID, void *functionPointer );
	virtual void UnregisterAsRemoteProcedureCall( int* uniqueID );
	virtual bool RPC( int* uniqueID, const char *data, unsigned int bitLength, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp );
	virtual bool RPC( int* uniqueID, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp );
	virtual void Pad( void ); // XXX: Fix it.
	virtual void SetTrackFrequencyTable( bool b );
	virtual bool GetSendFrequencyTable( unsigned int outputFrequencyTable[ 256 ] );
	virtual float GetCompressionRatio( void ) const;
	virtual float GetDecompressionRatio( void ) const;
	virtual void AttachPlugin( void *messageHandler );
	virtual void DetachPlugin( void *messageHandler );
	virtual BitStream * GetStaticServerData( void );
	virtual void SetStaticServerData( const char *data, const int length );
	virtual BitStream * GetStaticClientData( const PlayerID playerId );
	virtual void SetStaticClientData( const PlayerID playerId, const char *data, const int length );
	virtual void SendStaticClientDataToServer( void );
	virtual PlayerID GetServerID( void ) const;
	virtual PlayerID GetPlayerID( void ) const;
	virtual PlayerID GetInternalID( void ) const;
	virtual const char* PlayerIDToDottedIP( const PlayerID playerId ) const;
	virtual void PushBackPacket( Packet *packet, bool pushAtHead );
	virtual void SetRouterInterface( void *routerInterface );
	virtual void RemoveRouterInterface( void *routerInterface );
	virtual void SetTimeoutTime( RakNetTime timeMS );
	virtual bool SetMTUSize( int size );
	virtual int GetMTUSize( void ) const;	
	virtual void AllowConnectionResponseIPMigration( bool allow );
	virtual void AdvertiseSystem( const char *host, unsigned short remotePort, const char *data, int dataLength );
	virtual RakNetStatisticsStruct * const GetStatistics( void );
	virtual void ApplyNetworkSimulator( double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance);
	virtual bool IsNetworkSimulatorActive( void );
	virtual PlayerIndex GetPlayerIndex( void );
};

class RakClient
{
public:
	RakClient( void *pRakClientInterface );
	bool RPC( int rpcId, BitStream *bitStream, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = RELIABLE_ORDERED, char orderingChannel = 0, bool shiftTimestamp = false );
	bool Send( BitStream *bitStream, PacketPriority priority = HIGH_PRIORITY, PacketReliability reliability = UNRELIABLE_SEQUENCED, char orderingChannel = 0 );
	void SendDeath( uint16_t killerId, uint8_t reason );
	void RequestClass( int classId );
	void SendSCMEvent( int vehicleID, int eventId, int param1, int param2 );
	void SendSpawn( void );
	void SendPickUp( int pickupId );
	RakClientInterface *GetRakClientInterface( void ) { return pRakClient; };

private:
	RakClientInterface *pRakClient;
};