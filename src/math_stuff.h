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
#ifndef M_PI
#define M_PI	3.14159265358979323844f
#endif
#define DEGTORAD( Deg ) ( (Deg * M_PI) / 180.0f )

int		near_zero ( float v );
void	vect2_normalize ( const float in[2], float out[2] );
float	vect2_length ( const float in[2] );
int		vect2_near_zero ( const float in[2] );
void	vect2_copy ( const uint8_t in[2], uint8_t out[2] );
void	vect3_zero ( float out[3] );
void	vect3_normalize ( const float in[3], float out[3] );
void	vect3_mult ( const float in[3], float m, float out[3] );
float	vect3_length ( const float in[3] );
void	vect3_div ( const float in[3], float m, float out[3] );
void	vect3_mult ( const float in[3], float m, float out[3] );
void	vect3_invert ( const float in[3], float out[3] );
void	vect3_vect3_mult ( const float in1[3], const float in2[3], float out[3] );
void	vect3_vect3_add ( const float in1[3], const float in2[3], float out[3] );
void	vect3_vect3_sub ( const float in1[3], const float in2[3], float out[3] );
int		vect3_near_zero ( const float in[3] );
void	vect3_copy ( const float in[3], float out[3] );
float	vect3_dist ( const float in1[3], const float in2[3] );
int		vect4_near_zero ( const float in[4] );
void	vect4_copy ( const uint8_t in[4], uint8_t out[4] );
void	vect4_copy ( const float in[4], float out[4] );
void	matrix_copy ( const float in[16], float out[16] );
float	vect3_dot_product ( const float in1[3], const float in2[3] );
void	vect3_cross_product ( const float in1[3], const float in2[3], float out[3] );
void	matrix_vect3_mult ( const float matrix[16], const float in[3], float out[3] );
void	matrix_vect4_mult ( const float matrix[16], const float in[4], float out[4] );
void	matrix_matrix_mult ( const float in1[16], const float in2[16], float out[16] );
void	matrix_vect3_rotate ( const float in[16], const float vect[3], float t, float out[16] );
void	matrix_vect3_switchXY ( const float in[16], float out[16] );
void	matrix_identity ( float out[16] );
float	roundf ( float v );

int		project ( const float in[3], const float model[16], const float proj[16], float out[3] );
