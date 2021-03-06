/*
 * main.c - IEC messages generating/parsing tests and usage examples.
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

#include <navigate.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void)
{
	int result;
	size_t msglength, nmwritten, nmread, remain, parsed;

	navi_approved_fmt_t msgtype;
	struct approved_field_t s;

	char buffer[1024];
	struct aam_t aam;
	struct ack_t ack;
	struct alr_t alr;
	struct dtm_t dtm;
	struct gbs_t gbs;
	struct gga_t gga;
	struct gll_t gll;
	struct gns_t gns;
	struct grs_t grs;
	struct gsa_t gsa;
	struct gst_t gst;
	struct rmc_t rmc;
	struct txt_t txt;
	struct vtg_t vtg;
	struct zda_t zda;

	struct navi_satinfo_t gsvinfo[9];

	char parsedbuffer[4096];
	const char *longtxtmessage = "Pay big attention to the Metro stations in St.Petersburg. "
		"Some stations have correspondents on several main lines. The big problem comes this way: "
		"Even if it is the same station, it will have different names on each main line. So if you "
		"know you want to reach Gostiny Dvor on the green line, pay attention as you might be "
		"travelling on the blue line. You would have to descend at Nevski Prospekt station which is "
		"in fact the same station as Gostiny Dvor.";
	int finished;

	const navi_error_t *lasterr;

	msglength = 0;
	remain = sizeof(buffer);

	// ZDA
	navi_init_zda(&zda);
	zda.vfields = ZDA_VALID_DATE | ZDA_VALID_LOCALZONE;
	navi_init_utc_from_hhmmss(8, 12, 38.56, &zda.utc);
	navi_init_date(1982, 5, 25, &zda.date);
	zda.lzoffset = -240;

	nmwritten = 0;
	s.afmt = navi_ZDA;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &zda, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of ZDA failed (%d)\n", result);
	}

	// DTM
	navi_init_dtm(&dtm);

	dtm.local_dtm = navi_UserDefined;

	navi_init_offset_from_degrees(0.2366, navi_North, &dtm.lat_offset);
	navi_init_offset_from_degrees(0.31825, navi_West, &dtm.long_offset);

	dtm.alt_offset = 3.446;
	dtm.reference_dtm = navi_WGS84;

	s.afmt = navi_DTM;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &dtm, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of DTM failed (%d)\n", result);
	}

	// GLL
	gll.fix.latitude.offset = 0.02;
	gll.fix.latitude.sign = navi_North;
	gll.fix.longitude.offset = 0.00000000999;
	gll.fix.longitude.sign = navi_East;
	gll.utc.hour = 4;
	gll.utc.min = 34;
	gll.utc.sec = 18.4;
	gll.status = navi_status_A;
	gll.mi = navi_Autonomous;

	s.afmt = navi_GLL;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &gll, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GLL failed (%d)\n", result);
	}

	// GNS
	navi_init_gns(&gns);
	navi_init_utc_from_hhmmss(20, 7, 1.0, &gns.utc);
	navi_init_position_from_degrees(60.0, 30.0, &gns.fix);
	gns.mi[0] = navi_Autonomous;
	gns.mi[1] = navi_Differential;
	gns.nmsatellites = 4;
	gns.hdop = 2.3;
	gns.antaltitude = 2.003;
	gns.geoidalsep = 18.2;
	gns.diffdata_age = 4;
	gns.station_id = 13;

	s.afmt = navi_GNS;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &gns, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GNS failed (%d)\n", result);
	}

	// RMC
	navi_init_rmc(&rmc);

	rmc.vfields = RMC_VALID_DATE;

	navi_init_utc_from_hhmmss(9, 19, 39.98, &rmc.utc);
	rmc.status = navi_status_V;
	navi_init_position_from_degrees(-74.64772882, 132.0000333, &rmc.fix);

	rmc.date.day = 18;
	rmc.date.month = 3;
	rmc.date.year = 2012;

	rmc.mi = navi_Estimated;

	s.afmt = navi_RMC;
	s.tid = navi_GL;

	// Part 1
	result = navi_create_msg(navi_af_Approved, &s, &rmc, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of RMC failed (%d)\n", result);
	}

	// Part 2
	navi_init_rmc(&rmc);

	rmc.vfields = RMC_VALID_DATE;

	navi_init_utc_from_hhmmss(9, 19, 39.98, &rmc.utc);
	rmc.status = navi_status_V;

	rmc.speedN = 1.03553;
	rmc.courseT = 180.2112;

	rmc.date.day = 18;
	rmc.date.month = 3;
	rmc.date.year = 2012;

	navi_init_offset_from_degrees(23.011, navi_East, &rmc.magnVariation);
	rmc.mi = navi_Estimated;

	result = navi_create_msg(navi_af_Approved, &s, &rmc, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of RMC failed (%d)\n", result);
	}

	// VTG
	navi_init_vtg(&vtg);
	vtg.courseT = 0.223;
	vtg.courseM = 22.203;
	vtg.speedN = MPS_TO_KNOTS(1.023);
	vtg.speedK = MPS_TO_KMPH(1.023);
	vtg.mi = navi_Simulator;

	s.afmt = navi_VTG;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &vtg, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of VTG failed (%d)\n", result);
	}

	printf("msglength = %d\n", msglength);
	printf("message = '%s'\n", buffer);

	finished = 0;
	parsed = 0;
	nmread = 0;

	do
	{
		while ((result = navi_parse_msg(buffer + parsed, sizeof(buffer) - parsed,
			sizeof(parsedbuffer), &msgtype, parsedbuffer, &nmread)) == navi_Ok)
		{
			parsed += nmread;

			if (msgtype == navi_af_Approved)
			{
				struct approved_field_t s;
				memmove(&s, parsedbuffer, sizeof(s));

				switch (s.afmt)
				{
				case navi_DTM:
					{
						struct dtm_t *dtm = (struct dtm_t *)((char *)parsedbuffer + sizeof(s));
						printf("Received DTM:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);

						if (dtm->local_dtm != navi_datum_NULL)
							printf("\tlocal datum = %d\n", dtm->local_dtm);
						if (dtm->local_dtmsd != navi_datumsub_NULL)
							printf("\tlocal datum subdivision = %d\n", dtm->local_dtmsd);
						if (dtm->lat_offset.sign != navi_offset_NULL)
							printf("\tlatitude offset = %.8f %s (%d)\n", dtm->lat_offset.offset,
							navi_fixsign_str(dtm->lat_offset.sign), dtm->lat_offset.sign);
						if (dtm->long_offset.sign != navi_offset_NULL)
							printf("\tlongitude offset = %.8f %s (%d)\n", dtm->long_offset.offset,
							navi_fixsign_str(dtm->long_offset.sign), dtm->long_offset.sign);
						if (navi_check_validity_number(dtm->alt_offset))
							printf("\taltitude offset, m = %f\n", dtm->alt_offset);
						if (dtm->reference_dtm != navi_datum_NULL)
							printf("\treference datum = %d\n", dtm->reference_dtm);
					}
					break;
				case navi_GLL:
					{
						struct gll_t *gll = (struct gll_t *)((char *)parsedbuffer + sizeof(s));
						printf("Received GLL:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);

						if (gll->fix.latitude.sign != navi_offset_NULL)
						{
							printf("\tlatitude = %.12f %s (%d)\n", gll->fix.latitude.offset,
								navi_fixsign_str(gll->fix.latitude.sign), gll->fix.latitude.sign);
							printf("\tlongitude = %.12f %s (%d)\n", gll->fix.longitude.offset,
								navi_fixsign_str(gll->fix.longitude.sign), gll->fix.longitude.sign);
						}
						if (navi_check_validity_utc(&gll->utc) == navi_Ok)
						{
							printf("\tutc = %02u:%02u:%06.3f\n", gll->utc.hour, gll->utc.min,
								gll->utc.sec);
						}

						printf("\tstatus = %d\n", gll->status);
						printf("\tmode indicator = %d\n", gll->mi);
					}
					break;
				case navi_GNS:
					{
						struct gns_t *gns = (struct gns_t *)((char *)parsedbuffer + sizeof(s));
						printf("Received GNS:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);

						if (navi_check_validity_utc(&gns->utc) == navi_Ok)
							printf("\tutc = %02u:%02u:%06.3f\n", gns->utc.hour, gns->utc.min,
							gns->utc.sec);
						if (gns->fix.latitude.sign != navi_offset_NULL)
						{
							printf("\tlatitude = %.12f %s (%d)\n", gns->fix.latitude.offset,
								navi_fixsign_str(gns->fix.latitude.sign), gns->fix.latitude.sign);
							printf("\tlongitude = %.12f %s (%d)\n", gns->fix.longitude.offset,
								navi_fixsign_str(gns->fix.longitude.sign), gns->fix.longitude.sign);
						}
						printf("\tmode indicator = %d %d\n", gns->mi[0], gns->mi[1]);
						if (gns->nmsatellites != -1)
							printf("\tsatellites = %d\n", gns->nmsatellites);
						if (navi_check_validity_number(gns->hdop) == navi_Ok)
							printf("\thdop = %.12f\n", gns->hdop);
						if (navi_check_validity_number(gns->antaltitude) == navi_Ok)
							printf("\tantenna altitude = %.12f\n", gns->antaltitude);
						if (navi_check_validity_number(gns->geoidalsep) == navi_Ok)
							printf("\tgeoidal separation = %.12f\n", gns->geoidalsep);
						if (gns->diffdata_age != -1)
							printf("\tage of dd = %if\n", gns->diffdata_age);
						if (gns->station_id != -1)
							printf("\tid = %d\n", gns->station_id);
					}
					break;
				case navi_RMC:
					{
						struct rmc_t *rmc = (struct rmc_t *)((char *)parsedbuffer + sizeof(s));
						printf("Received RMC:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);

						if (navi_check_validity_utc(&rmc->utc) == navi_Ok)
							printf("\tutc = %02u:%02u:%06.3f\n", rmc->utc.hour, rmc->utc.min,
							rmc->utc.sec);
						printf("\tstatus = %d\n", rmc->status);
						if (rmc->fix.latitude.sign != navi_offset_NULL)
						{
							printf("\tlatitude = %.12f %s (%d)\n", rmc->fix.latitude.offset,
								navi_fixsign_str(rmc->fix.latitude.sign), rmc->fix.latitude.sign);
							printf("\tlongitude = %.12f %s (%d)\n", rmc->fix.longitude.offset,
								navi_fixsign_str(rmc->fix.longitude.sign), rmc->fix.longitude.sign);
						}
						if (navi_check_validity_number(rmc->speedN) == navi_Ok)
							printf("\tspeed, knots = %f\n", rmc->speedN);
						if (navi_check_validity_number(rmc->courseT) == navi_Ok)
							printf("\tcourse, true = %f\n", rmc->courseT);
						if (rmc->vfields & RMC_VALID_DATE)
						{
							printf("\tdate = %04d-%02d-%02d\n", rmc->date.year + 2000, rmc->date.month,
								rmc->date.day);
						}
						if (navi_check_validity_offset(&rmc->magnVariation) == navi_Ok)
						{
							printf("\tmagnetic variation = %f (%d)\n",
								rmc->magnVariation.offset, rmc->magnVariation.sign);
						}
						printf("\tmode indicator = %d\n", rmc->mi);
					}
					break;
				case navi_VTG:
					{
						struct vtg_t *vtg = (struct vtg_t *)((char *)parsedbuffer + sizeof(s));
						printf("Received VTG:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);

						if (navi_check_validity_number(vtg->courseT) == navi_Ok)
							printf("\tcource, true = %f\n", vtg->courseT);
						if (navi_check_validity_number(vtg->courseM) == navi_Ok)
							printf("\tcourse, magnetic = %f\n", vtg->courseM);
						if (navi_check_validity_number(vtg->speedN) == navi_Ok)
							printf("\tspeed, knots = %f\n", vtg->speedN);
						if (navi_check_validity_number(vtg->speedK) == navi_Ok)
							printf("\tspeed, km/h = %f\n", vtg->speedK);
						printf("\tmode indicator = %d\n", vtg->mi);
					}
					break;
				case navi_ZDA:
					{
						struct zda_t *zda = (struct zda_t *)((char *)parsedbuffer + sizeof(s));
						printf("Received ZDA:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);

						if (navi_check_validity_utc(&zda->utc) == navi_Ok)
						{
							printf("\tutc = %02u:%02u:%06.3f\n", zda->utc.hour, zda->utc.min,
								zda->utc.sec);
						}
						if (zda->vfields & ZDA_VALID_DATE)
						{
							printf("\tdate = %04d-%02d-%02d\n", zda->date.year, zda->date.month,
								zda->date.day);
						}
						if (zda->vfields & ZDA_VALID_LOCALZONE)
							printf("\tlocal zone offset = %d\n", zda->lzoffset);
					}
					break;
				default:
					break;
				}
			}
		}

		lasterr = navierr_get_last();

		if (lasterr->errclass == navi_CrcEror)
		{
			printf("CRC error\n");
			parsed += nmread;	// advance to parse next message
		}
		else if (lasterr->errclass == navi_MsgNotSupported)
		{
			parsed += nmread;	// advance to parse next message

			switch (msgtype)
			{
			case navi_DTM:
				printf("Could not parse DTM\n");
				break;
			case navi_GLL:
				printf("Could not parse GLL\n");
				break;
			case navi_GNS:
				printf("Could not parse GNS\n");
				break;
			case navi_RMC:
				printf("Could not parse RMC\n");
				break;
			case navi_VTG:
				printf("Could not parse VTG\n");
				break;
			case navi_ZDA:
				printf("Could not parse ZDA\n");
				break;
			default:
				break;
			}
		}
		else if (lasterr->errclass == navi_NoValidMessage)
		{
			printf("Buffer emptied (%d)\n", lasterr->errclass);
			finished = 1;
		}
		else
		{
			printf("Parsing result = %d\n", lasterr->errclass);
			finished = 1;
		}
	} while (!finished);

	msglength = 0;
	remain = sizeof(buffer);

	// GBS
	navi_init_gbs(&gbs);

	navi_init_utc_from_hhmmss(0, 34, 16.0, &gbs.utc);
	gbs.experrlat = 1.4;
	gbs.experrlon = 0.12;
	gbs.experralt = 1.1;
	gbs.failed_id = 66;
	gbs.probability = 0.12;
	gbs.estimate = 1.1;
	gbs.deviation = 1.3;

	s.afmt = navi_GBS;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &gbs, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GBS failed (%d)\n", result);
	}

	// GGA
	navi_init_gga(&gga);
	navi_init_utc_from_hhmmss(0, 34, 16.0, &gga.utc);
	navi_init_position_from_degrees(-12.0, -112.01, &gga.fix);
	gga.gpsindicator = navi_gps_Differential;
	gga.nmsatellites = 8;
	gga.hdop = 1.0;
	gga.antaltitude = 8.1;
	gga.geoidalsep = -1.2;
	gga.diffdata_age = 21;
	gga.station_id = 1011;

	s.afmt = navi_GGA;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &gga, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GGA failed (%d)\n", result);
	}

	// GRS
	navi_init_grs(&grs);
	navi_init_utc_from_hhmmss(0, 34, 16.0, &grs.utc);
	grs.mode = 0;

	grs.residuals[0] = 1.0;
	grs.residuals[1] = 0.2;
	grs.residuals[2] = 0.34;
	grs.residuals[3] = 1.01;
	grs.residuals[4] = 0.98;
	grs.residuals[7] = 0.1;
	grs.residuals[8] = -103.7;

	s.afmt = navi_GRS;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &grs, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GRS failed (%d)\n", result);
	}

	// GSA
	navi_init_gsa(&gsa);

	gsa.swmode = navi_gsa_Automatic;
	gsa.fixmode = 3;

	gsa.satellites[0] = 1;
	gsa.satellites[1] = 12;
	gsa.satellites[2] = 3;
	gsa.satellites[3] = 2;
	gsa.satellites[4] = 18;
	gsa.satellites[7] = 24;
	gsa.satellites[8] = 14;

	gsa.hdop = 2.12;
	gsa.vdop = 0.012;
	gsa.pdop = 2.12003396;

	s.afmt = navi_GSA;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &gsa, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GSA failed (%d)\n", result);
	}

	// GST
	navi_init_gst(&gst);

	navi_init_utc_from_hhmmss(14, 8, 16.0, &gst.utc);

	gst.rms = 1.4;
	gst.devmajor = 0.56;
	gst.devminor = 3.2;
	gst.orientmajor = 18.0;
	gst.devlaterr = 0.2;
	gst.devlonerr = 0.1;
	gst.devalterr = 1.0;

	s.afmt = navi_GST;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &gst, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GST failed (%d)\n", result);
	}

	// GSV
	gsvinfo[0].vfields = SATINFO_VALID_ORIENTATION;
	gsvinfo[0].id = 4;
	gsvinfo[0].elevation = 12;
	gsvinfo[0].azimuth = 0;

	gsvinfo[1].vfields = SATINFO_VALID_ORIENTATION | SATINFO_VALID_SNR;
	gsvinfo[1].id = 5;
	gsvinfo[1].elevation = 18;
	gsvinfo[1].azimuth = 12;
	gsvinfo[1].snr = 45;

	gsvinfo[2].vfields = 0;
	gsvinfo[2].id = 14;

	gsvinfo[3].vfields = SATINFO_VALID_ORIENTATION | SATINFO_VALID_SNR;
	gsvinfo[3].id = 18;
	gsvinfo[3].elevation = 12;
	gsvinfo[3].azimuth = 300;
	gsvinfo[3].snr = 70;

	gsvinfo[4].vfields = 0;
	gsvinfo[4].id = 6;

	gsvinfo[5].vfields = SATINFO_VALID_SNR;
	gsvinfo[5].id = 7;
	gsvinfo[5].snr = 4;

	gsvinfo[6].vfields = SATINFO_VALID_SNR;
	gsvinfo[6].id = 8;
	gsvinfo[6].snr = 4;

	gsvinfo[7].vfields = SATINFO_VALID_SNR;
	gsvinfo[7].id = 9;
	gsvinfo[7].snr = 4;

	gsvinfo[8].vfields = SATINFO_VALID_SNR;
	gsvinfo[8].id = 10;
	gsvinfo[8].snr = 4;

	result = navi_create_gsv_sequence(navi_GL, 9, gsvinfo, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of GSV failed (%d)\n", result);
	}

	// AAM
	navi_init_aam(&aam);
	aam.circle = navi_status_A;
	aam.perp = navi_status_V;
	aam.radius = 10.1;
	strcpy(aam.wpid, "St. Petersburg, Russia");

	s.afmt = navi_AAM;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &aam, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of AAM failed (%d)\n", result);
	}

	// ACK
	navi_init_ack(&ack);
	ack.alarmid = 846;

	s.afmt = navi_ACK;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &ack, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of ACK failed (%d)\n", result);
	}

	// ALR
	navi_init_alr(&alr);
	navi_init_utc_from_hhmmss(12, 8, 13, &alr.utc);
	alr.alarmid = 846;
	alr.condition = navi_status_A;
	alr.ackstate = navi_status_V;

	s.afmt = navi_ALR;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &alr, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of ALR failed (%d)\n", result);
	}

	// ALR
	navi_init_alr(&alr);
	navi_init_utc_from_hhmmss(16, 12, 0, &alr.utc);
	alr.alarmid = 7;
	alr.condition = navi_status_V;
	alr.ackstate = navi_status_V;
	strcpy(alr.description, "Captain, take your pills.");

	s.afmt = navi_ALR;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &alr, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of ALR failed (%d)\n", result);
	}

	printf("msglength = %d\n", msglength);
	printf("message = '%s'\n", buffer);

	finished = 0;
	parsed = 0;
	nmread = 0;

	do
	{
		while ((result = navi_parse_msg(buffer + parsed, sizeof(buffer) - parsed,
			sizeof(parsedbuffer), &msgtype, parsedbuffer, &nmread)) == navi_Ok)
		{
			parsed += nmread;

			if (msgtype == navi_af_Approved)
			{
				struct approved_field_t s;
				memmove(&s, parsedbuffer, sizeof(s));

				switch (s.afmt)
				{
				case navi_GBS:
					{
						struct gbs_t *gbs = (struct gbs_t *)((char *)parsedbuffer + sizeof(s));

						printf("Received GBS:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						printf("\tutc = %02u:%02u:%06.3f\n", gbs->utc.hour,
							gbs->utc.min, gbs->utc.sec);
						if (navi_check_validity_number(gbs->experrlat) == navi_Ok)
							printf("\tExpected error in latitude: %f\n", gbs->experrlat);
						if (navi_check_validity_number(gbs->experrlon) == navi_Ok)
							printf("\tExpected error in longitude: %f\n", gbs->experrlon);
						if (navi_check_validity_number(gbs->experralt) == navi_Ok)
							printf("\tExpected error in altitude: %f\n", gbs->experralt);
						if (gbs->failed_id != -1)
							printf("\tFault station ID: %d\n", gbs->failed_id);
						if (navi_check_validity_number(gbs->probability) == navi_Ok)
							printf("\tProbability: %f\n", gbs->probability);
						if (navi_check_validity_number(gbs->estimate) == navi_Ok)
							printf("\tEstimated: %f\n", gbs->estimate);
						if (navi_check_validity_number(gbs->deviation) == navi_Ok)
							printf("\tDeviation: %f\n", gbs->deviation);
					}
					break;
				case navi_GGA:
					{
						struct gga_t *gga = (struct gga_t *)((char *)parsedbuffer + sizeof(s));

						printf("Received GGA:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						if (navi_check_validity_utc(&gga->utc) == navi_Ok)
						{
							printf("\tutc = %02u:%02u:%06.3f\n", gga->utc.hour, gga->utc.min,
								gga->utc.sec);
						}
						if (navi_check_validity_position(&gga->fix) == navi_Ok)
						{
							printf("\tlatitude = %f %s (%d)\n", gga->fix.latitude.offset,
								navi_fixsign_str(gga->fix.latitude.sign), gga->fix.latitude.sign);
							printf("\tlongitude = %f %s (%d)\n", gga->fix.longitude.offset,
								navi_fixsign_str(gga->fix.longitude.sign), gga->fix.longitude.sign);
						}
						printf("\tGPS quality indicator: %i\n", gga->gpsindicator);
						if (gga->nmsatellites != -1)
							printf("\tNm of satellites in use: %i\n", gga->nmsatellites);
						if (navi_check_validity_number(gga->hdop) == navi_Ok)
							printf("\tHDOP: %f\n", gga->hdop);
						if (navi_check_validity_number(gga->antaltitude) == navi_Ok)
							printf("\tAntenna altitude: %f\n", gga->antaltitude);
						if (navi_check_validity_number(gga->geoidalsep) == navi_Ok)
							printf("\tGeoidal separation: %f\n", gga->geoidalsep);
						if (gga->diffdata_age != -1)
							printf("\tAge of differential GPS data: %i\n", gga->diffdata_age);
						if (gga->station_id != -1)
							printf("\tRef. station ID: %i\n", gga->station_id);
					}
					break;
				case navi_GRS:
					{
						int i;
						struct grs_t *grs = (struct grs_t *)((char *)parsedbuffer + sizeof(s));

						printf("Received GRS:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						printf("\tutc = %02u:%02u:%06.3f\n", grs->utc.hour,
							grs->utc.min, grs->utc.sec);
						printf("\tmode = %i\n", grs->mode);
						for (i = 0; i < GRS_MAX_SATELLITES; i++)
						{
							if (navi_check_validity_number(grs->residuals[i]) == navi_Ok)
								printf("\tResidual for %i = %f\n", i, grs->residuals[i]);
						}
					}
					break;
				case navi_GSA:
					{
						int i;
						struct gsa_t *gsa = (struct gsa_t *)((char *)parsedbuffer + sizeof(s));

						printf("Received GSA:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						if (gsa->swmode !=  navi_gsa_NULL)
							printf("\tswitchmode = %i\n", gsa->swmode);
						if (gsa->fixmode != -1)
							printf("\tfixmode = %i\n", gsa->fixmode);
						for (i = 0; i < GSA_MAX_SATELLITES; i++)
						{
							if (gsa->satellites[i] != -1)
								printf("\tSatellite %i = %i\n", i, gsa->satellites[i]);
						}
						if (navi_check_validity_number(gsa->pdop) == navi_Ok)
							printf("\tPDOP = %f\n", gsa->pdop);
						if (navi_check_validity_number(gsa->hdop) == navi_Ok)
							printf("\tHDOP = %f\n", gsa->hdop);
						if (navi_check_validity_number(gsa->vdop) == navi_Ok)
							printf("\tVDOP = %f\n", gsa->vdop);
					}
					break;
				case navi_GST:
					{
						struct gst_t *gst = (struct gst_t *)((char *)parsedbuffer + sizeof(s));

						printf("Received GST:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						printf("\tutc = %02u:%02u:%06.3f\n", gst->utc.hour,
							gst->utc.min, gst->utc.sec);

						if (navi_check_validity_number(gst->rms) == navi_Ok)
							printf("\tRMS = %f\n", gst->rms);
						if (navi_check_validity_number(gst->devmajor) == navi_Ok)
						{
							printf("\tstd dev of semi-major = %f\n", gst->devmajor);
							printf("\tstd dev of semi-minor = %f\n", gst->devminor);
							printf("\torientation of semi-major = %f\n", gst->orientmajor);
						}
						if (navi_check_validity_number(gst->devlaterr) == navi_Ok)
						{
							printf("\tstd dev of latitude err = %f\n", gst->devlaterr);
							printf("\tstd dev of longitude err = %f\n", gst->devlonerr);
						}
						if (navi_check_validity_number(gst->devalterr) == navi_Ok)
							printf("\tstd dev of altitude err = %f\n", gst->devalterr);
					}
					break;
				case navi_GSV:
					{
						int i;
						struct gsv_t *gsv = (struct gsv_t *)((char *)parsedbuffer + sizeof(s));

						printf("Received GSV:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						printf("\tTotal nm of messages: %i\n", gsv->totalnm);
						printf("\tMessage number: %i\n", gsv->msgnm);
						if (gsv->nmsatellites != -1)
							printf("\tTotal satellites in view: %i\n", gsv->nmsatellites);

						for (i = 0; i < GSV_MAX_SATELLITES_PER_MESSAGE && gsv->info[i].id != 0; i++)
						{
							printf("\tSatellite id: %i\n", gsv->info[i].id);
							if (gsv->info[i].vfields & SATINFO_VALID_ORIENTATION)
								printf("\t\tElevation: %i\n", gsv->info[i].elevation);
							if (gsv->info[i].vfields & SATINFO_VALID_ORIENTATION)
								printf("\t\tAzimuth: %i\n", gsv->info[i].azimuth);
							if (gsv->info[i].vfields & SATINFO_VALID_SNR)
								printf("\t\tSNR: %i\n", gsv->info[i].snr);
						}
					}
					break;
				case navi_AAM:
					{
						struct aam_t *aam = (struct aam_t *)((char *)parsedbuffer + sizeof(s));

						printf("Received AAM:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						printf("\tStatus of circle: %s\n", aam->circle == navi_status_A ? "entered" : "not entered");
						printf("\tStatus of perpendicular: %s\n", aam->perp == navi_status_A ? "passed" : "not passed");
						printf("\tArrival circle radius: %f nautical miles\n", aam->radius);
						printf("\tWaypoint ID: %s\n", aam->wpid);
					}
					break;
				case navi_ACK:
					{
						struct ack_t *ack = (struct ack_t *)((char *)parsedbuffer + sizeof(s));

						printf("Received ACK:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						printf("\tLocal alarm identifier: %i\n", ack->alarmid);
					}
					break;
				case navi_ALR:
					{
						struct alr_t *alr = (struct alr_t *)((char *)parsedbuffer + sizeof(s));

						printf("Received ALR:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						printf("\tutc = %02u:%02u:%06.3f\n", alr->utc.hour,
							alr->utc.min, alr->utc.sec);
						printf("\tLocal alarm identifier: %i\n", alr->alarmid);
						printf("\tCondition of alarm: %s\n", alr->condition == navi_status_A ?
							"threshold exceeded" : "not exceeded");
						printf("\tAcknowledge state: %s\n", alr->ackstate == navi_status_A ?
							"acknowledged" : "unacknowledged");
						if (strlen(alr->description) > 0)
							printf("\tAlarm's description: %s\n", alr->description);
					}
					break;
				default:
					break;
				}
			}
		}

		lasterr = navierr_get_last();

		if (lasterr->errclass == navi_CrcEror)
		{
			printf("CRC error\n");
			parsed += nmread;	// advance to parse next message
		}
		else if (lasterr->errclass == navi_MsgNotSupported)
		{
			parsed += nmread;	// advance to parse next message

			switch (msgtype)
			{
			default:
				break;
			}
		}
		else if (lasterr->errclass == navi_NoValidMessage)
		{
			printf("Buffer emptied (%d)\n", lasterr->errclass);
			finished = 1;
		}
		else
		{
			printf("Parsing result = %d\n", lasterr->errclass);
			finished = 1;
		}
	} while (!finished);

	msglength = 0;
	remain = sizeof(buffer);

	// TXT
	navi_init_txt(&txt);
	txt.textid = 25;
	strcpy(txt.textmsg, "DR MODE - ANTENNA FAULT!");

	s.afmt = navi_TXT;
	s.tid = navi_GL;

	result = navi_create_msg(navi_af_Approved, &s, &txt, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of TXT failed (%d)\n", result);
	}

	// Long TXT, splitted into several messages
	result = navi_create_txt_sequence(navi_GL, 25, longtxtmessage, buffer + msglength,
		remain, &nmwritten);
	if (result == navi_Ok)
	{
		msglength += nmwritten;
		remain -= nmwritten;
	}
	else
	{
		printf("Composition of TXT failed (%d)\n", navierr_get_last()->errclass);
	}

	printf("msglength = %d\n", msglength);
	printf("message = '%s'\n", buffer);

	finished = 0;
	parsed = 0;
	nmread = 0;

	do
	{
		while ((result = navi_parse_msg(buffer + parsed, sizeof(buffer) - parsed,
			sizeof(parsedbuffer), &msgtype, parsedbuffer, &nmread)) == navi_Ok)
		{
			parsed += nmread;

			if (msgtype == navi_af_Approved)
			{
				struct approved_field_t s;
				memmove(&s, parsedbuffer, sizeof(s));

				switch (s.afmt)
				{
				case navi_TXT:
					{
						struct txt_t *txt = (struct txt_t *)((char *)parsedbuffer + sizeof(s));

						printf("Received TXT:\n\ttalker id = %s (%d)\n",
							navi_talkerid_str(s.tid), s.tid);
						printf("\tTotal nm of messages: %i\n", txt->totalnm);
						printf("\tMessage number: %i\n", txt->msgnm);
						printf("\tText identifier: %i\n", txt->textid);
						if (strlen(txt->textmsg) > 0)
						{
							printf("\tText message: %s\n", txt->textmsg);
						}
					}
					break;
				default:
					break;
				}
			}
		}

		lasterr = navierr_get_last();

		if (lasterr->errclass == navi_CrcEror)
		{
			printf("CRC error\n");
			parsed += nmread;	// advance to parse next message
		}
		else if (lasterr->errclass == navi_MsgNotSupported)
		{
			parsed += nmread;	// advance to parse next message

			switch (msgtype)
			{
			default:
				break;
			}
		}
		else if (lasterr->errclass == navi_NoValidMessage)
		{
			printf("Buffer emptied (%d)\n", lasterr->errclass);
			finished = 1;
		}
		else
		{
			printf("Parsing result = %d\n", lasterr->errclass);
			finished = 1;
		}
	} while (!finished);

#ifdef _MSC_VER
	printf("sizeof struct aam_t = %Iu\n", sizeof(struct aam_t));
	printf("sizeof struct ack_t = %Iu\n", sizeof(struct ack_t));
	printf("sizeof struct alr_t = %Iu\n", sizeof(struct alr_t));
	printf("sizeof struct dtm_t = %Iu\n", sizeof(struct dtm_t));
	printf("sizeof struct gbs_t = %Iu\n", sizeof(struct gbs_t));
	printf("sizeof struct gga_t = %Iu\n", sizeof(struct gga_t));
	printf("sizeof struct gll_t = %Iu\n", sizeof(struct gll_t));
	printf("sizeof struct gns_t = %Iu\n", sizeof(struct gns_t));
	printf("sizeof struct grs_t = %Iu\n", sizeof(struct grs_t));
	printf("sizeof struct gsa_t = %Iu\n", sizeof(struct gsa_t));
	printf("sizeof struct gst_t = %Iu\n", sizeof(struct gst_t));
	printf("sizeof struct gsv_t = %Iu\n", sizeof(struct gsv_t));
	printf("sizeof struct rmc_t = %Iu\n", sizeof(struct rmc_t));
	printf("sizeof struct txt_t = %Iu\n", sizeof(struct txt_t));
	printf("sizeof struct vtg_t = %Iu\n", sizeof(struct vtg_t));
	printf("sizeof struct zda_t = %Iu\n", sizeof(struct zda_t));
#else
	printf("sizeof struct aam_t = %zu\n", sizeof(struct aam_t));
	printf("sizeof struct ack_t = %zu\n", sizeof(struct ack_t));
	printf("sizeof struct alr_t = %zu\n", sizeof(struct alr_t));
	printf("sizeof struct dtm_t = %zu\n", sizeof(struct dtm_t));
	printf("sizeof struct gbs_t = %zu\n", sizeof(struct gbs_t));
	printf("sizeof struct gga_t = %zu\n", sizeof(struct gga_t));
	printf("sizeof struct gll_t = %zu\n", sizeof(struct gll_t));
	printf("sizeof struct gns_t = %zu\n", sizeof(struct gns_t));
	printf("sizeof struct grs_t = %zu\n", sizeof(struct grs_t));
	printf("sizeof struct gsa_t = %zu\n", sizeof(struct gsa_t));
	printf("sizeof struct gst_t = %zu\n", sizeof(struct gst_t));
	printf("sizeof struct gsv_t = %zu\n", sizeof(struct gsv_t));
	printf("sizeof struct rmc_t = %zu\n", sizeof(struct rmc_t));
	printf("sizeof struct txt_t = %zu\n", sizeof(struct txt_t));
	printf("sizeof struct vtg_t = %zu\n", sizeof(struct vtg_t));
	printf("sizeof struct zda_t = %zu\n", sizeof(struct zda_t));
#endif // MSVC_VER

	return 0;
}

