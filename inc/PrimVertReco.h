/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  Rafał Lalik <rafal.lalik@ph.tum.de>
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
 *
 */

#ifndef PRIMVERTRECO_H
#define PRIMVERTRECO_H

#include <hparticlecand.h>

typedef std::pair<TVector3, TLorentzVector> hades_track;
class PrimVertReco
{
public:
	PrimVertReco();
	PrimVertReco(size_t ntracks);

	void insert_track(HParticleCand* track);
	void insert_track(const hades_track & track);
	void insert_track(const TVector3 & base, const TLorentzVector & track);
	
	virtual ~PrimVertReco();

	TVector3 calc() const;
	void clear();

	std::vector<hades_track> get_tracks() const { return tracks; }

protected:

private:
	size_t maxtracks;

	std::vector<hades_track> tracks;
};

#endif // PRIMVERTRECO_H
