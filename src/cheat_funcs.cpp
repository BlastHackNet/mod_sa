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

const struct weapon_entry	weapon_list[] =
{
	{ 0, 0, -1, "Fist" },
	{ 1, 0, 331, "Brass Knuckles" },
	{ 2, 1, 333, "Golf Club" },
	{ 3, 1, 334, "Nitestick" },
	{ 4, 1, 335, "Knife" },
	{ 5, 1, 336, "Baseball Bat" },
	{ 6, 1, 337, "Shovel" },
	{ 7, 1, 338, "Pool Cue" },
	{ 8, 1, 339, "Katana" },
	{ 9, 1, 341, "Chainsaw" },
	{ 22, 2, 346, "Pistol" },
	{ 23, 2, 347, "Silenced Pistol" },
	{ 24, 2, 348, "Desert Eagle" },
	{ 25, 3, 349, "Shotgun" },
	{ 26, 3, 350, "Sawn-Off Shotgun" },
	{ 27, 3, 351, "SPAZ12" },
	{ 28, 4, 352, "Micro UZI" },
	{ 29, 4, 353, "MP5" },
	{ 32, 4, 372, "Tech9" },
	{ 30, 5, 355, "AK47" },
	{ 31, 5, 356, "M4" },
	{ 33, 6, 357, "Country Rifle" },
	{ 34, 6, 358, "Sniper Rifle" },
	{ 35, 7, 359, "Rocket Launcher" },
	{ 36, 7, 360, "Heat Seeking RPG" },
	{ 37, 7, 361, "Flame Thrower" },
	{ 38, 7, 362, "Minigun" },
	{ 16, 8, 342, "Grenade" },
	{ 17, 8, 343, "Teargas" },
	{ 18, 8, 344, "Molotov Cocktail" },
	{ 39, 8, 363, "Remote Explosives" },
	{ 41, 9, 365, "Spray Can" },
	{ 42, 9, 366, "Fire Extinguisher" },
	{ 43, 9, 367, "Camera" },
	{ 10, 10, 321, "Dildo 1" },
	{ 11, 10, 322, "Dildo 2" },
	{ 12, 10, 323, "Vibe 1" },
	{ 13, 10, 324, "Vibe 2" },
	{ 14, 10, 325, "Flowers" },
	{ 15, 10, 326, "Cane" },
	{ 44, 11, 368, "NV Goggles" },
	{ 45, 11, 369, "IR Goggles" },
	{ 46, 11, 371, "Parachute" },
	{ 40, 12, 364, "Detonator" },
	{ -1, -1, -1, NULL }
};

/* IDs must be sequential */
const struct vehicle_entry	vehicle_list[VEHICLE_LIST_SIZE] =
{	// model_id, vehicle class, vehicle name, passenger seats
	{ 400, VEHICLE_CLASS_CAR, "Landstalker", 3 },
	{ 401, VEHICLE_CLASS_CAR, "Bravura", 1 },
	{ 402, VEHICLE_CLASS_CAR_FAST, "Buffalo", 1 },
	{ 403, VEHICLE_CLASS_HEAVY, "Linerunner", 1 },
	{ 404, VEHICLE_CLASS_CAR, "Perennial", 3 },
	{ 405, VEHICLE_CLASS_CAR, "Sentinel", 3 },
	{ 406, VEHICLE_CLASS_HEAVY, "Dumper", 0 },
	{ 407, VEHICLE_CLASS_HEAVY, "Fire Truck", 1 },
	{ 408, VEHICLE_CLASS_HEAVY, "Trashmaster", 1 },
	{ 409, VEHICLE_CLASS_HEAVY, "Stretch", 3 },
	{ 410, VEHICLE_CLASS_CAR, "Manana", 1 },
	{ 411, VEHICLE_CLASS_CAR_FAST, "Infernus", 1 },
	{ 412, VEHICLE_CLASS_CAR, "Voodoo", 1 },
	{ 413, VEHICLE_CLASS_CAR, "Pony", 3 },
	{ 414, VEHICLE_CLASS_CAR, "Mule", 1 },
	{ 415, VEHICLE_CLASS_CAR_FAST, "Cheetah", 1 },
	{ 416, VEHICLE_CLASS_HEAVY, "Ambulance", 3 },
	{ 417, VEHICLE_CLASS_HELI, "Leviathan", 1 },
	{ 418, VEHICLE_CLASS_CAR, "Moonbeam", 3 },
	{ 419, VEHICLE_CLASS_CAR, "Esperanto", 1 },
	{ 420, VEHICLE_CLASS_CAR, "Taxi", 3 },
	{ 421, VEHICLE_CLASS_CAR, "Washington", 3 },
	{ 422, VEHICLE_CLASS_CAR, "Bobcat", 1 },
	{ 423, VEHICLE_CLASS_HEAVY, "Mr. Whoopee", 1 },
	{ 424, VEHICLE_CLASS_CAR, "BF Injection", 1 },
	{ 425, VEHICLE_CLASS_HELI, "Hunter", 0 },
	{ 426, VEHICLE_CLASS_CAR, "Premier", 3 },
	{ 427, VEHICLE_CLASS_HEAVY, "Enforcer", 3 },
	{ 428, VEHICLE_CLASS_HEAVY, "Securicar", 3 },
	{ 429, VEHICLE_CLASS_CAR_FAST, "Banshee", 1 },
	{ 430, VEHICLE_CLASS_BOAT, "Predator", 0 },
	{ 431, VEHICLE_CLASS_HEAVY, "Bus", 7 },
	{ 432, VEHICLE_CLASS_HEAVY, "Rhino", 0 },

	/* tank... */
	{ 433, VEHICLE_CLASS_HEAVY, "Barracks", 1 },
	{ 434, VEHICLE_CLASS_CAR_FAST, "Hotknife", 1 },
	{ 435, VEHICLE_CLASS_TRAILER, "Artict Trailer", 0 },
	{ 436, VEHICLE_CLASS_CAR, "Previon", 1 },
	{ 437, VEHICLE_CLASS_HEAVY, "Coach", 7 },
	{ 438, VEHICLE_CLASS_CAR, "Cabbie", 3 },
	{ 439, VEHICLE_CLASS_CAR_FAST, "Stallion", 1 },
	{ 440, VEHICLE_CLASS_CAR, "Rumpo", 3 },
	{ 441, VEHICLE_CLASS_MINI, "RC Bandit", 0 },
	{ 442, VEHICLE_CLASS_CAR, "Romero", 1 },
	{ 443, VEHICLE_CLASS_HEAVY, "Packer", 1 },
	{ 444, VEHICLE_CLASS_HEAVY, "Monster", 1 },
	{ 445, VEHICLE_CLASS_CAR, "Admiral", 3 },
	{ 446, VEHICLE_CLASS_BOAT, "Squalo", 0 },
	{ 447, VEHICLE_CLASS_HELI, "Seasparrow", 1 },
	{ 448, VEHICLE_CLASS_BIKE, "Pizza Boy", 0 },

	// needs to be researched to find actual max passengers in SA:MP
	{ 449, VEHICLE_CLASS_HEAVY, "Trolly", 1 },

	/* train... */
	{ 450, VEHICLE_CLASS_TRAILER, "Artict Trailer 2", 0 },
	{ 451, VEHICLE_CLASS_CAR_FAST, "Turismo", 1 },
	{ 452, VEHICLE_CLASS_BOAT, "Speeder", 0 },
	{ 453, VEHICLE_CLASS_BOAT, "Reefer", 0 },
	{ 454, VEHICLE_CLASS_BOAT, "Tropic", 0 },
	{ 455, VEHICLE_CLASS_HEAVY, "Flatbed", 1 },
	{ 456, VEHICLE_CLASS_HEAVY, "Yankee", 1 },
	{ 457, VEHICLE_CLASS_MINI, "Caddy", 1 },
	{ 458, VEHICLE_CLASS_CAR, "Solair", 3 },
	{ 459, VEHICLE_CLASS_HEAVY, "Berkley's RC Van", 3 },
	{ 460, VEHICLE_CLASS_AIRPLANE, "Skimmer", 1 },
	{ 461, VEHICLE_CLASS_BIKE, "PCJ-600", 1 },
	{ 462, VEHICLE_CLASS_BIKE, "Faggio", 1 },
	{ 463, VEHICLE_CLASS_BIKE, "Freeway", 1 },
	{ 464, VEHICLE_CLASS_MINI, "RC Baron", 0 },
	{ 465, VEHICLE_CLASS_MINI, "RC Raider", 0 },
	{ 466, VEHICLE_CLASS_CAR, "Glendale", 3 },
	{ 467, VEHICLE_CLASS_CAR, "Oceanic", 3 },
	{ 468, VEHICLE_CLASS_BIKE, "Sanchez", 1 },
	{ 469, VEHICLE_CLASS_HELI, "Sparrow", 1 },
	{ 470, VEHICLE_CLASS_CAR, "Patriot", 3 },
	{ 471, VEHICLE_CLASS_BIKE, "Quadbike", 1 },

	/* sort of.. */
	{ 472, VEHICLE_CLASS_BOAT, "Coastguard", 0 },
	{ 473, VEHICLE_CLASS_BOAT, "Dinghy", 0 },
	{ 474, VEHICLE_CLASS_CAR, "Hermes", 1 },
	{ 475, VEHICLE_CLASS_CAR, "Sabre", 1 },
	{ 476, VEHICLE_CLASS_AIRPLANE, "Rustler", 0 },
	{ 477, VEHICLE_CLASS_CAR_FAST, "ZR-350", 1 },
	{ 478, VEHICLE_CLASS_CAR, "Walton", 1 },
	{ 479, VEHICLE_CLASS_CAR, "Regina", 3 },
	{ 480, VEHICLE_CLASS_CAR_FAST, "Comet", 1 },
	{ 481, VEHICLE_CLASS_BIKE, "BMX", 0 },
	{ 482, VEHICLE_CLASS_HEAVY, "Burrito", 3 },

	// more research on this, the side door might allow 2 passengers
	{ 483, VEHICLE_CLASS_HEAVY, "Camper", 2 },
	{ 484, VEHICLE_CLASS_BOAT, "Marquis", 0 },
	{ 485, VEHICLE_CLASS_MINI, "Baggage", 0 },
	{ 486, VEHICLE_CLASS_HEAVY, "Dozer", 0 },
	{ 487, VEHICLE_CLASS_HELI, "Maverick", 3 },
	{ 488, VEHICLE_CLASS_HELI, "News Chopper", 1 },
	{ 489, VEHICLE_CLASS_CAR, "Rancher", 1 },
	{ 490, VEHICLE_CLASS_CAR, "FBI Rancher", 3 },
	{ 491, VEHICLE_CLASS_CAR, "Virgo", 1 },
	{ 492, VEHICLE_CLASS_CAR, "Greenwood", 3 },
	{ 493, VEHICLE_CLASS_BOAT, "Jetmax", 0 },
	{ 494, VEHICLE_CLASS_CAR_FAST, "Hotring Racer", 1 },
	{ 495, VEHICLE_CLASS_CAR, "Sandking", 1 },
	{ 496, VEHICLE_CLASS_CAR, "Blista Compact", 1 },
	{ 497, VEHICLE_CLASS_HELI, "Police Maverick", 3 },
	{ 498, VEHICLE_CLASS_HEAVY, "Boxville", 3 },
	{ 499, VEHICLE_CLASS_HEAVY, "Benson", 1 },
	{ 500, VEHICLE_CLASS_CAR, "Mesa", 1 },
	{ 501, VEHICLE_CLASS_MINI, "RC Goblin", 0 },
	{ 502, VEHICLE_CLASS_CAR_FAST, "Hotring Racer 2", 1 },
	{ 503, VEHICLE_CLASS_CAR_FAST, "Hotring Racer 3", 1 },
	{ 504, VEHICLE_CLASS_CAR_FAST, "Bloodring Banger", 1 },
	{ 505, VEHICLE_CLASS_CAR, "Rancher", 1 },
	{ 506, VEHICLE_CLASS_CAR_FAST, "Super GT", 1 },
	{ 507, VEHICLE_CLASS_CAR, "Elegant", 3 },
	{ 508, VEHICLE_CLASS_HEAVY, "Journey", 1 },
	{ 509, VEHICLE_CLASS_BIKE, "Bike", 0 },
	{ 510, VEHICLE_CLASS_BIKE, "Mountain Bike", 0 },
	{ 511, VEHICLE_CLASS_AIRPLANE, "Beagle", 1 },
	{ 512, VEHICLE_CLASS_AIRPLANE, "Cropduster", 0 },
	{ 513, VEHICLE_CLASS_AIRPLANE, "Stuntplane", 0 },
	{ 514, VEHICLE_CLASS_HEAVY, "Tanker", 1 },

	/* semi truck */
	{ 515, VEHICLE_CLASS_HEAVY, "Roadtrain", 1 },

	/* semi truck */
	{ 516, VEHICLE_CLASS_CAR, "Nebula", 3 },
	{ 517, VEHICLE_CLASS_CAR, "Majestic", 1 },
	{ 518, VEHICLE_CLASS_CAR, "Buccaneer", 1 },
	{ 519, VEHICLE_CLASS_AIRPLANE, "Shamal", 0 },
	{ 520, VEHICLE_CLASS_AIRPLANE, "Hydra", 0 },
	{ 521, VEHICLE_CLASS_BIKE, "FCR-900", 1 },
	{ 522, VEHICLE_CLASS_BIKE, "NRG-500", 1 },
	{ 523, VEHICLE_CLASS_BIKE, "HPV1000", 1 },
	{ 524, VEHICLE_CLASS_HEAVY, "Cement Truck", 1 },
	{ 525, VEHICLE_CLASS_HEAVY, "Towtruck", 1 },
	{ 526, VEHICLE_CLASS_CAR, "Fortune", 1 },
	{ 527, VEHICLE_CLASS_CAR, "Cadrona", 1 },
	{ 528, VEHICLE_CLASS_HEAVY, "FBI Truck", 1 },
	{ 529, VEHICLE_CLASS_CAR, "Willard", 3 },
	{ 530, VEHICLE_CLASS_MINI, "Forklift", 0 },
	{ 531, VEHICLE_CLASS_CAR, "Tractor", 0 },
	{ 532, VEHICLE_CLASS_HEAVY, "Combine Harvester", 0 },
	{ 533, VEHICLE_CLASS_CAR, "Feltzer", 1 },
	{ 534, VEHICLE_CLASS_CAR, "Remington", 1 },
	{ 535, VEHICLE_CLASS_CAR_FAST, "Slamvan", 1 },
	{ 536, VEHICLE_CLASS_CAR_FAST, "Blade", 1 },
	{ 537, VEHICLE_CLASS_HEAVY, "Freight", 1 },

	/* train engine... */
	{ 538, VEHICLE_CLASS_HEAVY, "Brown Streak Engine", 1 },

	/* train engine... */
	{ 539, VEHICLE_CLASS_BOAT, "Vortex", 0 },
	{ 540, VEHICLE_CLASS_CAR, "Vincent", 3 },
	{ 541, VEHICLE_CLASS_CAR_FAST, "Bullet", 1 },
	{ 542, VEHICLE_CLASS_CAR, "Clover", 1 },
	{ 543, VEHICLE_CLASS_CAR, "Sadler", 1 },
	{ 544, VEHICLE_CLASS_HEAVY, "Fire Truck with ladder", 1 },
	{ 545, VEHICLE_CLASS_CAR, "Hustler", 1 },
	{ 546, VEHICLE_CLASS_CAR, "Intruder", 3 },
	{ 547, VEHICLE_CLASS_CAR, "Primo", 3 },
	{ 548, VEHICLE_CLASS_HELI, "Cargobob", 1 },
	{ 549, VEHICLE_CLASS_CAR, "Tampa", 1 },
	{ 550, VEHICLE_CLASS_CAR, "Sunrise", 3 },
	{ 551, VEHICLE_CLASS_CAR, "Merit", 3 },
	{ 552, VEHICLE_CLASS_HEAVY, "Utility Van", 1 },
	{ 553, VEHICLE_CLASS_AIRPLANE, "Nevada", 0 },
	{ 554, VEHICLE_CLASS_CAR, "Yosemite", 1 },
	{ 555, VEHICLE_CLASS_CAR, "Windsor", 1 },
	{ 556, VEHICLE_CLASS_HEAVY, "Monster 2", 1 },
	{ 557, VEHICLE_CLASS_HEAVY, "Monster 3", 1 },
	{ 558, VEHICLE_CLASS_CAR_FAST, "Uranus", 1 },
	{ 559, VEHICLE_CLASS_CAR_FAST, "Jester", 1 },
	{ 560, VEHICLE_CLASS_CAR_FAST, "Sultan", 3 },
	{ 561, VEHICLE_CLASS_CAR, "Stratum", 3 },
	{ 562, VEHICLE_CLASS_CAR_FAST, "Elegy", 1 },
	{ 563, VEHICLE_CLASS_HELI, "Raindance", 1 },
	{ 564, VEHICLE_CLASS_MINI, "RC Tiger", 0 },
	{ 565, VEHICLE_CLASS_CAR, "Flash", 1 },
	{ 566, VEHICLE_CLASS_CAR, "Tahoma", 3 },
	{ 567, VEHICLE_CLASS_CAR, "Savanna", 3 },
	{ 568, VEHICLE_CLASS_CAR_FAST, "Bandito", 0 },
	{ 569, VEHICLE_CLASS_HEAVY, "Freight Train Flatbed", 0 },

	/* train car... */
	{ 570, VEHICLE_CLASS_HEAVY, "Brown Streak", 0 },

	/* train car... XXX dupe, streakc */
	{ 571, VEHICLE_CLASS_MINI, "Kart", 0 },
	{ 572, VEHICLE_CLASS_MINI, "Mower", 0 },
	{ 573, VEHICLE_CLASS_HEAVY, "Dune", 1 },
	{ 574, VEHICLE_CLASS_MINI, "Sweeper", 0 },
	{ 575, VEHICLE_CLASS_CAR, "Broadway", 1 },
	{ 576, VEHICLE_CLASS_CAR, "Tornado", 1 },
	{ 577, VEHICLE_CLASS_AIRPLANE, "AT-400", 0 },
	{ 578, VEHICLE_CLASS_HEAVY, "DFT-30", 1 },

	/* large flat-bed truck */
	{ 579, VEHICLE_CLASS_CAR, "Huntley", 3 },
	{ 580, VEHICLE_CLASS_CAR, "Stafford", 1 },
	{ 581, VEHICLE_CLASS_BIKE, "BF-400", 1 },
	{ 582, VEHICLE_CLASS_HEAVY, "News Van", 3 },
	{ 583, VEHICLE_CLASS_MINI, "Tug", 0 },
	{ 584, VEHICLE_CLASS_TRAILER, "Petrol Trailer", 0 },
	{ 585, VEHICLE_CLASS_CAR, "Emperor", 3 },
	{ 586, VEHICLE_CLASS_BIKE, "Wayfarer", 1 },
	{ 587, VEHICLE_CLASS_CAR_FAST, "Euros", 1 },
	{ 588, VEHICLE_CLASS_HEAVY, "Hotdog", 1 },
	{ 589, VEHICLE_CLASS_CAR, "Club", 1 },
	{ 590, VEHICLE_CLASS_HEAVY, "Freight Train Boxcar", 0 },

	/* train car... */
	{ 591, VEHICLE_CLASS_TRAILER, "Artict Trailer 3", 0 },
	{ 592, VEHICLE_CLASS_AIRPLANE, "Andromada", 0 },
	{ 593, VEHICLE_CLASS_AIRPLANE, "Dodo", 1 },
	{ 594, VEHICLE_CLASS_MINI, "RC Cam", 0 },
	{ 595, VEHICLE_CLASS_BOAT, "Launch", 0 },
	{ 596, VEHICLE_CLASS_CAR, "Police Car (LS)", 3 },
	{ 597, VEHICLE_CLASS_CAR, "Police Car (SF)", 3 },
	{ 598, VEHICLE_CLASS_CAR, "Police Car (LV)", 3 },
	{ 599, VEHICLE_CLASS_CAR, "Police Ranger", 1 },
	{ 600, VEHICLE_CLASS_CAR, "Picador", 1 },
	{ 601, VEHICLE_CLASS_HEAVY, "S.W.A.T.", 1 },
	{ 602, VEHICLE_CLASS_CAR_FAST, "Alpha", 1 },
	{ 603, VEHICLE_CLASS_CAR_FAST, "Phoenix", 1 },
	{ 604, VEHICLE_CLASS_CAR, "Damaged Glendale", 3 },
	{ 605, VEHICLE_CLASS_CAR, "Damaged Sadler", 1 },
	{ 606, VEHICLE_CLASS_TRAILER, "Baggage Trailer", 0 },
	{ 607, VEHICLE_CLASS_TRAILER, "Baggage Trailer 2", 0 },
	{ 608, VEHICLE_CLASS_TRAILER, "Tug Staircase", 0 },
	{ 609, VEHICLE_CLASS_HEAVY, "Black Boxville", 3 },
	{ 610, VEHICLE_CLASS_TRAILER, "Farm Trailer", 0 },
	{ 611, VEHICLE_CLASS_TRAILER, "Street Sweeper Trailer", 0 }
};

const struct interiors		interiors_list[] =
{
	{ 11, 2003.1178f, 1015.1948f, 33.008f, 351.5789f, "Four Dragons' Managerial Suite" },
	{ 5, 770.8033f, -0.7033f, 1000.7267f, 22.8599f, "Ganton Gym" },
	{ 3, 974.0177f, -9.5937f, 1001.1484f, 22.6045f, "Brothel" },
	{ 3, 961.9308f, -51.9071f, 1001.1172f, 95.5381f, "Brothel2" },
	{ 3, 830.6016f, 5.9404f, 1004.1797f, 125.8149f, "Inside Track Betting" },
	{ 3, 1037.8276f, 0.397f, 1001.2845f, 353.9335f, "Blastin' Fools Records" },
	{ 3, 1212.1489f, -28.5388f, 1000.9531f, 170.5692f, "The Big Spread Ranch" },
	{ 18, 1290.4106f, 1.9512f, 1001.0201f, 179.9419f, "Warehouse 1" },
	{ 1, 1412.1472f, -2.2836f, 1000.9241f, 114.661f, "Warehouse 2" },
	{ 3, 1527.0468f, -12.0236f, 1002.0971f, 350.0013f, "B Dup's Apartment" },
	{ 2, 1523.5098f, -47.8211f, 1002.2699f, 262.7038f, "B Dup's Crack Palace" },
	{ 3, 612.2191f, -123.9028f, 997.9922f, 266.5704f, "Wheel Arch Angels" },
	{ 3, 512.9291f, -11.6929f, 1001.5653f, 198.7669f, "OG Loc's House" },
	{ 3, 418.4666f, -80.4595f, 1001.8047f, 343.2358f, "Barber Shop" },
	{ 3, 386.5259f, 173.6381f, 1008.3828f, 63.7399f, "Planning Department" },
	{ 3, 288.4723f, 170.0647f, 1007.1794f, 22.0477f, "Las Venturas Police Department" },
	{ 3, 206.4627f, -137.7076f, 1003.0938f, 10.9347f, "Pro-Laps" },
	{ 3, -100.2674f, -22.9376f, 1000.7188f, 17.285f, "Sex Shop" },
	{ 3, -201.2236f, -43.2465f, 1002.2734f, 45.8613f, "Las Venturas Tattoo parlor" },
	{ 17, -202.9381f, -6.7006f, 1002.2734f, 204.2693f, "Lost San Fierro Tattoo parlor" },
	{ 17, -25.7220f, -187.8216f, 1003.5469f, 5.0760f, "24/7 (version 1)" },
	{ 5, 454.9853f, -107.2548f, 999.4376f, 309.0195f, "Diner 1" },
	{ 5, 372.5565f, -131.3607f, 1001.4922f, 354.2285f, "Pizza Stack" },
	{ 17, 378.026f, -190.5155f, 1000.6328f, 141.0245f, "Rusty Brown's Donuts" },
	{ 7, 315.244f, -140.8858f, 999.6016f, 7.4226f, "Ammu-nation" },
	{ 5, 225.0306f, -9.1838f, 1002.218f, 85.5322f, "Victim" },
	{ 2, 611.3536f, -77.5574f, 997.9995f, 320.9263f, "Loco Low Co" },
	{ 10, 246.0688f, 108.9703f, 1003.2188f, 0.2922f, "San Fierro Police Department" },
	{ 10, 6.0856f, -28.8966f, 1003.5494f, 5.0365f, "24/7 (version 2 - large)" },
	{ 7, 773.7318f, -74.6957f, 1000.6542f, 5.2304f, "Below The Belt Gym (Las Venturas)" },
	{ 1, 621.4528f, -23.7289f, 1000.9219f, 15.6789f, "Transfenders" },
	{ 1, 445.6003f, -6.9823f, 1000.7344f, 172.2105f, "World of Coq" },
	{ 1, 285.8361f, -39.0166f, 1001.5156f, 0.7529f, "Ammu-nation (version 2)" },
	{ 1, 204.1174f, -46.8047f, 1001.8047f, 357.5777f, "SubUrban" },
	{ 1, 245.2307f, 304.7632f, 999.1484f, 273.4364f, "Denise's Bedroom" },
	{ 3, 290.623f, 309.0622f, 999.1484f, 89.9164f, "Helena's Barn" },
	{ 5, 322.5014f, 303.6906f, 999.1484f, 8.1747f, "Barbara's Love nest" },
	{ 1, -2041.2334f, 178.3969f, 28.8465f, 156.2153f, "San Fierro Garage" },
	{ 1, -1402.6613f, 106.3897f, 1032.2734f, 105.1356f, "Oval Stadium" },
	{ 7, -1403.0116f, -250.4526f, 1043.5341f, 355.8576f, "8-Track Stadium" },
	{ 2, 1204.6689f, -13.5429f, 1000.9219f, 350.0204f, "The Pig Pen (strip club 2)" },
	{ 10, 2016.1156f, 1017.1541f, 996.875f, 88.0055f, "Four Dragons" },
	{ 1, -741.8495f, 493.0036f, 1371.9766f, 71.7782f, "Liberty City" },
	{ 2, 2447.8704f, -1704.4509f, 1013.5078f, 314.5253f, "Ryder's house" },
	{ 1, 2527.0176f, -1679.2076f, 1015.4986f, 260.9709f, "Sweet's House" },
	{ 10, -1129.8909f, 1057.5424f, 1346.4141f, 274.5268f, "RC Battlefield" },
	{ 3, 2496.0549f, -1695.1749f, 1014.7422f, 179.2174f, "The Johnson House" },
	{ 10, 366.0248f, -73.3478f, 1001.5078f, 292.0084f, "Burger shot" },
	{ 1, 2233.9363f, 1711.8038f, 1011.6312f, 184.3891f, "Caligula's Casino" },
	{ 2, 269.6405f, 305.9512f, 999.1484f, 215.6625f, "Katie's Lovenest" },
	{ 2, 414.2987f, -18.8044f, 1001.8047f, 41.4265f, "Barber Shop 2 (Reece's)" },
	{ 2, 1.1853f, -3.2387f, 999.4284f, 87.5718f, "Angel \"Pine Trailer\"" },
	{ 18, -30.9875f, -89.6806f, 1003.5469f, 359.8401f, "24/7 (version 3)" },
	{ 18, 161.4048f, -94.2416f, 1001.8047f, 0.7938f, "Zip" },
	{ 3, -2638.8232f, 1407.3395f, 906.4609f, 94.6794f, "The Pleasure Domes" },
	{ 5, 1267.8407f, -776.9587f, 1091.9063f, 231.3418f, "Madd Dogg's Mansion" },
	{ 2, 2536.5322f, -1294.8425f, 1044.125f, 254.9548f, "Big Smoke's Crack Palace" },
	{ 5, 2350.1597f, -1181.0658f, 1027.9766f, 99.1864f, "Burning Desire Building" },
	{ 1, -2158.6731f, 642.09f, 1052.375f, 86.5402f, "Wu-Zi Mu's" },
	{ 10, 419.8936f, 2537.1155f, 10.0f, 67.6537f, "Abandoned AC tower" },
	{ 14, 256.9047f, -41.6537f, 1002.0234f, 85.8774f, "Wardrobe/Changing room" },
	{ 14, 204.1658f, -165.7678f, 1000.5234f, 181.7583f, "Didier Sachs" },
	{ 12, 1133.35f, -7.8462f, 1000.6797f, 165.8482f, "Casino (Redsands West)" },
	{ 14, -1420.4277f, 1616.9221f, 1052.5313f, 159.1255f, "Kickstart Stadium" },
	{ 17, 493.1443f, -24.2607f, 1000.6797f, 356.9864f, "Club" },
	{ 18, 1727.2853f, -1642.9451f, 20.2254f, 172.4193f, "Atrium" },
	{ 16, -202.842f, -24.0325f, 1002.2734f, 252.8154f, "Los Santos Tattoo Parlor" },
	{ 5, 2233.6919f, -1112.8107f, 1050.8828f, 8.6483f, "Safe House group 1" },
	{ 6, 1211.2484f, 1049.0234f, 359.941f, 170.9341f, "Safe House group 2" },
	{ 9, 2319.1272f, -1023.9562f, 1050.2109f, 167.3959f, "Safe House group 3" },
	{ 10, 2261.0977f, -1137.8833f, 1050.6328f, 266.88f, "Safe House group 4" },
	{ 17, -944.2402f, 1886.1536f, 5.0051f, 179.8548f, "Sherman Dam" },
	{ 16, -26.1856f, -140.9164f, 1003.5469f, 2.9087f, "24/7 (version 4)" },
	{ 15, 2217.281f, -1150.5349f, 1025.7969f, 273.7328f, "Jefferson Motel" },
	{ 1, 1.5491f, 23.3183f, 1199.5938f, 359.9054f, "Jet Interior" },
	{ 1, 681.6216f, -451.8933f, -25.6172f, 166.166f, "The Welcome Pump" },
	{ 3, 234.6087f, 1187.8195f, 1080.2578f, 349.4844f, "Burglary House X1" },
	{ 2, 225.5707f, 1240.0643f, 1082.1406f, 96.2852f, "Burglary House X2" },
	{ 1, 224.288f, 1289.1907f, 1082.1406f, 359.868f, "Burglary House X3" },
	{ 5, 239.2819f, 1114.1991f, 1080.9922f, 270.2654f, "Burglary House X4" },
	{ 15, 207.5219f, -109.7448f, 1005.1328f, 358.62f, "Binco" },
	{ 15, 295.1391f, 1473.3719f, 1080.2578f, 352.9526f, "4 Burglary houses" },
	{ 15, -1417.8927f, 932.4482f, 1041.5313f, 0.7013f, "Blood Bowl Stadium" },
	{ 12, 446.3247f, 509.9662f, 1001.4195f, 330.5671f, "Budget Inn Motel Room" },
	{ 0, 2306.3826f, -15.2365f, 26.7496f, 274.49f, "Palamino Bank" },
	{ 0, 2331.8984f, 6.7816f, 26.5032f, 100.2357f, "Palamino Diner" },
	{ 0, 663.0588f, -573.6274f, 16.3359f, 264.9829f, "Dillimore Gas Station" },
	{ 18, -227.5703f, 1401.5544f, 27.7656f, 269.2978f, "Lil' Probe Inn" },
	{ 0, -688.1496f, 942.0826f, 13.6328f, 177.6574f, "Torreno's Ranch" },
	{ 0, -1916.1268f, 714.8617f, 46.5625f, 152.2839f, "Zombotech - lobby area" },
	{ 0, 818.7714f, -1102.8689f, 25.794f, 91.1439f, "Crypt in LS cemetery (temple)" },
	{ 0, 255.2083f, -59.6753f, 1.5703f, 1.4645f, "Blueberry Liquor Store" },
	{ 2, 446.626f, 1397.738f, 1084.3047f, 343.9647f, "Pair of Burglary Houses" },
	{ 5, 227.3922f, 1114.6572f, 1080.9985f, 267.459f, "Crack Den" },
	{ 5, 227.7559f, 1114.3844f, 1080.9922f, 266.2624f, "Burglary House X11" },
	{ 4, 261.1165f, 1287.2197f, 1080.2578f, 178.9149f, "Burglary House X12" },
	{ 4, 291.7626f, -80.1306f, 1001.5156f, 290.2195f, "Ammu-nation (version 3)" },
	{ 4, 449.0172f, -88.9894f, 999.5547f, 89.6608f, "Jay's Diner" },
	{ 4, -27.844f, -26.6737f, 1003.5573f, 184.3118f, "24/7 (version 5)" },
	{ 0, 2135.2004f, -2276.2815f, 20.6719f, 318.59f, "Warehouse 3" },
	{ 4, 306.1966f, 307.819f, 1003.3047f, 203.1354f, "Michelle's Love Nest*" },
	{ 10, 24.3769f, 1341.1829f, 1084.375f, 8.3305f, "Burglary House X14" },
	{ 1, 963.0586f, 2159.7563f, 1011.0303f, 175.313f, "Sindacco Abatoir" },
	{ 0, 2548.4807f, 2823.7429f, 10.8203f, 270.6003f, "K.A.C.C. Military Fuels Depot" },
	{ 0, 215.1515f, 1874.0579f, 13.1406f, 177.5538f, "Area 69" },
	{ 4, 221.6766f, 1142.4962f, 1082.6094f, 184.9618f, "Burglary House X13" },
	{ 12, 2323.7063f, -1147.6509f, 1050.7101f, 206.5352f, "Unused Safe House" },
	{ 6, 344.9984f, 307.1824f, 999.1557f, 193.643f, "Millie's Bedroom" },
	{ 12, 411.9707f, -51.9217f, 1001.8984f, 173.3449f, "Barber Shop" },
	{ 4, -1421.5618f, -663.8262f, 1059.5569f, 170.9341f, "Dirtbike Stadium" },
	{ 6, 773.8887f, -47.7698f, 1000.5859f, 10.7161f, "Cobra Gym" },
	{ 6, 246.6695f, 65.8039f, 1003.6406f, 7.9562f, "Los Santos Police Department" },
	{ 14, -1864.9434f, 55.7325f, 1055.5276f, 85.8541f, "Los Santos Airport" },
	{ 4, -262.1759f, 1456.6158f, 1084.3672f, 82.459f, "Burglary House X15" },
	{ 5, 22.861f, 1404.9165f, 1084.4297f, 349.6158f, "Burglary House X16" },
	{ 5, 140.3679f, 1367.8837f, 1083.8621f, 349.2372f, "Burglary House X17" },
	{ 3, 1494.8589f, 1306.48f, 1093.2953f, 196.065f, "Bike School" },
	{ 14, -1813.213f, -58.012f, 1058.9641f, 335.3199f, "Francis International Airport" },
	{ 16, -1401.067f, 1265.3706f, 1039.8672f, 178.6483f, "Vice Stadium" },
	{ 6, 234.2826f, 1065.229f, 1084.2101f, 4.3864f, "Burglary House X18" },
	{ 6, -68.5145f, 1353.8485f, 1080.2109f, 3.5742f, "Burglary House X19" },
	{ 6, -2240.1028f, 136.973f, 1035.4141f, 269.0954f, "Zero's RC Shop" },
	{ 6, 297.144f, -109.8702f, 1001.5156f, 20.2254f, "Ammu-nation (version 4)" },
	{ 6, 316.5025f, -167.6272f, 999.5938f, 10.3031f, "Ammu-nation (version 5)" },
	{ 15, -285.2511f, 1471.197f, 1084.375f, 85.6547f, "Burglary House X20" },
	{ 6, -26.8339f, -55.5846f, 1003.5469f, 3.9528f, "24/7 (version 6)" },
	{ 6, 442.1295f, -52.4782f, 999.7167f, 177.9394f, "Secret Valley Diner" },
	{ 2, 2182.2017f, 1628.5848f, 1043.8723f, 224.8601f, "Rosenberg's Office in Caligulas" },
	{ 6, 748.4623f, 1438.2378f, 1102.9531f, 0.6069f, "Fanny Batter's Whore House" },
	{ 8, 2807.3604f, -1171.7048f, 1025.5703f, 193.7117f, "Colonel Furhberger's" },
	{ 9, 366.0002f, -9.4338f, 1001.8516f, 160.528f, "Cluckin' Bell" },
	{ 1, 2216.1282f, -1076.3052f, 1050.4844f, 86.428f, "The Camel's Toe Safehouse" },
	{ 1, 2268.5156f, 1647.7682f, 1084.2344f, 99.7331f, "Caligula's Roof" },
	{ 2, 2236.6997f, -1078.9478f, 1049.0234f, 2.5706f, "Old Venturas Strip Casino" },
	{ 3, -2031.1196f, -115.8287f, 1035.1719f, 190.1877f, "Driving School" },
	{ 8, 2365.1089f, -1133.0795f, 1050.875f, 177.3947f, "Verdant Bluffs Safehouse" },
	{ 0, 1168.512f, 1360.1145f, 10.9293f, 196.5933f, "Bike School" },
	{ 9, 315.4544f, 976.5972f, 1960.8511f, 359.6368f, "Andromada" },
	{ 10, 1893.0731f, 1017.8958f, 31.8828f, 86.1044f, "Four Dragons' Janitor's Office" },
	{ 11, 501.9578f, -70.5648f, 998.7578f, 171.5706f, "Bar" },
	{ 8, -42.5267f, 1408.23f, 1084.4297f, 172.068f, "Burglary House X21" },
	{ 11, 2283.3118f, 1139.307f, 1050.8984f, 19.7032f, "Willowfield Safehouse" },
	{ 9, 84.9244f, 1324.2983f, 1083.8594f, 159.5582f, "Burglary House X22" },
	{ 9, 260.7421f, 1238.2261f, 1084.2578f, 84.3084f, "Burglary House X23" },
	{ 0, -1658.1656f, 1215.0002f, 7.25f, 103.9074f, "Otto's Autos" },
	{ 0, -1961.6281f, 295.2378f, 35.4688f, 264.4891f, "Wang Cars" }
};

// new functions to check for bad pointers
int isBadPtr_GTA_pVehicle ( vehicle_info *p_VehicleInfo )
{
	if ( p_VehicleInfo == NULL )
		return 1;
	if ( !
			(
				(DWORD) p_VehicleInfo >= (DWORD) pool_vehicle->start
				&& (DWORD) p_VehicleInfo <= ((DWORD) pool_vehicle->start + (pool_vehicle->size * sizeof(vehicle_info)))
			)
		)
		return 1;
	return ( p_VehicleInfo->base.matrix == NULL ) || (p_VehicleInfo->base.nType != ENTITY_TYPE_VEHICLE);
}

int isBadPtr_GTA_pVehicle ( CVehicle *p_CVehicle )
{
	if ( p_CVehicle == NULL )
		return 1;
	CVehicleSAInterface *p_CVehicleSAInterface = p_CVehicle->GetVehicleInterface();
	if ( p_CVehicleSAInterface == NULL )
		return 1;
	if ( !
			(
				(DWORD) p_CVehicleSAInterface >= (DWORD) pool_vehicle->start
				&& (DWORD) p_CVehicleSAInterface <= ((DWORD) pool_vehicle->start + (pool_vehicle->size * sizeof(CVehicleSAInterface)))
			)
		)
		return 1;
	return ( p_CVehicleSAInterface->Placeable.matrix == NULL ) || (p_CVehicleSAInterface->nType != ENTITY_TYPE_VEHICLE);
}

int isBadPtr_GTA_pVehicle ( CVehicleSA *p_CVehicleSA )
{
	if ( p_CVehicleSA == NULL )
		return 1;
	CVehicleSAInterface *p_CVehicleSAInterface = p_CVehicleSA->GetVehicleInterface();
	if ( p_CVehicleSAInterface == NULL )
		return 1;
	if	( !
			(
				(DWORD) p_CVehicleSAInterface >= (DWORD) pool_vehicle->start
				&& (DWORD) p_CVehicleSAInterface <= ((DWORD) pool_vehicle->start + (pool_vehicle->size * sizeof(CVehicleSAInterface)))
			)
		)
		return 1;
	return ( p_CVehicleSAInterface->Placeable.matrix == NULL ) || (p_CVehicleSAInterface->nType != ENTITY_TYPE_VEHICLE);
}

int isBadPtr_GTA_pVehicle ( CVehicleSAInterface *p_CVehicleSAInterface )
{
	if ( p_CVehicleSAInterface == NULL )
		return 1;
	if ( !
			(
				 (DWORD) p_CVehicleSAInterface >= (DWORD) pool_vehicle->start
				 && (DWORD) p_CVehicleSAInterface <= ((DWORD) pool_vehicle->start + (pool_vehicle->size * sizeof(CVehicleSAInterface)))
			)
		)
		return 1;
	return ( p_CVehicleSAInterface->Placeable.matrix == NULL ) || (p_CVehicleSAInterface->nType != ENTITY_TYPE_VEHICLE);
}

int isBadPtr_GTA_pPed ( actor_info *pActorInfo )
{
	if ( pActorInfo == NULL )
		return 1;
	if ( !
			(
				(DWORD) pActorInfo >= (DWORD) pool_actor->start
				&& (DWORD) pActorInfo <= ((DWORD) pool_actor->start + (pool_actor->size * sizeof(actor_info)))
			)
		)
		return 1;
	return (pActorInfo->base.matrix == NULL) || (pActorInfo->base.nType != ENTITY_TYPE_PED);
}

int isBadPtr_GTA_pPed ( CPed *pCPed )
{
	if ( pCPed == NULL )
		return 1;
	CPedSAInterface *pCPedSAInterface = pCPed->GetPedInterface();
	if ( !
			(
				(DWORD) pCPedSAInterface >= (DWORD) pool_actor->start
				&& (DWORD) pCPedSAInterface <= ((DWORD) pool_actor->start + (pool_actor->size * sizeof(CPedSAInterface)))
			)
		)
		return 1;
	return ( pCPedSAInterface->Placeable.matrix == NULL ) || (pCPedSAInterface->nType != ENTITY_TYPE_PED);
}

int isBadPtr_GTA_pPed ( CPedSAInterface *pCPedSAInterface )
{
	if ( pCPedSAInterface == NULL )
		return 1;
	if ( !
			(
				(DWORD) pCPedSAInterface >= (DWORD) pool_actor->start
				&& (DWORD) pCPedSAInterface <= ((DWORD) pool_actor->start + (pool_actor->size * sizeof(CPedSAInterface)))
			)
		)
		return 1;
	return ( pCPedSAInterface->Placeable.matrix == NULL ) || (pCPedSAInterface->nType != ENTITY_TYPE_PED);
}

int isBadPtr_GTA_pBuildingInfo ( DWORD p_BuildingInfo )
{
	if ( p_BuildingInfo == NULL )
		return 1;

	struct pool *pool_building = *(struct pool **)BUILDING_POOL_POINTER;
	if ( pool_building == NULL || pool_building->start == NULL || pool_building->size <= 0 )
		return 1;

	if ( !
			 (
			 (DWORD) p_BuildingInfo >= (DWORD) pool_building->start && (DWORD) p_BuildingInfo <=
			 ((DWORD) pool_building->start + (pool_building->size * 56))
		) )
		return 1;

	return 0;
}

int isBadPtr_GTA_pObjectInfo ( DWORD p_ObjectInfo )
{
	if ( p_ObjectInfo == NULL )
		return 1;

	struct pool *pool_object = *(struct pool **)OBJECT_POOL_POINTER;
	if ( pool_object == NULL || pool_object->start == NULL || pool_object->size <= 0 )
		return 1;

	if ( !
			 (
			 (DWORD) p_ObjectInfo >= (DWORD) pool_object->start && (DWORD) p_ObjectInfo <=
			 ((DWORD) pool_object->start + (pool_object->size * 412))
		) )
		return 1;

	return 0;
}

bool isBadPtr_handlerAny ( void *pointer, ULONG size, DWORD dwFlags )
{
	DWORD						dwSize;
	MEMORY_BASIC_INFORMATION	meminfo;

	if ( NULL == pointer )
		return true;

	memset( &meminfo, 0x00, sizeof(meminfo) );
	dwSize = VirtualQuery( pointer, &meminfo, sizeof(meminfo) );

	if ( 0 == dwSize )
		return true;

	if ( MEM_COMMIT != meminfo.State )
		return true;

	if ( 0 == (meminfo.Protect & dwFlags) )
		return true;

	if ( size > meminfo.RegionSize )
		return true;

	if ( (unsigned)((char *)pointer - (char *)meminfo.BaseAddress) > (unsigned)(meminfo.RegionSize - size) )
		return true;

	return false;
}

bool isBadPtr_readAny ( void *pointer, ULONG size )
{
	return isBadPtr_handlerAny( pointer, size, PAGE_READONLY | PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READ |
								PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY );
}

bool isBadPtr_writeAny ( void *pointer, ULONG size )
{
	return isBadPtr_handlerAny( pointer, size,
								PAGE_READWRITE | PAGE_WRITECOPY | PAGE_EXECUTE_READWRITE | PAGE_EXECUTE_WRITECOPY );
}

uint32_t GetFromPool ( DWORD value, DWORD Pool, DWORD function )
{
	uint32_t	retval;
	__asm
	{
		mov ecx, Pool
		mov ecx, [ecx]
		push value
		call function
		mov retval, eax
	}

	return retval;
}

inline int ScriptCarId ( struct vehicle_info *car )
{
	return (int)GetFromPool( (DWORD) car, VEHICLE_POOL_POINTER, FUNC_GET_CAR_ID );
}

inline int ScriptActorId ( struct actor_info *actor )
{
	return (int)GetFromPool( (DWORD) actor, ACTOR_POOL_POINTER, FUNC_GET_ACTOR_ID );
}

inline int ScriptObjectId ( struct object_info *object )
{
	return (int)GetFromPool( (DWORD) object, OBJECT_POOL_POINTER, FUNC_GET_OBJECT_ID );
}

inline struct vehicle_info *GetVehicleByGtaId ( int car_id )
{
	return (vehicle_info *)GetFromPool( (DWORD) car_id, VEHICLE_POOL_POINTER, FUNC_GET_CAR_STRUCT );
}

inline struct actor_info *GetActorByGtaId ( int actor_id )
{
	return (actor_info *)GetFromPool( (DWORD) actor_id, ACTOR_POOL_POINTER, FUNC_GET_ACTOR_STRUCT );
}

inline struct object_info *GetObjectByGtaId ( int object_id )
{
	return (object_info *)GetFromPool( (DWORD) object_id, OBJECT_POOL_POINTER, FUNC_GET_OBJECT_STRUCT );
}

void gta_weather_state_set ( int state )
{
	*(uint16_t *)0x00C81318 = ( uint16_t ) state;
	*(uint16_t *)0x00C8131C = ( uint16_t ) state;
	*(uint16_t *)0x00C81320 = ( uint16_t ) state;
}

void gta_time_hour_set ( int hour )
{
	*(uint8_t *)0x00B70153 = ( uint8_t ) hour;
}

void gta_money_set ( uint32_t value )
{
	*(uint32_t *)0x00B7CE50 = value;
	*(uint32_t *)0x00B7CE54 = value;
}

uint32_t gta_money_get ( void )
{
	return * (uint32_t *)0x00B7CE50;
}

void gta_gravity_set ( float value )
{
	memcpy_safe( (void *)0x00863984, &value, sizeof(float) );
}

float gta_gravity_get ( void )
{
	float	value;

	memcpy_safe( &value, (void *)0x00863984, sizeof(float) );

	return value;
}

void gta_game_speed_set ( float value )
{
	*(float *)0x00B7CB64 = value;
}

float gta_game_speed_get ( void )
{
	return * (float *)0x00B7CB64;
}

struct checkpoint *gta_checkpoint_info_get ( int n )
{
	struct checkpoint	*cp = (struct checkpoint *)0x00C7F158;

	if ( vect3_near_zero(cp->position) )
		return NULL;

	return &cp[n];
}

int gta_menu_active ( void )
{
	return (int)( *(uint8_t *)0x00BA67A4 );
}

void gta_menu_active_set ( int enabled )
{
	/* untested */
	*(uint8_t *)0x00BA67A4 = ( uint8_t ) enabled;
}

const struct weapon_entry *gta_weapon_get_by_name ( const char *name )
{
	const struct weapon_entry	*entry = weapon_list;

	while ( entry->name != NULL )
	{
		if ( _stricmp(entry->name, name) == 0 )
			return entry;
		entry++;
	}

	return NULL;
}

void gta_weapon_set ( struct actor_info *info, int slot, int id, int ammo, int ammo_clip )
{
	/*memset(&info->weapon[slot], 0, sizeof(struct weapon));*/
	if ( slot < 0 || slot > 12 )
	{
		Log( "invalid weapon slot %d!", slot );
		return;
	}
	if (id < WEAPONTYPE_UNARMED || id >= WEAPONTYPE_LAST_WEAPONTYPE)
	{
		Log("invalid weapon id %d!", id);
		return;
	}

	// less optimized, but more secure way
	CWeapon *weap = pPedSelf->GiveWeapon(eWeaponType(id), 1);
	weap->SetAmmoTotal(ammo);
	weap->SetAmmoInClip(ammo_clip);
}

int gta_weapon_ammo_set ( struct actor_info *info, int slot, int ammo )
{
	uint32_t	ammo_old = info->weapon[slot].ammo;

	if ( ammo >= 0 )
		info->weapon[slot].ammo = ammo;

	return ammo_old;
}

int gta_weapon_ammo_clip_set ( struct actor_info *info, int slot, int ammo_clip )
{
	uint32_t	ammo_clip_old = info->weapon[slot].ammo_clip;

	if ( ammo_clip >= 0 )
		info->weapon[slot].ammo_clip = ammo_clip;

	return ammo_clip_old;
}

const char *gta_vehicle_class_name ( int id )
{
	switch ( id )
	{
	case VEHICLE_CLASS_CAR:
		return "Regular cars";

	case VEHICLE_CLASS_CAR_FAST:
		return "Fast cars";

	case VEHICLE_CLASS_HEAVY:
		return "Heavy vehicles";

	case VEHICLE_CLASS_HELI:
		return "Helicopters";

	case VEHICLE_CLASS_AIRPLANE:
		return "Airplanes";

	case VEHICLE_CLASS_BIKE:
		return "Bikes";

	case VEHICLE_CLASS_BOAT:
		return "Boats";

	case VEHICLE_CLASS_MINI:
		return "Small vehicles";

	case VEHICLE_CLASS_TRAILER:
		return "Trailers";
	}

	return "Unknown class (bug)";
}

const struct vehicle_entry *gta_vehicle_get_by_id ( int id )
{
	id -= VEHICLE_LIST_ID_START;

	if ( id < 0 || id >= VEHICLE_LIST_SIZE )
		return NULL;

	return &vehicle_list[id];
}

void loadAllWeaponModels ( void )
{
	static int	models_loaded;
	if ( !models_loaded )
	{
		const struct weapon_entry	*weapon;
		for ( weapon = weapon_list; weapon->name != NULL; weapon++ )
		{
			if ( weapon->model_id == -1 )
				continue;
			if ( GTAfunc_isModelLoaded(weapon->model_id) )
				continue;
			GTAfunc_requestModelLoad( weapon->model_id );
			GTAfunc_loadRequestedModels();
		}

		models_loaded = 1;
	}
}

void loadSpecificModel ( int iModelID )
{
	if ( GTAfunc_isModelLoaded(iModelID) )
		return;
	GTAfunc_requestModelLoad( iModelID );
	GTAfunc_loadRequestedModels();
	while ( !GTAfunc_isModelLoaded(iModelID) )
		Sleep( 10 );
}

typedef void * ( __cdecl * vehicle_spawn_func ) (int);

void gta_vehicle_spawn ( int vehicle_id )
{
	vehicle_spawn_func	vehicle_spawn = ( vehicle_spawn_func ) 0x0043A0B0;

	Log( "Calling vehicle_spawn(%d)...", vehicle_id );
	vehicle_spawn( vehicle_id );
	Log( "Returned." );
}

typedef void * ( __cdecl * jetpack_give_func ) (void);

void gta_jetpack_give ( void )
{
	jetpack_give_func	jetpack_give = ( jetpack_give_func ) 0x00439600;

	Log( "Calling jetpack_give()..." );
	jetpack_give();
	Log( "Returned." );
}

int gta_interior_id_get ( void )
{
	return (int) * (uint32_t *)0x00B72914;
}

void gta_interior_id_set ( int id )
{
	struct actor_info	*info = actor_info_get( ACTOR_SELF, 0 );

	*(uint32_t *)0x00B72914 = ( uint32_t ) id;

	if ( info != NULL )
		info->base.interior_id = ( uint8_t ) id;
}

void gta_blow_all_cars ()
{
	uint32_t	func = 0x439D80;
	__asm call func
}

/* returns the time since start in 100 usec precision
   will wrap after 119.3 hours (should be ok though,
   since SA-MP usually crashes at least once every hour,
   and very few people play for 119 hours straight... */
uint64_t __time_get ( void )
{
	static int				init = 0;
	static ULARGE_INTEGER	init_time;
	FILETIME				ft;
	ULARGE_INTEGER			time_now;

	GetSystemTimeAsFileTime( &ft );
	time_now.LowPart = ft.dwLowDateTime;
	time_now.HighPart = ft.dwHighDateTime;

	time_now.QuadPart /= ( uint64_t ) 1000; /* convert to 100 usec */

	if ( !init )
	{
		init_time.QuadPart = time_now.QuadPart - MSEC_TO_TIME( 1000 );
		init = 1;
	}

	return ( uint64_t ) ( time_now.QuadPart - init_time.QuadPart );
}

void cheat_state_text ( const char *fmt, ... )
{
	va_list ap;
	if ( fmt == NULL )
	{
		cheat_state->text_time = 0;
		return;
	}

	memset( cheat_state->text, 0, sizeof(cheat_state->text) );

	va_start( ap, fmt );
	vsnprintf( cheat_state->text, sizeof(cheat_state->text)-1, fmt, ap );
	va_end( ap );
	cheat_state->text_time = time_get();
}

/* returns actor <id>'s struct
   if id is ACTOR_SELF (-1), the pointer to our own actor is returned */
struct actor_info *actor_info_get ( int id, int flags )
{
	struct actor_info	*info;

	if ( pool_actor == NULL )
		return NULL;

	if ( id != ACTOR_SELF && (id < 0 && id >= pool_actor->size) )
		return NULL;

	if ( id == ACTOR_SELF )
	{
		info = (struct actor_info *)( UINT_PTR ) * (uint32_t *)ACTOR_POINTER_SELF;
		if ( isBadPtr_GTA_pPed(info) )
			return NULL;
	}
	else
	{
		info = &( (struct actor_info *)pool_actor->start )[id];
		if ( isBadPtr_GTA_pPed(info) )
			return NULL;
	}

	/* XXX this should not be nessecary... but it is. fix it. */
	if ( vect3_near_zero(&info->base.matrix[4 * 3]) )
		return NULL;

	if ( (flags & ACTOR_ALIVE) && ACTOR_IS_DEAD(info) )
		return NULL;

	/* exclude actors in the same car as ACTOR_SELF */
	if ( flags & ACTOR_NOT_SAME_VEHICLE )
	{
		struct actor_info	*self = actor_info_get( ACTOR_SELF, 0 );

		if ( self != NULL
		 &&	 info->state == ACTOR_STATE_DRIVING
		 &&	 self->state == ACTOR_STATE_DRIVING
		 &&	 info->vehicle == self->vehicle ) return NULL;
	}

	return info;
}

void cheat_teleport_history_save ( void )
{
	struct cheat_state_teleport *teleport;
	struct object_base			*base;

	if ( cheat_state->state == CHEAT_STATE_VEHICLE )
		base = &vehicle_info_get( VEHICLE_SELF, 0 )->base;
	else if ( cheat_state->state == CHEAT_STATE_ACTOR )
		base = &actor_info_get( ACTOR_SELF, 0 )->base;
	else
		return;

	if ( ++cheat_state->teleport_hist_count > TELEPORT_HIST_MAX )
	{
		cheat_state->teleport_hist_count = TELEPORT_HIST_MAX;
		memmove( &cheat_state->teleport_hist[0], &cheat_state->teleport_hist[1], sizeof(*teleport) * (TELEPORT_HIST_MAX - 1) );
	}

	teleport = &cheat_state->teleport_hist[cheat_state->teleport_hist_count - 1];
	teleport->set = 1;
	matrix_copy( base->matrix, teleport->matrix );
	teleport->interior_id = gta_interior_id_get();
}

void vehicle_detachables_teleport ( struct vehicle_info *info, const float from[3], const float to[3] )
{
	int i, n;

	/*Log("detachables for type=%d id=%d:", info->vehicle_type, info->vehicle_id);
   dump_vect("bike1[0]", info->detachable_bike1[0].position);
   for(i=0; i<4; i++)
      dump_vect("bike2[]", info->detachable_bike2[i].position);
   for(i=0; i<4; i++)
      dump_vect("car[]", info->detachable_car[i].position);
   Log("");*/
	switch ( info->vehicle_type )
	{
	case VEHICLE_TYPE_CAR:	/* + helicopters and planes */
		for ( n = 0; n < 4; n++ )
		{
			for ( i = 0; i < 3; i++ )
				info->detachable_car[n].position[i] += to[i] - from[i];
		}
		break;

	case VEHICLE_TYPE_BIKE:
		for ( i = 0; i < 3; i++ )
			info->detachable_bike1[0].position[i] += to[i] - from[i];
		for ( n = 0; n < 4; n++ )
		{
			for ( i = 0; i < 3; i++ )
				info->detachable_bike2[n].position[i] += to[i] - from[i];
		}
		break;

	case VEHICLE_TYPE_TRAIN:
		/* XXX: fixme */
		break;

	case VEHICLE_TYPE_BOAT:
		for ( n = 0; n < 2; n++ )
		{
			for ( i = 0; i < 3; i++ )
				info->detachable_bike2[n].position[i] += to[i] - from[i];
		}
		break;
	}

	/*Log("detachables after teleport for type=%d id=%d:", info->vehicle_type, info->vehicle_id);
   dump_vect("bike1[0]", info->detachable_bike1[0].position);
   for(i=0; i<4; i++)
      dump_vect("bike2[]", info->detachable_bike2[i].position);
   for(i=0; i<4; i++)
      dump_vect("car[]", info->detachable_car[i].position);
   Log("");
   Log("");
   Log("");*/
}

/* returns vehicle <id>'s struct
   if id is VEHICLE_SELF (-1), the pointer to our own vehicle is returned */
struct vehicle_info *vehicle_info_get ( int id, int flags )
{
	struct vehicle_info *info;

	if ( pool_vehicle == NULL )
		return NULL;

	if ( id != VEHICLE_SELF && (id < 0 && id >= pool_vehicle->size) )
		return NULL;

	if ( id == VEHICLE_SELF )
	{
		info = (struct vehicle_info *)( UINT_PTR ) * (uint32_t *)VEHICLE_POINTER_SELF;
		if ( isBadPtr_GTA_pVehicle(info) )
			return NULL;

		// check to see if we're actually in the vehicle
		struct actor_info	*actor = actor_info_get( ACTOR_SELF, ACTOR_ALIVE );
		if ( !vehicle_contains_actor(info, actor) )
			return NULL;
	}
	else
	{
		info = &( (struct vehicle_info *)pool_vehicle->start )[id];
		if ( isBadPtr_GTA_pVehicle(info) )
			return NULL;
	}

	// filtering for VEHICLE_EMPTY
	// put it here if we ever actually use it =P
	if ( (flags & VEHICLE_ALIVE) && (info->hitpoints < 250.0f && info->burn_timer == 0.0f) )
		return NULL;

	return info;
}

void cheat_vehicle_tires_set ( struct vehicle_info *info, uint8_t tire_status )
{
	struct vehicle_info *temp;

	uint8_t				tires[4] = { tire_status, tire_status, tire_status, tire_status };

	for ( temp = info; temp != NULL; temp = temp->trailer )
	{
		if(temp == NULL) return;

		uint8_t type = temp->vehicle_type;

		if ( type == VEHICLE_TYPE_CAR )
			vect4_copy( tires, temp->car_tire_status );
		else if ( type == VEHICLE_TYPE_BIKE )
			vect2_copy( tires, temp->bike_tire_status );

		if ( !set.trailer_support )
			break;
	}
}

int vehicle_contains_trailer ( struct vehicle_info *info, const struct vehicle_info *trailer )
{
	struct vehicle_info *temp;

	for ( temp = info; temp != NULL; temp = temp->trailer )
	{
		if(temp == NULL) return 0;

		if ( temp == trailer )
			return 1;
	}

	return 0;
}

int vehicle_contains_actor ( struct vehicle_info *vehicle, struct actor_info *actor )
{
	struct actor_info	*passengers[VEHICLE_MAX_PASSENGERS];
	struct actor_info	*temp;

	if ( actor == NULL )
		return NULL;

	memcpy( passengers, vehicle->passengers, sizeof(uint32_t) * VEHICLE_MAX_PASSENGERS );

	int i;
	for ( i = 0; i < VEHICLE_MAX_PASSENGERS; i++ )
	{
		temp = passengers[i];
		if ( temp == actor )
			return 1;
	}

	return NULL;
}

void vehicle_state_store ( const struct vehicle_info *info, struct vehicle_state *state )
{
	if ( info == NULL )
		return;

	vect3_copy( info->speed, state->speed );
	vect3_copy( info->spin, state->spin );
	matrix_copy( info->base.matrix, state->matrix );

	if ( !set.trailer_support )
		return;

	state->trailerPtr = info->trailer;
	state->trailer = new struct vehicle_state;
	vehicle_state_store( state->trailerPtr, state->trailer );		/* XXX - recursion sucks */
}

void vehicle_state_restore ( struct vehicle_info *info, const struct vehicle_state *state )
{
	if ( info == NULL )
		return;

	vect3_copy( state->speed, info->speed );
	vect3_copy( state->spin, info->spin );
	matrix_copy( state->matrix, info->base.matrix );

	if ( set.trailer_support )
		vehicle_state_restore( state->trailerPtr, state->trailer ); /* XXX - recursion sucks */
}

/* prevents the vehicle from going below a certain point. doesn't always work
   for some reason ;) */
void vehicle_prevent_below_height ( struct vehicle_info *info, float height )
{
	float	z = info->base.matrix[4 * 3 + 2];
	float	zspeed = info->speed[2];	/* XXX: this is wrong */

	if ( z < height || (zspeed < 0.0f && (z + zspeed) < height) )
	{
		float	vect[3] = { info->base.matrix[4 * 3 + 0], info->base.matrix[4 * 3 + 1], height };

		vehicle_detachables_teleport( info, &info->base.matrix[4 * 3], vect );

		vect3_copy( vect, &info->base.matrix[4 * 3] );

		info->speed[2] = 0.05f;
		vect3_zero( info->spin );
	}
}

/* returns the id of the next vehicle or actor. Scans in direction <dir> (1, -1)  */
static int __generic_find ( int do_vehicles, int id, int dir, int flags )
{
	const struct pool	*pool = do_vehicles ? pool_vehicle : pool_actor;
	int					i, n = id;

	if ( pool_vehicle == NULL )
		return -1;

	/* loop through the vehicle pool until we find a vehicle */
	for ( i = 0; i < pool->size; i++ )
	{
		n += dir;

		if ( n > pool->size - 1 )
			n = 0;
		if ( n < 0 )
			n = pool->size - 1;

		if ( do_vehicles )
		{
			if ( vehicle_info_get(n, flags) != NULL )
			{
				if ( vehicle_info_get(n, flags)->base.matrix != vehicle_info_get(VEHICLE_SELF, 0)->base.matrix )
					return n;
			}
		}
		else
		{
			if ( actor_info_get(n, flags) != NULL )
			{
				if ( actor_info_get(n, flags)->base.matrix != actor_info_get(ACTOR_SELF, 0)->base.matrix )
					return n;
			}
		}
	}

	return -1;
}

int vehicle_find ( int id, int dir, int flags )
{
	return __generic_find( 1, id, dir, flags );
}

int actor_find ( int id, int dir, int flags )
{
	return __generic_find( 0, id, dir, flags );
}

/* XXX make these generic */

/* returns the id of the nearest vehicle */
int vehicle_find_nearest ( int flags )
{
	struct vehicle_info		*vehicle_self, *info;
	const struct actor_info *actor_self;
	float					dist = -1.0f;
	int						id_nearest = -1;

	if ( pool_vehicle == NULL )
		return -1;
	if ( (actor_self = actor_info_get(ACTOR_SELF, 0)) == NULL )
		return -1;
	vehicle_self = vehicle_info_get( VEHICLE_SELF, 0 );

	for ( int n = 0; n < pool_vehicle->size; n++ )
	{
		float	vect[3];
		if ( (info = vehicle_info_get(n, flags)) == NULL )
			continue;

		// if SAMP is loaded, check if the vehicle is streamed in
		if ( g_SAMP != NULL )
		{
			int iVehicleSAMPID = getSAMPVehicleIDFromGTAVehicle( info );
			if ( isBadSAMPVehicleID(iVehicleSAMPID) )
				continue;
		}

		// don't include our vehicle or its trailer
		if ( vehicle_self != NULL )
		{
			if ( vehicle_self->base.matrix == info->base.matrix )
				continue;
			if ( vehicle_self->trailer == info )
				continue;
		}

		// filter vehicle by flags function
		if ( vehicle_filter_flags(info, flags) == 0 )
			continue;

		// looks like we're all good, now where the heck is we all at?
		vect3_vect3_sub( &actor_self->base.matrix[4 * 3], &info->base.matrix[4 * 3], vect );
		vect[2] += 2.0f;
		if ( dist < 0.0f || vect3_length(vect) < dist )
		{
			dist = vect3_length( vect );
			id_nearest = n;
		}
	}

	return id_nearest;
}

int vehicle_filter_flags ( vehicle_info *info, int flags )
{
	// filters
	int isOccupied = 0, seat;
	if ( (flags & VEHICLE_NOTBURNING) && info->burn_timer > 0.0f )
		return 0;
	if ( (flags & VEHICLE_ALIVE) && (info->hitpoints < 250.0f && info->burn_timer == 0.0f) )
		return 0;
	if ( (flags & VEHICLE_OCCUPIED) || (flags & VEHICLE_EMPTY) )
	{
		const struct vehicle_entry	*vehicle;
		vehicle = gta_vehicle_get_by_id( info->base.model_alt_id );

		const int	seat_count = vehicle->passengers;
		for ( seat = 0; seat < seat_count + 1; seat++ )
		{
			//for (seat = 0; seat <= 7; seat++) {
			if ( info->passengers[seat] != NULL )
			{
				isOccupied = 1;
			}
		}

		if ( (flags & VEHICLE_OCCUPIED) && isOccupied == 0 )
			return 0;
		else if ( (flags & VEHICLE_EMPTY) && isOccupied == 1 )
			return 1;
	}

	// nothing was filtered out, return 1
	return 1;
}

/* returns the id of the nearest actor */
int actor_find_nearest ( int flags )
{
	return actor_find_nearest_ex(flags, [](actor_info *){ return true; });
}

int actor_find_nearest_ex(int flags, std::function<bool(actor_info *)> pred)
{
	const struct actor_info *self;

	if ( pool_actor == NULL )
		return -1;

	if ( (self = actor_info_get(ACTOR_SELF, 0)) == NULL )
		return -1;

	struct actor_info		*info;
	float					vect[3];
	float					dist = -1.0f;
	int						id_nearest = -1;
	int						n;

	for ( n = 0; n < pool_actor->size; n++ )
	{
		if ( (info = actor_info_get(n, flags)) == NULL )
			continue;

		if ( self->base.matrix == info->base.matrix )
			continue;

		if (!pred(info))
			continue;

		vect3_vect3_sub( &self->base.matrix[4 * 3], &info->base.matrix[4 * 3], vect );

		if ( dist < 0.0f || vect3_length(vect) < dist )
		{
			dist = vect3_length( vect );
			id_nearest = n;
		}
	}

	return id_nearest;
}

struct vehicle_info *actor_vehicle_get ( const struct actor_info *info )
{
	if ( info->state == ACTOR_STATE_DRIVING && !isBadPtr_GTA_pVehicle(info->vehicle) )
		return info->vehicle;

	return NULL;
}

// (MTA10/multiplayer_sa/CMultiplayerSA.cpp)
void SetCloudsEnabled ( int iEnabled )
{
	//volumetric clouds
	if ( iEnabled )
		memcpy_safe( (void *)0x716380, "\xA1", 1 );
	else
		memcpy_safe( (void *)0x716380, "\xC3", 1 );

	// foggy weather clouds (above ground)
	if ( iEnabled )
		memcpy_safe( (void *)0x716C90, "\xD9", 1 );
	else
		memcpy_safe( (void *)0x716C90, "\xC3", 1 );

	// normal clouds
	//0071395A     90             NOP
	if ( iEnabled )
		memcpy_safe( (void *)0x713950, "\x83", 1 );
	else
		memcpy_safe( (void *)0x713950, "\xC3", 1 );

	// plane trails (not really clouds, but they're sort of vapour)
	if ( iEnabled )
		memcpy_safe( (void *)0x717180, "\x83\xEC\x08", 3 );
	else
		memcpy_safe( (void *)0x717180, "\xC2\x04\x00", 3 );
}

// ---------------------------------------------------------------------------------------
// ped animations
bool pPedSelf_setMoveAnimation__array ( int move_animations__arrayId )
{
	traceLastFunc( "pPedSelf_setMoveAnimation__array()" );

	// should be an array id
	if ( move_animations__arrayId < 0 || move_animations__arrayId >= MOVE_ANIMATIONS_COUNT
		|| pPedSelf == NULL )
		return false;

    CPlayerPedSA* pLocalPlayerSA = dynamic_cast < CPlayerPedSA* > ( pPedSelf );
	if ( pLocalPlayerSA == NULL )
			return false;

	if ( pLocalPlayerSA->GetMoveAnim() != move_animations[move_animations__arrayId].moveStyleId )
		pLocalPlayerSA->SetMoveAnim( move_animations[move_animations__arrayId].moveStyleId );
	//pPedSelf->GetPedInterface()->iMoveAnimGroup = move_animations[move_animations__arrayId].moveStyleId;
	return true;
}

bool isMoveAnimationIdValid ( int iAnimationID )
{
	// id invalid when < lowest id or > highest id (move_animations is sorted by the ID)
	if ( iAnimationID < move_animations[0].moveStyleId ||
		iAnimationID > move_animations[MOVE_ANIMATIONS_COUNT-1].moveStyleId )
		return false;

	for ( int i = 0; i < MOVE_ANIMATIONS_COUNT; i++ )
	{
		if ( move_animations[i].moveStyleId == iAnimationID )
			return true;
	}
	return false;
}

bool pPedSelf_setMoveAnimation ( int iAnimationID )
{
	traceLastFunc( "pPedSelf_setMoveAnimation()" );

	// would crash with invalid animation ID
	if ( pPedSelf == NULL || !isMoveAnimationIdValid(iAnimationID) )
		return false;

	CPlayerPedSA* pLocalPlayerSA = dynamic_cast < CPlayerPedSA* > ( pPedSelf );
	if ( pLocalPlayerSA == NULL )
		return false;

	if ( (int)pLocalPlayerSA->GetMoveAnim() != iAnimationID )
		pLocalPlayerSA->SetMoveAnim( (eMoveAnim)iAnimationID );
	return true;
}

// ---------------------------------------------------------------------------------------
// new vehicle types and upgrades
bool vehicle_iModelID_IsValid ( int iModelID )
{
	return iModelID >= 400 && iModelID <= 611;
}

bool vehicle_upgrade_iModelID_IsValid ( int iModelID )
{
	return iModelID >= 1000 && iModelID <= 1193;
}

eClientVehicleType GetVehicleType ( int iModelID )
{
	traceLastFunc( "GetVehicleType()" );

	// Valid vehicle model id?
	if ( vehicle_iModelID_IsValid(iModelID) )
	{
		// Return the appropriate type
		if ( GTAfunc_vehicle_iModelID_IsCar(iModelID) )
			return CLIENTVEHICLE_CAR;
		if ( GTAfunc_vehicle_iModelID_IsBike(iModelID) )
			return CLIENTVEHICLE_BIKE;
		if ( GTAfunc_vehicle_iModelID_IsPlane(iModelID) )
			return CLIENTVEHICLE_PLANE;
		if ( GTAfunc_vehicle_iModelID_IsHeli(iModelID) )
			return CLIENTVEHICLE_HELI;
		if ( GTAfunc_vehicle_iModelID_IsBoat(iModelID) )
			return CLIENTVEHICLE_BOAT;
		if ( GTAfunc_vehicle_iModelID_IsQuadBike(iModelID) )
			return CLIENTVEHICLE_QUADBIKE;
		if ( GTAfunc_vehicle_iModelID_IsBmx(iModelID) )
			return CLIENTVEHICLE_BMX;
		if ( GTAfunc_vehicle_iModelID_IsMonsterTruck(iModelID) )
			return CLIENTVEHICLE_MONSTERTRUCK;
		if ( GTAfunc_vehicle_iModelID_IsTrailer(iModelID) )
			return CLIENTVEHICLE_TRAILER;
		if ( GTAfunc_vehicle_iModelID_IsTrain(iModelID) )
			return CLIENTVEHICLE_TRAIN;
	}

	// Invalid vehicle id or some other error
	return CLIENTVEHICLE_NONE;
}

bool isUpgradeCompatible ( int iModelID, vehicle_info *vinfo )
{
	traceLastFunc( "isUpgradeCompatible()" );

	// get vehicle model
	int					usModel = vinfo->base.model_alt_id;

	// get vehicle type
	eClientVehicleType	vehicleType = GetVehicleType( usModel );

	// no upgrades for you!
	if ( vehicleType == CLIENTVEHICLE_BOAT
	 ||	 vehicleType == CLIENTVEHICLE_TRAIN
	 ||	 vehicleType == CLIENTVEHICLE_HELI
	 ||	 vehicleType == CLIENTVEHICLE_PLANE
	 ||	 vehicleType == CLIENTVEHICLE_BIKE
	 ||	 vehicleType == CLIENTVEHICLE_BMX ) return false;

	// shorter upgrade model id variable
	unsigned short	us = iModelID;

	// these can go on any vehicle that hasn't been filtered out yet
	if ( us == VEHICLEUPGRADE_NITRO_5X || us == VEHICLEUPGRADE_NITRO_2X || us == VEHICLEUPGRADE_NITRO_10X )
		return true;

	// hydraulics on the rest except for monster trucks
	if ( us == VEHICLEUPGRADE_HYDRAULICS && vehicleType != CLIENTVEHICLE_MONSTERTRUCK )
		return true;

	// Wheels should be compatible with any car
	if ( us == 1025
	 ||	 us == 1073
	 ||	 us == 1074
	 ||	 us == 1075
	 ||	 us == 1076
	 ||	 us == 1077
	 ||	 us == 1078
	 ||	 us == 1079
	 ||	 us == 1080
	 ||	 us == 1081
	 ||	 us == 1082
	 ||	 us == 1083
	 ||	 us == 1084
	 ||	 us == 1085
	 ||	 us == 1096
	 ||	 us == 1097
	 ||	 us == 1098 ) return true;

	switch ( usModel )
	{
	case 400:
		return us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1018
		||	us == 1013
		||	us == 1024
		||	us == 1008
		||	us == 1009
		||	us == 1010;

	case 401:
		return us == 1005
		||	us == 1004
		||	us == 1142
		||	us == 1143
		||	us == 1144
		||	us == 114
		||	us == 1020
		||	us == 1019
		||	us == 1013
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1001
		||	us == 1003
		||	us == 1017
		||	us == 1007;

	case 402:
		return us == 1009 || us == 1010;

	case 404:
		return us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1013
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1002
		||	us == 1016
		||	us == 1000
		||	us == 1017
		||	us == 1007;

	case 405:
		return us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1001
		||	us == 1014
		||	us == 1023
		||	us == 1000;

	case 409:
		return us == 1009;

	case 410:
		return us == 1019
		||	us == 1021
		||	us == 1020
		||	us == 1013
		||	us == 1024
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1001
		||	us == 1023
		||	us == 1003
		||	us == 1017
		||	us == 1007;

	case 411:
		return us == 1008 || us == 1009 || us == 1010;

	case 412:
		return us == 1008 || us == 1009 || us == 1010;

	case 415:
		return us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1001
		||	us == 1023
		||	us == 1003
		||	us == 1017
		||	us == 1007;

	case 418:
		return us == 1020
		||	us == 1021
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1002
		||	us == 1016;

	case 419:
		return us == 1008 || us == 1009 || us == 1010;

	case 420:
		return us == 1005
		||	us == 1004
		||	us == 1021
		||	us == 1019
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1001
		||	us == 1003;

	case 421:
		return us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1014
		||	us == 1023
		||	us == 1016
		||	us == 1000;

	case 422:
		return us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1013
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1017
		||	us == 1007;

	case 426:
		return us == 1005
		||	us == 1004
		||	us == 1021
		||	us == 1019
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1001
		||	us == 1003;

	case 429:
		return us == 1008 || us == 1009 || us == 1010;

	case 436:
		return us == 1020
		||	us == 1021
		||	us == 1022
		||	us == 1019
		||	us == 1013
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1001
		||	us == 1003
		||	us == 1017
		||	us == 1007;

	case 438:
		return us == 1008 || us == 1009 || us == 1010;

	case 439:
		return us == 1003
		||	us == 1023
		||	us == 1001
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1017
		||	us == 1007
		||	us == 1142
		||	us == 1143
		||	us == 1144
		||	us == 1145
		||	us == 1013;

	case 442:
		return us == 1008 || us == 1009 || us == 1010;

	case 445:
		return us == 1008 || us == 1009 || us == 1010;

	case 451:
		return us == 1008 || us == 1009 || us == 1010;

	case 458:
		return us == 1008 || us == 1009 || us == 1010;

	case 466:
		return us == 1008 || us == 1009 || us == 1010;

	case 467:
		return us == 1008 || us == 1009 || us == 1010;

	case 474:
		return us == 1008 || us == 1009 || us == 1010;

	case 475:
		return us == 1008 || us == 1009 || us == 1010;

	case 477:
		return us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1017
		||	us == 1007;

	case 478:
		return us == 1005
		||	us == 1004
		||	us == 1012
		||	us == 1020
		||	us == 1021
		||	us == 1022
		||	us == 1013
		||	us == 1024
		||	us == 1008
		||	us == 1009
		||	us == 1010;

	case 479:
		return us == 1008 || us == 1009 || us == 1010;

	case 480:
		return us == 1008 || us == 1009 || us == 1010;

	case 489:
		return us == 1005
		||	us == 1004
		||	us == 1020
		||	us == 1019
		||	us == 1018
		||	us == 1013
		||	us == 1024
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1002
		||	us == 1016
		||	us == 1000;

	case 490:
		return us == 1002 || us == 1016 || us == 1000 || us == 1020 || us == 1021 || us == 1019;

	case 491:
		return us == 1142
		||	us == 1143
		||	us == 1144
		||	us == 1145
		||	us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1014
		||	us == 1023
		||	us == 1003
		||	us == 1017
		||	us == 1007;

	case 492:
		return us == 1005
		||	us == 1004
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1016
		||	us == 1000;

	case 496:
		return us == 1006
		||	us == 1017
		||	us == 1007
		||	us == 1011
		||	us == 1019
		||	us == 1023
		||	us == 1001
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1003
		||	us == 1002
		||	us == 1142
		||	us == 1143
		||	us == 1020;

	case 500:
		return us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1013
		||	us == 1024
		||	us == 1008
		||	us == 1009
		||	us == 1010;

	case 505:
		return us == 1005
		||	us == 1004
		||	us == 1020
		||	us == 1019
		||	us == 1018
		||	us == 1013
		||	us == 1024
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1002
		||	us == 1016
		||	us == 1000;

	case 506:
		return us == 1009;

	case 507:
		return us == 1008 || us == 1009 || us == 1010;

	case 516:
		return us == 1004
		||	us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1002
		||	us == 1015
		||	us == 1016
		||	us == 1000
		||	us == 1017
		||	us == 1007;

	case 517:
		return us == 1142
		||	us == 1143
		||	us == 1144
		||	us == 1145
		||	us == 1020
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1002
		||	us == 1023
		||	us == 1016
		||	us == 1003
		||	us == 1017
		||	us == 1007;

	case 518:
		return us == 1005
		||	us == 1142
		||	us == 1143
		||	us == 1144
		||	us == 1145
		||	us == 1020
		||	us == 1018
		||	us == 1013
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1001
		||	us == 1023
		||	us == 1003
		||	us == 1017
		||	us == 1007;

	case 526:
		return us == 1008 || us == 1009 || us == 1010;

	case 527:
		return us == 1021
		||	us == 1020
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1001
		||	us == 1014
		||	us == 1015
		||	us == 1017
		||	us == 1007;

	case 529:
		return us == 1012
		||	us == 1011
		||	us == 1020
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1001
		||	us == 1023
		||	us == 1003
		||	us == 1017
		||	us == 1007;

	case 533:
		return us == 1008 || us == 1009 || us == 1010;

	case 534:
		return us == 1126
		||	us == 1127
		||	us == 1179
		||	us == 1185
		||	us == 1100
		||	us == 1123
		||	us == 1125
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1180
		||	us == 1178
		||	us == 1101
		||	us == 1122
		||	us == 1124
		||	us == 1106;

	case 535:
		return us == 1109
		||	us == 1110
		||	us == 1113
		||	us == 1114
		||	us == 1115
		||	us == 1116
		||	us == 1117
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1120
		||	us == 1118
		||	us == 1121
		||	us == 1119;

	case 536:
		return us == 1104
		||	us == 1105
		||	us == 1182
		||	us == 1181
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1184
		||	us == 1183
		||	us == 1128
		||	us == 1103
		||	us == 1107
		||	us == 1108;

	case 540:
		return us == 1004
		||	us == 1142
		||	us == 1143
		||	us == 1144
		||	us == 1145
		||	us == 1020
		||	us == 1019
		||	us == 1018
		||	us == 1024
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1001
		||	us == 1023
		||	us == 1017
		||	us == 1007;

	case 541:
		return us == 1008 || us == 1009 || us == 1010;

	case 542:
		return us == 1144
		||	us == 1145
		||	us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1014
		||	us == 1015;

	case 545:
		return us == 1008 || us == 1009 || us == 1010;

	case 546:
		return us == 1004
		||	us == 1142
		||	us == 1143
		||	us == 1144
		||	us == 1145
		||	us == 1019
		||	us == 1018
		||	us == 1024
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1002
		||	us == 1001
		||	us == 1023
		||	us == 1017
		||	us == 1007;

	case 547:
		return us == 1142
		||	us == 1143
		||	us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1016
		||	us == 1003
		||	us == 1000;

	case 549:
		return us == 1012
		||	us == 1011
		||	us == 1142
		||	us == 1143
		||	us == 1144
		||	us == 1145
		||	us == 1020
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1001
		||	us == 1023
		||	us == 1003
		||	us == 1017
		||	us == 1007;

	case 550:
		return us == 1005
		||	us == 1004
		||	us == 1142
		||	us == 1143
		||	us == 1144
		||	us == 1145
		||	us == 1020
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1001
		||	us == 1023
		||	us == 1003;

	case 551:
		return us == 1005
		||	us == 1020
		||	us == 1021
		||	us == 1019
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1002
		||	us == 1023
		||	us == 1016
		||	us == 1003;

	case 555:
		return us == 1008 || us == 1009 || us == 1010;

	case 558:
		return us == 1092
		||	us == 1089
		||	us == 1166
		||	us == 1165
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1168
		||	us == 1167
		||	us == 1088
		||	us == 1091
		||	us == 1164
		||	us == 1163
		||	us == 1094
		||	us == 1090
		||	us == 1095
		||	us == 1093;

	case 559:
		return us == 1065
		||	us == 1066
		||	us == 1160
		||	us == 1173
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1159
		||	us == 1161
		||	us == 1162
		||	us == 1158
		||	us == 1067
		||	us == 1068
		||	us == 1071
		||	us == 1069
		||	us == 1072
		||	us == 1070
		||	us == 1009;

	case 560:
		return us == 1028
		||	us == 1029
		||	us == 1169
		||	us == 1170
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1141
		||	us == 1140
		||	us == 1032
		||	us == 1033
		||	us == 1138
		||	us == 1139
		||	us == 1027
		||	us == 1026
		||	us == 1030
		||	us == 1031;

	case 561:
		return us == 1064
		||	us == 1059
		||	us == 1155
		||	us == 1157
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1154
		||	us == 1156
		||	us == 1055
		||	us == 1061
		||	us == 1058
		||	us == 1060
		||	us == 1062
		||	us == 1056
		||	us == 1063
		||	us == 1057;

	case 562:
		return us == 1034
		||	us == 1037
		||	us == 1171
		||	us == 1172
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1149
		||	us == 1148
		||	us == 1038
		||	us == 1035
		||	us == 1147
		||	us == 1146
		||	us == 1040
		||	us == 1036
		||	us == 1041
		||	us == 1039;

	case 565:
		return us == 1046
		||	us == 1045
		||	us == 1153
		||	us == 1152
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1150
		||	us == 1151
		||	us == 1054
		||	us == 1053
		||	us == 1049
		||	us == 1050
		||	us == 1051
		||	us == 1047
		||	us == 1052
		||	us == 1048;

	case 566:
		return us == 1008 || us == 1009 || us == 1010;

	case 567:
		return us == 1129
		||	us == 1132
		||	us == 1189
		||	us == 1188
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1187
		||	us == 1186
		||	us == 1130
		||	us == 1131
		||	us == 1102
		||	us == 1133;

	case 575:
		return us == 1044
		||	us == 1043
		||	us == 1174
		||	us == 1175
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1176
		||	us == 1177
		||	us == 1099
		||	us == 1042;

	case 576:
		return us == 1136
		||	us == 1135
		||	us == 1191
		||	us == 1190
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1192
		||	us == 1193
		||	us == 1137
		||	us == 1134;

	case 579:
		return us == 1008 || us == 1009 || us == 1010;

	case 580:
		return us == 1020
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1001
		||	us == 1023
		||	us == 1017
		||	us == 1007;

	case 585:
		return us == 1142
		||	us == 1143
		||	us == 1144
		||	us == 1145
		||	us == 1020
		||	us == 1019
		||	us == 1018
		||	us == 1013
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1001
		||	us == 1023
		||	us == 1003
		||	us == 1017
		||	us == 1007;

	case 587:
		return us == 1008 || us == 1009 || us == 1010;

	case 589:
		return us == 1005
		||	us == 1004
		||	us == 1144
		||	us == 1145
		||	us == 1020
		||	us == 1018
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1024
		||	us == 1013
		||	us == 1006
		||	us == 1016
		||	us == 1000
		||	us == 1017
		||	us == 1007;

	case 600:
		return us == 1005
		||	us == 1004
		||	us == 1020
		||	us == 1022
		||	us == 1018
		||	us == 1013
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1017
		||	us == 1007;

	case 602:
		return us == 1008 || us == 1009 || us == 1010;

	case 603:
		return us == 1144
		||	us == 1145
		||	us == 1142
		||	us == 1143
		||	us == 1020
		||	us == 1019
		||	us == 1018
		||	us == 1024
		||	us == 1008
		||	us == 1009
		||	us == 1010
		||	us == 1006
		||	us == 1001
		||	us == 1023
		||	us == 1017
		||	us == 1007;
	}

	// no mod for you
	return false;
}

bool GetSlotFromUpgrade ( int us, int &ucSlot )
{
	traceLastFunc( "GetSlotFromUpgrade()" );

	// TODO: 1013, 1024, 1109, 1110
	if ( us == 1000
	 ||	 us == 1001
	 ||	 us == 1002
	 ||	 us == 1003
	 ||	 us == 1014 /* spoiler */
	 ||	 us == 1015
	 ||	 us == 1016
	 ||	 us == 1023
	 ||	 us == 1049
	 ||	 us == 1050
	 ||	 us == 1058
	 ||	 us == 1060
	 ||	 us == 1138
	 ||	 us == 1139
	 ||	 us == 1146
	 ||	 us == 1147
	 ||	 us == 1158
	 ||	 us == 1162
	 ||	 us == 1163
	 ||	 us == 1164 )
	{
		ucSlot = 2;
		return true;
	}

	if ( us == 1004 || us == 1005 ) // vent
	{
		ucSlot = 1;
		return true;
	}

	if ( us == 1006
	 ||	 us == 1032
	 ||	 us == 1033
	 ||	 us == 1035
	 ||	 us == 1038 /* roof */
	 ||	 us == 1053
	 ||	 us == 1054
	 ||	 us == 1055
	 ||	 us == 1061
	 ||	 us == 1067
	 ||	 us == 1068
	 ||	 us == 1088
	 ||	 us == 1091
	 ||	 us == 1103
	 ||	 us == 1128
	 ||	 us == 1130
	 ||	 us == 1131 )
	{
		ucSlot = 7;
		return true;
	}

	if ( us == 1007
	 ||	 us == 1017
	 ||	 us == 1026
	 ||	 us == 1027
	 ||	 us == 1030 /* sideskirt */
	 ||	 us == 1031
	 ||	 us == 1036
	 ||	 us == 1039
	 ||	 us == 1040
	 ||	 us == 1041
	 ||	 us == 1042
	 ||	 us == 1047
	 ||	 us == 1048
	 ||	 us == 1051
	 ||	 us == 1052
	 ||	 us == 1056
	 ||	 us == 1057
	 ||	 us == 1062
	 ||	 us == 1063
	 ||	 us == 1069
	 ||	 us == 1070
	 ||	 us == 1071
	 ||	 us == 1072
	 ||	 us == 1090
	 ||	 us == 1093
	 ||	 us == 1094
	 ||	 us == 1095
	 ||	 us == 1099
	 ||	 us == 1101
	 ||	 us == 1102
	 ||	 us == 1106
	 ||	 us == 1107
	 ||	 us == 1108
	 ||	 us == 1118
	 ||	 us == 1119
	 ||	 us == 1120
	 ||	 us == 1121
	 ||	 us == 1122
	 ||	 us == 1124
	 ||	 us == 1133
	 ||	 us == 1134
	 ||	 us == 1137 )
	{
		ucSlot = 3;
		return true;
	}

	if ( us == 1008 || us == 1009 || us == 1010 )	// nitro
	{
		ucSlot = 8;
		return true;
	}

	if ( us == 1011
	 ||	 us == 1012
	 ||	 us == 1111
	 ||	 us == 1112
	 ||	 us == 1142		/* bonet */
	 ||	 us == 1143
	 ||	 us == 1144
	 ||	 us == 1145 )
	{
		ucSlot = 0;
		return true;
	}

	if ( us == 1018
	 ||	 us == 1019
	 ||	 us == 1020
	 ||	 us == 1021
	 ||	 us == 1022		/* exhaust */
	 ||	 us == 1028
	 ||	 us == 1029
	 ||	 us == 1034
	 ||	 us == 1037
	 ||	 us == 1043
	 ||	 us == 1044
	 ||	 us == 1045
	 ||	 us == 1046
	 ||	 us == 1059
	 ||	 us == 1064
	 ||	 us == 1065
	 ||	 us == 1066
	 ||	 us == 1089
	 ||	 us == 1092
	 ||	 us == 1104
	 ||	 us == 1105
	 ||	 us == 1113
	 ||	 us == 1114
	 ||	 us == 1126
	 ||	 us == 1127
	 ||	 us == 1129
	 ||	 us == 1132
	 ||	 us == 1135
	 ||	 us == 1136 )
	{
		ucSlot = 13;
		return true;
	}

	if ( us == 1025
	 ||	 us == 1073
	 ||	 us == 1074
	 ||	 us == 1075
	 ||	 us == 1076		/* wheels */
	 ||	 us == 1077
	 ||	 us == 1078
	 ||	 us == 1079
	 ||	 us == 1080
	 ||	 us == 1081
	 ||	 us == 1082
	 ||	 us == 1083
	 ||	 us == 1084
	 ||	 us == 1085
	 ||	 us == 1096
	 ||	 us == 1097
	 ||	 us == 1098 )
	{
		ucSlot = 12;
		return true;
	}

	if ( us == 1086 )	// stereo
	{
		ucSlot = 10;
		return true;
	}

	if ( us == 1087 )	// hydraulics
	{
		ucSlot = 9;
		return true;
	}

	if ( us == 1100 || us == 1123 || us == 1125 )	// misc
	{
		ucSlot = 16;
		return true;
	}

	if ( us == 1115 || us == 1116 ) // front bullbars
	{
		ucSlot = 4;
		return true;
	}

	if ( us == 1117
	 ||	 us == 1152
	 ||	 us == 1153
	 ||	 us == 1155
	 ||	 us == 1157 /* front bumper */
	 ||	 us == 1160
	 ||	 us == 1165
	 ||	 us == 1166
	 ||	 us == 1169
	 ||	 us == 1170
	 ||	 us == 1171
	 ||	 us == 1172
	 ||	 us == 1173
	 ||	 us == 1174
	 ||	 us == 1175
	 ||	 us == 1179
	 ||	 us == 1181
	 ||	 us == 1182
	 ||	 us == 1185
	 ||	 us == 1188
	 ||	 us == 1189
	 ||	 us == 1190
	 ||	 us == 1191 )
	{
		ucSlot = 14;
		return true;
	}

	if ( us == 1140
	 ||	 us == 1141
	 ||	 us == 1148
	 ||	 us == 1149
	 ||	 us == 1150 /* rear bumper */
	 ||	 us == 1151
	 ||	 us == 1154
	 ||	 us == 1156
	 ||	 us == 1159
	 ||	 us == 1161
	 ||	 us == 1167
	 ||	 us == 1168
	 ||	 us == 1176
	 ||	 us == 1177
	 ||	 us == 1178
	 ||	 us == 1180
	 ||	 us == 1183
	 ||	 us == 1184
	 ||	 us == 1186
	 ||	 us == 1187
	 ||	 us == 1192
	 ||	 us == 1193 )
	{
		ucSlot = 15;
		return true;
	}

	return false;
}

vehicle_upgrade_info get_cveh_upgrade_info ( int iModelID, int &iUpgradeInfoID )
{
	if ( vehicle_upgrade_iModelID_IsValid(iModelID) )
	{
		for ( int i = 0; i < VEHICLE_UPGRADES_COUNT; i++ )
		{
			if ( cveh_upgrade_info[i].iModelID == iModelID )
			{
				iUpgradeInfoID = i;
				return cveh_upgrade_info[i];
			}
		}
	}

	vehicle_upgrade_info	invalid = { -1, 0, 0 };
	return invalid;
}

void vehicle_addUpgrade ( vehicle_info *vinfo, int iModelID )
{
	traceLastFunc( "vehicle_addUpgrade()" );
	if ( vinfo == NULL )
		return;

	// filter out the bad mods
	if ( iModelID >= 1000 && iModelID <= 1193 )
	{
		// is the mod compatible with my ride? (upgrade model, vehicle_info)
		if ( !isUpgradeCompatible(iModelID, vinfo) )
			return;

		// is the mod already loaded?
		if ( !GTAfunc_isModelLoaded(iModelID) )
		{
			// request model to load broh
			GTAfunc_requestModelLoad( iModelID );

			// load currently requested models broh
			GTAfunc_loadRequestedModels();
		}

		// wait for it to load
		while ( !GTAfunc_isModelLoaded(iModelID) )
			Sleep( 10 );

		// put a mod in my ride broh
		GTAfunc_requestAnyVehicleUpgrade( vinfo, iModelID );

		// tell everyone else we got a mod broh
		if ( g_SAMP != NULL )
		{
			sendSCMEvent( 2, g_Players->pLocalPlayer->sCurrentVehicleID, iModelID, 0 );
		}
	}
}

//#define EVENT_TYPE_PAINTJOB			1
//#define EVENT_TYPE_CARCOMPONENT		2
//#define EVENT_TYPE_CARCOLOR			3

//#define EVENT_ENTEREXIT_MODSHOP		4
int vehicle_getPaintJob ( vehicle_info *vinfo )
{
	traceLastFunc( "vehicle_getPaintJob()" );
	if ( vinfo == NULL )
		return -1;

	int iRemap = GTAfunc_vehicle_getRemapIndex( vinfo );
	int iReturn = ( iRemap == -1 ) ? 3 : iRemap;
	return iReturn;
}

void vehicle_setPaintJob ( vehicle_info *vinfo, unsigned char new_paintjob )
{
	traceLastFunc( "vehicle_setPaintJob()" );
	if ( vinfo == NULL )
		return;

	int current_paintjob = vehicle_getPaintJob( vinfo );
	if ( new_paintjob != current_paintjob && new_paintjob <= 4 )
	{
		GTAfunc_vehicle_setRemap( vinfo, static_cast<unsigned int>(new_paintjob) );
		if ( g_SAMP != NULL )
		{
			sendSCMEvent( 1, g_Players->pLocalPlayer->sCurrentVehicleID, new_paintjob, 0 );
		}
	}
}

int vehicle_getColor0 ( vehicle_info *vinfo )
{
	if ( vinfo == NULL )
		return -1;
	return vinfo->color[0];
}

int vehicle_getColor1 ( vehicle_info *vinfo )
{
	if ( vinfo == NULL )
		return -1;
	return vinfo->color[1];
}

void vehicle_setColor0 ( vehicle_info *vinfo, int new_color )
{
	traceLastFunc( "vehicle_setColor0()" );
	if ( vinfo == NULL )
		return;

	vinfo->color[0] = new_color;
	if ( g_SAMP != NULL )
	{
		uint16_t sampVeh = g_Players->pLocalPlayer->sCurrentVehicleID;
		if (!isBadSAMPVehicleID(sampVeh))
		{
			sendSCMEvent(3, sampVeh, new_color, vinfo->color[1]);
			if (g_Vehicles->pSAMP_Vehicle[sampVeh] != nullptr)
			{
				g_Vehicles->pSAMP_Vehicle[sampVeh]->byteColor[0] = new_color;
			}
		}
	}
}

void vehicle_setColor1 ( vehicle_info *vinfo, int new_color )
{
	traceLastFunc( "vehicle_setColor1()" );
	if ( vinfo == NULL )
		return;

	vinfo->color[1] = new_color;
	if ( g_SAMP != NULL )
	{
		uint16_t sampVeh = g_Players->pLocalPlayer->sCurrentVehicleID;
		if (!isBadSAMPVehicleID(sampVeh))
		{
			sendSCMEvent(3, sampVeh, vinfo->color[0], new_color);
			if (g_Vehicles->pSAMP_Vehicle[sampVeh] != nullptr)
			{
				g_Vehicles->pSAMP_Vehicle[sampVeh]->byteColor[1] = new_color;
			}
		}
	}
}

RwColor getVehicleColorRGB(unsigned int index)
{
	static RwColor *colorTable = nullptr;
	if (colorTable == nullptr)
	{
		memcpy_safe(&colorTable, (void *)0x4C8390, 4);
	}
	return colorTable[index];
}

// ---------------------------------------------------------------------------------------
// ---------------------------------------------------------------------------------------

// ---------------------------------------------------------------------------------------
static int __page_size_get ( void )
{
	static int	page_size = -1;
	SYSTEM_INFO si;

	if ( page_size == -1 )
	{
		GetSystemInfo( &si );
		page_size = (int)si.dwPageSize;
	}

	return page_size;
}

static int __page_write ( void *_dest, const void *_src, uint32_t len )
{
	static int		page_size = __page_size_get();
	uint8_t			*dest = (uint8_t *)_dest;
	const uint8_t	*src = (const uint8_t *)_src;
	DWORD			prot_prev = 0;
	int				prot_changed = 0;
	int				ret = 1;

	while ( len > 0 )
	{
		ret = 1;
		int page_offset = (int)( (UINT_PTR) dest % page_size );
		int page_remain = page_size - page_offset;
		int this_len = len;

		if ( this_len > page_remain )
			this_len = page_remain;

		if ( isBadPtr_writeAny(dest, this_len) )
		{
			if ( !VirtualProtect((void *)dest, this_len, PAGE_EXECUTE_READWRITE, &prot_prev) )
				ret = 0;
			else
				prot_changed = 1;
		}

		if ( ret )
			memcpy( dest, src, this_len );

		if ( prot_changed )
		{
			DWORD	dummy;
			if ( !VirtualProtect((void *)dest, this_len, prot_prev, &dummy) )
				Log( "__page_write() could not restore original permissions for ptr %p", dest );
		}

		dest += this_len;
		src += this_len;
		len -= this_len;
	}

	return ret;
}

static int __page_read ( void *_dest, const void *_src, uint32_t len )
{
	static int	page_size = __page_size_get();
	uint8_t		*dest = (uint8_t *)_dest;
	uint8_t		*src = (uint8_t *)_src;
	DWORD		prot_prev = 0;
	int			prot_changed = 0;
	int			ret = 1;

	while ( len > 0 )
	{
		ret = 1;
		int page_offset = (int)( (UINT_PTR) src % page_size );
		int page_remain = page_size - page_offset;
		int this_len = len;

		if ( this_len > page_remain )
			this_len = page_remain;

		if ( isBadPtr_readAny(src, this_len) )
		{
			if ( !VirtualProtect((void *)src, this_len, PAGE_EXECUTE_READWRITE, &prot_prev) )
				ret = 0;
			else
				prot_changed = 1;
		}

		if ( ret )
			memcpy( dest, src, this_len );
		else
			memset( dest, 0, this_len );

		if ( prot_changed )
		{
			DWORD	dummy;
			if ( !VirtualProtect((void *)src, this_len, prot_prev, &dummy) )
				Log( "__page_read() could not restore original permissions for ptr %p", src );
		}

		dest += this_len;
		src += this_len;
		len -= this_len;
	}

	return ret;
}

int memcpy_safe ( void *_dest, const void *_src, uint32_t len, int check, const void *checkdata )
{
	static int		page_size = __page_size_get();
	static int		recurse_ok = 1;
	uint8_t			buf[4096];
	uint8_t			*dest = (uint8_t *)_dest;
	const uint8_t	*src = (const uint8_t *)_src;
	int				ret = 1;

	if (check && checkdata)
	{
		if (!memcmp_safe(checkdata, _dest, len))
			return 0;
	}

	while ( len > 0 )
	{
		uint32_t	this_len = sizeof( buf );

		if ( this_len > len )
			this_len = len;

		if ( !__page_read(buf, src, this_len) )
			ret = 0;

		if ( !__page_write(dest, buf, this_len) )
			ret = 0;

		len -= this_len;
		src += this_len;
		dest += this_len;
	}

	return ret;
}

int memset_safe ( void *_dest, int c, uint32_t len )
{
	uint8_t *dest = (uint8_t *)_dest;
	uint8_t buf[4096];

	memset( buf, c, (len > 4096) ? 4096 : len );

	for ( ;; )
	{
		if ( len > 4096 )
		{
			if ( !memcpy_safe(dest, buf, 4096) )
				return 0;
			dest += 4096;
			len -= 4096;
		}
		else
		{
			if ( !memcpy_safe(dest, buf, len) )
				return 0;
			break;
		}
	}

	return 1;
}

int memcmp_safe ( const void *_s1, const void *_s2, uint32_t len )
{
	const uint8_t	*s1 = (const uint8_t *)_s1;
	const uint8_t	*s2 = (const uint8_t *)_s2;
	uint8_t			buf[4096];

	for ( ;; )
	{
		if ( len > 4096 )
		{
			if ( !memcpy_safe(buf, s1, 4096) )
				return 0;
			if ( memcmp(buf, s2, 4096) )
				return 0;
			s1 += 4096;
			s2 += 4096;
			len -= 4096;
		}
		else
		{
			if ( !memcpy_safe(buf, s1, len) )
				return 0;
			if ( memcmp(buf, s2, len) )
				return 0;
			break;
		}
	}

	return 1;
}

void *dll_baseptr_get ( const char *dll_name )
{
	return GetModuleHandle( dll_name );
}

void str_split_free ( struct str_split *split )
{
	if ( split != NULL )
	{
		if ( split->str != NULL )
			free( split->str );
		if ( split->argv != NULL )
			free( split->argv );
		free( split );
	}
}

struct str_split *str_split ( const char *str, const char *ch )
{
	struct str_split	*split;
	char				*prev, *next;
	char				*dest;
	void				*tmp;

	/* left trim */
	while ( *str && strchr(ch, *str) != NULL )
		str++;

	split = (struct str_split *)calloc( 1, sizeof(struct str_split) );
	if ( split == NULL )
		return NULL;

	split->str = _strdup( str );
	if ( split->str == NULL )
	{
		free( split );
		return NULL;
	}

	for ( prev = split->str;; prev = next )
	{
		if ( *prev == '"' )
		{
			/* find the ending " */
			for ( dest = next = ++prev; *next; next++ )
			{
				if ( *next == '"' )
				{
					next++;
					break;
				}
				else if ( *next == '\\' && next[1] != 0 )
					*dest++ = *++next;
				else
					*dest++ = *next;
			}

			*dest = 0;
		}
		else
		{
			next = prev;
		}

		/* find next value */
		for ( ; *next && strchr(ch, *next) == NULL; next++ );
		next = *next ? next : NULL;

		if ( (tmp = realloc(split->argv, (split->argc + 1) * sizeof(char *))) == NULL )
			goto out;
		split->argv = (char **)tmp;

		split->argv[split->argc] = prev;
		split->argc++;

		if ( next == NULL )
			break;

		for ( *next++ = 0; *next && strchr(ch, *next) != NULL; next++ );

		if ( *next == 0 )
			break;
	}

	tmp = realloc( split->argv, (split->argc + 1) * sizeof(char *) );
	if ( tmp == NULL )
		goto out;
	split->argv = (char **)tmp;

	split->argv[split->argc] = NULL;

	return split;

out: ;
	str_split_free( split );
	return NULL;
}

size_t strlcpy ( char *dst, const char *src, size_t size )
{
	size_t	len = strlen( src );

	if ( size == 0 )
		return len;

	if ( len >= size )
	{
		size--;
		memcpy( dst, src, size );
		dst[size] = 0;
	}
	else if ( size > 0 )
	{
		strcpy( dst, src );
	}

	return len;
}

size_t strlcat ( char *dst, const char *src, size_t size )
{
	size_t	dlen = strlen( dst );
	size_t	slen = strlen( src );

	if ( size == 0 )
		return dlen + slen;

	if ( dlen + slen >= size )
	{
		size -= dlen - 1;
		memcpy( dst + dlen, src, size );
		dst[dlen + size] = 0;
	}
	else if ( size > 0 )
	{
		strcpy( dst + dlen, src );
	}

	return dlen + slen;
}

bool findstrinstr ( char *text, char *find )
{
	char	realtext[256];
	char	subtext[256];
	char	*result;
	char	*next;
	char	temp;
	int		i = 0;

	traceLastFunc( "findstrinstr()" );

	// can't find stuff that isn't there unless you are high
	if ( text == NULL || find == NULL )
		return false;

	// lower case text ( sizeof()-2 = 1 for array + 1 for termination after while() )
	while ( text[i] != NULL && i < (sizeof(realtext)-2) )
	{
		temp = text[i];
		if ( isupper(temp) )
			temp = tolower( temp );
		realtext[i] = temp;
		i++;
	}
	realtext[i] = 0;

	// replace unwanted characters/spaces with dots
	i = 0;
	while ( find[i] != NULL && i < (sizeof(subtext)-2) )
	{
		temp = find[i];
		if ( isupper(temp) )
			temp = tolower( temp );
		if ( !isalpha(temp) )
			temp = '.';
		subtext[i] = temp;
		i++;
	}
	subtext[i] = 0;

	// use i to count the successfully found text parts
	i = 0;

	// split and find every part of subtext/find in text
	result = &subtext[0];
	while ( *result != NULL )
	{
		next = strstr( result, "." );
		if ( next != NULL )
		{
			// more than one non-alphabetic character
			if ( next == result )
			{
				do
					next++;
				while ( *next == '.' );

				if ( *next == NULL )
					return (i != 0);
				result = next;
				next = strstr( result, "." );
				if ( next != NULL )
					*next = NULL;
			}
			else
				*next = NULL;
		}

		if ( strstr(realtext, result) == NULL )
			return false;

		if ( next == NULL )
			return true;

		i++;
		result = next + 1;
	}

	return false;
}

void *memdup ( const void *src, int len )
{
	void	*dest = malloc( len );

	if ( dest != NULL )
		memcpy( dest, src, len );

	return dest;
}

static signed char hex_to_dec ( signed char ch )
{
	if ( ch >= '0' && ch <= '9' )
		return ch - '0';
	if ( ch >= 'A' && ch <= 'F' )
		return ch - 'A' + 10;
	if ( ch >= 'a' && ch <= 'f' )
		return ch - 'A' + 10;

	return -1;
}

uint8_t *hex_to_bin ( const char *str )
{
	int		len = (int)strlen( str );
	uint8_t *buf, *sbuf;

	if ( len == 0 || len % 2 != 0 )
		return NULL;

	sbuf = buf = (uint8_t *)malloc( len / 2 );

	while ( *str )
	{
		signed char bh = hex_to_dec( *str++ );
		signed char bl = hex_to_dec( *str++ );

		if ( bl == -1 || bh == -1 )
		{
			free( sbuf );
			return NULL;
		}

		*buf++ = ( uint8_t ) ( bl | (bh << 4) );
	}

	return sbuf;
}

bool hex_is_valid( const std::string& hex )
{
	if ( hex.empty() )
		return false;
	for ( size_t i = 0, len = hex.length(); i < len; i++ )
	{
		if ( hex_to_dec( hex[i] ) == -1 )
			return false;
	}
	return true;
}

// new functions related to R* classes //
CVehicle *getSelfCVehicle ( void )
{
	return pGameInterface->GetPools()->GetPedFromRef( CPOOLS_PED_SELF_REF )->GetVehicle();
}
int getVehicleGTAIDFromInterface ( DWORD *vehicle )
{
	return (int)( (DWORD) vehicle - (DWORD) pool_vehicle->start ) / 2584;
}
int getPedGTAIDFromInterface ( DWORD *ped )
{
	return (int)( (DWORD) ped - (DWORD) pool_actor->start ) / 1988;
}
D3DXVECTOR3 CVecToD3DXVEC ( CVector vec )
{
	return D3DXVECTOR3( vec.fX, vec.fY, vec.fZ );
}
