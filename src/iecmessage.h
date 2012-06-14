/*
 * iecmessage.h - supported IEC message definitions
 *
 * Copyright (C) 2012 I. S. Gorbunov <igor.genius at gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef IEC_MESSAGE_H
#define IEC_MESSAGE_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

//
// Supported IEC 61162-1 (2000-07) messages
//

// The maximum number of characters in a sentence shall be 82,
// consisting of a maximum of 79 characters between the starting
// delimeter '$' and the terminating delimeter <cr><lf>.
#define IEC_MESSAGE_MAXSIZE		82

//
// Approved sentence formatters
//
enum naviSentence_t
{
	_AAM = 0,	// waypoint arrival alarm
	_ACK = 1,	// acknowledgement alarm
	_ALM = 2,	// GPS almanac data
	_ALR = 3,	// set alarm state
	_APB = 4,	// heading/track controller (Autopilot) sentence B
	_BEC = 5,	// bearing and distance to waypoint, dead reckoning
	_BOD = 6,	// bearing, origin to destination
	_BWC = 7,	// bearing and distance to waypoint
	_BWR = 8,	// bearing and distance to waypoint, rhumb line
	_BWW = 9,	// bearing, waypoint to waypoint
	_DBT = 10,	// depth below transducer
	_DCN = 11,	// DECCA position
	_DPT = 12,	// depth
	_DSC = 13,	// digital selective calling information
	_DSE = 14,	// expanded digital selective calling
	_DSI = 15,	// DSC transponder initialize
	_DSR = 16,	// DSC transponder response
	_DTM = 17,	// datum reference
	_FSI = 18,	// frequency set information
	_GBS = 19,	// GNSS satellite fault detection
	_GGA = 20,	// global positioning system fix data
	_GLC = 21,	// geographic position, LORAN-C
	_GLL = 22,	// geographic position, latitude/longitude
	_GNS = 23,	// GNSS fix data
	_GRS = 24,	// GNSS range residuals
	_GSA = 25,	// GNSS DOP and active satellites
	_GST = 26,	// GNSS pseudorange error statistics
	_GSV = 27,	// GNSS satellites in view
	_HDG = 28,	// heading, deviation and variation
	_HDT = 29,	// heading, true
	_HMR = 30,	// heading monitor - receive
	_HMS = 31,	// heading monitor - set
	_HSC = 32,	// heading steering command
	_HTC = 33,	// heading/track control command
	_HTD = 34,	// heading/track control data
	_LCD = 35,	// LORAN-C signal data
	_MLA = 36,	// Glonass almanac data
	_MSK = 37,	// MSK receiver interface
	_MSS = 38,	// MSK receiver signal status
	_MTW = 39,	// water temperature
	_MWD = 40,	// wind direction and speed
	_MWV = 41,	// wind speed and angle
	_OSD = 42,	// own ship data
	_RMA = 43,	// recommended minimum specific LORAN-C data
	_RMB = 44,	// recommended minimum navigation information
	_RMC = 45,	// recommended minimum specific GNSS data
	_ROT = 46,	// rate of turn
	_RPM = 47,	// revolutions
	_RSA = 48,	// rudder sensor angle
	_RSD = 49,	// radar system data
	_RTE = 50,	// routes
	_SFI = 51,	// scanning frequency information
	_STN = 52,	// multiple data ID
	_TLB = 53,	// target label
	_TLL = 54,	// target latitude and longitude
	_TTM = 55,	// tracked target message
	_TXT = 56,	// text transmission
	_VBW = 57,	// dual ground/water speed
	_VDR = 58,	// set and drift
	_VHW = 59,	// water speed and heading
	_VLW = 60,	// distance travelled through the water
	_VPW = 61,	// speed, measured parallel to wind
	_VTG = 62,	// course over ground and ground speed
	_WCV = 63,	// waypoint closure velocity
	_WNC = 64,	// distance, waypoint to waypoint
	_WPL = 65,	// waypoint location
	_XDR = 66,	// transducer measurements
	_XTE = 67,	// cross-track error, measured
	_XTR = 68,	// cross-track error, dead reckoning
	_ZDA = 69,	// time and date
	_ZDL = 70,	// time and distance to variable point
	_ZFO = 71,	// UTC and time from origin waypoint
	_ZTG = 72	// UTC and time to destination waypoint
};

//
// Talker Identifier Mnemonics
//
enum naviTalkerId_t
{
	// Heading/track controller (autopilot)
	_AG = 0,	// general
	_AP = 1,	// magnetic
	// Automatic identification system
	_AI = 2,
	// Communications:
	_CD = 3,	// digital selective calling (DSC)
	_CR = 4,	// data receiver
	_CS = 5,	// satellite
	_CT = 6,	// radio-telephone (MF/HF)
	_CV = 7,	// radio-telephone (VHF)
	_CX = 8,	// scanning receiver
	// DECCA navigator
	_DE = 9,
	// Direction finder
	_DF = 10,
	// Electronic chart systems (ECS)
	_EC = 11,
	// Electronic chart display and information system (ECDIS)
	_EI = 12,
	// Emergency position indicating radio beacon (EPIRB)
	_EP = 13,
	// Engine room monitoring systems
	_ER = 14,
	// Galileo receiver
	_GA = 15,
	// Global positioning system (GPS)
	_GP = 16,
	// GLONASS receiver
	_GL = 17,
	// Global navigation satellite system (GNSS)
	_GN = 18,
	// SBAS receiver
	_GW = 19,
	// Heading sensors:
	_HC = 20,	// compass, magnetic
	_HE = 21,	// gyro, north seeking
	_HN = 22,	// gyro, non-north seeking
	// Integrated instrumentation
	_II = 23,
	// Integrated navigation
	_IN = 24,
	// LORAN: LORAN-C
	_LC = 25,
	// Proprietary code
	_P = 26,
	// Radar and/or radar plotting
	_RA = 27,
	// Sounder, depth
	_SD = 28,
	// Electronic positioning system, other/general
	_SN = 29,
	// Sounder, scanning
	_SS = 30,
	// Turn rate indicator
	_TI = 31,
	// Velocity sensors:
	_VD = 32,	// Doppler, other/general
	_VM = 33,	// speed log, water, magnetic
	_VW = 34,	// speed log, water, mechanical
	// Voyage data recorder
	_VR = 35,
	// Transducer
	_YX = 36,
	// Timekeepers, time/date
	_ZA = 37,	// atomic clock
	_ZC = 38,	// chronometer
	_ZQ = 39,	// quartz
	_ZV = 40,	// radio update
	// Weather instruments
	_WI = 41
};

//
// Local/reference datums
//
enum naviDatum_t
{
	_WGS84 = 0,
	_WGS72 = 1,
	_SGS85 = 2,
	_PE90 = 3,
	_UserDefined = 4
};

enum naviOffsetSign_t
{
	_North = 0, // North
	_South = 1,	// South
	_East = 2,	// East
	_West = 3	// West
};

enum naviStatus_t
{
	_Valid = 0,		// data valid
	_Invalid = 1	// data invalid
};

enum naviModeIndicator_t
{
	// Satellite system used in non-differential mode in position fix
	_Autonomous = 0,

	// Satellite sysytem used in differential mode in position fix
	_Differential = 1,

	// Estimated (dead reckoning) mode
	_Estimated = 2,

	// Manual input mode
	_ManualInput = 3,

	// Simulator mode
	_Simulator = 4,

	// No fix. Satellite system not used in position fix, or fix not valid
	_NotValid = 5,

	//
	// Additions to GNS message

	// Satellite system used in precision mode
	_Precise = 6,

	// Satellite system used in Real Time Kinematic mode with fixed integers
	_RTKinematic = 7,

	// Satellite system used in Real Time Kinematic mode with
	// floating integers
	_FloatRTK = 8
};

struct naviUtc_t
{
	int hour, min, sec, msec;
};

struct naviOffset_t
{
	double offset;					// degrees or minutes
	enum naviOffsetSign_t offsign;	// N/S or E/W
};

//	// Waypoint arrival alarm
//	struct aam_t
//	{
//	};

//	// Acknowledgement alarm
//	struct ack_t
//	{
//	};

//	// GPS almanac data
//	struct alm_t
//	{
//	};

//	// Set alarm state
//	struct alr_t
//	{
//	};

//	// Heading/track controller (Autopilot) sentence B
//	struct alr_t
//	{
//	};

//	// Bearing and distance to waypoint, dead reckoning
//	struct bec_t
//	{
//	};

//	// Bearing, origin to destination
//	struct bod_t
//	{
//	};

//	// Bearing and distance to waypoint
//	struct bwc_t
//	{
//	};

//	// Bearing and distance to waypoint, rhumb line
//	struct bwr_t
//	{
//	};

//	// Bearing, waypoint to waypoint
//	struct bww_t
//	{
//	};

//	// Depth below transducer
//	struct dbt_t
//	{
//	};

//	// DECCA position
//	struct dcn_t
//	{
//	};

//	// Depth
//	struct dpt_t
//	{
//	};

//	// Digital selective calling information
//	struct dsc_t
//	{
//	};

//	// Expanded digital selective calling
//	struct dse_t
//	{
//	};

//	// DSC transponder initialise
//	struct dsi_t
//	{
//	};

//	// DSR transponder response
//	struct dsr_t
//	{
//	};

	//
	// Datum reference
	struct dtm_t
	{
		enum ValidFields_t
		{
			_LocalDatum = 0x01, _LocalDatumSub = 0x02, _LatOffset = 0x04,
			_LonOffset = 0x08, _AltitudeOffset = 0x10, _ReferenceDatum = 0x20
		};
		enum naviLocalDatumSub_t { };

		enum naviTalkerId_t tid;
		unsigned vfields;		// valid fields, bitwise or of ValidFields_t
		enum naviDatum_t ld;			// local datum
		enum naviLocalDatumSub_t lds;	// local datum subdivision code
		struct naviOffset_t latofs;		// latitude offset, min,N/S
		struct naviOffset_t lonofs;		// longitude offset, min,E/W
		double altoffset;				// altitude offset, m
		enum naviDatum_t rd;			// reference datum
	};

//	// Frequency set information
//	struct fsi_t
//	{
//	};

//	// GNSS Satellite fault detection
//	struct gbs_t
//	{
//	};

//	// Global positioning system fix data
//	struct gga_t
//	{
//	};

//	// Geographic position, LORAN-C
//	struct glc_t
//	{
//	};

	//
	// Geographic position, latitude/longitude
	struct gll_t
	{
		enum ValidFields_t
		{
			_Latitude = 0x01, _Longitude = 0x02, _UTC = 0x04
		};

		enum naviTalkerId_t tid;
		unsigned vfields;		// valid fields, bitwise or of ValidFields_t
		struct naviOffset_t latitude;	// latitude, degrees,N/S
		struct naviOffset_t longitude;	// longitude, degrees,E/W
		enum naviUtc_t utc;
		enum naviStatus_t status;
		enum naviModeIndicator_t mi;
	} gll_t;

	//
	// GNSS fix data
	struct gns_t
	{
		enum ValidFields_t
		{
			_UTC = 0x001, _Latitude = 0x002, _Longitude = 0x004,
			_ModeIndicator = 0x008, _TotalNmOfSatellites = 0x010, _Hdop = 0x020,
			_AntennaAltitude = 0x040, _GeoidalSep = 0x080,
			_AgeOfDiffData = 0x100, _DiffRefStationId = 0x200
		};

		enum naviTalkerId_t tid;
		unsigned vfields;		// valid fields, bitwise or of ValidFields_t
		enum naviUtc_t utc;
		struct naviOffset_t latitude;	// latitude, degrees,N/S
		struct naviOffset_t longitude;	// longitude, degrees,E/W
		enum naviModeIndicator_t mi[2];	// GPS, GLONASS
		int totalsats;			// Total number of satellites in use, 00-99
		double hdop;			// Horizontal Dilution of Precision
		double antaltitude;		// Antenna altitude, m, re:mean-sea-level (geoid)
		double geoidalsep;		// Geoidal separation, m
		double diffage;			// Age of differential data
		int id;					// Differential reference station ID
	};

//	// GNSS range residuals
//	struct grs_t
//	{
//	};

//	// GNSS DOP and active satellites
//	struct gsa_t
//	{
//	};

//	// GNSS pseudorange error statistics
//	struct gst_t
//	{
//	};

//	// GNSS satellites in view
//	struct gsv_t
//	{
//	};

//	// Heading, deviation and variation
//	struct hdg_t
//	{
//	};

//	// Heading, true
//	struct hdt_t
//	{
//	};

//	// Heading monitor - receive
//	struct hmr_t
//	{
//	};

//	// Heading monitor - set
//	struct hms_t
//	{
//	};

//	// Heading steering command
//	struct hsc_t
//	{
//	};

//	// Heading/track control command
//	struct htc_t
//	{
//	};

//	// Heading/track control data
//	struct htd_t
//	{
//	};

//	// LORAN-C signal data
//	struct lcd_t
//	{
//	};

//	// Glonass almanac data
//	struct mla_t
//	{
//	};

//	// MKS receiver interface
//	struct msk_t
//	{
//	};

//	// MKS receiver signal status
//	struct mss_t
//	{
//	};

//	// Water temperature
//	struct mtw_t
//	{
//	};

//	// Wind direction and speed
//	struct mwd_t
//	{
//	};

//	// Wind speed and angle
//	struct mwv_t
//	{
//	};

//	// Own ship data
//	struct osd_t
//	{
//	};

//	// Recommended minimum specific LORAN-C data
//	struct rma_t
//	{
//	};

//	// Recommended minimum navigation information
//	struct rmb_t
//	{
//	};

	//
	// Recommended minimum specific GNSS data
	struct rmc_t
	{
		enum _ValidFields_t
		{
			_UTC = 0x01, _Latitude = 0x02, _Longitude = 0x04, _Speed = 0x08,
			_CourseTrue = 0x10, _Date = 0x20, _MagnVariation = 0x40
		};

		enum naviTalkerId_t tid;
		unsigned vfields;		// valid fields, bitwise or of ValidFields_t
		enum naviUtc_t utc;
		enum naviStatus_t status;
		struct naviOffset_t latitude;	// latitude, degrees,N/S
		struct naviOffset_t longitude;	// longitude, degrees,E/W
		double speed;			// Speed over ground, knots
		double courseTrue;		// Course over ground, degrees true
		int day, month, year;	// Day (01 to 31), Month (01 to 12), Year (UTC)
		struct naviOffset_t magnetic;	// Magnetic variation, degrees,E/W
		enum naviModeIndicator_t mi;
	};

//	// Rate of turn
//	struct rot_t
//	{
//	};

//	// Revolutions
//	struct rpm_t
//	{
//	};

//	// Revolutions
//	struct rpm_t
//	{
//	};

//	// Rudder sensor angle
//	struct rsa_t
//	{
//	};

//	// Radar system data
//	struct rsd_t
//	{
//	};

//	// Routes
//	struct rte_t
//	{
//	};

//	// Scanning frequency information
//	struct sfi_t
//	{
//	};

//	// Multiple data ID
//	struct stn_t
//	{
//	};

//	// Target label
//	struct tlb_t
//	{
//	};

//	// Target latitude and longitude
//	struct tll_t
//	{
//	};

//	// Tracked target message
//	struct ttm_t
//	{
//	};

//	// Text transmission
//	struct txt_t
//	{
//	};

//	// Dual ground/water speed
//	struct vbw_t
//	{
//	};

//	// Set and drift
//	struct vdr_t
//	{
//	};

//	// Water speed and heading
//	struct vhw_t
//	{
//	};

//	// Distance travelled thourgh the water
//	struct vlw_t
//	{
//	};

//	// Speed, measured parallel to wind
//	struct vpw_t
//	{
//	};

	//
	// Cource over ground and ground speed
	struct vtg_t
	{
		enum ValidFields_t
		{
			_CourseTrue = 0x01, _CourseMagn = 0x02, _Speed = 0x04
		};

		enum naviTalkerId_t tid;
		unsigned vfields;		// valid fields, bitwise or of ValidFields_t
		double courseTrue;		// Course over ground, degrees true
		double courseMagn;		// Course over ground, degrees magnetic
		double speed;			// Speed over ground, m/s
		enum naviModeIndicator_t mi;
	};

//	// Waypoint closure velocity
//	struct wcv_t
//	{
//	};

//	// Distance, waypoint to waypoint
//	struct wnc_t
//	{
//	};

//	// Waypoint location
//	struct wpl_t
//	{
//	};

//	// Transducer measurements
//	struct xdr_t
//	{
//	};

//	// Cross-track error, measured
//	struct xte_t
//	{
//	};

//	// Cross-track error, dead reckoning
//	struct xtr_t
//	{
//	};

	//
	// Time and date
	struct zda_t
	{
		enum ValidFields_t
		{
			_UTC = 0x01, _Day = 0x02, _Month = 0x04, _Year = 0x08,
			_LocalZone = 0x10
		};

		enum naviTalkerId_t tid;
		unsigned vfields;		// valid fields, bitwise or of ValidFields_t
		enum naviUtc_t utc;
		int day, month, year;	// Day (01 to 31), Month (01 to 12), Year (UTC)
		int lzoffset;			// Local zone offset in minutes
	};

//	// Time and distance to variable point
//	struct zdl_t
//	{
//	};

//	// UTC and time from origin waypoint
//	struct zfo_t
//	{
//	};

//	// UTC and time to destination waypoint
//	struct ztg_t
//	{
//	};

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // IEC_MESSAGE_H

