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
#include "main.h"

// externals
unsigned long	ulFullScreenRefreshRate;
extern D3DC9	orig_Direct3DCreate9 = NULL;;

// externals
#pragma data_seg( ".d3d9_shared" )
proxyIDirect3DDevice9	*pDirect3DDevice9 = NULL;
HRESULT_VOID			orig_Direct3DShaderValidatorCreate9 = NULL;
IDirect3DDevice9		*origIDirect3DDevice9;
IDirect3DDevice9		*pRwD3DDevice = (IDirect3DDevice9 *) * (DWORD *)__RwD3DDevice;
IDirect3DTexture9		*pSpriteTexture;
D3DPRESENT_PARAMETERS	pPresentParam;
D3DMATRIX				m_mViewMatrix, m_mProjMatrix, m_mWorldMatrix;
CDirect3DData			*pD3DData =	new CDirect3DData();
#pragma data_seg()
bool					bD3DRenderInit;
bool					bD3DWindowModeSet;
bool					g_isRequestingWindowModeToggle;
bool					g_isRequesting_RwD3D9ChangeVideoMode;

IDirect3DPixelShader9	*chams_green;
IDirect3DPixelShader9	*chams_blue;
IDirect3DPixelShader9	*chams_red;

D3DXVECTOR3				speedoPos;
D3DXVECTOR2				needlePos;

IDirect3DTexture9		*tSpeedoPNG;
ID3DXSprite				*sSpeedoPNG;
IDirect3DTexture9		*tNeedlePNG;
ID3DXSprite				*sNeedlePNG;

// create a render object
CD3DRender				*render = new CD3DRender( 128 );

// create font objects

// also HUD somehow, the HUD comment below isn't totally right
CD3DFont				*pD3DFont = new CD3DFont( "Tahoma", 10, FCR_BORDER );

//pd3dFont_sampStuff = player info list, player score list, player ESP
CD3DFont				*pD3DFont_sampStuff = new CD3DFont( "Tahoma", 10, FCR_BORDER );

//pD3DFontFixed = cheat_state_msg, HUD
CD3DFont				*pD3DFontFixed = new CD3DFont( "Small Fonts", 8, FCR_BORDER );

//pD3DFontFixedSmall = health under bars (cars, players), vehicle ESP
CD3DFont				*pD3DFontFixedSmall = new CD3DFont( "Small Fonts", 8, FCR_BORDER );

//pD3DFontChat = chat, kill list
//CD3DFont				*pD3DFontChat = new CD3DFont( "Tahoma", 10, FCR_NONE );
CD3DFont				*pD3DFontChat = new CD3DFont( "Tahoma", 11, FCR_BOLD | FCR_BORDER );

//pD3DFontDebugWnd = debug window
CD3DFont				*pD3DFontDebugWnd = new CD3DFont("Lucida Console", 8, FCR_BORDER );

struct gui				*hud_bar = &set.guiset[0];
struct gui				*menu_titlebar_background = &set.guiset[2];
struct gui				*menu_background = &set.guiset[3];
struct gui				*menu_selected_item_bar = &set.guiset[4];
struct gui				*menu_selected_item_text = &set.guiset[5];

struct gui				*gta_hp_bar = &set.guiset[6];
struct gui				*gta_money_hud = &set.guiset[7];

extern int				iClickWarpEnabled;

///////////////////////////////////////////////////////////////////////////////
// Common D3D functions.
///////////////////////////////////////////////////////////////////////////////

// Function taken from the MTA:SA source code (MTA10/core/CGraphics.cpp)
void CalcScreenCoors ( D3DXVECTOR3 *vecWorld, D3DXVECTOR3 *vecScreen )
{
	/** C++-ifyed function 0x71DA00, formerly called by CHudSA::CalcScreenCoors **/
	// Get the static view matrix as D3DXMATRIX
	D3DXMATRIX	m ( (float *)(0xB6FA2C) );

	// Get the static virtual screen (x,y)-sizes
	DWORD		*dwLenX = ( DWORD * ) ( 0xC17044 );
	DWORD		*dwLenY = ( DWORD * ) ( 0xC17048 );

	//DWORD *dwLenZ = (DWORD*)(0xC1704C);
	//double aspectRatio = (*dwLenX) / (*dwLenY);
	// Do a transformation
	vecScreen->x = ( vecWorld->z * m._31 ) + ( vecWorld->y * m._21 ) + ( vecWorld->x * m._11 ) + m._41;
	vecScreen->y = ( vecWorld->z * m._32 ) + ( vecWorld->y * m._22 ) + ( vecWorld->x * m._12 ) + m._42;
	vecScreen->z = ( vecWorld->z * m._33 ) + ( vecWorld->y * m._23 ) + ( vecWorld->x * m._13 ) + m._43;

	// Get the correct screen coordinates
	double	fRecip = (double)1.0 / vecScreen->z;	//(vecScreen->z - (*dwLenZ));
	vecScreen->x *= (float)( fRecip * (*dwLenX) );
	vecScreen->y *= (float)( fRecip * (*dwLenY) );
}

void CalcWorldCoors ( D3DXVECTOR3 *vecScreen, D3DXVECTOR3 *vecWorld )
{
	// Get the static view matrix as D3DXMATRIX
	D3DXMATRIX	m ( (float *)(0xB6FA2C) );

	// Invert the view matrix
	D3DXMATRIX minv;
	memset ( &minv, 0, sizeof ( D3DXMATRIX ) );
	m._44 = 1.0f;
	D3DXMatrixInverse ( &minv, NULL, &m );

	DWORD		*dwLenX = ( DWORD * ) ( 0xC17044 );
	DWORD		*dwLenY = ( DWORD * ) ( 0xC17048 );

	// Reverse screen coordinates
	double fRecip = (double)1.0 / vecScreen->z;
	vecScreen->x /= (float)(fRecip * (*dwLenX) );
	vecScreen->y /= (float)(fRecip * (*dwLenY) );

	// Do an (inverse) transformation
	vecWorld->x = ( vecScreen->z * minv._31 ) + ( vecScreen->y * minv._21 ) + ( vecScreen->x * minv._11 ) + minv._41;
	vecWorld->y = ( vecScreen->z * minv._32 ) + ( vecScreen->y * minv._22 ) + ( vecScreen->x * minv._12 ) + minv._42;
	vecWorld->z = ( vecScreen->z * minv._33 ) + ( vecScreen->y * minv._23 ) + ( vecScreen->x * minv._13 ) + minv._43;
}

static WCHAR *ToWChar ( char *str )
{
	static WCHAR	buffer[1024];
	_wcsset( buffer, 0 );
	MultiByteToWideChar( CP_ACP, 0, str, strlen(str), buffer, 1024 );
	return buffer;
}

// by s0beit, GHOSTER, Azorbix
HRESULT GenerateShader ( IDirect3DDevice9 *Device, IDirect3DPixelShader9 **pShader, float alpha, float red, float green,
						 float blue )
{
	traceLastFunc( "GenerateShader()" );

	char		szShader[256];
	ID3DXBuffer *pShaderBuffer = NULL;
	sprintf_s( szShader, sizeof(szShader), "ps.1.1\ndef c0, %f, %f, %f, %f\nmov r0,c0", red, green, blue, alpha );
	if ( FAILED(D3DXAssembleShader(szShader, sizeof(szShader), NULL, NULL, 0, &pShaderBuffer, NULL)) )
	{
		// Log( "Shader fail." ); - yeah it does sometimes
		return E_FAIL;
	}

	if ( FAILED(Device->CreatePixelShader((const DWORD *)pShaderBuffer->GetBufferPointer(), pShader)) )
	{
		return E_FAIL;
	}

	return S_OK;
}

void LoadSpriteTexture ( void )
{
	char			filename[MAX_PATH];
	D3DLOCKED_RECT	d3dlr;
	FILE			*fd = NULL;
	int				x, y;
	uint8_t			*surface;

	SAFE_RELEASE( pSpriteTexture );
	pSpriteTexture = NULL;

	/* XXX use a different texture format */
	if ( FAILED(origIDirect3DDevice9->CreateTexture(256, 256, 1, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pSpriteTexture,
				 NULL)) )
	{
		Log( "Failed to create sprite texture!" );
		goto out;
	}

	snprintf( filename, sizeof(filename), "%s\\" M0D_FOLDER "%s", g_szWorkingDirectory, RAW_TEX_FILE );
	if ( (fd = fopen(filename, "rb")) == NULL )
	{
		Log( "Failed to open %s!", filename );
		goto out;
	}

	if ( FAILED(pSpriteTexture->LockRect(0, &d3dlr, 0, 0)) )
	{
		Log( "Failed to lock texture!" );
		goto out;
	}

	surface = (uint8_t *)d3dlr.pBits;

	for ( y = 0; y < 120; y++ )
	{
		uint8_t data[240];
		fread( data, 240, 1, fd );

		for ( x = 0; x < 240; x++ )
		{
			uint8_t alpha = ( data[x] & 7 ) << 5;
			uint8_t value = data[x] &~7;

			surface[x * 4 + 0] = value;
			surface[x * 4 + 1] = value;
			surface[x * 4 + 2] = value;
			surface[x * 4 + 3] = alpha;
		}

		surface += d3dlr.Pitch;
	}

	pSpriteTexture->UnlockRect( 0 );

	fclose( fd );

	//Log("Sprite texture loaded.");
	return;

out: ;
	SAFE_RELEASE( pSpriteTexture ) if ( fd != NULL )
		fclose( fd );
	return;
}

static void mmm_yummy_poop ( const void *info, int *enabled, int *prev_enabled, int *render, const char *teh_name )
{
	if ( info == NULL )
	{
		*prev_enabled = -1;
		*render = 0;
	}
	else
	{
		if ( *prev_enabled == -1 )
		{
			*prev_enabled = *enabled;
			*render = !*enabled;
		}

		if ( !*prev_enabled && *enabled && *render )
		{
			*enabled = 0;
			*prev_enabled = 0;
			*render = 0;
			cheat_state_text( "Disabled %s", teh_name );
		}
		else if ( *prev_enabled && !*enabled )
		{
			cheat_state_text( "Switched to s0beit %s", teh_name );
			*render = 1;
		}
		else if ( !*prev_enabled && *enabled )
		{
			cheat_state_text( "Switched to SA:MP %s", teh_name );
			*render = 0;
		}

		*prev_enabled = *enabled;
	}
}

void RenderDebug ( void )
{
	static const int	ROW_HEIGHT = (int)ceilf( pD3DFontDebugWnd->DrawHeight() );
	static const int	CHAR_WIDTH = (int)ceilf( pD3DFontDebugWnd->DrawLength("W") );
	static const int	ROWS = DEBUG_DATA_SIZE / 16;
	static const int	data_size[4] = { 1, 2, 4, 4 };
	struct debug_info	*debug = &cheat_state->debug;
	static char			str_data[17], str[256];
	int					x, y, row, col, i;
	int					offset, offset16;
	uint8_t				*ptr, *data;

	ptr = debug->ptr[debug->hist_pos] - DEBUG_DATA_SIZE;
	offset = debug->offset[debug->hist_pos];
	offset16 = (unsigned int)offset % 16;
	ptr += offset - offset16 + DEBUG_DATA_SIZE / 2;

	memset( debug->data, 0, DEBUG_DATA_SIZE );
	memcpy_safe( debug->data, ptr, DEBUG_DATA_SIZE );

	if ( !debug->data_prev_clear )
	{
		for ( i = 0; i < DEBUG_DATA_SIZE; i++ )
		{
			if ( debug->data[i] != debug->data_prev[i] )
				debug->modify_time[i] = time_get();
		}
	}
	else
	{
		memset( debug->modify_time, 0, sizeof(debug->modify_time) );
	}

	debug->data_prev_clear = 0;

	x = 324;
	y = 4;

	/* blue box */
	render->D3DBoxi( x - 2, y - 2, CHAR_WIDTH * 75 + 4, ROW_HEIGHT * 27 + 4, D3DCOLOR_ARGB(180, 0, 0, 150), NULL );

	/* render selection */
	for ( row = offset16; row < offset16 + data_size[debug->data_type]; row++ )
	{
		col = ( ROWS / 2 ) + row / 16;
		render->D3DBoxi( x + CHAR_WIDTH * (10 + (row % 16) * 3), y + ROW_HEIGHT * col, CHAR_WIDTH * 3, ROW_HEIGHT,
						 D3DCOLOR_ARGB(127, 0, 255, 0), NULL );
		render->D3DBoxi( x + CHAR_WIDTH * (59 + (row % 16)), y + ROW_HEIGHT * col, CHAR_WIDTH, ROW_HEIGHT,
						 D3DCOLOR_ARGB(127, 0, 255, 0), NULL );
	}

	/* render hex view */
	for ( row = 0; row < ROWS; row++ )
	{
		int red_text = 0;
		int len = 10;
		int xpos = x;

		snprintf( str, sizeof(str), "%p  ", ptr + row * 16 );

		for ( col = 0; col < 16; col++ )
		{
			uint32_t	mod_time = debug->modify_time[row * 16 + col];
			uint8_t		ch = debug->data[row * 16 + col];
			int			color_switch = 0;

			if ( mod_time != 0 && time_get() < mod_time + MSEC_TO_TIME(2000) )
				color_switch = !red_text;			/* switch color, unless red_text == 1 */
			else if ( red_text )
				color_switch = 1;

			if ( color_switch )
			{
				pD3DFontDebugWnd->PrintShadow( (float)xpos, (float)y,
											red_text ? D3DCOLOR_XRGB(255, 31, 31) : D3DCOLOR_XRGB(191, 191, 191), str );

				xpos += CHAR_WIDTH * len;
				str[0] = 0;
				len = 0;

				red_text ^= 1;
			}

			snprintf( str + len, sizeof(str) - len, "%02x ", debug->data[row * 16 + col] );
			len += 3;

			str_data[col] = (char)( (ch < 32) ? '.' : ch );
		}

		pD3DFontDebugWnd->PrintShadow( (float)xpos, (float)y, red_text ? D3DCOLOR_XRGB(255, 31, 31) : D3DCOLOR_XRGB(191, 191, 191),
									str );

		pD3DFontDebugWnd->PrintShadow( (float)x + CHAR_WIDTH * 59, (float)y, D3DCOLOR_XRGB(191, 191, 191), str_data );

		y += ROW_HEIGHT;
	}

	/* everything else \o/ */
	data = &debug->data[DEBUG_DATA_SIZE / 2 + offset16];
	memcpy( debug->cursor_data, data, sizeof(debug->cursor_data) );

	/* data type info */
	snprintf( str, sizeof(str), "=>%c%02x(%-3d),%c%04x(%-5d),%c%08x(%d),%c%.4f, %s ptr", (debug->data_type == 0) ? '*' : ' ',
			  *(uint8_t *)data, *(uint8_t *)data, (debug->data_type == 1) ? '*' : ' ', *(uint16_t *)data,
			  *(uint16_t *)data, (debug->data_type == 2) ? '*' : ' ', *(uint32_t *)data, *(uint32_t *)data,
			  (debug->data_type == 3) ? '*' : ' ', *(float *)data, isBadPtr_readAny(*(void **)data, 1) ? "Bad" : "OK" );
	pD3DFontDebugWnd->PrintShadow( (float)x, (float)y, D3DCOLOR_XRGB(191, 191, 191), str );
	y += ROW_HEIGHT;

	/* ptr info */
	snprintf( str, sizeof(str), "Viewing: %s", debug_classify_pointer((void *)(debug->ptr[debug->hist_pos] + offset)) );
	pD3DFontDebugWnd->PrintShadow( (float)x, (float)y, D3DCOLOR_XRGB(191, 191, 191), str );
	y += ROW_HEIGHT;

	snprintf( str, sizeof(str), "Pointer: %s", debug_classify_pointer(*(void **)data) );
	pD3DFontDebugWnd->PrintShadow( (float)x, (float)y, D3DCOLOR_XRGB(191, 191, 191), str );
	y += ROW_HEIGHT;

	/* ptr stack info */
	snprintf( debug->ptr_hist_str, sizeof(debug->ptr_hist_str), "Ptr stack (%d): %s", debug->hist_pos,
			  debug->hist_pos > 2 ? "... " : "" );
	for ( i = debug->hist_pos - 2; i <= debug->hist_pos; i++ )
	{
		int len = (int)strlen( debug->ptr_hist_str );

		if ( i < 0 )
			continue;
		snprintf( debug->ptr_hist_str + len, sizeof(debug->ptr_hist_str) - len, "%p+0x%x -> ", debug->ptr[i],
				  debug->offset[i] );
	}

	debug->ptr_hist_str[strlen( debug->ptr_hist_str ) - 4] = 0;
	pD3DFontDebugWnd->PrintShadow( (float)x, (float)y, D3DCOLOR_XRGB(191, 191, 191), debug->ptr_hist_str );
	y += ROW_HEIGHT * 2;

	/* print help */
	pD3DFontDebugWnd->PrintShadow( (float)x, (float)y, D3DCOLOR_XRGB(191, 191, 191),
								"np4/6,8/2,9/3 = move   np7 = return   np1 = go to pointer" );
	y += ROW_HEIGHT;

	pD3DFontDebugWnd->PrintShadow( (float)x, (float)y, D3DCOLOR_XRGB(191, 191, 191),
								"np/ = data type   np-/+ = inc/dec   np* = ptr stack to clipboard" );

	memcpy( debug->data_prev, debug->data, DEBUG_DATA_SIZE );
}

void RenderMenu ( void )
{
	static const int	ROW_HEIGHT = (int)ceilf( pD3DFont->DrawHeight() );
	static const int	MENU_HEIGHT = (int)ceilf( pD3DFont->DrawHeight() * (float)MENU_ROWS ) + 2;

	char				title[256] = NAME;
	struct menu_item	*item;
	struct menu			*menu;
	int					left, top;
	float				x, y;
	int					pos, top_pos, i;
	float				tdlen;

	if ( menu_active == NULL )
		return;

	/* find root menu */
	for ( menu = menu_active; menu->parent != NULL; menu = menu->parent );

	while ( menu != NULL )
	{
		if ( menu->pos < 0 || menu->pos >= menu->count )
			break;
		item = &menu->item[menu->pos];
		if ( item->submenu == NULL || menu == menu_active )
			break;
		snprintf( title + strlen(title), sizeof(title) - strlen(title), " > %s", item->name );
		menu = item->submenu;
	}

	/* draw titlebar */
	left = pPresentParam.BackBufferWidth / 2 - MENU_WIDTH / 2;
	top = pPresentParam.BackBufferHeight - MENU_HEIGHT - ROW_HEIGHT - 2 - 20 - 2;

	tdlen = pD3DFont->DrawLength(title);
	tdlen -= MENU_WIDTH;
	if (tdlen < 0.0f)
		tdlen = 0.0f;
	int cp = pD3DFont->GetCharPos(title, tdlen); // child p... char pos
	if (cp > 0) ++cp;
	render->D3DBoxBorderi( left, top, MENU_WIDTH, ROW_HEIGHT + 2,
						   D3DCOLOR_ARGB(223, 91, 91, 91), D3DCOLOR_ARGB(menu_titlebar_background->alpha,
						   menu_titlebar_background->red, menu_titlebar_background->green,
						   menu_titlebar_background->blue) );
	pD3DFont->PrintShadow( (float)(left + 1), (float)(top + 1), D3DCOLOR_XRGB(223, 223, 223), &title[cp] );

	/* draw window */
	left = pPresentParam.BackBufferWidth / 2 - MENU_WIDTH / 2;
	top = pPresentParam.BackBufferHeight - MENU_HEIGHT - 1 - 20;
	render->D3DBoxBorderi( left, top, MENU_WIDTH, MENU_HEIGHT, D3DCOLOR_ARGB(223, 63, 63, 63),
						   D3DCOLOR_ARGB(menu_background->alpha, menu_background->red, menu_background->green, menu_background->blue) );

	/* calculate positions */
	pos = menu_active->pos;
	top_pos = menu_active->top_pos;

	if ( pos - MENU_ROWS >= top_pos )
		top_pos = pos - MENU_ROWS + 1;
	if ( pos < top_pos )
		top_pos = pos;

	if ( top_pos < 0 )
		top_pos = 0;
	else if ( top_pos >= menu_active->count )
		top_pos = menu_active->count - 1;

	menu_active->top_pos = top_pos;

	/* draw menu items */
	y = (float)top;
	x = (float)( left + 2 );

	for ( i = top_pos; i < top_pos + MENU_ROWS; i++, y += pD3DFont->DrawHeight() )
	{
		int enabled;

		if ( i < 0 || i >= menu_active->count )
			continue;

		item = &menu_active->item[i];
		enabled = menu_active->callback( MENU_OP_ENABLED, item );

		if ( i == pos )
		{
			render->D3DBoxi( left + 1, (int)floorf(y) + 1, MENU_WIDTH - 1, ROW_HEIGHT + 1, D3DCOLOR_ARGB(
								 menu_selected_item_bar->alpha, menu_selected_item_bar->red,
							 menu_selected_item_bar->green, menu_selected_item_bar->blue), NULL );
		}

		if ( i == menu_mouseover )
		{
			render->D3DBoxi( left + 1, (int)floorf(y) + 1, MENU_WIDTH - 1, ROW_HEIGHT + 1, D3DCOLOR_ARGB(
								 menu_selected_item_bar->alpha / 2, menu_selected_item_bar->red,
							 menu_selected_item_bar->green, menu_selected_item_bar->blue), NULL );
		}

		if ( item->name[0] == '\t' )
		{
			pD3DFont->PrintShadow( x, y, item->color, item->name + 1 );
			render->D3DBoxi( left + 2, (int)floorf(y) + ROW_HEIGHT - 1, (int)ceilf(pD3DFont->DrawLength(item->name + 1)),
							 1, D3DCOLOR_ARGB(191, 127, 127, 127), NULL );
		}
		else
		{
			/* XXX ... */
			pD3DFont->PrintShadow( x, y, enabled ? D3DCOLOR_XRGB(menu_selected_item_text->red,
								   menu_selected_item_text->green, menu_selected_item_text->blue) : item->color,
								   item->name );
		}

		if ( item->submenu != NULL )
		{
			pD3DFont->PrintShadow( x + (float)MENU_WIDTH - pD3DFont->DrawLength(">") - 4, y,
								   D3DCOLOR_ARGB(191, 127, 127, 127), ">" );
		}
	}
}

void RenderMapDot ( const float self_pos[3], const float pos[16], DWORD color, const char *name )
{
	static int	init;
	float		vect[3], rvect[2];
	float		a, x, y;

	vect3_vect3_sub( pos, self_pos, vect );

	if ( vect3_length(vect) > 1000.0f )
		return;

	color = ( color & 0x00FFFFFF ) | 0xDF000000;

	a = -atan2f( cam_matrix[4 * 0 + 0], cam_matrix[4 * 0 + 1] ) - M_PI / 2.0f;

	rvect[0] = vect[0] * cosf( a ) - -vect[1] * sinf( a );
	rvect[1] = vect[0] * sinf( a ) + -vect[1] * cosf( a );

	rvect[1] /= pPresentParam.BackBufferWidth / pPresentParam.BackBufferHeight;

	x = (float)pPresentParam.BackBufferWidth / 2 + roundf( rvect[0] );
	y = (float)pPresentParam.BackBufferHeight / 2 + roundf( rvect[1] );
	if (x < 0.0f || x > pPresentParam.BackBufferWidth || y < 0.0f || y > pPresentParam.BackBufferHeight)
		return;
	if (set.map_draw_lines && vect3_length(vect) > 5.0f)
		render->D3DLine(x, y, pPresentParam.BackBufferWidth / 2, pPresentParam.BackBufferHeight / 2, color);

	/* the "^ v o" icons are 9x9 large, and located at 168x98 in the texture */
	if ( pSpriteTexture != NULL )
	{
		float	u, v, ts;

		if ( name != NULL )
			pD3DFontFixed->PrintShadow( floor(x - pD3DFontFixed->DrawLength(name) / 2.0f), floor(y - 14.0f), color, name );

		u = 168.0f;
		v = 98.0f;

		if ( vect[2] < -4.0f )
			u += 9.0f;
		else if ( vect[2] <= 4.0f )
			u += 18.0f;

		u /= 256.0f;
		v /= 256.0f;
		ts = 9.0f / 256.0f;

		render->D3DBindTexture( pSpriteTexture );

		render->D3DTexQuad( x - 4.5f, y - 4.5f, x + 4.5f, y + 4.5f, u, v, u + ts, v + ts );

		render->D3DBindTexture( NULL );
	}
	else
	{
		if ( name != NULL )
			pD3DFont->PrintShadow( floor(x - pD3DFontFixed->DrawLength(name) / 2.0f), floor(y - 14.0f), color, name );

		if ( vect[2] < -4.0f )
		{
			pD3DFont->PrintShadow( floor(x - 4.5f), floor(y - 4.5f), color, "v" );
			return;
		}
		else if ( vect[2] <= 4.0f )
		{
			pD3DFont->PrintShadow( floor(x - 4.5f), floor(y - 4.5f), color, "o" );
			return;
		}
		else if ( vect[2] > 4.0f )
		{
			pD3DFont->PrintShadow( floor(x - 4.5f), floor(y - 4.5f), color, "^" );
			return;
		}
	}
}

void RenderMap ( void )
{
	traceLastFunc( "renderMap()" );

	// don't run in the menu
	if ( gta_menu_active() )
		return;

	if ( g_SAMP != NULL )
	{
		// showing scorelist?
		if ( (GetAsyncKeyState(VK_TAB) < 0 && set.d3dtext_score)
		 ||	 g_Scoreboard->iIsEnabled ) 
			return;

		if ( GetAsyncKeyState(VK_F1) < 0 )
			return;
		if ( GetAsyncKeyState(VK_F5) < 0 )
			return;
		if ( GetAsyncKeyState(VK_F10) < 0 )
			return;
	}

	struct actor_info	*self = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
	if ( self == NULL )
		return;

	const struct vehicle_entry	*vehicle;
	float						pos[3];
	char						buf[256];
	int							i;

	if ( pool_actor != NULL )
	{
		if ( g_SAMP != NULL )
		{
			for ( i = 0; i < SAMP_MAX_PLAYERS; i++ )
			{
				if ( !getPlayerPos(i, pos) )
					continue;
				if ( g_Players->pRemotePlayer[i] == NULL )
					continue;
				_snprintf_s( buf, sizeof(buf)-1, "%s(%d)", getPlayerName(i), i );
				RenderMapDot( &self->base.matrix[4 * 3], pos, samp_color_get(i), buf );
			}
		}
		else
		{
			CPoolsSA::pedPool_t::mapType::iterator it = ((CPoolsSA *)pGameInterface->GetPools())->m_pedPool.map.begin();
			for (; it.pos < it.end; it++)
			{
				CPedSA *ped = it.pos->second;
				if (ped == nullptr)
					continue;
				if (ped == pPedSelf)
					continue;
				_snprintf_s(buf, sizeof(buf)-1, "%d", ped->GetArrayID());
				RenderMapDot(&self->base.matrix[4 * 3], &ped->GetPosition()->fX, D3DCOLOR_XRGB(255, 255, 255), buf);
			}
		}
	}

	if ( cheat_state->_generic.map_vehicles )
	{
		if ( g_SAMP != NULL )
		{
			if ( g_Vehicles != NULL )
			{
				for ( i = 0; i < SAMP_MAX_VEHICLES; i++ )
				{
					if ( g_Vehicles->iIsListed[i] != 1 )
						continue;
					if ( g_Vehicles->pSAMP_Vehicle[i] == NULL )
						continue;
					if ( g_Vehicles->pSAMP_Vehicle[i]->pGTA_Vehicle != NULL )
					{
						vehicle = gta_vehicle_get_by_id( g_Vehicles->pSAMP_Vehicle[i]->pGTA_Vehicle->base.model_alt_id );
						if ( g_Players->pLocalPlayer->sCurrentVehicleID == i )
							continue;

						RwColor color = getVehicleColorRGB(vehicle_getColor0(g_Vehicles->pSAMP_Vehicle[i]->pGTA_Vehicle));
						_snprintf_s( buf, sizeof(buf)-1, "%s(%d)", vehicle->name, i );
						RenderMapDot( &self->base.matrix[4 * 3],
									  &g_Vehicles->pSAMP_Vehicle[i]->pGTA_Vehicle->base.matrix[4 * 3],
									  D3DCOLOR_XRGB(color.r, color.g, color.b), buf );
					}
				}
			}
		}
		else
		{
			for ( i = 0; i < pool_vehicle->size; i++ )
			{
				struct vehicle_info *vehs = vehicle_info_get( i, VEHICLE_ALIVE );
				if ( vehs == NULL )
					continue;
				RwColor color = getVehicleColorRGB(vehicle_getColor0(vehs));
				vehicle = gta_vehicle_get_by_id( vehs->base.model_alt_id );
				_snprintf_s( buf, sizeof(buf)-1, "%s (%d)", vehicle->name, i );
				RenderMapDot( &self->base.matrix[4 * 3], &vehs->base.matrix[4 * 3], D3DCOLOR_XRGB(color.r, color.g, color.b), buf );
			}
		}
	}

	if ( cheat_state->_generic.teletext )
	{
		for ( i = 0; i < TELEPORT_MAX; i++ )
		{
			vect3_copy( &cheat_state->teleport[i].matrix[4 * 3], pos );
			if ( vect3_near_zero(pos) )
				continue;
			_snprintf_s( buf, sizeof(buf)-1, "Teleport %d (%0.1f)", i, vect3_dist(&self->base.matrix[4 * 3], pos) );
			RenderMapDot( &self->base.matrix[4 * 3], pos, D3DCOLOR_XRGB(0, 200, 200), buf );
		}
	}
	
	// self
	RenderMapDot( &self->base.matrix[4 * 3], &self->base.matrix[4 * 3], D3DCOLOR_XRGB(255, 255, 255), NULL );
}

void RenderPedHPBar ( void )
{
	if ( !set.left_bottom_bars_enable )
		return;

	struct actor_info	*info = actor_info_get( ACTOR_SELF, 0 );
	char				text[32];
	int					bottom, fontHeight;

	if ( info == NULL )
		return;

	bottom = pPresentParam.BackBufferHeight;
	fontHeight = (int)pD3DFontFixed->DrawHeight() - 1;

	render->D3DBoxi( 0, bottom - fontHeight, 101, fontHeight, D3DCOLOR_ARGB(127, 0, 0, 0), NULL );
	render->D3DBoxi( 0, bottom - fontHeight + 1, (int)info->hitpoints, fontHeight - 2, D3DCOLOR_ARGB(127, 191, 0, 0), 100 );
	_snprintf_s( text, sizeof(text)-1, "Health: %d", (int)info->hitpoints );
	pD3DFontFixed->PrintShadow( (float)(2), (float)(bottom - fontHeight), D3DCOLOR_XRGB(255, 255, 255), text );

	render->D3DBoxi( 0, bottom - 20, 101, 10, D3DCOLOR_ARGB(127, 0, 0, 0), NULL );
	if ( info->armor == NULL )
	{
		pD3DFontFixed->PrintShadow( (float)(2), (float)(bottom - (fontHeight*2)), D3DCOLOR_XRGB(255, 255, 255), "No armor" );
	}
	else
	{
		render->D3DBoxi( 0, bottom - (fontHeight*2) + 1, (int)info->armor, fontHeight - 2, D3DCOLOR_ARGB(127, 255, 255, 255), 100 );
		_snprintf_s( text, sizeof(text)-1, "Armor: %d", (int)info->armor );
		pD3DFontFixed->PrintShadow( (float)(2), (float)(bottom - (fontHeight*2)), D3DCOLOR_XRGB(255, 255, 255), text );
	}
}

void RenderVehicleHPBar ( void )
{
	if ( !set.left_bottom_bars_enable )
		return;

	struct actor_info	*pinfo = actor_info_get( ACTOR_SELF, 0 );
	struct vehicle_info *vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
	char				text[32];
	int					hp, bottom, barHeight, fontHeight;
	float				speed;

	if ( vinfo == NULL )
		return;
	if ( pinfo == NULL )
		return;

	bottom = pPresentParam.BackBufferHeight;
	barHeight = (int)pD3DFont->DrawHeight() - 5;
	fontHeight = (int)pD3DFontFixed->DrawHeight() - 2;

	if ( vinfo->hitpoints > 1000.0f )
		hp = 100;
	else
		hp = (int)( vinfo->hitpoints / 10.0f );

	render->D3DBoxi( 0, bottom - fontHeight, 101, fontHeight + 2, D3DCOLOR_ARGB(127, 0, 0, 0), NULL );
	render->D3DBoxi( 0, bottom - fontHeight + 1, hp, fontHeight, D3DCOLOR_ARGB(127, 191, 0, 0), 1000 );
	_snprintf_s( text, sizeof(text)-1, "VHealth: %d", hp );
	pD3DFontFixed->PrintShadow( (float)(2), (float)(bottom - fontHeight - 1), D3DCOLOR_XRGB(255, 255, 255), text );

	if ( !set.speedometer_old_enable )
	{
		render->D3DBoxi( 0, bottom - (fontHeight*2), 101, fontHeight + 2, D3DCOLOR_ARGB(127, 0, 0, 0), NULL );
		render->D3DBoxi( 0, bottom - (fontHeight*2) + 1, (int)pinfo->hitpoints, fontHeight, D3DCOLOR_ARGB(127, 191, 0, 0), 100 );
		if ( pinfo->armor != NULL )
			render->D3DBoxi( 0, bottom - (fontHeight*2), (int)pinfo->armor, 8, D3DCOLOR_ARGB(127, 255, 255, 255), 100 );
		_snprintf_s( text, sizeof(text)-1, "PHealth: %d", (int)pinfo->hitpoints );
		pD3DFontFixed->PrintShadow( (float)(2), (float)(bottom - (fontHeight*2)  - 1), D3DCOLOR_XRGB(255, 255, 255), text );
	}
	else if ( !cheat_state->vehicle.air_brake )
	{
		float	spood = vect3_length( vinfo->speed );
		render->D3DBoxi( 0, bottom - barHeight - fontHeight, 101, 10, D3DCOLOR_ARGB(127, 0, 0, 0), NULL );
		render->D3DBoxi( 0, bottom - barHeight - fontHeight + 1, (int)(spood * 64), 8, D3DCOLOR_ARGB(127, 191, 191, 0), 100 );
		_snprintf_s( text, sizeof(text)-1, "%0.2f km/h", (float)(spood * 170) );
		pD3DFontFixed->PrintShadow( (float)(2), (float)(bottom - (fontHeight*2) - 1), D3DCOLOR_XRGB(255, 255, 255), text );
	}

	// acceleration/distance speed
	static float	speed_last;
	static float	speed_lastVect[3];
	static float	speed_nowVect[3];
	static float	speed_dist;
	static float	speed_secondsLastCheck = 0.0f;
	static float	speed_now;
	static float	speed_acceleration;

	// update our data about position, speed, acceleration
	if ( (TIME_TO_DOUBLE(time_get()) - speed_secondsLastCheck) > 0.10f )
	{
		////////////////////
		// distance speed //
		////////////////////
		vect3_copy( speed_nowVect, speed_lastVect );
		vect3_copy( &vinfo->base.matrix[4 * 3], speed_nowVect );
		speed_dist = vect3_dist( speed_lastVect, speed_nowVect ) / ( TIME_TO_DOUBLE(time_get()) - (float)speed_secondsLastCheck );

		//////////
		// m/ss //
		//////////
		speed_last = speed_now;
		speed_now = ( vect3_length(vinfo->speed) * 170.0f ) / 3.6f;
		speed_acceleration = ( speed_now - speed_last ) / ( TIME_TO_DOUBLE(time_get()) - speed_secondsLastCheck );
		speed_secondsLastCheck = TIME_TO_DOUBLE( time_get() );
	}

	// distance speed while air braking
	if ( cheat_state->vehicle.air_brake )
	{
		// speedometer - analog (needle)
		speed = speed_dist * ( 3.43f / 170.0f );

		// speedometer - digital (numbers above health)
		if ( set.speedometer_old_enable )
		{
			render->D3DBoxi( 0, bottom - barHeight - fontHeight, 101, 10, D3DCOLOR_ARGB(127, 0, 0, 0), NULL );
			render->D3DBoxi( 0, bottom - barHeight - fontHeight + 1, (int)(speed_dist * 1.3f), 8, D3DCOLOR_ARGB(127, 191, 191, 0), 100 );
			_snprintf_s( text, sizeof(text)-1, "%0.2f km/h", (float)(speed_dist * 3.43f) );
			pD3DFontFixed->PrintShadow( (float)(2), (float)(bottom - (fontHeight*2) - 1), D3DCOLOR_XRGB(255, 255, 255), text );
		}
	}
	else
	{
		// air brake deactivated - set the speedometer speed to real speed
		speed = vect3_length( vinfo->speed );
	}

	if ( set.speedometer_enable )
	{
		if ( speed > 260.0f )
			speed = 260.0f;

		static float	mult = set.speedometer_multiplier;

		float			rotationNeedle = 0.0f;
		D3DXMATRIX		mat;

		rotationNeedle = DEGTORAD( (90.0f / 100.0f) * ((speed * mult) * 1.55f) );
		rotationNeedle /= 2;
		if ( rotationNeedle > 3.29f )
			rotationNeedle = 3.29f;

		D3DXVECTOR2 axisSpeedo = D3DXVECTOR2( speedoPos.x, speedoPos.y );
		D3DXVECTOR2 axisNeedle = D3DXVECTOR2( (130.00f * needlePos.x), (152.00f * needlePos.y) );

		if ( !gta_menu_active() && !KEY_DOWN(VK_TAB) )
		{
			if ( (sSpeedoPNG) && (tSpeedoPNG) && (sNeedlePNG) && (tNeedlePNG) )
			{
				D3DXMatrixTransformation2D( &mat, NULL, 0.0f, &needlePos, &axisNeedle, 0.0f, &axisSpeedo );
				sSpeedoPNG->Begin( D3DXSPRITE_ALPHABLEND );
				sSpeedoPNG->SetTransform( &mat );
				sSpeedoPNG->Draw( tSpeedoPNG, NULL, NULL, NULL, 0xCCFFFFFF );
				sSpeedoPNG->End();

				D3DXMatrixTransformation2D( &mat, NULL, 0.0f, &needlePos, &axisNeedle, rotationNeedle, &axisSpeedo );
				sNeedlePNG->Begin( D3DXSPRITE_ALPHABLEND );
				sNeedlePNG->SetTransform( &mat );
				sNeedlePNG->Draw( tNeedlePNG, NULL, NULL, NULL, 0xCCFFFFFF );
				sNeedlePNG->End();
			}
		}
	}

	// acceleration meter
	render->D3DBoxi( 0, bottom - 30, 101, 10, D3DCOLOR_ARGB(127, 0, 0, 0), NULL );
	if ( speed_acceleration <= -0.01f )
		render->D3DBoxi( 0, bottom - barHeight - 19, (int)(speed_acceleration * -4.8f), 8, D3DCOLOR_ARGB(127, 191, 191, 0), 100 );
	else
		render->D3DBoxi( 0, bottom - barHeight - 19, (int)(speed_acceleration * 4.8f), 8, D3DCOLOR_ARGB(127, 191, 191, 0), 100 );
	_snprintf_s( text, sizeof(text)-1, "%0.2f m/ss", (float)(speed_acceleration) );
	pD3DFontFixed->PrintShadow( (float)(2), (float)(bottom - barHeight - 21), D3DCOLOR_XRGB(255, 255, 255), text );

}

// for renderPlayerTags()
struct playerTagInfo
{
#pragma pack( 1 )
	CVector tagPosition;
	float	tagOffsetY;
	bool	isStairStacked;
	float	stairStackedOffset;
	bool	isPastMaxDistance;
} g_playerTagInfo[SAMP_MAX_PLAYERS];

// new "Air Ride" player ESP by nuckfuts
// this is optimized to all hell, so please don't
// mess with it unless you completely understand it
void renderPlayerTags ( void )
{
	traceLastFunc( "renderPlayerTags()" );

	// don't run in the menu
	if ( gta_menu_active() )
		return;

	// Exit this function and enable samp nametags, if panic key
	if ( cheat_state->_generic.cheat_panic_enabled || !cheat_state->render_player_tags )
	{
		if ( g_dwSAMP_Addr && g_SAMP )
		{
			sampPatchDisableNameTags( 0 );
		}
		return;
	}

	// don't run during certain samp events
	if ( g_dwSAMP_Addr && g_SAMP )
	{
		if (
			// Scoreboard open?
			( GetAsyncKeyState(VK_TAB) < 0 && set.d3dtext_score )
			|| g_Scoreboard->iIsEnabled
			// F10 key down?
			|| GetAsyncKeyState(VK_F10) < 0
		)
		{
			return;
		}

		// Disable samp Nametags
		sampPatchDisableNameTags( 1 );
	}

	// don't run if the CGameSA doesn't exist
	if ( !pGameInterface )
		return;

	// don't run if we don't exist
	if (isBadPtr_GTA_pPed(pPedSelf))
		return;

	// for tracking player states as we iterate through
	bool	isPedESPCollided[SAMP_MAX_PLAYERS];
	bool	isPedESPStairStacked[SAMP_MAX_PLAYERS];
	memset( isPedESPCollided, false, sizeof(bool) * SAMP_MAX_PLAYERS );
	memset( isPedESPStairStacked, true, sizeof(bool) * SAMP_MAX_PLAYERS );

	// alignment settings
	int			ESP_tag_player_pixelOffsetY = -10;
	float		ESP_tag_player_D3DBox_pixelOffsetX = -0.5f;
	float		ESP_tag_player_D3DBox_pixelOffsetY = 1.0f;
	float		ESP_tag_player_posOffsetZ = 1.0f;
	float		ESP_tag_player_espHeight = 20.0f;
	//float		ESP_tag_player_movementSpeed = 5.0f;

	// trash values to use during iterations
	float		vh, va;
	int			iGTAID, iGTAID_Inner, selfGTAID;
	CVector		iterPosition, ourPosMinusIter, ourPosition;
	D3DXVECTOR3 poss, screenposs;
	char		buf[256];

	// get our info
	if ( pPedSelf->GetVehicle() )
	{
		// RC Vehicle Fix (Not showing names of recently streamed in players
		// while being in a RC Vehicle)
		ourPosition = *(pPedSelf->GetVehicle()->GetPosition());
	}
	else
	{
		ourPosition = pPedSelfSA->Placeable.matrix->vPos;
	}

	// get our scripting ID so we can exclude ourself
	selfGTAID = (int)pPedSelf->GetArrayID();

	// setup iterator
	CPedSA		*iterPed = NULL;
	CPoolsSA	*pPools = reinterpret_cast < CPoolsSA * > ( pGameInterface->GetPools() );
	CPoolsSA::pedPool_t::mapType::iterator iter = pPools->m_pedPool.map.begin();

	// get initial variables for peds streamed in
	while ( iter.pos < iter.end )
	{
		// map iterator pointer to our pointer
		iterPed = iter.pos->second;

		// advance to next item for next pass
		iter.pos++;
		if ( !iterPed )
			continue;

		// get player id
		iGTAID = (int)iterPed->GetArrayID();

		// ignore if it's us
		if ( iGTAID == selfGTAID )
			continue;

		// RC Vehicle fix (not showing names of players in RC vehicles)
		if ( iterPed->GetVehicle() != NULL )
		{
			if ( gta_vehicle_get_by_id(iterPed->GetVehicle()->GetModelIndex())->class_id == VEHICLE_CLASS_MINI
				&& iterPed->GetVehicle()->GetDriver() == iterPed )
			{
				iterPosition = *iterPed->GetVehicle()->GetPosition();
			}
			else
			{
				iterPosition = iterPed->GetInterface()->Placeable.matrix->vPos;
			}
		}
		else
		{
			iterPosition = iterPed->GetInterface()->Placeable.matrix->vPos;
		}

		// check if it's farther than set.player_tags_dist
		ourPosMinusIter = ourPosition - iterPosition;
		if ( ourPosMinusIter.Length() > set.player_tags_dist )
		{
			g_playerTagInfo[iGTAID].isPastMaxDistance = true;
			continue;
		}
		else
			g_playerTagInfo[iGTAID].isPastMaxDistance = false;

		// get the player position in 2D
		poss.x = iterPosition.fX;
		poss.y = iterPosition.fY;
		poss.z = iterPosition.fZ + ESP_tag_player_posOffsetZ;
		CalcScreenCoors( &poss, &screenposs );

		// check if the iter is culled or not
		if ( screenposs.z < 1.f )
		{
			g_playerTagInfo[iGTAID].tagOffsetY = 0.0f;
			g_playerTagInfo[iGTAID].isPastMaxDistance = true;
			continue;
		}

		// global, set ESP position for tagOffsetY use
		g_playerTagInfo[iGTAID].tagPosition.fX = screenposs.x;
		g_playerTagInfo[iGTAID].tagPosition.fY = screenposs.y;
		g_playerTagInfo[iGTAID].tagPosition.fZ = screenposs.z;
	}

	// reset iter position & setup iterInner
	iter = pPools->m_pedPool.map.begin();

	CPedSA	*iterInnerPed = NULL;
	CPoolsSA::pedPool_t::mapType::iterator iterInner;

	// remove staircase problem
	while ( iter.pos < iter.end )
	{
		// map iterator pointer to our pointer
		iterPed = iter.pos->second;

		// advance to next item for next pass
		iter.pos++;
		if ( !iterPed )
			continue;

		// get player id
		iGTAID = (int)iterPed->GetArrayID();

		// ignore if it's us
		if ( iGTAID == selfGTAID )
			continue;

		// filter out "ok" ESP
		if ( g_playerTagInfo[iGTAID].isPastMaxDistance
			||	!g_playerTagInfo[iGTAID].isStairStacked
				&& g_playerTagInfo[iGTAID].tagOffsetY < 40.0f
			)
			continue;

		// detect stair stacking per frame if ESP isn't already stair stacked
		if ( !g_playerTagInfo[iGTAID].isStairStacked )
		{
			// reset iterInner position
			iterInner = pPools->m_pedPool.map.begin();
			while ( iterInner.pos < iterInner.end )
			{
				// map iterator pointer to our pointer
				iterInnerPed = iterInner.pos->second;

				// advance to next item for next pass
				iterInner.pos++;
				if ( !iterInnerPed )
					continue;

				// get player id
				iGTAID_Inner = (int)iterInnerPed->GetArrayID();

				// ignore if it's us or isPastMaxDistance
				if ( g_playerTagInfo[iGTAID_Inner].isPastMaxDistance || iGTAID_Inner == iGTAID )
					continue;

				// test to see who comes out on top
				if ( abs(g_playerTagInfo[iGTAID].tagPosition.fX - g_playerTagInfo[iGTAID_Inner].tagPosition.fX) <= 100.0f
				 &&	 abs((g_playerTagInfo[iGTAID].tagPosition.fY - (g_playerTagInfo[iGTAID].tagOffsetY / 2.0f)) - (g_playerTagInfo[iGTAID_Inner].tagPosition.fY - g_playerTagInfo[iGTAID_Inner].tagOffsetY)) <= ESP_tag_player_espHeight )
				{
					isPedESPStairStacked[iGTAID] = false;
				}
			}

			// setup stair stack variables needed to un stack the ESP
			if ( isPedESPStairStacked[iGTAID] )
			{
				g_playerTagInfo[iGTAID].isStairStacked = true;
				g_playerTagInfo[iGTAID].stairStackedOffset = g_playerTagInfo[iGTAID].tagOffsetY / 2.0f;
			}
		}	// end inner while - detect stair stacking

		// lower the offsets for stair stacked ESP
		// and turn off stack status of ESP that reaches the "available" offset
		if ( g_playerTagInfo[iGTAID].isStairStacked )
		{
			g_playerTagInfo[iGTAID].tagOffsetY -= 5.0f;
			g_playerTagInfo[iGTAID].stairStackedOffset -= 5.0f;
			if ( g_playerTagInfo[iGTAID].stairStackedOffset < 5.0f )
			{
				g_playerTagInfo[iGTAID].stairStackedOffset = 0.0f;
				g_playerTagInfo[iGTAID].isStairStacked = false;
			}
		}
	}		// end outer while - remove staircase problem

	// reset iter position & setup iterInner
	iter = pPools->m_pedPool.map.begin();

	// detect & adjust for ESP collisions
	while ( iter.pos < iter.end )
	{
		// map iterator pointer to our pointer
		iterPed = iter.pos->second;

		// advance to next item for next pass
		iter.pos++;
		if ( !iterPed )
			continue;

		// get player id
		iGTAID = (int)iterPed->GetArrayID();

		// we isPastMaxDistance or stairstacked, move along
		if ( g_playerTagInfo[iGTAID].isPastMaxDistance || g_playerTagInfo[iGTAID].isStairStacked )
			continue;

		// reset iterInner position
		iterInner = pPools->m_pedPool.map.begin();
		while ( iterInner.pos < iterInner.end )
		{
			// map iterator pointer to our pointer
			iterInnerPed = iterInner.pos->second;

			// advance to next item for next pass
			iterInner.pos++;
			if ( !iterInnerPed )
				continue;

			// get player id
			iGTAID_Inner = (int)iterInnerPed->GetArrayID();

			// filter out isPastMaxDistance, stairstacked, and same Ped
			if ( g_playerTagInfo[iGTAID].isPastMaxDistance
			 ||	 g_playerTagInfo[iGTAID_Inner].isStairStacked
			 ||	 iGTAID == iGTAID_Inner ) continue;

			// player is within range, figure out if there's collision
			if ( abs(g_playerTagInfo[iGTAID].tagPosition.fX - g_playerTagInfo[iGTAID_Inner].tagPosition.fX) <= 100.0f
			 &&	 abs((g_playerTagInfo[iGTAID].tagPosition.fY - g_playerTagInfo[iGTAID].tagOffsetY) - (
						  g_playerTagInfo[iGTAID_Inner].tagPosition.fY - g_playerTagInfo[iGTAID_Inner].tagOffsetY)) <= ESP_tag_player_espHeight )
			{
				// collision, figure out who gets to stay
				if ( g_playerTagInfo[iGTAID].tagPosition.fZ < g_playerTagInfo[iGTAID_Inner].tagPosition.fZ )
				{
					// playerID "g_pTI_i" is farther, it should move up
					g_playerTagInfo[iGTAID_Inner].tagOffsetY += 5.0f;
					isPedESPCollided[iGTAID_Inner] = true;
				}
				else if ( g_playerTagInfo[iGTAID].tagPosition.fZ > g_playerTagInfo[iGTAID_Inner].tagPosition.fZ )
				{
					// playerID "i" is farther, it should move up
					// we should only need normal upward movement here
					g_playerTagInfo[iGTAID].tagOffsetY += 5.0f;
					isPedESPCollided[iGTAID] = true;
				}
				else
				{
					// both playerIDs are the same position @_@ so prefer the lower ID#
					if ( iGTAID < iGTAID_Inner )
					{
						g_playerTagInfo[iGTAID_Inner].tagOffsetY += 5.0f;
						isPedESPCollided[iGTAID_Inner] = true;
					}
					else
					{
						g_playerTagInfo[iGTAID].tagOffsetY += 5.0f;
						isPedESPCollided[iGTAID] = true;
					}
				}
			}

			// are we jigglin?  everybody likes ta jiggle.
			if (	abs(g_playerTagInfo[iGTAID].tagPosition.fX - g_playerTagInfo[iGTAID_Inner].tagPosition.fX) <= 100.0f
					&& abs(
						(g_playerTagInfo[iGTAID].tagPosition.fY - g_playerTagInfo[iGTAID].tagOffsetY)
						- (g_playerTagInfo[iGTAID_Inner].tagPosition.fY - g_playerTagInfo[iGTAID_Inner].tagOffsetY)
					) - 5.0f <= ESP_tag_player_espHeight
				)
			{
				if ( g_playerTagInfo[iGTAID].tagPosition.fZ < g_playerTagInfo[iGTAID_Inner].tagPosition.fZ )
				{
					isPedESPCollided[iGTAID_Inner] = true;
				}
				else
				{
					isPedESPCollided[iGTAID] = true;
				}
			}
		}	// end inner while

		// return tagOffsetY to zero if needed
		if ( !isPedESPCollided[iGTAID] )
		{
			if ( g_playerTagInfo[iGTAID].tagOffsetY >= 5.0f )
			{
				g_playerTagInfo[iGTAID].tagOffsetY -= 5.0f;
			}
			else
			{
				g_playerTagInfo[iGTAID].tagOffsetY = 0.0f;
			}
		}
	}		// end outer while

	// reset iter position & setup iterInner
	iter = pPools->m_pedPool.map.begin();

	// start render ESP tags
	float h, playerBaseY;
	while ( iter.pos < iter.end )
	{
		// map iterator pointer to our pointer
		iterPed = iter.pos->second;

		// advance to next item for next pass
		iter.pos++;
		if ( !iterPed )
			continue;

		// get player id
		iGTAID = (int)iterPed->GetArrayID();

		// ignore if isPastMaxDistance or if it's us
		if ( g_playerTagInfo[iGTAID].isPastMaxDistance || iGTAID == selfGTAID )
			continue;

		playerBaseY = g_playerTagInfo[iGTAID].tagPosition.fY -
			g_playerTagInfo[iGTAID].tagOffsetY +
			ESP_tag_player_pixelOffsetY;

		int iSAMPID;
		if ( g_Players )
			iSAMPID = translateGTASAMP_pedPool.iSAMPID[getPedGTAIDFromInterface( (DWORD *)iterPed->GetPedInterface() )];

		// get Ped health
		// works in single player, but SAMP maintains its own player health
		//vh = iterPed->GetHealth();
		// get samp health
		if ( g_Players )
		{
			if ( g_Players->pRemotePlayer[iSAMPID] != NULL
				&&	 g_Players->pRemotePlayer[iSAMPID]->pPlayerData != NULL
				&&  g_Players->pRemotePlayer[iSAMPID]->pPlayerData->pSAMP_Actor != NULL
				&&  (DWORD)g_Players->pRemotePlayer[iSAMPID]->pPlayerData->pSAMP_Actor->pGTA_Ped == (DWORD)iterPed->GetPedInterface() )
			{
				vh = g_Players->pRemotePlayer[iSAMPID]->pPlayerData->fActorHealth;
				va = g_Players->pRemotePlayer[iSAMPID]->pPlayerData->fActorArmor;
			}
			else
			{
				// SA-MP running, but was not a remote player
				continue;
			}
		}
		else
		{
			// SA-MP not running or failed to initialize g_Players
			vh = iterPed->GetHealth();
			va = iterPed->GetArmor();
		}


		float hpbar = vh;
		if ( hpbar > 100.0f )
			hpbar = 100.0f;
		hpbar *= 70.0f / 100.0f;

		float offY = ESP_tag_player_D3DBox_pixelOffsetY;
		if ( va > 0.0f )
		{
			float armbar = va;
			if ( armbar > 100.0f )
				armbar = 100.0f;
			armbar *= 70.0f / 100.0f;
			render->D3DBoxBorder( g_playerTagInfo[iGTAID].tagPosition.fX + ESP_tag_player_D3DBox_pixelOffsetX,
							playerBaseY + offY, 70.0f, 10.0f, D3DCOLOR_ARGB(255, 0, 0, 0), D3DCOLOR_ARGB(128, 50, 50, 50) );
			render->D3DBox( g_playerTagInfo[iGTAID].tagPosition.fX + 1.0f + ESP_tag_player_D3DBox_pixelOffsetX,
							playerBaseY + 1.0f + offY, armbar - 2.0f, 8.0f,
							D3DCOLOR_ARGB(128, 250, 250, 250) );
			offY += 11.0f;
		}

		render->D3DBoxBorder( g_playerTagInfo[iGTAID].tagPosition.fX + ESP_tag_player_D3DBox_pixelOffsetX,
						playerBaseY + offY, 70.0f, 10.0f, D3DCOLOR_ARGB(255, 0, 0, 0), D3DCOLOR_ARGB(128, 80, 0, 0) );
		render->D3DBox( g_playerTagInfo[iGTAID].tagPosition.fX + 1.0f + ESP_tag_player_D3DBox_pixelOffsetX,
						playerBaseY + 1.0f + offY, hpbar - 2.0f, 8.0f, D3DCOLOR_ARGB(128, 255, 0, 0) );

		// this should also calculate the anti-aliasing top edge somehow
		h = pD3DFontFixedSmall->DrawHeight() + 1;

		if (va > 0.0f)
			sprintf_s(buf, "%d {E00000}%d", (int)va, (int)vh);
		else
			sprintf_s(buf, "{E00000}%d", (int)vh);
		float w = pD3DFontFixedSmall->DrawLength(buf);
		pD3DFontFixedSmall->PrintShadow(g_playerTagInfo[iGTAID].tagPosition.fX + 70.0f - w - 1.0f, playerBaseY + 10.0f + offY,
										D3DCOLOR_ARGB(0xFF, 0xF0, 0xF0, 0xF0), buf);
		if ( g_Players )
		{
			// render the main nametag last so it's on top
			// this should calculate the anti-aliasing top edge somehow
			h = pD3DFont_sampStuff->DrawHeight() - 1;
			sprintf_s( buf, "%s (%d)", getPlayerName(iSAMPID), iSAMPID );
			pD3DFont_sampStuff->PrintShadow( g_playerTagInfo[iGTAID].tagPosition.fX, playerBaseY - h,
			samp_color_get( iSAMPID, 0xDD000000 ), buf );

			if (g_Players->pRemotePlayer[iSAMPID]->pPlayerData->iAFKState == 2)
			{
				pD3DFontFixedSmall->PrintShadow(g_playerTagInfo[iGTAID].tagPosition.fX + 1.0f, playerBaseY + 10.0f + offY,
												D3DCOLOR_ARGB(0xFF, 0xF0, 0xF0, 0xF0), "AFK");
			}
		}
	}

	// end render ESP tags
}

// render vehicle ESP
void renderVehicleTags ( void )
{
	traceLastFunc( "renderVehicleTags()" );

	// don't run if the menu is active
	if ( gta_menu_active() )
		return;

	// no tags during panic attacks
	if ( cheat_state->_generic.cheat_panic_enabled )
		return;

	// don't run if the pools don't exist
	if ( !pGameInterface || !pGameInterface->GetPools() )
		return;

	// don't run if we don't exist
	if ( !pPedSelf )
		return;

	// don't display tags during certain key press & game events
	// g_dwSAMP_Addr will be set before sa-mp was completely initialized
	if	( g_SAMP && g_dwSAMP_Addr &&
			(
				(GetAsyncKeyState(VK_TAB) < 0 && set.d3dtext_score)
				|| g_Scoreboard->iIsEnabled
				|| GetAsyncKeyState(VK_F10) < 0
			)
		)
		return;

	const vehicle_entry *vehicle;
	char				buf[256];
	int					ESP_tag_vehicle_pixelOffsetY = 0;
	float				ESP_tag_vehicle_D3DBox_pixelOffsetX = -0.5;
	float				ESP_tag_vehicle_D3DBox_pixelOffsetY = -0.5;
	float				ESP_tag_vehicle_posOffsetZ = -1.0f;
	int					v;
	float				w, h, vh;

	D3DXVECTOR3			poss, screenposs;
	D3DCOLOR			vcolor;
	CVector2D			screenPosition;
	CVector				ourPosition, iterPosition, ourPosMinusIter;

	// get our position
	if ( !isBadPtr_GTA_pVehicle(pPedSelf->GetVehicle()) )
	{
		// RC Vehicle Fix (Not showing names of recently streamed in players
		// while being in a RC Vehicle)
		ourPosition = *(pPedSelf->GetVehicle()->GetPosition());
	}
	else
	{
		ourPosition = pPedSelf->GetInterface()->Placeable.matrix->vPos;
	}

	// setup iterator
	CVehicleSA	*iterVehicle = NULL;
	CPoolsSA	*pPools = reinterpret_cast < CPoolsSA * > ( pGameInterface->GetPools() );
	CPoolsSA::vehiclePool_t::mapType::iterator iter = pPools->m_vehiclePool.map.begin();

	// iterate
	while ( iter.pos < iter.end )
	{
		// map iterator CVehicleSA pointer to our CVehicleSA pointer
		iterVehicle = iter.pos->second;

		// advance to next CVehicleSA for next pass
		iter.pos++;

		// move past null pointers
		if ( isBadPtr_GTA_pVehicle(iterVehicle) )
			continue;
		//if ( isBadPtr_GTA_pVehicle(iterVehicle->GetVehicleInterface()) )
		//	continue;

		// check if it's farther than set.vehicle_tags_dist
		iterPosition = iterVehicle->GetInterface()->Placeable.matrix->vPos;
		ourPosMinusIter = ourPosition - iterPosition;
		if ( ourPosMinusIter.Length() > set.vehicle_tags_dist )
			continue;

		// check if it's our vehicle
		if ( iterVehicle == pPedSelf->GetVehicle() )
			continue;

		// check if it's near zero
		if ( iterVehicle->GetPosition()->IsNearZero() )
			continue;

		// CVector to D3DXVECTOR3, function to be converted to CVector later
		poss.x = iterPosition.fX;
		poss.y = iterPosition.fY;
		poss.z = iterPosition.fZ + ESP_tag_vehicle_posOffsetZ;

		// yup
		CalcScreenCoors( &poss, &screenposs );

		// check if the vehicle is culled or not
		if ( screenposs.z < 1.f )
			continue;

		// D3DXVECTOR3 to CVector2D
		screenPosition.fX = screenposs.x;
		screenPosition.fY = screenposs.y;

		// get the vehicle model's name
		vehicle = gta_vehicle_get_by_id( iterVehicle->GetModelIndex() );

		// get SAMP's vehicle id
		if ( g_Vehicles != NULL )
			v = translateGTASAMP_vehiclePool.iSAMPID[getVehicleGTAIDFromInterface( (DWORD *)iterVehicle->GetVehicleInterface() )];
		else
			v = (int)iterVehicle->GetArrayID();

		/////////////////
		// render time //
		h = pD3DFontFixed->DrawHeight();
		_snprintf_s( buf, sizeof(buf)-1, "%s (%d)", vehicle->name, v );
		w = pD3DFontFixed->DrawLength( buf );

		// get color by primary vehicle color from colors palette
		byte color[4];
		iterVehicle->GetColor(&color[0], &color[1], &color[2], &color[3]);
		RwColor rwcolor = getVehicleColorRGB(color[0]);

		// render vehicle name
		pD3DFontFixed->PrintShadow( screenPosition.fX, screenPosition.fY - h + ESP_tag_vehicle_pixelOffsetY,
										 D3DCOLOR_ARGB( 128, rwcolor.r, rwcolor.g, rwcolor.b ), buf );

		// health bar
		vh = iterVehicle->GetVehicleInterface()->m_nHealth;
		if ( vh > 1000.0f )
			vh = 1000.0f;
		vh /= 10.0f;
		if ( vh > 50.0f )
			vcolor = D3DCOLOR_ARGB( 64, 0, 150, 0 );
		else if ( vh > 25.0f )
			vcolor = D3DCOLOR_ARGB( 64, 150, 150, 0 );
		else
			vcolor = D3DCOLOR_ARGB( 64, 200, 0, 0 );

		// render health bar
		render->D3DBox( screenPosition.fX + ESP_tag_vehicle_D3DBox_pixelOffsetX,
						screenPosition.fY + ESP_tag_vehicle_pixelOffsetY + ESP_tag_vehicle_D3DBox_pixelOffsetY, 100.0f,
						11.0f, D3DCOLOR_ARGB(48, 0, 0, 0) );
		render->D3DBox( screenPosition.fX + 1.0f + ESP_tag_vehicle_D3DBox_pixelOffsetX,
						screenPosition.fY + 1.0f + ESP_tag_vehicle_pixelOffsetY + ESP_tag_vehicle_D3DBox_pixelOffsetY,
						vh - 2.0f, 9.0f, vcolor );

		h = pD3DFontFixedSmall->DrawHeight();
		_snprintf_s( buf, sizeof(buf)-1, "Health: %d", (int)vh );
		pD3DFontFixedSmall->PrintShadow( screenPosition.fX + 4.0f,
										 screenPosition.fY - h + 10.0f + ESP_tag_vehicle_pixelOffsetY,
										 D3DCOLOR_ARGB(90, 0, 255, 0), buf );

/*
// trailer debugging visualizations
		CVector vecTowBarPos, vecTowHitchPos;
		iterVehicle->GetTowBarPos( &vecTowBarPos );
		iterVehicle->GetTowHitchPos( &vecTowHitchPos );
		// plot vehicle position box
		render->D3DBox( screenPosition.fX,
						screenPosition.fY,
						5.0f,
						5.0f,
						D3DCOLOR_ARGB(255, 0, 0, 255) );
		// plot Tow Bar box
		poss.x = vecTowBarPos.fX;
		poss.y = vecTowBarPos.fY;
		poss.z = vecTowBarPos.fZ;
		CalcScreenCoors( &poss, &screenposs );
		screenPosition.fX = screenposs.x;
		screenPosition.fY = screenposs.y;
		render->D3DBox( screenPosition.fX,
						screenPosition.fY,
						10.0f,
						10.0f,
						D3DCOLOR_ARGB(255, 0, 255, 0) );
		// plot Tow Hitch box
		poss.x = vecTowHitchPos.fX;
		poss.y = vecTowHitchPos.fY;
		poss.z = vecTowHitchPos.fZ;
		CalcScreenCoors( &poss, &screenposs );
		screenPosition.fX = screenposs.x;
		screenPosition.fY = screenposs.y;
		render->D3DBox( screenPosition.fX,
						screenPosition.fY,
						10.0f,
						10.0f,
						D3DCOLOR_ARGB(255, 255, 0, 0) );
*/
	}
}

void RenderTeleportTexts ( void )
{
	int					i;
	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );
	char				buf[32];

	if ( cheat_state->_generic.cheat_panic_enabled )
		return;

	if ( self != NULL )
	{
		for ( i = 0; i < TELEPORT_MAX; i++ )
		{
			float		pos[3], screenpos[3];
			D3DXVECTOR3 poss, screenposs;
			vect3_copy( &cheat_state->teleport[i].matrix[4 * 3], pos );
			if ( vect3_near_zero(pos) )
				continue;
			if ( vect3_dist(pos, &self->base.matrix[4 * 3]) > set.player_tags_dist )
				continue;

			poss.x = pos[0];
			poss.y = pos[1];
			poss.z = pos[2];
			CalcScreenCoors( &poss, &screenposs );
			screenpos[0] = screenposs.x;
			screenpos[1] = screenposs.y;
			screenpos[2] = screenposs.z;
			if ( screenpos[2] < 1.f )
				continue;

			sprintf( buf, "Teleport: %d", i );
			pD3DFontFixed->PrintShadow( screenpos[0], screenpos[1] - 5.0f, D3DCOLOR_XRGB(0, 200, 200), buf );
		}
	}
}

void RenderPickupTexts ( void )
{
	traceLastFunc( "renderPickupTexts()" );

	if ( cheat_state->_generic.cheat_panic_enabled )
		return;
	if ( g_SAMP->pPools->pPickup == NULL )
		return;

	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

	if ( (GetAsyncKeyState(VK_TAB) < 0 && set.d3dtext_score)
	 ||	 g_Scoreboard->iIsEnabled ) 
		return;

	char	buf[32];
	int		i;
	if ( self != NULL )
	{
		for ( i = 0; i < SAMP_MAX_PICKUPS; i++ )
		{
			if ( g_SAMP->pPools->pPickup->pickup[i].iModelID == 0 )
				continue;
			if ( g_SAMP->pPools->pPickup->pickup[i].iType == 0 )
				continue;

			float		pos[3], screenpos[3];
			D3DXVECTOR3 poss, screenposs;
			vect3_copy( g_SAMP->pPools->pPickup->pickup[i].fPosition, pos );
			if ( vect3_near_zero(pos) )
				continue;
			if ( vect3_dist( pos, &self->base.matrix[4 * 3] ) > set.pickup_tags_dist )
				continue;

			poss.x = pos[0];
			poss.y = pos[1];
			poss.z = pos[2];
			CalcScreenCoors( &poss, &screenposs );
			screenpos[0] = screenposs.x;
			screenpos[1] = screenposs.y;
			screenpos[2] = screenposs.z;
			if ( screenpos[2] < 1.f )
				continue;

			_snprintf_s( buf, sizeof(buf)-1, "Pickup: %d, ModelID: %d", i, g_SAMP->pPools->pPickup->pickup[i].iModelID );
			pD3DFontFixed->PrintShadow( screenpos[0], screenpos[1] - 5.0f, D3DCOLOR_XRGB(0, 200, 0), buf );
		}
	}
}

void RenderObjectTexts ( void )
{
	traceLastFunc( "renderObjectTexts()" );

	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );
	if ( cheat_state->_generic.cheat_panic_enabled || self == NULL )
		return;
	if ( g_SAMP->pPools->pObject == NULL )
		return;

	if ( (GetAsyncKeyState(VK_TAB) < 0 && set.d3dtext_score)
	 ||	g_Scoreboard->iIsEnabled ) 
		return;

	char	buf[32];
	int		i;
	for ( i = 0; i < SAMP_MAX_OBJECTS; i++ )
	{
		if ( g_SAMP->pPools->pObject->iIsListed[i] != 1 )
			continue;
		if ( g_SAMP->pPools->pObject->object[i] == NULL )
			continue;
		if ( g_SAMP->pPools->pObject->object[i]->pGTAEntity == NULL )
			continue;

		float		pos[3], screenpos[3];
		D3DXVECTOR3 poss, screenposs;
		vect3_copy( &g_SAMP->pPools->pObject->object[i]->pGTAEntity->base.matrix[4 * 3], pos );
		if ( vect3_near_zero(pos) )
			continue;
		if ( vect3_dist(pos, &self->base.matrix[4 * 3]) > set.object_tags_dist )
			continue;

		poss.x = pos[0];
		poss.y = pos[1];
		poss.z = pos[2];
		CalcScreenCoors( &poss, &screenposs );
		screenpos[0] = screenposs.x;
		screenpos[1] = screenposs.y;
		screenpos[2] = screenposs.z;
		if ( screenpos[2] < 1.f )
			continue;

		_snprintf_s( buf, sizeof(buf)-1, "Object: %d, ModelID: %d", i,
				 g_SAMP->pPools->pObject->object[i]->pGTAEntity->base.model_alt_id );
		pD3DFontFixed->PrintShadow( screenpos[0], screenpos[1] - 5.0f, D3DCOLOR_XRGB(200, 200, 0), buf );
	}
}

void renderPlayerInfoList ( void )
{
	traceLastFunc( "renderPlayerInfoList()" );

	if ( gta_menu_active() )
		return;

	if ( (GetAsyncKeyState(VK_TAB) < 0 && set.d3dtext_score)
	 ||	g_Scoreboard->iIsEnabled ) return;

	if ( GetAsyncKeyState(VK_F1) < 0 )
		return;
	if ( GetAsyncKeyState(VK_F5) < 0 )
		return;
	if ( GetAsyncKeyState(VK_F10) < 0 )
		return;
	if ( cheat_state->_generic.cheat_panic_enabled )
		return;

	if ( g_Players == NULL && g_Vehicles == NULL )
		return;

	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );
	if ( self == NULL )
		return;

	//chat window is on the left
	float						width = ( pPresentParam.BackBufferWidth / 4 );
	float						height = 20.0f;

	const struct vehicle_entry	*vehicle;
	char						buf[256];
	float						pos[3];

	int							amount_players = getPlayerCount();
	if ( amount_players == 1 )
	{
		pD3DFont_sampStuff->PrintShadow( width, height, D3DCOLOR_XRGB(255, 255, 255),
										 "There are no more players but you" );
		return;
	}

	int max_amount_players = ( pPresentParam.BackBufferHeight ) / ( 1.0f + pD3DFont_sampStuff->DrawHeight() );
	max_amount_players -= 2;

	int			rendered_players = 0;
	static int	current_player = 0;
	static int	current_player_id = 0;

	/***/
	if ( amount_players > max_amount_players )
	{
		if ( KEY_PRESSED(VK_NEXT) )
		{
			current_player += max_amount_players;
			if ( current_player > (amount_players - max_amount_players) )
				current_player = 1 + amount_players - max_amount_players;
			current_player_id = getNthPlayerID( current_player );
		}
		else if ( KEY_PRESSED(VK_PRIOR) )
		{
			current_player -= max_amount_players;
			if ( current_player < 0 )
			{
				current_player = 0;
				current_player_id = 0;
			}
			else
				current_player_id = getNthPlayerID( current_player );
		}
	}
	else
	{
		current_player = 0;
		current_player_id = 0;
	}

	/***/
	int i;
	for ( i = current_player_id; i < SAMP_MAX_PLAYERS; i++ )
	{
		D3DCOLOR	color = MENU_COLOR_DEFAULT;
		if ( g_Players->iIsListed[i] != 1 )
			continue;

		rendered_players++;
		if ( rendered_players >= max_amount_players )
			return;

		if ( g_Players->pRemotePlayer[i]->pPlayerData == NULL
		 ||	 g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Actor == NULL )
		{
			_snprintf_s( buf, sizeof(buf)-1, "Name: %s (ID: %d), not streamed in", getPlayerName(i), i );
			pD3DFont_sampStuff->PrintShadow( width, height, color, buf );
			height += 1.0f + pD3DFont_sampStuff->DrawHeight();
			continue;
		}

		if ( !getPlayerPos(i, pos) )
			continue;

		color = samp_color_get( i );

		const char	*szPlayerName = getPlayerName( i );
		int			iPlayerHealth = (int)g_Players->pRemotePlayer[i]->pPlayerData->fActorHealth;
		int			iPlayerArmor = (int)g_Players->pRemotePlayer[i]->pPlayerData->fActorArmor;
		int			iVehicleID = (int)g_Players->pRemotePlayer[i]->pPlayerData->sVehicleID;
		int			iVehicleHealth;
		if ( g_Players->pRemotePlayer[i]->pPlayerData != NULL
		 &&	 g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Vehicle != NULL )
		{
			uint16_t	playerVehicleID = g_Players->pRemotePlayer[i]->pPlayerData->sVehicleID;
			vehicle = gta_vehicle_get_by_id( g_Vehicles->pSAMP_Vehicle[playerVehicleID]->pGTA_Vehicle->base.model_alt_id );
			iVehicleHealth = (int)g_Players->pRemotePlayer[i]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle->hitpoints;
		}

		switch ( getPlayerState(i) )
		{
		case PLAYER_STATE_NONE:
			_snprintf_s( buf, sizeof(buf)-1, "Name: %s (ID: %d), State: None", szPlayerName, i );
			pD3DFont_sampStuff->PrintShadow( width, height, color, buf );
			break;

		case PLAYER_STATE_ONFOOT:
			_snprintf_s( buf, sizeof(buf)-1, "Name: %s (ID: %d), State: On foot, Health: %d, Armor: %d, Distance: %0.2f",
						 szPlayerName, i, iPlayerHealth, iPlayerArmor, vect3_dist((float *)pos, &self->base.matrix[4 * 3]) );
			pD3DFont_sampStuff->PrintShadow( width, height, color, buf );
			break;

		case PLAYER_STATE_DRIVER:
			_snprintf_s( buf, sizeof(buf)-1, "Name: %s (ID: %d), State: Driver (%s (%d)), VHealth: %d, Distance: %0.2f",
						 szPlayerName, i, vehicle->name, iVehicleID, iVehicleHealth,
						 vect3_dist((float *)pos, &self->base.matrix[4 * 3]) );
			pD3DFont_sampStuff->PrintShadow( width, height, color, buf );
			break;

		case PLAYER_STATE_PASSENGER:
			_snprintf_s( buf, sizeof(buf)-1, "Name: %s (ID: %d), State: Passenger (%s (%d)), Distance: %0.2f",
						 szPlayerName, i, vehicle->name, iVehicleID, vect3_dist((float *)pos, &self->base.matrix[4 * 3]) );
			pD3DFont_sampStuff->PrintShadow( width, height, color, buf );
			break;

		case PLAYER_STATE_WASTED:
			_snprintf_s( buf, sizeof(buf)-1, "Name: %s (ID: %d), State: Wasted", szPlayerName, i );
			pD3DFont_sampStuff->PrintShadow( width, height, color, buf );
			break;

		case PLAYER_STATE_SPAWNED:
			_snprintf_s( buf, sizeof(buf)-1, "Name: %s (ID: %d), State: Spawned", szPlayerName, i );
			pD3DFont_sampStuff->PrintShadow( width, height, color, buf );
			break;
		}

		height += 1.0f + pD3DFont_sampStuff->DrawHeight();
	}
}

void renderTextLabels ()
{
	traceLastFunc( "renderTextLabels()" );

	// orig-Textlabels
	memcpy_safe( (void *)(g_dwSAMP_Addr + SAMP_DRAWTEXTLABELS), "\x74", 1 );

	if ( gta_menu_active() || !set.d3dtext_labels )
		return;

	if ( cheat_state->_generic.cheat_panic_enabled )
		return;

	if ( g_SAMP->pPools->pText3D == NULL || g_Vehicles == NULL || g_Players == NULL )
		return;

	struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );
	if ( self == NULL )
		return;

	// Deactivate orig-Textlabels
	memcpy_safe( (void *)(g_dwSAMP_Addr + SAMP_DRAWTEXTLABELS), "\xEB", 1 );

	if ( (GetAsyncKeyState(VK_TAB) < 0 && set.d3dtext_score)
		|| g_Scoreboard->iIsEnabled ) 
		return;

	if ( GetAsyncKeyState(VK_F10) < 0 )
		return;

	char	buf[2048];
	for ( int i = 0; i < SAMP_MAX_3DTEXTS; i++ )
	{
		if ( !g_SAMP->pPools->pText3D->iIsListed[i] )
			continue;
		if ( g_SAMP->pPools->pText3D->textLabel[i].pText != NULL )
		{
			float		pos[3], screenpos[3];
			D3DXVECTOR3 poss, screenposs;

			if ( g_SAMP->pPools->pText3D->textLabel[i].sAttachedToPlayerID == ((uint16_t) - 1)
			 &&	 g_SAMP->pPools->pText3D->textLabel[i].sAttachedToVehicleID == ((uint16_t) - 1) )
			{
				vect3_copy( g_SAMP->pPools->pText3D->textLabel[i].fPosition, pos );
			}
			else if ( g_SAMP->pPools->pText3D->textLabel[i].sAttachedToPlayerID != ((uint16_t) - 1) )
			{
				int id = g_SAMP->pPools->pText3D->textLabel[i].sAttachedToPlayerID;
				// check if player is valid
				if ( g_Players->pRemotePlayer[id] == NULL || g_Players->pRemotePlayer[id]->pPlayerData == NULL 
					|| g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor == NULL
					|| g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor->pGTA_Ped == NULL )
					continue;
				vect3_copy( &g_Players->pRemotePlayer[id]->pPlayerData->pSAMP_Actor->pGTA_Ped->base.matrix[4 * 3],
					pos );
				if ( !near_zero(pos[2]) )
					pos[2] += 0.5f;
			}
			else if ( g_SAMP->pPools->pText3D->textLabel[i].sAttachedToVehicleID != ((uint16_t) - 1) )
			{
				int id = g_SAMP->pPools->pText3D->textLabel[i].sAttachedToVehicleID;
				// check if vehicle is valid
				if ( g_Vehicles->pGTA_Vehicle[id] == NULL )
					continue;
				else
					vect3_copy( &g_Vehicles->pGTA_Vehicle[id]->base.matrix[4 * 3], pos );
			}

			if ( vect3_near_zero(pos) )
				continue;
			if ( vect3_dist(pos, &self->base.matrix[4 * 3]) > set.d3dtext_labels_maxDist )
				continue;

			poss.x = pos[0];
			poss.y = pos[1];
			poss.z = pos[2];
			CalcScreenCoors( &poss, &screenposs );
			screenpos[0] = screenposs.x;
			screenpos[1] = screenposs.y;
			screenpos[2] = screenposs.z;

			if ( screenpos[2] < 1.f )
				continue;

			snprintf( buf, sizeof(buf), "%s", g_SAMP->pPools->pText3D->textLabel[i].pText );
			pD3DFontFixed->PrintShadow( screenpos[0], screenpos[1], g_SAMP->pPools->pText3D->textLabel[i].color,
										buf );
		}
	}
}

void renderScoreList ()
{
	traceLastFunc( "renderScoreList()" );

	if ( g_Players == NULL )
		return;

	if ( GetAsyncKeyState(VK_F10) < 0 )
		return;

	if ( !set.d3dtext_score )
		return;

	// enable textdrawPool
	// memcpy_safe( (void *)(g_dwSAMP_Addr + SAMP_GAMEPROCESSHOOK), "\x74", 1 );

	static int	patched = 0;
	if ( cheat_state->_generic.cheat_panic_enabled && patched )
	{
		patched = !sampPatchDisableScoreboardToggleOn( 0 );
		return;
	}
	else if ( cheat_state->_generic.cheat_panic_enabled )
		return;
	else
	{
		sampPatchDisableScoreboardToggleOn( 1 );
		patched = 1;
	}

	if (g_Scoreboard->iIsEnabled)
		toggleOffScoreboard();

	if ( !KEY_DOWN(VK_TAB) )
		return;

	// disable SAMP chat
	g_Chat->iChatWindowMode = 0;
	//memcpy_safe( (void *)(g_dwSAMP_Addr + SAMP_GAMEPROCESSHOOK), "\xEB", 1 );

	//// Want updated data
	updateScoreboardData();

	char 	buffer[512];
	float	lowest;
	int		amount_players = getPlayerCount();
	lowest = 115.0f;

	int max_amount_players = ( pPresentParam.BackBufferHeight - 110.0f - lowest ) /
		( 1.0f + pD3DFont_sampStuff->DrawHeight() );
	max_amount_players -= 2;

	int			rendered_players = 0;
	static int	current_player = 0;
	static int	current_player_id = 0;
	float		loc[2] = { (float) ( pPresentParam.BackBufferWidth / 4 ), 100.0f };

	if ( amount_players < max_amount_players )
	{
		current_player = 0;
		current_player_id = 0;
		if ( amount_players < max_amount_players / 2 )
		{
			loc[1] = ( pPresentParam.BackBufferHeight / 4 );
			lowest = pPresentParam.BackBufferHeight - loc[1] - ( (amount_players + 2) * (1.0f + pD3DFont_sampStuff->DrawHeight()) );
		}
		else
			loc[1] += ( 1.0f + pD3DFont_sampStuff->DrawHeight() ) * ( (max_amount_players + 1) - amount_players );
	}
	else if ( amount_players > max_amount_players )
	{
		if ( KEY_PRESSED(VK_NEXT) )
		{
			current_player += max_amount_players;
			if ( current_player > (amount_players - max_amount_players) )
				current_player = 1 + amount_players - max_amount_players;
			current_player_id = getNthPlayerID( current_player );
		}
		else if ( KEY_PRESSED(VK_PRIOR) )
		{
			current_player -= max_amount_players;
			if ( current_player < 0 )
			{
				current_player = 0;
				current_player_id = 0;
			}
			else
				current_player_id = getNthPlayerID( current_player );
		}
	}
	else
		current_player = 0;

	loc[1] -= 1.0f + pD3DFont_sampStuff->DrawHeight();
	render->D3DBox( loc[0] - 10.0f, loc[1] - 2.0f, (pPresentParam.BackBufferWidth / 2),
					pD3DFont_sampStuff->DrawHeight() + 3.0f, D3DCOLOR_ARGB(150, 200, 200, 200) );
	_snprintf_s( buffer, sizeof(buffer)-1, "%s (%s:%d) Connected Players: %d", g_SAMP->szHostname, g_SAMP->szIP,
				 g_SAMP->ulPort, amount_players );
	pD3DFont_sampStuff->PrintShadow( loc[0], loc[1], D3DCOLOR_ARGB(200, 255, 255, 255), buffer );
	loc[1] += 10.0f + pD3DFont_sampStuff->DrawHeight();

	render->D3DBox( loc[0] - 10.0f, loc[1] - 10.0f, (pPresentParam.BackBufferWidth / 2),
					pPresentParam.BackBufferHeight - loc[1] - lowest, D3DCOLOR_ARGB(150, 100, 100, 100) );

	_snprintf_s( buffer, sizeof(buffer)-1, "%s (%d)", getPlayerName(g_Players->sLocalPlayerID), g_Players->sLocalPlayerID );
	pD3DFont_sampStuff->PrintShadow( loc[0], loc[1], samp_color_get(g_Players->sLocalPlayerID), buffer );

	loc[0] += ( pPresentParam.BackBufferWidth / 4 );
	_snprintf_s( buffer, sizeof(buffer)-1, "%d", g_Players->iLocalPlayerScore );
	pD3DFont_sampStuff->PrintShadow( loc[0], loc[1], samp_color_get(g_Players->sLocalPlayerID), buffer );

	loc[0] += ( pPresentParam.BackBufferWidth / 4 ) - 70.0f;
	_snprintf_s( buffer, sizeof(buffer)-1, "%d", g_Players->iLocalPlayerPing );
	pD3DFont_sampStuff->PrintShadow( loc[0], loc[1], samp_color_get(g_Players->sLocalPlayerID), buffer );

	for ( int i = current_player_id; i < SAMP_MAX_PLAYERS; i++ )
	{
		if ( g_Players->sLocalPlayerID == i )
			continue;
		if ( g_Players->pRemotePlayer[i] == NULL )
			continue;

		rendered_players++;
		loc[0] = ( pPresentParam.BackBufferWidth / 4 );
		loc[1] += 1.0f + pD3DFont_sampStuff->DrawHeight();

		if ( g_Players->pRemotePlayer[i]->iIsNPC == 1 )
			_snprintf_s( buffer, sizeof(buffer)-1, "[BOT]%s (%d)", getPlayerName(i), i );
		else
			_snprintf_s( buffer, sizeof(buffer)-1, "%s (%d)", getPlayerName(i), i );

		pD3DFont_sampStuff->PrintShadow( loc[0], loc[1], samp_color_get(i), buffer );

		loc[0] += ( pPresentParam.BackBufferWidth / 4 );
		_snprintf_s( buffer, sizeof(buffer)-1, "%d", g_Players->pRemotePlayer[i]->iScore );
		pD3DFont_sampStuff->PrintShadow( loc[0], loc[1], samp_color_get(i), buffer );

		loc[0] += ( pPresentParam.BackBufferWidth / 4 ) - 70.0f;
		_snprintf_s( buffer, sizeof(buffer)-1, "%d", g_Players->pRemotePlayer[i]->iPing );
		pD3DFont_sampStuff->PrintShadow( loc[0], loc[1], samp_color_get(i), buffer );

		if ( rendered_players >= max_amount_players )
			return;
	}
}

void renderKillList ( void )
{
	traceLastFunc( "renderKillList()" );

	if ( g_DeathList == NULL )
		return;

	static int	kill_last = -1, kill_render = 0;

	if ( (GetAsyncKeyState(VK_TAB) < 0 && set.d3dtext_score)
	 ||	 g_Scoreboard->iIsEnabled ) return;

	if ( GetAsyncKeyState(VK_F10) < 0 )
		return;

	if ( cheat_state->_generic.cheat_panic_enabled )
		return;

	mmm_yummy_poop( g_DeathList, &g_DeathList->iEnabled, &kill_last, &kill_render, "kill list" );

	if ( kill_render && !gta_menu_active() )
	{
		float	x = (float)pPresentParam.BackBufferWidth - 180.0f;
		float	y = 220.0f;
		float	w, h;
		int		i;

		if ( pSpriteTexture != NULL )
			render->D3DBindTexture( pSpriteTexture );

		for ( i = 0; i < 5; i++ )
		{
			struct stKillEntry	*ent = &g_DeathList->killEntry[i];

			if ( strlen(ent->szVictim) > 0 )
			{
				int type = ent->byteType;

				if ( type == 49 )
				{
					type = 20;	// run over
				}
				else if ( type == 54 )
				{
					type = 21;	// fall
				}
				else if ( (type >= 18 && type <= 20) || type >= 47 )
				{
					type = 19;	// suicide
				}

				if ( pSpriteTexture != NULL )
				{
					float	u = 0.0f, v = 0.0f;
					u = (float)( (type % 10) * 24 ) / 256.0f;
					v = (float)( (type / 10) * 24 ) / 256.0f;

					render->D3DTexQuad( x - 12.0f, y - 12.0f, x + 12.0f, y + 12.0f, u, v, u + 23.0f / 256.0f,
										v + 23.0f / 256.0f );
				}
				else
				{
					char	buf[32];
					sprintf( buf, "%d", type );
					pD3DFontChat->PrintShadow( x - 12.0f, y - 12.0f, 0xFFFFFFFF, buf );
				}

				h = pD3DFontChat->DrawHeight() / 2.0f;
				if ( strlen(ent->szKiller) == 0 )
				{
					w = pD3DFontChat->DrawLength( ent->szVictim );
					pD3DFontChat->PrintShadow( x - 16.0f - w, y - h, ent->clVictimColor, ent->szVictim );
				}
				else
				{
					w = pD3DFontChat->DrawLength( ent->szKiller );
					pD3DFontChat->PrintShadow( x - 16.0f - w, y - h, ent->clKillerColor, ent->szKiller );
					pD3DFontChat->PrintShadow( x + 16.0f, y - h, ent->clVictimColor, ent->szVictim );
				}
			}

			y += 24.0f;
		}

		if ( pSpriteTexture != NULL )
			render->D3DBindTexture( NULL );
	}
}

void clickWarp()
{
	traceLastFunc("clickWarp()");

	if (!g_iCursorEnabled) return;
	if (gta_menu_active()) return;

	POINT cursor_pos;
	if (GetCursorPos(&cursor_pos) && ScreenToClient(pPresentParam.hDeviceWindow, &cursor_pos))
	{
		D3DXVECTOR3 poss, screenposs;
		float pos[3];
		char buf[256];

		CVehicle *pCVehicleTeleport = nullptr;
		screenposs.x = (float)cursor_pos.x;
		screenposs.y = (float)cursor_pos.y;
		screenposs.z = 700.0f;

		CalcWorldCoors(&screenposs, &poss);

		CVector vecTarget(poss.x, poss.y, poss.z);

		// setup variables
		CVector				vecOrigin, vecGroundPos;
		CColPoint			*pCollision = nullptr;
		CEntitySAInterface	*pCollisionEntity = nullptr;

		// origin = our camera
		vecOrigin = *pGame->GetCamera()->GetCam(pGame->GetCamera()->GetActiveCam())->GetSource();

		// check for collision
		bool bCollision = GTAfunc_ProcessLineOfSight( &vecOrigin, &vecTarget, &pCollision, &pCollisionEntity,
			1, 1, 0, 1, 1, 0, 0, 0 );

		if (bCollision && pCollision)
		{
			// calculate position to check for ground
			vecGroundPos = *pCollision->GetPosition();
			if ( cheat_state->state == CHEAT_STATE_VEHICLE )
			{
				vecGroundPos = vecGroundPos - (*pCollision->GetNormal() * 2.0f);
			}
			else
			{
				vecGroundPos = vecGroundPos - (*pCollision->GetNormal() * 0.5f);
			}

			// get ground position from collision position
			if (pPedSelf->GetAreaCode() == 0)
			{
				vecGroundPos.fZ = pGameInterface->GetWorld()->FindGroundZForPosition(vecGroundPos.fX, vecGroundPos.fY);
			}
			else
			{
				CVector vecGroundPosSlightlyAbove = vecGroundPos;
				vecGroundPosSlightlyAbove.fZ += 1.0f;
				vecGroundPos.fZ = pGameInterface->GetWorld()->FindGroundZFor3DPosition(&vecGroundPosSlightlyAbove);
			}

			// setup some stuff for vehicle jumper
			if (pCollisionEntity && pCollisionEntity->nType == ENTITY_TYPE_VEHICLE)
			{
				pCVehicleTeleport = pGameInterface->GetPools()->GetVehicle((DWORD *)pCollisionEntity);
				if (pCVehicleTeleport)
				{
					const struct vehicle_entry *vehicleEntry = gta_vehicle_get_by_id(pCVehicleTeleport->GetModelIndex());
					if (vehicleEntry != nullptr)
					{
						sprintf(buf, "Warp to %s", vehicleEntry->name);
					}
				}
				else
				{
					sprintf(buf, "Distance %0.2f", vect3_dist(&vecOrigin.fX, &vecGroundPos.fX));
				}
			}
			// setup some stuff for normal warp
			else
			{
				sprintf(buf, "Distance %0.2f", vect3_dist(&vecOrigin.fX, &vecGroundPos.fX));
			}
		}
		else
		{
			iClickWarpEnabled = 0; // force disable, prevents clicks
			//toggleSAMPCursor(0);
			return;
		}
		if (pCollision != nullptr)
		{
			// destroy the collision object
			pCollision->Destroy();
		}
		if (iClickWarpEnabled)
		{
			if (pCVehicleTeleport != nullptr)
			{
				// ClickWarp to vehicle
				int iVehicleID = getVehicleGTAIDFromInterface( (DWORD*) pCVehicleTeleport->GetInterface() );
				if ( !vehicleJumper(iVehicleID) && cheat_state->state != CHEAT_STATE_VEHICLE )
				{
					// failed to jump into vehicle, warp to it instead if we're not in a vehicle

					// check for collision
					CMatrix matVehicle;
					pCVehicleTeleport->GetMatrix(&matVehicle);
					CVector vecVehicleAbove = (matVehicle.vUp * 5.0f) + *pCVehicleTeleport->GetPosition(); // up multiplier should be enough to get above most vehicles, but not enough to jump above things over it
					bool bCollision = GTAfunc_ProcessLineOfSight( &vecVehicleAbove, pCVehicleTeleport->GetPosition(), &pCollision, &pCollisionEntity,
						1, 1, 0, 1, 1, 0, 0, 0 );
					if (bCollision && pCollision)
					{
						// set pos floats for actual teleporting
						pos[0] = pCollision->GetPosition()->fX;
						pos[1] = pCollision->GetPosition()->fY;
						pos[2] = pCollision->GetPosition()->fZ + 0.5f; // should be enough so we're surfing properly
					}
					else
					{
						// set pos floats for actual teleporting
						pos[0] = vecGroundPos.fX;
						pos[1] = vecGroundPos.fY;
						pos[2] = vecGroundPos.fZ + 0.5f;
					}
					if (pCollision != nullptr)
					{
						// destroy the collision object
						pCollision->Destroy();
					}
					// teleport
					cheat_teleport(pos, gta_interior_id_get());
					GTAfunc_TogglePlayerControllable(0);
					GTAfunc_LockActor(0);
				}
			} // end ClickWarp to vehicle
			else
			{
				// ClickWarp to location
				if ( cheat_state->state == CHEAT_STATE_VEHICLE )
				{
					// check for collision
					CVehicle *vehSelf = pPedSelf->GetVehicle();
					if (vehSelf)
					{
						// check for collision
						CVector vecVehicleGravity;
						vehSelf->GetGravity(&vecVehicleGravity);
						CVector vecVehicleAbove = (-vecVehicleGravity * 5.0f) + vecGroundPos;
						CVector vecVehicleBelow = (vecVehicleGravity * 5.0f) + vecGroundPos;
						bool bCollision = GTAfunc_ProcessLineOfSight( &vecVehicleAbove, &vecVehicleBelow, &pCollision, &pCollisionEntity,
							1, 0, 0, 1, 1, 0, 0, 0 ); // not checking for vehicle collisions
						if (bCollision && pCollision)
						{
							// set vehicle to same Up position has surface normal
							CMatrix matVehicleSelf;
							vehSelf->GetMatrix(&matVehicleSelf);
							CVector vecCollisionNormal = *pCollision->GetNormal();

							// get "down" from vehicle model
							CVector rotationAxis = matVehicleSelf.vUp;

							// normalize our vectors
							vecCollisionNormal.Normalize();
							rotationAxis.Normalize();

							// axis and rotation for gravity
							float	theta = acos(rotationAxis.DotProduct(&vecCollisionNormal));
							if (!near_zero(theta))
							{
								rotationAxis.CrossProduct(&vecCollisionNormal);
								rotationAxis.Normalize();
								rotationAxis.ZeroNearZero();
								matVehicleSelf = matVehicleSelf.Rotate(&rotationAxis, -theta);
							}

							// set the new matrix
							vehSelf->SetMatrix(&matVehicleSelf);

							// set pos floats for actual teleporting
							pos[0] = pCollision->GetPosition()->fX;
							pos[1] = pCollision->GetPosition()->fY;
							pos[2] = pCollision->GetPosition()->fZ + 1.0f; // should be enough to stay above the ground properly
						}
						else
						{
							// set pos floats for actual teleporting
							pos[0] = vecGroundPos.fX;
							pos[1] = vecGroundPos.fY;
							pos[2] = vecGroundPos.fZ + 0.5f;
						}
						if (pCollision != nullptr)
						{
							// destroy the collision object
							pCollision->Destroy();
						}
					}
					else
					{
						// set pos floats for actual teleporting
						pos[0] = vecGroundPos.fX;
						pos[1] = vecGroundPos.fY;
						pos[2] = vecGroundPos.fZ + 0.5f;
					}
				}
				else
				{
					// set pos floats for actual teleporting
					pos[0] = vecGroundPos.fX;
					pos[1] = vecGroundPos.fY;
					pos[2] = vecGroundPos.fZ + 0.5f;
				}

				// teleport
				cheat_teleport(pos, gta_interior_id_get());
				GTAfunc_TogglePlayerControllable(0);
				GTAfunc_LockActor(0);
			} // end ClickWarp to location

			iClickWarpEnabled = 0;
			toggleSAMPCursor(0);
			g_iCursorEnabled = 0;
		}

		if (pCVehicleTeleport != nullptr)
		{
			D3DXVECTOR3 vehPoss, vehScreenposs;
			vehPoss.x = pCVehicleTeleport->GetPosition()->fX;
			vehPoss.y = pCVehicleTeleport->GetPosition()->fY;
			vehPoss.z = pCVehicleTeleport->GetPosition()->fZ + -1.0f;
			CalcScreenCoors( &vehPoss, &vehScreenposs );
			// print vehicle warp target name below vehicle & vehicle esp
			pD3DFontChat->PrintShadow(vehScreenposs.x, vehScreenposs.y + 10.0f, -1, buf);
		}
		else if (bCollision && pCollision)
		{
			D3DXVECTOR3 groundPoss, groundScreenposs;
			groundPoss.x = vecGroundPos.fX;
			groundPoss.y = vecGroundPos.fY;
			groundPoss.z = vecGroundPos.fZ;
			CalcScreenCoors( &groundPoss, &groundScreenposs );
			// print warp distance
			pD3DFontChat->PrintShadow(
				groundScreenposs.x - (pD3DFontChat->DrawLength(buf) / 2.0f) + 3.5f,
				groundScreenposs.y - 20.0f,
				-1, buf);
		}
	}
}

float	fYChatPosAdj = 167.0f;
void renderChat ( void )
{
	traceLastFunc( "renderChat()" );

	if ( g_Chat == NULL )
		return;

	static int	state_chatWindow = 0;
	if ( KEY_PRESSED(VK_TAB) && set.d3dtext_score )
	{
		state_chatWindow = g_Chat->iChatWindowMode;
	}

	if ( (KEY_DOWN(VK_TAB) && set.d3dtext_score)
	 ||	 (g_Scoreboard->iIsEnabled && !set.d3dtext_score) ) return;

	if ( GetAsyncKeyState(VK_F1) < 0 )
		return;
	if ( GetAsyncKeyState(VK_F5) < 0 )
		return;
	if ( GetAsyncKeyState(VK_F10) < 0 )
		return;

	static int	chat_last = -1, chat_render;

	// Patch to disable chatbox-input field positioning
	static int	patched = 0;
	if ( patched && (cheat_state->_generic.cheat_panic_enabled || !chat_render) )
	{
		patched = !sampPatchDisableChatInputAdjust( 0 );
	}
	else if ( !cheat_state->_generic.cheat_panic_enabled && chat_render )
	{
		if ( !patched )
		{
			sampPatchDisableChatInputAdjust( 1 );
			patched = 1;
		}

		// reposition the input field
		int chatInput_pos[2];
		chatInput_pos[1] = ((int)fYChatPosAdj) + 29;
		if ( chatInput_pos[1] <= 0 )
		{
			// top left corner, if above screen
			chatInput_pos[0] = 35;
			chatInput_pos[1] = 30;
		}
		else if ( chatInput_pos[1] > (int)pPresentParam.BackBufferHeight )
		{
			// middle + avoid the mouse cursor being on the text, if under screen
			chatInput_pos[0] = (pPresentParam.BackBufferWidth/2)-20;
			chatInput_pos[1] = (pPresentParam.BackBufferHeight/2)-30;
		}
		else
			chatInput_pos[0] = 35;

		// two different locations because of the way the patch is working
		g_Input->pDXUTEditBox->dwPosChatInput[0] = chatInput_pos[0];
		g_Chat->dwChatboxOffset = chatInput_pos[1];
	}
	// Input field repositioning end

	if ( cheat_state->_generic.cheat_panic_enabled )
		return;

	if ( KEY_RELEASED(VK_TAB) && set.d3dtext_score )
	{
		g_Chat->iChatWindowMode = state_chatWindow;
		chat_last = g_Chat->iChatWindowMode;
		if ( g_Chat->iChatWindowMode == 2 || g_Chat->iChatWindowMode == 1 )
		{
			chat_render = 0;
		}
		else
		{
			chat_render = 1;
		}
	}

	mmm_yummy_poop( g_Chat, &g_Chat->iChatWindowMode, &chat_last, &chat_render, "chat text" );

	if ( chat_render && !gta_menu_active() )
	{
		if ( set.d3dtext_chat_lines <= 0 )
			set.d3dtext_chat_lines = 10;
		if ( set.d3dtext_chat_lines >= 100 )
			set.d3dtext_chat_lines = 100;

		float	fYChatPos = fYChatPosAdj;

		if ( KEY_DOWN(VK_PRIOR) )
		{
			( fYChatPos ) -= 20.0f;
			fYChatPosAdj = fYChatPos;
		}
		else
		{
			fYChatPos = fYChatPosAdj;
		}

		if ( KEY_DOWN(VK_NEXT) )
		{
			( fYChatPos ) += 20.0f;
			fYChatPosAdj = fYChatPos;
		}
		else
		{
			fYChatPos = fYChatPosAdj;
		}

		// Open urls when clicking on it in the chatbox
		if ( g_Input->iInputEnabled && g_Input->pDXUTEditBox != NULL )
		{
			POINT cursor_pos;
			if ( GetCursorPos(&cursor_pos) && ScreenToClient(pPresentParam.hDeviceWindow, &cursor_pos) )
			{
				float pos_array = (float)cursor_pos.y;
				pos_array -= fYChatPos;
				pos_array /= (1.0f + pD3DFontChat->DrawHeight());
				int array_pos = 98+(int)pos_array;

				if ( array_pos >= 0 && array_pos <= 99 && g_Chat->chatEntry[array_pos].iType != NULL
					&& strlen(g_Chat->chatEntry[array_pos].szText) > 11 )
				{
					struct stChatEntry	*ent = &g_Chat->chatEntry[array_pos];
					char *pUrl = NULL;
					for ( int i = 0; pUrl == NULL && i < 4; i++ )
					{
						switch ( i )
						{
							case 0:
								pUrl = strstr( ent->szText, "http://" );
								break;
							case 1:
								pUrl = strstr( ent->szText, "https://" );
								break;
							case 2:
								pUrl = strstr( ent->szText, "ftp://" );
								break;
							case 3:
								pUrl = strstr( ent->szText, "samp://" );
								break;
						}
					}
					if ( pUrl != NULL )
					{
						float chatPos[2];

						// Filter the URL
						char url_buffer[99];
						strncpy_s( url_buffer, pUrl, sizeof(url_buffer)-1 );
						char *pUrl_End = strstr( url_buffer, " " );
						if ( pUrl_End )
							*pUrl_End = NULL;
						cheat_state_text( "URL: %s", url_buffer );

						// calculate x1 by getting the getting the length it takes until the beginning of the URL is reached
						*pUrl = NULL;
						chatPos[0] = 35.0f + pD3DFontChat->DrawLength( ent->szText );
						// restore the original first character in the url
						*pUrl = url_buffer[0];
						if ( ent->iType == 10 )
							chatPos[0] += pD3DFontChat->DrawLength( ent->szPrefix ) + pD3DFontChat->DrawLength( " " );

						// y pos
						chatPos[1] = fYChatPos + ((1.0f + pD3DFontChat->DrawHeight())*(int)pos_array);
						// Underline the URL
						render->D3DBox( chatPos[0], chatPos[1], (pD3DFontChat->DrawLength(url_buffer)), (3.0f), 0xFF0000CC );
						
						if ( GetKeyState(VK_LBUTTON) < 0 )
						{
							if ( strncmp(url_buffer, "samp://", 7) == 0 )
							{
								char *port = strstr( &url_buffer[7],":" );
								if ( port != NULL )
								{
									// 0-terminate the IP
									*port = NULL;
									port++;
									changeServer(&url_buffer[7], atoi(port), "");
								}
								else //- Try to connect to port 7777? Looks invalid though
									addMessageToChatWindow( "Port missing. Correct would be: samp://127.0.0.1:7777" );
							}
							else
								ShellExecute( NULL, "open", url_buffer, NULL, NULL, SW_SHOWNORMAL );
						}
					}
				}
			}
		}

		float	pw;
		int		i = 99;
		int		iLinesForLoop = ( i - set.d3dtext_chat_lines );
		for ( ; i > iLinesForLoop; i-- )
		{
			struct stChatEntry	*ent = &g_Chat->chatEntry[i];
			static const D3DCOLOR alpha = 0xFF000000;
			switch ( ent->iType )
			{
			case 2:
				pw = pD3DFontChat->DrawLength( ent->szPrefix ) + pD3DFontChat->DrawLength( " " );
				pD3DFontChat->PrintShadow( 35.0f, fYChatPos, ent->clPrefixColor | alpha, ent->szPrefix );
				pD3DFontChat->PrintShadow( 35.0f + pw, fYChatPos, ent->clTextColor | alpha, ent->szText );
				break;

			case 4:
			case 8:
				pD3DFontChat->PrintShadow( 35.0f, fYChatPos, ent->clTextColor | alpha, ent->szText );
				break;
			}

			fYChatPos -= 1.0f + pD3DFontChat->DrawHeight();
		}
	}
}


void renderPlayerInfo ( int iPlayerID )
{
	traceLastFunc( "renderPlayerInfo()" );

	if ( (KEY_DOWN(VK_TAB) && set.d3dtext_score)
	 ||	 (g_Scoreboard->iIsEnabled && !set.d3dtext_score) ) return;

	if ( GetAsyncKeyState(VK_F1) < 0 )
		return;
	if ( GetAsyncKeyState(VK_F5) < 0 )
		return;
	if ( GetAsyncKeyState(VK_F10) < 0 )
		return;

	if ( cheat_state->_generic.cheat_panic_enabled )
		return;

	D3DCOLOR	color = D3DCOLOR_ARGB( 0xFF, 0xFF, 0x00, 0x00 );
	float		y = 0.0f;
	( y ) += 300.0f;

	char	buf[512];

	//Localplayer
	if ( iPlayerID == -2 )
	{
		pD3DFontFixed->PrintShadow( 20.0f, y, color, "Local Player Info" );

		color = D3DCOLOR_ARGB( 0xFF, 0x99, 0x99, 0x99 );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		sprintf( buf, "Name: %s", getPlayerName(g_Players->sLocalPlayerID) );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();

		sprintf( buf, "Team ID: %u", g_Players->pLocalPlayer->byteTeamID );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		sprintf( buf, "byteCurrentInterior: %u", g_Players->pLocalPlayer->byteCurrentInterior );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();

#ifdef M0D_DEV_ADVANCEDINFO
		sprintf( buf, "iIsWasted: %i", g_Players->pLocalPlayer->iIsWasted );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		sprintf( buf, "iIsSpectating: %i", g_Players->pLocalPlayer->iIsSpectating );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		sprintf( buf, "iSpectateID: %i", g_Players->pLocalPlayer->iSpectateID );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		sprintf( buf, "byteSpectateMode: %u", g_Players->pLocalPlayer->byteSpectateMode );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		sprintf( buf, "byteSpectateType: %u", g_Players->pLocalPlayer->byteSpectateType );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		sprintf( buf, "iInitiatedSpectating: %i", g_Players->pLocalPlayer->iInitiatedSpectating );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		sprintf( buf, "iClassSelectionOnDeath: %i", g_Players->pLocalPlayer->iClassSelectionOnDeath );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
#endif
		actor_info	*self = actor_info_get( ACTOR_SELF, NULL );
		if ( self == NULL )
			return;

		vehicle_info	*vinfo = vehicle_info_get( VEHICLE_SELF, 0 );
		if ( vinfo != NULL )
		{
			pD3DFontFixed->PrintShadow( 20.0f, y, color, "Vehicle" );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			if ( vinfo->passengers[0] == actor_info_get(ACTOR_SELF, ACTOR_ALIVE) )
			{
				sprintf( buf, " Vehicle ID: %u", g_Players->pLocalPlayer->sCurrentVehicleID );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			}
		}

#ifdef M0D_DEV_ADVANCEDINFO
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		sprintf( buf, "_______ADVANCED_INFO________" );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();

		// couldnt find own vehicle & is in a vehicle = passenger drive by
		// or is in vehicle and not driver = passenger
		if ( vinfo == NULL && self->pedFlags.bInVehicle || (vinfo != NULL && vinfo->passengers[0] != self) )
		{
			sprintf( buf, "    pLocalPlayer->iPassengerDriveBy: %i", g_Players->pLocalPlayer->iPassengerDriveBy );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->passengerData.sVehicleID: %u",
					 g_Players->pLocalPlayer->passengerData.sVehicleID );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->passengerData.fPosition: %0.2f %0.2f %0.2f",
					 g_Players->pLocalPlayer->passengerData.fPosition[0],
					 g_Players->pLocalPlayer->passengerData.fPosition[1],
					 g_Players->pLocalPlayer->passengerData.fPosition[2] );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->passengerData.byteArmor: %u",
					 g_Players->pLocalPlayer->passengerData.byteArmor );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->passengerData.byteHealth: %u",
					 g_Players->pLocalPlayer->passengerData.byteHealth );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->passengerData.byteSeatID: %u",
					 g_Players->pLocalPlayer->passengerData.byteSeatID );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->passengerData.byteCurrentWeapon: %u",
					 g_Players->pLocalPlayer->passengerData.byteCurrentWeapon );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->passengerData.sKeys: %u", g_Players->pLocalPlayer->passengerData.sKeys );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		}
		else if ( vinfo != NULL )
		{
			if ( vinfo->passengers[0] == self )
			{
				sprintf( buf, "    pLocalPlayer->iIsInRCVehicle: %u", g_Players->pLocalPlayer->iIsInRCVehicle );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.sKeys: %i", g_Players->pLocalPlayer->inCarData.sKeys );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.byteArmor: %u", g_Players->pLocalPlayer->inCarData.byteArmor );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.bytePlayerHealth: %u",
						 g_Players->pLocalPlayer->inCarData.bytePlayerHealth );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.fVehicleHealth: %0.2f",
						 g_Players->pLocalPlayer->inCarData.fVehicleHealth );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.byteCurrentWeapon: %u",
						 g_Players->pLocalPlayer->inCarData.byteCurrentWeapon );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.byteLandingGearState: %u",
						 g_Players->pLocalPlayer->inCarData.byteLandingGearState );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.byteSiren: %u", g_Players->pLocalPlayer->inCarData.byteSiren );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.sVehileID: %i", g_Players->pLocalPlayer->inCarData.sVehicleID );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.sTrailerID: %i",
						 g_Players->pLocalPlayer->inCarData.sTrailerID );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.fQuaternion: %0.2f %0.2f %0.2f %0.2f",
						 g_Players->pLocalPlayer->inCarData.fQuaternion[0], g_Players->pLocalPlayer->inCarData.fQuaternion[1],
						 g_Players->pLocalPlayer->inCarData.fQuaternion[2], g_Players->pLocalPlayer->inCarData.fQuaternion[3] );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.fMoveSpeed: %0.2f %0.2f %0.2f",
						 g_Players->pLocalPlayer->inCarData.fMoveSpeed[0],
						 g_Players->pLocalPlayer->inCarData.fMoveSpeed[1],
						 g_Players->pLocalPlayer->inCarData.fMoveSpeed[2] );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->inCarData.fPosition: %0.2f %0.2f %0.2f",
						 g_Players->pLocalPlayer->inCarData.fPosition[0],
						 g_Players->pLocalPlayer->inCarData.fPosition[1],
						 g_Players->pLocalPlayer->inCarData.fPosition[2] );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				if ( g_Players->pLocalPlayer->inCarData.sTrailerID != 0 )
				{
					sprintf( buf, "    pLocalPlayer->trailerData.sTrailerID: %u",
							 g_Players->pLocalPlayer->trailerData.sTrailerID );
					pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
					( y ) += 1.0f + pD3DFontFixed->DrawHeight();
					sprintf( buf, "    pLocalPlayer->trailerData.fPosition: %0.2f %0.2f %0.2f",
							 g_Players->pLocalPlayer->trailerData.fPosition[0],
							 g_Players->pLocalPlayer->trailerData.fPosition[1],
							 g_Players->pLocalPlayer->trailerData.fPosition[2] );
					pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
					( y ) += 1.0f + pD3DFontFixed->DrawHeight();
					sprintf( buf, "    pLocalPlayer->trailerData.fQuaternion: %0.2f %0.2f %0.2f %0.2f",
							 g_Players->pLocalPlayer->trailerData.fQuaternion[0],
							 g_Players->pLocalPlayer->trailerData.fQuaternion[1],
							 g_Players->pLocalPlayer->trailerData.fQuaternion[2],
							 g_Players->pLocalPlayer->trailerData.fQuaternion[3] );
					pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
					( y ) += 1.0f + pD3DFontFixed->DrawHeight();
					pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
					( y ) += 1.0f + pD3DFontFixed->DrawHeight();
					sprintf( buf, "    pLocalPlayer->trailerData.fSpeed: %0.2f %0.2f %0.2f",
							 g_Players->pLocalPlayer->trailerData.fSpeed[0],
							 g_Players->pLocalPlayer->trailerData.fSpeed[1],
							 g_Players->pLocalPlayer->trailerData.fSpeed[2] );
					pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
					( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				}

				sprintf( buf, "    pLocalPlayer->vehicleDamageData.sVehicleID_lastDmg: %u",
						 g_Players->pLocalPlayer->vehicleDamageData.sVehicleID_lastDamageProcessed );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->vehicleDamageData.iDoorDamage: %i",
						 g_Players->pLocalPlayer->vehicleDamageData.iDoorDamage );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->vehicleDamageData.iBumperDamage: %i",
						 g_Players->pLocalPlayer->vehicleDamageData.iBumperDamage );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->vehicleDamageData.byteWheelDamage: %u",
						 g_Players->pLocalPlayer->vehicleDamageData.byteWheelDamage );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->vehicleDamageData.byteLightDamage: %i",
						 g_Players->pLocalPlayer->vehicleDamageData.byteLightDamage );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			}
		}
		else
		{
			sprintf( buf, "    pLocalPlayer->onFootData.byteArmor: %u", g_Players->pLocalPlayer->onFootData.byteArmor );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->onFootData.byteHealth: %u", g_Players->pLocalPlayer->onFootData.byteHealth );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->onFootData.byteCurrentWeapon: %u",
					 g_Players->pLocalPlayer->onFootData.byteCurrentWeapon );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->onFootData.byteSpecialAction: %u",
					 g_Players->pLocalPlayer->onFootData.byteSpecialAction );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->onFootData.sSurfingVehicleID: %i",
					 g_Players->pLocalPlayer->onFootData.sSurfingVehicleID );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();

			if ( g_Players->pLocalPlayer->onFootData.sSurfingVehicleID != 0 )
			{
				sprintf( buf, "    pLocalPlayer->surfData.iSurfMode: %i", g_Players->pLocalPlayer->surfData.iSurfMode );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->surfData.fSurfPosition: %0.2f %0.2f %0.2f",
					g_Players->pLocalPlayer->surfData.fSurfPosition[0],
					g_Players->pLocalPlayer->surfData.fSurfPosition[1],
					g_Players->pLocalPlayer->surfData.fSurfPosition[2] );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "    pLocalPlayer->onFootData.fSurfingOffsets: %0.2f %0.2f %0.2f",
					g_Players->pLocalPlayer->onFootData.fSurfingOffsets[0],
					g_Players->pLocalPlayer->onFootData.fSurfingOffsets[1],
					g_Players->pLocalPlayer->onFootData.fSurfingOffsets[2] );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			}

			sprintf( buf, "    pLocalPlayer->onFootData.fPosition: %0.2f %0.2f %0.2f",
					 g_Players->pLocalPlayer->onFootData.fPosition[0], g_Players->pLocalPlayer->onFootData.fPosition[1],
					 g_Players->pLocalPlayer->onFootData.fPosition[2] );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->onFootData.fMoveSpeed: %0.2f %0.2f %0.2f",
					 g_Players->pLocalPlayer->onFootData.fMoveSpeed[0],
					 g_Players->pLocalPlayer->onFootData.fMoveSpeed[1],
					 g_Players->pLocalPlayer->onFootData.fMoveSpeed[2] );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "    pLocalPlayer->onFootData.iCurrentAnimationID: %x",
					 g_Players->pLocalPlayer->onFootData.sCurrentAnimationID );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		}
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();

		if ( vinfo == NULL )
			return;

		/*for ( int iRow = 0; iRow < 4; iRow++ )
		{
			for ( int iCol = 0; iCol < 3; iCol++ )
			{
				sprintf( buf, " MATRIX[4*%d+%d]: %0.3f", iRow, iCol, vinfo->base.matrix[4 * iRow + iCol] );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			}
		}*/
#endif
		return;
	}

	//Remote Player
	sprintf( buf, "Infos on player %s(%d)", getPlayerName(iPlayerID), iPlayerID );
	pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
	( y ) += 1.0f + pD3DFontFixed->DrawHeight();

	if ( g_Players->pRemotePlayer[iPlayerID] != NULL )
	{
		float	position[3];
		color = samp_color_get( iPlayerID );

		sprintf( buf, "Team ID: %u", g_Players->pRemotePlayer[iPlayerID]->pPlayerData->byteTeamID );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();

		if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData == NULL
		 ||	 g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Actor == NULL )
		{
			pD3DFontFixed->PrintShadow( 20.0f, y, D3DCOLOR_XRGB(200, 0, 0), "Player is streamed out or invalid." );
			return;
		}
		else
		{
			vect3_copy( &g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[0], position );

			sprintf( buf, "Player state: %u", g_Players->pRemotePlayer[iPlayerID]->pPlayerData->bytePlayerState );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();

			sprintf( buf, "Actor health: %0.2f", g_Players->pRemotePlayer[iPlayerID]->pPlayerData->fActorHealth );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			sprintf( buf, "Actor armor: %0.2f", g_Players->pRemotePlayer[iPlayerID]->pPlayerData->fActorArmor );
			pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
			( y ) += 1.0f + pD3DFontFixed->DrawHeight();

			if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle != NULL )
			{
				vect3_copy( &g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle->base.
								matrix[4 * 3], position );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, "The player is in a vehicle" );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, " Vehicle ID: %u", g_Players->pRemotePlayer[iPlayerID]->pPlayerData->sVehicleID );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				
				if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle == NULL )
				{
#ifdef M0D_DEV
					sprintf( buf, " Something is wrong with samp vehicle struct." );
					pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
					( y ) += 1.0f + pD3DFontFixed->DrawHeight();
#endif
					return;
				}

				char	*veh_name = (char *)gta_vehicle_get_by_id( g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle->base.model_alt_id )->name;
				if ( veh_name != NULL )
				{
					sprintf( buf, " Vehicle Type: %s", veh_name );
				}

				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, " Seat ID: %u", g_Players->pRemotePlayer[iPlayerID]->pPlayerData->byteSeatID );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, " Vehicle Position: %0.2f %0.2f %0.2f",			
						 g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle->base.matrix[4 * 3],
						 g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle->base.matrix[4 * 3 + 1],
						 g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle->base.matrix[4 * 3 + 2] );			
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, " Vehicle health: %d", (int)(
							 g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->pGTA_Vehicle->hitpoints /
						 10) );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				if ( g_Players->pRemotePlayer[iPlayerID]->pPlayerData->byteSeatID == 0 )
				{
					sprintf( buf, " Vehicle Speed: %0.2f km/h", (float)(
								 vect3_length(g_Players->pRemotePlayer[iPlayerID]->pPlayerData->inCarData.fMoveSpeed) *
							 170) );
					pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
					( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				}
				else
				{
					sprintf( buf, " passengerDriveBy: %i",
							 g_Players->pRemotePlayer[iPlayerID]->pPlayerData->iPassengerDriveBy );
					pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
					( y ) += 1.0f + pD3DFontFixed->DrawHeight();

					struct actor_info	*driver = g_Players->pRemotePlayer[iPlayerID]->pPlayerData->pSAMP_Vehicle->
						pGTA_Vehicle->passengers[0];
					if ( driver != NULL )
					{
						int sampid_driver = translateGTASAMP_pedPool.iSAMPID[getPedGTAIDFromInterface( (DWORD *)driver )];
						if ( g_Players->pRemotePlayer[sampid_driver] != NULL )
						{
							sprintf( buf, " Vehicle Speed: %0.2f km/h", (float)(vect3_length(g_Players->pRemotePlayer[sampid_driver]->pPlayerData->inCarData.fMoveSpeed) * 170) );
							pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
							( y ) += 1.0f + pD3DFontFixed->DrawHeight();
							sprintf( buf, " Vehicle Driver: %s (%d)", getPlayerName(sampid_driver), sampid_driver );
							pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
							( y ) += 1.0f + pD3DFontFixed->DrawHeight();
						}
					}
				}
			}
			else
			{
				sprintf( buf, "Actor position: %0.2f, %0.2f, %0.2f",
						 g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[0],
						 g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[1],
						 g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fPosition[2] );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
				sprintf( buf, "Actor Speed: %0.2f km/h", (float)(vect3_length(g_Players->pRemotePlayer[iPlayerID]->pPlayerData->onFootData.fMoveSpeed) * 170) );
				pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
				( y ) += 1.0f + pD3DFontFixed->DrawHeight();
			}
		}

		CPed	*pPedSelf = pPools->GetPedFromRef( CPOOLS_PED_SELF_REF );
		CVector *pos_self;
		pos_self = pPedSelf->GetPosition();

		float	self_pos[3] = { pos_self->fX, pos_self->fY, pos_self->fZ };
		sprintf( buf, "Distance: %0.2f", vect3_dist(position, self_pos) );
		pD3DFontFixed->PrintShadow( 20.0f, y, color, buf );
		( y ) += 1.0f + pD3DFontFixed->DrawHeight();
	}

	return;
}

extern int	iDebuggingPlayer, iViewingInfoPlayer;

void renderSAMP ( void )
{
	traceLastFunc( "renderSAMP()" );
	
	// get samp structures
	if ( !g_renderSAMP_initSAMPstructs )
	{
		g_SAMP = stGetSampInfo();
		if ( isBadPtr_writeAny(g_SAMP, sizeof(stSAMP)) )
			return;
		
		if ( isBadPtr_writeAny(g_SAMP->pPools, sizeof(stSAMPPools)) )
			return;
		
		g_Players = g_SAMP->pPools->pPlayer;
		if ( isBadPtr_writeAny(g_Players, sizeof(stPlayerPool)) )
			return;

		g_Vehicles = g_SAMP->pPools->pVehicle;
		if ( isBadPtr_writeAny(g_Vehicles, sizeof(stVehiclePool)) )
			return;
		
		g_Chat = stGetSampChatInfo();
		if ( isBadPtr_writeAny(g_Chat, sizeof(stChatInfo)) )
			return;

		g_Input = stGetInputInfo();
		if ( isBadPtr_writeAny(g_Input, sizeof(stInputInfo)) )
			return;

		g_DeathList = stGetKillInfo();
		if ( isBadPtr_writeAny(g_DeathList, sizeof(stKillInfo)) )
			return;

		g_Scoreboard = stGetScoreboardInfo();
		if ( isBadPtr_writeAny(g_Scoreboard, sizeof(stScoreboardInfo)) )
			return;
			
		if ( g_SAMP->pRakClientInterface == NULL )
			return;
		
		// initialize raknet
		g_RakClient = new RakClient( g_SAMP->pRakClientInterface );
		g_SAMP->pRakClientInterface = new HookedRakClientInterface();
		
		// init modCommands
		if ( set.mod_commands_activated )
			initChatCmds();

		memcpy_safe((void *)0x004B35A0, (uint8_t *)"\x83\xEC\x0C\x56\x8B\xF1", 6 ); // godmode patch
		
		// 0x: Set's the Frame Sleeping to 0 so you get more performance (sa:mp init is so far a good place ;d) .
		*(BYTE*)0xBAB318 = 0;
		memset_safe((void *)0x53E94C, 0, 1);

		g_renderSAMP_initSAMPstructs = 1;
	}

	if ( g_SAMP != NULL )
	{
		setSAMPCustomSendRates( set.onfoot_sendrate, set.incar_sendrate, set.aim_sendrate, set.headsync_sendrate );

		if ( !g_SAMP->pSettings->byteShowNameTags && set.nametags_show )
			g_SAMP->pSettings->byteShowNameTags = 1;
		if ( g_SAMP->pSettings->byteNoNametagsBehindWalls && set.disable_line_of_sight )
			g_SAMP->pSettings->byteNoNametagsBehindWalls = 0;
		if ( !g_SAMP->pSettings->bytePlayerMarkersMode && set.markers_show )
			g_SAMP->pSettings->bytePlayerMarkersMode = PLAYER_MARKERS_MODE_GLOBAL;

		g_SAMP->pSettings->fNameTagsDistance = set.line_of_sight_dist;
		if ( cheat_state->_generic.pickuptexts )
			RenderPickupTexts();
		if ( cheat_state->_generic.objecttexts )
			RenderObjectTexts();
		if ( cheat_state->player_info_list )
			renderPlayerInfoList();

		renderKillList();
		renderChat();
		renderScoreList();
		renderTextLabels();
		clickWarp();

		if ( iViewingInfoPlayer != -1 )
		{
			if ( iViewingInfoPlayer != -2 && g_Players->pRemotePlayer[iViewingInfoPlayer] == NULL )
				iViewingInfoPlayer = -1;
			else
				renderPlayerInfo( iViewingInfoPlayer );
		}

		static int	a;
		if ( !a )
		{
			if ( set.player_tags_dist > set.line_of_sight_dist )
				memcpy_safe( (void *)(g_dwSAMP_Addr + SAMP_DRAWING_DISTANCE), &set.player_tags_dist, sizeof(float) );
			else
				memcpy_safe( (void *)(g_dwSAMP_Addr + SAMP_DRAWING_DISTANCE), &set.line_of_sight_dist, sizeof(float) );

			a = 1;
		}
	}
}

void mapMenuTeleport ( void )
{
	if ( set.map_must_be_open && *(byte *)0xBA68A5 != 5 )
		return;

	if ( (*(int *)0xBA6774 != 0) && GetAsyncKeyState(set.key_map_teleport) & ( 1 << 16 ) && pGameInterface != NULL )
	{
		// ty to Racer_S for this
		float	mapPos[3];
		for ( int i = 0; i < (0xAF * 0x28); i += 0x28 )
		{
			if ( *(short *)(0xBA873D + i) == 4611 )
			{
				float	*pos = (float *)( 0xBA86F8 + 0x28 + i );
				gta_interior_id_set( 0 );
				mapPos[0] = *pos;
				mapPos[1] = *( pos + 1 );
				mapPos[2] = pGameInterface->GetWorld()->FindGroundZForPosition( mapPos[0], mapPos[1] ) + 2.0f;
				cheat_teleport( mapPos, 0 );
			}
		}
	}
}

void texturesInitResources ( IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *pPresentationParameters )
{
	if ( set.speedometer_enable
	 &&	 (
			 fopen(set.speedometer_speedo_png_filename, "rb") == NULL
	 ||	 fopen(set.speedometer_needle_png_filename, "rb") == NULL
	 ) )
	{
		Log( "Could not find the speedometer files, disabling it." );
		set.speedometer_enable = false;
		set.speedometer_old_enable = true;
	}
	else if ( set.speedometer_enable )
	{
		// init speedo
		tSpeedoPNG = NULL;
		sSpeedoPNG = NULL;
		tNeedlePNG = NULL;
		sNeedlePNG = NULL;
		if ( !tSpeedoPNG )
			D3DXCreateTextureFromFile( pDevice, set.speedometer_speedo_png_filename, &tSpeedoPNG );
		if ( !sSpeedoPNG )
			D3DXCreateSprite( pDevice, &sSpeedoPNG );
		if ( !tNeedlePNG )
			D3DXCreateTextureFromFile( pDevice, set.speedometer_needle_png_filename, &tNeedlePNG );
		if ( !sNeedlePNG )
			D3DXCreateSprite( pDevice, &sNeedlePNG );
		needlePos.x = ( pPresentationParameters->BackBufferWidth / 1024.0f );
		needlePos.y = ( pPresentationParameters->BackBufferHeight / 768.0f );
		speedoPos.x = ( 750.0f * needlePos.x );
		speedoPos.y = pPresentationParameters->BackBufferHeight - ( 292.0f * needlePos.y );
	}
	
	// ret
}

float		fpsDisplay, fpsBuf1, fpsBuf2, fpsBuf3, fpsBuf4;
uint32_t	fps_time = GetTickCount();
int			fpsFrameCounter;
float getFPS ( void )
{
	// increment frame counter
	fpsFrameCounter++;

	// get fps
	if ( (GetTickCount() - 240) > fps_time )
	{
		// for averaging
		fpsBuf4 = fpsBuf3;
		fpsBuf3 = fpsBuf2;
		fpsBuf2 = fpsBuf1;

		// set new FPS
		fpsBuf1 = ( fpsFrameCounter * 4 );
		fpsDisplay = ( fpsBuf1 + fpsBuf2 + fpsBuf3 + fpsBuf4 ) / 4.0;

		// reset counter
		fpsFrameCounter = 0;

		// reset tick
		fps_time = GetTickCount();
	}

	return fpsDisplay;
}

void proxyID3DDevice9_UnInitOurShit ( void )
{
	traceLastFunc( "proxyID3DDevice9_UnInitOurShit()" );

	// fonts
	pD3DFont->Invalidate();
	pD3DFontFixed->Invalidate();
	pD3DFontFixedSmall->Invalidate();
	pD3DFontChat->Invalidate();
	pD3DFont_sampStuff->Invalidate();
	pD3DFontDebugWnd->Invalidate();

	SAFE_RELEASE( chams_green );
	SAFE_RELEASE( chams_blue );
	SAFE_RELEASE( chams_red );

	if ( set.speedometer_enable )
	{
		SAFE_RELEASE( sSpeedoPNG );
		SAFE_RELEASE( tSpeedoPNG );
		SAFE_RELEASE( sNeedlePNG );
		SAFE_RELEASE( tNeedlePNG );
	}
	
	// death texture
	SAFE_RELEASE( pSpriteTexture );

	// the main render class
	render->Invalidate();

	// supposedly this worked so set init state
	// this should probably actually check eventually
	static int	proxyIDirect3DDevice9_init = 0;
	bD3DRenderInit = false;
}

void proxyID3DDevice9_InitOurShit ( D3DPRESENT_PARAMETERS *pPresentationParameters )
{
	traceLastFunc( "proxyID3DDevice9_InitOurShit()" );

	// orig device has been reset, let's re-init
	render->Initialize( origIDirect3DDevice9 );

	// load fonts
	pD3DFont->Initialize( origIDirect3DDevice9 );
	pD3DFontFixed->Initialize( origIDirect3DDevice9 );
	pD3DFontFixedSmall->Initialize( origIDirect3DDevice9 );
	pD3DFontChat->Initialize( origIDirect3DDevice9 );
	pD3DFont_sampStuff->Initialize( origIDirect3DDevice9 );
	pD3DFontDebugWnd->Initialize( origIDirect3DDevice9 );

	// load shaders
	GenerateShader( origIDirect3DDevice9, &chams_green, 0.8f, 0, 1.0f, 0 );
	GenerateShader( origIDirect3DDevice9, &chams_blue, 0.8f, 0, 0, 1.0f );
	GenerateShader( origIDirect3DDevice9, &chams_red, 0.8f, 1.0f, 0, 0 );

	// load GUI textures/sprits
	texturesInitResources( origIDirect3DDevice9, pPresentationParameters );

	// load death texture
	LoadSpriteTexture();
	
	// supposedly this worked so set init state
	// this should probably actually check eventually
	bD3DRenderInit = true;
}

// window/fullscreen init/update
bool	g_InitWindowMode_ForceUpdate_Active = false;
void proxyID3DDevice9_InitWindowMode ( D3DPRESENT_PARAMETERS *pPresentationParameters )
{
	traceLastFunc( "proxyID3DDevice9_InitWindowMode()" );

	// window mode toggle, flips set.window_mode bit
	if ( g_isRequestingWindowModeToggle )
	{
		g_isRequestingWindowModeToggle = false;
		set.window_mode ^= 1;
	}

	// m_ForceChange settings
	bool	m_ForceUpdate;

	// set to force the desired video mode if needed
	if ( set.window_mode != pPresentationParameters->Windowed || set.window_mode != g_pGTAPresent->Windowed )
	{
		// we need to force an update
		m_ForceUpdate = true;
	}

	// we do not want basic presentation parameters anymore
	/*g_pGTAPresent->Flags = 0;
	g_pGTAPresent->PresentationInterval = 0;
	pPresentationParameters->Flags = 0;
	pPresentationParameters->PresentationInterval = 0;*/

	// get the current video mode & the correct back buffer size
	int			m_dwVideoMode = g_pCSettingsSAInterface->dwVideoMode;
	VideoMode	m_currentVideoMode;
	GTAfunc_getVideoModeInfo( &m_currentVideoMode, m_dwVideoMode );

	int presentWidth = m_currentVideoMode.width;
	int presentHeight = m_currentVideoMode.height;

	// set windowed or fullscreen
	if ( g_isRequesting_RwD3D9ChangeVideoMode && m_ForceUpdate && !g_InitWindowMode_ForceUpdate_Active )
	{
		g_isRequesting_RwD3D9ChangeVideoMode = false;
		g_InitWindowMode_ForceUpdate_Active = true;
		if ( set.window_mode )
		{
			// set to windowed
			if ( GTAfunc_RwD3D9ChangeVideoMode(0) != 1 )
			{
				Log( "proxyID3DDevice9_InitWindowMode() failed to GTAfunc_RwD3D9ChangeVideoMode(0) #1" );
				g_InitWindowMode_ForceUpdate_Active = false;
				return;
			}
			else
			{
				*(int *)0xC920CC = 1;	// _?windowed
				g_RsGlobal->ps->fullscreen = 0;
				if ( isBadPtr_writeAny(g_pGTAPresent, sizeof(D3DPRESENT_PARAMETERS)) )
				{
					Log( "proxyID3DDevice9_InitWindowMode() g_pGTAPresent pointer bad. Continuing anyways." );
				}
				else
				{
					g_pGTAPresent->Windowed = 1;
					g_pGTAPresent->FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
					g_pGTAPresent->BackBufferWidth = presentWidth;
					g_pGTAPresent->BackBufferHeight = presentHeight;
				}

				if ( isBadPtr_writeAny(pPresentationParameters, sizeof(D3DPRESENT_PARAMETERS)) )
				{
					Log( "proxyID3DDevice9_InitWindowMode() pPresentationParameters pointer bad. Continuing anyways." );
				}
				else
				{
					pPresentationParameters->Windowed = 1;
					pPresentationParameters->FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
					pPresentationParameters->BackBufferWidth = presentWidth;
					pPresentationParameters->BackBufferHeight = presentHeight;
				}

				if ( GTAfunc_RwD3D9ChangeVideoMode(0) != 1 )
				{
					Log( "proxyID3DDevice9_InitWindowMode() failed to GTAfunc_RwD3D9ChangeVideoMode(0) #2" );
					g_InitWindowMode_ForceUpdate_Active = false;
					return;
				}

				//GTAfunc_setCurrentVideoMode(0);
			}
		}
		else if ( !set.window_mode )
		{
			// set to fullscreen
			if ( GTAfunc_RwD3D9ChangeVideoMode(0) != 1 )
			{
				Log( "proxyID3DDevice9_InitWindowMode() failed to GTAfunc_RwD3D9ChangeVideoMode(0) #3" );
				g_InitWindowMode_ForceUpdate_Active = false;
				return;
			}
			else
			{
				*(int *)0xC920CC = 0;	// _?windowed
				g_RsGlobal->ps->fullscreen = 1;
				if ( isBadPtr_writeAny(g_pGTAPresent, sizeof(D3DPRESENT_PARAMETERS)) )
				{
					Log( "proxyID3DDevice9_InitWindowMode() g_pGTAPresent pointer bad. Continuing anyways." );
				}
				else
				{
					g_pGTAPresent->Windowed = 0;
					g_pGTAPresent->FullScreen_RefreshRateInHz = ulFullScreenRefreshRate;
					g_pGTAPresent->BackBufferWidth = presentWidth;
					g_pGTAPresent->BackBufferHeight = presentHeight;
				}

				if ( isBadPtr_writeAny(pPresentationParameters, sizeof(D3DPRESENT_PARAMETERS)) )
				{
					Log( "proxyID3DDevice9_InitWindowMode() pPresentationParameters pointer bad. Continuing anyways." );
				}
				else
				{
					pPresentationParameters->Windowed = 0;
					pPresentationParameters->FullScreen_RefreshRateInHz = ulFullScreenRefreshRate;
					pPresentationParameters->BackBufferWidth = presentWidth;
					pPresentationParameters->BackBufferHeight = presentHeight;
				}

				if ( GTAfunc_RwD3D9ChangeVideoMode(m_dwVideoMode) != 1 )
				{
					Log( "proxyID3DDevice9_InitWindowMode() failed to GTAfunc_RwD3D9ChangeVideoMode(m_dwVideoMode) #1, m_dwVideoMode=%d",
					 m_dwVideoMode );
					g_InitWindowMode_ForceUpdate_Active = false;
					return;
				}

				//GTAfunc_setCurrentVideoMode(m_dwVideoMode);
			}
		}

		g_InitWindowMode_ForceUpdate_Active = false;
	}
	else if ( m_ForceUpdate && set.window_mode && !g_InitWindowMode_ForceUpdate_Active )
	{
		g_InitWindowMode_ForceUpdate_Active = true;
		*(int *)0xC920CC = 1;			// _?windowed
		g_RsGlobal->ps->fullscreen = 0;
		if ( isBadPtr_writeAny(g_pGTAPresent, sizeof(D3DPRESENT_PARAMETERS)) )
		{
			Log( "proxyID3DDevice9_InitWindowMode() g_pGTAPresent pointer bad. Continuing anyways." );
		}
		else
		{
			g_pGTAPresent->Windowed = 1;
			g_pGTAPresent->FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			g_pGTAPresent->BackBufferWidth = presentWidth;
			g_pGTAPresent->BackBufferHeight = presentHeight;
		}

		if ( isBadPtr_writeAny(pPresentationParameters, sizeof(D3DPRESENT_PARAMETERS)) )
		{
			Log( "proxyID3DDevice9_InitWindowMode() pPresentationParameters pointer bad. Continuing anyways." );
		}
		else
		{
			pPresentationParameters->Windowed = 1;
			pPresentationParameters->FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
			pPresentationParameters->BackBufferWidth = presentWidth;
			pPresentationParameters->BackBufferHeight = presentHeight;
		}

		g_InitWindowMode_ForceUpdate_Active = false;
	}

	// window mode stuff
	if ( set.window_mode
	 &&	 pPresentationParameters->BackBufferWidth != 0
	 &&	 pPresentationParameters->BackBufferHeight != 0 )
	{
		// title bar or not?
		if ( set.window_mode_titlebar )
		{
			RECT	um;		// damn near killed um

			// add caption bar, etc
			SetWindowLong( pPresentationParameters->hDeviceWindow, GWL_STYLE,
						   WS_POPUP | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_VISIBLE );

			// update caption bar, etc
			SetWindowPos( pPresentationParameters->hDeviceWindow, HWND_NOTOPMOST, 0, 0, 0, 0,
						  SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOMOVE );

			// the client area of the window must be the same size as the back buffer
			GetClientRect( pPresentationParameters->hDeviceWindow, &um );
			if ( um.right == pPresentationParameters->BackBufferWidth
			 &&	 um.bottom == pPresentationParameters->BackBufferHeight ) goto proxyID3DDevice9_InitWindowMode_end;
			SetWindowPos( pPresentationParameters->hDeviceWindow, HWND_NOTOPMOST, 0, 0,
						  pPresentationParameters->BackBufferWidth + (pPresentationParameters->BackBufferWidth - um.right),
							  pPresentationParameters->BackBufferHeight + (pPresentationParameters->BackBufferHeight - um.bottom),
								  SWP_FRAMECHANGED | SWP_SHOWWINDOW | SWP_NOMOVE );
			if ( pool_actor != NULL )
			{
				int x, y;
				x = GetSystemMetrics( SM_CXSCREEN );
				y = GetSystemMetrics( SM_CYSCREEN );
				SetWindowPos( pPresentationParameters->hDeviceWindow, HWND_NOTOPMOST,
							  (x / 2) - (pPresentationParameters->BackBufferWidth / 2),
							  (y / 2) - (pPresentationParameters->BackBufferHeight / 2),
							  pPresentationParameters->BackBufferWidth + (pPresentationParameters->BackBufferWidth - um.right),
						  pPresentationParameters->BackBufferHeight +
								  (pPresentationParameters->BackBufferHeight - um.bottom), SWP_SHOWWINDOW );
			}
		}
		else
		{
			// center the window
			SetWindowPos( pPresentationParameters->hDeviceWindow, HWND_NOTOPMOST, 0, 0, 0, 0,
						  SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE );
		}
	}

proxyID3DDevice9_InitWindowMode_end: ;
	// always make sure our window_mode is synced with the game's
	set.window_mode = ( g_RsGlobal->ps->fullscreen == 0 );
}

void renderHandler()
{
	traceLastFunc( "renderHandler()" );

	// set FPS limit for vsync mode
	*(int*)0xC1704C = set.fps_limit;

	// we should already be initialized, but what the hell why not
	while ( !bD3DRenderInit )
		proxyID3DDevice9_InitOurShit( &pPresentParam );

	// init death type textures and HUD colors
	static int	proxyIDirect3DDevice9_init = 0;
	if ( !proxyIDirect3DDevice9_init )
	{
		LoadSpriteTexture();

		*(uint8_t *)0xBAB22C = gta_hp_bar->red;
		*(uint8_t *)0xBAB22D = gta_hp_bar->green;
		*(uint8_t *)0xBAB22E = gta_hp_bar->blue;
		*(uint8_t *)0xBAB22F = gta_hp_bar->alpha;

		*(uint8_t *)0xBAB230 = gta_money_hud->red;
		*(uint8_t *)0xBAB231 = gta_money_hud->green;
		*(uint8_t *)0xBAB232 = gta_money_hud->blue;
		*(uint8_t *)0xBAB233 = gta_money_hud->alpha;
		
		proxyIDirect3DDevice9_init = 1;
	}

	// setup render class now for doing stuff within cheat_hook
	bool	isBeginRenderWIN = SUCCEEDED( render->BeginRender() );

	// run all dem hacks
	cheat_hook( pPresentParam.hDeviceWindow );

#define HUD_TEXT( x, color, text ) \
	pD3DFont->PrintShadow( 1.0f + (x), (float)(pPresentParam.BackBufferHeight) - pD3DFont->DrawHeight() - 3, (color), \
						   (text) ); \
	( x ) += pD3DFont->DrawLength( text );

#define HUD_TEXT_TGL( x, color, text ) \
	HUD_TEXT( x, color_text, "[" ); \
	HUD_TEXT( x, color, text ); \
	HUD_TEXT( x, color_text, "] " )

	char		buf[256];
	float		x = 0.0f;

	uint32_t	color_text = D3DCOLOR_ARGB( 191, 255, 255, 255 );
	uint32_t	color_enabled = D3DCOLOR_ARGB( 191, 63, 255, 63 );
	uint32_t	color_disabled = D3DCOLOR_ARGB( 191, 255, 255, 255 );

	if ( isBeginRenderWIN )
	{
		static int	game_inited;

		if ( set.d3dtext_hud )
		{
			if ( cheat_panic() || cheat_state->state == CHEAT_STATE_NONE )
			{
				if ( set.flickering_problem )
					goto no_render;

				if( !set.flickering_problem )
				{
					if ( iIsSAMPSupported )
					{
						uint32_t	bar_color = D3DCOLOR_ARGB( hud_bar->alpha, hud_bar->red, hud_bar->green,
															   hud_bar->blue );
						render->D3DBoxi( (int)x - 1,
										 (int)(pPresentParam.BackBufferHeight - 1) - (int)pD3DFont->DrawHeight() - 3,
										 (int)(pPresentParam.BackBufferWidth + 14), 22, bar_color, NULL );

						_snprintf_s( buf, sizeof(buf)-1, "%s for %s", NAME, g_szSAMPVer );
						HUD_TEXT( x, D3DCOLOR_ARGB(127, 255, 255, 255), buf );
					}
					else
					{
						uint32_t	bar_color = D3DCOLOR_ARGB( hud_bar->alpha, hud_bar->red, hud_bar->green,
															   hud_bar->blue );
						render->D3DBoxi( (int)x - 1,
										 (int)(pPresentParam.BackBufferHeight - 1) - (int)pD3DFont->DrawHeight() - 3,
										 (int)(pPresentParam.BackBufferWidth + 14), 22, bar_color, NULL );
						HUD_TEXT( x, D3DCOLOR_ARGB(127, 255, 255, 255), NAME );
					}
				}

				// startup logo was here, but damn it works better without it
				// we should figure out why that is some time
			}
			else
			{

				if ( !game_inited )
				{
					game_inited = 1;
					goto no_render;
				}

				if ( set.flickering_problem )
					if ( gta_menu_active() )
						goto no_render;

				if ( set.left_bottom_bars_enable )
					( x ) += 102.f;

				if ( set.hud_draw_bar )
				{
					uint32_t	bar_color = D3DCOLOR_ARGB( hud_bar->alpha, hud_bar->red, hud_bar->green, hud_bar->blue );

					render->D3DBoxi( (int)x - 1, (int)(pPresentParam.BackBufferHeight - 1) - (int)pD3DFont->DrawHeight() - 3,
									 (int)(pPresentParam.BackBufferWidth + 14), 22, bar_color, NULL );
				}

				if ( set.hud_indicator_inv )
				{
					HUD_TEXT_TGL( x, cheat_state->_generic.hp_cheat ? color_enabled : color_disabled, "Inv" );
				}

				if ( set.hud_indicator_weapon )
				{
					HUD_TEXT_TGL( x, cheat_state->_generic.weapon ? color_enabled : color_disabled, "Weapon" );
				}

				if ( set.hud_indicator_money )
				{
					HUD_TEXT_TGL( x, cheat_state->_generic.money ? color_enabled : color_disabled, "Money" );
				}

				if ( set.hud_indicator_freeze )
				{
					HUD_TEXT_TGL( x, cheat_state->_generic.vehicles_freeze ? color_enabled : color_disabled, "Freeze" );
				}

				if ( set.hud_fps_draw )
				{
					float		m_FPS = getFPS();
					int			m_FPS_int = (int)m_FPS;
					uint32_t	color_fps = D3DCOLOR_XRGB( 200, 200, 0 );
					if ( m_FPS_int >= 23 )
						color_fps = D3DCOLOR_XRGB( 0, 200, 0 );
					else if ( m_FPS_int >= 13 && m_FPS_int <= 22 )
						color_fps = D3DCOLOR_XRGB( 200, 200, 0 );
					else if ( m_FPS_int <= 12 )
						color_fps = D3DCOLOR_XRGB( 200, 0, 0 );
					if ( pGameInterface && pGameInterface->GetSettings()->IsFrameLimiterEnabled() )
					{
						_snprintf_s( buf, sizeof(buf)-1, "%0.0f (%d)", m_FPS, *(int *)0xC1704C );
					}
					else
					{
						_snprintf_s( buf, sizeof(buf)-1, "%0.0f", m_FPS );
					}

					pD3DFont->PrintShadow( pPresentParam.BackBufferWidth - pD3DFont->DrawLength(buf) - 2,
										   pPresentParam.BackBufferHeight - pD3DFont->DrawHeight() - 2, color_fps, buf );
				}
			}

			if ( cheat_state->state == CHEAT_STATE_VEHICLE )
			{
				if ( set.hud_indicator_inveh_airbrk )
				{
					HUD_TEXT_TGL( x, cheat_state->vehicle.air_brake ? color_enabled : color_disabled, "AirBrk" );
				}

				if ( set.hud_indicator_inveh_stick )
				{
					HUD_TEXT_TGL( x, cheat_state->vehicle.stick ? color_enabled : color_disabled, "Stick" );
				}

				if ( set.hud_indicator_inveh_brkdance )
				{
					HUD_TEXT_TGL( x, cheat_state->vehicle.brkdance ? color_enabled : color_disabled, "BrkDance" );
				}

				if ( set.hud_indicator_inveh_spider )
				{
					HUD_TEXT_TGL( x, cheat_state->vehicle.spiderWheels_on ? color_enabled : color_disabled, "Spider" );
				}

				if ( set.hud_indicator_inveh_fly )
				{
					HUD_TEXT_TGL( x, cheat_state->vehicle.fly ? color_enabled : color_disabled, "Fly" );
				}

				if ( set.hud_indicator_freezerot )
				{
					HUD_TEXT_TGL( x, cheat_state->vehicle.freezerot ? color_enabled : color_disabled, "FreezeRot" );
				}

				RenderVehicleHPBar();
			}
			else if ( cheat_state->state == CHEAT_STATE_ACTOR )
			{
				if ( set.hud_indicator_onfoot_airbrk )
				{
					HUD_TEXT_TGL( x, cheat_state->actor.air_brake ? color_enabled : color_disabled, "AirBrk" );
				}

				if ( set.hud_indicator_onfoot_stick )
				{
					HUD_TEXT_TGL( x, cheat_state->actor.stick ? color_enabled : color_disabled, "Stick" );
				}

				if ( set.hud_indicator_onfoot_aim )
				{
					HUD_TEXT_TGL( x, cheat_state->actor.autoaim ? color_enabled : color_disabled, "Aim" );
				}

				if ( set.hud_indicator_onfoot_fly )
				{
					HUD_TEXT_TGL( x, cheat_state->actor.fly_on ? color_enabled : color_disabled, "Fly" );
				}

				if (set.hud_indicator_surf)
				{
					HUD_TEXT_TGL( x, cheat_state->actor.surf ? color_enabled : color_disabled, "Surf" );
				}

				RenderPedHPBar();
			} // end CHEAT_STATE_ACTOR

			if ( cheat_state->state != CHEAT_STATE_NONE )
			{
				if ( set.hud_indicator_pos )
				{
					float	*coord =
						( cheat_state->state == CHEAT_STATE_VEHICLE )
							? cheat_state->vehicle.coords : cheat_state->actor.coords;

					_snprintf_s( buf, sizeof(buf)-1, "  %.2f, %.2f, %.2f  %d", coord[0], coord[1], coord[2],
								 gta_interior_id_get() );
					HUD_TEXT( x, color_text, buf );
				}
			}				// end != CHEAT_STATE_NONE

			if ( cheat_state->text_time > 0 && time_get() - cheat_state->text_time < MSEC_TO_TIME(3000) )
			{
				uint32_t	color, alpha = 255;

				if ( time_get() - cheat_state->text_time > MSEC_TO_TIME(2000) )
					alpha -= ( time_get() - cheat_state->text_time - MSEC_TO_TIME(2000) ) * 255 / MSEC_TO_TIME( 1000 );

				color = D3DCOLOR_ARGB( alpha, 255, 255, 255 );

				_snprintf_s( buf, sizeof(buf)-1, "%s <-", cheat_state->text );
				pD3DFont->PrintShadow( pPresentParam.BackBufferWidth - pD3DFont->DrawLength(buf) - 3.0f, 1,
									   D3DCOLOR_ARGB(alpha, 255, 255, 255), buf );
			}
		}

		renderSAMP();	// sure why not
		renderPlayerTags();

		if ( cheat_state->_generic.teletext )
			RenderTeleportTexts();
		if ( cheat_state->debug_enabled )
			RenderDebug();
		if ( cheat_state->render_vehicle_tags )
			renderVehicleTags();
		if ( cheat_state->_generic.map )
			RenderMap();

		// render menu
		if ( cheat_state->_generic.menu )
			RenderMenu();


no_render: ;
		render->EndRender();
	}

	mapMenuTeleport();

	traceLastFunc( "it_wasnt_us()" );
}

///////////////////////////////////////////////////////////////////////////////
// End of common D3D functions.
///////////////////////////////////////////////////////////////////////////////

proxyIDirect3DDevice9::proxyIDirect3DDevice9 ( IDirect3DDevice9 *pOriginal )
{
	//Log("proxyIDirect3DDevice9 constructor called. Original IDirect3DDevice9 interface address is 0x%p", pOriginal);
	origIDirect3DDevice9 = pOriginal;
	bD3DRenderInit = false;
}

proxyIDirect3DDevice9::~proxyIDirect3DDevice9 ( void )
{
	Log( "proxyIDirect3DDevice9 destructor called." );
}

HRESULT proxyIDirect3DDevice9::QueryInterface ( REFIID riid, void **ppvObj )
{
	HRESULT hRes;

	*ppvObj = NULL;
	hRes = origIDirect3DDevice9->QueryInterface( riid, ppvObj );
	if ( hRes == NOERROR )
		*ppvObj = this;

	return hRes;
}

ULONG proxyIDirect3DDevice9::AddRef ( void )
{
	return origIDirect3DDevice9->AddRef();
}

ULONG proxyIDirect3DDevice9::Release ( void )
{
	ULONG	count = origIDirect3DDevice9->Release();

	if ( count == 0 )
	{
		delete( this );
	}

	return count;
}

HRESULT proxyIDirect3DDevice9::TestCooperativeLevel ( void )
{
	return origIDirect3DDevice9->TestCooperativeLevel();
}

UINT proxyIDirect3DDevice9::GetAvailableTextureMem ( void )
{
	return origIDirect3DDevice9->GetAvailableTextureMem();
}

HRESULT proxyIDirect3DDevice9::EvictManagedResources ( void )
{
	return origIDirect3DDevice9->EvictManagedResources();
}

HRESULT proxyIDirect3DDevice9::GetDirect3D ( IDirect3D9 **ppD3D9 )
{
	return origIDirect3DDevice9->GetDirect3D( ppD3D9 );
}

HRESULT proxyIDirect3DDevice9::GetDeviceCaps ( D3DCAPS9 *pCaps )
{
	return origIDirect3DDevice9->GetDeviceCaps( pCaps );
}

HRESULT proxyIDirect3DDevice9::GetDisplayMode ( UINT iSwapChain, D3DDISPLAYMODE *pMode )
{
	return origIDirect3DDevice9->GetDisplayMode( iSwapChain, pMode );
}

HRESULT proxyIDirect3DDevice9::GetCreationParameters ( D3DDEVICE_CREATION_PARAMETERS *pParameters )
{
	return origIDirect3DDevice9->GetCreationParameters( pParameters );
}

HRESULT proxyIDirect3DDevice9::SetCursorProperties ( UINT XHotSpot, UINT YHotSpot, IDirect3DSurface9 *pCursorBitmap )
{
	return origIDirect3DDevice9->SetCursorProperties( XHotSpot, YHotSpot, pCursorBitmap );
}

void proxyIDirect3DDevice9::SetCursorPosition ( int X, int Y, DWORD Flags )
{
	origIDirect3DDevice9->SetCursorPosition( X, Y, Flags );
}

BOOL proxyIDirect3DDevice9::ShowCursor ( BOOL bShow )
{
	return origIDirect3DDevice9->ShowCursor( bShow );
}

HRESULT proxyIDirect3DDevice9::CreateAdditionalSwapChain ( D3DPRESENT_PARAMETERS *pPresentationParameters,
														   IDirect3DSwapChain9 **pSwapChain )
{
	return origIDirect3DDevice9->CreateAdditionalSwapChain( pPresentationParameters, pSwapChain );
}

HRESULT proxyIDirect3DDevice9::GetSwapChain ( UINT iSwapChain, IDirect3DSwapChain9 **pSwapChain )
{
	return origIDirect3DDevice9->GetSwapChain( iSwapChain, pSwapChain );
}

UINT proxyIDirect3DDevice9::GetNumberOfSwapChains ( void )
{
	return origIDirect3DDevice9->GetNumberOfSwapChains();
}

HRESULT proxyIDirect3DDevice9::Reset ( D3DPRESENT_PARAMETERS *pPresentationParameters )
{
	traceLastFunc( "proxyIDirect3DDevice9::Reset()" );

	// new PROPER reset code
	//
	// return for the reset
	HRESULT hRes_orig_Reset;

	// this should always be done if a reset is requested
	// and we have assets initialized on the proxy device
	while ( bD3DRenderInit )
		proxyID3DDevice9_UnInitOurShit();

	// always attempt to reset orig device if we are asked to
	// since GTA is getting the state of the original device
	hRes_orig_Reset = origIDirect3DDevice9->Reset( pPresentationParameters );

	// handle the return from original Reset()
	if ( hRes_orig_Reset == D3D_OK )
	{
		// variable for checking the pointers
		short	badPointerCount_g_pGTAPresent = 0;
		bool	badPointerBreak_g_pGTAPresent = false;
		short	badPointerCount_pPresentationParameters = 0;
		bool	badPointerBreak_pPresentationParameters = false;
		while ( isBadPtr_writeAny(g_pGTAPresent, sizeof(D3DPRESENT_PARAMETERS)) && !badPointerBreak_g_pGTAPresent )
		{
			badPointerCount_g_pGTAPresent++;
			if ( badPointerCount_g_pGTAPresent < 50 )
			{
				Sleep( 100 );
			}
			else
			{
				Log( "During D3D9 Reset(), g_pGTAPresent was bad for over 5 seconds. Continuing anyways." );
				badPointerBreak_g_pGTAPresent = true;
			}
		}

		while
		(
			isBadPtr_writeAny(pPresentationParameters, sizeof(D3DPRESENT_PARAMETERS))
			&& !badPointerBreak_pPresentationParameters
		)
		{
			badPointerCount_pPresentationParameters++;
			if ( badPointerCount_pPresentationParameters < 50 )
			{
				Sleep( 100 );
			}
			else
			{
				Log( "During D3D9 Reset(), pPresentationParameters was bad for over 5 seconds. Continuing anyways." );
				badPointerBreak_pPresentationParameters = true;
			}
		}

		// init our shit
		while ( !bD3DRenderInit )
		{
			proxyID3DDevice9_InitOurShit( pPresentationParameters );
			if ( !bD3DRenderInit )
				Sleep( 100 );
		}

		// init our window mode
		proxyID3DDevice9_InitWindowMode( pPresentationParameters );

		// update the global Present Param struct AFTER original reset, only if it's ok
		pPresentParam = *pPresentationParameters;

		// Update our data.
		pD3DData->StoreViewport( 0, 0, pPresentationParameters->BackBufferWidth,
								 pPresentationParameters->BackBufferHeight );
	}

	// reporting problems is about all we can do here.
	// we would normally just end the application gracefully right
	// now, but GTA should be handling this on its own, so whatever.
	else if ( hRes_orig_Reset == D3DERR_DEVICELOST )
	{
		Log( "origIDirect3DDevice9::Reset() returned D3DERR_DEVICELOST" );
	}
	else if ( hRes_orig_Reset == D3DERR_DRIVERINTERNALERROR )
	{
		Log( "WTF: origIDirect3DDevice9::Reset() returned D3DERR_DRIVERINTERNALERROR" );
	}
	else if ( hRes_orig_Reset == D3DERR_OUTOFVIDEOMEMORY )
	{
		Log( "WTF: origIDirect3DDevice9::Reset() returned D3DERR_OUTOFVIDEOMEMORY" );
	}
	else
	{
		Log( "WTF: origIDirect3DDevice9::Reset() returned value %d", hRes_orig_Reset );
	}

	// bai
	return hRes_orig_Reset;
}

HRESULT proxyIDirect3DDevice9::Present ( CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride,
										 CONST RGNDATA *pDirtyRegion )
{
	traceLastFunc( "proxyIDirect3DDevice9::Present()" );

	renderHandler();

	// A fog flicker fix for some ATI cards
	// this is screwing up right not for some reason
	// check out the other pD3DData references for an idea of what this does
	//
	//D3DMATRIX projMatrix;
	//pD3DData->GetTransform ( D3DTS_PROJECTION, &projMatrix );
	//origIDirect3DDevice9->SetTransform ( D3DTS_PROJECTION, &projMatrix );

	// get original function to return
	return origIDirect3DDevice9->Present( pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion );
}

HRESULT proxyIDirect3DDevice9::GetBackBuffer ( UINT iSwapChain, UINT iBackBuffer, D3DBACKBUFFER_TYPE Type,
											   IDirect3DSurface9 **ppBackBuffer )
{
	return origIDirect3DDevice9->GetBackBuffer( iSwapChain, iBackBuffer, Type, ppBackBuffer );
}

HRESULT proxyIDirect3DDevice9::GetRasterStatus ( UINT iSwapChain, D3DRASTER_STATUS *pRasterStatus )
{
	return origIDirect3DDevice9->GetRasterStatus( iSwapChain, pRasterStatus );
}

HRESULT proxyIDirect3DDevice9::SetDialogBoxMode ( BOOL bEnableDialogs )
{
	return origIDirect3DDevice9->SetDialogBoxMode( bEnableDialogs );
}

void proxyIDirect3DDevice9::SetGammaRamp ( UINT iSwapChain, DWORD Flags, CONST D3DGAMMARAMP *pRamp )
{
	origIDirect3DDevice9->SetGammaRamp( iSwapChain, Flags, pRamp );
}

void proxyIDirect3DDevice9::GetGammaRamp ( UINT iSwapChain, D3DGAMMARAMP *pRamp )
{
	origIDirect3DDevice9->GetGammaRamp( iSwapChain, pRamp );
}

HRESULT proxyIDirect3DDevice9::CreateTexture ( UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format,
											   D3DPOOL Pool, IDirect3DTexture9 **ppTexture, HANDLE *pSharedHandle )
{
	return origIDirect3DDevice9->CreateTexture( Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateVolumeTexture ( UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage,
													 D3DFORMAT Format, D3DPOOL Pool,
													 IDirect3DVolumeTexture9 **ppVolumeTexture, HANDLE *pSharedHandle )
{
	return origIDirect3DDevice9->CreateVolumeTexture( Width, Height, Depth, Levels, Usage, Format, Pool,
													  ppVolumeTexture, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateCubeTexture ( UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format,
												   D3DPOOL Pool, IDirect3DCubeTexture9 **ppCubeTexture,
												   HANDLE *pSharedHandle )
{
	return origIDirect3DDevice9->CreateCubeTexture( EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture,
													pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateVertexBuffer ( UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool,
													IDirect3DVertexBuffer9 **ppVertexBuffer, HANDLE *pSharedHandle )
{
	return origIDirect3DDevice9->CreateVertexBuffer( Length, Usage, FVF, Pool, ppVertexBuffer, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateIndexBuffer ( UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool,
												   IDirect3DIndexBuffer9 **ppIndexBuffer, HANDLE *pSharedHandle )
{
	return origIDirect3DDevice9->CreateIndexBuffer( Length, Usage, Format, Pool, ppIndexBuffer, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateRenderTarget ( UINT Width, UINT Height, D3DFORMAT Format,
													D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality,
													BOOL Lockable, IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle )
{
	return origIDirect3DDevice9->CreateRenderTarget( Width, Height, Format, MultiSample, MultisampleQuality, Lockable,
													 ppSurface, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::CreateDepthStencilSurface ( UINT Width, UINT Height, D3DFORMAT Format,
														   D3DMULTISAMPLE_TYPE MultiSample, DWORD MultisampleQuality,
														   BOOL Discard, IDirect3DSurface9 **ppSurface,
														   HANDLE *pSharedHandle )
{
	return origIDirect3DDevice9->CreateDepthStencilSurface( Width, Height, Format, MultiSample, MultisampleQuality,
															Discard, ppSurface, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::UpdateSurface ( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect,
											   IDirect3DSurface9 *pDestinationSurface, CONST POINT *pDestPoint )
{
	return origIDirect3DDevice9->UpdateSurface( pSourceSurface, pSourceRect, pDestinationSurface, pDestPoint );
}

HRESULT proxyIDirect3DDevice9::UpdateTexture ( IDirect3DBaseTexture9 *pSourceTexture,
											   IDirect3DBaseTexture9 *pDestinationTexture )
{
	return origIDirect3DDevice9->UpdateTexture( pSourceTexture, pDestinationTexture );
}

HRESULT proxyIDirect3DDevice9::GetRenderTargetData ( IDirect3DSurface9 *pRenderTarget, IDirect3DSurface9 *pDestSurface )
{
	return origIDirect3DDevice9->GetRenderTargetData( pRenderTarget, pDestSurface );
}

HRESULT proxyIDirect3DDevice9::GetFrontBufferData ( UINT iSwapChain, IDirect3DSurface9 *pDestSurface )
{
	return origIDirect3DDevice9->GetFrontBufferData( iSwapChain, pDestSurface );
}

HRESULT proxyIDirect3DDevice9::StretchRect ( IDirect3DSurface9 *pSourceSurface, CONST RECT *pSourceRect,
											 IDirect3DSurface9 *pDestSurface, CONST RECT *pDestRect,
											 D3DTEXTUREFILTERTYPE Filter )
{
	return origIDirect3DDevice9->StretchRect( pSourceSurface, pSourceRect, pDestSurface, pDestRect, Filter );
}

HRESULT proxyIDirect3DDevice9::ColorFill ( IDirect3DSurface9 *pSurface, CONST RECT *pRect, D3DCOLOR color )
{
	return origIDirect3DDevice9->ColorFill( pSurface, pRect, color );
}

HRESULT proxyIDirect3DDevice9::CreateOffscreenPlainSurface ( UINT Width, UINT Height, D3DFORMAT Format, D3DPOOL Pool,
															 IDirect3DSurface9 **ppSurface, HANDLE *pSharedHandle )
{
	return origIDirect3DDevice9->CreateOffscreenPlainSurface( Width, Height, Format, Pool, ppSurface, pSharedHandle );
}

HRESULT proxyIDirect3DDevice9::SetRenderTarget ( DWORD RenderTargetIndex, IDirect3DSurface9 *pRenderTarget )
{
	return origIDirect3DDevice9->SetRenderTarget( RenderTargetIndex, pRenderTarget );
}

HRESULT proxyIDirect3DDevice9::GetRenderTarget ( DWORD RenderTargetIndex, IDirect3DSurface9 **ppRenderTarget )
{
	return origIDirect3DDevice9->GetRenderTarget( RenderTargetIndex, ppRenderTarget );
}

HRESULT proxyIDirect3DDevice9::SetDepthStencilSurface ( IDirect3DSurface9 *pNewZStencil )
{
	return origIDirect3DDevice9->SetDepthStencilSurface( pNewZStencil );
}

HRESULT proxyIDirect3DDevice9::GetDepthStencilSurface ( IDirect3DSurface9 **ppZStencilSurface )
{
	return origIDirect3DDevice9->GetDepthStencilSurface( ppZStencilSurface );
}

HRESULT proxyIDirect3DDevice9::BeginScene ( void )
{
	traceLastFunc( "proxyIDirect3DDevice9::BeginScene()" );

	// return original function
	HRESULT ret = origIDirect3DDevice9->BeginScene();
	traceLastFunc( "end of proxyIDirect3DDevice9::BeginScene()" );
	return ret;
}

HRESULT proxyIDirect3DDevice9::EndScene ( void )
{
	return origIDirect3DDevice9->EndScene();
}

HRESULT proxyIDirect3DDevice9::Clear ( DWORD Count, CONST D3DRECT *pRects, DWORD Flags, D3DCOLOR Color, float Z,
									   DWORD Stencil )
{
	return origIDirect3DDevice9->Clear( Count, pRects, Flags, Color, Z, Stencil );
}

HRESULT proxyIDirect3DDevice9::SetTransform ( D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix )
{
	// Store the matrix
	pD3DData->StoreTransform ( State, pMatrix );

	return origIDirect3DDevice9->SetTransform( State, pMatrix );
}

HRESULT proxyIDirect3DDevice9::GetTransform ( D3DTRANSFORMSTATETYPE State, D3DMATRIX *pMatrix )
{
	return origIDirect3DDevice9->GetTransform( State, pMatrix );
}

HRESULT proxyIDirect3DDevice9::MultiplyTransform ( D3DTRANSFORMSTATETYPE State, CONST D3DMATRIX *pMatrix )
{
	return origIDirect3DDevice9->MultiplyTransform( State, pMatrix );
}

HRESULT proxyIDirect3DDevice9::SetViewport ( CONST D3DVIEWPORT9 *pViewport )
{
	// Store matrix
	pD3DData->StoreViewport ( pViewport->X, pViewport->Y, pViewport->Width, pViewport->Height );

	return origIDirect3DDevice9->SetViewport( pViewport );
}

HRESULT proxyIDirect3DDevice9::GetViewport ( D3DVIEWPORT9 *pViewport )
{
	return origIDirect3DDevice9->GetViewport( pViewport );
}

HRESULT proxyIDirect3DDevice9::SetMaterial ( CONST D3DMATERIAL9 *pMaterial )
{
	return origIDirect3DDevice9->SetMaterial( pMaterial );
}

HRESULT proxyIDirect3DDevice9::GetMaterial ( D3DMATERIAL9 *pMaterial )
{
	return origIDirect3DDevice9->GetMaterial( pMaterial );
}

HRESULT proxyIDirect3DDevice9::SetLight ( DWORD Index, CONST D3DLIGHT9 *pLight )
{
	return origIDirect3DDevice9->SetLight( Index, pLight );
}

HRESULT proxyIDirect3DDevice9::GetLight ( DWORD Index, D3DLIGHT9 *pLight )
{
	return origIDirect3DDevice9->GetLight( Index, pLight );
}

HRESULT proxyIDirect3DDevice9::LightEnable ( DWORD Index, BOOL Enable )
{
	return origIDirect3DDevice9->LightEnable( Index, Enable );
}

HRESULT proxyIDirect3DDevice9::GetLightEnable ( DWORD Index, BOOL *pEnable )
{
	return origIDirect3DDevice9->GetLightEnable( Index, pEnable );
}

HRESULT proxyIDirect3DDevice9::SetClipPlane ( DWORD Index, CONST float *pPlane )
{
	return origIDirect3DDevice9->SetClipPlane( Index, pPlane );
}

HRESULT proxyIDirect3DDevice9::GetClipPlane ( DWORD Index, float *pPlane )
{
	return origIDirect3DDevice9->GetClipPlane( Index, pPlane );
}

HRESULT proxyIDirect3DDevice9::SetRenderState ( D3DRENDERSTATETYPE State, DWORD Value )
{
	return origIDirect3DDevice9->SetRenderState( State, Value );
}

HRESULT proxyIDirect3DDevice9::GetRenderState ( D3DRENDERSTATETYPE State, DWORD *pValue )
{
	return origIDirect3DDevice9->GetRenderState( State, pValue );
}

HRESULT proxyIDirect3DDevice9::CreateStateBlock ( D3DSTATEBLOCKTYPE Type, IDirect3DStateBlock9 **ppSB )
{
	return origIDirect3DDevice9->CreateStateBlock( Type, ppSB );
}

HRESULT proxyIDirect3DDevice9::BeginStateBlock ( void )
{
	return origIDirect3DDevice9->BeginStateBlock();
}

HRESULT proxyIDirect3DDevice9::EndStateBlock ( IDirect3DStateBlock9 **ppSB )
{
	return origIDirect3DDevice9->EndStateBlock( ppSB );
}

HRESULT proxyIDirect3DDevice9::SetClipStatus ( CONST D3DCLIPSTATUS9 *pClipStatus )
{
	return origIDirect3DDevice9->SetClipStatus( pClipStatus );
}

HRESULT proxyIDirect3DDevice9::GetClipStatus ( D3DCLIPSTATUS9 *pClipStatus )
{
	return origIDirect3DDevice9->GetClipStatus( pClipStatus );
}

HRESULT proxyIDirect3DDevice9::GetTexture ( DWORD Stage, IDirect3DBaseTexture9 **ppTexture )
{
	return origIDirect3DDevice9->GetTexture( Stage, ppTexture );
}

HRESULT proxyIDirect3DDevice9::SetTexture ( DWORD Stage, IDirect3DBaseTexture9 *pTexture )
{
	return origIDirect3DDevice9->SetTexture( Stage, pTexture );
}

HRESULT proxyIDirect3DDevice9::GetTextureStageState ( DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD *pValue )
{
	return origIDirect3DDevice9->GetTextureStageState( Stage, Type, pValue );
}

HRESULT proxyIDirect3DDevice9::SetTextureStageState ( DWORD Stage, D3DTEXTURESTAGESTATETYPE Type, DWORD Value )
{
	return origIDirect3DDevice9->SetTextureStageState( Stage, Type, Value );
}

HRESULT proxyIDirect3DDevice9::GetSamplerState ( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD *pValue )
{
	return origIDirect3DDevice9->GetSamplerState( Sampler, Type, pValue );
}

HRESULT proxyIDirect3DDevice9::SetSamplerState ( DWORD Sampler, D3DSAMPLERSTATETYPE Type, DWORD Value )
{
	return origIDirect3DDevice9->SetSamplerState( Sampler, Type, Value );
}

HRESULT proxyIDirect3DDevice9::ValidateDevice ( DWORD *pNumPasses )
{
	return origIDirect3DDevice9->ValidateDevice( pNumPasses );
}

HRESULT proxyIDirect3DDevice9::SetPaletteEntries ( UINT PaletteNumber, CONST PALETTEENTRY *pEntries )
{
	return origIDirect3DDevice9->SetPaletteEntries( PaletteNumber, pEntries );
}

HRESULT proxyIDirect3DDevice9::GetPaletteEntries ( UINT PaletteNumber, PALETTEENTRY *pEntries )
{
	return origIDirect3DDevice9->GetPaletteEntries( PaletteNumber, pEntries );
}

HRESULT proxyIDirect3DDevice9::SetCurrentTexturePalette ( UINT PaletteNumber )
{
	return origIDirect3DDevice9->SetCurrentTexturePalette( PaletteNumber );
}

HRESULT proxyIDirect3DDevice9::GetCurrentTexturePalette ( UINT *PaletteNumber )
{
	return origIDirect3DDevice9->GetCurrentTexturePalette( PaletteNumber );
}

HRESULT proxyIDirect3DDevice9::SetScissorRect ( CONST RECT *pRect )
{
	return origIDirect3DDevice9->SetScissorRect( pRect );
}

HRESULT proxyIDirect3DDevice9::GetScissorRect ( RECT *pRect )
{
	return origIDirect3DDevice9->GetScissorRect( pRect );
}

HRESULT proxyIDirect3DDevice9::SetSoftwareVertexProcessing ( BOOL bSoftware )
{
	return origIDirect3DDevice9->SetSoftwareVertexProcessing( bSoftware );
}

BOOL proxyIDirect3DDevice9::GetSoftwareVertexProcessing ( void )
{
	return origIDirect3DDevice9->GetSoftwareVertexProcessing();
}

HRESULT proxyIDirect3DDevice9::SetNPatchMode ( float nSegments )
{
	return origIDirect3DDevice9->SetNPatchMode( nSegments );
}

float proxyIDirect3DDevice9::GetNPatchMode ( void )
{
	return origIDirect3DDevice9->GetNPatchMode();
}

HRESULT proxyIDirect3DDevice9::DrawPrimitive ( D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT PrimitiveCount )
{
	return origIDirect3DDevice9->DrawPrimitive( PrimitiveType, StartVertex, PrimitiveCount );
}

HRESULT proxyIDirect3DDevice9::DrawIndexedPrimitive ( D3DPRIMITIVETYPE PrimitiveType, INT BaseVertexIndex,
													  UINT MinVertexIndex, UINT NumVertices, UINT startIndex,
													  UINT primCount )
{
	DWORD	dwRet_addr = ( DWORD ) _ReturnAddress();

	// chams probably works better with texture instead of shaders
	if ( set.chams_on
	 &&	 !cheat_state->_generic.cheat_panic_enabled )
	{
		// actors
		if ( dwRet_addr == 0x761142 )
		{
			origIDirect3DDevice9->SetRenderState( D3DRS_ZENABLE, false );
			//origIDirect3DDevice9->SetRenderState( D3DRS_LIGHTING, true );
			//origIDirect3DDevice9->SetRenderState( D3DRS_SPECULARENABLE, true );
			//origIDirect3DDevice9->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
			//origIDirect3DDevice9->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, true );
			//origIDirect3DDevice9->SetRenderState( D3DRS_ANTIALIASEDLINEENABLE, true );

			if (set.chams_wireframe)
			{
				origIDirect3DDevice9->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );
			}
			else
			{
				origIDirect3DDevice9->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
			}
			origIDirect3DDevice9->SetRenderState( D3DRS_PATCHEDGESTYLE, D3DPATCHEDGE_CONTINUOUS );


			// actor behind wall
			origIDirect3DDevice9->SetPixelShader( chams_blue );
			origIDirect3DDevice9->DrawIndexedPrimitive( PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices,
														startIndex, primCount );

			// actor infront wall
			origIDirect3DDevice9->SetPixelShader( chams_green );
			origIDirect3DDevice9->SetRenderState( D3DRS_ZENABLE, true );
			origIDirect3DDevice9->DrawIndexedPrimitive( PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices,
														startIndex, primCount );
			origIDirect3DDevice9->SetPixelShader( NULL );
			return origIDirect3DDevice9->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
		}

		// some environment parts are also found..
		// weapons
		/*if ( dwRet_addr == 0x75731B )
		{
			LPDIRECT3DVERTEXBUFFER9 Stream_Data;
			D3DVERTEXBUFFER_DESC desc;
			unsigned int desc_size = 0;
			UINT Stride = 0;
			if ( origIDirect3DDevice9->GetStreamSource(0, &Stream_Data, &NumVertices,&Stride) == D3D_OK )
			{
				if ( Stream_Data != NULL )
				{
					Stream_Data->GetDesc( &desc );
					Stream_Data->Release();
					desc_size = desc.Size;
				}
			}

			if ( desc_size == 0x20000 )
			{
				origIDirect3DDevice9->SetRenderState( D3DRS_ZENABLE, false );
				origIDirect3DDevice9->SetRenderState( D3DRS_FILLMODE, D3DFILL_WIREFRAME );

				// weapon behind wall
				origIDirect3DDevice9->SetPixelShader( chams_red );
				origIDirect3DDevice9->DrawIndexedPrimitive( PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices,
															startIndex, primCount );

				// weapon infront wall
				origIDirect3DDevice9->SetPixelShader( chams_blue );
				origIDirect3DDevice9->SetRenderState( D3DRS_ZENABLE, true );
				origIDirect3DDevice9->DrawIndexedPrimitive( PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices,
															startIndex, primCount );
				origIDirect3DDevice9->SetPixelShader( NULL );
				return origIDirect3DDevice9->SetRenderState( D3DRS_FILLMODE, D3DFILL_SOLID );
			}
		}*/
	}

	return origIDirect3DDevice9->DrawIndexedPrimitive( PrimitiveType, BaseVertexIndex, MinVertexIndex, NumVertices,
													   startIndex, primCount );
}

HRESULT proxyIDirect3DDevice9::DrawPrimitiveUP ( D3DPRIMITIVETYPE PrimitiveType, UINT PrimitiveCount,
												 CONST void *pVertexStreamZeroData, UINT VertexStreamZeroStride )
{
	return origIDirect3DDevice9->DrawPrimitiveUP( PrimitiveType, PrimitiveCount, pVertexStreamZeroData,
												  VertexStreamZeroStride );
}

HRESULT proxyIDirect3DDevice9::DrawIndexedPrimitiveUP ( D3DPRIMITIVETYPE PrimitiveType, UINT MinVertexIndex,
														UINT NumVertices, UINT PrimitiveCount, CONST void *pIndexData,
														D3DFORMAT IndexDataFormat, CONST void *pVertexStreamZeroData,
														UINT VertexStreamZeroStride )
{
	return origIDirect3DDevice9->DrawIndexedPrimitiveUP( PrimitiveType, MinVertexIndex, NumVertices, PrimitiveCount,
														 pIndexData, IndexDataFormat, pVertexStreamZeroData,
														 VertexStreamZeroStride );
}

HRESULT proxyIDirect3DDevice9::ProcessVertices ( UINT SrcStartIndex, UINT DestIndex, UINT VertexCount,
												 IDirect3DVertexBuffer9 *pDestBuffer,
												 IDirect3DVertexDeclaration9 *pVertexDecl, DWORD Flags )
{
	return origIDirect3DDevice9->ProcessVertices( SrcStartIndex, DestIndex, VertexCount, pDestBuffer, pVertexDecl, Flags );
}

HRESULT proxyIDirect3DDevice9::CreateVertexDeclaration ( CONST D3DVERTEXELEMENT9 *pVertexElements,
														 IDirect3DVertexDeclaration9 **ppDecl )
{
	return origIDirect3DDevice9->CreateVertexDeclaration( pVertexElements, ppDecl );
}

HRESULT proxyIDirect3DDevice9::SetVertexDeclaration ( IDirect3DVertexDeclaration9 *pDecl )
{
	return origIDirect3DDevice9->SetVertexDeclaration( pDecl );
}

HRESULT proxyIDirect3DDevice9::GetVertexDeclaration ( IDirect3DVertexDeclaration9 **ppDecl )
{
	return origIDirect3DDevice9->GetVertexDeclaration( ppDecl );
}

HRESULT proxyIDirect3DDevice9::SetFVF ( DWORD FVF )
{
	return origIDirect3DDevice9->SetFVF( FVF );
}

HRESULT proxyIDirect3DDevice9::GetFVF ( DWORD *pFVF )
{
	return origIDirect3DDevice9->GetFVF( pFVF );
}

HRESULT proxyIDirect3DDevice9::CreateVertexShader ( CONST DWORD *pFunction, IDirect3DVertexShader9 **ppShader )
{
	return origIDirect3DDevice9->CreateVertexShader( pFunction, ppShader );
}

HRESULT proxyIDirect3DDevice9::SetVertexShader ( IDirect3DVertexShader9 *pShader )
{
	return origIDirect3DDevice9->SetVertexShader( pShader );
}

HRESULT proxyIDirect3DDevice9::GetVertexShader ( IDirect3DVertexShader9 **ppShader )
{
	return origIDirect3DDevice9->GetVertexShader( ppShader );
}

HRESULT proxyIDirect3DDevice9::SetVertexShaderConstantF ( UINT StartRegister, CONST float *pConstantData,
														  UINT Vector4fCount )
{
	return origIDirect3DDevice9->SetVertexShaderConstantF( StartRegister, pConstantData, Vector4fCount );
}

HRESULT proxyIDirect3DDevice9::GetVertexShaderConstantF ( UINT StartRegister, float *pConstantData, UINT Vector4fCount )
{
	return origIDirect3DDevice9->GetVertexShaderConstantF( StartRegister, pConstantData, Vector4fCount );
}

HRESULT proxyIDirect3DDevice9::SetVertexShaderConstantI ( UINT StartRegister, CONST int *pConstantData,
														  UINT Vector4iCount )
{
	return origIDirect3DDevice9->SetVertexShaderConstantI( StartRegister, pConstantData, Vector4iCount );
}

HRESULT proxyIDirect3DDevice9::GetVertexShaderConstantI ( UINT StartRegister, int *pConstantData, UINT Vector4iCount )
{
	return origIDirect3DDevice9->GetVertexShaderConstantI( StartRegister, pConstantData, Vector4iCount );
}

HRESULT proxyIDirect3DDevice9::SetVertexShaderConstantB ( UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount )
{
	return origIDirect3DDevice9->SetVertexShaderConstantB( StartRegister, pConstantData, BoolCount );
}

HRESULT proxyIDirect3DDevice9::GetVertexShaderConstantB ( UINT StartRegister, BOOL *pConstantData, UINT BoolCount )
{
	return origIDirect3DDevice9->GetVertexShaderConstantB( StartRegister, pConstantData, BoolCount );
}

HRESULT proxyIDirect3DDevice9::SetStreamSource ( UINT StreamNumber, IDirect3DVertexBuffer9 *pStreamData,
												 UINT OffsetInBytes, UINT Stride )
{
	return origIDirect3DDevice9->SetStreamSource( StreamNumber, pStreamData, OffsetInBytes, Stride );
}

HRESULT proxyIDirect3DDevice9::GetStreamSource ( UINT StreamNumber, IDirect3DVertexBuffer9 **ppStreamData,
												 UINT *OffsetInBytes, UINT *pStride )
{
	return origIDirect3DDevice9->GetStreamSource( StreamNumber, ppStreamData, OffsetInBytes, pStride );
}

HRESULT proxyIDirect3DDevice9::SetStreamSourceFreq ( UINT StreamNumber, UINT Divider )
{
	return origIDirect3DDevice9->SetStreamSourceFreq( StreamNumber, Divider );
}

HRESULT proxyIDirect3DDevice9::GetStreamSourceFreq ( UINT StreamNumber, UINT *Divider )
{
	return origIDirect3DDevice9->GetStreamSourceFreq( StreamNumber, Divider );
}

HRESULT proxyIDirect3DDevice9::SetIndices ( IDirect3DIndexBuffer9 *pIndexData )
{
	return origIDirect3DDevice9->SetIndices( pIndexData );
}

HRESULT proxyIDirect3DDevice9::GetIndices ( IDirect3DIndexBuffer9 **ppIndexData )
{
	return origIDirect3DDevice9->GetIndices( ppIndexData );
}

HRESULT proxyIDirect3DDevice9::CreatePixelShader ( CONST DWORD *pFunction, IDirect3DPixelShader9 **ppShader )
{
	return origIDirect3DDevice9->CreatePixelShader( pFunction, ppShader );
}

HRESULT proxyIDirect3DDevice9::SetPixelShader ( IDirect3DPixelShader9 *pShader )
{
	return origIDirect3DDevice9->SetPixelShader( pShader );
}

HRESULT proxyIDirect3DDevice9::GetPixelShader ( IDirect3DPixelShader9 **ppShader )
{
	return origIDirect3DDevice9->GetPixelShader( ppShader );
}

HRESULT proxyIDirect3DDevice9::SetPixelShaderConstantF ( UINT StartRegister, CONST float *pConstantData,
														 UINT Vector4fCount )
{
	return origIDirect3DDevice9->SetPixelShaderConstantF( StartRegister, pConstantData, Vector4fCount );
}

HRESULT proxyIDirect3DDevice9::GetPixelShaderConstantF ( UINT StartRegister, float *pConstantData, UINT Vector4fCount )
{
	return origIDirect3DDevice9->GetPixelShaderConstantF( StartRegister, pConstantData, Vector4fCount );
}

HRESULT proxyIDirect3DDevice9::SetPixelShaderConstantI ( UINT StartRegister, CONST int *pConstantData, UINT Vector4iCount )
{
	return origIDirect3DDevice9->SetPixelShaderConstantI( StartRegister, pConstantData, Vector4iCount );
}

HRESULT proxyIDirect3DDevice9::GetPixelShaderConstantI ( UINT StartRegister, int *pConstantData, UINT Vector4iCount )
{
	return origIDirect3DDevice9->GetPixelShaderConstantI( StartRegister, pConstantData, Vector4iCount );
}

HRESULT proxyIDirect3DDevice9::SetPixelShaderConstantB ( UINT StartRegister, CONST BOOL *pConstantData, UINT BoolCount )
{
	return origIDirect3DDevice9->SetPixelShaderConstantB( StartRegister, pConstantData, BoolCount );
}

HRESULT proxyIDirect3DDevice9::GetPixelShaderConstantB ( UINT StartRegister, BOOL *pConstantData, UINT BoolCount )
{
	return origIDirect3DDevice9->GetPixelShaderConstantB( StartRegister, pConstantData, BoolCount );
}

HRESULT proxyIDirect3DDevice9::DrawRectPatch ( UINT Handle, CONST float *pNumSegs, CONST D3DRECTPATCH_INFO *pRectPatchInfo )
{
	return origIDirect3DDevice9->DrawRectPatch( Handle, pNumSegs, pRectPatchInfo );
}

HRESULT proxyIDirect3DDevice9::DrawTriPatch ( UINT Handle, CONST float *pNumSegs, CONST D3DTRIPATCH_INFO *pTriPatchInfo )
{
	return origIDirect3DDevice9->DrawTriPatch( Handle, pNumSegs, pTriPatchInfo );
}

HRESULT proxyIDirect3DDevice9::DeletePatch ( UINT Handle )
{
	return origIDirect3DDevice9->DeletePatch( Handle );
}

HRESULT proxyIDirect3DDevice9::CreateQuery ( D3DQUERYTYPE Type, IDirect3DQuery9 **ppQuery )
{
	return origIDirect3DDevice9->CreateQuery( Type, ppQuery );
}

void toggleWindowedMode ( void )
{
	traceLastFunc( "toggleWindowedMode()" );

	g_isRequestingWindowModeToggle = true;
	g_isRequesting_RwD3D9ChangeVideoMode = true;
	proxyID3DDevice9_InitWindowMode( &pPresentParam );
}
