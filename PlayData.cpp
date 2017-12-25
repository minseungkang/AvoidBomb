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
			
		}//기록이 없는 경우
		else
		{

			if (deathRecord <= StageManager::playerNode->getDeathCnt()) 
			{
				return deathRecord;
			}// 기록 갱신 실패한 경우
			else
			{
				for (int i = 0; i < StageManager::currentStage - 1; i++)
				{
					fscanf(fp, "%d\n");
				}
				fprintf(fp, "%d\n", StageManager::playerNode->getDeathCnt());
				return StageManager::playerNode->getDeathCnt();
			}// 기록 갱신 성공
		}//기록이 있는 경우

	}
}
