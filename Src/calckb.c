#include "calckb.h"
#include "kb.h"
#include "stm32f4xx_hal.h"
#include "calc.h"

char layoutNum[4][3] = {
		{'1', '2', '3'},
		{'4', '5', '6'},
		{'7', '8', '9'},
		{'#', '0', '='}
};

char layoutSym[4][3] = {
		{'+', '-', '.'},
		{'*', '/', '.'},
		{'.', '.', '.'},
		{'#', '<', 'C'}
};

char getKey(void) {
	uint8_t key;
	uint8_t Row[4] = {ROW1, ROW2, ROW3, ROW4};
	for (int i = 0; i < 4; i++) {
		key = Check_Row(Row[i]);
		if (key == 0x01) {
			return getLayout() ? layoutNum[i][2] : layoutSym[i][2];
		}
		if (key == 0x02) {
			return getLayout() ? layoutNum[i][1] : layoutSym[i][1];
		}
		if (key == 0x04) {
			return getLayout() ? layoutNum[i][0] : layoutSym[i][0];
		}
	}
	return 0;
}
