/*******************************************************************************
* ASTex:                                                                       *
* Copyright (C) IGG Group, ICube, University of Strasbourg, France             *
*                                                                              *
* This library is free software; you can redistribute it and/or modify it      *
* under the terms of the GNU Lesser General Public License as published by the *
* Free Software Foundation; either version 2.1 of the License, or (at your     *
* option) any later version.                                                   *
*                                                                              *
* This library is distributed in the hope that it will be useful, but WITHOUT  *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License  *
* for more details.                                                            *
*                                                                              *
* You should have received a copy of the GNU Lesser General Public License     *
* along with this library; if not, write to the Free Software Foundation,      *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.           *
*                                                                              *
* Web site: https://astex-icube.github.io                                      *
* Contact information: astex@icube.unistra.fr                                  *
*                                                                              *
*******************************************************************************/



#include "quilting_interp_cont.h"

int main(int argc, char** argv)
{

	QuiltingInterpCont q;

	if (argc == 2)
		q.loadInput(std::string(argv[1]));
	else
		q.loadInput(TEMPO_PATH+"quilting_input.png");

//	q.setFirstTile(600,90);

	q.computeFittingTilesPathCutInterp(512,512,64,16,7,5,4096);
	q.saveOutput(TEMPO_PATH+"quilting_path_output.png");


  return EXIT_SUCCESS;
}

