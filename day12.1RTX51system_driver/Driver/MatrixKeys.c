#include "MatrixKeys.h"

// ����״̬��¼����¼���е�
static u16 key_state = 0xFFFF;

//======================================================================================
//(row * ROW_NUM) + col = idx(��ť�±�)
// ����ǰһ��״̬Ϊ̧��
#define IS_KEY_UP(row, col) ((key_state >> (row * ROW_NUM + col)) & 0x01) == KEY_UP
// ����ǰһ��״̬Ϊ����
#define IS_KEY_DOWN(row, col) ((key_state >> (row * ROW_NUM + col)) & 0x01) == KEY_DOWN
//======================================================================================

//======================================================================================
// ��¼״̬Plus
#define SET_KEY_UP(row, col) key_state |= (1 << (row * ROW_NUM + col))
#define SET_KEY_DOWN(row, col) key_state &= ~(1 << (row * ROW_NUM + col))
//======================================================================================

//======================================================================================
// �жϵڼ���
static u8 COL_STATE(u8 col)
{
	if (col == 0)
		return COL1;
	if (col == 1)
		return COL2;
	if (col == 2)
		return COL3;
	if (col == 3)
		return COL4;
	return COL1;
}
// �ж���һ�����
static void ROW_OUT(u8 row)
{
	if (row == 0)
	{
		ROW1 = 0;
		ROW2 = 1;
		ROW3 = 1;
		ROW4 = 1;
	}
	if (row == 1)
	{
		ROW1 = 1;
		ROW2 = 0;
		ROW3 = 1;
		ROW4 = 1;
	}
	if (row == 2)
	{
		ROW1 = 1;
		ROW2 = 1;
		ROW3 = 0;
		ROW4 = 1;
	}
	if (row == 3)
	{
		ROW1 = 1;
		ROW2 = 1;
		ROW3 = 1;
		ROW4 = 0;
	}
}
//======================================================================================

void MK_init()
{
	KEYS_PIN_INIT();
}
void MK_scan(u16 *state)
{
	u8 i, j;
	// j : row; i : col;
	for (j = 0; j < ROW_NUM; j++)
	{
		ROW_OUT(j);
		for (i = 0; i < COL_NUM; i++)
		{
			if (COL_STATE(i) == KEY_DOWN && IS_KEY_UP(j, i))
			{
				MK_on_keydown(j, i); // ��ť���µ�ƽΪ��
				SET_KEY_DOWN(j, i);
			}
			else if (COL_STATE(i) == KEY_UP && IS_KEY_DOWN(j, i))
			{
				MK_on_keyup(j, i); // ��ţ̌���ƽΪ��
				SET_KEY_UP(j, i);
			}
		}
	}
}