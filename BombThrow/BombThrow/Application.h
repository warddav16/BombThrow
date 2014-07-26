#pragma once
class CApplication
{
public:
	CApplication(void);
	~CApplication(void);

	void Quit();

private:
	void Startup();
	void Close();
	void Run();
};

