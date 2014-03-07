/* 
 * PROJECT: mod_sa
 * COPYRIGHT: FYP
 * DATE: 21.02.2013
 * FILE: RakClient.cpp
*/

#include "main.h"

RakClient *g_RakClient = NULL;

RakClient::RakClient( void *pRakClientInterface )
{
	pRakClient = (RakClientInterface *)pRakClientInterface;
}

bool RakClient::RPC( int rpcId, BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool shiftTimestamp )
{
	if ( !pRakClient )
		return false;

	return pRakClient->RPC( &rpcId, bitStream, priority, reliability, orderingChannel, shiftTimestamp );
}

bool RakClient::Send( BitStream *bitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel )
{
	if ( !pRakClient )
		return false;

	return pRakClient->Send( bitStream, priority, reliability, orderingChannel );
}

// misc functions
void  RakClient::SendDeath( uint16_t killerId, uint8_t reason )
{
	BitStream bsDeath;

	bsDeath.Write( reason );
	bsDeath.Write( killerId );
	g_RakClient->RPC( RPC_Death, &bsDeath );
}

void RakClient::SendPickUp( int pickupId )
{
	BitStream bsPickup;

	bsPickup.Write( pickupId );
	
	RPC( RPC_PickedUpPickup, &bsPickup );
}

void  RakClient::RequestClass( int classId )
{
	BitStream bsClass;

	bsClass.Write( classId );
	g_RakClient->RPC( RPC_RequestClass, &bsClass );
}

void  RakClient::SendSCMEvent( int vehicleID, int eventId, int param1, int param2 )
{
	BitStream bsScmEvent;

	bsScmEvent.Write ( vehicleID );
	bsScmEvent.Write ( param1 );
	bsScmEvent.Write ( param2 );
	bsScmEvent.Write ( eventId );

	RPC( RPC_ScmEvent, &bsScmEvent );
}
void RakClient::SendSpawn( void )
{
	BitStream bsSpawn;

	g_RakClient->RPC( RPC_RequestSpawn, &bsSpawn );
	g_RakClient->RPC( RPC_Spawn, &bsSpawn );
}