#pragma once

/// <summary>
/// ���̺� �� �ε��ϵ��� ����
/// </summary>
class SaveLoadManager : public singletonBase<SaveLoadManager>
{
private :
	
public :
	HRESULT Init();

	// SAVE //
	void SaveData();
	
	// LOAD //
	void LoadData();
	map<string, string> LoadIniFromIni();
};

