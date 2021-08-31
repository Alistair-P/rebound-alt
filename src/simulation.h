// TES is an open source integration package for modelling exoplanet evolution.
// Copyright (C) <2021>  <Peter Bartram, Alexander Wittig>

// TES is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>. 

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <stdint.h>
#include <stdio.h>

typedef struct UNIVERSAL_VARS UNIVERSAL_VARS;
typedef struct DHEM DHEM;
typedef struct RADAU RADAU;

/**
 * This is the main error enum for the simulation.
 */
typedef enum ERROR_SIMULATION_
{
	SIM_ERROR_OK = 0,	/// Everything is OK.

}ERROR_SIMULATION;


typedef struct _SIMULATION_
{
	// ##############################################
	// To keep / refactor
	// ##############################################
	double * mass;						/// Initial particle masses
	double * X_dh;						/// Memory for current state in dh coords.
	double * Q_dh;						/// Current state in dh coords.
	double * P_dh;						/// Current state in dh coords.

	// ##############################################
	// To throw away
	// ##############################################
	// RHS function pointers to be provided by all force models.
	void (*f_rhs)(struct reb_simulation* r, double * dQ, double * dP, double * dQ_dot,
					double * dP_dot, double * dQ_ddot, double * dP_ddot,
									uint32_t stageNumber, double * cs1, double * cs2);							
	void (*fStartOfStep)(struct reb_simulation* r, double t0, double h, double * hArr, uint32_t z_stagesPerStep, uint32_t z_rebasis);
	uint32_t (*fRectify)(struct reb_simulation* r, double t, double * Q, double * P,
								double * dQ, double * dP, uint32_t * rectifiedArray, uint32_t stageNumber);
		void (*fPerformSummation)(struct reb_simulation* r, double *, double *, double *, double *, uint32_t);
}SIMULATION;


SIMULATION * Simulation_Init(struct reb_simulation* r, uint32_t z_n);
void Simulation_Free(void);

#endif /* SIMULATION_H_ */
