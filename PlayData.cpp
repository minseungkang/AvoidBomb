#include "PlayData.h"
FILE* PlayData::fp = fopen((FileUtils::getInstance()->fullPathForFilename("PlayData.txt")).c_str(), "r+");

int PlayData::writeRecord()
{

	if (fp != nullptr)
	{
		rewind(fp);
		int deathRecord;
		for (int i = 0; i < StageManager::currentStage - 1; i++)
		{
			fscanf(fp, "%d\n");
		}
		if (fscanf(fp, "%d\n", &deathRecord) == -1)
		{
			fprintf(fp, "%d\n", StageManager::playerNode->getDeathCnt());
			return StageManager::playerNode->getDeathCnt();
			
		}//����� ���� ���
		else
		{

			if (deathRecord <= StageManager::playerNode->getDeathCnt()) 
			{
				return deathRecord;
			}// ��� ���� ������ ���
			else
			{
				for (int i = 0; i < StageManager::currentStage - 1; i++)
				{
					fscanf(fp, "%d\n");
				}
				fprintf(fp, "%d\n", StageManager::playerNode->getDeathCnt());
				return StageManager::playerNode->getDeathCnt();
			}// ��� ���� ����
		}//����� �ִ� ���

	}
}
