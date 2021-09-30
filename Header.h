#pragma once

enum essential {
	minIndex = 0,
	gameName = 1,
	maxIndex = 4,
	rowAndCol = 5,
	maxPlayedNum = 9,
	gomokuDiag = 18,
	gomokuRowAndCol = 19
};

enum error {
	success = 0,
	argNum = 2,
	didQuit = 20,
	didDraw = 30,
	invalid_initiation = 40,
	invalid_gameName = 50,
	b_alloc = 60
};

enum nineIndex {
	rowOneOne = 6,
	rowOneTwo = 7,
	rowOneThree = 8,
	rowTwoOne = 11,
	rowTwoTwo = 12,
	rowTwoThree = 13,
	rowThreeOne = 16,
	rowThreeTwo = 17,
	rowThreeThree = 18
};
