#include "clip.h"

namespace egc {

	std::vector<int> computeCSCode(std::vector<vec3> clipWindow, const vec3 p) {
		std::vector<int> code;
		code.push_back(0);
		code.push_back(0);
		code.push_back(0);
		code.push_back(0);
		
		 
		//TO DO - compute the code for the point given as argument
		if (p.y < clipWindow[0].y)
		{
			code[0] = 1;
		}
		if (p.x < clipWindow[0].x)
		{
			code[3] = 1;
		}
		if (p.x > clipWindow[2].x)
		{
			code[2] = 1;
		}
		if (p.y > clipWindow[2].y)
		{
			code[1] = 1;
		}
		return code;
	}

	bool simpleRejection(std::vector<int> cod1, std::vector<int> cod2) {

		std::vector<int> ans;
		int nr_of_zeros = 0;
		for (int i = 0; i < 4; i++)
		{
			if (!(cod1[i] & cod2[i]))
				nr_of_zeros++;
		}
		if (nr_of_zeros == 4)
			return false;
		return true;
	}

	bool simpleAcceptance(std::vector<int> cod1, std::vector<int> cod2) {
		//TO DO - write the code to determine if the two input codes represent 
		//points in the SIMPLE ACCEPTANCE case
		for (int i = 0; i < 4; i++)
		{
			if (cod1[i] | cod2[i])
				return false;
		}
		return true;
	}
	bool isInsideDisplayArea(std::vector<int> cod)
	{
		for (int i = 0; i < 4; i++)
		{
			if (cod[i] != 0)
				return false;
		}
		return true;
	}
	//function returns -1 if the line segment cannot be clipped
	int lineClip_CohenSutherland(std::vector<vec3> clipWindow, vec3& p1, vec3& p2) {
		//TO DO - implement the Cohen-Sutherland line clipping algorithm - consult the laboratory work
		bool FINISHED = false;
		while (!FINISHED) {
			std::vector<int> COD1 = computeCSCode(clipWindow, p1); // compute the 4 digits code for P(x1, y1)
			std::vector<int> COD2 = computeCSCode(clipWindow, p2); // compute the 4 digits code for P(x2, y2)
			bool RESPINS = simpleRejection(COD1, COD2); // test for simple rejection case
			if (RESPINS) {
				FINISHED = true;
			}
			else {
				bool DISPLAY = simpleAcceptance(COD1, COD2); // test for simple acceptance case
				if (DISPLAY) {
					FINISHED = true;
				}
				else {
					if (isInsideDisplayArea(COD1)) { //ca sa nu mai faci un if le da swap
						std::swap(COD1, COD2);
						std::swap(p1, p2);
					}
					if (COD1[0] == 1 && p2.y != p1.y) { // eliminate the segment above the display area
						p1.x += (p2.x - p1.x) * (clipWindow[0].y - p1.y) / (p2.y - p1.y);
						p1.y = clipWindow[0].y;
					}
					else if (COD1[1] == 1 && p2.y != p1.y) { // eliminate the segment under the display area
						p1.x += (p2.x - p1.x) * (clipWindow[2].y - p1.y) / (p2.y - p1.y);
						p1.y = clipWindow[2].y;
					}
					else if (COD1[2] == 1 && p2.x != p1.x) { // eliminate the segment on the right of the display area
						p1.y += (p2.y - p1.y) * (clipWindow[2].x - p1.x) / (p2.x - p1.x);
						p1.x = clipWindow[2].x;
					}
					else if (COD1[3] == 1 && p2.x != p1.x) { // eliminate the segment on the left of the display area
						p1.y += (p2.y - p1.y) * (clipWindow[0].x - p1.x) / (p2.x - p1.x);
						p1.x = clipWindow[0].x;
					}
				}
			}
		}


		return 0;
	}
}

