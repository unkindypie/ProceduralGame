#include "Sublevel.h"
int randomNumber(int minNum, int maxNum) {
	int result;
	int lowNum = 0;
	int hiNum = 0;
	if (minNum < maxNum) {
		lowNum = minNum;
		hiNum = maxNum + 1;
	}
	else {
		lowNum = maxNum + 1;
		hiNum = minNum;
	}
	result = (rand() % (hiNum - lowNum)) + lowNum;
	return result;
}

Sublevel::Sublevel()
{

}
Sublevel::Sublevel(size_t x, size_t y) //����������� ��� �������� ��������� � ������������ ������� � �������
{
	this->x = x;
	this->y = y;
	int times = 0; //���������� ����� ��� ���� ������, ����� ����������� ������ ��������� ��� ���������� ����������� ������ ����� �� ����� �������, ���
	//�� ���������� ������� ����� ������ ������������� ������� � ��������� ������ � ����������� ����
	do //������
	{
		width = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
		times++;
	} while (width + x > X_SIZE && times < MAX_RAND_LOOP_COUNT); //���� ������� �� �������� ������� � ���������� �������� ������ �������������
	times = 0;
	do//������
	{
		height = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
		times++;
	} while (height + y > Y_SIZE && times < MAX_RAND_LOOP_COUNT);

	for (int i = 0; i < height; i++) //����� ��������� ������ ���������� ������������ ������ Content
	{
		map.push_back(vector<Content*>(width));
	}
	for (int i = 0; i < height; i++)  //���� ������� �� ������� ��� ������������ ������
	{
		for (int j = 0; j < width; j++)
		{
			if(i == 0 || j == 0 || j == width - 1 || i == height - 1)//���� ��� �������, �� ������ �������
			{
				map[i][j] = new Block(x + j, y + i, brick);
			}
			else//���� ���, �� �������
			{
				map[i][j] = new Block(x + j, y + i, none);
			}
		}
	}
}
Sublevel::Sublevel(size_t x, size_t y, size_t holeCoordX, size_t holeCoordY, bool holeType)  //����������� ��� �������� ��������� � ����������� � ����� �������(holeType = 0 - ����, 1 - �����)
{
	bool doesHoleExist = 0;
	while(!doesHoleExist || enterPosX >= width - 2 || enterPosY >= height-2){ 
		map.clear();
		this->x = x;
		this->y = y;

		if(holeType)//� ����������� �� ����, ���� ��� ��� ����� ��������� ���������� � ������������� ����������
		{
			exitPosX = holeCoordX;
			exitPosY = holeCoordY;
		}
		else
		{
			enterPosX = holeCoordX;
			enterPosY = holeCoordY;
		}
		int times = 0; //���������� ����� ��� ���� ������, ����� ����������� ������ ��������� ��� ���������� ����������� ������ ����� �� ����� �������, ���
		//�� ���������� ������� ����� ������ ������������� ������� � ��������� ������ � ����������� ����
		do //������
		{
			width = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
			times++;
		} while (width + x > X_SIZE && times < MAX_RAND_LOOP_COUNT); //���� ������� �� �������� ������� � ���������� �������� ������ �������������
		times = 0;
		do//������
		{
			height = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
			times++;
		} while (height + y > Y_SIZE && times < MAX_RAND_LOOP_COUNT);

		for (int i = 0; i < height; i++) //����� ��������� ������ ���������� ������������ ������ Content
		{
			map.push_back(vector<Content*>(width));
		}
		for (int i = 0; i < height; i++)  //���� ������� �� ������� ��� ������������ ������
		{
			for (int j = 0; j < width; j++)
			{
				if (i == 0 || j == 0 || j == width - 1 || i == height - 1)//���� ��� �������, �� ������ �������
				{
					map[i][j] = new Block(x + j, y + i, brick);
				}
				else//���� ���, �� �������
				{
					map[i][j] = new Block(x + j, y + i, none);
				}
				if(i == holeCoordY && j == holeCoordX)//����� �� ���������
				{
					map[i][j] = new Block(x + j, y + i, none);
					doesHoleExist = 1;
				}
			}
		}
	}
}
Sublevel::Sublevel(size_t x, size_t y, int lastWidth, size_t holeCoordX, size_t holeCoordY, bool holeType, LevelGenerationState & gState) //������������ ������ � ���������� �����
{
	bool doesHoleExist = 0;
	size_t iterationsCounter = 0;
	while (!doesHoleExist || enterPosX > width || enterPosY > height) {
		iterationsCounter++;
		if(iterationsCounter > MAX_RAND_LOOP_COUNT) //� ������ ���� ����������� ����� � ����������� ����, �� ������ �� ���� � ���������� ��� �������
		{
			gState = restart;
			break;
		}
		map.clear();
		this->x = x;
		this->y = y;

		if (holeType)//� ����������� �� ����, ���� ��� ��� ����� ��������� ���������� � ������������� ����������
		{
			exitPosX = holeCoordX;
			exitPosY = holeCoordY;
		}
		else
		{
			enterPosX = holeCoordX;
			enterPosY = holeCoordY;
		}
		int times = 0; //���������� ����� ��� ���� ������, ����� ����������� ������ ��������� ��� ���������� ����������� ������ ����� �� ����� �������, ���
		//�� ���������� ������� ����� ������ ������������� ������� � ��������� ������ � ����������� ����

		width = lastWidth; 
		times = 0;
		do//������
		{
			height = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
			times++;
		} while (height + y > Y_SIZE && times < MAX_RAND_LOOP_COUNT);
		
		for (int i = 0; i < height; i++) //����� ��������� ������ ���������� ������������ ������ Content
		{
			map.push_back(vector<Content*>(width));
		}
		for (int i = 0; i < height; i++)  //���� ������� �� ������� ��� ������������ ������
		{
			for (int j = 0; j < width; j++)
			{
				if (i == 0 || j == 0 || j == width - 1 || i == height - 1)//���� ��� �������, �� ������ �������
				{
					map[i][j] = new Block(x + j, y + i, brick);
				}
				else//���� ���, �� �������
				{
					map[i][j] = new Block(x + j, y + i, none);
				}
				if (i == holeCoordY && j == holeCoordX)//����� �� ���������
				{
					map[i][j] = new Block(x + j, y + i, none);
					doesHoleExist = 1;
				}
			}
		}
	}
}

Sublevel::Sublevel(size_t x, size_t y, int lastWidth) // ���������� � ������������ ������� 
{

	this->x = x;
	this->y = y;
	int times = 0;
	width = lastWidth;
	times = 0;
	do
	{
		height = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);//rand() % 20;
		times++;
	} while (height + y > Y_SIZE && times < MAX_RAND_LOOP_COUNT);
	for (int i = 0; i < height; i++)
	{
		map.push_back(vector<Content*>(width));
	}
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 || j == 0 || j == width - 1 || i == height - 1)
			{
				map[i][j] = new Block(x + j, y + i, brick);
			}
			else
			{
				map[i][j] = new Block(x + j, y + i, none);
			}
		}
	}

}
Sublevel::Sublevel(size_t x, size_t y, hole holePosition, holeMode mode) //����������� ��� �������� ��������� � ������������(holeType = 0 - ����, 1 - �����)
{
	this->x = x;
	this->y = y;
	
	int times = 0; //���������� ����� ��� ���� ������, ����� ����������� ������ ��������� ��� ���������� ����������� ������ ����� �� ����� �������, ���
	//�� ���������� ������� ����� ������ ������������� ������� � ��������� ������ � ����������� ����
	do //������
	{
		width = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
		times++;
	} while (width + x > X_SIZE && times < MAX_RAND_LOOP_COUNT); //���� ������� �� �������� ������� � ���������� �������� ������ �������������
	times = 0;
	do//������
	{
		height = randomNumber(MIN_RAND_SIZE, MAX_RAND_SIZE);
		times++;
	} while (height + y > Y_SIZE && times < MAX_RAND_LOOP_COUNT);
	//��������� ��������� ����� � ������
	switch (mode)
	{
	case enter:
		generateEnterExit(enterPosX, enterPosY, width, height, holePosition);
		break;
	case exit_:
		generateEnterExit(exitPosX, exitPosY, width, height, holePosition);
		break;
	case enter_and_exit:
		generateEnterExit(enterPosX, enterPosY, width, height, holePosition);
		generateEnterExit(exitPosX, exitPosY, width, height, holePosition);
		break;
	default:
		break;
	}

	for (int i = 0; i < height; i++) //����� ��������� ������ ���������� ������������ ������ Content
	{
		map.push_back(vector<Content*>(width));
	}
	for (int i = 0; i < height; i++)  //���� ������� �� ������� ��� ������������ ������
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 || j == 0 || j == width - 1 || i == height - 1)//���� ��� �������, �� ������ �������
			{
				map[i][j] = new Block(x + j, y + i, brick);
			}
			else //���� ���, �� �������
			{
				map[i][j] = new Block(x + j, y + i, none);
			}
			if (i == enterPosY && j == enterPosX || i == exitPosY && j == exitPosX) //������ ����� ���� ����
			{
				map[i][j] = new Block(x + j, y + i, none);
				
			}
		}
	}
	
}
void Sublevel::generateEnterExit(int & coordX, int & coordY, size_t width, size_t height, hole holePosition)
{
	switch (holePosition) //�� ����� ����� ������� �������
	{
	case left:

		coordY = randomNumber(3, height-2);
		coordX = 0;
		break;
	case right:
		coordY = randomNumber(3, height-2);
		coordX = width-1;
		break;
	case top:
		coordY = 0;
		coordX = randomNumber(3, width-2);
		break;
	case down:
		coordY = height-1;
		coordX = randomNumber(3, width-2);
		break;
	default:
		break;
	}
}
void Sublevel::getExitGlobalCoords(int & x, int & y)
{
	x = map[exitPosY][exitPosX]->getX();
	y = map[exitPosY][exitPosX]->getY();
}
void Sublevel::addExit(hole holePosition)
{
	generateEnterExit(exitPosX, exitPosY, width, height, holePosition); //��������� ����������
	map[exitPosY][exitPosX] = new Block(x + exitPosX, y + exitPosY, none); //������ �� ��� ������ ����
}
void Sublevel::addEnter(hole holePosition)
{
	generateEnterExit(enterPosX, enterPosY, width, height, holePosition); //��������� ����������
	map[enterPosY][enterPosX] = new Block(x + enterPosX, y + enterPosY, none); //������ �� ��� ������ ����
}
size_t Sublevel::getX()
{
	return x;
}
size_t Sublevel::getY()
{
	return y;
}
size_t Sublevel::getHeight()
{
	return height;
}
size_t Sublevel::getWidth()
{
	return width;
}
size_t Sublevel::getEnterPosX()
{
	return enterPosX;
}
size_t Sublevel::getEnterPosY()
{
	return enterPosY;
}
size_t Sublevel::getExitPosX()
{
	return exitPosX;
}
size_t Sublevel::getExitPosY()
{
	return exitPosY;
}
vector<vector<Content*>> & Sublevel::getMap()
{
	return map;
}

