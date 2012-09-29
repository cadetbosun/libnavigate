/*
 * alm.cpp - implementation of Alm_t class
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

#include <libnavigate/c++/alm.hpp>

namespace libnavigate
{

Alm_t::Alm_t(const TalkerId_t &tid) : Message_t(MessageType_t::ALM)
{
	navi_init_alm(&m_value, tid.toTalkerIdCode());
}

Alm_t::~Alm_t() { }

TalkerId_t Alm_t::talkerId() const
	{ return TalkerId_t::fromTalkerIdCode(m_value.tid); }

int Alm_t::nmOfSatellites() const
	{ return m_value.nmsatellites; }

int Alm_t::totalNmOfMessages() const
	{ return m_value.totalnm; }

int Alm_t::messageNumber() const
	{ return m_value.msgnm; }

unsigned int Alm_t::satellitePrn(int satIdx) const
	{ return m_value.almlist[satIdx].satelliteprn; }

unsigned int Alm_t::gpsWeek(int satIdx) const
	{ return m_value.almlist[satIdx].gpsweek; }

unsigned int Alm_t::svHealth(int satIdx) const
	{ return m_value.almlist[satIdx].svhealth; }

unsigned int Alm_t::eccentricity(int satIdx) const
	{ return m_value.almlist[satIdx].e; }

unsigned int Alm_t::almanacReferenceTime(int satIdx) const
	{ return m_value.almlist[satIdx].toa; }

unsigned int Alm_t::inclinationAngle(int satIdx) const
	{ return m_value.almlist[satIdx].sigmai; }

unsigned int Alm_t::rateOfRightAscension(int satIdx) const
	{ return m_value.almlist[satIdx].omegadot; }

unsigned int Alm_t::sqrtOfSemiMajorAxis(int satIdx) const
	{ return m_value.almlist[satIdx].sqrtsemiaxis; }

unsigned int Alm_t::argumentOfPerigee(int satIdx) const
	{ return m_value.almlist[satIdx].omega; }

unsigned int Alm_t::longitudeOfAscensionNode(int satIdx) const
	{ return m_value.almlist[satIdx].omega0; }

unsigned int Alm_t::meanAnomaly(int satIdx) const
	{ return m_value.almlist[satIdx].m0; }

unsigned int Alm_t::clockParameter0(int satIdx) const
	{ return m_value.almlist[satIdx].af0; }

unsigned int Alm_t::clockParameter1(int satIdx) const
	{ return m_value.almlist[satIdx].af1; }

void Alm_t::setTalkerId(const TalkerId_t &tid)
	{ m_value.tid = tid.toTalkerIdCode(); }

void Alm_t::setNmOfSatellites(int value)
	{ m_value.nmsatellites = value; }

void Alm_t::setTotalNmOfMessages(int value)
	{ m_value.totalnm = value; }

void Alm_t::setMessageNumber(int value)
	{ m_value.msgnm = value; }

void Alm_t::setSatellitePrn(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].satelliteprn = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_SATELLITEPRN;
}

void Alm_t::setGpsWeek(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].gpsweek = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_GPSWEEK;
}

void Alm_t::setSvHealth(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].svhealth = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_SVHEALTH;
}

void Alm_t::setEccentricity(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].e = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_E;
}

void Alm_t::setAlmanacReferenceTime(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].toa = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_TOA;
}

void Alm_t::setInclinationAngle(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].sigmai = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_SIGMAI;
}

void Alm_t::setRateOfRightAscension(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].omegadot = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_OMEGADOT;
}

void Alm_t::setSqrtOfSemiMajorAxis(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].sqrtsemiaxis = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_SQRTSEMIAXIS;
}

void Alm_t::setArgumentOfPerigee(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].omega = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_OMEGA;
}

void Alm_t::setLongitudeOfAscensionNode(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].omega0 = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_OMEGA0;
}

void Alm_t::setMeanAnomaly(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].m0 = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_M0;
}

void Alm_t::setClockParameter0(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].af0 = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_AF0;
}

void Alm_t::setClockParameter1(int satIdx, unsigned int value)
{
	m_value.almlist[satIdx].af1 = value;
	m_value.almlist[satIdx].vfields |= GPSALM_VALID_AF1;
}

void Alm_t::clearMessage()
{
	navi_init_alm(&m_value, TalkerId_t::Unknown);
}

Alm_t::operator const void *() const
	{ return (const void *)&m_value; }

Alm_t::operator void *()
	{ return &m_value; }

}

